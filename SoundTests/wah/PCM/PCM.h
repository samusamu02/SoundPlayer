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

	// ワウ用pcmデータ
	std::unique_ptr<STEREO_PCM> pcm0_;
	std::unique_ptr<STEREO_PCM> pcm1_;

	// 左右分け
	std::unique_ptr<ChannelL> channelL_;
	std::unique_ptr<ChannelR> channelR_;

	// 遅延器の数
	long I;
	long J;

	// クオリティファクタ

private:
};

