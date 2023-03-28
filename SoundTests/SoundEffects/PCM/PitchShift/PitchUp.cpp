#include <Windows.h>
#include "PitchUp.h"
#include "../sinc.h"
#include "../../Wave/Wave.h"

PitchUp::PitchUp()
{
}

PitchUp::~PitchUp()
{
	// �X�}�[�g�|�C���^�ŊǗ����Ă���̂ŉ���̏����͏����K�v�Ȃ�
}

bool PitchUp::GenelateEffectWaveFile(const double rate ,const wchar_t* fileName,const wchar_t* afterFileName)
{
	if (rate < 0.0)
	{
		return false;
	}

	// Wav��ǂݍ���
	lpWave.WaveRead(*pcm0_, fileName);
	
	// �s�b�`�̔{������
	rate_ = rate;

	// ����PCM�ƕϊ����PCM�̒l���Z�b�g����
	pcmSet_->PCMSetPitchShift(*pcm1_, *pcm0_,rate_);

	// �ϐ�������
	Init();

	// ���`�����l���̕ϐ�������
	ChannelL_Init();

	// �E�`�����l���̕ϐ�������
	ChannelR_Init();

	// ���`�����l���̃^�C���X�g���b�`
	ChannelL_Timestretching();

	// �E�`�����l���̃^�C���X�g���b�`
	ChannelR_Timestretching();

	// ���`�����l���̃^�C���X�g���b�`������������o�͗p��PCM�Ƀf�[�^���Z�b�g
	pcmSet_->PCMSetNormal(*pcm2_, *pcm0_);

	// ���`�����l���̃��T���v�����O
	ChannelL_Resampling();

	// �E�`�����l���̃��T���v�����O
	ChannelR_Resampling();

	// ��������
	lpWave.WaveWrite(*pcm2_, afterFileName);

	return true;
}

void PitchUp::Init(void)
{
	template_size_ = static_cast<int>(pcm1_->fs * 0.001);				

	// �s�b�`�ύX�̊��������߂�
	pitch_ = 1.0 / rate_;

	// �n�j���O���̃T�C�Y
	N_ = 128;
}

void PitchUp::ChannelL_Init(void)
{
	channelL_->pmin = static_cast<int>(pcm1_->fs * 0.005);
	channelL_->pmax = static_cast<int>(pcm1_->fs * 0.02);

	channelL_->x.resize(template_size_);
	channelL_->y.resize(template_size_);
	channelL_->r.resize(channelL_->pmax + 1.0);

	channelL_->offset0 = 0;
	channelL_->offset1 = 0;
}

void PitchUp::ChannelR_Init(void)
{
	channelR_->pmin = static_cast<int>(pcm1_->fs * 0.005);
	channelR_->pmax = static_cast<int>(pcm1_->fs * 0.02);

	channelR_->x.resize(template_size_);
	channelR_->y.resize(template_size_);
	channelR_->r.resize(channelR_->pmax + 1.0);

	channelR_->offset0 = 0;
	channelR_->offset1 = 0;
}

void PitchUp::ChannelL_Timestretching(void)
{
	while (channelL_->offset0 + channelL_->pmax * 2 < pcm0_->length)
	{
		for (int n = 0; n < template_size_; n++)
		{
			// ���̉��f�[�^���i�[����
			channelL_->x[n] = pcm0_->sL[channelL_->offset0 + n];
		}

		rmax_ = 0.0;

		// ���֊֐��̃s�[�N�̈ʒu
		int peakPos = channelL_->pmin;
		for (int m = channelL_->pmin; m <= channelL_->pmax; m++)
		{
			for (int n = 0; n < template_size_; n++)
			{
				// m�T���v�����炵�����f�[�^
				channelL_->y[n] = pcm0_->sL[channelL_->offset0 + m + n];
			}
			channelL_->r[m] = 0.0;
			for (int n = 0; n < template_size_; n++)
			{
				// ���֊֐�
				channelL_->r[m] += channelL_->x[n] * channelL_->y[n];
			}
			if (channelL_->r[m] > rmax_)
			{
				// ���֊֐��̃s�[�N
				rmax_ = channelL_->r[m];
				// �g�`�̎���
				peakPos = m;
			}
		}

		// �����グ��
		for (int n = 0; n < peakPos; n++)
		{
			pcm1_->sL[channelL_->offset1 + n] = pcm0_->sL[channelL_->offset0 + n];

			// �P�������̏d�ݕt��
			pcm1_->sL[channelL_->offset1 + peakPos + n] = pcm0_->sL[channelL_->offset0 + peakPos + n] * (peakPos - n) / peakPos;
			// �P�������̏d�ݕt��
			pcm1_->sL[channelL_->offset1 + peakPos + n] += pcm0_->sL[channelL_->offset0 + n] * n / peakPos;
		}

		channelL_->q = static_cast<int>(peakPos * rate_ / (1.0 - rate_) + 0.5);
		for (int n = peakPos; n < channelL_->q; n++)
		{
			if (channelL_->offset0 + n >= pcm0_->length)
			{
				break;
			}
			pcm1_->sL[channelL_->offset1 + peakPos + n] = pcm0_->sL[channelL_->offset0 + n];
		}

		// �I�t�Z�b�g�̍X�V
		channelL_->offset0 += channelL_->q;
		channelL_->offset1 += peakPos + channelL_->q;
	}
}

