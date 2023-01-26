#include <DxLib.h>
#include "DrawObj.h"

DrawObj::DrawObj()
{
	// Œ»İ‚ÌƒTƒ“ƒvƒ‹‚ÌˆÊ’u‚ğæ“¾
	samplePos_ = GetCurrentPositionSoundMem(soundHandle_);
}

DrawObj::~DrawObj()
{
}
