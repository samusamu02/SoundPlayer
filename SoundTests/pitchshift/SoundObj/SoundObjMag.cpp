#include "SoundObjMag.h"

SoundObjMag::SoundObjMag()
{
	// �C���X�^���X
	drawObjMag_ = std::make_unique<DrawObjMag>();
}

SoundObjMag::~SoundObjMag()
{
	// �����Ȃ�
}

void SoundObjMag::Init(void)
{
	// �`��Ǘ��N���X�̏������֐��Ăяo��
	drawObjMag_->Init();
}

void SoundObjMag::Update(void)
{
	// �`��Ǘ��N���X�̍X�V�֐��Ăяo��
	drawObjMag_->Update();
}

void SoundObjMag::Draw(void)
{
	// �`��Ǘ��N���X�̕`��֐��Ăяo��
	drawObjMag_->Draw();
}
