#include "PitchUp.h"
#include "../Wave/Wave.h"

#include "sinc.h"
#include <Windows.h>

PitchUp::PitchUp(double rate)
{
	rate_ = rate;	// 音の高さの変更

	// インスタンス
	pcm0_ = std::make_unique<STEREO_PCM>();
	pcm1_ = std::make_unique<STEREO_PCM>();
	pcm2_ = std::make_unique<STEREO_PCM>();
	channelL_ = std::make_unique<ChannelL>();
	channelR_ = std::make_unique<ChannelR>();
	pcmSet_ = std::make_unique<PCMSet>();
}

PitchUp::~PitchUp()
{
	// スマートポインタで管理しているので解放の処理は書く必要なし
}

void PitchUp::GenelatePitchUpWaveFile(const wchar_t* fileName,const wchar_t* afterFileName)
{
	// Wavを読み込む
	lpWave.WaveRead(*pcm0_, fileName);

	// 元のPCMと変換後のPCMの値をセットする
	pcmSet_->PCMSetPitchUp(*pcm1_, *pcm0_,rate_);

	// 相関関数のサイズ
	template_size_ = static_cast<int>(pcm1_->fs * 0.001);			// 標本化周波数の1000分の1のサイズ

	// 左右チャンネルで分ける
	// 左チャンネル
	channelL_->pmin = static_cast<int>(pcm1_->fs * 0.005);			// ピークの捜索範囲の下限(L)
	channelL_->pmax = static_cast<int>(pcm1_->fs * 0.02);			// ピークの探索範囲の上限(L)

	// メモリ確保(L)
	channelL_->x.resize(template_size_);				// 相関関数分のメモリサイズの確保
	channelL_->y.resize(template_size_);				// 相関関数分のメモリサイズの確保
	channelL_->r.resize(channelL_->pmax + 1);			// ピークの探索範囲の上限分のメモリ確保

	// 右チャンネル
	channelR_->pmin = static_cast<int>(pcm1_->fs * 0.005);			// ピークの捜索範囲の下限(R)
	channelR_->pmax = static_cast<int>(pcm1_->fs * 0.02);			// ピークの探索範囲の上限(R)

	// メモリ確保(R)
	channelR_->x.resize(template_size_);				// 相関関数分のメモリサイズの確保
	channelR_->y.resize(template_size_);				// 相関関数分のメモリサイズの確保
	channelR_->r.resize(channelR_->pmax + 1);			// ピークの探索範囲の上限分のメモリ確保

	// オフセットの初期化
	channelL_->offset0 = 0;
	channelL_->offset1 = 0;

	channelR_->offset0 = 0;
	channelR_->offset1 = 0;

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
		channelL_->p = channelL_->pmin;
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
				channelL_->p = m;										
			}
		}

		for (int n = 0; n < channelL_->p; n++)
		{
			pcm1_->sL[channelL_->offset1 + n] = pcm0_->sL[channelL_->offset0 + n];

			// 単調減少の重み付け
			pcm1_->sL[channelL_->offset1 + channelL_->p + n] = pcm0_->sL[channelL_->offset0 + channelL_->p + n] * (channelL_->p - n) / channelL_->p;
			// 単調増加の重み付け
			pcm1_->sL[channelL_->offset1 + channelL_->p + n] += pcm0_->sL[channelL_->offset0 + n] * n / channelL_->p;
		}

		channelL_->q = static_cast<int>(channelL_->p * rate_ / (1.0 - rate_) + 0.5);
		for (int n = channelL_->p; n < channelL_->q; n++)
		{
			if (channelL_->offset0 + n >= pcm0_->length)
			{
				break;
			}
			pcm1_->sL[channelL_->offset1 + channelL_->p + n] = pcm0_->sL[channelL_->offset0 + n];
		}

		// オフセットの更新
		// 更新したら次のサンプルへ
		channelL_->offset0 += channelL_->q;				
		channelL_->offset1 += channelL_->p + channelL_->q;			
	}

	// チャンネルR用の音を伸ばす処理(タイムストレッチ)
	while (channelR_->offset0 + channelR_->pmax * 2 < pcm0_->length)
	{
		for (int n = 0; n < template_size_; n++)
		{
			// 元のデータを格納する
			channelR_->x[n] = pcm0_->sR[channelR_->offset0 + n];		
		}

		rmax_ = 0.0;
		channelR_->p = channelR_->pmin;
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
				channelR_->p = m;				
			}
		}

		for (int n = 0; n < channelR_->p; n++)
		{
			// offset0とnサンプル数を格納
			pcm1_->sR[channelR_->offset1 + n] = pcm0_->sR[channelR_->offset0 + n];

			// 単調減少の重み付け
			pcm1_->sR[channelR_->offset1 + channelR_->p + n] = pcm0_->sR[channelR_->offset0 + channelR_->p + n] * (channelR_->p - n) / channelR_->p;
			// 単調増加の重み付け
			pcm1_->sR[channelR_->offset1 + channelR_->p + n] += pcm0_->sR[channelR_->offset0 + n] * n / channelR_->p;
		}

		// 基準時刻の更新
		channelR_->q = static_cast<int>(channelR_->p * rate_/ (1.0 - rate_) + 0.5);
		for (int n = channelR_->p; n < channelR_->q; n++)
		{
			// 元の音データの長さと同じになったらループを抜ける
			if (channelR_->offset0 + n >= pcm0_->length)
			{
				break;
			}
			// サンプルのコピー
			pcm1_->sR[channelR_->offset1 + channelR_->p + n] = pcm0_->sR[channelR_->offset0 + n];
		}

		// offset0の更新
		channelR_->offset0 += channelR_->q;						
		// offset1の更新
		channelR_->offset1 += channelR_->p + channelR_->q;				
	}

	// ピッチ変更の割合を求める
	pitch_ = 1.0 / rate_;

	// タイムストレッチが完了したら出力ようのPCMにデータをセット
	pcmSet_->PCMSetNormal(*pcm2_, *pcm0_);

	// シンク関数を打ち切るためにハニング窓を使用する
	// ハニング窓のサイズ
	N_ = 128;	

	// 実際にピッチシフトを行う
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

	lpWave.WaveWrite(*pcm2_,afterFileName);
	MessageBox(nullptr, L"変換完了が完了しました", L"変換完了", 0);
}
