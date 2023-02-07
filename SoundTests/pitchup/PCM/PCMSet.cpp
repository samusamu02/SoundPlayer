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
	after.length = static_cast<int>(after.length / rate) + 1;				// 音のデータの長さ
	after.s.resize(after.length);								// 音のデータ

}

void PCMSet::PCMSetPitchUp(STEREO_PCM& after, STEREO_PCM& before,double rate)
{
	
	after.fs = before.fs;										// 標本化周波数
	after.bits = before.bits;									// 量子化精度
	after.length = static_cast<int>(before.length / rate) + 1;				// 音のデータの長さ
	after.sL.resize(after.length);								// 音のデータ(L)
	after.sR.resize(after.length);								// 音のデータ(R)

}

void PCMSet::PCMSetNormal(MONO_PCM& after, MONO_PCM& before)
{
	after.fs = before.fs;											// 標本化周波数
	after.bits = before.bits;										// 量子化精度
	after.length = before.length;									// 音データの長さ
	after.s.resize(after.length);									// 音のデータ
}

void PCMSet::PCMSetNormal(STEREO_PCM& after, STEREO_PCM& before)
{
	after.fs = before.fs;											// 標本化周波数
	after.bits = before.bits;										// 量子化精度
	after.length = before.length;									// 音データの長さ
	after.sL.resize(after.length);									// 音データ(L)
	after.sR.resize(after.length);									// 音データ(R)
}
