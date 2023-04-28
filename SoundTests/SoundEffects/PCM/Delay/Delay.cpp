#include "Delay.h"
#include "../../Wave/Wave.h"

Delay::Delay()
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

Delay::~Delay()
{
}

void Delay::Init(void)
{
	// �J��Ԃ���
	repeat_ = 2;
}

void Delay::ChannelL_Init(void)
{
	// ������
	channelL_->attenuation_ = 0.5;

	// �x������
	channelL_->delay_ = pcm1_->fs * 0.375;
}

void Delay::ChannelR_Init(void)
{
	// ������
	channelR_->attenuation_ = 0.5;

	// �x������
	channelR_->delay_ = pcm1_->fs * 0.375;
}

void Delay::ChannelL_Delay(void)
{
	// ���`�����l���̃f�B���C����
	for (int n = 0; n < pcm1_->length; n++)
	{
		// ���݂̎����̉��f�[�^
		pcm1_->sL[n] = pcm0_->sL[n];

		for (int i = 1;i <= repeat_; i++)
		{
			int m = static_cast<int>(static_cast<double>(n) - static_cast<double>(i) * channelL_->delay_);

			if (m >= 0)
			{
				// �ߋ��̉��f�[�^���~�b�N�X����
				pcm1_->sL[n] += pow(channelL_->attenuation_, static_cast<double>(i)) * pcm0_->sL[m];
			}
		}
	}
}

void Delay::ChannelR_Delay(void)
{
	// �E�`�����l���̃f�B���C����
	for (int n = 0; n < pcm1_->length; n++)
	{
		// ���݂̎����̉��f�[�^
		pcm1_->sR[n] = pcm0_->sR[n];

		for (int i = 1; i <= repeat_; i++)
		{
			int m = static_cast<int>(static_cast<double>(n) - static_cast<double>(i) * channelR_->delay_);

			if (m >= 0)
			{
				// �ߋ��̉��f�[�^���~�b�N�X����
				pcm1_->sR[n] += pow(channelR_->attenuation_, static_cast<double>(i)) * pcm0_->sR[m];
			}
		}
	}
}

void Delay::GenelateDelayWaveFile(const wchar_t* fileName, const wchar_t* afterFileName)
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
	ChannelL_Delay();

	// �E�`�����l���̃��E����
	ChannelR_Delay();

	// wav�t�@�C���̏o��
	lpWave.WaveWrite(*pcm1_, afterFileName);
}
