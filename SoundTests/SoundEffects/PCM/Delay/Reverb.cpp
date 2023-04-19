#include "Reverb.h"
#include "../../Wave/Wave.h"

Reverb::Reverb()
{
}

Reverb::~Reverb()
{
}

void Reverb::Init(void)
{
	repeat_ = 10;
}

void Reverb::ChannelL_Init(void)
{
	channelL_->attenuation = 0.5;
	channelL_->delay = pcm1_->fs * 0.05;
}

void Reverb::ChannelR_Init(void)
{
	channelR_->attenuation = 0.5;
	channelR_->delay = pcm1_->fs * 0.05;
}

void Reverb::GenelateReverbWaveFile(const wchar_t* fileName, const wchar_t* afterFileName)
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