#pragma once
#include <vector>

struct MONO_PCM
{
	int fs;       // 標本化周波数 
	int bits;     // 量子化精度 
	int length;   // 音データの長さ 
	std::vector<double> s;    // 音データ 
};

struct STEREO_PCM
{
	int fs;       // 標本化周波数 
	int bits;     // 量子化精度 
	int length;   // 音データの長さ 
	std::vector<double> sL;   // 音データ（Lチャンネル） 
	std::vector<double> sR;   // 音データ（Rチャンネル） 
};