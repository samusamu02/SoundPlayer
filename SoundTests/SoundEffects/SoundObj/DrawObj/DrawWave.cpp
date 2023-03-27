#include "DrawWave.h"
#include "../../SceneMag.h"
DrawWave::DrawWave()
{
	// warning対策
	drawStartSampleCount_ = 0;
	totalSampleCount_ = 0;
	screen_h_ = 0;
	screen_w_ = 0;
}

DrawWave::~DrawWave()
{
}

void DrawWave::Init(void)
{
	// 初期化
	screen_w_ = lpScenMag.GetScreen_W();	// 幅
	screen_h_ = lpScenMag.GetScreen_H();	// 高さ

	// 総サンプル数の取得
	totalSampleCount_ = lpSoundSet.GetTotalSampleCount();

	// 現在のサンプル数の初期化
	drawStartSampleCount_ = 0;
}

void DrawWave::Update(void)
{
	// 現在のサウンドハンドルの取得
	auto soundHande = lpSoundSet.GetSoundHandle();

	// 現在のサンプルの位置
	auto samplePos = GetCurrentPositionSoundMem(soundHande);

	// 取得した再生位置をサンプリングレートで割ってスクロール
	drawStartSampleCount_ = lpSoundSet.GetDrawStartSampleCount();
	drawStartSampleCount_ += samplePos;

	// 描画範囲（端まで)
	if (drawStartSampleCount_ + screen_w_ > samplePos)
	{
		drawStartSampleCount_ = samplePos;
	}
}

void DrawWave::Draw(void)
{
	// 現在のソフトサウンドハンドルの取得
	auto softSoundHandle = lpSoundSet.GetSouftSoundHandle();

	// 右チャンネル、左チャンネル
	int Ch1, Ch2;
	// 波形を描画
	// 1サンプルずつ処理を行う
	for (LONGLONG i = 0; i < screen_w_ / 2 && i + drawStartSampleCount_ < totalSampleCount_; i++)
	{
		// 波形の振幅値を取得
		ReadSoftSoundData(softSoundHandle, i + drawStartSampleCount_, &Ch1, &Ch2);

		// 振幅値の高さの縦ラインを描画
		DrawLine(static_cast<int>(i), screen_h_ / 4, static_cast<int>(i), screen_h_ / 4 + (Ch1 * (screen_h_ / 4) / sampleNum_),0x0000ff);
		DrawLine(static_cast<int>(i), screen_h_ - screen_h_ / 4, static_cast<int>(i), screen_h_ - screen_h_ / 4 + (Ch2 * (screen_h_ / 4) / sampleNum_), 0x0000ff);
	}
}
