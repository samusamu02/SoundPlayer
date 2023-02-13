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

	double rate_;		// �Đ����x
	double rmax_;		// ���֊֐��̃s�[�N
	double t_;			// �s�b�`�ύX����l�ƃT���v�������v�Z����
	double pitch_;		// �s�b�`�ύX�̒l

	// �n�j���O���̃T�C�Y
	int N_;

	// ���֊֐��̃T�C�Y
	int template_size_;

private:
};

