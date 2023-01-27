#include <DxLib.h>
#include "DrawSpectrum.h"

DrawSpectrum::DrawSpectrum()
{
	// �������Ăяo��
	Init();
}

DrawSpectrum::~DrawSpectrum()
{
}

void DrawSpectrum::Init(void)
{
	// �v�f���̊m��
	paramList_.resize(buffuerlength_);

	// �X�y�N�g���`��
	// ���݂̍Đ��ʒu������g�����z�𓾂�
	GetFFTVibrationSoftSound(softSoundHandle_, -1, samplePos_, fftsampleNam_, paramList_.data(), fftsampleNam_);
}

void DrawSpectrum::Draw(void)
{
	// ���g�����z����ʂ�`�悷��
	int x = -1;
	int j = 0;

	// ���̊Ԋu
	int offset = 15;
	// �T���v�������������s��
	for (int a = 0; a < fftsampleNam_; a++)
	{
		// �ΐ��������łȂ��ꍇ�̂ݒl��ς���
		auto log = (int)(log10((double)a) * 10);
		if (log != x)
		{
			// �`��ʒu
			j++;

			// �����ɑ΂���log�őΐ����Ƃ�
			x = (int)(log10((double)a) * 10);

			// �p�����[�^�[
			float Param;

			// �֐�����擾�ł���l��`��ɓK�����l�ɒ���
			Param = pow(paramList_[a], 0.5f) * 0.8f;

			// �U���X�y�N�g���̕`��(�E���ɂ��炵�ĕ`��j
			DrawBox(((SCREEN_W / 2) + 50) + j * offset, SCREEN_H - (int)(Param * SCREEN_H), ((SCREEN_W / 2) + 50) + j * offset + 4, SCREEN_H, 0x00ff00, true);
		}
	}
}
