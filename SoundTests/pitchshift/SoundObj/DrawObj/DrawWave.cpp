#include "DrawWave.h"
#include "../../Scene/SceneMag.h"
DrawWave::DrawWave()
{
}

DrawWave::~DrawWave()
{
}

void DrawWave::Init(void)
{

}

void DrawWave::Update(void)
{
	// スクリーンサイズの取得
	auto screen_w = lpScenMag.GetSCREEN_W();

	// 現在の再生位置を取得
	auto soundHande = lpSoundSet.GetSoundHandle();
	auto samplePos = GetCurrentPositionSoundMem(soundHande);

	// 取得した再生位置をサンプリングレートで割ってスクロール
	auto drawStartSampleCount = lpSoundSet.GetDrawStartSampleCount();
	drawStartSampleCount += samplePos / 44.1;

	
	// 描画範囲（端まで)
	if (drawStartSampleCount + screen_w > samplePos)
	{
		drawStartSampleCount = samplePos;
	}

	// 終了チェック
	if (loopCount_ == 0)
	{
		// 曲の終わりを見る
		auto totalSampleCount = lpSoundSet.GetTotalSampleCount();
		if (samplePos == totalSampleCount)
		{
			lpSoundSet.SoundInit(soundFile_.beforeFileName, false);
			PlaySoundMem(soundHande, DX_PLAYTYPE_BACK);
			loopCount_ = 1;
		}
	}
}

void DrawWave::Draw(void)
{
	// スクリーンサイズの取得
	auto screen_w = lpScenMag.GetSCREEN_W();
	auto screen_h = lpScenMag.GetSCREEN_H();

	auto softSoundHandle = lpSoundSet.GetSouftSoundHandle();

	// 右チャンネル、左チャンネル
	int Ch1, Ch2;
	// 波形を描画
	// 1サンプルずつ処理を行う
	auto drawStartSampleCount = lpSoundSet.GetDrawStartSampleCount();
	auto totalSampleCount = lpSoundSet.GetTotalSampleCount();
	for (long long i = 0; i < screen_w / 2 && i + drawStartSampleCount < totalSampleCount; i++)
	{
		// 波形の振幅値を取得
		ReadSoftSoundData(softSoundHandle, i + drawStartSampleCount, &Ch1, &Ch2);

		// 振幅値の高さの縦ラインを描画
		DrawLine(i, screen_h / 4, i, screen_h / 4 + (Ch1 * (screen_h / 4) / sampleNum_), GetColor(0, 0, 255));
		DrawLine(i, screen_h - screen_h / 4, i, screen_h - screen_h / 4 + (Ch2 * (screen_h / 4) / sampleNum_), GetColor(0, 0, 255));
	}
}
