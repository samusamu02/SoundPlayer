#include "DrawObjMag.h"
DrawObjMag::DrawObjMag()
{
	drawBG_ = std::make_unique<DrawBG>();
}

DrawObjMag::~DrawObjMag()
{
}

void DrawObjMag::Init(void)
{

}

void DrawObjMag::Update(void)
{
}

void DrawObjMag::Draw(void)
{
	// ”wŒi‚Ì•`‰æ
	drawBG_->Draw();
}
