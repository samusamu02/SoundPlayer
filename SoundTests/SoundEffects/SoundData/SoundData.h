#pragma once
#include <memory>
#include "../PCM/PitchShift/PitchUp.h"
#include "../SoundObj/SoundFile.h"

#define lpSoundSet SoundData::GetInstance()

class SoundData 
{
public:
    static SoundData& GetInstance()
    {
        static SoundData s_Instance;
        return s_Instance;
    }

    // �T�E���h�̏�����
    void SoundDataInit(const wchar_t* fileName);

    // �\�t�g�n���h���̎擾
    int GetSouftSoundHandle(void);

    // �T�E���h�n���h���̎擾
    int GetSoundHandle(void);

    // �T���v�������̎擾
    long long GetTotalSampleCount(void);

    // ���݂̃T���v�����̎擾
    long long GetDrawStartSampleCount(void);
private:
    SoundData();
    ~SoundData();

    // �T�E���h�̃t�@�C��
    SoundFile soundFile_;

    // �T���v������
    long long totalSampleCount_;

    // ���݂̃T���v���̈ʒu�̎擾
    long long drawStartSampleCount_;

    // �\�t�g�T�E���h�n���h��
    int softSoundHandle_;

    // �T�E���h�n���h��
    int soundHandle_;
};

