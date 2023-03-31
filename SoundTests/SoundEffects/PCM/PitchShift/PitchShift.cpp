#include "PitchShift.h"

PitchShift::PitchShift()
{
	// PCM�̏������̃I�u�W�F�N�g
	pcmSet_ = std::make_unique<PCMSet>();

	// pcm�̃I�u�W�F�N�g
	pcm0_ = std::make_unique<STEREO_PCM>();
	pcm1_ = std::make_unique<STEREO_PCM>();
	pcm2_ = std::make_unique<STEREO_PCM>();

	// ���E�`�����l���̃I�u�W�F�N�g
	channelL_ = std::make_unique<ChannelL>();
	channelR_ = std::make_unique<ChannelR>();
}

PitchShift::~PitchShift()
{
}
