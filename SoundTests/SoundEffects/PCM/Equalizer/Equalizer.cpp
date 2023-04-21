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

void Equalizer::ChannelL_IIR(void)
{
	// �Ւf���g��
	channelL_->cf_ = 10.0 / pcm0_->fs;

	// �N�I���e�B�t�@�N�^
	channelL_->q_Factor_ = 1.0 / sqrt(2.0);
	channelL_->gain_ = -1.0;

	// IIR�t�B���^�̐݌v
	IIR_low_shelving(channelL_->cf_, channelL_->q_Factor_, channelL_->gain_, channelL_->coefficients_a_.data(), channelL_->coefficients_b_.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->coefficients_A_[0][m] = channelL_->coefficients_a_[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->coefficients_B_[0][m] = channelL_->coefficients_b_[m];
	}

	// ���S���g��
	channelL_->cf_ = 50.0 / pcm0_->fs;

	// �N�I���e�B�t�@�N�^
	channelL_->q_Factor_ = 1.0 / sqrt(2.0);
	channelL_->gain_ = 1.0;

	// IIR�t�B���^�̐݌v
	IIR_peaking(channelL_->cf_, channelL_->q_Factor_, channelL_->gain_, channelL_->coefficients_a_.data(), channelL_->coefficients_b_.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->coefficients_A_[1][m] = channelL_->coefficients_a_[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->coefficients_B_[1][m] = channelL_->coefficients_b_[m];
	}

	// �Ւf���g��
	channelL_->cf_ = 100.0 / pcm0_->fs;

	// �N�I���e�B�t�@�N�^
	channelL_->q_Factor_ = 1.0 / sqrt(2.0);
	channelL_->gain_ = -1.0;

	// IIR�t�B���^�̐݌v
	IIR_high_shelving(channelL_->cf_, channelL_->q_Factor_, channelL_->gain_, channelL_->coefficients_a_.data(), channelL_->coefficients_b_.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->coefficients_A_[2][m] = channelL_->coefficients_a_[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->coefficients_B_[2][m] = channelL_->coefficients_b_[m];
	}
}

void Equalizer::ChannelR_IIR(void)
{
	// �Ւf���g��
	channelR_->cf_ = 10.0 / pcm0_->fs;

	// �N�I���e�B�t�@�N�^
	channelR_->q_Factor_ = 1.0 / sqrt(2.0);
	channelR_->gain_ = -1.0;

	// IIR�t�B���^�̐݌v
	IIR_low_shelving(channelR_->cf_, channelR_->q_Factor_, channelR_->gain_, channelR_->coefficients_a_.data(), channelR_->coefficients_b_.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->coefficients_A_[0][m] = channelR_->coefficients_a_[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->coefficients_B_[0][m] = channelR_->coefficients_b_[m];
	}

	// ���S���g��
	channelR_->cf_ = 50.0 / pcm0_->fs;

	// �N�I���e�B�t�@�N�^
	channelR_->q_Factor_ = 1.0 / sqrt(2.0);
	channelR_->gain_ = 1.0;

	// IIR�t�B���^�̐݌v
	IIR_peaking(channelR_->cf_, channelR_->q_Factor_, channelR_->gain_, channelR_->coefficients_a_.data(), channelR_->coefficients_b_.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->coefficients_A_[1][m] = channelR_->coefficients_a_[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->coefficients_B_[1][m] = channelR_->coefficients_b_[m];
	}

	// �Ւf���g��
	channelR_->cf_ = 100.0 / pcm0_->fs;

	// �N�I���e�B�t�@�N�^
	channelR_->q_Factor_ = 1.0 / sqrt(2.0);
	channelR_->gain_ = -1.0;

	// IIR�t�B���^�̐݌v
	IIR_high_shelving(channelR_->cf_, channelR_->q_Factor_, channelR_->gain_, channelR_->coefficients_a_.data(), channelR_->coefficients_b_.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->coefficients_A_[2][m] = channelR_->coefficients_a_[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->coefficients_B_[2][m] = channelR_->coefficients_b_[m];
	}
}

void Equalizer::ChannelL_Equalizer(void)
{
	// ���`�����l���̃C�R���C�U����
	for (int i = 0; i < 3; i++)
	{
		for (int n = 0; n < pcm1_->length; n++)
		{
			// �o�͐M���o�b�t�@�̒l��0�Ƀ��Z�b�g
			pcm1_->sL[n] = 0.0;
		}

		for (int n = 0; n < pcm1_->length; n++)
		{

			// FIR�t�B���^�����O
			for (int m = 0; m <= delaylineNum_; m++)
			{
				if (n - m >= 0)
				{
					pcm1_->sL[n] += channelL_->coefficients_B_[i][m] * pcm0_->sL[n - m];
				}
			}

			// IIR�t�B���^�����O
			for (int m = 1; m <= delaylineNum_; m++)
			{
				if (n - m >= 0)
				{
					pcm1_->sL[n] += -channelL_->coefficients_A_[i][m] * pcm1_->sL[n - m];
				}
			}
		}

		// �f�[�^�̃R�s�[
		for (int n = 0; n < pcm1_->length; n++)
		{
			pcm0_->sL[n] = pcm1_->sL[n];
		}
	}
}

void Equalizer::ChannelR_Equalizer(void)
{
	//�E�`�����l���̃C�R���C�U����(�ȉ����������̂��R�����g�ȗ��j
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
					pcm1_->sR[n] += channelR_->coefficients_B_[i][m] * pcm0_->sR[n - m];
				}
			}
			for (int m = 1; m <= delaylineNum_; m++)
			{
				if (n - m >= 0)
				{
					pcm1_->sR[n] += -channelR_->coefficients_A_[i][m] * pcm1_->sR[n - m];
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
	ChannelL_IIR();

	// �E�`�����l���̏�����
	ChannelR_IIR();

	// ���`�����l���̃��E����
	ChannelL_Equalizer();

	// �E�`�����l���̃��E����
	ChannelR_Equalizer();

	// wav�t�@�C���̏o��
	lpWave.WaveWrite(*pcm1_, afterFileName);
}
