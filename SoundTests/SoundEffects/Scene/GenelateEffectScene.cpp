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
	// �����Ȃ�
}

uniqueBase GenelateEffectScene::Update(uniqueBase ownScene)
{
	DrawOwnScreen();

	// �ʃX���b�h
	std::thread th_1([&] {pitchDown_->GenelatePitchShiftWaveFile(1.2, soundFile_.beforeFileName, soundFile_.afterFilenName); });
	th_1.join();

	// �X���b�h�̏��������������玟�̃V�[����
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
	DrawFormatString(10, 0, 0xffffff, L"�G�t�F�N�g�ɃT�E���h��K�p���ł�");
}
