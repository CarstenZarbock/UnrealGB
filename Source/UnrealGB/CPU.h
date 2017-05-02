// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CPU.generated.h"

/**
 * 
 */
#define FLAG_ZERO		0x80
#define FLAG_OPERATION	0x40
#define FLAG_HALFCARRY	0x20
#define FLAG_CARRY		0x10

#define INSTUCTIONSCOUNT	256

USTRUCT(BlueprintType)
struct FClock
{
	GENERATED_BODY()
	BYTE m;
	BYTE t;

	FClock()
	{
		m = 0;
		t = 0;
	}
};

USTRUCT(BlueprintType)
struct FRegister
{
	GENERATED_BODY()
	BYTE a;
	BYTE b;
	BYTE c;
	BYTE d;
	BYTE e;
	BYTE h;
	BYTE l;
	BYTE f;
	WORD pc; //clock for last instruction
	WORD sp; //clock for last instruction
	BYTE m; //probably 16bit?
	BYTE t; //probably 16bit?

	BYTE ime;

	FRegister()
	{
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		e = 0;
		h = 0;
		l = 0;
		f = 0;
		pc = 0;
		sp = 0;
		m = 0;
		t = 0;
	}
};

class UMMU;
class UGPU;

UCLASS(Blueprintable)
class UNREALGB_API UCPU : public UObject
{
	GENERATED_BODY()

public:
	FRegister _register;
	FClock _clock;
	BYTE _halt;
	BYTE _stop;

	UCPU();
	~UCPU();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMMU* MMU;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGPU* GPU;

	void Reset();
	UFUNCTION(BlueprintCallable, Category = "CPU")
	void Dispatch();
	void PrintDebug();

	/* OPs */
	// Load / Store
	int LDrr_bb();
	int LDrr_bc();
	int LDrr_bd();
	int LDrr_be();
	int LDrr_bh();
	int LDrr_bl();
	int LDrr_ba();

	int LDrr_cb();
	int LDrr_cc();
	int LDrr_cd();
	int LDrr_ce();
	int LDrr_ch();
	int LDrr_cl();
	int LDrr_ca();

	int LDrr_db();
	int LDrr_dc();
	int LDrr_dd();
	int LDrr_de();
	int LDrr_dh();
	int LDrr_dl();
	int LDrr_da();

	int LDrr_eb();
	int LDrr_ec();
	int LDrr_ed();
	int LDrr_ee();
	int LDrr_eh();
	int LDrr_el();
	int LDrr_ea();

	int LDrr_hb();
	int LDrr_hc();
	int LDrr_hd();
	int LDrr_he();
	int LDrr_hh();
	int LDrr_hl();
	int LDrr_ha();

	int LDrr_lb();
	int LDrr_lc();
	int LDrr_ld();
	int LDrr_le();
	int LDrr_lh();
	int LDrr_ll();
	int LDrr_la();

	int LDrr_ab();
	int LDrr_ac();
	int LDrr_ad();
	int LDrr_ae();
	int LDrr_ah();
	int LDrr_al();
	int LDrr_aa();

	int LDrHLm_b();
	int LDrHLm_c();
	int LDrHLm_d();
	int LDrHLm_e();
	int LDrHLm_h();
	int LDrHLm_l();
	int LDrHLm_a();

	int LDHLmr_b();
	int LDHLmr_c();
	int LDHLmr_d();
	int LDHLmr_e();
	int LDHLmr_h();
	int LDHLmr_l();
	int LDHLmr_a();

	int LDrn_b();
	int LDrn_c();
	int LDrn_d();
	int LDrn_e();
	int LDrn_h();
	int LDrn_l();
	int LDrn_a();

	int LDHLmn();
	
	int LDBCmA();
	int LDDEmA();
	
	int LDmmA();

	int LDABCm();
	int LDADEm();

	int LDAmm();

	int LDBCnn();
	int LDDEnn();
	int LDHLnn();
	int LDSPnn();

	int LDHLmm();
	int LDmmHL();

	int LDHLIA();
	int LDAHLI();

