#include <DxLib.h>
#include "DrawObj.h"

DrawObj::DrawObj()
{
	// 現在のサンプルの位置を取得
	samplePos_ = GetCurrentPositionSoundMem(soundHandle_);
}

DrawObj::~DrawObj()
{
}
