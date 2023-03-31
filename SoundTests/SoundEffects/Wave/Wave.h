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

    // 16bit��wav�̓ǂݍ���
    void WaveRead(MONO_PCM& pcm, const wchar_t* file_name);                 // ���m����
    void WaveRead(STEREO_PCM& pcm, const wchar_t* file_name);               // �X�e���I

    // 16bit��wav�̏�������
    bool WaveWrite(MONO_PCM& pcm, const wchar_t* file_name);                // ���m����
    bool WaveWrite(STEREO_PCM& pcm, const wchar_t* file_name);              // �X�e���I

    bool GetFlag();     // �t���O�̏�Ԃ��擾


    bool writeFinish; // �������݃t���O
private:

    Wave();
    ~Wave();
};


