#include "SoundObjeMag.h"

SoundObjeMag::SoundObjeMag()
{
	Init();
}

SoundObjeMag::~SoundObjeMag()
{
}

void SoundObjeMag::Init()
{
	// �C���X�^���X
	drawObjmag_ = std::make_unique<DrawObjMag>();

	// �C�j�V�����C�Y�̌Ăяo��
	drawObjmag_->Init();
}

void SoundObjeMag::Upadate()
{
	drawObjmag_->Update();
}

void SoundObjeMag::Draw()
{
	drawObjmag_->Draw();
}
