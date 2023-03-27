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
	// �`��Ǘ��N���X�̏������֐��Ăяo��
	drawObjMag_->Init();

	// �J�E���g�̏�����
	loopCount_ = 0;
}

void SoundObjMag::Update(void)
{
	// �`��Ǘ��N���X�̍X�V�����Ăяo��
	drawObjMag_->Update();

	// �I���`�F�b�N
	if (loopCount_ == 0)
	{
		// �ϊ��O�̃T�E���h�n���h���̎擾
		auto beforesoundHandle = lpSoundSet.GetSoundHandle();
		// ���T���v�����̎擾
		auto totalSampleCount = lpSoundSet.GetTotalSampleCount();
		// ���݂̃T�E���h���̎擾
		auto samplePos = GetCurrentPositionSoundMem(beforesoundHandle);

		// �Ō�܂ōĐ�����邩�E���L�[����͂���ƕϊ���̃T�E���h���Đ�����
		if (samplePos == totalSampleCount || 
			CheckHitKey(KEY_INPUT_RIGHT))
		{
			// �ϊ���̃T�E���h���Đ�����
			// �ϊ��O�̃T�E���h�n���h���̍폜
			DeleteSoundMem(beforesoundHandle);
			// �V�����T�E���h�n���h���̃Z�b�g
			lpSoundSet.SoundDataInit(soundFile_.afterFilenName);	
			// �ϊ���̃T�E���h�n���h���̎擾
			auto afuterSoundHandle = lpSoundSet.GetSoundHandle();
			// �Đ�
			PlaySoundMem(afuterSoundHandle, DX_PLAYTYPE_BACK);
			// ���[�v�J�E���g��1�ɂ���
			loopCount_ = 1;
		}
	}
}

void SoundObjMag::Draw(void)
{
	// �`��Ǘ��N���X�̕`��֐��Ăяo��
	drawObjMag_->Draw();
}