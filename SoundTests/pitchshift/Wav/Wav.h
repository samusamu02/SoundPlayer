#pragma once
#include <memory>
#include "PCM.h"

// 呼び出し用マクロ
#define lpWave Wav::Get()

class Wav
{
public:

	static Wav& Get()
	{
		static Wav s_Instane;
		return s_Instane;
	}

	void wave_read_16bit_mono(MONO_PCM& pcm, const wchar_t* file_name);
	void wave_read_16bit_stereo(STEREO_PCM& pcm, const wchar_t* file_name);
	void wave_write_16bit_mono(MONO_PCM& pcm, const wchar_t* file_name);
	void wave_write_16bit_stereo(STEREO_PCM& pcm, const wchar_t* file_name);
private:
	Wav();
	~Wav();
};

