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
	// ピッチアップ(flagがtrueの場合のみ新しくwavファイルを生成する
	if (genelateFlag == true)
	{
		pitchUp_ = std::make_unique<PitchUp>(0.8);
		pitchUp_->GenelatePitchUpWaveFile(fileName, soundFile_.afterFilenName);
	}

	// サウンドファイルの読み込み
	softSoundHandle_ = LoadSoftSound(fileName);

	// ソフトサウンドハンドルからサウンドハンドルを作成
	soundHandle_ = LoadSoundMemFromSoftSound(softSoundHandle_);

	// サウンドファイルの長さを取得
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
