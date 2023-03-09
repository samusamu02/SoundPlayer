#include "Wah.h"
#include "../Wave/Wave.h"

#include "sinc.h"
#include <Windows.h>

Wah::Wah()
{
	// �C���X�^���X
	pcm0_ = std::make_unique<STEREO_PCM>();
	pcm1_ = std::make_unique<STEREO_PCM>();
	channelL_ = std::make_unique<ChannelL>();
	channelR_ = std::make_unique<ChannelR>();
	pcmSet_ = std::make_unique<PCMSet>();
}

Wah::~Wah()
{
	// �X�}�[�g�|�C���^�ŊǗ����Ă���̂ŉ���̏����͏����K�v�Ȃ�
}

void Wah::GenelateWahWaveFile(const wchar_t* fileName, const wchar_t* afterFileName)
{
	// Wav��ǂݍ���
	lpWave.WaveRead(*pcm0_, fileName);

	// ���̃T�E�h�f�[�^���R�s�[
	

	lpWave.WaveWrite(*pcm2_, afterFileName);
	MessageBox(nullptr, L"�ϊ��������������܂���", L"�ϊ�����", 0);
}
