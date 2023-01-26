#include <DxLib.h>
#include "SetSound.h"

SetSound::SetSound()
{
	// ピッチを0.5上げる
	pitchUp_ = std::make_unique<PitchUp>(0.5);
}

SetSound::~SetSound()
{

}

void SetSound::SetSoundInit(const wchar_t* fileName, bool genelateFlag)
{
	// ピッチアップ(flagがtrueの場合のみ新しくwavファイルを生成する
	if (genelateFlag == true)
	{
		pitchUp_->GenelatePitchUpWaveFile(fileName, file_2_);
	}

	// サウンドファイルの読み込み
	softSoundHandle_ = LoadSoftSound(fileName);

	// ソフトサウンドハンドルからサウンドハンドルを作成
	soundHandle_ = LoadSoundMemFromSoftSound(softSoundHandle_);

	// サウンドファイルの周波数を得る
	frequency_ = GetFrequencySoundMem(soundHandle_);
}


