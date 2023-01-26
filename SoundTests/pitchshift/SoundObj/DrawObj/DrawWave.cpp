#include <DxLib.h>
#include "DrawWave.h"

DrawWave::DrawWave()
{
	Init();
}

DrawWave::~DrawWave()
{

}

void DrawWave::Init()
{
	totalSampleCount_ = GetSoftSoundSampleNum(softSoundHandle_);
}

void DrawWave::DrawSoundWave()
{
	// 右チャンネル、左チャンネル
	int Ch1, Ch2;
	// 波形を描画
	// 1サンプルずつ処理を行う
	for (LONGLONG i = 0; i < SCREEN_W / 2 && i + DrawStartSampleCount < TotalSampleCount; i++)
	{
		// 波形の振幅値を取得
		ReadSoftSoundData(SoftSoundHandle, i + DrawStartSampleCount, &Ch1, &Ch2);

		// 振幅値の高さの縦ラインを描画
		DrawLine(i, SCREEN_H / 4, i, SCREEN_H / 4 + (Ch1 * (SCREEN_H / 4) / sampleNum), GetColor(0, 0, 255));
		DrawLine(i, SCREEN_H - SCREEN_H / 4, i, SCREEN_H - SCREEN_H / 4 + (Ch2 * (SCREEN_H / 4) / sampleNum), GetColor(0, 0, 255));
	}
}
