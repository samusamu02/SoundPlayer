#include "PCM.h"

PCM::PCM()
{
	// �\���̂̏�����
	channelL_ = {};		// �E�`�����l��
	channelR_ = {};		// ���`�����l��
	// �T�E���h�f�[�^
	pcm0_ = {};			
	pcm1_ = {};
	pcm2_ = {};

	// ������
	rate_ = 0.0;
	rmax_ = 0.0;
	t_ = 0.0;
	pitch_ = 0.0;

	N_ = 0;
	template_size_ = 0;
}

PCM::~PCM()
{
	// ���ɂȂ�
}
