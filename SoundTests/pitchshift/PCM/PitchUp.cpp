#include "PitchUp.h"
#include "../Wave/Wave.h"

#include "sinc.h"

PitchUp::PitchUp(double rate)
{
	rate_ = rate;	// ���̍����̕ύX

	pcmSet_ = std::make_unique<PCMSet>();
}

PitchUp::~PitchUp()
{
	// ���������
	free(pcm0_.sL);
	free(pcm0_.sR);
	free(pcm1_.sL);
	free(pcm1_.sR);
	free(pcm2_.sL);
	free(pcm2_.sR);
	free(channelL_.x);
	free(channelL_.y);
	free(channelL_.r);
	free(channelR_.x);
	free(channelR_.y);
	free(channelR_.r);
}

void PitchUp::GenelatePitchUpWaveFile(const wchar_t* fileName,const wchar_t* afterFileName)
{
	lpWave.WaveRead(pcm0_, fileName);

	pcmSet_->PCMSetPitchUp(pcm1_, pcm0_,rate_);

	template_size_ = (int)(pcm1_.fs * 0.01);			// ���֊֐��̃T�C�Y

	// ���E�`�����l���ŕ�����
	channelL_.pmin = (int)(pcm1_.fs * 0.005);		// �s�[�N�̑{���͈͂̉���
	channelL_.pmax = (int)(pcm1_.fs * 0.02);		// �s�[�N�̒T���͈͂̏��

	channelL_.x = (double*)calloc(template_size_, sizeof(double));
	channelL_.y = (double*)calloc(template_size_, sizeof(double));
	channelL_.r = (double*)calloc((channelL_.pmax + 1), sizeof(double));

	channelR_.pmin = (int)(pcm1_.fs * 0.005);		// �s�[�N�̑{���͈͂̉���
	channelR_.pmax = (int)(pcm1_.fs * 0.02);		// �s�[�N�̒T���͈͂̏��

	channelR_.x = (double*)calloc(template_size_, sizeof(double));
	channelR_.y = (double*)calloc(template_size_, sizeof(double));
	channelR_.r = (double*)calloc((channelR_.pmax + 1), sizeof(double));

	channelL_.offset0 = 0;
	channelL_.offset1 = 0;

	channelR_.offset0 = 0;
	channelR_.offset1 = 0;

	// �`�F���l��L�p�̏���
	while (channelL_.offset0 + channelL_.pmax * 2 < pcm0_.length)
	{
		for (int n = 0; n < template_size_; n++)
		{
			channelL_.x[n] = pcm0_.sL[channelL_.offset0 + n];		// �{���̉��f�[�^	
		}

		rmax_ = 0.0;
		channelL_.p = channelL_.pmin;
		for (int m = channelL_.pmin; m <= channelL_.pmax; m++)
		{
			for (int n = 0; n < template_size_; n++)
			{
				channelL_.y[n] = pcm0_.sL[channelL_.offset0 + m + n];	// m�T���v�����炵�����f�[�^
			}
			channelL_.r[m] = 0.0;
			for (int n = 0; n < template_size_; n++)
			{
				channelL_.r[m] += channelL_.x[n] * channelL_.y[n];	// ���֊֐�
			}
			if (channelL_.r[m] > rmax_)
			{
				rmax_ = channelL_.r[m];	// ���֊֐��̃s�[�N
				channelL_.p = m;			// �g�`�̎���
			}
		}

		for (int n = 0; n < channelL_.p; n++)
		{
			pcm1_.sL[channelL_.offset1 + n] = pcm0_.sL[channelL_.offset0 + n];
		}
		for (int n = 0; n < channelL_.p; n++)
		{
			pcm1_.sL[channelL_.offset1 + channelL_.p + n] = pcm0_.sL[channelL_.offset0 + channelL_.p + n] * (channelL_.p - n) / channelL_.p;	// �P�������̏d�ݕt��
			pcm1_.sL[channelL_.offset1 + channelL_.p + n] += pcm0_.sL[channelL_.offset0 + n] * n / channelL_.p;								// �P�������̏d�ݕt��
		}

		channelL_.q = (int)(channelL_.p * rate_ / (1.0 - rate_) + 0.5);
		for (int n = channelL_.p; n < channelL_.q; n++)
		{
			if (channelL_.offset0 + n >= pcm0_.length)
			{
				break;
			}
			pcm1_.sL[channelL_.offset1 + channelL_.p + n] = pcm0_.sL[channelL_.offset0 + n];
		}

		channelL_.offset0 += channelL_.q;		// offset0�̍X�V
		channelL_.offset1 += channelL_.p + channelL_.q;			// offset1�̍X�V
	}

	// �`�����l��R�p�̏���
	while (channelR_.offset0 + channelR_.pmax * 2 < pcm0_.length)
	{
		for (int n = 0; n < template_size_; n++)
		{
			channelR_.x[n] = pcm0_.sR[channelR_.offset0 + n];		// �{���̉��f�[�^	
		}

		rmax_ = 0.0;
		channelR_.p = channelR_.pmin;
		for (int m = channelR_.pmin; m <= channelR_.pmax; m++)
		{
			for (int n = 0; n < template_size_; n++)
			{
				channelR_.y[n] = pcm0_.sR[channelR_.offset0 + m + n];	// m�T���v�����炵�����f�[�^
			}
			channelR_.r[m] = 0.0;
			for (int n = 0; n < template_size_; n++)
			{
				channelR_.r[m] += channelR_.x[n] * channelR_.y[n];	// ���֊֐�
			}
			if (channelR_.r[m] > rmax_)
			{
				rmax_ = channelR_.r[m];	// ���֊֐��̃s�[�N
				channelR_.p = m;			// �g�`�̎���
			}
		}

		for (int n = 0; n < channelR_.p; n++)
		{
			pcm1_.sR[channelR_.offset1 + n] = pcm0_.sR[channelR_.offset0 + n];
		}
		for (int n = 0; n < channelR_.p; n++)
		{
			pcm1_.sR[channelR_.offset1 + channelR_.p + n] = pcm0_.sR[channelR_.offset0 + channelR_.p + n] * (channelR_.p - n) / channelR_.p;	// �P�������̏d�ݕt��
			pcm1_.sR[channelR_.offset1 + channelR_.p + n] += pcm0_.sR[channelR_.offset0 + n] * n / channelR_.p;			// �P�������̏d�ݕt��
		}

		channelR_.q = (int)(channelR_.p * rate_/ (1.0 - rate_) + 0.5);
		for (int n = channelR_.p; n < channelR_.q; n++)
		{
			if (channelR_.offset0 + n >= pcm0_.length)
			{
				break;
			}
			pcm1_.sR[channelR_.offset1 + channelR_.p + n] = pcm0_.sR[channelR_.offset0 + n];
		}

		channelR_.offset0 += channelR_.q;							// offset0�̍X�V
		channelR_.offset1 += channelR_.p + channelR_.q;			// offset1�̍X�V
	}

	pitch_ = 1.0 / rate_;

	pcmSet_->PCMSetNormal(pcm2_, pcm0_);

	N_ = 128;		// �n�j���O���̃T�C�Y

	for (int n = 0; n < pcm2_.length; n++)
	{
		t_ = pitch_ * n;

		channelL_.ta = (int)t_;

		if (t_ == channelL_.ta)
		{
			channelL_.tb = channelL_.ta;
		}
		else
		{
			channelL_.tb = channelL_.ta + 1;
		}

		for (int m = channelL_.tb - N_ / 2; m <= channelL_.ta + N_ / 2; m++)
		{
			if (m >= 0 && m < pcm1_.length)
			{
				pcm2_.sL[n] += pcm1_.sL[m] * sinc(M_PI * (t_ - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (t_ - m) / (N_ * 2 + 1)));
			}
		}
	}

	for (int n = 0; n < pcm2_.length; n++)
	{
		t_ = pitch_ * n;

		channelR_.ta = (int)t_;

		if (t_ == channelR_.ta)
		{
			channelR_.tb = channelR_.ta;
		}
		else
		{
			channelR_.tb = channelR_.ta + 1;
		}

		for (int m = channelR_.tb - N_ / 2; m <= channelR_.ta + N_ / 2; m++)
		{
			if (m >= 0 && m < pcm1_.length)
			{
				pcm2_.sR[n] += pcm1_.sR[m] * sinc(M_PI * (t_ - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (t_ - m) / (N_ * 2 + 1)));
			}
		}
	}

	lpWave.WaveWrite(pcm2_,afterFileName);
}
