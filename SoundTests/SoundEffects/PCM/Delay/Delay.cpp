#include "Delay.h"
#include "../../Wave/Wave.h"

Delay::Delay()
{
	// PCMの初期化のオブジェクト
	pcmSet_ = std::make_unique<PCMSet>();

	// pcmのオブジェクト
	pcm0_ = std::make_unique<STEREO_PCM>();
	pcm1_ = std::make_unique<STEREO_PCM>();

	// 左右チャンネルのオブジェクト
	channelL_ = std::make_unique<ChannelL>();
	channelR_ = std::make_unique<ChannelR>();
}

Delay::~Delay()
{
}

void Delay::Init(void)
{
	// 繰り返し回数
	repeat_ = 2;
}

void Delay::ChannelL_Init(void)
{
	// 減衰率
	channelL_->attenuation_ = 0.5;

	// 遅延時間
	channelL_->delay_ = pcm1_->fs * 0.375;
}

void Delay::ChannelR_Init(void)
{
	// 減衰率
	channelR_->attenuation_ = 0.5;

	// 遅延時間
	channelR_->delay_ = pcm1_->fs * 0.375;
}

void Delay::ChannelL_Delay(void)
{
	// 左チャンネルのディレイ処理
	for (int n = 0; n < pcm1_->length; n++)
	{
		// 現在の時刻の音データ
		pcm1_->sL[n] = pcm0_->sL[n];

		for (int i = 1;i <= repeat_; i++)
		{
			int m = static_cast<int>(static_cast<double>(n) - static_cast<double>(i) * channelL_->delay_);

			if (m >= 0)
			{
				// 過去の音データをミックスする
				pcm1_->sL[n] += pow(channelL_->attenuation_, static_cast<double>(i)) * pcm0_->sL[m];
			}
		}
	}
}

void Delay::ChannelR_Delay(void)
{
	// 右チャンネルのディレイ処理
	for (int n = 0; n < pcm1_->length; n++)
	{
		// 現在の時刻の音データ
		pcm1_->sR[n] = pcm0_->sR[n];

		for (int i = 1; i <= repeat_; i++)
		{
			int m = static_cast<int>(static_cast<double>(n) - static_cast<double>(i) * channelR_->delay_);

			if (m >= 0)
			{
				// 過去の音データをミックスする
				pcm1_->sR[n] += pow(channelR_->attenuation_, static_cast<double>(i)) * pcm0_->sR[m];
			}
		}
	}
}

void Delay::GenelateDelayWaveFile(const wchar_t* fileName, const wchar_t* afterFileName)
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
