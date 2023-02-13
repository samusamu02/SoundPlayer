#pragma once
#include <memory>
#include "../PCM/PitchDown.h"
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

    // �T�E���h�̏�����
    void SoundInit(const wchar_t* fileName, bool genelateFlag);

    // �\�t�g�n���h���̎擾
    int GetSouftSoundHandle(void);

    // �T�E���h�n���h���̎擾
    int GetSoundHandle(void);

    // �T���v�������̎擾
    long long GetTotalSampleCount(void);

    // ���݂̃T���v�����̎擾
    long long GetDrawStartSampleCount(void);
private:
    SoundSet();
    ~SoundSet();

    // �\�t�g�T�E���h�n���h��
    int softSoundHandle_;
    // �T�E���h�n���h��
    int soundHandle_;

    // �T���v������
    long long totalSampleCount_;

    // ���݂̃T���v���̈ʒu�̎擾
    long long drawStartSampleCount_;

    // �s�b�`�A�b�v�̃I�u�W�F�N�g
    std::unique_ptr<PitchDown> pitchDown_;

    // �T�E���h�̃t�@�C��
    SoundFile soundFile_;
};

