#include "PCM.h"

PCM::PCM()
{
	// \‘¢‘Ì‚Ì‰Šú‰»
	channelL_ = {};
	channelR_ = {};
	pcm0_ = {};
	pcm1_ = {};
	pcm2_ = {};

	// ‚Æ‚è‚ ‚¦‚¸0‚ğ“ü‚ê‚éB
	rate_ = 0.0;
	rmax_ = 0.0;
	t_ = 0.0;
	pitch_ = 0.0;

	N_ = 0;
	template_size_ = 0;
}

PCM::~PCM()
{
	// “Á‚É‚È‚µ
}
