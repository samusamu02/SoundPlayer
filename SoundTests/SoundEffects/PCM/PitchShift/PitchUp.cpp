#include <Windows.h>
#include "PitchUp.h"
#include "../../Wave/Wave.h"
#include "../../common/sinc.h"

PitchUp::PitchUp()
{
	// �����Ȃ�
}

PitchUp::~PitchUp()
{
	// �����Ȃ�
}

void PitchUp::Init(void)
{
	// �ϐ��̏�����
	correlationSize_ = static_cast<int>(pcm1_->fs * 0.001);
	pitch_ = 1.0 / rate_;
	hanningSize_ = 128;
}

void PitchUp::ChannelL_Init(void)
{
	// ���`�����l���̕ϐ��̏�����
	channelL_->search_min_ = static_cast<int>(pcm1_->fs * 0.005);
	channelL_->search_max_ = static_cast<int>(pcm1_->fs * 0.02);

	channelL_->soundData_.resize(correlationSize_);
	channelL_->shiftData_.resize(correlationSize_);
	channelL_->correlation_.resize(channelL_->search_max_ + 1.0);

	channelL_->in_pos_ = 0;
	channelL_->out_pos_ = 0;
}

void PitchUp::ChannelR_Init(void)
{
	// �E�`�����l���̕ϐ��̏�����
	channelR_->search_min_ = static_cast<int>(pcm1_->fs * 0.005);
	channelR_->search_max_ = static_cast<int>(pcm1_->fs * 0.02);

	channelR_->soundData_.resize(correlationSize_);
	channelR_->shiftData_.resize(correlationSize_);
	channelR_->correlation_.resize(channelR_->search_max_ + 1.0);

	channelR_->in_pos_ = 0;
	channelR_->out_pos_ = 0;
}

void PitchUp::ChannelL_Timestretching(void)
{
	// ���`�����l���̃^�C���X�g���b�`����
	while (channelL_->in_pos_ + channelL_->search_max_ * 2 < pcm0_->length)
	{
		for (int n = 0; n < correlationSize_; n++)
		{
			// ���̉��f�[�^�̃R�s�[
			channelL_->soundData_[n] = pcm0_->sL[channelL_->in_pos_ + n];
		}

		// ���֊֐��͈̔͂̏�����
		peak_ = 0.0;
		int p = channelL_->search_min_;

		for (int m = channelL_->search_min_; m <= channelL_->search_max_; m++)
		{
			for (int n = 0; n < correlationSize_; n++)
			{
				// m�T���v�����炵�����f�[�^
				channelL_->shiftData_[n] = pcm0_->sL[channelL_->in_pos_ + m + n];
			}

			// ���֊֐��̌v�Z
			channelL_->correlation_[m] = 0.0;
			for (int n = 0; n < correlationSize_; n++)
			{
				channelL_->correlation_[m] += channelL_->soundData_[n] * channelL_->shiftData_[n];
			}
			if (channelL_->correlation_[m] > peak_)
			{
				// ���֊֐��̃s�[�N
				peak_ = channelL_->correlation_[m];

				// �g�`�̎���
				p = m;
			}
		}

		// �d�ݕt�����s���A�^�C���X�g���b�`���pcm�̐���
		for (int n = 0; n < p; n++)
		{
			pcm1_->sL[channelL_->out_pos_ + n] = pcm0_->sL[channelL_->in_pos_ + n];

			// �P�������̏d�ݕt��
			pcm1_->sL[channelL_->out_pos_ + p + n] = pcm0_->sL[channelL_->in_pos_ + p + n] * (p - n) / p;
			// �P�������̏d�ݕt��
			pcm1_->sL[channelL_->out_pos_ + p + n] += pcm0_->sL[channelL_->in_pos_ + n] * n / p;
		}

		// �d�ݕt���͈̔͂𒴂��������͓��Ԋu�ŃT���v�����O
		int q = static_cast<int>(p * rate_ / (1.0 - rate_) + 0.5);
		for (int n = p; n < q; n++)
		{
			if (channelL_->in_pos_ + n >= pcm0_->length)
			{
				break;
			}
			pcm1_->sL[channelL_->out_pos_ + p + n] = pcm0_->sL[channelL_->in_pos_ + n];
		}

		// pos�̍X�V
		channelL_->in_pos_ += q;
		channelL_->out_pos_ += p + q;
	}
}

