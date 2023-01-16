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

    // 16bit��wav�̓ǂݍ���
    void wave_read_16bit_mono(MONO_PCM& pcm, const wchar_t* file_name);        // ���m����
    void wave_read_16bit_stereo(STEREO_PCM& pcm, const wchar_t* file_name);    // �X�e���I

    // 16bit��wav�̏�������
    void wave_write_16bit_mono(MONO_PCM& pcm, const wchar_t* file_name);       // ���m����
    void wave_write_16bit_stereo(STEREO_PCM& pcm, const wchar_t* file_name);   // �X�e���I
private:

    Wave();
    ~Wave();
};


