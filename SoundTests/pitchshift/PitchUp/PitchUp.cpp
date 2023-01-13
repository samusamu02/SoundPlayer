#include "PitchUp.h"
#include "../Wav/Wav.h"
#include "sinc.h"

// 円周率
double M_PI = 3.14159265358979323846264338327950288;

PitchUp::PitchUp()
{
	Init();

	pcm1_.sL = static_cast<double*>(calloc(pcm1_.length, sizeof(double)));		// 音データ
	pcm1_.sR = static_cast<double*>(calloc(pcm1_.length, sizeof(double)));		// 音データ


	channelL_.x = static_cast<double*>(calloc(template_size, sizeof(double)));
	channelL_.y = static_cast<double*>(calloc(template_size, sizeof(double)));
	channelL_.r = static_cast<double*>(calloc((channelL_.pmax + 1), sizeof(double)));

	channelR_.x = static_cast<double*>(calloc(template_size, sizeof(double)));
	channelR_.y = static_cast<double*>(calloc(template_size, sizeof(double)));
	channelR_.r = static_cast<double*>(calloc((channelR_.pmax + 1), sizeof(double)));

}

PitchUp::~PitchUp()
{
	delete pcm0_.sL;
	delete pcm0_.sR;
	delete pcm1_.sL;
	delete pcm1_.sR;
	delete pcm2_.sL;
	delete pcm2_.sR;
	delete channelL_.x;
	delete channelL_.y;
	delete channelL_.r;
	delete channelR_.x;
	delete channelR_.y;
	delete channelR_.r;

}

void PitchUp::Init()
{
	rate = 0.8;														// 音の高さを1.25倍にする

	pcm1_.fs = pcm0_.fs;											// 標本化周波数
	pcm1_.bits = pcm0_.bits;										// 量子化精度
	pcm1_.length = static_cast<int>(pcm0_.length / rate) + 1;		// 音のデータの長さ

	template_size = static_cast<int>(pcm1_.fs * 0.01);				// 相関関数のサイズ

	// 左右チャンネルで分ける
	channelL_.pmin = static_cast<int>(pcm1_.fs * 0.005);			// ピークの捜索範囲の下限
	channelL_.pmax = static_cast<int>(pcm1_.fs * 0.02);				// ピークの探索範囲の上限

	channelR_.pmin = static_cast<int>(pcm1_.fs * 0.005);			// ピークの捜索範囲の下限
	channelR_.pmax = static_cast<int>(pcm1_.fs * 0.02);				// ピークの探索範囲の上限

	channelL_.offset0 = 0;
	channelL_.offset1 = 0;

	channelR_.offset0 = 0;
	channelR_.offset1 = 0;
}

