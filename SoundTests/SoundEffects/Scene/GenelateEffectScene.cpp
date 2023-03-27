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

}

uniqueBase GenelateEffectScene::Update(uniqueBase ownScene)
{
	DrawOwnScreen();

	std::thread th_1([&] {pitchDown_->GenelatePitchShiftFile(1.2, soundFile_.beforeFileName, soundFile_.afterFilenName); });
	th_1.join();

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
}
