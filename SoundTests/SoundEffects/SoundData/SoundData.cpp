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
	// サウンドファイルの読み込み
	softSoundHandle_ = LoadSoftSound(fileName);

	// ソフトサウンドハンドルからサウンドハンドルを作成
	soundHandle_ = LoadSoundMemFromSoftSound(softSoundHandle_);

	// サウンドファイルの長さを取得
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
