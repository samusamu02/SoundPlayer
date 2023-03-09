#include "DrawObjMag.h"
DrawObjMag::DrawObjMag()
{
	// �C���X�^���X
	drawBG_ = std::make_shared<DrawBG>();
	drawWave_ = std::make_shared<DrawWave>();
	drawSpectrum_ = std::make_shared<DrawSpectrum>();
}

DrawObjMag::~DrawObjMag()
{
	// �����Ȃ�
}

void DrawObjMag::Init(void)
{
	// �w�i�̏������֐��Ăяo��
	drawBG_->Init();

	// �g�`�̏������֐��̌Ăяo��
	drawWave_->Init();

	// �X�y�N�g���̏������֐��̌Ăяo��
	drawSpectrum_->Init();
}

void DrawObjMag::Update(void)
{
	drawWave_->Update();
}

void DrawObjMag::Draw(void)
{
	// �w�i�̕`��֐��̌Ăяo��
	drawBG_->Draw();

	// �g�`�̕`��֐��̌Ăяo��
	drawWave_->Draw();

	// �X�y�N�g���̕`��֐��Ăяo��
	drawSpectrum_->Draw();
}