void PitchUp::ChannelR_Timestretching(void)
{
	// �E�`�����l���Ɠ����������s��(�ȉ����l�̏����ׂ̈̃R�����g�ȗ�)
	while (channelR_->in_pos_ + channelR_->search_max_ * 2 < pcm0_->length)
	{
		for (int n = 0; n < correlationSize_; n++)
		{
			channelR_->soundData_[n] = pcm0_->sR[channelR_->in_pos_ + n];
		}

		peak_ = 0.0;
		int p = channelR_->search_min_;

		for (int m = channelR_->search_min_; m <= channelR_->search_max_; m++)
		{
			for (int n = 0; n < correlationSize_; n++)
			{
				channelR_->shiftData_[n] = pcm0_->sR[channelR_->in_pos_ + m + n];
			}
			channelR_->correlation_[m] = 0.0;
			for (int n = 0; n < correlationSize_; n++)
			{
				channelR_->correlation_[m] += channelR_->soundData_[n] * channelR_->shiftData_[n];
			}
			if (channelR_->correlation_[m] > peak_)
			{
				peak_ = channelR_->correlation_[m];

				p = m;
			}
		}

		for (int n = 0; n < p; n++)
		{
			pcm1_->sR[channelR_->out_pos_ + n] = pcm0_->sR[channelR_->in_pos_ + n];

			pcm1_->sR[channelR_->out_pos_ + p + n] = pcm0_->sR[channelR_->in_pos_ + p + n] * (p - n) / p;
			pcm1_->sR[channelR_->out_pos_ + p + n] += pcm0_->sR[channelR_->in_pos_ + n] * n / p;
		}

		int q = static_cast<int>(p * rate_ / (1.0 - rate_) + 0.5);
		for (int n = p; n < q; n++)
		{
			if (channelR_->in_pos_ + n >= pcm0_->length)
			{
				break;
			}
			pcm1_->sR[channelR_->out_pos_ + p + n] = pcm0_->sR[channelR_->in_pos_ + n];
		}

		channelR_->in_pos_ += q;
		channelR_->out_pos_ += p + q;
	}
}

void PitchUp::ChannelL_Resampling(void)
{
	// �s�b�`�ύX���s��
	for (int n = 0; n < pcm2_->length; n++)
	{
		// ���݂̃C���f�b�N�X�Ƀs�b�`���|�����l����
		timeIndex_ = pitch_ * n;

		// �f�[�^�̃R�s�[
		channelL_->currentIndex_ = static_cast<int>(timeIndex_);

		// �����ƕ��������ŕ�����
		if (timeIndex_ == channelL_->currentIndex_)
		{

			channelL_->nextIndex_ = channelL_->currentIndex_;
		}
		else
		{
			// ���������̏ꍇ��+1������
			channelL_->nextIndex_ = channelL_->currentIndex_ + 1;
		}

		// ���֐���sinc�֐���p���ĐV����pcm�f�[�^���v�Z����
		for (double m = channelL_->nextIndex_ - hanningSize_ / 2; m <= channelL_->currentIndex_ + hanningSize_ / 2; m++)
		{
			if (m >= 0 && m < pcm1_->length)
			{
				pcm2_->sL[n] += pcm1_->sL[m] * sinc(M_PI * (timeIndex_ - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (timeIndex_ - m) / (hanningSize_ * 2 + 1)));
			}
		}
	}
}

void PitchUp::ChannelR_Resampling(void)
{
	// �E�`�����l���Ɠ����������s��(�ȉ����l�̏����ׂ̈̃R�����g�ȗ�)
	for (int n = 0; n < pcm2_->length; n++)
	{
		timeIndex_ = pitch_ * n;

		channelR_->currentIndex_ = static_cast<int>(timeIndex_);

		if (timeIndex_ == channelR_->currentIndex_)
		{
			channelR_->nextIndex_ = channelR_->currentIndex_;
		}
		else
		{
			channelR_->nextIndex_ = channelR_->currentIndex_ + 1;
		}

		for (double m = channelR_->nextIndex_ - hanningSize_ / 2; m <= channelR_->currentIndex_ + hanningSize_ / 2; m++)
		{
			if (m >= 0 && m < pcm1_->length)
			{
				pcm2_->sR[n] += pcm1_->sR[m] * sinc(M_PI * (timeIndex_ - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (timeIndex_ - m) / (hanningSize_ * 2 + 1)));
			}
		}
	}
}

void PitchUp::GenelatePitchShiftWaveFile(const double rate ,const wchar_t* fileName,const wchar_t* afterFileName)
{
	// Wav��ǂݍ���
	lpWave.WaveRead(*pcm0_, fileName);
	
	// �^�C���X�g���b�`�̐L�k������
	rate_ = rate;

	// ����PCM�ƃG�t�F�N�g��K�p����PCM�̒l���Z�b�g����
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

	// wav�t�@�C���̏o��
	lpWave.WaveWrite(*pcm2_, afterFileName);
}
