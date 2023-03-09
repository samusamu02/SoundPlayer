#pragma once
#include "PCM.h"
#include "../Wave/PCMDef.h"
class PCMSet :
    public PCM
{
public:
    PCMSet();
    ~PCMSet();

    /// <summary>
    /// �s�b�`�V�t�g�p�̕ϊ��O�̂�PCM��ϊ�����PCM�ɑ���֐�
    /// </summary>
    /// <param name="after">��������PCM</param>
    /// <param name="before">���f�[�^</param>
    void PCMSetPitchUp(MONO_PCM& after, MONO_PCM& before,double rate);

    /// <summary>
    /// �s�b�`�V�t�g�p�̕ϊ��O�̂�PCM��ϊ�����PCM�ɑ������֐�
    /// </summary>
    /// <param name="after">��������PCM</param>
    /// <param name="before">���f�[�^</param>
    void PCMSetPitchUp(STEREO_PCM& after, STEREO_PCM& before,double rate);

    /// <summary>
    /// �ϊ��O�̂�PCM��ϊ�����PCM�ɑ������֐�
    /// </summary>
    /// <param name="after">��������PCM</param>
    /// <param name="before">���f�[�^</param>
    void PCMSetNormal(MONO_PCM& after, MONO_PCM& before);

    /// <summary>
    /// �ϊ��O�̂�PCM��ϊ�����PCM�ɑ������֐�
    /// </summary>
    /// <param name="after">��������PCM</param>
    /// <param name="before">���f�[�^</param>
    void PCMSetNormal(STEREO_PCM& after, STEREO_PCM& before);

private:
};

