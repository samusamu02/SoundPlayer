#pragma once
#include "SoundObj.h"
#include <memory>
#include "../PCM/PitchUp.h"
class SetSound :
    public SoundObj
{
public:
    SetSound();
    ~SetSound();

    /// <summary>
    /// �T�E���h�n���h���ɃT�E���h�t�@�C�����Z�b�g����
    /// </summary>
    /// <param name="fileName">�T�E���h�t�@�C����</param>
    /// <param name="genelateFlag">�V����wav��ϊ����邩�ǂ����̃t���O</param>
    void SetSoundInit(const wchar_t* fileName, bool genelateFlag);
private:
    // �s�b�`�A�b�v�p�̃I�u�W�F�N�g
    std::unique_ptr<PitchUp> pitchUp_;
};

