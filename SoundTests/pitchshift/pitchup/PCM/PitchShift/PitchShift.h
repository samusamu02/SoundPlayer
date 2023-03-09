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

	// �^�C���X�g���b�`
	virtual void Timestretching(void) = 0;

	// ���T���v�����O
	virtual void Resampling(void) = 0;

	/// <summary>
	/// �V�����s�b�`�ύX���ꂽwav�t�@�C���𐶐�����
	/// </summary>
	/// <param name="rate">�s�b�`�ύX�̔{��</param>
	/// <param name="fileName">�ύX�O</param>
	/// <param name="afterFileName">�ύX��</param>
	virtual bool GenelatePitchShiftFile(const double rate, const wchar_t* fileName, const wchar_t* afterFileName) = 0;

	// PCM�̏������̃I�u�W�F�N�g
	std::unique_ptr<PCMSet> pcmSet_;

	// �s�b�`�V�t�g�p
	std::unique_ptr<STEREO_PCM> pcm0_;
	std::unique_ptr<STEREO_PCM> pcm1_;
	std::unique_ptr<STEREO_PCM> pcm2_;

	// ���E����
	std::unique_ptr<ChannelL> channelL_;
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

