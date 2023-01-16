#pragma once
#include "../Wave/PCM.h"
#include "Channel.h"

class PitchShift
{
public:
	PitchShift();
	virtual ~PitchShift();
protected:

	// ピッチシフト用
	STEREO_PCM pcm0_;
	STEREO_PCM pcm1_;
	STEREO_PCM pcm2_;

	// 左右分け
	ChannelL channelL_;
	ChannelR channelR_;


	double rate;
	double rmax;
	double t;
	double pitch;

	int N;
	int template_size;

private:
};

