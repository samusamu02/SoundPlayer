#pragma once
#include "../Wave/PCM.h"
#include "Channel.h"

class PitchShift
{
public:
	PitchShift();
	virtual ~PitchShift();
protected:

	// �s�b�`�V�t�g�p
	STEREO_PCM pcm0_;
	STEREO_PCM pcm1_;
	STEREO_PCM pcm2_;

	// ���E����
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

