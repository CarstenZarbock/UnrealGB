// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealGB.h"
#include "CPU.h"
#include "MMU.h"
#include "GPU.h"
#include "Engine.h"

UCPU::UCPU()
{

}

UCPU::~UCPU()
{
}

void UCPU::Reset()
{
	this->_register.a = 0;
	this->_register.b = 0;
	this->_register.c = 0;
	this->_register.d = 0;
	this->_register.e = 0;
	this->_register.h = 0;
	this->_register.l = 0;
	this->_register.f = 0;
	this->_register.pc = 0;
	this->_register.sp = 0; //set execution point back to 0
	
	this->_clock.m = 0;
	this->_clock.t = 0;
}

void UCPU::Dispatch()
{
	if (_stop == 0)
	{
		//represents each CPU tick / step
		BYTE op = MMU->rb(_register.pc++);	// Get the instruction
											//B* bptr1 = (pointerToA->*mfs[0])();
		(this->*OPmap[op])();
		_register.pc &= 65535;				// Mask PC to 16 bits
		_clock.m += _register.m;			// Add time to CPU clock
		_clock.t += _register.t;

		GPU->Step();
	}

	PrintDebug();
}

void UCPU::PrintDebug()
{
	int iIndex = 10;
	FString Message;

	Message.Append("CPU Register: ");
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;

	Message.Append("A: ");
	Message.Append(FString::FromInt(_register.a));
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;

	Message.Append("B: ");
	Message.Append(FString::FromInt(_register.b));
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;

	Message.Append("C: ");
	Message.Append(FString::FromInt(_register.c));
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;

	Message.Append("D: ");
	Message.Append(FString::FromInt(_register.d));
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;

	Message.Append("E: ");
	Message.Append(FString::FromInt(_register.e));
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;

	Message.Append("H: ");
	Message.Append(FString::FromInt(_register.h));
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;

	Message.Append("L: ");
	Message.Append(FString::FromInt(_register.l));
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;

	Message.Append("F: ");
	Message.Append(FString::FromInt(_register.f));
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;

	Message.Append("PC: ");
	Message.Append(FString::FromInt(_register.pc));
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;

	Message.Append("SP: ");
	Message.Append(FString::FromInt(_register.sp));
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;

	Message.Append("M: ");
	Message.Append(FString::FromInt(_register.m));
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;

	Message.Append("T: ");
	Message.Append(FString::FromInt(_register.t));
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;

	Message.Append("CPU _clock: ");
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;

	Message.Append("M: ");
	Message.Append(FString::FromInt(_clock.m));
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;

	Message.Append("T: ");
	Message.Append(FString::FromInt(_clock.t));
	GEngine->AddOnScreenDebugMessage(iIndex, 100.0f, FColor::Cyan, Message);
	Message.Empty();
	iIndex++;
}

