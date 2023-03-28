#include <DxLib.h>
#include "SoundPlayScene.h"
SoundPlayScene::SoundPlayScene()
{
	// �C���X�^���X
	soundObjMag_ = std::make_unique<SoundObjMag>();

	Init();

	DrawOwnScreen();
}

SoundPlayScene::~SoundPlayScene()
{

}

void SoundPlayScene::Init(void)
{
	// ����������
	soundObjMag_->Init();

	// �T�E���h�̍Đ�
	auto soundHandle = lpSoundSet.GetSoundHandle();
	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
}

uniqueBase SoundPlayScene::Update(uniqueBase ownScene)
{
	// �X�V����
	soundObjMag_->Update();

	// �`�揈��
	DrawOwnScreen();

	// �����̃V�[����Ԃ�
	return ownScene;
}

void SoundPlayScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	// �T�E���h�I�u�W�F�N�g�̕`�揈��
	soundObjMag_->Draw();
}
