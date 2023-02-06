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
	// �ϊ����s�����ǂ����̃`�F�b�N
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

	// �T�E���h�̍Đ�
	auto soundHandle = lpSoundSet.GetSoundHandle();
	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);

	// �J�E���g�̏�����
	loopCount_ = 0;

	// �`��Ǘ��N���X�̏������֐��Ăяo��
	drawObjMag_->Init();
}

void SoundObjMag::Update(void)
{
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
			lpSoundSet.SoundInit(soundFile_.afterFilenName, false);	
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

bool SoundObjMag::GetYESNOFlag(void)
{
	return YESNOflag_;
}
