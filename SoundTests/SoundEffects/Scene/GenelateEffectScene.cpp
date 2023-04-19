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

	// �ʃX���b�h�Ƃ��ď���
	//std::thread th_1([&] {pitchUp_->GenelatePitchShiftWaveFile(0.8,soundFile_.beforeFileName, soundFile_.afterFilenName); });
	//th_1.join();
	
	//std::thread th_1([&] {equalizer_->GenelateEquaLizerWaveFile(soundFile_.beforeFileName, soundFile_.afterFilenName); });
	//th_1.join();

	// �X���b�h�̏��������������玟�̃V�[����
	//if (th_1.joinable() == false)
	//{
	//	return std::make_unique<SoundPlayScene>();
	//}

	return ownScene;
}

void GenelateEffectScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	int y = 0;

	if (CheckHitKey(KEY_INPUT_DOWN) == 0)
	{
		y++;
	}

	DrawFormatString(10, y, 0xffffff, L"��");

	DrawFormatString(10, 0, 0xffffff, L"�K�p����T�E���h�G�t�F�N�g��I��ł�������");

	DrawFormatString(10, 0, 0xffffff, L"�T�E���h�ɃG�t�F�N�g��K�p���ł�");
}