#include <Windows.h>
#include "PitchDown.h"
#include "../sinc.h"
#include "../../Wave/Wave.h"

PitchDown::PitchDown()
{

}

PitchDown::~PitchDown()
{

}

void PitchDown::Init(void)
{
	template_size_ = static_cast<int>(pcm1_->fs * 0.001);

	// ピッチ変更の割合を求める
	pitch_ = 1.0 / rate_;

	// ハニング窓のサイズ
	N_ = 128;
}

void PitchDown::ChannelL_Init(void)
{
	// 左チャンネルの変数の初期化
	channelL_->pmin = static_cast<int>(pcm1_->fs * 0.005);
	channelL_->pmax = static_cast<int>(pcm1_->fs * 0.02);

	channelL_->x.resize(template_size_);
	channelL_->y.resize(template_size_);
	channelL_->r.resize(channelL_->pmax + 1.0);

	channelL_->offset0 = 0;
	channelL_->offset1 = 0;
}

void PitchDown::ChannelR_Init(void)
{
	// 右チャンネルの変数の初期化
	channelR_->pmin = static_cast<int>(pcm1_->fs * 0.005);
	channelR_->pmax = static_cast<int>(pcm1_->fs * 0.02);

	channelR_->x.resize(template_size_);
	channelR_->y.resize(template_size_);
	channelR_->r.resize(channelR_->pmax + 1.0);

	channelR_->offset0 = 0;
	channelR_->offset1 = 0;
}

void PitchDown::ChannelL_Timestretching(void)
{
	// チェンネルL用の音を伸ばす処理(タイムストレッチ)
	// 1サンプル毎に処理を行う
	while (channelL_->offset0 + channelL_->pmax * 2 < pcm0_->length)
	{
		for (int n = 0; n < template_size_; n++)
		{
			// 元の音データを格納する
			channelL_->x[n] = pcm0_->sL[channelL_->offset0 + n];
		}

		rmax_ = 0.0;

		// 相関関数のピークの位置
		int peakPos = channelL_->pmin;
		for (int m = channelL_->pmin; m <= channelL_->pmax; m++)
		{
			for (int n = 0; n < template_size_; n++)
			{
				// mサンプルずらした音データ
				channelL_->y[n] = pcm0_->sL[channelL_->offset0 + m + n];
			}
			channelL_->r[m] = 0.0;
			for (int n = 0; n < template_size_; n++)
			{
				// 相関関数
				channelL_->r[m] += channelL_->x[n] * channelL_->y[n];
			}
			if (channelL_->r[m] > rmax_)
			{
				// 相関関数のピーク
				rmax_ = channelL_->r[m];
				// 波形の周期
				peakPos = m;
			}
		}

		// 音を下げる処理
		for (int n = 0; n < peakPos; n++)
		{
			// 単調減少の重み付け
			pcm1_->sL[channelL_->offset1 + n] = pcm0_->sL[channelL_->offset0 + n] * (peakPos - n) / peakPos;
			// 単調増加の重み付け
			pcm1_->sL[channelL_->offset1 + n] += pcm0_->sL[channelL_->offset0 + peakPos + n] * n / peakPos;
		}

		channelL_->q = static_cast<int>(peakPos / (rate_ - 1.0) + 0.5);
		for (int n = peakPos; n < channelL_->q; n++)
		{
			if (channelL_->offset0 + peakPos + n >= pcm0_->length)
			{
				break;
			}
			pcm1_->sL[channelL_->offset1 + n] = pcm0_->sL[channelL_->offset0 + peakPos + n];
		}

		// オフセットの更新
		// 更新したら次のサンプルへ
		channelL_->offset0 += peakPos + channelL_->q;
		channelL_->offset1 += channelL_->q;
	}
}

