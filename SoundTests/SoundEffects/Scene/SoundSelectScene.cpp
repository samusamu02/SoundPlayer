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
	// �T�E���h�̏�����
	lpSoundSet.SoundDataInit(soundFile_.beforeFileName);
}

uniqueBase SoundSelectScene::Update(uniqueBase ownScene)
{
	// ��ɕ`����s��
	DrawOwnScreen();

	// �T�E���h�n���h���̎擾
	auto soundHandle = lpSoundSet.GetSoundHandle();

	if (soundHandle > 0)
	{
		// �T�E���h������΃V�[���ֈړ�����
		return std::make_unique<GenelateEffectScene>();
	}
	else
	{
		// �T�E���h���Ȃ��ꍇ
		DrawFormatString(10, 10, 0xffffff, L"�T�E���h�t�@�C�������݂��܂���");
	}

	return ownScene;
}

void SoundSelectScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
}
