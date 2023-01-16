#pragma once
#include "PCM.h"

#define lpWave Wave::Get()

class Wave
{
public:

    static Wave& Get()
    {
        static Wave s_Instance;
        return s_Instance;
    };

    // 16bitのwavの読み込み
    void wave_read_16bit_mono(MONO_PCM& pcm, const wchar_t* file_name);        // モノラル
    void wave_read_16bit_stereo(STEREO_PCM& pcm, const wchar_t* file_name);    // ステレオ

    // 16bitのwavの書き込み
    void wave_write_16bit_mono(MONO_PCM& pcm, const wchar_t* file_name);       // モノラル
    void wave_write_16bit_stereo(STEREO_PCM& pcm, const wchar_t* file_name);   // ステレオ
private:

    Wave();
    ~Wave();
};


