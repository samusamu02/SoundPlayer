#include "Wah.h"
#include "../../Wave/Wave.h"
#include "../../common/iir_filter.h"

Wah::Wah()
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

Wah::~Wah()
{
	// 処理なし
}

void Wah::Init(void)
{
	// 変数初期化
	delaylineNum_ = 2;

	depth_ = 800.0;
	rate_ = 1.0;
}

void Wah::ChannelL_Wah(void)
{
	// ワウ
	for (int n = 0; n < pcm1_->length; n++)
	{
		// 中心周波数
		channelL_->fc = (1000.0 + depth_ * sin(2.0 * M_PI * rate_ * n / pcm1_->fs)) / pcm1_->fs;

		// クオリティファクタ
		channelL_->q_ = 2.0;

		// IIRフィルタの設計
		IIR_resonator(channelL_->fc, channelL_->q_, channelL_->attenuation.data(), channelL_->delay.data());

		// フィルタ処理
		for (int m = 0; m <= delaylineNum_; m++)
		{
			if (n - m >= 0)
			{
				pcm1_->sL[n] += channelL_->delay[m] * pcm0_->sL[n - m];
			}
		}
		for (int m = 1; m <= delaylineNum_; m++)
		{
			if (n - m >= 0)
			{
				pcm1_->sL[n] += -channelL_->attenuation[m] * pcm1_->sL[n - m];
			}
		}

	}
}

void Wah::ChannelR_Wah(void)
{
	// 左チャンネルと同じ処理を行う(以下同様の処理の為のコメント省略)
	for (int n = 0; n < pcm1_->length; n++)
	{
		channelR_->fc = (1000.0 + depth_ * sin(2.0 * M_PI * rate_ * n / pcm1_->fs)) / pcm1_->fs;

		channelR_->q_ = 2.0;

		IIR_resonator(channelR_->fc, channelR_->q_, channelR_->attenuation.data(), channelR_->delay.data());

		for (int m = 0; m <= delaylineNum_; m++)
		{
			if (n - m >= 0)
			{
				pcm1_->sR[n] += channelR_->delay[m] * pcm0_->sR[n - m];
			}
		}
		for (int m = 1; m <= delaylineNum_; m++)
		{
			if (n - m >= 0)
			{
				pcm1_->sR[n] += -channelR_->attenuation[m] * pcm1_->sR[n - m];
			}
		}

	}
}

void Wah::GenelateWahWaveFile(const wchar_t* fileName, const wchar_t* afterFileName)
{
	// wavファイルの読み込み
	lpWave.WaveRead(*pcm0_, fileName);

	// 元のPCMとエフェクトを適用するPCMの値をセットする
	pcmSet_->PCMSetNormal(*pcm1_, *pcm0_);

	// 初期化処理
	Init();

	// 左チャンネルのワウ処理
	ChannelL_Wah();

	// 右チャンネルのワウ処理
	ChannelR_Wah();

	// wavファイルの出力
	lpWave.WaveWrite(*pcm1_, afterFileName);
}
