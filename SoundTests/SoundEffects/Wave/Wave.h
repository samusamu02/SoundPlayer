#pragma once
#include "PCMDef.h"

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
    void WaveRead(MONO_PCM& pcm, const wchar_t* file_name);                 // モノラル
    void WaveRead(STEREO_PCM& pcm, const wchar_t* file_name);               // ステレオ

    // 16bitのwavの書き込み
    bool WaveWrite(MONO_PCM& pcm, const wchar_t* file_name);                // モノラル
    bool WaveWrite(STEREO_PCM& pcm, const wchar_t* file_name);              // ステレオ

    bool GetFlag();     // フラグの状態を取得


    bool writeFinish; // 書き込みフラグ
private:

    Wave();
    ~Wave();
};


