#pragma once
#include "PCM.h"
class PCMSet :
    public PCM
{
public:
    PCMSet();
    ~PCMSet();

    /// <summary>
    /// �ϊ��O�̂�PCM��ϊ�����PCM�ɑ������֐�
    /// </summary>
    /// <param name="after">��������PCM</param>
    /// <param name="before">���f�[�^</param>
    void PCMSetWah(MONO_PCM& after, MONO_PCM& before);

    /// <summary>
    /// �ϊ��O�̂�PCM��ϊ�����PCM�ɑ������֐�
    /// </summary>
    /// <param name="after">��������PCM</param>
    /// <param name="before">���f�[�^</param>
    void PCMSetWah(STEREO_PCM& after, STEREO_PCM& before);

private:
};

