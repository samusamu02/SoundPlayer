#include <DxLib.h>
#include "SoundData.h"

SoundData::SoundData()
{

}

SoundData::~SoundData()
{
}

void SoundData::SoundDataInit(const wchar_t* fileName)
{
	// �T�E���h�t�@�C���̓ǂݍ���
	softSoundHandle_ = LoadSoftSound(fileName);

	// �\�t�g�T�E���h�n���h������T�E���h�n���h�����쐬
	soundHandle_ = LoadSoundMemFromSoftSound(softSoundHandle_);

	// �T�E���h�t�@�C���̒������擾
	totalSampleCount_ = GetSoftSoundSampleNum(softSoundHandle_);
}

int SoundData::GetSouftSoundHandle(void)
{
	return softSoundHandle_;
}

int SoundData::GetSoundHandle(void)
{
	return soundHandle_;
}

long long SoundData::GetTotalSampleCount(void)
{
	return totalSampleCount_;
}

long long SoundData::GetDrawStartSampleCount(void)
{
	return drawStartSampleCount_;
}
