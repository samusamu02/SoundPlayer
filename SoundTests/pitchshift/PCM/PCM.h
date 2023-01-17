#pragma once
#include "../Wave/PCMDef.h"
#include "Channel.h"

#define M_PI 3.14159265359

class PCM
{
public:
	PCM();
	virtual ~PCM();
protected:

	// ピッチシフト用
	STEREO_PCM pcm0_;
	STEREO_PCM pcm1_;
	STEREO_PCM pcm2_;

	// 左右分け
	ChannelL channelL_;
	ChannelR channelR_;

	double rate_;
	double rmax_;
	double t_;
	double pitch_;

	int N_;
	int template_size_;

private:
};

