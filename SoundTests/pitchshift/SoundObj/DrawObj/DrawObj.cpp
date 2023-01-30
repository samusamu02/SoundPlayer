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
	// Œ»İ‚ÌÄ¶ˆÊ’u‚ğæ“¾
	samplePos_ = GetCurrentPositionSoundMem(soundHandle_);

	// ƒTƒ“ƒvƒ‹”
	sampleNum_ = 32768;
}
