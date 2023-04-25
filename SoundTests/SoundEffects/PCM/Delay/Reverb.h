#pragma once
#include "Delay.h"
class Reverb :
    public Delay
{
public:
    Reverb();
    ~Reverb();

    // ����������
    void Init(void) override;

    // ���o�[�u�p�̍��`�����l���̕ϐ��̏���������
    void ChannelL_Init(void) override;

    // ���o�[�u�p�̉E�`�����l���̕ϐ��̏���������
    void ChannelR_Init(void) override;

    /// <summary>
    /// �V�������o�[�u���K�p���ꂽwav�t�@�C���𐶐�����
    /// </summary>
    /// <param name="fileName">�K�p�O�̃t�@�C��</param>
    /// <param name="afterFileName">�K�p��̃t�@�C��</param>
    void GenelateReverbWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);
private:
};

