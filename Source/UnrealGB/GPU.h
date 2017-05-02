// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "GPU.generated.h"
#define SIZE_VRAM	8192
/**
*
*/
class UCPU;
class UMMU;

struct _Palette
{
	FColor color[4];
};

UCLASS(Blueprintable)
class UNREALGB_API UGPU : public UObject
{
	GENERATED_BODY()

public:
	BYTE _switchbg;
	BYTE _bgmap;
	BYTE _bgtile;
	BYTE _switchlcd;
	BYTE _scy;
	BYTE _scx;
	BYTE _tileset[384][8][8];
	_Palette _pal[4];

	BYTE* _vram;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Materials)
	UTexture2D* _Scrn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Materials)
	UTexture2D* _Canvas;

	UGPU();
	~UGPU();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCPU* CPU;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMMU* MMU;

	BYTE _mode;
	BYTE _modeclock;
	BYTE _line;

	UFUNCTION(BlueprintCallable, Category = "GPU")
	void Reset();
	UFUNCTION(BlueprintCallable, Category = "GPU")
	void Step();
	UFUNCTION(BlueprintCallable, Category = "GPU")
	void Renderscan();

	void ResetRenderBuffer();
	void RenderBufferToCanvas();

	BYTE rb(WORD addr);
	void wb(WORD addr, BYTE val);
	void UpdateTile(WORD addr, BYTE val);
};