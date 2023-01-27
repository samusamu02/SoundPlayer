#include "DrawObjMag.h"

DrawObjMag::DrawObjMag()
{
	Init();

	// �C���X�^���X
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
		// ���ׂĂ̏������֐����Ă�
		obj->Init();
	}
}

void DrawObjMag::Update(void)
{
	for (auto& obj : drawObj_)
	{
		// ���ׂĂ̍X�V�֐����Ă�
		obj->Update();
	}
}

void DrawObjMag::Draw(void)
{
	for (auto& obj : drawObj_)
	{
		// ���ׂĂ̕`��֐����Ă�
		obj->Draw();
	}
}
