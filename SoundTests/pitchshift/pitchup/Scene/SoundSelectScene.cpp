#include <DxLib.h>
#include "SoundSelectScene.h"
#include "SoundPlayScene.h"
#include "GenelateEffectScene.h"
#include "../SoundData/SoundData.h"

SoundSelectScene::SoundSelectScene()
{
	Init();
	DrawOwnScreen();
}

SoundSelectScene::~SoundSelectScene()
{
}

void SoundSelectScene::Init(void)
{
	lpSoundSet.SoundDataInit(L"Sound/Peak_test_A.wav");
}

uniqueBase SoundSelectScene::Update(uniqueBase ownScene)
{
	DrawOwnScreen();

	auto soundHandle = lpSoundSet.GetSoundHandle();

	if (soundHandle > 0)
	{
		return std::make_unique<GenelateEffectScene>();
	}

	return ownScene;
}

void SoundSelectScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
}
