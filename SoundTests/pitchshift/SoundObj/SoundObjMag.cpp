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
	// •`‰æŠÖŒW‚Ì•`‰æŠÖ”ŒÄ‚Ño‚µ
	drawObjMag_->Draw();
}
