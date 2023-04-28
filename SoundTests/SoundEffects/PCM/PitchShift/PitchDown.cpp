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
	channelL_->search_min_ = static_cast<int>(pcm1_->fs * 0.005);
	channelL_->search_max_ = static_cast<int>(pcm1_->fs * 0.02);

	channelL_->soundData_.resize(correlationSize_);
	channelL_->shiftData_.resize(correlationSize_);
	channelL_->correlation_.resize(channelL_->search_max_ + 1.0);

	channelL_->in_pos_ = 0;
	channelL_->out_pos_ = 0;
}

void PitchDown::ChannelR_Init(void)
{
	// 右チャンネルの変数の初期化
	channelR_->search_min_ = static_cast<int>(pcm1_->fs * 0.005);
	channelR_->search_max_ = static_cast<int>(pcm1_->fs * 0.02);

	channelR_->soundData_.resize(correlationSize_);
	channelR_->shiftData_.resize(correlationSize_);
	channelR_->correlation_.resize(channelR_->search_max_ + 1.0);

	channelR_->in_pos_ = 0;
	channelR_->out_pos_ = 0;
}

void PitchDown::ChannelL_Timestretching(void)
{
	// 左チャンネルのタイムストレッチ処理
	while (channelL_->in_pos_ + channelL_->search_max_ * 2 < pcm0_->length)
	{
		for (int n = 0; n < correlationSize_; n++)
		{
			// 元の音データのコピー
			channelL_->soundData_[n] = pcm0_->sL[channelL_->in_pos_ + n];
		}

		// 相関関数の範囲の初期化
		peak_ = 0.0;
		double p = channelL_->search_min_;

		for (int m = static_cast<int>(channelL_->search_min_); m <= static_cast<int>(channelL_->search_max_); m++)
		{
			for (int n = 0; n < correlationSize_; n++)
			{
				// mサンプルずらした音データ
				channelL_->shiftData_[n] = pcm0_->sL[channelL_->in_pos_ + m + n];
			}

			// 相関関数の計算
			channelL_->correlation_[m] = 0.0;
			for (int n = 0; n < correlationSize_; n++)
			{
				channelL_->correlation_[m] += channelL_->soundData_[n] * channelL_->shiftData_[n];
			}
			if (channelL_->correlation_[m] > peak_)
			{
				// 相関関数のピーク
				peak_ = channelL_->correlation_[m];

				// 波形の周期
				p = m;
			}
		}

		// 重み付けを行い、タイムストレッチ後のpcmを生成
		for (int n = 0; n < p; n++)
		{
			// 単調減少の重み付け
			pcm1_->sL[channelL_->out_pos_ + n] = pcm0_->sL[channelL_->in_pos_ + n] * (p - n) / p;
			// 単調増加の重み付け
			pcm1_->sL[channelL_->out_pos_ + n] += pcm0_->sL[channelL_->in_pos_ + p + n] * n / p;
		}

		// 重み付けの範囲を超えた部分は等間隔でサンプリング
		int q = static_cast<int>(p / (rate_ - 1.0) + 0.5);
		for (int n = p; n < q; n++)
		{
			if (channelL_->in_pos_ + p + n >= pcm0_->length)
			{
				break;
			}
			pcm1_->sL[channelL_->out_pos_ + n] = pcm0_->sL[channelL_->in_pos_ + p + n];
		}

		// posの更新
		channelL_->in_pos_ += p + q;
		channelL_->out_pos_ += q;
	}
}

void PitchDown::ChannelR_Timestretching(void)
{
	// 右チャンネルのタイムストレッチ処理（以下同様の処理の為のコメント省略）
	while (channelR_->in_pos_ + channelR_->search_max_ * 2 < pcm0_->length)
	{
		for (int n = 0; n < correlationSize_; n++)
		{
			channelR_->soundData_[n] = pcm0_->sR[channelR_->in_pos_ + n];
		}

		peak_ = 0.0;
		int p = channelR_->search_min_;

		for (int m = channelR_->search_min_; m <= channelR_->search_max_; m++)
		{
			for (int n = 0; n < correlationSize_; n++)
			{
				channelR_->shiftData_[n] = pcm0_->sR[channelR_->in_pos_ + m + n];
			}
			channelR_->correlation_[m] = 0.0;
			for (int n = 0; n < correlationSize_; n++)
			{
				channelR_->correlation_[m] += channelR_->soundData_[n] * channelR_->shiftData_[n];
			}
			if (channelR_->correlation_[m] > peak_)
			{
				peak_ = channelR_->correlation_[m];

				p = m;
			}
		}

		for (int n = 0; n < p; n++)
		{
			pcm1_->sR[channelR_->out_pos_ + n] = pcm0_->sR[channelR_->in_pos_ + n] * (p - n) / p;
			pcm1_->sR[channelR_->out_pos_ + n] += pcm0_->sR[channelR_->in_pos_ + p + n] * n / p;
		}

		int q = static_cast<int>(p / (rate_ - 1.0) + 0.5);
		for (int n = p; n < q; n++)
		{
			if (channelR_->in_pos_ + p + n >= pcm0_->length)
			{
				break;
			}
			pcm1_->sR[channelR_->out_pos_ + n] = pcm0_->sR[channelR_->in_pos_ + p + n];
		}

		channelR_->in_pos_ += p + q;
		channelR_->out_pos_ += q;
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
		channelL_->currentIndex_ = static_cast<int>(timeIndex_);

		// 整数と浮動小数で分ける
		if (timeIndex_ == channelL_->currentIndex_)
		{
			channelL_->nextIndex_ = channelL_->currentIndex_;
		}
		else
		{
			// 浮動小数の場合は+1をする
			channelL_->nextIndex_ = channelL_->currentIndex_ + 1;
		}

		// 窓関数とsinc関数を用いて新しくpcmデータを計算する
		for (int m = channelL_->nextIndex_ - hanningSize_ / 2; m <= channelL_->currentIndex_ + hanningSize_ / 2; m++)
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
	// 右チャンネルと同じ処理を行う(以下同様の処理の為のコメント省略)
	for (int n = 0; n < pcm2_->length; n++)
	{
		timeIndex_ = pitch_ * n;

		channelR_->currentIndex_ = static_cast<int>(timeIndex_);

		if (timeIndex_ == channelR_->currentIndex_)
		{
			channelR_->nextIndex_ = channelR_->currentIndex_;
		}
		else
		{
			channelR_->nextIndex_ = channelR_->currentIndex_ + 1;
		}

		for (int m = channelR_->nextIndex_ - hanningSize_ / 2; m <= channelR_->currentIndex_ + hanningSize_ / 2; m++)
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

	// 元のPCMとエフェクトを適用するPCMの値をセットする
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

	// wavファイルの出力
	lpWave.WaveWrite(*pcm2_, afterFileName);
}