void PitchUp::ChannelR_Timestretching(void)
{
	while (channelR_->offset0 + channelR_->pmax * 2 < pcm0_->length)
	{
		for (int n = 0; n < template_size_; n++)
		{
			// ���̃f�[�^���i�[����
			channelR_->x[n] = pcm0_->sR[channelR_->offset0 + n];
		}

		rmax_ = 0.0;

		int peakPos = channelR_->pmin;

		for (int m = channelR_->pmin; m <= channelR_->pmax; m++)
		{
			for (int n = 0; n < template_size_; n++)
			{
				// m�T���v�����炵�����f�[�^
				channelR_->y[n] = pcm0_->sR[channelR_->offset0 + m + n];
			}
			channelR_->r[m] = 0.0;
			for (int n = 0; n < template_size_; n++)
			{
				// ���֊֐�
				channelR_->r[m] += channelR_->x[n] * channelR_->y[n];
			}
			if (channelR_->r[m] > rmax_)
			{
				// ���֊֐��̃s�[�N
				rmax_ = channelR_->r[m];
				// �g�`�̎���
				peakPos = m;
			}
		}

		// �����グ��
		for (int n = 0; n < peakPos; n++)
		{
			pcm1_->sR[channelR_->offset1 + n] = pcm0_->sR[channelR_->offset0 + n];

			pcm1_->sR[channelR_->offset1 + peakPos + n] = pcm0_->sR[channelR_->offset0 + peakPos + n] * (peakPos - n) / peakPos;
			pcm1_->sR[channelR_->offset1 + peakPos + n] += pcm0_->sR[channelR_->offset0 + n] * n / peakPos;
		}

		channelR_->q = static_cast<int>(peakPos * rate_ / (1.0 - rate_) + 0.5);
		for (int n = peakPos; n < channelR_->q; n++)
		{
			if (channelR_->offset0 + n >= pcm0_->length)
			{
				break;
			}
			pcm1_->sR[channelR_->offset1 + peakPos + n] = pcm0_->sR[channelR_->offset0 + n];
		}

		// �I�t�Z�b�g�̍X�V
		channelR_->offset0 += channelR_->q;
		channelR_->offset1 += peakPos + channelR_->q;
	}
}

void PitchUp::ChannelL_Resampling(void)
{
	for (int n = 0; n < pcm2_->length; n++)
	{
		t_ = pitch_ * n;

		channelL_->ta = static_cast<int>(t_);

		if (t_ == channelL_->ta)
		{

			channelL_->tb = channelL_->ta;
		}
		else
		{

			channelL_->tb = channelL_->ta + 1;
		}

		for (double m = channelL_->tb - N_ / 2; m <= channelL_->ta + N_ / 2; m++)
		{
			if (m >= 0 && m < pcm1_->length)
			{
				pcm2_->sL[n] += pcm1_->sL[m] * sinc(M_PI * (t_ - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (t_ - m) / (N_ * 2 + 1)));
			}
		}
	}
}

void PitchUp::ChannelR_Resampling(void)
{
	for (int n = 0; n < pcm2_->length; n++)
	{
		t_ = pitch_ * n;

		// ���������߂�
		channelR_->ta = static_cast<int>(t_);

		//�@�����ƕ��������_�𕪂���
		if (t_ == channelR_->ta)
		{
			channelR_->tb = channelR_->ta;
		}
		else
		{
			// ���������_�̏ꍇ+1������
			channelR_->tb = channelR_->ta + 1;
		}

		// �t�B���^�[��������
		for (double m = channelR_->tb - N_ / 2; m <= channelR_->ta + N_ / 2; m++)
		{
			if (m >= 0 && m < pcm1_->length)
			{
				pcm2_->sR[n] += pcm1_->sR[m] * sinc(M_PI * (t_ - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (t_ - m) / (N_ * 2 + 1)));
			}
		}
	}
}
