#include "DrawObjMag.h"

DrawObjMag::DrawObjMag()
{
	Init();

	// インスタンス
	drawObj_.push_back(std::make_unique<DrawObj>());
	drawObj_.push_back(std::make_unique<DrawBG>());
	drawObj_.push_back(std::make_unique<DrawWave>());
	drawObj_.push_back(std::make_unique<DrawSpectrum>());
}

DrawObjMag::~DrawObjMag()
{
}

void DrawObjMag::Init(void)
{
	for (auto& obj : drawObj_)
	{
		// すべての初期化関数を呼ぶ
		obj->Init();
	}
}

void DrawObjMag::Update(void)
{
	for (auto& obj : drawObj_)
	{
		// すべての更新関数を呼ぶ
		obj->Update();
	}
}

void DrawObjMag::Draw(void)
{
	for (auto& obj : drawObj_)
	{
		// すべての描画関数を呼ぶ
		obj->Draw();
	}
}
