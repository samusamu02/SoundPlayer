#include "PitchShift.h"

PitchShift::PitchShift()
{
	// PCMの初期化のオブジェクト
	pcmSet_ = std::make_unique<PCMSet>();

	// pcmのオブジェクト
	pcm0_ = std::make_unique<STEREO_PCM>();
	pcm1_ = std::make_unique<STEREO_PCM>();
	pcm2_ = std::make_unique<STEREO_PCM>();

	// 左右チャンネルのオブジェクト
	channelL_ = std::make_unique<ChannelL>();
	channelR_ = std::make_unique<ChannelR>();
}

PitchShift::~PitchShift()
{
}
