#pragma once
#include <memory>
#include "../Wav/PCM.h"

// ステレオでは左右に分かれているので片方ずつに処理でき量に構造体で分ける
// 左チャンネル用の構造体
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

// 右チャンネル用の構造体
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
	// 初期化
	void Init();

	// 音データ
	STEREO_PCM pcm0_;
	STEREO_PCM pcm1_;
	STEREO_PCM pcm2_;

	// 左右チャンネル
	ChannelL channelL_;
	ChannelR channelR_;

	int template_size;
	int N;

	double rate;
	double rmax;
	double t;
	double pitch;

};

