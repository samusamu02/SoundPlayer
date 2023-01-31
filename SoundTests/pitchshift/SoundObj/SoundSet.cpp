#include <DxLib.h>
#include "SoundSet.h"
SoundSet::SoundSet()
{
}

SoundSet::~SoundSet()
{
}

void SoundSet::SoundInit(const wchar_t* fileName, bool genelateFlag)
{
	// �s�b�`�A�b�v(flag��true�̏ꍇ�̂ݐV����wav�t�@�C���𐶐�����
	if (genelateFlag == true)
	{
		pitchUp_ = std::make_unique<PitchUp>(0.8);
		pitchUp_->GenelatePitchUpWaveFile(fileName, soundFile_.afterFilenName);
	}

	// �T�E���h�t�@�C���̓ǂݍ���
	softSoundHandle_ = LoadSoftSound(fileName);

	// �\�t�g�T�E���h�n���h������T�E���h�n���h�����쐬
	soundHandle_ = LoadSoundMemFromSoftSound(softSoundHandle_);

	// �T�E���h�t�@�C���̒������擾
	totalSampleCount_ = GetSoftSoundSampleNum(softSoundHandle_);
}

int SoundSet::GetSouftSoundHandle(void)
{
	return softSoundHandle_;
}

int SoundSet::GetSoundHandle(void)
{
	return soundHandle_;
}

long long SoundSet::GetTotalSampleCount(void)
{
	return totalSampleCount_;
}

long long SoundSet::GetDrawStartSampleCount(void)
{
	return drawStartSampleCount_;
}
