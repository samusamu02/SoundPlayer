#include <DxLib.h>
#include "DrawObj.h"

DrawObj::DrawObj()
{
	// ���݂̃T���v���̈ʒu���擾
	samplePos_ = GetCurrentPositionSoundMem(soundHandle_);
}

DrawObj::~DrawObj()
{
}
