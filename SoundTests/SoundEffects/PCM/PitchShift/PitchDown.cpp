#include <Windows.h>
#include "PitchDown.h"
#include "../../Wave/Wave.h"
#include "../../common/sinc.h"

PitchDown::PitchDown()
{

}

PitchDown::~PitchDown()
{

}

void PitchDown::Init(void)
{
	// �ϐ��̏�����
	correlationSize_ = static_cast<int>(pcm1_->fs * 0.001);
	pitch_ = 1.0 / rate_;
	hanningSize_ = 128;
}

void PitchDown::ChannelL_Init(void)
{
	// ���`�����l���̕ϐ��̏�����
	channelL_->search_min = static_cast<int>(pcm1_->fs * 0.005);
	channelL_->search_max = static_cast<int>(pcm1_->fs * 0.02);

	channelL_->soundData.resize(correlationSize_);
	channelL_->shiftData.resize(correlationSize_);
	channelL_->correlation.resize(channelL_->search_max + 1.0);

	channelL_->in_pos = 0;
	channelL_->out_pos = 0;
}

void PitchDown::ChannelR_Init(void)
{
	// �E�`�����l���̕ϐ��̏�����
	channelR_->search_min = static_cast<int>(pcm1_->fs * 0.005);
	channelR_->search_max = static_cast<int>(pcm1_->fs * 0.02);

	channelR_->soundData.resize(correlationSize_);
	channelR_->shiftData.resize(correlationSize_);
	channelR_->correlation.resize(channelR_->search_max + 1.0);

	channelR_->in_pos = 0;
	channelR_->out_pos = 0;
}

void PitchDown::ChannelL_Timestretching(void)
{
	while (channelL_->in_pos + channelL_->search_max * 2 < pcm0_->length)
	{
		for (int n = 0; n < correlationSize_; n++)
		{
			// ���̉��f�[�^�̃R�s�[
			channelL_->soundData[n] = pcm0_->sL[channelL_->in_pos + n];
		}

		// ���֊֐��͈̔͂̏�����
		peak_ = 0.0;
		double p = channelL_->search_min;

		for (int m = channelL_->search_min; m <= channelL_->search_max; m++)
		{
			for (int n = 0; n < correlationSize_; n++)
			{
				// m�T���v�����炵�����f�[�^
				channelL_->shiftData[n] = pcm0_->sL[channelL_->in_pos + m + n];
			}

			// ���֊֐��̌v�Z
			channelL_->correlation[m] = 0.0;
			for (int n = 0; n < correlationSize_; n++)
			{
				channelL_->correlation[m] += channelL_->soundData[n] * channelL_->shiftData[n];
			}
			if (channelL_->correlation[m] > peak_)
			{
				// ���֊֐��̃s�[�N
				peak_ = channelL_->correlation[m];

				// �g�`�̎���
				p = m;
			}
		}

		// �d�ݕt�����s���A�^�C���X�g���b�`���pcm�𐶐�
		for (int n = 0; n < p; n++)
		{
			// �P�������̏d�ݕt��
			pcm1_->sL[channelL_->out_pos + n] = pcm0_->sL[channelL_->in_pos + n] * (p - n) / p;
			// �P�������̏d�ݕt��
			pcm1_->sL[channelL_->out_pos + n] += pcm0_->sL[channelL_->in_pos + p + n] * n / p;
		}

		// �d�ݕt���͈̔͂𒴂��������͓��Ԋu�ŃT���v�����O
		int q = static_cast<int>(p / (rate_ - 1.0) + 0.5);
		for (int n = p; n < q; n++)
		{
			if (channelL_->in_pos + p + n >= pcm0_->length)
			{
				break;
			}
			pcm1_->sL[channelL_->out_pos + n] = pcm0_->sL[channelL_->in_pos + p + n];
		}

		// pos�̍X�V
		channelL_->in_pos += p + q;
		channelL_->out_pos += q;
	}
}

