#include "DrawSpectrum.h"
#include "../../Scene/SceneMag.h"

DrawSpectrum::DrawSpectrum()
{
}

DrawSpectrum::~DrawSpectrum()
{
}

void DrawSpectrum::Init(void)
{
	// スクリーンサイズ
	screen_w_ = lpScenMag.GetScreen_W();	// 幅
	screen_h_ = lpScenMag.GetScreen_H();	// 広さ

	// サンプル数分要素数を確保する
	paramList.resize(sampleNum_);

	// FFTのサンプル数
	fftSampleNum_ = 4096;
}

void DrawSpectrum::Draw(void)
{
	// サウンドハンドルの取得
	auto softSoundHandle = lpSoundSet.GetSouftSoundHandle();

	// スペクトル描画
	// 現在の再生位置から周波数分布を得る
	// 現在のサウンドハンドルの取得
	auto soundHande = lpSoundSet.GetSoundHandle();
	// 現在の再生位置を取得
	auto samplePos = GetCurrentPositionSoundMem(soundHande);
	// FFTにより周波数分布を取得
	GetFFTVibrationSoftSound(softSoundHandle, -1, samplePos, fftSampleNum_, paramList.data(), fftSampleNum_);

	// 周波数分布を画面を描画する
	int x = -1;
	int j = 0;

	// 軸の間隔
	int offset = 15;
	// サンプル数分処理を行う
	for (int a = 0; a < fftSampleNum_; a++)
	{
		// 対数が同じでない場合のみ値を変える
		auto log = static_cast<int>((log10(static_cast<double>(a)) * 10));
		if (log != x)
		{
			// 描画位置
			j++;

			// 横軸に対してlogで対数をとる
			x = static_cast<int>((log10((double)a) * 10));

			// パラメーター
			float Param;

			// 関数から取得できる値を描画に適した値に調整
			Param = pow(paramList[a], 0.5f) * 0.8f;

			// 振幅スペクトルの描画(右側にずらして描画）
			DrawBox(((screen_w_ / 2) + 50) + j * offset, screen_h_ - (int)(Param * screen_h_), ((screen_w_ / 2) + 50) + j * offset + 4, screen_h_, 0x00ff00, true);
		}
	}
}
