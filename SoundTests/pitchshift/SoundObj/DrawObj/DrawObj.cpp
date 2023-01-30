#include "DrawObj.h"

DrawObj::DrawObj()
{
	Init();
}

DrawObj::~DrawObj()
{
}

void DrawObj::Init(void)
{
	// 現在の再生位置を取得
	samplePos_ = GetCurrentPositionSoundMem(soundHandle_);

	// サンプル数
	sampleNum_ = 32768;
}
