#include "DrawObjMag.h"

DrawObjMag::DrawObjMag()
{
	Init();
}

DrawObjMag::~DrawObjMag()
{
}

void DrawObjMag::Init(void)
{

	for (auto& obj : drawObj_)
	{
		// オブジェクト生成
		obj = std::unique_ptr<DrawObj>();

		// すべての初期化関数を呼ぶ
		obj->Init();
	}
}

void DrawObjMag::Update(void)
{
	for (auto& obj : drawObj_)
	{
		obj->Update();
	}
}

void DrawObjMag::Draw(void)
{
	for (auto& obj : drawObj_)
	{
		obj->Draw();
	}
}
