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
		// �I�u�W�F�N�g����
		obj = std::unique_ptr<DrawObj>();

		// ���ׂĂ̏������֐����Ă�
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
