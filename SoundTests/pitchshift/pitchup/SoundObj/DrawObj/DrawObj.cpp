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
	// サンプル数
	sampleNum_ = 32768;
}