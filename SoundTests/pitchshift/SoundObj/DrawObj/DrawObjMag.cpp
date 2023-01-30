#include "DrawObjMag.h"
DrawObjMag::DrawObjMag()
{
	// インスタンス
	drawBG_ = std::make_unique<DrawBG>();
	drawWave_ = std::make_unique<DrawWave>();
	drawSpectrum_ = std::make_unique<DrawSpectrum>();
}

DrawObjMag::~DrawObjMag()
{
	// 処理なし
}

void DrawObjMag::Init(void)
{
	// 背景の初期化関数呼び出し
	drawBG_->Init();

	// 波形の初期化関数の呼び出し
	drawWave_->Init();

	// スペクトルの初期化関数の呼び出し
	drawSpectrum_->Init();
}

void DrawObjMag::Update(void)
{
	// 背景の更新関数の呼び出し
	drawBG_->Update();

	// 波形の更新関数の呼び出し
	drawWave_->Update();
}

void DrawObjMag::Draw(void)
{
	// 背景の描画関数の呼び出し
	drawBG_->Draw();

	// 波形の描画関数の呼び出し
	drawWave_->Draw();

	// スペクトルの描画関数呼び出し
	drawSpectrum_->Draw();
}
