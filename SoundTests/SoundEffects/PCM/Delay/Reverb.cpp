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
	// 繰り返し回数
	repeat_ = 10;
}

void Reverb::ChannelL_Init(void)
{
	// リバーブ用の変数の初期化
	channelL_->attenuation_ = 0.5;
	channelL_->delay_ = pcm1_->fs * 0.05;
}

void Reverb::ChannelR_Init(void)
{
	// リバーブ用の変数の初期化
	channelR_->attenuation_ = 0.5;
	channelR_->delay_ = pcm1_->fs * 0.05;
}

void Reverb::GenelateReverbWaveFile(const wchar_t* fileName, const wchar_t* afterFileName)
{
	// wavファイルの読み込み
	lpWave.WaveRead(*pcm0_, fileName);

	// 元のPCMとエフェクトを適用するPCMの値をセットする
	pcmSet_->PCMSetNormal(*pcm1_, *pcm0_);

	// 初期化処理
	Init();

	// 左チャンネルの初期化
	ChannelL_Init();

	// 右チャンネルの初期化
	ChannelR_Init();

	// 左チャンネルのワウ処理
	ChannelL_Delay();

	// 右チャンネルのワウ処理
	ChannelR_Delay();

	// wavファイルの出力
	lpWave.WaveWrite(*pcm1_, afterFileName);
}
