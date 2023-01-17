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

	// �s�b�`�V�t�g�p
	STEREO_PCM pcm0_;
	STEREO_PCM pcm1_;
	STEREO_PCM pcm2_;

	// ���E����
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

