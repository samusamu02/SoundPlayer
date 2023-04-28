#include <DxLib.h>
#include "SoundPlayScene.h"
#include "SoundSelectScene.h"

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

	// �t���O�̏�����
	viewFlag_ = true;
}

uniqueBase SoundPlayScene::Update(uniqueBase ownScene)
{
	// �X�V����
	soundObjMag_->Update();

	// �`�揈��
	DrawOwnScreen();

	// �X�y�[�X�������ꂽ�猳�̃V�[���ɂ��ǂ�
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// �������ɂ���T�E���h�f�[�^�̍폜
		auto soundHandle = lpSoundSet.GetSoundHandle();
		DeleteSoundMem(soundHandle);

		// �ŏ��̃V�[���ɖ߂�
		return std::make_unique<SoundSelectScene>();
	}

	// �E�L�[�������ꂽ�t���O��false�ɂ���
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		viewFlag_ = false;
	}

	// �����̃V�[����Ԃ�
	return ownScene;
}

void SoundPlayScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	// �T�E���h�I�u�W�F�N�g�̕`�揈��
	soundObjMag_->Draw();

	// y���W
	int y = 0;

	if (viewFlag_ == true)
	{
		DrawFormatString(10, y, 0xffffff, L"�E�L�[����͂���ƃG�t�F�N�g�K�p��̃T�E���h�t�@�C�����Đ��ł��܂�");
	}

	// �t���O�̏�Ԃɂ��y���W��ς���
	DrawFormatString(10,viewFlag_ ? 30 : y, 0xffffff, L"�X�y�[�X�L�[����͂���ƍŏ��̃V�[���ɖ߂�܂�");
}