	int LDHLDA();
	int LDAHLD();

	int LDAIOn();
	int LDIOnA();
	int LDAIOC();
	int LDIOCA();

	int LDHLSPn();

	int SWAPr_b();
	int SWAPr_c();
	int SWAPr_d();
	int SWAPr_e();
	int SWAPr_h();
	int SWAPr_l();
	int SWAPr_a();

	/* Data processing */
	int ADDr_b();
	int ADDr_c();
	int ADDr_d();
	int ADDr_e();
	int ADDr_h();
	int ADDr_l();
	int ADDr_a();
	int ADDHL();
	int ADDn();
	int ADDHLBC();
	int ADDHLDE();
	int ADDHLSP();
	int ADDSPn();

	int ADCr_b();
	int ADCr_c();
	int ADCr_d();
	int ADCr_e();
	int ADCr_h();
	int ADCr_l();
	int ADCr_a();
	int ADCHL();
	int ADCn();

	int SUBr_b();
	int SUBr_c();
	int SUBr_d();
	int SUBr_e();
	int SUBr_h();
	int SUBr_l();
	int SUBr_a();
	int SUBHL();
	int SUBn();

	int SBCr_b();
	int SBCr_c();
	int SBCr_d();
	int SBCr_e();
	int SBCr_h();
	int SBCr_l();
	int SBCr_a();
	int SBCHL();
	int SBCn();

	int CPr_b();
	int CPr_c();
	int CPr_d();
	int CPr_e();
	int CPr_h();
	int CPr_l();
	int CPr_a();
	int CPHL();
	int CPn();

	int ANDr_b();
	int ANDr_c();
	int ANDr_d();
	int ANDr_e();
	int ANDr_h();
	int ANDr_l();
	int ANDr_a();
	int ANDHL();
	int ANDn();

	int ORr_b();
	int ORr_c();
	int ORr_d();
	int ORr_e();
	int ORr_h();
	int ORr_l();
	int ORr_a();
	int ORHL();
	int ORn();

	int XORr_b();
	int XORr_c();
	int XORr_d();
	int XORr_e();
	int XORr_h();
	int XORr_l();
	int XORr_a();
	int XORHL();
	int XORn();

	int INCr_b();
	int INCr_c();
	int INCr_d();
	int INCr_e();
	int INCr_h();
	int INCr_l();
	int INCr_a();
	int INCHLm();

	int DECr_b();
	int DECr_c();
	int DECr_d();
	int DECr_e();
	int DECr_h();
	int DECr_l();
	int DECr_a();
	int DECHLm();

	int INCBC();
	int INCDE();
	int INCHL();
	int INCSP();
	
	int DECBC();
	int DECDE();
	int DECHL();
	int DECSP();

	/* Bit manipulation */
	int BIT0b();
	int BIT0c();
	int BIT0d();
	int BIT0e();
	int BIT0h();
	int BIT0l();
	int BIT0a();
	int BIT0m();

	int BIT1b();
	int BIT1c();
	int BIT1d();
	int BIT1e();
	int BIT1h();
	int BIT1l();
	int BIT1a();
	int BIT1m();

	int BIT2b();
	int BIT2c();
	int BIT2d();
	int BIT2e();
	int BIT2h();
	int BIT2l();
	int BIT2a();
	int BIT2m();

	int BIT3b();
	int BIT3c();
	int BIT3d();
	int BIT3e();
	int BIT3h();
	int BIT3l();
	int BIT3a();
	int BIT3m();

	int BIT4b();
	int BIT4c();
	int BIT4d();
	int BIT4e();
	int BIT4h();
	int BIT4l();
	int BIT4a();
	int BIT4m();

	int BIT5b();
	int BIT5c();
	int BIT5d();
	int BIT5e();
	int BIT5h();
	int BIT5l();
	int BIT5a();
	int BIT5m();

	int BIT6b();
	int BIT6c();
	int BIT6d();
	int BIT6e();
	int BIT6h();
	int BIT6l();
	int BIT6a();
	int BIT6m();

