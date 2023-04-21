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

	// ���݂̃��j���[�Z���N�g�̏��
	nowSelect = static_cast<int>(Effect::PitchUp);
}

uniqueBase GenelateEffectScene::Update(uniqueBase ownScene)
{
	DrawOwnScreen();

	// �ʃX���b�h�Ƃ��ď���
	std::thread thred([&] {pitchUp_->GenelatePitchShiftWaveFile(0.8, soundFile_.beforeFileName, soundFile_.afterFilenName); });

	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		switch (nowSelect)
		{
		case static_cast<int>(Effect::PitchUp):
			if (thred.joinable() == false)
			{

			}
			break;
		default:
			break;
		}
	}

	return ownScene;
}

void GenelateEffectScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	int y = 0;
	y = 
	DrawFormatString(250, y, 0xffffff, L"��");
}