void PitchDown::ChannelR_Timestretching(void)
{
	// ���`�����l���Ɠ����������s��(�ȉ����l�̏����ׂ̈̃R�����g�ȗ�)
	while (channelR_->in_pos + channelR_->search_max * 2 < pcm0_->length)
	{
		for (int n = 0; n < correlationSize_; n++)
		{
			channelR_->soundData[n] = pcm0_->sR[channelR_->in_pos + n];
		}

		peak_ = 0.0;
		int p = channelR_->search_min;

		for (int m = channelR_->search_min; m <= channelR_->search_max; m++)
		{
			for (int n = 0; n < correlationSize_; n++)
			{
				channelR_->shiftData[n] = pcm0_->sR[channelR_->in_pos + m + n];
			}
			channelR_->correlation[m] = 0.0;
			for (int n = 0; n < correlationSize_; n++)
			{
				channelR_->correlation[m] += channelR_->soundData[n] * channelR_->shiftData[n];
			}
			if (channelR_->correlation[m] > peak_)
			{
				peak_ = channelR_->correlation[m];

				p = m;
			}
		}

		for (int n = 0; n < p; n++)
		{
			pcm1_->sR[channelR_->out_pos + n] = pcm0_->sR[channelR_->in_pos + n] * (p - n) / p;
			pcm1_->sR[channelR_->out_pos + n] += pcm0_->sR[channelR_->in_pos + p + n] * n / p;
		}

		int q = static_cast<int>(p / (rate_ - 1.0) + 0.5);
		for (int n = p; n < q; n++)
		{
			if (channelR_->in_pos + p + n >= pcm0_->length)
			{
				break;
			}
			pcm1_->sR[channelR_->out_pos + n] = pcm0_->sR[channelR_->in_pos + p + n];
		}

		channelR_->in_pos += p + q;
		channelR_->out_pos += q;
	}
}

void PitchDown::ChannelL_Resampling(void)
{
	// �s�b�`�ύX���s��
	for (int n = 0; n < pcm2_->length; n++)
	{
		// ���݂̃C���f�b�N�X�Ƀs�b�`���|�����l����
		timeIndex_ = pitch_ * n;

		// �f�[�^�̃R�s�[
		channelL_->currentIndex = static_cast<int>(timeIndex_);

		// �����ƕ��������ŕ�����
		if (timeIndex_ == channelL_->currentIndex)
		{
			channelL_->nextIndex = channelL_->currentIndex;
		}
		else
		{
			// ���������̏ꍇ��+1������
			channelL_->nextIndex = channelL_->currentIndex + 1;
		}

		// ���֐���sinc�֐���p���ĐV����pcm�f�[�^���v�Z����
		for (int m = channelL_->nextIndex - hanningSize_ / 2; m <= channelL_->currentIndex + hanningSize_ / 2; m++)
		{
			if (m >= 0 && m < pcm1_->length)
			{
				// sinc�֐����g���ăt�B���^��������
				pcm2_->sL[n] += pcm1_->sL[m] * sinc(M_PI * (timeIndex_ - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (timeIndex_ - m) / (hanningSize_ * 2 + 1)));
			}
		}
	}
}

void PitchDown::ChannelR_Resampling(void)
{
	// ���`�����l���Ɠ����������s��(�ȉ����l�̏����ׂ̈̃R�����g�ȗ�)
	for (int n = 0; n < pcm2_->length; n++)
	{
		timeIndex_ = pitch_ * n;

		channelR_->currentIndex = static_cast<int>(timeIndex_);

		if (timeIndex_ == channelR_->currentIndex)
		{
			channelR_->nextIndex = channelR_->currentIndex;
		}
		else
		{
			channelR_->nextIndex = channelR_->currentIndex + 1;
		}

		for (int m = channelR_->nextIndex - hanningSize_ / 2; m <= channelR_->currentIndex + hanningSize_ / 2; m++)
		{
			if (m >= 0 && m < pcm1_->length)
			{
				pcm2_->sR[n] += pcm1_->sR[m] * sinc(M_PI * (timeIndex_ - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (timeIndex_ - m) / (hanningSize_ * 2 + 1)));
			}
		}
	}
}

void PitchDown::GenelatePitchShiftWaveFile(const double rate, const wchar_t* fileName, const wchar_t* afterFileName)
{
	// Wav��ǂݍ���
	lpWave.WaveRead(*pcm0_, fileName);

	// �^�C���X�g���b�`�̐L�k������
	rate_ = rate;

	// 	// ����PCM�ƃG�t�F�N�g��K�p����PCM�̒l���Z�b�g����
	pcmSet_->PCMSetPitchShift(*pcm1_, *pcm0_, rate_);

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
}
