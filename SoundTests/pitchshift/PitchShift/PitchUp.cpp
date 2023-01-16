#include "PitchUp.h"
#include "../Wave/Wave.h"

#include "sinc.h"

PitchUp::PitchUp()
{
	rate = 0.8;	// ���̍�����2�{�ɂ���
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

void PitchUp::GenelatePitchUpWaveFile(void)
{
	lpWave.wave_read_16bit_stereo(pcm0_, L"Sound/Peak_test_A.wav");

	pcm1_.fs = pcm0_.fs;										// �W�{�����g��
	pcm1_.bits = pcm0_.bits;									// �ʎq�����x
	pcm1_.length = (int)(pcm0_.length / rate) + 1;				// ���̃f�[�^�̒���
	pcm1_.sL = (double*)calloc(pcm1_.length, sizeof(double));	// ���̃f�[�^
	pcm1_.sR = (double*)calloc(pcm1_.length, sizeof(double));	// ���̃f�[�^

	template_size = (int)(pcm1_.fs * 0.01);			// ���֊֐��̃T�C�Y

	// ���E�`�����l���ŕ�����
	channelL_.pmin = (int)(pcm1_.fs * 0.005);		// �s�[�N�̑{���͈͂̉���
	channelL_.pmax = (int)(pcm1_.fs * 0.02);		// �s�[�N�̒T���͈͂̏��

	channelL_.x = (double*)calloc(template_size, sizeof(double));
	channelL_.y = (double*)calloc(template_size, sizeof(double));
	channelL_.r = (double*)calloc((channelL_.pmax + 1), sizeof(double));

	channelR_.pmin = (int)(pcm1_.fs * 0.005);		// �s�[�N�̑{���͈͂̉���
	channelR_.pmax = (int)(pcm1_.fs * 0.02);		// �s�[�N�̒T���͈͂̏��

	channelR_.x = (double*)calloc(template_size, sizeof(double));
	channelR_.y = (double*)calloc(template_size, sizeof(double));
	channelR_.r = (double*)calloc((channelR_.pmax + 1), sizeof(double));

	channelL_.offset0 = 0;
	channelL_.offset1 = 0;

	channelR_.offset0 = 0;
	channelR_.offset1 = 0;

	// �`�F���l��L�p�̏���
	while (channelL_.offset0 + channelL_.pmax * 2 < pcm0_.length)
	{
		for (int n = 0; n < template_size; n++)
		{
			channelL_.x[n] = pcm0_.sL[channelL_.offset0 + n];		// �{���̉��f�[�^	
		}

		rmax = 0.0;
		channelL_.p = channelL_.pmin;
		for (int m = channelL_.pmin; m <= channelL_.pmax; m++)
		{
			for (int n = 0; n < template_size; n++)
			{
				channelL_.y[n] = pcm0_.sL[channelL_.offset0 + m + n];	// m�T���v�����炵�����f�[�^
			}
			channelL_.r[m] = 0.0;
			for (int n = 0; n < template_size; n++)
			{
				channelL_.r[m] += channelL_.x[n] * channelL_.y[n];	// ���֊֐�
			}
			if (channelL_.r[m] > rmax)
			{
				rmax = channelL_.r[m];	// ���֊֐��̃s�[�N
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

		channelL_.q = (int)(channelL_.p / (1.0 - rate) + 0.5);
		for (int n = channelL_.p; n < channelL_.q; n++)
		{
			if (channelL_.offset0 + channelL_.p + n >= pcm0_.length)
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
		for (int n = 0; n < template_size; n++)
		{
			channelR_.x[n] = pcm0_.sR[channelR_.offset0 + n];		// �{���̉��f�[�^	
		}

		rmax = 0.0;
		channelR_.p = channelR_.pmin;
		for (int m = channelR_.pmin; m <= channelR_.pmax; m++)
		{
			for (int n = 0; n < template_size; n++)
			{
				channelR_.y[n] = pcm0_.sR[channelR_.offset0 + m + n];	// m�T���v�����炵�����f�[�^
			}
			channelR_.r[m] = 0.0;
			for (int n = 0; n < template_size; n++)
			{
				channelR_.r[m] += channelR_.x[n] * channelR_.y[n];	// ���֊֐�
			}
			if (channelR_.r[m] > rmax)
			{
				rmax = channelR_.r[m];	// ���֊֐��̃s�[�N
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

		channelR_.q = (int)(channelR_.p / (1.0 - rate) + 0.5);
		for (int n = channelR_.p; n < channelR_.q; n++)
		{
			if (channelR_.offset0 + channelR_.p + n >= pcm0_.length)
			{
				break;
			}
			pcm1_.sR[channelR_.offset1 + channelR_.p + n] = pcm0_.sR[channelR_.offset0 + n];
		}

		channelR_.offset0 += channelR_.q;							// offset0�̍X�V
		channelR_.offset1 += channelR_.p + channelR_.q;			// offset1�̍X�V
	}

	pitch = 1.0 / rate;

	pcm2_.fs = pcm0_.fs;											// �W�{�����g��
	pcm2_.bits = pcm0_.bits;										// �ʎq�����x
	pcm2_.length = pcm0_.length;									// ���f�[�^�̒���
	pcm2_.sL = (double*)calloc(pcm2_.length, sizeof(double));		// ���f�[�^
	pcm2_.sR = (double*)calloc(pcm2_.length, sizeof(double));		// ���f�[�^

	N = 128;		// �n�j���O���̃T�C�Y

	for (int n = 0; n < pcm2_.length; n++)
	{
		t = pitch * n;

		channelL_.ta = (int)t;

		if (t == channelL_.ta)
		{
			channelL_.tb = channelL_.ta;
		}
		else
		{
			channelL_.tb = channelL_.ta + 1;
		}

		for (int m = channelL_.tb - N / 2; m <= channelL_.ta + N / 2; m++)
		{
			if (m >= 0 && m < pcm1_.length)
			{
				pcm2_.sL[n] += pcm1_.sL[m] * sinc(M_PI * (t - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (t - m) / (N * 2 + 1)));
			}
		}
	}

	for (int n = 0; n < pcm2_.length; n++)
	{
		t = pitch * n;

		channelR_.ta = (int)t;

		if (t == channelR_.ta)
		{
			channelR_.tb = channelR_.ta;
		}
		else
		{
			channelR_.tb = channelR_.ta + 1;
		}

		for (int m = channelR_.tb - N / 2; m <= channelR_.ta + N / 2; m++)
		{
			if (m >= 0 && m < pcm1_.length)
			{
				pcm2_.sR[n] += pcm1_.sR[m] * sinc(M_PI * (t - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (t - m) / (N * 2 + 1)));
			}
		}
	}

	lpWave.wave_write_16bit_stereo(pcm2_, L"Sound/ex11_5.wav");

	// �o�͂ł����烁���������
}
