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

	// サウンドハンドルの取得
	auto soundHandle = lpSoundSet.GetSoundHandle();

	if (soundHandle > 0)
	{
		// サウンドがあればシーンへ移動する
		return std::make_unique<GenelateEffectScene>();
	}
	else
	{
		// サウンドがない場合
		DrawFormatString(10, 10, 0xffffff, L"サウンドファイルが存在しません");
	}

	return ownScene;
}

void SoundSelectScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
}
