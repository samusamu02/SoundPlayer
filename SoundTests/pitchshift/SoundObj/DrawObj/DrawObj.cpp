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
	// ���݂̍Đ��ʒu���擾
	samplePos_ = GetCurrentPositionSoundMem(soundHandle_);

	// �T���v����
	sampleNum_ = 32768;
}
