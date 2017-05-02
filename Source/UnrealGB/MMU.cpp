// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealGB.h"
#include "MMU.h"
#include "CPU.h"
#include "GPU.h"
#include <stdio.h>
#include <iostream>

UMMU::UMMU()
{
	_wram = new BYTE[SIZE_WRAM];
	_eram = new BYTE[SIZE_ERAM];
	_zram = new BYTE[SIZE_ZRAM];
}

UMMU::~UMMU()
{
}

// Get the size of a file
long UMMU::getFileSize(FILE *file)
{
		long lCurPos, lEndPos;
		lCurPos = ftell(file);
		fseek(file, 0, 2);
		lEndPos = ftell(file);
		fseek(file, lCurPos, 0);
		return lEndPos;
}

int UMMU::LoadRom(FString filePath)
{
		FILE *file = NULL; 

		if ((file = fopen(TCHAR_TO_ANSI(*filePath), "rb")) == NULL)
		{
			// file not opened
			return -1;
		}

		long fileSize = getFileSize(file);
		_rom = new BYTE[fileSize];
		fread(_rom, fileSize, 1, file);
		
		return fileSize;
}

void UMMU::Reset()
{
	for (int i = 0; i < SIZE_WRAM; i++) {
		_wram[i] = 0;
		_eram[i] = 0;
	}

	for (int i = 0; i < SIZE_ZRAM; i++) {
		_zram[i] = 0;
	}

	bInBios = true;
	//MMU._ie = 0; //Whats that
	//MMU._if = 0;
}

BYTE UMMU::rb(WORD addr)
{
	switch (addr & 0xF000)
	{
		// BIOS (256b)/ROM0
	case 0x0000:
		if (bInBios)
		{
			if (addr < 0x0100)
				return _bios[addr];
			else if (CPU->_register.pc == 0x0100)
				bInBios = false;
		}

		return _rom[addr];

		// ROM0
	case 0x1000:
	case 0x2000:
	case 0x3000:
		return _rom[addr];

		// ROM1 (unbanked) (16k)
	case 0x4000:
	case 0x5000:
	case 0x6000:
	case 0x7000:
		return _rom[addr];

		// Graphics: VRAM (8k)
	case 0x8000:
	case 0x9000:
		break; //return GPU._vram[addr & 0x1FFF] todo

		// External RAM (8k)
	case 0xA000:
	case 0xB000:
		return _eram[addr & 0x1FFF];

		// Working RAM (8k)
	case 0xC000:
	case 0xD000:
		return _wram[addr & 0x1FFF];

		// Working RAM shadow
	case 0xE000:
		return _wram[addr & 0x1FFF];

		// Working RAM shadow, I/O, Zero-page RAM
	case 0xF000:
		switch (addr & 0x0F00)
		{
			// Working RAM shadow
		case 0x000: case 0x100: case 0x200: case 0x300:
		case 0x400: case 0x500: case 0x600: case 0x700:
		case 0x800: case 0x900: case 0xA00: case 0xB00:
		case 0xC00: case 0xD00:
			return _wram[addr & 0x1FFF];

			// Graphics: object attribute memory
			// OAM is 160 bytes, remaining bytes read as 0
		case 0xE00:
			if (addr < 0xFEA0)
				return 0;// GPU._oam[addr & 0xFF]; todo
			else
				return 0;

			// Zero-page
		case 0xF00:
			if (addr >= 0xFF80)
			{
				return _zram[addr & 0x7F];
			}
			else
			{
				// I/O control handling
				switch (addr & 0x00F0)
				{
					// GPU (64 registers)
				case 0x40: case 0x50: case 0x60: case 0x70:
					return GPU->rb(addr);
				}
				return 0;
			}
		}
	}

	return 0;
}

WORD UMMU::rw(WORD addr)
{
	return (rb(addr) + (rb(addr + 1) << 8));
}

void UMMU::wb(WORD addr, BYTE val)
{
	switch (addr & 0xF000)
	{
		// ROM bank 0
	case 0x0000:
		if (bInBios && addr < 0x0100) return;
		// fall through

	case 0x1000:
	case 0x2000:
	case 0x3000:
		break;

		// ROM bank 1
	case 0x4000: case 0x5000: case 0x6000: case 0x7000:
		break;

		// VRAM
	case 0x8000: case 0x9000:
		// Only the VRAM case is shown:
		GPU->_vram[addr & 0x1FFF] = val;
		GPU->UpdateTile(addr, val);
		break;

		// External RAM
	case 0xA000: case 0xB000:
		_eram[addr & 0x1FFF] = val;
		break;

		// Work RAM and echo
	case 0xC000: case 0xD000: case 0xE000:
		_wram[addr & 0x1FFF] = val;
		break;

		// Everything else
	case 0xF000:
		switch (addr & 0x0F00)
		{
			// Echo RAM
		case 0x000: case 0x100: case 0x200: case 0x300:
		case 0x400: case 0x500: case 0x600: case 0x700:
		case 0x800: case 0x900: case 0xA00: case 0xB00:
		case 0xC00: case 0xD00:
			_wram[addr & 0x1FFF] = val;
			break;

			// OAM
		case 0xE00:
			//if ((addr & 0xFF) < 0xA0) GPU._oam[addr & 0xFF] = val;
			//GPU.updateoam(addr, val);
			break;

			// Zero-page
		case 0xF00:
			if (addr >= 0xFF80)
			{
				_zram[addr & 0x7F] = val;
			}
			else
			{
				// I/O
				switch (addr & 0x00F0)
				{
					// GPU
				case 0x40: case 0x50: case 0x60: case 0x70:
					GPU->wb(addr, val);
					break;
				}
			}
			break;
		}
		break;
	}
}

void UMMU::ww(WORD addr, WORD val)
{
	wb(addr, val & 255); 
	wb(addr + 1, val >> 8);
}