	int BIT7b();
	int BIT7c();
	int BIT7d();
	int BIT7e();
	int BIT7h();
	int BIT7l();
	int BIT7a();
	int BIT7m();

	int RLA();
	int RLCA();
	int RRA();
	int RRCA();

	int RLr_b();
	int RLr_c();
	int RLr_d();
	int RLr_e();
	int RLr_h();
	int RLr_l();
	int RLr_a();
	int RLHL();

	int RLCr_b();
	int RLCr_c();
	int RLCr_d();
	int RLCr_e();
	int RLCr_h();
	int RLCr_l();
	int RLCr_a();
	int RLCHL();

	int RRr_b();
	int RRr_c();
	int RRr_d();
	int RRr_e();
	int RRr_h();
	int RRr_l();
	int RRr_a();
	int RRHL();

	int RRCr_b();
	int RRCr_c();
	int RRCr_d();
	int RRCr_e();
	int RRCr_h();
	int RRCr_l();
	int RRCr_a();
	int RRCHL();

	int SLAr_b();
	int SLAr_c();
	int SLAr_d();
	int SLAr_e();
	int SLAr_h();
	int SLAr_l();
	int SLAr_a();
	
	int SLLr_b();
	int SLLr_c();
	int SLLr_d();
	int SLLr_e();
	int SLLr_h();
	int SLLr_l();
	int SLLr_a();

	int SRAr_b();
	int SRAr_c();
	int SRAr_d();
	int SRAr_e();
	int SRAr_h();
	int SRAr_l();
	int SRAr_a();

	int SRLr_b();
	int SRLr_c();
	int SRLr_d();
	int SRLr_e();
	int SRLr_h();
	int SRLr_l();
	int SRLr_a();

	int CPL();
	int NEG();

	int CCF();
	int SCF();

	/* Stack */
	int PUSHBC();
	int PUSHDE();
	int PUSHHL();
	int PUSHAF();

	int POPBC();
	int POPDE();
	int POPHL();
	int POPAF();

	/* Jump */
	int JPnn();
	int JPHL();
	int JPNZnn();
	int JPZnn();
	int JPNCnn();
	int JPCnn();

	int JRn();

	int JRNZn();
	int JRZn();
	int JRNCn();
	int JRCn();

	int DJNZn();

	int CALLnn();
	int CALLNZnn();
	int CALLZnn();
	int CALLNCnn();
	int CALLCnn();

	int RET();
	int RETI();
	int RETNZ();
	int RETZ();
	int RETNC();
	int RETC();

	int RST00();
	int RST08();
	int RST10();
	int RST18();
	int RST20();
	int RST28();
	int RST30();
	int RST38();
	int RST40();
	int RST48();
	int RST50();
	int RST58();
	int RST60();

	int NOP();
	int HALT();

	int DI();
	int EI();
		
	/* Helper functions */
	int fz(BYTE i, BYTE as = 0);
	int MAPcb();

	int XX();

	typedef int(UCPU::*InstructionFunction)();

