#include "PitchShift.h"

PitchShift::PitchShift()
{
	// �\���̂̏�����
	channelL_ = {};
	channelR_ = {};
	pcm0_ = {};
	pcm1_ = {};
	pcm2_ = {};

	// �Ƃ肠����0������B
	rate = 0.0;
	rmax = 0.0;
	t = 0.0;
	pitch = 0.0;

	N = 0;
	template_size = 0;
}

PitchShift::~PitchShift()
{
	// ���ɂȂ�
}
