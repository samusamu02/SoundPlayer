#include "PitchUp.h"
#include "../Wave/Wave.h"

#include "sinc.h"

PitchUp::PitchUp(double rate)
{
	rate_ = rate;	// 音の高さの変更

	pcmSet_ = std::make_unique<PCMSet>();
}

PitchUp::~PitchUp()
{
	// メモリ解放
	free(pcm0_.sL);
	free(pcm0_.sR);
	free(pcm1_.sL);
	free(pcm1_.sR);
	free(pcm2_.sL);
	free(pcm2_.sR);

	// std::vectorの解放
	channelL_.x.clear();
	channelL_.y.clear();
	channelL_.r.clear();
	channelR_.x.clear();
	channelR_.y.clear();
	channelR_.r.clear();
}

void PitchUp::GenelatePitchUpWaveFile(const wchar_t* fileName,const wchar_t* afterFileName)
{
	lpWave.WaveRead(pcm0_, fileName);

	pcmSet_->PCMSetPitchUp(pcm1_, pcm0_,rate_);

	// 相関関数のサイズ
	template_size_ = (int)(pcm1_.fs * 0.001);			// 標本化周波数の1000分の1のサイズ

	// 左右チャンネルで分ける
	// 左チャンネル
	channelL_.pmin = (int)(pcm1_.fs * 0.005);			// ピークの捜索範囲の下限(L)
	channelL_.pmax = (int)(pcm1_.fs * 0.02);			// ピークの探索範囲の上限(L)

	// メモリ確保(L)
	channelL_.x.resize(template_size_);		// 相関関数分のメモリサイズの確保
	channelL_.y.resize(template_size_);		// 相関関数分のメモリサイズの確保
	channelL_.r.resize(channelL_.pmax + 1);

	// 右チャンネル
	channelR_.pmin = (int)(pcm1_.fs * 0.005);		// ピークの捜索範囲の下限(R)
	channelR_.pmax = (int)(pcm1_.fs * 0.02);		// ピークの探索範囲の上限(R)

	// メモリ確保(R)
	channelR_.x.resize(template_size_);		// 相関関数分のメモリサイズの確保
	channelR_.y.resize(template_size_);		// 相関関数分のメモリサイズの確保
	channelR_.r.resize(channelR_.pmax + 1);

	channelL_.offset0 = 0;
	channelL_.offset1 = 0;

	channelR_.offset0 = 0;
	channelR_.offset1 = 0;

	// チェンネルL用の音を伸ばす処理(タイムストレッチ)
	while (channelL_.offset0 + channelL_.pmax * 2 < pcm0_.length)
	{
		for (int n = 0; n < template_size_; n++)
		{
			channelL_.x[n] = pcm0_.sL[channelL_.offset0 + n];			// 本来の音データ	
		}

		rmax_ = 0.0;
		channelL_.p = channelL_.pmin;
		for (int m = channelL_.pmin; m <= channelL_.pmax; m++)
		{
			for (int n = 0; n < template_size_; n++)
			{
				channelL_.y[n] = pcm0_.sL[channelL_.offset0 + m + n];	// mサンプルずらした音データ
			}
			channelL_.r[m] = 0.0;
			for (int n = 0; n < template_size_; n++)
			{
				channelL_.r[m] += channelL_.x[n] * channelL_.y[n];	// 相関関数
			}
			if (channelL_.r[m] > rmax_)
			{
				rmax_ = channelL_.r[m];	// 相関関数のピーク
				channelL_.p = m;			// 波形の周期
			}
		}

		for (int n = 0; n < channelL_.p; n++)
		{
			pcm1_.sL[channelL_.offset1 + n] = pcm0_.sL[channelL_.offset0 + n];
		}
		for (int n = 0; n < channelL_.p; n++)
		{
			pcm1_.sL[channelL_.offset1 + channelL_.p + n] = pcm0_.sL[channelL_.offset0 + channelL_.p + n] * (channelL_.p - n) / channelL_.p;	// 単調減少の重み付け
			pcm1_.sL[channelL_.offset1 + channelL_.p + n] += pcm0_.sL[channelL_.offset0 + n] * n / channelL_.p;								// 単調増加の重み付け
		}

		channelL_.q = (int)(channelL_.p * rate_ / (1.0 - rate_) + 0.5);
		for (int n = channelL_.p; n < channelL_.q; n++)
		{
			if (channelL_.offset0 + n >= pcm0_.length)
			{
				break;
			}
			pcm1_.sL[channelL_.offset1 + channelL_.p + n] = pcm0_.sL[channelL_.offset0 + n];
		}

		channelL_.offset0 += channelL_.q;						// offset0の更新
		channelL_.offset1 += channelL_.p + channelL_.q;			// offset1の更新
	}

	// チャンネルR用の音を伸ばす処理(タイムストレッチ)
	while (channelR_.offset0 + channelR_.pmax * 2 < pcm0_.length)
	{
		for (int n = 0; n < template_size_; n++)
		{
			channelR_.x[n] = pcm0_.sR[channelR_.offset0 + n];		// 本来の音データ	
		}

		rmax_ = 0.0;
		channelR_.p = channelR_.pmin;
		for (int m = channelR_.pmin; m <= channelR_.pmax; m++)
		{
			for (int n = 0; n < template_size_; n++)
			{
				channelR_.y[n] = pcm0_.sR[channelR_.offset0 + m + n];	// mサンプルずらした音データ
			}
			channelR_.r[m] = 0.0;
			for (int n = 0; n < template_size_; n++)
			{
				channelR_.r[m] += channelR_.x[n] * channelR_.y[n];	// 相関関数
			}
			if (channelR_.r[m] > rmax_)
			{
				rmax_ = channelR_.r[m];		// 相関関数のピーク
				channelR_.p = m;			// 波形の周期
			}
		}

		for (int n = 0; n < channelR_.p; n++)
		{
			pcm1_.sR[channelR_.offset1 + n] = pcm0_.sR[channelR_.offset0 + n];
		}
		for (int n = 0; n < channelR_.p; n++)
		{
			pcm1_.sR[channelR_.offset1 + channelR_.p + n] = pcm0_.sR[channelR_.offset0 + channelR_.p + n] * (channelR_.p - n) / channelR_.p;	// 単調減少の重み付け
			pcm1_.sR[channelR_.offset1 + channelR_.p + n] += pcm0_.sR[channelR_.offset0 + n] * n / channelR_.p;									// 単調増加の重み付け
		}

		channelR_.q = (int)(channelR_.p * rate_/ (1.0 - rate_) + 0.5);
		for (int n = channelR_.p; n < channelR_.q; n++)
		{
			if (channelR_.offset0 + n >= pcm0_.length)
			{
				break;
			}
			pcm1_.sR[channelR_.offset1 + channelR_.p + n] = pcm0_.sR[channelR_.offset0 + n];
		}

		channelR_.offset0 += channelR_.q;							// offset0の更新
		channelR_.offset1 += channelR_.p + channelR_.q;				// offset1の更新
	}

	// 両チャンネルのタイムストレッチが完了したらピッチの変更を行う
	pitch_ = 1.0 / rate_;


	pcmSet_->PCMSetNormal(pcm2_, pcm0_);

	// シンク関数を打ち切るため
	N_ = 64;		// ハニング窓のサイズ

	// 実際にピッチシフトを行う(L)
	for (int n = 0; n < pcm2_.length; n++)
	{
		// ピッチの変更を曲の長さ分行う
		t_ = pitch_ * n;

		// 
		channelL_.ta = (int)t_;

		if (t_ == channelL_.ta)
		{
			channelL_.tb = channelL_.ta;
		}
		else
		{
			channelL_.tb = channelL_.ta + 1;
		}

		for (int m = channelL_.tb - N_ / 2; m <= channelL_.ta + N_ / 2; m++)
		{
			if (m >= 0 && m < pcm1_.length)
			{
				// sinc関数を使ってリサンプリグによって音の高さを変える
				pcm2_.sL[n] += pcm1_.sL[m] * sinc(M_PI * (t_ - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (t_ - m) / (N_ * 2 + 1)));
			}
		}
	}

	// 実際にピッチシフトを行う(R)
	for (int n = 0; n < pcm2_.length; n++)
	{
		t_ = pitch_ * n;

		channelR_.ta = (int)t_;

		if (t_ == channelR_.ta)
		{
			channelR_.tb = channelR_.ta;
		}
		else
		{
			channelR_.tb = channelR_.ta + 1;
		}

		for (int m = channelR_.tb - N_ / 2; m <= channelR_.ta + N_ / 2; m++)
		{
			if (m >= 0 && m < pcm1_.length)
			{
				// sinc関数を使ってフィルタをかける
				pcm2_.sR[n] += pcm1_.sR[m] * sinc(M_PI * (t_ - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (t_ - m) / (N_ * 2 + 1)));
			}
		}
	}

	lpWave.WaveWrite(pcm2_,afterFileName);
}
