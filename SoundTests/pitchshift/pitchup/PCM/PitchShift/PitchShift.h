#pragma once
#include <memory>
#include "../PCM.h"
#include "PitchShift.h"
#include "../PCMSet.h"
#include "../Channel.h"
#include "../../Wave/PCMDef.h"

class PitchShift
	: public PCM
{
public:
	PitchShift();
	virtual ~PitchShift();

protected:
	// 初期化
	virtual void Init(void) = 0;

	// タイムストレッチ
	virtual void Timestretching(void) = 0;

	// リサンプリング
	virtual void Resampling(void) = 0;

	/// <summary>
	/// 新しくピッチ変更されたwavファイルを生成する
	/// </summary>
	/// <param name="rate">ピッチ変更の倍率</param>
	/// <param name="fileName">変更前</param>
	/// <param name="afterFileName">変更後</param>
	virtual bool GenelatePitchShiftFile(const double rate, const wchar_t* fileName, const wchar_t* afterFileName) = 0;

	// PCMの初期化のオブジェクト
	std::unique_ptr<PCMSet> pcmSet_;

	// ピッチシフト用
	std::unique_ptr<STEREO_PCM> pcm0_;
	std::unique_ptr<STEREO_PCM> pcm1_;
	std::unique_ptr<STEREO_PCM> pcm2_;

	// 左右分け
	std::unique_ptr<ChannelL> channelL_;
	std::unique_ptr<ChannelR> channelR_;

	// 再生速度
	double rate_;

	// 相関関数のピーク
	double rmax_;

	// ピッチ変更する値とサンプル数を計算する
	double t_;

	// ピッチ変更の値
	double pitch_;

	// ハニング窓のサイズ
	int N_;

	// 相関関数のサイズ
	int template_size_;
private:
};

