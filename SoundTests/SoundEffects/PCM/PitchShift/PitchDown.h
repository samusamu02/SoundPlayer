#pragma once
#include "PitchShift.h"
class PitchDown :
    public PitchShift
{
public:
    PitchDown();
    ~PitchDown();

	/// <summary>
	/// 新しくピッチシフトが適用されたwavファイルを生成する
	/// </summary>
	/// <param name="rate">ピッチ変更の倍率</param>
	/// <param name="fileName">適用前のファイル</param>
	/// <param name="afterFileName">適用後のファイル</param>
	void GenelatePitchShiftWaveFile(const double rate, const wchar_t* fileName, const wchar_t* afterFileName) override;

private:
	// 初期化処理
	void Init(void) override;

	// 左チャンネルの変数初期化処理
	void ChannelL_Init(void) override;

	// 右チャンネルの変数初期化処理
	void ChannelR_Init(void) override;

	// 左チャンネルのタイムストレッチ処理
	void ChannelL_Timestretching(void) override;

	// 右チャンネルのタイムストレッチ処理
	void ChannelR_Timestretching(void) override;

	// 左チャンネルのリサンプリング処理
	void ChannelL_Resampling(void) override;

	// 右チャンネルのリサンプリング処理
	void ChannelR_Resampling(void) override;

};

