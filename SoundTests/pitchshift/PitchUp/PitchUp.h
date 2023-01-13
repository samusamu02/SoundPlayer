#pragma once
#include <memory>
#include "../Wav/PCM.h"

// �X�e���I�ł͍��E�ɕ�����Ă���̂ŕЕ����ɏ����ł��ʂɍ\���̂ŕ�����
// ���`�����l���p�̍\����
struct ChannelL
{
	int pmin;
	int pmax;
	int p;
	int q;
	int offset0;
	int offset1;
	int ta;
	int tb;

	double* x;
	double* y;
	double* r;
};

// �E�`�����l���p�̍\����
struct ChannelR
{
	int pmin;
	int pmax;
	int p;
	int q;
	int offset0;
	int offset1;
	int ta;
	int tb;

	double* x;
	double* y;
	double* r;
};
class PitchUp
{
public:
	PitchUp();
	~PitchUp();

	void GeneratePitchUpWaveFile(const wchar_t* fileName, const wchar_t* genarateFileName);

private:
	// ������
	void Init();

	// ���f�[�^
	STEREO_PCM pcm0_;
	STEREO_PCM pcm1_;
	STEREO_PCM pcm2_;

	// ���E�`�����l��
	ChannelL channelL_;
	ChannelR channelR_;

	int template_size;
	int N;

	double rate;
	double rmax;
	double t;
	double pitch;

};

