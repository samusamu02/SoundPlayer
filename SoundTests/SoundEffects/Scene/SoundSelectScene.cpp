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
	// サウンドの初期化
	lpSoundSet.SoundDataInit(soundFile_.beforeFileName);
}

uniqueBase SoundSelectScene::Update(uniqueBase ownScene)
{
	// 先に描画を行う
	DrawOwnScreen();

	//
	auto soundHandle = lpSoundSet.GetSoundHandle();

	if (soundHandle > 0)
	{
		return std::make_unique<GenelateEffectScene>();
	}
	else
	{

	}

	return ownScene;
}

void SoundSelectScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
}
