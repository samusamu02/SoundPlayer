#pragma once
#include <memory>
#include "../PCM.h"
#include "PitchShift.h"
#include "../PCMSet.h"
#include "../Channel.h"
#include "../../Wave/PCMDef.h"

class PitchShift
	: public PCM
{
public:
	PitchShift();
	virtual ~PitchShift();

protected:
	// ������
	virtual void Init(void) = 0;

	// ���`�����l���̕ϐ�������
	virtual void ChannelL_Init(void) = 0;

	// �E�`�����l���̕ϐ�������
	virtual void ChannelR_Init(void) = 0;

	// ���`�����l���̃^�C���X�g���b�`
	virtual void ChannelL_Timestretching(void) = 0;

	// �E�`�����l���̃^�C���X�g���b�`
	virtual void ChannelR_Timestretching(void) = 0;

	// ���`�����l���̃��T���v�����O
	virtual void ChannelL_Resampling(void) = 0;

	// �E�`�����l���̃��T���v�����O
	virtual void ChannelR_Resampling(void) = 0;

	// PCM�̏������̃I�u�W�F�N�g
	std::unique_ptr<PCMSet> pcmSet_;

	// �s�b�`�V�t�g�p
	std::unique_ptr<STEREO_PCM> pcm0_;
	std::unique_ptr<STEREO_PCM> pcm1_;
	std::unique_ptr<STEREO_PCM> pcm2_;

	// ���`�����l��
	std::unique_ptr<ChannelL> channelL_;
	// �E�`�����l��
	std::unique_ptr<ChannelR> channelR_;

	// �Đ����x
	double rate_;

	// ���֊֐��̃s�[�N
	double rmax_;

	// �s�b�`�ύX����l�ƃT���v�������v�Z����
	double t_;

	// �s�b�`�ύX�̒l
	double pitch_;

	// �n�j���O���̃T�C�Y
	int N_;

	// ���֊֐��̃T�C�Y
	int template_size_;
private:
};

