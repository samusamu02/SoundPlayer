#include <DxLib.h>
#include "DrawWave.h"

// スクリーンの大きさ
constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;

DrawWave::DrawWave()
{
	// 初期化呼び出し
	Init();
}

DrawWave::~DrawWave()
{
	
}

void DrawWave::Init()
{
	// サンプル数の取得
	totalSampleCount_ = GetSoftSoundSampleNum(softSoundHandle_);
}

void DrawWave::DrawSoundWave()
{
	// 右チャンネル、左チャンネル
	int Ch1, Ch2;

	// 波形を描画
	// 1サンプルずつ処理を行う
	for (LONGLONG i = 0; i < SCREEN_W / 2 && i + drawStartSampleCount_ < totalSampleCount_; i++)
	{
		// 波形の振幅値を取得
		ReadSoftSoundData(softSoundHandle_, i + drawStartSampleCount_, &Ch1, &Ch2);

		// 振幅値の高さの縦ラインを描画
		DrawLine(i, SCREEN_H / 4, i, SCREEN_H / 4 + (Ch1 * (SCREEN_H / 4) / sampleNum_), GetColor(0, 0, 255));
		DrawLine(i, SCREEN_H - SCREEN_H / 4, i, SCREEN_H - SCREEN_H / 4 + (Ch2 * (SCREEN_H / 4) / sampleNum_), GetColor(0, 0, 255));
	}
}
