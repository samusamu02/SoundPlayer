#include "Equalizer.h"
#include "../../Wave/Wave.h"
#include "../../common/iir_filter.h"

Equalizer::Equalizer()
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

Equalizer::~Equalizer()
{
}

void Equalizer::Init(void)
{
	// 遅延器の数
	delaylineNum_ = 2;
}

void Equalizer::ChannelL_Init(void)
{
	// 遮断周波数
	channelL_->fc = 10.0 / pcm0_->fs;

	// クオリティファクタ
	channelL_->Q = 1.0 / sqrt(2.0);

	channelL_->g = -1.0;

	// IIRフィルタの設計
	IIR_low_shelving(channelL_->fc, channelL_->Q, channelL_->g, channelL_->a.data(), channelL_->b.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->A[0][m] = channelL_->a[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->B[0][m] = channelL_->b[m];
	}

	// 中心周波数
	channelL_->fc = 50.0 / pcm0_->fs;

	// クオリティファクタ
	channelL_->Q = 1.0 / sqrt(2.0);

	channelL_->g = 1.0;

	// IIRフィルタの設計
	IIR_peaking(channelL_->fc, channelL_->Q, channelL_->g, channelL_->a.data(), channelL_->b.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->A[1][m] = channelL_->a[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->B[1][m] = channelL_->b[m];
	}

	// 遮断周波数
	channelL_->fc = 100.0 / pcm0_->fs;

	// クオリティファクタ
	channelL_->Q = 1.0 / sqrt(2.0);

	channelL_->g = -1.0;

	// IIRフィルタの設計
	IIR_high_shelving(channelL_->fc, channelL_->Q, channelL_->g, channelL_->a.data(), channelL_->b.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->A[2][m] = channelL_->a[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->B[2][m] = channelL_->b[m];
	}
}

void Equalizer::ChannelR_Init(void)
{
	// 遮断周波数
	channelR_->fc = 10.0 / pcm0_->fs;

	// クオリティファクタ
	channelR_->Q = 1.0 / sqrt(2.0);

	channelR_->g = -1.0;

	// IIRフィルタの設計
	IIR_low_shelving(channelR_->fc, channelR_->Q, channelR_->g, channelR_->a.data(), channelR_->b.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->A[0][m] = channelR_->a[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->B[0][m] = channelR_->b[m];
	}

	// 中心周波数
	channelR_->fc = 50.0 / pcm0_->fs;

	// クオリティファクタ
	channelR_->Q = 1.0 / sqrt(2.0);

	channelR_->g = 1.0;

	// IIRフィルタの設計
	IIR_peaking(channelR_->fc, channelR_->Q, channelR_->g, channelR_->a.data(), channelR_->b.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->A[1][m] = channelR_->a[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->B[1][m] = channelR_->b[m];
	}

	// 遮断周波数
	channelR_->fc = 100.0 / pcm0_->fs;

	// クオリティファクタ
	channelR_->Q = 1.0 / sqrt(2.0);

	channelR_->g = -1.0;

	// IIRフィルタの設計
	IIR_high_shelving(channelR_->fc, channelR_->Q, channelR_->g, channelR_->a.data(), channelR_->b.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->A[2][m] = channelR_->a[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->B[2][m] = channelR_->b[m];
	}
}

void Equalizer::ChannelL_Equalizer(void)
{
	// イコライザ（3帯域)
	for (int i = 0; i < 3; i++)
	{
		for (int n = 0; n < pcm1_->length; n++)
		{
			pcm1_->sL[n] = 0.0;
		}

		for (int n = 0; n < pcm1_->length; n++)
		{
			for (int m = 0; m <= delaylineNum_; m++)
			{
				if (n - m >= 0)
				{
					pcm1_->sL[n] += channelL_->B[i][m] * pcm0_->sL[n - m];
				}
			}
			for (int m = 1; m <= delaylineNum_; m++)
			{
				if (n - m >= 0)
				{
					pcm1_->sL[n] += -channelL_->A[i][m] * pcm1_->sL[n - m];
				}
			}
		}

		for (int n = 0; n < pcm1_->length; n++)
		{
			pcm0_->sL[n] = pcm1_->sL[n];
		}
	}
}

void Equalizer::ChannelR_Equalizer(void)
{
	// イコライザ（3帯域)
	for (int i = 0; i < 3; i++)
	{
		for (int n = 0; n < pcm1_->length; n++)
		{
			pcm1_->sR[n] = 0.0;
		}

		for (int n = 0; n < pcm1_->length; n++)
		{
			for (int m = 0; m <= delaylineNum_; m++)
			{
				if (n - m >= 0)
				{
					pcm1_->sR[n] += channelR_->B[i][m] * pcm0_->sR[n - m];
				}
			}
			for (int m = 1; m <= delaylineNum_; m++)
			{
				if (n - m >= 0)
				{
					pcm1_->sR[n] += -channelR_->A[i][m] * pcm1_->sR[n - m];
				}
			}
		}

		for (int n = 0; n < pcm1_->length; n++)
		{
			pcm0_->sR[n] = pcm1_->sR[n];
		}
	}
}

void Equalizer::GenelateEquaLizerWaveFile(const wchar_t* fileName, const wchar_t* afterFileName)
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
	ChannelL_Equalizer();

	// 右チャンネルのワウ処理
	ChannelR_Equalizer();

	// wavファイルの出力
	lpWave.WaveWrite(*pcm1_, afterFileName);
}
