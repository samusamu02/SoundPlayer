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
	// 変数の初期化
	correlationSize_ = static_cast<int>(pcm1_->fs * 0.001);
	pitch_ = 1.0 / rate_;
	hanningSize_ = 128;
}

void PitchDown::ChannelL_Init(void)
{
	// 左チャンネルの変数の初期化
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
	// 右チャンネルの変数の初期化
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
			// 元の音データのコピー
			channelL_->soundData[n] = pcm0_->sL[channelL_->in_pos + n];
		}

		// 相関関数の範囲の初期化
		peak_ = 0.0;
		double p = channelL_->search_min;

		for (int m = channelL_->search_min; m <= channelL_->search_max; m++)
		{
			for (int n = 0; n < correlationSize_; n++)
			{
				// mサンプルずらした音データ
				channelL_->shiftData[n] = pcm0_->sL[channelL_->in_pos + m + n];
			}

			// 相関関数の計算
			channelL_->correlation[m] = 0.0;
			for (int n = 0; n < correlationSize_; n++)
			{
				channelL_->correlation[m] += channelL_->soundData[n] * channelL_->shiftData[n];
			}
			if (channelL_->correlation[m] > peak_)
			{
				// 相関関数のピーク
				peak_ = channelL_->correlation[m];

				// 波形の周期
				p = m;
			}
		}

		// 重み付けを行い、タイムストレッチ後のpcmを生成
		for (int n = 0; n < p; n++)
		{
			// 単調減少の重み付け
			pcm1_->sL[channelL_->out_pos + n] = pcm0_->sL[channelL_->in_pos + n] * (p - n) / p;
			// 単調増加の重み付け
			pcm1_->sL[channelL_->out_pos + n] += pcm0_->sL[channelL_->in_pos + p + n] * n / p;
		}

		// 重み付けの範囲を超えた部分は等間隔でサンプリング
		int q = static_cast<int>(p / (rate_ - 1.0) + 0.5);
		for (int n = p; n < q; n++)
		{
			if (channelL_->in_pos + p + n >= pcm0_->length)
			{
				break;
			}
			pcm1_->sL[channelL_->out_pos + n] = pcm0_->sL[channelL_->in_pos + p + n];
		}

		// posの更新
		channelL_->in_pos += p + q;
		channelL_->out_pos += q;
	}
}

void PitchDown::ChannelR_Timestretching(void)
{
	// 左チャンネルと同じ処理を行う(以下同様の処理の為のコメント省略)
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
	// ピッチ変更を行う
	for (int n = 0; n < pcm2_->length; n++)
	{
		// 現在のインデックスにピッチを掛けた値を代入
		timeIndex_ = pitch_ * n;

		// データのコピー
		channelL_->currentIndex = static_cast<int>(timeIndex_);

		// 整数と浮動小数で分ける
		if (timeIndex_ == channelL_->currentIndex)
		{
			channelL_->nextIndex = channelL_->currentIndex;
		}
		else
		{
			// 浮動小数の場合は+1をする
			channelL_->nextIndex = channelL_->currentIndex + 1;
		}

		// 窓関数とsinc関数を用いて新しくpcmデータを計算する
		for (int m = channelL_->nextIndex - hanningSize_ / 2; m <= channelL_->currentIndex + hanningSize_ / 2; m++)
		{
			if (m >= 0 && m < pcm1_->length)
			{
				// sinc関数を使ってフィルタをかける
				pcm2_->sL[n] += pcm1_->sL[m] * sinc(M_PI * (timeIndex_ - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (timeIndex_ - m) / (hanningSize_ * 2 + 1)));
			}
		}
	}
}

void PitchDown::ChannelR_Resampling(void)
{
	// 左チャンネルと同じ処理を行う(以下同様の処理の為のコメント省略)
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
	// Wavを読み込む
	lpWave.WaveRead(*pcm0_, fileName);

	// タイムストレッチの伸縮率を代入
	rate_ = rate;

	// 	// 元のPCMとエフェクトを適用するPCMの値をセットする
	pcmSet_->PCMSetPitchShift(*pcm1_, *pcm0_, rate_);

	// 変数初期化
	Init();

	// 左チャンネルの変数初期化
	ChannelL_Init();

	// 右チャンネルの変数初期化
	ChannelR_Init();

	// 左チャンネルのタイムストレッチ
	ChannelL_Timestretching();

	// 右チャンネルのタイムストレッチ
	ChannelR_Timestretching();

	// 両チャンネルのタイムストレッチが完了したら出力用のPCMにデータをセット
	pcmSet_->PCMSetNormal(*pcm2_, *pcm0_);

	// 左チャンネルのリサンプリング
	ChannelL_Resampling();

	// 右チャンネルのリサンプリング
	ChannelR_Resampling();

	// 書き込み
	lpWave.WaveWrite(*pcm2_, afterFileName);
}
