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

	// 取得した再生位置をサンプリングレートで割ってスクロール
	drawStartSampleCount_ += samplePos_ / 44.1;

	// 描画範囲（端まで)
	if (drawStartSampleCount_ + screen_w > samplePos_)
	{
		drawStartSampleCount_ = samplePos_;
	}
}

void DrawWave::Draw(void)
{
	// スクリーンサイズの取得
	auto screen_w = lpScenMag.GetSCREEN_W();
	auto screen_h = lpScenMag.GetSCREEN_H();

	// 右チャンネル、左チャンネル
	int Ch1, Ch2;
	// 波形を描画
	// 1サンプルずつ処理を行う
	for (long long i = 0; i < screen_w / 2 && i + drawStartSampleCount_ < totalSampleCount_; i++)
	{
		// 波形の振幅値を取得
		ReadSoftSoundData(softSoundHandle_, i + drawStartSampleCount_, &Ch1, &Ch2);

		// 振幅値の高さの縦ラインを描画
		DrawLine(i, screen_h / 4, i, screen_h / 4 + (Ch1 * (screen_h / 4) / sampleNum_), GetColor(0, 0, 255));
		DrawLine(i, screen_h - screen_h / 4, i, screen_h - screen_h / 4 + (Ch2 * (screen_h / 4) / sampleNum_), GetColor(0, 0, 255));
	}
}
