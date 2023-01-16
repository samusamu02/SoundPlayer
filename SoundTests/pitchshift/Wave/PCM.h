#pragma once

struct MONO_PCM
{
	int fs;       // 標本化周波数 
	int bits;     // 量子化精度 
	int length;   // 音データの長さ 
	double* s;    // 音データ 
};

struct STEREO_PCM
{
	int fs;       // 標本化周波数 
	int bits;     // 量子化精度 
	int length;   // 音データの長さ 
	double* sL;   // 音データ（Lチャンネル） 
	double* sR;   // 音データ（Rチャンネル） 
};