void PitchDown::ChannelR_Timestretching(void)
{
	// チャンネルR用の音を伸ばす処理(タイムストレッチ)
	while (channelR_->offset0 + channelR_->pmax * 2 < pcm0_->length)
	{
		for (int n = 0; n < template_size_; n++)
		{
			// 元のデータを格納する
			channelR_->x[n] = pcm0_->sR[channelR_->offset0 + n];
		}

		rmax_ = 0.0;
		int peakPos = channelR_->pmin;
		for (int m = channelR_->pmin; m <= channelR_->pmax; m++)
		{
			for (int n = 0; n < template_size_; n++)
			{
				// mサンプルずらした音データ
				channelR_->y[n] = pcm0_->sR[channelR_->offset0 + m + n];
			}
			channelR_->r[m] = 0.0;
			for (int n = 0; n < template_size_; n++)
			{
				// 相関関数
				channelR_->r[m] += channelR_->x[n] * channelR_->y[n];
			}
			if (channelR_->r[m] > rmax_)
			{
				// 相関関数のピーク
				rmax_ = channelR_->r[m];
				// 波形の周期
				peakPos = m;
			}
		}

		// 音を下げる処理
		for (int n = 0; n < peakPos; n++)
		{
			// 単調減少の重み付け
			pcm1_->sR[channelR_->offset1 + n] = pcm0_->sR[channelR_->offset0 + n] * (peakPos - n) / peakPos;
			// 単調増加の重み付け
			pcm1_->sR[channelR_->offset1 + n] += pcm0_->sR[channelR_->offset0 + peakPos + n] * n / peakPos;
		}

		// 基準時刻の更新
		channelR_->q = static_cast<int>(peakPos / (rate_ - 1.0) + 0.5);
		for (int n = peakPos; n < channelR_->q; n++)
		{
			// 元の音データの長さと同じになったらループを抜ける
			if (channelR_->offset0 + peakPos + n >= pcm0_->length)
			{
				break;
			}
			// サンプルのコピー
			pcm1_->sR[channelR_->offset1 + n] = pcm0_->sR[channelR_->offset0 + peakPos + n];
		}

		// offset0の更新
		channelR_->offset0 += peakPos + channelR_->q;
		// offset1の更新
		channelR_->offset1 += channelR_->q;
	}
}

void PitchDown::ChannelL_Resampling(void)
{
	for (int n = 0; n < pcm2_->length; n++)
	{

		// ピッチの変更をすべてのサンプルに対して行う
		t_ = pitch_ * n;

		// 左チャンネルのピッチ変更
		channelL_->ta = static_cast<int>(t_);

		// 整数と小数点以下がある場合で分ける
		if (t_ == channelL_->ta)
		{
			// taの値を代入
			channelL_->tb = channelL_->ta;
		}
		else
		{
			// taの値+1を代入
			channelL_->tb = channelL_->ta + 1;
		}

		// すべてのサンプルに対して処理を行う
		for (int m = channelL_->tb - N_ / 2; m <= channelL_->ta + N_ / 2; m++)
		{
			if (m >= 0 && m < pcm1_->length)
			{
				// sinc関数を使ってフィルタをかける
				pcm2_->sL[n] += pcm1_->sL[m] * sinc(M_PI * (t_ - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (t_ - m) / (N_ * 2 + 1)));
			}
		}
	}
}

void PitchDown::ChannelR_Resampling(void)
{
	for (int n = 0; n < pcm2_->length; n++)
	{
		t_ = pitch_ * n;

		// 右チャンネルのピッチ変更（左チャンネルと同じ処理を行う）
		channelR_->ta = static_cast<int>(t_);

		if (t_ == channelR_->ta)
		{
			channelR_->tb = channelR_->ta;
		}
		else
		{
			channelR_->tb = channelR_->ta + 1;
		}

		for (int m = channelR_->tb - N_ / 2; m <= channelR_->ta + N_ / 2; m++)
		{
			if (m >= 0 && m < pcm1_->length)
			{
				// sinc関数を使ってフィルタをかける
				pcm2_->sR[n] += pcm1_->sR[m] * sinc(M_PI * (t_ - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (t_ - m) / (N_ * 2 + 1)));
			}
		}
	}
}

void PitchDown::GenelatePitchShiftWaveFile(const double rate, const wchar_t* fileName, const wchar_t* afterFileName)
{
	// Wavを読み込む
	lpWave.WaveRead(*pcm0_, fileName);

	// ピッチの倍率を代入
	rate_ = rate;

	// 元のPCMと変換後のPCMの値をセットする
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
