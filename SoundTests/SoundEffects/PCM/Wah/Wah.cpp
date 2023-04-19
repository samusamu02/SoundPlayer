#include "Wah.h"
#include "../../Wave/Wave.h"
#include "../../common/iir_filter.h"

Wah::Wah()
{
	// PCM�̏������̃I�u�W�F�N�g
	pcmSet_ = std::make_unique<PCMSet>();

	// pcm�̃I�u�W�F�N�g
	pcm0_ = std::make_unique<STEREO_PCM>();
	pcm1_ = std::make_unique<STEREO_PCM>();

	// ���E�`�����l���̃I�u�W�F�N�g
	channelL_ = std::make_unique<ChannelL>();
	channelR_ = std::make_unique<ChannelR>();
}

Wah::~Wah()
{
	// �����Ȃ�
}

void Wah::Init(void)
{
	// �ϐ�������
	delaylineNum_ = 2;

	depth_ = 800.0;
	rate_ = 1.0;
}

void Wah::ChannelL_Wah(void)
{
	// ���E
	for (int n = 0; n < pcm1_->length; n++)
	{
		// ���S���g��
		channelL_->fc = (1000.0 + depth_ * sin(2.0 * M_PI * rate_ * n / pcm1_->fs)) / pcm1_->fs;

		// �N�I���e�B�t�@�N�^
		channelL_->q_ = 2.0;

		// IIR�t�B���^�̐݌v
		IIR_resonator(channelL_->fc, channelL_->q_, channelL_->attenuation.data(), channelL_->delay.data());

		// �t�B���^����
		for (int m = 0; m <= delaylineNum_; m++)
		{
			if (n - m >= 0)
			{
				pcm1_->sL[n] += channelL_->delay[m] * pcm0_->sL[n - m];
			}
		}
		for (int m = 1; m <= delaylineNum_; m++)
		{
			if (n - m >= 0)
			{
				pcm1_->sL[n] += -channelL_->attenuation[m] * pcm1_->sL[n - m];
			}
		}

	}
}

void Wah::ChannelR_Wah(void)
{
	// ���`�����l���Ɠ����������s��(�ȉ����l�̏����ׂ̈̃R�����g�ȗ�)
	for (int n = 0; n < pcm1_->length; n++)
	{
		channelR_->fc = (1000.0 + depth_ * sin(2.0 * M_PI * rate_ * n / pcm1_->fs)) / pcm1_->fs;

		channelR_->q_ = 2.0;

		IIR_resonator(channelR_->fc, channelR_->q_, channelR_->attenuation.data(), channelR_->delay.data());

		for (int m = 0; m <= delaylineNum_; m++)
		{
			if (n - m >= 0)
			{
				pcm1_->sR[n] += channelR_->delay[m] * pcm0_->sR[n - m];
			}
		}
		for (int m = 1; m <= delaylineNum_; m++)
		{
			if (n - m >= 0)
			{
				pcm1_->sR[n] += -channelR_->attenuation[m] * pcm1_->sR[n - m];
			}
		}

	}
}

void Wah::GenelateWahWaveFile(const wchar_t* fileName, const wchar_t* afterFileName)
{
	// wav�t�@�C���̓ǂݍ���
	lpWave.WaveRead(*pcm0_, fileName);

	// ����PCM�ƃG�t�F�N�g��K�p����PCM�̒l���Z�b�g����
	pcmSet_->PCMSetNormal(*pcm1_, *pcm0_);

	// ����������
	Init();

	// ���`�����l���̃��E����
	ChannelL_Wah();

	// �E�`�����l���̃��E����
	ChannelR_Wah();

	// wav�t�@�C���̏o��
	lpWave.WaveWrite(*pcm1_, afterFileName);
}
