#include <DxLib.h>
#include <thread>
#include "GenelateEffectScene.h"
#include "SoundPlayScene.h"

GenelateEffectScene::GenelateEffectScene()
{
	pitchDown_ = std::make_unique<PitchDown>();
	Init();
	DrawOwnScreen();
}

GenelateEffectScene::~GenelateEffectScene()
{
}

void GenelateEffectScene::Init(void)
{
	// 処理なし
}

uniqueBase GenelateEffectScene::Update(uniqueBase ownScene)
{
	DrawOwnScreen();

	// 別スレッド
	std::thread th_1([&] {pitchDown_->GenelatePitchShiftWaveFile(1.2, soundFile_.beforeFileName, soundFile_.afterFilenName); });
	th_1.join();

	// スレッドの処理が完了したら次のシーンへ
	if (th_1.joinable() == false)
	{
		return std::make_unique<SoundPlayScene>();
	}

	return ownScene;
}

void GenelateEffectScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawFormatString(10, 0, 0xffffff, L"エフェクトにサウンドを適用中です");
}
