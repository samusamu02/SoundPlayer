#include "PCM.h"

PCM::PCM()
{
	// 構造体の初期化
	channelL_ = {};
	channelR_ = {};
	pcm0_ = {};
	pcm1_ = {};
	pcm2_ = {};

	// とりあえず0を入れる。
	rate_ = 0.0;
	rmax_ = 0.0;
	t_ = 0.0;
	pitch_ = 0.0;

	N_ = 0;
	template_size_ = 0;
}

PCM::~PCM()
{
	// 特になし
}
