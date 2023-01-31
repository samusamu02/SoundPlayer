#pragma once
#include <memory>
#include "../PCM/PitchUp.h"
#include "SoundFile.h"

#define lpSoundSet SoundSet::GetInstance()

class SoundSet 
{
public:
    static SoundSet& GetInstance()
    {
        static SoundSet s_Instance;
        return s_Instance;
    }

    void SoundInit(const wchar_t* fileName, bool genelateFlag);

    int GetSouftSoundHandle(void);
    int GetSoundHandle(void);
    long long GetTotalSampleCount(void);
    long long GetDrawStartSampleCount(void);
private:
    SoundSet();
    ~SoundSet();

    // �\�t�g�T�E���h�n���h��
    int softSoundHandle_;
    // �T�E���h�n���h��
    int soundHandle_;

    // ���݂̃T���v���̈ʒu�̎擾
    long long totalSampleCount_;
    long long drawStartSampleCount_;

    std::unique_ptr<PitchUp> pitchUp_;
    SoundFile soundFile_;
};

