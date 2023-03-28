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
    /// �s�b�`�V�t�g�p�̃G�t�F�N�g�K�p�O�̃T�E���h�t�@�C���̃f�[�^���R�s�[����֐�
    /// </summary>
    /// <param name="after">�R�s�[����ϐ�</param>
    /// <param name="before">���f�[�^</param>
    void PCMSetPitchShift(MONO_PCM& after, MONO_PCM& before,double rate);

    /// <summary>
    /// �s�b�`�V�t�g�p�̃G�t�F�N�g�K�p�O�̃T�E���h�t�@�C���̃f�[�^���R�s�[����֐�
    /// </summary>
    /// <param name="after">��������PCM</param>
    /// <param name="before">���f�[�^</param>
    void PCMSetPitchShift(STEREO_PCM& after, STEREO_PCM& before,double rate);

    /// <summary>
    /// �G�t�F�N�g�K�p�O�̃T�E���h�t�@�C���̃f�[�^���R�s�[����֐�
    /// </summary>
    /// <param name="after">��������PCM</param>
    /// <param name="before">���f�[�^</param>
    void PCMSetNormal(MONO_PCM& after, MONO_PCM& before);

    /// <summary>
    /// �G�t�F�N�g�K�p�O�̃T�E���h�t�@�C���̃f�[�^���R�s�[����֐�
    /// </summary>
    /// <param name="after">�R�s�[����ϐ�</param>
    /// <param name="before">���f�[�^</param>
    void PCMSetNormal(STEREO_PCM& after, STEREO_PCM& before);

private:
};

