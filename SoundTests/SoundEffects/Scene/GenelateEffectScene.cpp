#include <DxLib.h>
#include <thread>
#include "GenelateEffectScene.h"
#include "SoundPlayScene.h"

GenelateEffectScene::GenelateEffectScene()
{
	Init();
	DrawOwnScreen();
}

GenelateEffectScene::~GenelateEffectScene()
{
}

void GenelateEffectScene::Init(void)
{
	pitchUp_ = std::make_unique<PitchUp>();
	pitchDown_ = std::make_unique<PitchDown>();
	wah_ = std::make_unique<Wah>();
	delay_ = std::make_unique<Delay>();
	reverb_ = std::make_unique<Reverb>();
	equalizer_ = std::make_unique<Equalizer>();
}

uniqueBase GenelateEffectScene::Update(uniqueBase ownScene)
{
	DrawOwnScreen();

	// 別スレッドとして処理
	//std::thread th_1([&] {pitchDown_->GenelatePitchShiftWaveFile(1.2,soundFile_.beforeFileName, soundFile_.afterFilenName); });
	//th_1.join();
	
	std::thread th_1([&] {equalizer_->GenelateEquaLizerWaveFile(soundFile_.beforeFileName, soundFile_.afterFilenName); });
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
	DrawFormatString(10, 0, 0xffffff, L"サウンドにエフェクトを適用中です");
}
