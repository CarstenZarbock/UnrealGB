// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealGB.h"
#include "GPU.h"
#include "CPU.h"
#include "MMU.h"

UGPU::UGPU()
{
	_Scrn = UTexture2D::CreateTransient(160, 133);
	_Scrn->UpdateResource();

	_Canvas = UTexture2D::CreateTransient(160, 133);
	_Canvas->UpdateResource();

	_vram = new BYTE[SIZE_VRAM];
}

UGPU::~UGPU()
{
}

void UGPU::RenderBufferToCanvas()
{
	GEngine->AddOnScreenDebugMessage(5, 100.0f, FColor::Blue, "UGPU::RenderBufferToCanvas()");
	FTexture2DMipMap* BufferMipMap = &_Scrn->PlatformData->Mips[0];
	FByteBulkData* BufferRawImageData = &BufferMipMap->BulkData;
	FColor* BufferFormatedImageData = static_cast<FColor*>(BufferRawImageData->Lock(LOCK_READ_ONLY));

	FTexture2DMipMap* CanvasMipMap = &_Canvas->PlatformData->Mips[0];
	FByteBulkData* CanvasRawImageData = &CanvasMipMap->BulkData;
	FColor* CanvasFormatedImageData = static_cast<FColor*>(CanvasRawImageData->Lock(LOCK_READ_ONLY));

	uint32 TextureWidth = BufferMipMap->SizeX, TextureHeight = BufferMipMap->SizeY;


	CanvasFormatedImageData = BufferFormatedImageData;

	BufferRawImageData->Unlock();
	CanvasRawImageData->Unlock();
	_Scrn->UpdateResource();
	_Canvas->UpdateResource();
}

void UGPU::ResetRenderBuffer()
{
	GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Blue, "UGPU::ResetRenderBuffer()");
	FTexture2DMipMap* MyMipMap = &_Scrn->PlatformData->Mips[0];
	FByteBulkData* RawImageData = &MyMipMap->BulkData;
	FColor* FormatedImageData = static_cast<FColor*>(RawImageData->Lock(LOCK_READ_ONLY));

	uint32 TextureWidth = MyMipMap->SizeX, TextureHeight = MyMipMap->SizeY;
	FColor PixelColor;
	PixelColor = FColor::Emerald;

	for (uint32 i = 0; i < (TextureHeight * TextureWidth); i++)
	{
		FormatedImageData[i] = PixelColor;
	}

	RawImageData->Unlock();
	_Scrn->UpdateResource();
}

void UGPU::UpdateTile(WORD addr, BYTE val)
{
	// Get the "base address" for this tile row
	addr &= 0x1FFE;

	// Work out which tile and row was updated
	WORD tile = (addr >> 4) & 511;
	BYTE y = (addr >> 1) & 7;

	BYTE sx;
	for (BYTE x = 0; x < 8; x++)
	{
		// Find bit index for this pixel
		sx = 1 << (7 - x);

		// Update tile set
		_tileset[tile][y][x] = ((_vram[addr] & sx) ? 1 : 0) + ((_vram[addr + 1] & sx) ? 2 : 0);
	}
}

void UGPU::Reset()
{
	for (int i = 0; i < 384; i++)
	{
		for (int t = 0; t < 8; t++)
		{
			for (int e = 0; e < 8; e++)
			{
				_tileset[i][t][e] = 0x00;
			}
		}
	}

	ResetRenderBuffer();
	RenderBufferToCanvas();
}

