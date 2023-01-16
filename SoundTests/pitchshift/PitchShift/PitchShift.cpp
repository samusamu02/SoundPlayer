#include "PitchShift.h"

PitchShift::PitchShift()
{
	// 構造体の初期化
	channelL_ = {};
	channelR_ = {};
	pcm0_ = {};
	pcm1_ = {};
	pcm2_ = {};

	// とりあえず0を入れる。
	rate = 0.0;
	rmax = 0.0;
	t = 0.0;
	pitch = 0.0;

	N = 0;
	template_size = 0;
}

PitchShift::~PitchShift()
{
	// 特になし
}
