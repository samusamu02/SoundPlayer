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
	// インスタンス
	drawObjmag_ = std::make_unique<DrawObjMag>();

	// イニシャライズの呼び出し
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