void UGPU::Renderscan()
{
	// VRAM offset for the tile map
	WORD mapoffs = _bgmap ? 0x1C00 : 0x1800;

	// Which line of tiles to use in the map
	mapoffs += ((_line + _scy) & 255) >> 3;

	// Which tile to start with in the map line
	WORD lineoffs = (_scx >> 3);

	// Which line of pixels to use in the tiles
	WORD y = (_line + _scy) & 7;

	// Where in the tileline to start
	BYTE x = _scx & 7;

	// Where to render on the canvas
	WORD canvasoffs = _line * 160 * 4;

	// Read tile index from the background map
	_Palette colour;
	WORD tile = _vram[mapoffs + lineoffs];

	// If the tile data set in use is #1, the
	// indices are signed; calculate a real tile offset
	if (_bgtile == 1 && tile < 128) tile += 256;

	FTexture2DMipMap* BufferMipMap = &_Scrn->PlatformData->Mips[0];
	FByteBulkData* BufferRawImageData = &BufferMipMap->BulkData;
	FColor* BufferFormatedImageData = static_cast<FColor*>(BufferRawImageData->Lock(LOCK_READ_ONLY));
	uint32 TextureWidth = BufferMipMap->SizeX, TextureHeight = BufferMipMap->SizeY;

	for (BYTE i = 0; i < 160; i++)
	{
		// Re-map the tile pixel through the palette
		colour = _pal[_tileset[tile][y][x]];

		// Plot the pixel to canvas
		BufferFormatedImageData[canvasoffs + 0] = colour.color[0];
		BufferFormatedImageData[canvasoffs + 1] = colour.color[1];
		BufferFormatedImageData[canvasoffs + 2] = colour.color[2];
		BufferFormatedImageData[canvasoffs + 3] = colour.color[3];

		canvasoffs += 4;

		// When this tile ends, read another
		x++;
		if (x == 8)
		{
			x = 0;
			lineoffs = (lineoffs + 1) & 31;
			tile = _vram[mapoffs + lineoffs];
			if (_bgtile == 1 && tile < 128) tile += 256;
		}
	}

	BufferRawImageData->Unlock();
}

void UGPU::Step()
{
	_modeclock += CPU->_register.m;

	switch (_mode)
	{
		// Hblank
		// After the last hblank, push the screen data to canvas
	case 0:
		if (_modeclock >= 0)
		{
			RenderBufferToCanvas();
			if (_line == 143)
			{
				// Enter vblank
				_mode = 1;
				RenderBufferToCanvas();
			}
			else
			{
				_mode = 2;
			}

			_line++;
			_modeclock = 0;
		}
		break;

		// Vblank (10 lines)
	case 1:
		if (_modeclock >= 456)
		{
			_modeclock = 0;
			_line++;

			if (_line > 153)
			{
				// Restart scanning modes
				_mode = 2;
				_line = 0;
			}
		}
		break;

		// OAM read mode, scanline active
	case 2:
		if (_modeclock >= 80)
		{
			// Enter scanline mode 3
			_modeclock = 0;
			_mode = 3;
		}
		break;

		// VRAM read mode, scanline active
		// Treat end of mode 3 as end of scanline
	case 3:
		if (_modeclock >= 172)
		{
			// Enter hblank
			_modeclock = 0;
			_mode = 0;

			// Write a scanline to the framebuffer
			Renderscan();
			//RenderBufferToCanvas();
		}
		break;
	}
}

BYTE UGPU::rb(WORD addr)
{
	switch (addr)
	{
		// LCD Control
	case 0xFF40:
		return (_switchbg ? 0x01 : 0x00) | (_bgmap ? 0x08 : 0x00) | (_bgtile ? 0x10 : 0x00) | (_switchlcd ? 0x80 : 0x00);

		// Scroll Y
	case 0xFF42:
		return _scy;

		// Scroll X
	case 0xFF43:
		return _scx;

		// Current scanline
	case 0xFF44:
		return _line;
	}

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "[GPU] UGPU::rb() Error => CPU _stop");
	CPU->_stop = 1;
	return 0x00;
}

void UGPU::wb(WORD addr, BYTE val)
{
	switch (addr)
	{
		// LCD Control
	case 0xFF40:
		_switchbg = (val & 0x01) ? 1 : 0;
		_bgmap = (val & 0x08) ? 1 : 0;
		_bgtile = (val & 0x10) ? 1 : 0;
		_switchlcd = (val & 0x80) ? 1 : 0;
		break;

		// Scroll Y
	case 0xFF42:
		_scy = val;
		break;

		// Scroll X
	case 0xFF43:
		_scx = val;
		break;

		// Background palette
	case 0xFF47:
		for (BYTE i = 0; i < 4; i++)
		{
			switch ((val >> (i * 2)) & 3)
			{
			case 0: _pal[i].color[0] = FColor::Emerald; break;
			case 1: _pal[i].color[1] = FColor::Silver; break; // 192, 192, 192, 255
			case 2: _pal[i].color[2] = FColor::Green; break; //[96, 96, 96, 255]
			case 3: _pal[i].color[3] = FColor::Black; break; //[0, 0, 0, 255]
			}
		}
		break;
	}
}