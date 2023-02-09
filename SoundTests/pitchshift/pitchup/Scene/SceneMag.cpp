#include "SceneMag.h"
#include <DxLib.h>

// �X�N���[���̑傫��
constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;

void SceneMag::Run()
{
	// �V�X�e�����������ł��Ă��Ȃ������珈�����s��Ȃ�
	if (!sysInit_)
	{
		if (!SysInit())
		{
			return;
		}
	}

	// �T�E���h�I�u�W�F�N�g�Ǘ��N���X�̃C���X�^���X
	soundObjMag_ = std::make_unique<SoundObjMag>();

	// �T�E���h�I�u�W�F�N�g�Ǘ��N���X�̏������֐��Ăяo��
	soundObjMag_->Init();

	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		// �T�E���h�I�u�W�F�N�g�Ǘ��N���X�̍X�V�֐��Ăяo��
		soundObjMag_->Update();

		// �`���𗠉�ʂɕύX
		SetDrawScreen(DX_SCREEN_BACK);

		// ��ʂ�����
		ClearDrawScreen();

		// 	// �T�E���h�I�u�W�F�N�g�Ǘ��N���X�̕`��֐��Ăяo��
		soundObjMag_->Draw();

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	//Dxlib�̏I��
	DxLib_End();
}

bool SceneMag::SysInit()
{
	// �E�C���h�E���[�h�ɕύX
	ChangeWindowMode(true);

	// ��ʉ𑜓x��ݒ�
	SetGraphMode(SCREEN_W, SCREEN_H, 32);

	// �w�i�F���D�F�ɐݒ�
	SetBackgroundColor(64, 64, 64);

	// �o�b�N�O���E���h
	SetAlwaysRunFlag(true);

	// �A�C�R���̐���
	SetWindowIconID(001);

	SetWindowText(L"�s�b�`�A�b�v�ύX�e�X�g");

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return false;
	}

	return true;
}

int SceneMag::GetScreen_H(void)
{
	return SCREEN_H;
}

int SceneMag::GetScreen_W(void)
{
	return SCREEN_W;
}

SceneMag::SceneMag()
{
	// �V�X�e���̏�Ԃ̎擾
	sysInit_ = SysInit();
}

SceneMag::~SceneMag()
{
	// �����̂Ȃ�
}