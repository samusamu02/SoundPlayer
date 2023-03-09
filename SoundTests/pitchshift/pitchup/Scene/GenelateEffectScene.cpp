#include <DxLib.h>
#include "GenelateEffectScene.h"

GenelateEffectScene::GenelateEffectScene()
{
	pitchUp_ = std::make_unique<PitchUp>();
	Init();
	DrawOwnScreen();
}

GenelateEffectScene::~GenelateEffectScene()
{
}

void GenelateEffectScene::Init(void)
{

}

uniqueBase GenelateEffectScene::Update(uniqueBase ownScene)
{
	DrawOwnScreen();

	return ownScene;
}

void GenelateEffectScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
}
