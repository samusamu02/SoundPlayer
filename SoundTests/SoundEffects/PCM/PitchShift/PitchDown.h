#pragma once
#include "PitchShift.h"
class PitchDown :
    public PitchShift
{
public:
    PitchDown();
    ~PitchDown();

	// 新しくwavファイルを生成
	void GenelatePitchShiftWaveFile(const double rate, const wchar_t* fileName, const wchar_t* afterFileName) override;

private:
	// 初期化
	void Init(void) override;

	// 左チャンネルの変数初期化
	void ChannelL_Init(void) override;

	// 右チャンネルの変数初期化
	void ChannelR_Init(void) override;

	// 左チャンネルのタイムストレッチ
	void ChannelL_Timestretching(void) override;

	// 右チャンネルのタイムストレッチ
	void ChannelR_Timestretching(void) override;

	// 左チャンネルのリサンプリング
	void ChannelL_Resampling(void) override;

	// 右チャンネルのリサンプリング
	void ChannelR_Resampling(void) override;

};