/* OPs */
// Load / Store
int UCPU::LDrr_bb() { _register.b = _register.b; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_bc() { _register.b = _register.c; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_bd() { _register.b = _register.d; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_be() { _register.b = _register.e; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_bh() { _register.b = _register.h; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_bl() { _register.b = _register.l; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_ba() { _register.b = _register.a; _register.m = 1; _register.t = 4; return 0; }

int UCPU::LDrr_cb() { _register.c = _register.b; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_cc() { _register.c = _register.c; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_cd() { _register.c = _register.d; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_ce() { _register.c = _register.e; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_ch() { _register.c = _register.h; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_cl() { _register.c = _register.l; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_ca() { _register.c = _register.a; _register.m = 1; _register.t = 4; return 0; }

int UCPU::LDrr_db() { _register.d = _register.b; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_dc() { _register.d = _register.c; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_dd() { _register.d = _register.d; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_de() { _register.d = _register.e; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_dh() { _register.d = _register.h; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_dl() { _register.d = _register.l; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_da() { _register.d = _register.a; _register.m = 1; _register.t = 4; return 0; }

int UCPU::LDrr_eb() { _register.e = _register.b; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_ec() { _register.e = _register.c; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_ed() { _register.e = _register.d; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_ee() { _register.e = _register.e; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_eh() { _register.e = _register.h; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_el() { _register.e = _register.l; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_ea() { _register.e = _register.a; _register.m = 1; _register.t = 4; return 0; }

int UCPU::LDrr_hb() { _register.h = _register.b; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_hc() { _register.h = _register.c; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_hd() { _register.h = _register.d; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_he() { _register.h = _register.e; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_hh() { _register.h = _register.h; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_hl() { _register.h = _register.l; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_ha() { _register.h = _register.a; _register.m = 1; _register.t = 4; return 0; }

int UCPU::LDrr_lb() { _register.l = _register.b; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_lc() { _register.l = _register.c; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_ld() { _register.l = _register.d; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_le() { _register.l = _register.e; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_lh() { _register.l = _register.h; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_ll() { _register.l = _register.l; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_la() { _register.l = _register.a; _register.m = 1; _register.t = 4; return 0; }

int UCPU::LDrr_ab() { _register.a = _register.b; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_ac() { _register.a = _register.c; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_ad() { _register.a = _register.d; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_ae() { _register.a = _register.e; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_ah() { _register.a = _register.h; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_al() { _register.a = _register.l; _register.m = 1; _register.t = 4; return 0; }
int UCPU::LDrr_aa() { _register.a = _register.a; _register.m = 1; _register.t = 4; return 0; }

int UCPU::LDrHLm_b() { _register.b = MMU->rb((_register.h << 8) + _register.l); _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDrHLm_c() { _register.c = MMU->rb((_register.h << 8) + _register.l); _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDrHLm_d() { _register.d = MMU->rb((_register.h << 8) + _register.l); _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDrHLm_e() { _register.e = MMU->rb((_register.h << 8) + _register.l); _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDrHLm_h() { _register.h = MMU->rb((_register.h << 8) + _register.l); _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDrHLm_l() { _register.l = MMU->rb((_register.h << 8) + _register.l); _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDrHLm_a() { _register.a = MMU->rb((_register.h << 8) + _register.l); _register.m = 2; _register.t = 8; return 0; }

int UCPU::LDHLmr_b() { MMU->wb((_register.h << 8) + _register.l, _register.b); _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDHLmr_c() { MMU->wb((_register.h << 8) + _register.l, _register.c); _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDHLmr_d() { MMU->wb((_register.h << 8) + _register.l, _register.d); _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDHLmr_e() { MMU->wb((_register.h << 8) + _register.l, _register.e); _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDHLmr_h() { MMU->wb((_register.h << 8) + _register.l, _register.h); _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDHLmr_l() { MMU->wb((_register.h << 8) + _register.l, _register.l); _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDHLmr_a() { MMU->wb((_register.h << 8) + _register.l, _register.a); _register.m = 2; _register.t = 8; return 0; }

int UCPU::LDrn_b() { _register.b = MMU->rb(_register.pc); _register.pc++; _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDrn_c() { _register.c = MMU->rb(_register.pc); _register.pc++; _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDrn_d() { _register.d = MMU->rb(_register.pc); _register.pc++; _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDrn_e() { _register.e = MMU->rb(_register.pc); _register.pc++; _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDrn_h() { _register.h = MMU->rb(_register.pc); _register.pc++; _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDrn_l() { _register.l = MMU->rb(_register.pc); _register.pc++; _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDrn_a() { _register.a = MMU->rb(_register.pc); _register.pc++; _register.m = 2; _register.t = 8; return 0; }

int UCPU::LDHLmn() { MMU->wb((_register.h << 8) + _register.l, MMU->rb(_register.pc)); _register.pc++; _register.m = 3; _register.t = 12;  return 0; }

int UCPU::LDBCmA() { MMU->wb((_register.b << 8) + _register.c, _register.a); _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDDEmA() { MMU->wb((_register.d << 8) + _register.e, _register.a); _register.m = 2; _register.t = 8; return 0; }

int UCPU::LDmmA() { MMU->wb(MMU->rw(_register.pc), _register.a); _register.pc += 2; _register.m = 4; _register.t = 16; return 0; }

int UCPU::LDABCm() { _register.a = MMU->rb((_register.b << 8) + _register.c); _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDADEm() { _register.a = MMU->rb((_register.d << 8) + _register.e); _register.m = 2; _register.t = 8; return 0; }

int UCPU::LDAmm() { _register.a = MMU->rb(MMU->rw(_register.pc)); _register.pc += 2; _register.m = 4; _register.t = 16; return 0; }

int UCPU::LDBCnn() { _register.c = MMU->rb(_register.pc); _register.b = MMU->rb(_register.pc + 1); _register.pc += 2; _register.m = 3; _register.t = 12; return 0; }
int UCPU::LDDEnn() { _register.e = MMU->rb(_register.pc); _register.d = MMU->rb(_register.pc + 1); _register.pc += 2; _register.m = 3; _register.t = 12; return 0; }
int UCPU::LDHLnn() { _register.l = MMU->rb(_register.pc); _register.h = MMU->rb(_register.pc + 1); _register.pc += 2; _register.m = 3; _register.t = 12; return 0; }
int UCPU::LDSPnn() { _register.sp = MMU->rb(_register.pc); _register.pc += 2; _register.m = 3; _register.t = 12; return 0; }

int UCPU::LDHLmm() { WORD i = MMU->rw(_register.pc); _register.pc += 2; _register.l = MMU->rb(i); _register.h = MMU->rb(i + 1); _register.m = 5; _register.t = 20; return 0; }
int UCPU::LDmmHL() { WORD i = MMU->rw(_register.pc); _register.pc += 2; MMU->ww(i, (_register.h << 8) + _register.l); _register.m = 5; _register.t = 20; return 0; }

int UCPU::LDHLIA() {
	MMU->wb((_register.h << 8) + _register.l, _register.a); _register.l = (_register.l + 1) & 255; if (!_register.l) { _register.h = (_register.h + 1) & 255; } _register.m = 2; _register.t = 8; return 0;
}
int UCPU::LDAHLI() {
	_register.a = MMU->rb((_register.h << 8) + _register.l); _register.l = (_register.l + 1) & 255; if (!_register.l) { _register.h = (_register.h + 1) & 255; } _register.m = 2; _register.t = 8; return 0;
}

int UCPU::LDHLDA() {
	MMU->wb((_register.h << 8) + _register.l, _register.a); _register.l = (_register.l - 1) & 255; if (_register.l == 255) { _register.h = (_register.h - 1) & 255; } _register.m = 2; _register.t = 8; return 0;
}
int UCPU::LDAHLD() {
	_register.a = MMU->rb((_register.h << 8) + _register.l); _register.l = (_register.l - 1) & 255; if (_register.l == 255) { _register.h = (_register.h - 1) & 255; } _register.m = 2; _register.t = 8; return 0;
}

int UCPU::LDAIOn() { _register.a = MMU->rb(0xFF00 + MMU->rb(_register.pc)); _register.pc++, _register.m = 3; _register.t = 12; return 0; }
int UCPU::LDIOnA() { MMU->wb(0xFF00 + MMU->rb(_register.pc), _register.a); _register.pc++; _register.m = 3; _register.t = 12; return 0; }
int UCPU::LDAIOC() { _register.a = MMU->rb(0xFF00 + _register.c); _register.m = 2; _register.t = 8; return 0; }
int UCPU::LDIOCA() { MMU->wb(0xFF00 + _register.c, _register.a); _register.m = 2; _register.t = 8; return 0; }

int UCPU::LDHLSPn() { 
	WORD i = MMU->rb(_register.pc); if (i > 127) { i = -((~i + 1) & 255); } _register.pc++; i += _register.sp; _register.h = (i >> 8) & 255; _register.m = 3; _register.t = 12; return 0; //todo: fix!
}

int UCPU::SWAPr_b() { BYTE tr = _register.b; _register.b = MMU->rb((_register.h << 8) + _register.l); MMU->wb((_register.h << 8) + _register.l, tr); _register.m = 4; _register.t = 16; return 0; }
int UCPU::SWAPr_c() { BYTE tr = _register.c; _register.c = MMU->rb((_register.h << 8) + _register.l); MMU->wb((_register.h << 8) + _register.l, tr); _register.m = 4; _register.t = 16; return 0; }
int UCPU::SWAPr_d() { BYTE tr = _register.d; _register.d = MMU->rb((_register.h << 8) + _register.l); MMU->wb((_register.h << 8) + _register.l, tr); _register.m = 4; _register.t = 16; return 0; }
int UCPU::SWAPr_e() { BYTE tr = _register.e; _register.e = MMU->rb((_register.h << 8) + _register.l); MMU->wb((_register.h << 8) + _register.l, tr); _register.m = 4; _register.t = 16; return 0; }
int UCPU::SWAPr_h() { BYTE tr = _register.h; _register.h = MMU->rb((_register.h << 8) + _register.l); MMU->wb((_register.h << 8) + _register.l, tr); _register.m = 4; _register.t = 16; return 0; }
int UCPU::SWAPr_l() { BYTE tr = _register.l; _register.l = MMU->rb((_register.h << 8) + _register.l); MMU->wb((_register.h << 8) + _register.l, tr); _register.m = 4; _register.t = 16; return 0; }
int UCPU::SWAPr_a() { BYTE tr = _register.a; _register.a = MMU->rb((_register.h << 8) + _register.l); MMU->wb((_register.h << 8) + _register.l, tr); _register.m = 4; _register.t = 16; return 0; }

/* Data processing */
int UCPU::ADDr_b() {
	_register.a += _register.b; this->fz(_register.a); if (_register.a > 255) { _register.f |= 0x10; } _register.a &= 255; _register.m = 1; _register.t = 4;  return 0;
}
int UCPU::ADDr_c() { _register.a += _register.c; this->fz(_register.a); if (_register.a > 255) { _register.f |= 0x10; } _register.a &= 255; _register.m = 1; _register.t = 4;  return 0; }
int UCPU::ADDr_d() { _register.a += _register.d; this->fz(_register.a); if (_register.a > 255) { _register.f |= 0x10; } _register.a &= 255; _register.m = 1; _register.t = 4;  return 0; }
int UCPU::ADDr_e() { _register.a += _register.e; this->fz(_register.a); if (_register.a > 255) { _register.f |= 0x10; } _register.a &= 255; _register.m = 1; _register.t = 4;  return 0; }
int UCPU::ADDr_h() { _register.a += _register.h; this->fz(_register.a); if (_register.a > 255) { _register.f |= 0x10; } _register.a &= 255; _register.m = 1; _register.t = 4;  return 0; }
int UCPU::ADDr_l() { _register.a += _register.l; this->fz(_register.a); if (_register.a > 255) { _register.f |= 0x10; } _register.a &= 255; _register.m = 1; _register.t = 4;  return 0; }
int UCPU::ADDr_a() { _register.a += _register.a; this->fz(_register.a); if (_register.a > 255) { _register.f |= 0x10; } _register.a &= 255; _register.m = 1; _register.t = 4;  return 0; }
int UCPU::ADDHL() { _register.a += MMU->rb((_register.h << 8) + _register.l); this->fz(_register.a); if (_register.a > 255) _register.f |= 0x10; _register.a &= 255; _register.m = 2; _register.t = 8; return 0; }
int UCPU::ADDn() { _register.a += MMU->rb(_register.pc); _register.pc++; this->fz(_register.a); if (_register.a>255) _register.f |= 0x10; _register.a &= 255; _register.m = 2; _register.t = 8; return 0; }
int UCPU::ADDHLBC() { WORD hl = (_register.h << 8) + _register.l; hl += (_register.b << 8) + _register.c; if (hl>65535) _register.f |= 0x10; else _register.f &= 0xEF; _register.h = (hl >> 8) & 255; _register.l = hl & 255; _register.m = 3; _register.t = 12; return 0; }
int UCPU::ADDHLDE() { WORD hl = (_register.h << 8) + _register.l; hl += (_register.d << 8) + _register.e; if (hl>65535) _register.f |= 0x10; else _register.f &= 0xEF; _register.h = (hl >> 8) & 255; _register.l = hl & 255; _register.m = 3; _register.t = 12; return 0; }
int UCPU::ADDHLSP() { WORD hl = (_register.h << 8) + _register.l; hl += (_register.h << 8) + _register.l; if (hl>65535) _register.f |= 0x10; else _register.f &= 0xEF; _register.h = (hl >> 8) & 255; _register.l = hl & 255; _register.m = 3; _register.t = 12; return 0; }
int UCPU::ADDSPn() { BYTE i = MMU->rb(_register.pc); if (i>127) i = -((~i + 1) & 255); _register.pc++; _register.sp += i; _register.m = 4; _register.t = 16; return 0; }

int UCPU::ADCr_b() { _register.a += _register.b; _register.a += (_register.f & 0x10) ? 1 : 0; this->fz(_register.a); if (_register.a>255) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::ADCr_c() { _register.a += _register.c; _register.a += (_register.f & 0x10) ? 1 : 0; this->fz(_register.a); if (_register.a>255) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::ADCr_d() { _register.a += _register.d; _register.a += (_register.f & 0x10) ? 1 : 0; this->fz(_register.a); if (_register.a>255) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::ADCr_e() { _register.a += _register.e; _register.a += (_register.f & 0x10) ? 1 : 0; this->fz(_register.a); if (_register.a>255) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::ADCr_h() { _register.a += _register.h; _register.a += (_register.f & 0x10) ? 1 : 0; this->fz(_register.a); if (_register.a>255) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::ADCr_l() { _register.a += _register.l; _register.a += (_register.f & 0x10) ? 1 : 0; this->fz(_register.a); if (_register.a>255) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::ADCr_a() { _register.a += _register.a; _register.a += (_register.f & 0x10) ? 1 : 0; this->fz(_register.a); if (_register.a>255) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::ADCHL() { _register.a += MMU->rb((_register.h << 8) + _register.l); _register.a += (_register.f & 0x10) ? 1 : 0; this->fz(_register.a); if (_register.a>255) _register.f |= 0x10; _register.a &= 255; _register.m = 2; _register.t = 8; return 0; }
int UCPU::ADCn() { _register.a += MMU->rb(_register.pc); _register.pc++; _register.a += (_register.f & 0x10) ? 1 : 0; this->fz(_register.a); if (_register.a>255) _register.f |= 0x10; _register.a &= 255; _register.m = 2; _register.t = 8; return 0; }

int UCPU::SUBr_b() { _register.a -= _register.b; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::SUBr_c() { _register.a -= _register.c; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::SUBr_d() { _register.a -= _register.d; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::SUBr_e() { _register.a -= _register.e; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::SUBr_h() { _register.a -= _register.h; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::SUBr_l() { _register.a -= _register.l; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::SUBr_a() { _register.a -= _register.a; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::SUBHL() { _register.a -= MMU->rb((_register.h << 8) + _register.l); this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SUBn() { _register.a -= MMU->rb(_register.pc); _register.pc++; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 2; _register.t = 8; return 0; }

int UCPU::SBCr_b() { _register.a -= _register.b; _register.a -= (_register.f & 0x10) ? 1 : 0; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::SBCr_c() { _register.a -= _register.c; _register.a -= (_register.f & 0x10) ? 1 : 0; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::SBCr_d() { _register.a -= _register.d; _register.a -= (_register.f & 0x10) ? 1 : 0; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::SBCr_e() { _register.a -= _register.e; _register.a -= (_register.f & 0x10) ? 1 : 0; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::SBCr_h() { _register.a -= _register.h; _register.a -= (_register.f & 0x10) ? 1 : 0; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::SBCr_l() { _register.a -= _register.l; _register.a -= (_register.f & 0x10) ? 1 : 0; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::SBCr_a() { _register.a -= _register.a; _register.a -= (_register.f & 0x10) ? 1 : 0; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::SBCHL() { _register.a -= MMU->rb((_register.h << 8) + _register.l); _register.a -= (_register.f & 0x10) ? 1 : 0; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SBCn() { _register.a -= MMU->rb(_register.pc); _register.pc++; _register.a -= (_register.f & 0x10) ? 1 : 0; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 2; _register.t = 8; return 0; }

int UCPU::CPr_b() { BYTE i = _register.a; i -= _register.b; this->fz(i, 1); if (i<0) _register.f |= 0x10; i &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::CPr_c() { BYTE i = _register.a; i -= _register.c; this->fz(i, 1); if (i<0) _register.f |= 0x10; i &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::CPr_d() { BYTE i = _register.a; i -= _register.d; this->fz(i, 1); if (i<0) _register.f |= 0x10; i &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::CPr_e() { BYTE i = _register.a; i -= _register.e; this->fz(i, 1); if (i<0) _register.f |= 0x10; i &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::CPr_h() { BYTE i = _register.a; i -= _register.h; this->fz(i, 1); if (i<0) _register.f |= 0x10; i &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::CPr_l() { BYTE i = _register.a; i -= _register.l; this->fz(i, 1); if (i<0) _register.f |= 0x10; i &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::CPr_a() { BYTE i = _register.a; i -= _register.a; this->fz(i, 1); if (i<0) _register.f |= 0x10; i &= 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::CPHL() { BYTE i = _register.a; i -= MMU->rb((_register.h << 8) + _register.l); this->fz(i, 1); if (i<0) _register.f |= 0x10; i &= 255; _register.m = 2; _register.t = 8; return 0; }
int UCPU::CPn() { BYTE i = _register.a; i -= MMU->rb(_register.pc); _register.pc++; this->fz(i, 1); if (i<0) _register.f |= 0x10; i &= 255; _register.m = 2; _register.t = 8; return 0; }

int UCPU::ANDr_b() { _register.a &= _register.b; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::ANDr_c() { _register.a &= _register.c; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::ANDr_d() { _register.a &= _register.d; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::ANDr_e() { _register.a &= _register.e; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::ANDr_h() { _register.a &= _register.h; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::ANDr_l() { _register.a &= _register.l; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::ANDr_a() { _register.a &= _register.a; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::ANDHL() { _register.a &= MMU->rb((_register.h << 8) + _register.l); _register.a &= 255; this->fz(_register.a); _register.m = 2; _register.t = 8; return 0; }
int UCPU::ANDn() { _register.a &= MMU->rb(_register.pc); _register.pc++; _register.a &= 255; this->fz(_register.a); _register.m = 2; _register.t = 8; return 0; }

int UCPU::ORr_b() { _register.a |= _register.b; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::ORr_c() { _register.a |= _register.c; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::ORr_d() { _register.a |= _register.d; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::ORr_e() { _register.a |= _register.e; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::ORr_h() { _register.a |= _register.h; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::ORr_l() { _register.a |= _register.l; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::ORr_a() { _register.a |= _register.a; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::ORHL() { _register.a |= MMU->rb((_register.h << 8) + _register.l); _register.a &= 255; this->fz(_register.a); _register.m = 2; _register.t = 8; return 0; }
int UCPU::ORn() { _register.a |= MMU->rb(_register.pc); _register.pc++; _register.a &= 255; this->fz(_register.a); _register.m = 2; _register.t = 8; return 0; }

int UCPU::XORr_b() { _register.a ^= _register.b; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::XORr_c() { _register.a ^= _register.c; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::XORr_d() { _register.a ^= _register.d; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::XORr_e() { _register.a ^= _register.e; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::XORr_h() { _register.a ^= _register.h; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::XORr_l() { _register.a ^= _register.l; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::XORr_a() { _register.a ^= _register.a; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::XORHL() { _register.a ^= MMU->rb((_register.h << 8) + _register.l); _register.a &= 255; this->fz(_register.a); _register.m = 2; _register.t = 8; return 0; }
int UCPU::XORn() { _register.a ^= MMU->rb(_register.pc); _register.pc++; _register.a &= 255; this->fz(_register.a); _register.m = 2; _register.t = 8; return 0; }

int UCPU::INCr_b() { _register.b++; _register.b &= 255; this->fz(_register.b); _register.m = 1; _register.t = 4; return 0; }
int UCPU::INCr_c() { _register.c++; _register.c &= 255; this->fz(_register.c); _register.m = 1; _register.t = 4; return 0; }
int UCPU::INCr_d() { _register.d++; _register.d &= 255; this->fz(_register.d); _register.m = 1; _register.t = 4; return 0; }
int UCPU::INCr_e() { _register.e++; _register.e &= 255; this->fz(_register.e); _register.m = 1; _register.t = 4; return 0; }
int UCPU::INCr_h() { _register.h++; _register.h &= 255; this->fz(_register.h); _register.m = 1; _register.t = 4; return 0; }
int UCPU::INCr_l() { _register.l++; _register.l &= 255; this->fz(_register.l); _register.m = 1; _register.t = 4; return 0; }
int UCPU::INCr_a() { _register.a++; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::INCHLm() { BYTE i = MMU->rb((_register.h << 8) + _register.l) + 1; i &= 255; MMU->wb((_register.h << 8) + _register.l, i); this->fz(i); _register.m = 3; _register.t = 12; return 0; }

int UCPU::DECr_b() { _register.b--; _register.b &= 255; this->fz(_register.b); _register.m = 1; _register.t = 4; return 0; }
int UCPU::DECr_c() { _register.c--; _register.c &= 255; this->fz(_register.c); _register.m = 1; _register.t = 4; return 0; }
int UCPU::DECr_d() { _register.d--; _register.d &= 255; this->fz(_register.d); _register.m = 1; _register.t = 4; return 0; }
int UCPU::DECr_e() { _register.e--; _register.e &= 255; this->fz(_register.e); _register.m = 1; _register.t = 4; return 0; }
int UCPU::DECr_h() { _register.h--; _register.h &= 255; this->fz(_register.h); _register.m = 1; _register.t = 4; return 0; }
int UCPU::DECr_l() { _register.l--; _register.l &= 255; this->fz(_register.l); _register.m = 1; _register.t = 4; return 0; }
int UCPU::DECr_a() { _register.a--; _register.a &= 255; this->fz(_register.a); _register.m = 1; _register.t = 4; return 0; }
int UCPU::DECHLm() { BYTE i = MMU->rb((_register.h << 8) + _register.l) - 1; i &= 255; MMU->wb((_register.h << 8) + _register.l, i); this->fz(i); _register.m = 3; _register.t = 12; return 0; }

int UCPU::INCBC() { _register.c = (_register.c + 1) & 255; if (!_register.c) _register.b = (_register.b + 1) & 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::INCDE() { _register.e = (_register.e + 1) & 255; if (!_register.e) _register.d = (_register.d + 1) & 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::INCHL() { _register.l = (_register.l + 1) & 255; if (!_register.l) _register.h = (_register.h + 1) & 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::INCSP() { _register.sp = (_register.sp + 1) & 65535; _register.m = 1; _register.t = 4; return 0; }

int UCPU::DECBC() { _register.c = (_register.c - 1) & 255; if (_register.c == 255) _register.b = (_register.b - 1) & 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::DECDE() { _register.e = (_register.e - 1) & 255; if (_register.e == 255) _register.d = (_register.d - 1) & 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::DECHL() { _register.l = (_register.l - 1) & 255; if (_register.l == 255) _register.h = (_register.h - 1) & 255; _register.m = 1; _register.t = 4; return 0; }
int UCPU::DECSP() { _register.sp = (_register.sp - 1) & 65535; _register.m = 1; _register.t = 4; return 0; }

/* Bit manipulation */
int UCPU::BIT0b() { this->fz(_register.b & 0x01); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT0c() { this->fz(_register.c & 0x01); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT0d() { this->fz(_register.d & 0x01); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT0e() { this->fz(_register.e & 0x01); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT0h() { this->fz(_register.h & 0x01); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT0l() { this->fz(_register.l & 0x01); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT0a() { this->fz(_register.a & 0x01); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT0m() { this->fz(MMU->rb((_register.h << 8) + _register.l) & 0x01); _register.m = 3; _register.t = 12; return 0; }

int UCPU::BIT1b() { this->fz(_register.b & 0x02); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT1c() { this->fz(_register.c & 0x02); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT1d() { this->fz(_register.d & 0x02); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT1e() { this->fz(_register.e & 0x02); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT1h() { this->fz(_register.h & 0x02); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT1l() { this->fz(_register.l & 0x02); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT1a() { this->fz(_register.a & 0x02); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT1m() { this->fz(MMU->rb((_register.h << 8) + _register.l) & 0x02); _register.m = 3; _register.t = 12; return 0; }

int UCPU::BIT2b() { this->fz(_register.b & 0x04); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT2c() { this->fz(_register.c & 0x04); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT2d() { this->fz(_register.d & 0x04); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT2e() { this->fz(_register.e & 0x04); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT2h() { this->fz(_register.h & 0x04); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT2l() { this->fz(_register.l & 0x04); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT2a() { this->fz(_register.a & 0x04); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT2m() { this->fz(MMU->rb((_register.h << 8) + _register.l) & 0x04); _register.m = 3; _register.t = 12; return 0; }

int UCPU::BIT3b() { this->fz(_register.b & 0x08); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT3c() { this->fz(_register.c & 0x08); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT3d() { this->fz(_register.d & 0x08); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT3e() { this->fz(_register.e & 0x08); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT3h() { this->fz(_register.h & 0x08); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT3l() { this->fz(_register.l & 0x08); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT3a() { this->fz(_register.a & 0x08); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT3m() { this->fz(MMU->rb((_register.h << 8) + _register.l) & 0x08); _register.m = 3; _register.t = 12; return 0; }

int UCPU::BIT4b() { this->fz(_register.b & 0x10); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT4c() { this->fz(_register.c & 0x10); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT4d() { this->fz(_register.d & 0x10); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT4e() { this->fz(_register.e & 0x10); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT4h() { this->fz(_register.h & 0x10); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT4l() { this->fz(_register.l & 0x10); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT4a() { this->fz(_register.a & 0x10); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT4m() { this->fz(MMU->rb((_register.h << 8) + _register.l) & 0x10); _register.m = 3; _register.t = 12; return 0; }

int UCPU::BIT5b() { this->fz(_register.b & 0x20); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT5c() { this->fz(_register.c & 0x20); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT5d() { this->fz(_register.d & 0x20); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT5e() { this->fz(_register.e & 0x20); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT5h() { this->fz(_register.h & 0x20); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT5l() { this->fz(_register.l & 0x20); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT5a() { this->fz(_register.a & 0x20); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT5m() { this->fz(MMU->rb((_register.h << 8) + _register.l) & 0x20); _register.m = 3; _register.t = 12; return 0; }

int UCPU::BIT6b() { this->fz(_register.b & 0x40); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT6c() { this->fz(_register.c & 0x40); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT6d() { this->fz(_register.d & 0x40); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT6e() { this->fz(_register.e & 0x40); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT6h() { this->fz(_register.h & 0x40); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT6l() { this->fz(_register.l & 0x40); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT6a() { this->fz(_register.a & 0x40); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT6m() { this->fz(MMU->rb((_register.h << 8) + _register.l) & 0x40); _register.m = 3; _register.t = 12; return 0; }

int UCPU::BIT7b() { this->fz(_register.b & 0x80); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT7c() { this->fz(_register.c & 0x80); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT7d() { this->fz(_register.d & 0x80); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT7e() { this->fz(_register.e & 0x80); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT7h() { this->fz(_register.h & 0x80); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT7l() { this->fz(_register.l & 0x80); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT7a() { this->fz(_register.a & 0x80); _register.m = 2; _register.t = 8; return 0; }
int UCPU::BIT7m() { this->fz(MMU->rb((_register.h << 8) + _register.l) & 0x80); _register.m = 3; _register.t = 12; return 0; }

int UCPU::RLA() { BYTE ci = _register.f & 0x10 ? 1 : 0; BYTE co = _register.a & 0x80 ? 0x10 : 0; _register.a = (_register.a << 1) + ci; _register.a &= 255; _register.f = (_register.f & 0xEF) + co; _register.m = 1; _register.t = 4; return 0; }
int UCPU::RLCA() { BYTE ci = _register.a & 0x80 ? 1 : 0; BYTE co = _register.a & 0x80 ? 0x10 : 0; _register.a = (_register.a << 1) + ci; _register.a &= 255; _register.f = (_register.f & 0xEF) + co; _register.m = 1; _register.t = 4; return 0; }
int UCPU::RRA() { BYTE ci = _register.f & 0x10 ? 0x80 : 0; BYTE co = _register.a & 1 ? 0x10 : 0; _register.a = (_register.a >> 1) + ci; _register.a &= 255; _register.f = (_register.f & 0xEF) + co; _register.m = 1; _register.t = 4; return 0; }
int UCPU::RRCA() { BYTE ci = _register.a & 1 ? 0x80 : 0; BYTE co = _register.a & 1 ? 0x10 : 0; _register.a = (_register.a >> 1) + ci; _register.a &= 255; _register.f = (_register.f & 0xEF) + co; _register.m = 1; _register.t = 4; return 0; }
int UCPU::RLr_b() { BYTE ci = _register.f & 0x10 ? 1 : 0; BYTE co = _register.b & 0x80 ? 0x10 : 0; _register.b = (_register.b << 1) + ci; _register.b &= 255; this->fz(_register.b); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RLr_c() { BYTE ci = _register.f & 0x10 ? 1 : 0; BYTE co = _register.c & 0x80 ? 0x10 : 0; _register.c = (_register.c << 1) + ci; _register.c &= 255; this->fz(_register.c); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RLr_d() { BYTE ci = _register.f & 0x10 ? 1 : 0; BYTE co = _register.d & 0x80 ? 0x10 : 0; _register.d = (_register.d << 1) + ci; _register.d &= 255; this->fz(_register.d); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RLr_e() { BYTE ci = _register.f & 0x10 ? 1 : 0; BYTE co = _register.e & 0x80 ? 0x10 : 0; _register.e = (_register.e << 1) + ci; _register.e &= 255; this->fz(_register.e); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RLr_h() { BYTE ci = _register.f & 0x10 ? 1 : 0; BYTE co = _register.h & 0x80 ? 0x10 : 0; _register.h = (_register.h << 1) + ci; _register.h &= 255; this->fz(_register.h); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RLr_l() { BYTE ci = _register.f & 0x10 ? 1 : 0; BYTE co = _register.l & 0x80 ? 0x10 : 0; _register.l = (_register.l << 1) + ci; _register.l &= 255; this->fz(_register.l); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RLr_a() { BYTE ci = _register.f & 0x10 ? 1 : 0; BYTE co = _register.a & 0x80 ? 0x10 : 0; _register.a = (_register.a << 1) + ci; _register.a &= 255; this->fz(_register.a); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RLHL() { BYTE i = MMU->rb((_register.h << 8) + _register.l); BYTE ci = _register.f & 0x10 ? 1 : 0; BYTE co = i & 0x80 ? 0x10 : 0; i = (i << 1) + ci; i &= 255; this->fz(i); MMU->wb((_register.h << 8) + _register.l, i); _register.f = (_register.f & 0xEF) + co; _register.m = 4; _register.t = 16; return 0; }

int UCPU::RLCr_b() { BYTE ci = _register.b & 0x80 ? 1 : 0; BYTE co = _register.b & 0x80 ? 0x10 : 0; _register.b = (_register.b << 1) + ci; _register.b &= 255; this->fz(_register.b); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RLCr_c() { BYTE ci = _register.c & 0x80 ? 1 : 0; BYTE co = _register.c & 0x80 ? 0x10 : 0; _register.c = (_register.c << 1) + ci; _register.c &= 255; this->fz(_register.c); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RLCr_d() { BYTE ci = _register.d & 0x80 ? 1 : 0; BYTE co = _register.d & 0x80 ? 0x10 : 0; _register.d = (_register.d << 1) + ci; _register.d &= 255; this->fz(_register.d); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RLCr_e() { BYTE ci = _register.e & 0x80 ? 1 : 0; BYTE co = _register.e & 0x80 ? 0x10 : 0; _register.e = (_register.e << 1) + ci; _register.e &= 255; this->fz(_register.e); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RLCr_h() { BYTE ci = _register.h & 0x80 ? 1 : 0; BYTE co = _register.h & 0x80 ? 0x10 : 0; _register.h = (_register.h << 1) + ci; _register.h &= 255; this->fz(_register.h); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RLCr_l() { BYTE ci = _register.l & 0x80 ? 1 : 0; BYTE co = _register.l & 0x80 ? 0x10 : 0; _register.l = (_register.l << 1) + ci; _register.l &= 255; this->fz(_register.l); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RLCr_a() { BYTE ci = _register.a & 0x80 ? 1 : 0; BYTE co = _register.a & 0x80 ? 0x10 : 0; _register.a = (_register.a << 1) + ci; _register.a &= 255; this->fz(_register.a); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RLCHL() { BYTE i = MMU->rb((_register.h << 8) + _register.l); BYTE ci = i & 0x80 ? 1 : 0; BYTE co = i & 0x80 ? 0x10 : 0; i = (i << 1) + ci; i &= 255; this->fz(i); MMU->wb((_register.h << 8) + _register.l, i); _register.f = (_register.f & 0xEF) + co; _register.m = 4; _register.t = 16; return 0; }

int UCPU::RRr_b() { BYTE ci = _register.f & 0x10 ? 0x80 : 0; BYTE co = _register.b & 1 ? 0x10 : 0; _register.b = (_register.b >> 1) + ci; _register.b &= 255; this->fz(_register.b); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RRr_c() { BYTE ci = _register.f & 0x10 ? 0x80 : 0; BYTE co = _register.c & 1 ? 0x10 : 0; _register.c = (_register.c >> 1) + ci; _register.c &= 255; this->fz(_register.c); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RRr_d() { BYTE ci = _register.f & 0x10 ? 0x80 : 0; BYTE co = _register.d & 1 ? 0x10 : 0; _register.d = (_register.d >> 1) + ci; _register.d &= 255; this->fz(_register.d); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RRr_e() { BYTE ci = _register.f & 0x10 ? 0x80 : 0; BYTE co = _register.e & 1 ? 0x10 : 0; _register.e = (_register.e >> 1) + ci; _register.e &= 255; this->fz(_register.e); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RRr_h() { BYTE ci = _register.f & 0x10 ? 0x80 : 0; BYTE co = _register.h & 1 ? 0x10 : 0; _register.h = (_register.h >> 1) + ci; _register.h &= 255; this->fz(_register.h); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RRr_l() { BYTE ci = _register.f & 0x10 ? 0x80 : 0; BYTE co = _register.l & 1 ? 0x10 : 0; _register.l = (_register.l >> 1) + ci; _register.l &= 255; this->fz(_register.l); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RRr_a() { BYTE ci = _register.f & 0x10 ? 0x80 : 0; BYTE co = _register.a & 1 ? 0x10 : 0; _register.a = (_register.a >> 1) + ci; _register.a &= 255; this->fz(_register.a); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RRHL() { BYTE i = MMU->rb((_register.h << 8) + _register.l); BYTE ci = _register.f & 0x10 ? 0x80 : 0; BYTE co = i & 1 ? 0x10 : 0; i = (i >> 1) + ci; i &= 255; MMU->wb((_register.h << 8) + _register.l, i); this->fz(i); _register.f = (_register.f & 0xEF) + co; _register.m = 4; _register.t = 16; return 0; }

int UCPU::RRCr_b() { BYTE ci = _register.b & 1 ? 0x80 : 0; BYTE co = _register.b & 1 ? 0x10 : 0; _register.b = (_register.b >> 1) + ci; _register.b &= 255; this->fz(_register.b); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RRCr_c() { BYTE ci = _register.c & 1 ? 0x80 : 0; BYTE co = _register.c & 1 ? 0x10 : 0; _register.c = (_register.c >> 1) + ci; _register.c &= 255; this->fz(_register.c); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RRCr_d() { BYTE ci = _register.d & 1 ? 0x80 : 0; BYTE co = _register.d & 1 ? 0x10 : 0; _register.d = (_register.d >> 1) + ci; _register.d &= 255; this->fz(_register.d); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RRCr_e() { BYTE ci = _register.e & 1 ? 0x80 : 0; BYTE co = _register.e & 1 ? 0x10 : 0; _register.e = (_register.e >> 1) + ci; _register.e &= 255; this->fz(_register.e); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RRCr_h() { BYTE ci = _register.h & 1 ? 0x80 : 0; BYTE co = _register.h & 1 ? 0x10 : 0; _register.h = (_register.h >> 1) + ci; _register.h &= 255; this->fz(_register.h); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RRCr_l() { BYTE ci = _register.l & 1 ? 0x80 : 0; BYTE co = _register.l & 1 ? 0x10 : 0; _register.l = (_register.l >> 1) + ci; _register.l &= 255; this->fz(_register.l); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RRCr_a() { BYTE ci = _register.a & 1 ? 0x80 : 0; BYTE co = _register.a & 1 ? 0x10 : 0; _register.a = (_register.a >> 1) + ci; _register.a &= 255; this->fz(_register.a); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::RRCHL() { BYTE i = MMU->rb((_register.h << 8) + _register.l); BYTE ci = i & 1 ? 0x80 : 0; BYTE co = i & 1 ? 0x10 : 0; i = (i >> 1) + ci; i &= 255; MMU->wb((_register.h << 8) + _register.l, i); this->fz(i); _register.f = (_register.f & 0xEF) + co; _register.m = 4; _register.t = 16; return 0; }

int UCPU::SLAr_b() { BYTE co = _register.b & 0x80 ? 0x10 : 0; _register.b = (_register.b << 1) & 255; this->fz(_register.b); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SLAr_c() { BYTE co = _register.c & 0x80 ? 0x10 : 0; _register.c = (_register.c << 1) & 255; this->fz(_register.c); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SLAr_d() { BYTE co = _register.d & 0x80 ? 0x10 : 0; _register.d = (_register.d << 1) & 255; this->fz(_register.d); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SLAr_e() { BYTE co = _register.e & 0x80 ? 0x10 : 0; _register.e = (_register.e << 1) & 255; this->fz(_register.e); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SLAr_h() { BYTE co = _register.h & 0x80 ? 0x10 : 0; _register.h = (_register.h << 1) & 255; this->fz(_register.h); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SLAr_l() { BYTE co = _register.l & 0x80 ? 0x10 : 0; _register.l = (_register.l << 1) & 255; this->fz(_register.l); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SLAr_a() { BYTE co = _register.a & 0x80 ? 0x10 : 0; _register.a = (_register.a << 1) & 255; this->fz(_register.a); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }

int UCPU::SLLr_b() { BYTE co = _register.b & 0x80 ? 0x10 : 0; _register.b = (_register.b << 1) & 255 + 1; this->fz(_register.b); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SLLr_c() { BYTE co = _register.c & 0x80 ? 0x10 : 0; _register.c = (_register.c << 1) & 255 + 1; this->fz(_register.c); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SLLr_d() { BYTE co = _register.d & 0x80 ? 0x10 : 0; _register.d = (_register.d << 1) & 255 + 1; this->fz(_register.d); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SLLr_e() { BYTE co = _register.e & 0x80 ? 0x10 : 0; _register.e = (_register.e << 1) & 255 + 1; this->fz(_register.e); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SLLr_h() { BYTE co = _register.h & 0x80 ? 0x10 : 0; _register.h = (_register.h << 1) & 255 + 1; this->fz(_register.h); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SLLr_l() { BYTE co = _register.l & 0x80 ? 0x10 : 0; _register.l = (_register.l << 1) & 255 + 1; this->fz(_register.l); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SLLr_a() { BYTE co = _register.a & 0x80 ? 0x10 : 0; _register.a = (_register.a << 1) & 255 + 1; this->fz(_register.a); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }

int UCPU::SRAr_b() { BYTE ci = _register.b & 0x80; BYTE co = _register.b & 1 ? 0x10 : 0; _register.b = ((_register.b >> 1) + ci) & 255; this->fz(_register.b); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SRAr_c() { BYTE ci = _register.c & 0x80; BYTE co = _register.c & 1 ? 0x10 : 0; _register.c = ((_register.c >> 1) + ci) & 255; this->fz(_register.c); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SRAr_d() { BYTE ci = _register.d & 0x80; BYTE co = _register.d & 1 ? 0x10 : 0; _register.d = ((_register.d >> 1) + ci) & 255; this->fz(_register.d); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SRAr_e() { BYTE ci = _register.e & 0x80; BYTE co = _register.e & 1 ? 0x10 : 0; _register.e = ((_register.e >> 1) + ci) & 255; this->fz(_register.e); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SRAr_h() { BYTE ci = _register.h & 0x80; BYTE co = _register.h & 1 ? 0x10 : 0; _register.h = ((_register.h >> 1) + ci) & 255; this->fz(_register.h); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SRAr_l() { BYTE ci = _register.l & 0x80; BYTE co = _register.l & 1 ? 0x10 : 0; _register.l = ((_register.l >> 1) + ci) & 255; this->fz(_register.l); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SRAr_a() { BYTE ci = _register.a & 0x80; BYTE co = _register.a & 1 ? 0x10 : 0; _register.a = ((_register.a >> 1) + ci) & 255; this->fz(_register.a); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }

int UCPU::SRLr_b() { BYTE co = _register.b & 1 ? 0x10 : 0; _register.b = (_register.b >> 1) & 255; this->fz(_register.b); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SRLr_c() { BYTE co = _register.c & 1 ? 0x10 : 0; _register.c = (_register.c >> 1) & 255; this->fz(_register.c); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SRLr_d() { BYTE co = _register.d & 1 ? 0x10 : 0; _register.d = (_register.d >> 1) & 255; this->fz(_register.d); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SRLr_e() { BYTE co = _register.e & 1 ? 0x10 : 0; _register.e = (_register.e >> 1) & 255; this->fz(_register.e); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SRLr_h() { BYTE co = _register.h & 1 ? 0x10 : 0; _register.h = (_register.h >> 1) & 255; this->fz(_register.h); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SRLr_l() { BYTE co = _register.l & 1 ? 0x10 : 0; _register.l = (_register.l >> 1) & 255; this->fz(_register.l); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }
int UCPU::SRLr_a() { BYTE co = _register.a & 1 ? 0x10 : 0; _register.a = (_register.a >> 1) & 255; this->fz(_register.a); _register.f = (_register.f & 0xEF) + co; _register.m = 2; _register.t = 8; return 0; }

int UCPU::CPL() { _register.a = (~_register.a) & 255; this->fz(_register.a, 1); _register.m = 1; _register.t = 4; return 0; }
int UCPU::NEG() { _register.a = 0 - _register.a; this->fz(_register.a, 1); if (_register.a<0) _register.f |= 0x10; _register.a &= 255; _register.m = 2; _register.t = 8; return 0; }

int UCPU::CCF() { BYTE ci = _register.f & 0x10 ? 0 : 0x10; _register.f = (_register.f & 0xEF) + ci; _register.m = 1; _register.t = 4; return 0; }
int UCPU::SCF() { _register.f |= 0x10; _register.m = 1; _register.t = 4; return 0; }

/* Stack */
int UCPU::PUSHBC() { _register.sp--; MMU->wb(_register.sp, _register.b); _register.sp--; MMU->wb(_register.sp, _register.c); _register.m = 3; _register.t = 12; return 0; }
int UCPU::PUSHDE() { _register.sp--; MMU->wb(_register.sp, _register.d); _register.sp--; MMU->wb(_register.sp, _register.e); _register.m = 3; _register.t = 12; return 0; }
int UCPU::PUSHHL() { _register.sp--; MMU->wb(_register.sp, _register.h); _register.sp--; MMU->wb(_register.sp, _register.l); _register.m = 3; _register.t = 12; return 0; }
int UCPU::PUSHAF() { _register.sp--; MMU->wb(_register.sp, _register.a); _register.sp--; MMU->wb(_register.sp, _register.f); _register.m = 3; _register.t = 12; return 0; }

int UCPU::POPBC() { _register.c = MMU->rb(_register.sp); _register.sp++; _register.b = MMU->rb(_register.sp); _register.sp++; _register.m = 3; _register.t = 12; return 0; }
int UCPU::POPDE() { _register.e = MMU->rb(_register.sp); _register.sp++; _register.d = MMU->rb(_register.sp); _register.sp++; _register.m = 3; _register.t = 12; return 0; }
int UCPU::POPHL() { _register.l = MMU->rb(_register.sp); _register.sp++; _register.h = MMU->rb(_register.sp); _register.sp++; _register.m = 3; _register.t = 12; return 0; }
int UCPU::POPAF() { _register.f = MMU->rb(_register.sp); _register.sp++; _register.a = MMU->rb(_register.sp); _register.sp++; _register.m = 3; _register.t = 12; return 0; }

/* Jump */
int UCPU::JPnn() { _register.pc = MMU->rw(_register.pc); _register.m = 3; _register.t = 12; return 0; }
int UCPU::JPHL() { _register.pc = (_register.h << 8) + _register.l;; _register.m = 1; _register.t = 4; return 0; }
int UCPU::JPNZnn() { _register.m = 3; _register.t = 12; if ((_register.f & 0x80) == 0x00) { _register.pc = MMU->rw(_register.pc); _register.m++; _register.t += 4; } else _register.pc += 2; return 0; }
int UCPU::JPZnn() { _register.m = 3; _register.t = 12; if ((_register.f & 0x80) == 0x80) { _register.pc = MMU->rw(_register.pc); _register.m++; _register.t += 4; } else _register.pc += 2; return 0; }
int UCPU::JPNCnn() { _register.m = 3; _register.t = 12; if ((_register.f & 0x10) == 0x00) { _register.pc = MMU->rw(_register.pc); _register.m++; _register.t += 4; } else _register.pc += 2; return 0; }
int UCPU::JPCnn() { _register.m = 3; _register.t = 12; if ((_register.f & 0x10) == 0x10) { _register.pc = MMU->rw(_register.pc); _register.m++; _register.t += 4; } else _register.pc += 2; return 0; }

int UCPU::JRn() { BYTE i = MMU->rb(_register.pc); if (i>127) i = -((~i + 1) & 255); _register.pc++; _register.m = 2; _register.t = 8; _register.pc += i; _register.m++; _register.t += 4; return 0; }

int UCPU::JRNZn() { BYTE i = MMU->rb(_register.pc); if (i>127) i = -((~i + 1) & 255); _register.pc++; _register.m = 2; _register.t = 8; if ((_register.f & 0x80) == 0x00) { _register.pc += i; _register.m++; _register.t += 4; } return 0; }
int UCPU::JRZn() { BYTE i = MMU->rb(_register.pc); if (i>127) i = -((~i + 1) & 255); _register.pc++; _register.m = 2; _register.t = 8; if ((_register.f & 0x80) == 0x80) { _register.pc += i; _register.m++; _register.t += 4; } return 0; }
int UCPU::JRNCn() { BYTE i = MMU->rb(_register.pc); if (i>127) i = -((~i + 1) & 255); _register.pc++; _register.m = 2; _register.t = 8; if ((_register.f & 0x10) == 0x00) { _register.pc += i; _register.m++; _register.t += 4; } return 0; }
int UCPU::JRCn() { BYTE i = MMU->rb(_register.pc); if (i>127) i = -((~i + 1) & 255); _register.pc++; _register.m = 2; _register.t = 8; if ((_register.f & 0x10) == 0x10) { _register.pc += i; _register.m++; _register.t += 4; } return 0; }

int UCPU::DJNZn() { BYTE i = MMU->rb(_register.pc); if (i>127) i = -((~i + 1) & 255); _register.pc++; _register.m = 2; _register.t = 8; _register.b--; if (_register.b) { _register.pc += i; _register.m++; _register.t += 4; } return 0; }

int UCPU::CALLnn() { _register.sp -= 2; MMU->ww(_register.sp, _register.pc + 2); _register.pc = MMU->rw(_register.pc); _register.m = 5; _register.t = 20; return 0; }
int UCPU::CALLNZnn() { _register.m = 3; _register.t = 12; if ((_register.f & 0x80) == 0x00) { _register.sp -= 2; MMU->ww(_register.sp, _register.pc + 2); _register.pc = MMU->rw(_register.pc); _register.m += 2; _register.t += 8; } else _register.pc += 2; return 0; }
int UCPU::CALLZnn() { _register.m = 3; _register.t = 12; if ((_register.f & 0x80) == 0x80) { _register.sp -= 2; MMU->ww(_register.sp, _register.pc + 2); _register.pc = MMU->rw(_register.pc); _register.m += 2; _register.t += 8; } else _register.pc += 2; return 0; }
int UCPU::CALLNCnn() { _register.m = 3; _register.t = 12; if ((_register.f & 0x10) == 0x00) { _register.sp -= 2; MMU->ww(_register.sp, _register.pc + 2); _register.pc = MMU->rw(_register.pc); _register.m += 2; _register.t += 8; } else _register.pc += 2; return 0; }
int UCPU::CALLCnn() { _register.m = 3; _register.t = 12; if ((_register.f & 0x10) == 0x10) { _register.sp -= 2; MMU->ww(_register.sp, _register.pc + 2); _register.pc = MMU->rw(_register.pc); _register.m += 2; _register.t += 8; } else _register.pc += 2; return 0; }

int UCPU::RET() { _register.pc = MMU->rw(_register.sp); _register.sp += 2; _register.m = 3; _register.t = 12; return 0; }
int UCPU::RETI() { _register.ime = 1; _register.pc = MMU->rw(_register.sp); _register.sp += 2; _register.m = 3; _register.t = 12; return 0; }
int UCPU::RETNZ() { _register.m = 1; _register.t = 4; if ((_register.f & 0x80) == 0x00) { _register.pc = MMU->rw(_register.sp); _register.sp += 2; _register.m += 2; _register.t += 8; } return 0; }
int UCPU::RETZ() { _register.m = 1; _register.t = 4; if ((_register.f & 0x80) == 0x80) { _register.pc = MMU->rw(_register.sp); _register.sp += 2; _register.m += 2; _register.t += 8; } return 0; }
int UCPU::RETNC() { _register.m = 1; _register.t = 4; if ((_register.f & 0x10) == 0x00) { _register.pc = MMU->rw(_register.sp); _register.sp += 2; _register.m += 2; _register.t += 8; } return 0; }
int UCPU::RETC() { _register.m = 1; _register.t = 4; if ((_register.f & 0x10) == 0x10) { _register.pc = MMU->rw(_register.sp); _register.sp += 2; _register.m += 2; _register.t += 8; } return 0; }

int UCPU::RST00() { _register.sp -= 2; MMU->ww(_register.sp, _register.pc); _register.pc = 0x00; _register.m = 3; _register.t = 12; return 0; }
int UCPU::RST08() { _register.sp -= 2; MMU->ww(_register.sp, _register.pc); _register.pc = 0x08; _register.m = 3; _register.t = 12; return 0; }
int UCPU::RST10() { _register.sp -= 2; MMU->ww(_register.sp, _register.pc); _register.pc = 0x10; _register.m = 3; _register.t = 12; return 0; }
int UCPU::RST18() { _register.sp -= 2; MMU->ww(_register.sp, _register.pc); _register.pc = 0x18; _register.m = 3; _register.t = 12; return 0; }
int UCPU::RST20() { _register.sp -= 2; MMU->ww(_register.sp, _register.pc); _register.pc = 0x20; _register.m = 3; _register.t = 12; return 0; }
int UCPU::RST28() { _register.sp -= 2; MMU->ww(_register.sp, _register.pc); _register.pc = 0x28; _register.m = 3; _register.t = 12; return 0; }
int UCPU::RST30() { _register.sp -= 2; MMU->ww(_register.sp, _register.pc); _register.pc = 0x30; _register.m = 3; _register.t = 12; return 0; }
int UCPU::RST38() { _register.sp -= 2; MMU->ww(_register.sp, _register.pc); _register.pc = 0x38; _register.m = 3; _register.t = 12; return 0; }
int UCPU::RST40() { _register.sp -= 2; MMU->ww(_register.sp, _register.pc); _register.pc = 0x40; _register.m = 3; _register.t = 12; return 0; }
int UCPU::RST48() { _register.sp -= 2; MMU->ww(_register.sp, _register.pc); _register.pc = 0x48; _register.m = 3; _register.t = 12; return 0; }
int UCPU::RST50() { _register.sp -= 2; MMU->ww(_register.sp, _register.pc); _register.pc = 0x50; _register.m = 3; _register.t = 12; return 0; }
int UCPU::RST58() { _register.sp -= 2; MMU->ww(_register.sp, _register.pc); _register.pc = 0x58; _register.m = 3; _register.t = 12; return 0; }
int UCPU::RST60() { _register.sp -= 2; MMU->ww(_register.sp, _register.pc); _register.pc = 0x60; _register.m = 3; _register.t = 12; return 0; }

int UCPU::NOP() { _register.m = 1; _register.t = 4; return 0; }
int UCPU::HALT() { _halt = 1; _register.m = 1; _register.t = 4; return 0; }

int UCPU::DI() { _register.ime = 0; _register.m = 1; _register.t = 4; return 0; }
int UCPU::EI() { _register.ime = 1; _register.m = 1; _register.t = 4; return 0; }

int UCPU::fz(BYTE i, BYTE as) { _register.f = 0; if (!(i & 255)) _register.f |= 128; _register.f |= as ? 0x40 : 0; return 0; };
int UCPU::XX()
{       
	/*Undefined map entry*/
	WORD opc = _register.pc - 1;
	BYTE op = MMU->rb(opc);
	FString Message;
	Message.Append("[CPU] Unimplemented instruction at ");
	Message.Append(FString::FromInt(op));
	Message.Append(", CPU stop.");
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, Message);
	_stop = 0;
	
	return 0;
}
int UCPU::MAPcb() { GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "MAPcb"); return 0; }