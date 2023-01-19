#include "PCMSet.h"

#include<stdio.h>
#include<stdlib.h>

PCMSet::PCMSet()
{
	// 特になし
}

PCMSet::~PCMSet()
{
	// 特になし
}

void PCMSet::PCMSetPitchUp(MONO_PCM& after, MONO_PCM& before,double rate)
{

	after.fs = before.fs;										// 標本化周波数
	after.bits = before.bits;									// 量子化精度
	after.length = (int)(after.length / rate) + 1;				// 音のデータの長さ
	after.s = (double*)calloc(after.length, sizeof(double));	// 音のデータ

}

void PCMSet::PCMSetPitchUp(STEREO_PCM& after, STEREO_PCM& before,double rate)
{
	
	after.fs = before.fs;										// 標本化周波数
	after.bits = before.bits;									// 量子化精度
	after.length = (int)(before.length / rate) + 1;				// 音のデータの長さ
	after.sL = (double*)calloc(after.length, sizeof(double));	// 音のデータ(L)
	after.sR = (double*)calloc(after.length, sizeof(double));	// 音のデータ(R)

}

void PCMSet::PCMSetNormal(MONO_PCM& after, MONO_PCM& before)
{
	after.fs = before.fs;											// 標本化周波数
	after.bits = before.bits;										// 量子化精度
	after.length = before.length;									// 音データの長さ
	after.s = (double*)calloc(after.length, sizeof(double));		// 音データ
}

void PCMSet::PCMSetNormal(STEREO_PCM& after, STEREO_PCM& before)
{
	after.fs = before.fs;											// 標本化周波数
	after.bits = before.bits;										// 量子化精度
	after.length = before.length;									// 音データの長さ
	after.sL = (double*)calloc(after.length, sizeof(double));		// 音データ(L)
	after.sR = (double*)calloc(after.length, sizeof(double));		// 音データ(R)
}
