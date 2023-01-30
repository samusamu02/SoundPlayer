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
	// サンプル数分要素数を確保する
	paramList.resize(sampleNum_);

	// FFTのサンプル数
	fftSampleNum_ = 4096;
}

void DrawSpectrum::Update(void)
{
}

void DrawSpectrum::Draw(void)
{
	// スクリーンサイズ
	auto screen_w = lpScenMag.GetSCREEN_W();	// 幅
	auto screen_h = lpScenMag.GetSCREEN_H();	// 広さ

	// スペクトル描画
	// 現在の再生位置から周波数分布を得る
	GetFFTVibrationSoftSound(softSoundHandle_, -1, samplePos_, fftSampleNum_, paramList.data(), fftSampleNum_);

	// 周波数分布を画面を描画する
	int x = -1;
	int j = 0;

	// 軸の間隔
	int offset = 15;
	// サンプル数分処理を行う
	for (int a = 0; a < fftSampleNum_; a++)
	{
		// 対数が同じでない場合のみ値を変える
		auto log = (int)(log10((double)a) * 10);
		if (log != x)
		{
			// 描画位置
			j++;

			// 横軸に対してlogで対数をとる
			x = (int)(log10((double)a) * 10);

			// パラメーター
			float Param;

			// 関数から取得できる値を描画に適した値に調整
			Param = pow(paramList[a], 0.5f) * 0.8f;

			// 振幅スペクトルの描画(右側にずらして描画）
			DrawBox(((screen_w / 2) + 50) + j * offset, screen_h - (int)(Param * screen_h), ((screen_w / 2) + 50) + j * offset + 4, screen_h, 0x00ff00, true);
		}
	}
}
