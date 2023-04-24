#pragma once
#include "Delay.h"
class Reverb :
    public Delay
{
public:
    Reverb();
    ~Reverb();

    // ����������
    virtual void Init(void);

    // ���o�[�u�p�̍��`�����l���̕ϐ��̏���������
    virtual void ChannelL_Init(void);

    // ���o�[�u�p�̉E�`�����l���̕ϐ��̏���������
    virtual void ChannelR_Init(void);

    /// <summary>
    /// �V�������o�[�u���K�p���ꂽwav�t�@�C���𐶐�����
    /// </summary>
    /// <param name="fileName">�K�p�O�̃t�@�C��</param>
    /// <param name="afterFileName">�K�p��̃t�@�C��</param>
    void GenelateReverbWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);
private:
};

