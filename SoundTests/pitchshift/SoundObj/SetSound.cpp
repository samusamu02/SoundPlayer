#include <DxLib.h>
#include "SetSound.h"

SetSound::SetSound()
{
	// �s�b�`��0.5�グ��
	pitchUp_ = std::make_unique<PitchUp>(0.5);
}

SetSound::~SetSound()
{

}

void SetSound::SetSoundInit(const wchar_t* fileName, bool genelateFlag)
{
	// �s�b�`�A�b�v(flag��true�̏ꍇ�̂ݐV����wav�t�@�C���𐶐�����
	if (genelateFlag == true)
	{
		pitchUp_->GenelatePitchUpWaveFile(fileName, file_2_);
	}

	// �T�E���h�t�@�C���̓ǂݍ���
	softSoundHandle_ = LoadSoftSound(fileName);

	// �\�t�g�T�E���h�n���h������T�E���h�n���h�����쐬
	soundHandle_ = LoadSoundMemFromSoftSound(softSoundHandle_);

	// �T�E���h�t�@�C���̎��g���𓾂�
	frequency_ = GetFrequencySoundMem(soundHandle_);
}


