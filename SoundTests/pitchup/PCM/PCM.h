#pragma once
#include <memory>
#include "../Wave/PCMDef.h"
#include "Channel.h"

// �~����
#define M_PI 3.14159265359

class PCM
{
public:
	PCM();
	virtual ~PCM();
protected:

	// �s�b�`�V�t�g�p
	std::unique_ptr<STEREO_PCM> pcm0_;
	std::unique_ptr<STEREO_PCM> pcm1_;
	std::unique_ptr<STEREO_PCM> pcm2_;

	// ���E����
	std::unique_ptr<ChannelL> channelL_;
	std::unique_ptr<ChannelR> channelR_;

	double rate_;
	double rmax_;
	double t_;
	double pitch_;

	// �n�j���O���̃T�C�Y
	int N_;

	// ���֊֐��̃T�C�Y
	int template_size_;

private:
};

