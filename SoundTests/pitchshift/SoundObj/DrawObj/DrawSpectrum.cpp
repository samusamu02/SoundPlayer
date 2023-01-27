#include <DxLib.h>
#include "DrawSpectrum.h"

DrawSpectrum::DrawSpectrum()
{
	// 初期化呼び出し
	Init();
}

DrawSpectrum::~DrawSpectrum()
{
}

void DrawSpectrum::Init(void)
{
	// 要素数の確定
	paramList_.resize(buffuerlength_);

	// スペクトル描画
	// 現在の再生位置から周波数分布を得る
	GetFFTVibrationSoftSound(softSoundHandle_, -1, samplePos_, fftsampleNam_, paramList_.data(), fftsampleNam_);
}

void DrawSpectrum::Draw(void)
{
	// 周波数分布を画面を描画する
	int x = -1;
	int j = 0;

	// 軸の間隔
	int offset = 15;
	// サンプル数分処理を行う
	for (int a = 0; a < fftsampleNam_; a++)
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
			Param = pow(paramList_[a], 0.5f) * 0.8f;

			// 振幅スペクトルの描画(右側にずらして描画）
			DrawBox(((SCREEN_W / 2) + 50) + j * offset, SCREEN_H - (int)(Param * SCREEN_H), ((SCREEN_W / 2) + 50) + j * offset + 4, SCREEN_H, 0x00ff00, true);
		}
	}
}