	InstructionFunction OPmap[INSTUCTIONSCOUNT] =
	{
		// 00
		&UCPU::NOP,
		&UCPU::LDBCnn,
		&UCPU::LDBCmA,
		&UCPU::INCBC,
		&UCPU::INCr_b,
		&UCPU::DECr_b,
		&UCPU::LDrn_b,
		&UCPU::RLCA,
		&UCPU::XX,
		&UCPU::ADDHLBC,
		&UCPU::LDABCm,
		&UCPU::DECBC,
		&UCPU::INCr_c,
		&UCPU::DECr_c,
		&UCPU::LDrn_c,
		&UCPU::RRCA,

		// 10
		&UCPU::DJNZn,	&UCPU::LDDEnn,	&UCPU::LDDEmA,	&UCPU::INCDE,
		&UCPU::INCr_d,	&UCPU::DECr_d,	&UCPU::LDrn_d,	&UCPU::RLA,
		&UCPU::JRn,		&UCPU::ADDHLDE,	&UCPU::LDADEm,	&UCPU::DECDE,
		&UCPU::INCr_e,	&UCPU::DECr_e,	&UCPU::LDrn_e,	&UCPU::RRA,
		// 20
		&UCPU::JRNZn,	&UCPU::LDHLnn,	&UCPU::LDHLIA,	&UCPU::INCHL,
		&UCPU::INCr_h,	&UCPU::DECr_h,	&UCPU::LDrn_h,	&UCPU::XX,
		&UCPU::JRZn,	&UCPU::XX,	&UCPU::LDAHLI,	&UCPU::DECHL,
		&UCPU::INCr_l,	&UCPU::DECr_l,	&UCPU::LDrn_l,	&UCPU::CPL,
		// 30
		&UCPU::JRNCn,	&UCPU::LDSPnn,	&UCPU::LDHLDA,	&UCPU::INCSP,
		&UCPU::INCHLm,	&UCPU::DECHLm,	&UCPU::LDHLmn,	&UCPU::SCF,
		&UCPU::JRCn,	&UCPU::ADDHLSP,	&UCPU::LDAHLD,	&UCPU::DECSP,
		&UCPU::INCr_a,	&UCPU::DECr_a,	&UCPU::LDrn_a,	&UCPU::CCF,
		// 40
		&UCPU::LDrr_bb,	&UCPU::LDrr_bc,	&UCPU::LDrr_bd,	&UCPU::LDrr_be,
		&UCPU::LDrr_bh,	&UCPU::LDrr_bl,	&UCPU::LDrHLm_b,	&UCPU::LDrr_ba,
		&UCPU::LDrr_cb,	&UCPU::LDrr_cc,	&UCPU::LDrr_cd,	&UCPU::LDrr_ce,
		&UCPU::LDrr_ch,	&UCPU::LDrr_cl,	&UCPU::LDrHLm_c,	&UCPU::LDrr_ca,
		// 50
		&UCPU::LDrr_db,	&UCPU::LDrr_dc,	&UCPU::LDrr_dd,	&UCPU::LDrr_de,
		&UCPU::LDrr_dh,	&UCPU::LDrr_dl,	&UCPU::LDrHLm_d,	&UCPU::LDrr_da,
		&UCPU::LDrr_eb,	&UCPU::LDrr_ec,	&UCPU::LDrr_ed,	&UCPU::LDrr_ee,
		&UCPU::LDrr_eh,	&UCPU::LDrr_el,	&UCPU::LDrHLm_e,	&UCPU::LDrr_ea,
		// 60
		&UCPU::LDrr_hb,	&UCPU::LDrr_hc,	&UCPU::LDrr_hd,	&UCPU::LDrr_he,
		&UCPU::LDrr_hh,	&UCPU::LDrr_hl,	&UCPU::LDrHLm_h,	&UCPU::LDrr_ha,
		&UCPU::LDrr_lb,	&UCPU::LDrr_lc,	&UCPU::LDrr_ld,	&UCPU::LDrr_le,
		&UCPU::LDrr_lh,	&UCPU::LDrr_ll,	&UCPU::LDrHLm_l,	&UCPU::LDrr_la,
		// 70
		&UCPU::LDHLmr_b,	&UCPU::LDHLmr_c,	&UCPU::LDHLmr_d,	&UCPU::LDHLmr_e,
		&UCPU::LDHLmr_h,	&UCPU::LDHLmr_l,	&UCPU::HALT,		&UCPU::LDHLmr_a,
		&UCPU::LDrr_ab,	&UCPU::LDrr_ac,	&UCPU::LDrr_ad,	&UCPU::LDrr_ae,
		&UCPU::LDrr_ah,	&UCPU::LDrr_al,	&UCPU::LDrHLm_a,	&UCPU::LDrr_aa,
		// 80
		&UCPU::ADDr_b,	&UCPU::ADDr_c,	&UCPU::ADDr_d,	&UCPU::ADDr_e,
		&UCPU::ADDr_h,	&UCPU::ADDr_l,	&UCPU::ADDHL,		&UCPU::ADDr_a,
		&UCPU::ADCr_b,	&UCPU::ADCr_c,	&UCPU::ADCr_d,	&UCPU::ADCr_e,
		&UCPU::ADCr_h,	&UCPU::ADCr_l,	&UCPU::ADCHL,		&UCPU::ADCr_a,
		// 90
		&UCPU::SUBr_b,	&UCPU::SUBr_c,	&UCPU::SUBr_d,	&UCPU::SUBr_e,
		&UCPU::SUBr_h,	&UCPU::SUBr_l,	&UCPU::SUBHL,		&UCPU::SUBr_a,
		&UCPU::SBCr_b,	&UCPU::SBCr_c,	&UCPU::SBCr_d,	&UCPU::SBCr_e,
		&UCPU::SBCr_h,	&UCPU::SBCr_l,	&UCPU::SBCHL,		&UCPU::SBCr_a,
		// A0
		&UCPU::ANDr_b,	&UCPU::ANDr_c,	&UCPU::ANDr_d,	&UCPU::ANDr_e,
		&UCPU::ANDr_h,	&UCPU::ANDr_l,	&UCPU::ANDHL,		&UCPU::ANDr_a,
		&UCPU::XORr_b,	&UCPU::XORr_c,	&UCPU::XORr_d,	&UCPU::XORr_e,
		&UCPU::XORr_h,	&UCPU::XORr_l,	&UCPU::XORHL,		&UCPU::XORr_a,
		// B0
		&UCPU::ORr_b,	&UCPU::ORr_c,		&UCPU::ORr_d,		&UCPU::ORr_e,
		&UCPU::ORr_h,	&UCPU::ORr_l,		&UCPU::ORHL,		&UCPU::ORr_a,
		&UCPU::CPr_b,	&UCPU::CPr_c,		&UCPU::CPr_d,		&UCPU::CPr_e,
		&UCPU::CPr_h,	&UCPU::CPr_l,		&UCPU::CPHL,		&UCPU::CPr_a,
		// C0
		&UCPU::RETNZ,	&UCPU::POPBC,		&UCPU::JPNZnn,	&UCPU::JPnn,
		&UCPU::CALLNZnn,	&UCPU::PUSHBC,	&UCPU::ADDn,		&UCPU::RST00,
		&UCPU::RETZ,	&UCPU::RET,		&UCPU::JPZnn,		&UCPU::MAPcb,
		&UCPU::CALLZnn,	&UCPU::CALLnn,	&UCPU::ADCn,		&UCPU::RST08,
		// D0
		&UCPU::RETNC,	&UCPU::POPDE,		&UCPU::JPNCnn,	&UCPU::XX,
		&UCPU::CALLNCnn,	&UCPU::PUSHDE,	&UCPU::SUBn,		&UCPU::RST10,
		&UCPU::RETC,	&UCPU::RETI,		&UCPU::JPCnn,		&UCPU::XX,
		&UCPU::CALLCnn,	&UCPU::XX,		&UCPU::SBCn,		&UCPU::RST18,
		// E0
		&UCPU::LDIOnA,	&UCPU::POPHL,		&UCPU::LDIOCA,	&UCPU::XX,
		&UCPU::XX,		&UCPU::PUSHHL,	&UCPU::ANDn,		&UCPU::RST20,
		&UCPU::ADDSPn,	&UCPU::JPHL,		&UCPU::LDmmA,		&UCPU::XX,
		&UCPU::XX,		&UCPU::XX,		&UCPU::XORn,		&UCPU::RST28,
		// F0
		&UCPU::LDAIOn,	&UCPU::POPAF,		&UCPU::LDAIOC,	&UCPU::DI,
		&UCPU::XX,		&UCPU::PUSHAF,	&UCPU::ORn,		&UCPU::RST30,
		&UCPU::LDHLSPn,	&UCPU::XX,		&UCPU::LDAmm,		&UCPU::EI,
		&UCPU::XX,		&UCPU::XX,		&UCPU::CPn,		&UCPU::RST38
	};
};