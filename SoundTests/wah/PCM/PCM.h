#pragma once
#include <memory>
#include "../Wave/PCMDef.h"
#include "Channel.h"

// ~ü¦
#define M_PI 3.14159265359

class PCM
{
public:
	PCM();
	virtual ~PCM();
protected:

	// Eppcmf[^
	std::unique_ptr<STEREO_PCM> pcm0_;
	std::unique_ptr<STEREO_PCM> pcm1_;

	// ¶Eª¯
	std::unique_ptr<ChannelL> channelL_;
	std::unique_ptr<ChannelR> channelR_;

	// xíÌ
	long I;
	long J;

	// NIeBt@N^

private:
};