void PitchUp::GeneratePitchUpWaveFile(const wchar_t* fileName, const wchar_t* genarateFileName)
{
	lpWave.wave_read_16bit_stereo(pcm0_, fileName);

	// チェンネルL用の処理
	while (channelL_.offset0 + channelL_.pmax * 2 < pcm0_.length)
	{
		for (int n = 0; n < template_size; n++)
		{
			channelL_.x[n] = pcm0_.sL[channelL_.offset0 + n];		// 本来の音データ	
		}

		rmax = 0.0;
		channelL_.p = channelL_.pmin;
		for (int m = channelL_.pmin; m <= channelL_.pmax; m++)
		{
			for (int n = 0; n < template_size; n++)
			{
				channelL_.y[n] = pcm0_.sL[channelL_.offset0 + m + n];	// mサンプルずらした音データ
			}
			channelL_.r[m] = 0.0;
			for (int n = 0; n < template_size; n++)
			{
				channelL_.r[m] += channelL_.x[n] * channelL_.y[n];	// 相関関数
			}
			if (channelL_.r[m] > rmax)
			{
				rmax = channelL_.r[m];		// 相関関数のピーク
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
			pcm1_.sL[channelL_.offset1 + channelL_.p + n] += pcm0_.sL[channelL_.offset0 + n] * n / channelL_.p;									// 単調増加の重み付け
		}

		channelL_.q = (int)(channelL_.p / (1.0 - rate) + 0.5);
		for (int n = channelL_.p; n < channelL_.q; n++)
		{
			if (channelL_.offset0 + channelL_.p + n >= pcm0_.length)
			{
				break;
			}
			pcm1_.sL[channelL_.offset1 + channelL_.p + n] = pcm0_.sL[channelL_.offset0 + n];
		}

		channelL_.offset0 += channelL_.q;		// offset0の更新
		channelL_.offset1 += channelL_.p + channelL_.q;			// offset1の更新
	}

	// チャンネルR用の処理
	while (channelR_.offset0 + channelR_.pmax * 2 < pcm0_.length)
	{
		for (int n = 0; n < template_size; n++)
		{
			channelR_.x[n] = pcm0_.sR[channelR_.offset0 + n];		// 本来の音データ	
		}

		rmax = 0.0;
		channelR_.p = channelR_.pmin;
		for (int m = channelR_.pmin; m <= channelR_.pmax; m++)
		{
			for (int n = 0; n < template_size; n++)
			{
				channelR_.y[n] = pcm0_.sR[channelR_.offset0 + m + n];	// mサンプルずらした音データ
			}
			channelR_.r[m] = 0.0;
			for (int n = 0; n < template_size; n++)
			{
				channelR_.r[m] += channelR_.x[n] * channelR_.y[n];	// 相関関数
			}
			if (channelR_.r[m] > rmax)
			{
				rmax = channelR_.r[m];	// 相関関数のピーク
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
			pcm1_.sR[channelR_.offset1 + channelR_.p + n] += pcm0_.sR[channelR_.offset0 + n] * n / channelR_.p;			// 単調増加の重み付け
		}

		channelR_.q = (int)(channelR_.p / (1.0 - rate) + 0.5);
		for (int n = channelR_.p; n < channelR_.q; n++)
		{
			if (channelR_.offset0 + channelR_.p + n >= pcm0_.length)
			{
				break;
			}
			pcm1_.sR[channelR_.offset1 + channelR_.p + n] = pcm0_.sR[channelR_.offset0 + n];
		}

		channelR_.offset0 += channelR_.q;							// offset0の更新
		channelR_.offset1 += channelR_.p + channelR_.q;			// offset1の更新
	}

	pitch = 1.0 / rate;

	pcm2_.fs = pcm0_.fs;											// 標本化周波数
	pcm2_.bits = pcm0_.bits;										// 量子化精度
	pcm2_.length = pcm0_.length;									// 音データの長さ
	pcm2_.sL = (double*)calloc(pcm2_.length, sizeof(double));		// 音データ
	pcm2_.sR = (double*)calloc(pcm2_.length, sizeof(double));		// 音データ

	N = 128;		// ハニング窓のサイズ

	for (int n = 0; n < pcm2_.length; n++)
	{
		t = pitch * n;

		channelL_.ta = (int)t;

		if (t == channelL_.ta)
		{
			channelL_.tb = channelL_.ta;
		}
		else
		{
			channelL_.tb = channelL_.ta + 1;
		}

		for (int m = channelL_.tb - N / 2; m <= channelL_.ta + N / 2; m++)
		{
			if (m >= 0 && m < pcm1_.length)
			{
				pcm2_.sL[n] += pcm1_.sL[m] * sinc(M_PI * (t - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (t - m) / (N * 2 + 1)));
			}
		}
	}

	for (int n = 0; n < pcm2_.length; n++)
	{
		t = pitch * n;

		channelR_.ta = (int)t;

		if (t == channelR_.ta)
		{
			channelR_.tb = channelR_.ta;
		}
		else
		{
			channelR_.tb = channelR_.ta + 1;
		}

		for (int m = channelR_.tb - N / 2; m <= channelR_.ta + N / 2; m++)
		{
			if (m >= 0 && m < pcm1_.length)
			{
				pcm2_.sR[n] += pcm1_.sR[m] * sinc(M_PI * (t - m)) * (0.5 + 0.5 * cos(2.0 * M_PI * (t - m) / (N * 2 + 1)));
			}
		}
	}

	lpWave.wave_write_16bit_stereo(pcm2_, genarateFileName);
}

