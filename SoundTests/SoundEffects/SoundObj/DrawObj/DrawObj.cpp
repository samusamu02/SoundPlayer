#include "DrawObj.h"
#include "../../SoundData/SoundData.h"

DrawObj::DrawObj()
{
	Init();
}

DrawObj::~DrawObj()
{
}

void DrawObj::Init(void)
{
	// �T���v����
	sampleNum_ = 32768;
}