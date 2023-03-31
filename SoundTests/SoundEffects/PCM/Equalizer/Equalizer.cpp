#include "Equalizer.h"
#include "../../Wave/Wave.h"
#include "../../common/iir_filter.h"

Equalizer::Equalizer()
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

Equalizer::~Equalizer()
{
}

void Equalizer::Init(void)
{
	// �x����̐�
	delaylineNum_ = 2;
}

void Equalizer::ChannelL_Init(void)
{
	// �Ւf���g��
	channelL_->fc = 10.0 / pcm0_->fs;

	// �N�I���e�B�t�@�N�^
	channelL_->Q = 1.0 / sqrt(2.0);

	channelL_->g = -1.0;

	// IIR�t�B���^�̐݌v
	IIR_low_shelving(channelL_->fc, channelL_->Q, channelL_->g, channelL_->a.data(), channelL_->b.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->A[0][m] = channelL_->a[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->B[0][m] = channelL_->b[m];
	}

	// ���S���g��
	channelL_->fc = 50.0 / pcm0_->fs;

	// �N�I���e�B�t�@�N�^
	channelL_->Q = 1.0 / sqrt(2.0);

	channelL_->g = 1.0;

	// IIR�t�B���^�̐݌v
	IIR_peaking(channelL_->fc, channelL_->Q, channelL_->g, channelL_->a.data(), channelL_->b.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->A[1][m] = channelL_->a[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->B[1][m] = channelL_->b[m];
	}

	// �Ւf���g��
	channelL_->fc = 100.0 / pcm0_->fs;

	// �N�I���e�B�t�@�N�^
	channelL_->Q = 1.0 / sqrt(2.0);

	channelL_->g = -1.0;

	// IIR�t�B���^�̐݌v
	IIR_high_shelving(channelL_->fc, channelL_->Q, channelL_->g, channelL_->a.data(), channelL_->b.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->A[2][m] = channelL_->a[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->B[2][m] = channelL_->b[m];
	}
}

void Equalizer::ChannelR_Init(void)
{
	// �Ւf���g��
	channelR_->fc = 10.0 / pcm0_->fs;

	// �N�I���e�B�t�@�N�^
	channelR_->Q = 1.0 / sqrt(2.0);

	channelR_->g = -1.0;

	// IIR�t�B���^�̐݌v
	IIR_low_shelving(channelR_->fc, channelR_->Q, channelR_->g, channelR_->a.data(), channelR_->b.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->A[0][m] = channelR_->a[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->B[0][m] = channelR_->b[m];
	}

	// ���S���g��
	channelR_->fc = 50.0 / pcm0_->fs;

	// �N�I���e�B�t�@�N�^
	channelR_->Q = 1.0 / sqrt(2.0);

	channelR_->g = 1.0;

	// IIR�t�B���^�̐݌v
	IIR_peaking(channelR_->fc, channelR_->Q, channelR_->g, channelR_->a.data(), channelR_->b.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->A[1][m] = channelR_->a[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->B[1][m] = channelR_->b[m];
	}

	// �Ւf���g��
	channelR_->fc = 100.0 / pcm0_->fs;

	// �N�I���e�B�t�@�N�^
	channelR_->Q = 1.0 / sqrt(2.0);

	channelR_->g = -1.0;

	// IIR�t�B���^�̐݌v
	IIR_high_shelving(channelR_->fc, channelR_->Q, channelR_->g, channelR_->a.data(), channelR_->b.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->A[2][m] = channelR_->a[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->B[2][m] = channelR_->b[m];
	}
}

void Equalizer::ChannelL_Equalizer(void)
{
	// �C�R���C�U�i3�ш�)
	for (int i = 0; i < 3; i++)
	{
		for (int n = 0; n < pcm1_->length; n++)
		{
			pcm1_->sL[n] = 0.0;
		}

		for (int n = 0; n < pcm1_->length; n++)
		{
			for (int m = 0; m <= delaylineNum_; m++)
			{
				if (n - m >= 0)
				{
					pcm1_->sL[n] += channelL_->B[i][m] * pcm0_->sL[n - m];
				}
			}
			for (int m = 1; m <= delaylineNum_; m++)
			{
				if (n - m >= 0)
				{
					pcm1_->sL[n] += -channelL_->A[i][m] * pcm1_->sL[n - m];
				}
			}
		}

		for (int n = 0; n < pcm1_->length; n++)
		{
			pcm0_->sL[n] = pcm1_->sL[n];
		}
	}
}

void Equalizer::ChannelR_Equalizer(void)
{
	// �C�R���C�U�i3�ш�)
	for (int i = 0; i < 3; i++)
	{
		for (int n = 0; n < pcm1_->length; n++)
		{
			pcm1_->sR[n] = 0.0;
		}

		for (int n = 0; n < pcm1_->length; n++)
		{
			for (int m = 0; m <= delaylineNum_; m++)
			{
				if (n - m >= 0)
				{
					pcm1_->sR[n] += channelR_->B[i][m] * pcm0_->sR[n - m];
				}
			}
			for (int m = 1; m <= delaylineNum_; m++)
			{
				if (n - m >= 0)
				{
					pcm1_->sR[n] += -channelR_->A[i][m] * pcm1_->sR[n - m];
				}
			}
		}

		for (int n = 0; n < pcm1_->length; n++)
		{
			pcm0_->sR[n] = pcm1_->sR[n];
		}
	}
}

void Equalizer::GenelateEquaLizerWaveFile(const wchar_t* fileName, const wchar_t* afterFileName)
{
	// wav�t�@�C���̓ǂݍ���
	lpWave.WaveRead(*pcm0_, fileName);

	// ����PCM�ƃG�t�F�N�g��K�p����PCM�̒l���Z�b�g����
	pcmSet_->PCMSetNormal(*pcm1_, *pcm0_);

	// ����������
	Init();

	// ���`�����l���̏�����
	ChannelL_Init();

	// �E�`�����l���̏�����
	ChannelR_Init();

	// ���`�����l���̃��E����
	ChannelL_Equalizer();

	// �E�`�����l���̃��E����
	ChannelR_Equalizer();

	// wav�t�@�C���̏o��
	lpWave.WaveWrite(*pcm1_, afterFileName);
}
