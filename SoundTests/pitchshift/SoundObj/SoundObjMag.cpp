#include "SoundObjMag.h"

SoundObjMag::SoundObjMag()
{
	drawObjMag_ = std::make_unique<DrawObjMag>();
}

SoundObjMag::~SoundObjMag()
{
}

void SoundObjMag::Init(void)
{
	drawObjMag_->Init();
}

void SoundObjMag::Update(void)
{
	drawObjMag_->Update();
}

void SoundObjMag::Draw(void)
{
	// 描画関係の描画関数呼び出し
	drawObjMag_->Draw();
}
