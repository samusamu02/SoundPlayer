#pragma once
#include <memory>
#include "../Wave/PCMDef.h"
#include "Channel.h"

// 円周率
#define M_PI 3.14159265359

class PCM
{
public:
	PCM();
	virtual ~PCM();
protected:

	// ピッチシフト用
	std::unique_ptr<STEREO_PCM> pcm0_;
	std::unique_ptr<STEREO_PCM> pcm1_;
	std::unique_ptr<STEREO_PCM> pcm2_;

	// 左右分け
	std::unique_ptr<ChannelL> channelL_;
	std::unique_ptr<ChannelR> channelR_;

	double rate_;
	double rmax_;
	double t_;
	double pitch_;

	// ハニング窓のサイズ
	int N_;

	// 相関関数のサイズ
	int template_size_;

private:
};

