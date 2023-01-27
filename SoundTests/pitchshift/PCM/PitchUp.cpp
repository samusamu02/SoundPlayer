#include "PitchUp.h"
#include "../Wave/Wave.h"

#include "sinc.h"
#include <Windows.h>

PitchUp::PitchUp(double rate)
{
	rate_ = rate;	// ���̍����̕ύX

	pcm0_ = std::make_unique<STEREO_PCM>();
	pcm1_ = std::make_unique<STEREO_PCM>();
	pcm2_ = std::make_unique<STEREO_PCM>();
	channelL_ = std::make_unique<ChannelL>();
	channelR_ = std::make_unique<ChannelR>();

	pcmSet_ = std::make_unique<PCMSet>();
}

PitchUp::~PitchUp()
{
	// �X�}�[�g�|�C���^�ŊǗ����Ă���̂ŉ���̏����͏����K�v�Ȃ�
}

void PitchUp::GenelatePitchUpWaveFile(const wchar_t* fileName,const wchar_t* afterFileName)
{
	// Wav��ǂݍ���
	lpWave.WaveRead(*pcm0_, fileName);

	// ����PCM�ƕϊ����PCM�̒l���Z�b�g����
	pcmSet_->PCMSetPitchUp(*pcm1_, *pcm0_,rate_);

	// ���֊֐��̃T�C�Y
	template_size_ = (int)(pcm1_->fs * 0.001);			// �W�{�����g����1000����1�̃T�C�Y

	// ���E�`�����l���ŕ�����
	// ���`�����l��
	channelL_->pmin = (int)(pcm1_->fs * 0.005);			// �s�[�N�̑{���͈͂̉���(L)
	channelL_->pmax = (int)(pcm1_->fs * 0.02);			// �s�[�N�̒T���͈͂̏��(L)

	// �������m��(L)
	channelL_->x.resize(template_size_);					// ���֊֐����̃������T�C�Y�̊m��
	channelL_->y.resize(template_size_);					// ���֊֐����̃������T�C�Y�̊m��
	channelL_->r.resize(channelL_->pmax + 1);

	// �E�`�����l��
	channelR_->pmin = (int)(pcm1_->fs * 0.005);			// �s�[�N�̑{���͈͂̉���(R)
	channelR_->pmax = (int)(pcm1_->fs * 0.02);			// �s�[�N�̒T���͈͂̏��(R)

	// �������m��(R)
	channelR_->x.resize(template_size_);					// ���֊֐����̃������T�C�Y�̊m��
	channelR_->y.resize(template_size_);					// ���֊֐����̃������T�C�Y�̊m��
	channelR_->r.resize(channelR_->pmax + 1);

	channelL_->offset0 = 0;
	channelL_->offset1 = 0;

	channelR_->offset0 = 0;
	channelR_->offset1 = 0;

	// �`�F���l��L�p�̉���L�΂�����(�^�C���X�g���b�`)
	// 1�T���v�����ɏ������s��
	while (channelL_->offset0 + channelL_->pmax * 2 < pcm0_->length)
	{
		for (int n = 0; n < template_size_; n++)
		{
			// ���̉��f�[�^���i�[����
			channelL_->x[n] = pcm0_->sL[channelL_->offset0 + n];			
		}

		rmax_ = 0.0;
		channelL_->p = channelL_->pmin;
		for (int m = channelL_->pmin; m <= channelL_->pmax; m++)
		{
			for (int n = 0; n < template_size_; n++)
			{
				channelL_->y[n] = pcm0_->sL[channelL_->offset0 + m + n];	// m�T���v�����炵�����f�[�^
			}
			channelL_->r[m] = 0.0;
			for (int n = 0; n < template_size_; n++)
			{
				channelL_->r[m] += channelL_->x[n] * channelL_->y[n];	// ���֊֐�
			}
			if (channelL_->r[m] > rmax_)
			{
				rmax_ = channelL_->r[m];	// ���֊֐��̃s�[�N
				channelL_->p = m;			// �g�`�̎���
			}
		}

		for (int n = 0; n < channelL_->p; n++)
		{
			pcm1_->sL[channelL_->offset1 + n] = pcm0_->sL[channelL_->offset0 + n];
		}
		for (int n = 0; n < channelL_->p; n++)
		{
			pcm1_->sL[channelL_->offset1 + channelL_->p + n] = pcm0_->sL[channelL_->offset0 + channelL_->p + n] * (channelL_->p - n) / channelL_->p;	// �P�������̏d�ݕt��
			pcm1_->sL[channelL_->offset1 + channelL_->p + n] += pcm0_->sL[channelL_->offset0 + n] * n / channelL_->p;									// �P�������̏d�ݕt��
		}

		channelL_->q = (int)(channelL_->p * rate_ / (1.0 - rate_) + 0.5);
		for (int n = channelL_->p; n < channelL_->q; n++)
		{
			if (channelL_->offset0 + n >= pcm0_->length)
			{
				break;
			}
			pcm1_->sL[channelL_->offset1 + channelL_->p + n] = pcm0_->sL[channelL_->offset0 + n];
		}

		channelL_->offset0 += channelL_->q;							// offset0�̍X�V
		channelL_->offset1 += channelL_->p + channelL_->q;			// offset1�̍X�V
	}

	// �`�����l��R�p�̉���L�΂�����(�^�C���X�g���b�`)
	while (channelR_->offset0 + channelR_->pmax * 2 < pcm0_->length)
	{
		for (int n = 0; n < template_size_; n++)
		{
			// ���̃f�[�^���i�[����
			channelR_->x[n] = pcm0_->sR[channelR_->offset0 + n];		
		}

		rmax_ = 0.0;
		channelR_->p = channelR_->pmin;
		for (int m = channelR_->pmin; m <= channelR_->pmax; m++)
		{
			for (int n = 0; n < template_size_; n++)
			{
				channelR_->y[n] = pcm0_->sR[channelR_->offset0 + m + n];	// m�T���v�����炵�����f�[�^
			}
			channelR_->r[m] = 0.0;
			for (int n = 0; n < template_size_; n++)
			{
				channelR_->r[m] += channelR_->x[n] * channelR_->y[n];	// ���֊֐�
			}
			if (channelR_->r[m] > rmax_)
			{
				rmax_ = channelR_->r[m];		// ���֊֐��̃s�[�N
				channelR_->p = m;				// �g�`�̎���
			}
		}

		for (int n = 0; n < channelR_->p; n++)
		{
			pcm1_->sR[channelR_->offset1 + n] = pcm0_->sR[channelR_->offset0 + n];
		}
		for (int n = 0; n < channelR_->p; n++)
		{
			pcm1_->sR[channelR_->offset1 + channelR_->p + n] = pcm0_->sR[channelR_->offset0 + channelR_->p + n] * (channelR_->p - n) / channelR_->p;	// �P�������̏d�ݕt��
			pcm1_->sR[channelR_->offset1 + channelR_->p + n] += pcm0_->sR[channelR_->offset0 + n] * n / channelR_->p;									// �P�������̏d�ݕt��
		}

		channelR_->q = (int)(channelR_->p * rate_/ (1.0 - rate_) + 0.5);
		for (int n = channelR_->p; n < channelR_->q; n++)
		{
			if (channelR_->offset0 + n >= pcm0_->length)
			{
				break;
			}
			pcm1_->sR[channelR_->offset1 + channelR_->p + n] = pcm0_->sR[channelR_->offset0 + n];
		}

		channelR_->offset0 += channelR_->q;								// offset0�̍X�V
		channelR_->offset1 += channelR_->p + channelR_->q;				// offset1�̍X�V
	}

	// �s�b�`�ύX�̊��������߂�
	pitch_ = 1.0 / rate_;

	// �^�C���X�g���b�`������������o�͂悤��PCM�Ƀf�[�^���Z�b�g
	pcmSet_->PCMSetNormal(*pcm2_, *pcm0_);

	// �V���N�֐���ł��؂邽�߂Ƀn�j���O�����g�p����
	// �n�j���O���̃T�C�Y
	N_ = 128;	

	// ���ۂɃs�b�`�V�t�g���s��(L)
	for (int n = 0; n < pcm2_->length; n++)
	{
		// �s�b�`�̕ύX���Ȃ̒������s��
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

		for (int m = channelL_->tb - N_ / 2; m <= channelL_->ta + N_ / 2; m++)
		{
			if (m >= 0 && m < pcm1_->length)
			{
				// sinc�֐����g���ăt�B���^��������
				pcm2_->sL[n] += pcm1_->sL[m] * sinc(M_PI * (t_ - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (t_ - m) / (N_ * 2 + 1)));
			}
		}
	}

	// ���ۂɃs�b�`�V�t�g���s��(R)
	for (int n = 0; n < pcm2_->length; n++)
	{
		t_ = pitch_ * n;

		channelR_->ta = (int)t_;

		if (t_ == channelR_->ta)
		{
			channelR_->tb = channelR_->ta;
		}
		else
		{
			channelR_->tb = channelR_->ta + 1;
		}

		for (int m = channelR_->tb - N_ / 2; m <= channelR_->ta + N_ / 2; m++)
		{
			if (m >= 0 && m < pcm1_->length)
			{
				// sinc�֐����g���ăt�B���^��������
				pcm2_->sR[n] += pcm1_->sR[m] * sinc(M_PI * (t_ - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (t_ - m) / (N_ * 2 + 1)));
			}
		}
	}

	// ���ׂẴT���v���̃s�b�`�A�b�v������������V����wav�t�@�C������������
	lpWave.WaveWrite(*pcm2_,afterFileName);

	// �����ł�����ϊ������̃��b�Z�[�W�{�b�N�X��\������
	MessageBox(nullptr, L"�ϊ��������������܂���", L"�ϊ�����", 0);
}
