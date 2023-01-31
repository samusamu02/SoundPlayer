#include "SoundObjMag.h"

SoundObjMag::SoundObjMag()
{
	// �C���X�^���X
	drawObjMag_ = std::make_unique <DrawObjMag>();
}

SoundObjMag::~SoundObjMag()
{
	// �����Ȃ�
}

void SoundObjMag::Init(void)
{
	// �T�E���h�{�̂̏�����
	auto YESNO = MessageBox(nullptr, L"�ϊ����s���܂���?", L"�s�b�`�A�b�v", MB_YESNO);

	if (YESNO == IDYES)
	{

		YESNOflag_ = true;
	}
	else
	{
		YESNOflag_ = false;
	}

	if (YESNOflag_ == true)
	{
		MessageBox(nullptr, L"�ϊ����s���܂�", L"�ϊ���", 0);
	}

	// �T�E���h�̏�����
	lpSoundSet.SoundInit(soundFile_.beforeFileName,YESNOflag_);

	// �`��Ǘ��N���X�̏������֐��Ăяo��
	drawObjMag_->Init();
}

void SoundObjMag::Update(void)
{
	// �`��Ǘ��N���X�̍X�V�֐��Ăяo��
	drawObjMag_->Update();

	// �T�E���h�̍Đ�
	auto soundHandle = lpSoundSet.GetSoundHandle();

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
	}
}

void SoundObjMag::Draw(void)
{
	// �`��Ǘ��N���X�̕`��֐��Ăяo��
	drawObjMag_->Draw();
}

bool SoundObjMag::GetYESNOFlag(void)
{
	return YESNOflag_;
}
