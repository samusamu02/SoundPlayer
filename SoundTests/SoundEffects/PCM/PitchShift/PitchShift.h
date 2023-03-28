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

	// 左チャンネルの変数初期化
	virtual void ChannelL_Init(void) = 0;

	// 右チャンネルの変数初期化
	virtual void ChannelR_Init(void) = 0;

	// 左チャンネルのタイムストレッチ
	virtual void ChannelL_Timestretching(void) = 0;

	// 右チャンネルのタイムストレッチ
	virtual void ChannelR_Timestretching(void) = 0;

	// 左チャンネルのリサンプリング
	virtual void ChannelL_Resampling(void) = 0;

	// 右チャンネルのリサンプリング
	virtual void ChannelR_Resampling(void) = 0;

	// PCMの初期化のオブジェクト
	std::unique_ptr<PCMSet> pcmSet_;

	// ピッチシフト用
	std::unique_ptr<STEREO_PCM> pcm0_;
	std::unique_ptr<STEREO_PCM> pcm1_;
	std::unique_ptr<STEREO_PCM> pcm2_;

	// 左チャンネル
	std::unique_ptr<ChannelL> channelL_;
	// 右チャンネル
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

