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

void Equalizer::ChannelL_IIR(void)
{
	// 遮断周波数
	channelL_->cf_ = 10.0 / pcm0_->fs;

	// クオリティファクタ
	channelL_->q_Factor_ = 1.0 / sqrt(2.0);
	channelL_->gain_ = -1.0;

	// IIRフィルタの設計
	IIR_low_shelving(channelL_->cf_, channelL_->q_Factor_, channelL_->gain_, channelL_->coefficients_a_.data(), channelL_->coefficients_b_.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->coefficients_A_[0][m] = channelL_->coefficients_a_[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->coefficients_B_[0][m] = channelL_->coefficients_b_[m];
	}

	// 中心周波数
	channelL_->cf_ = 50.0 / pcm0_->fs;

	// クオリティファクタ
	channelL_->q_Factor_ = 1.0 / sqrt(2.0);
	channelL_->gain_ = 1.0;

	// IIRフィルタの設計
	IIR_peaking(channelL_->cf_, channelL_->q_Factor_, channelL_->gain_, channelL_->coefficients_a_.data(), channelL_->coefficients_b_.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->coefficients_A_[1][m] = channelL_->coefficients_a_[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->coefficients_B_[1][m] = channelL_->coefficients_b_[m];
	}

	// 遮断周波数
	channelL_->cf_ = 100.0 / pcm0_->fs;

	// クオリティファクタ
	channelL_->q_Factor_ = 1.0 / sqrt(2.0);
	channelL_->gain_ = -1.0;

	// IIRフィルタの設計
	IIR_high_shelving(channelL_->cf_, channelL_->q_Factor_, channelL_->gain_, channelL_->coefficients_a_.data(), channelL_->coefficients_b_.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->coefficients_A_[2][m] = channelL_->coefficients_a_[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelL_->coefficients_B_[2][m] = channelL_->coefficients_b_[m];
	}
}

void Equalizer::ChannelR_IIR(void)
{
	// 遮断周波数
	channelR_->cf_ = 10.0 / pcm0_->fs;

	// クオリティファクタ
	channelR_->q_Factor_ = 1.0 / sqrt(2.0);
	channelR_->gain_ = -1.0;

	// IIRフィルタの設計
	IIR_low_shelving(channelR_->cf_, channelR_->q_Factor_, channelR_->gain_, channelR_->coefficients_a_.data(), channelR_->coefficients_b_.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->coefficients_A_[0][m] = channelR_->coefficients_a_[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->coefficients_B_[0][m] = channelR_->coefficients_b_[m];
	}

	// 中心周波数
	channelR_->cf_ = 50.0 / pcm0_->fs;

	// クオリティファクタ
	channelR_->q_Factor_ = 1.0 / sqrt(2.0);
	channelR_->gain_ = 1.0;

	// IIRフィルタの設計
	IIR_peaking(channelR_->cf_, channelR_->q_Factor_, channelR_->gain_, channelR_->coefficients_a_.data(), channelR_->coefficients_b_.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->coefficients_A_[1][m] = channelR_->coefficients_a_[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->coefficients_B_[1][m] = channelR_->coefficients_b_[m];
	}

	// 遮断周波数
	channelR_->cf_ = 100.0 / pcm0_->fs;

	// クオリティファクタ
	channelR_->q_Factor_ = 1.0 / sqrt(2.0);
	channelR_->gain_ = -1.0;

	// IIRフィルタの設計
	IIR_high_shelving(channelR_->cf_, channelR_->q_Factor_, channelR_->gain_, channelR_->coefficients_a_.data(), channelR_->coefficients_b_.data());
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->coefficients_A_[2][m] = channelR_->coefficients_a_[m];
	}
	for (int m = 0; m <= delaylineNum_; m++)
	{
		channelR_->coefficients_B_[2][m] = channelR_->coefficients_b_[m];
	}
}

void Equalizer::ChannelL_Equalizer(void)
{
	// 左チャンネルのイコライザ処理
	for (int i = 0; i < 3; i++)
	{
		for (int n = 0; n < pcm1_->length; n++)
		{
			// 出力信号バッファの値を0にリセット
			pcm1_->sL[n] = 0.0;
		}

		for (int n = 0; n < pcm1_->length; n++)
		{

			// FIRフィルタリング
			for (int m = 0; m <= delaylineNum_; m++)
			{
				if (n - m >= 0)
				{
					pcm1_->sL[n] += channelL_->coefficients_B_[i][m] * pcm0_->sL[n - m];
				}
			}

			// IIRフィルタリング
			for (int m = 1; m <= delaylineNum_; m++)
			{
				if (n - m >= 0)
				{
					pcm1_->sL[n] += -channelL_->coefficients_A_[i][m] * pcm1_->sL[n - m];
				}
			}
		}

		// データのコピー
		for (int n = 0; n < pcm1_->length; n++)
		{
			pcm0_->sL[n] = pcm1_->sL[n];
		}
	}
}

void Equalizer::ChannelR_Equalizer(void)
{
	//右チャンネルのイコライザ処理(以下同じ処理のたコメント省略）
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
					pcm1_->sR[n] += channelR_->coefficients_B_[i][m] * pcm0_->sR[n - m];
				}
			}
			for (int m = 1; m <= delaylineNum_; m++)
			{
				if (n - m >= 0)
				{
					pcm1_->sR[n] += -channelR_->coefficients_A_[i][m] * pcm1_->sR[n - m];
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
	ChannelL_IIR();

	// 右チャンネルの初期化
	ChannelR_IIR();

	// 左チャンネルのワウ処理
	ChannelL_Equalizer();

	// 右チャンネルのワウ処理
	ChannelR_Equalizer();

	// wavファイルの出力
	lpWave.WaveWrite(*pcm1_, afterFileName);
}
