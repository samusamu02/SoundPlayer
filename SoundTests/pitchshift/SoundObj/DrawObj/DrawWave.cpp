#include <DxLib.h>
#include "DrawWave.h"

DrawWave::DrawWave()
{
	// �������Ăяo��
	Init();
}

DrawWave::~DrawWave()
{
	
}

void DrawWave::Init()
{
	// �T���v�����̎擾
	totalSampleCount_ = GetSoftSoundSampleNum(softSoundHandle_);
}

void DrawWave::Update()
{
	// �擾�����Đ��ʒu���T���v�����O���[�g�Ŋ����ăX�N���[��
	drawStartSampleCount_ += samplePos_ / 44.1;
	// �`��͈́i����͒[����[�܂�)
	if (drawStartSampleCount_ + SCREEN_W > samplePos_)
	{
		drawStartSampleCount_ = samplePos_;
	}
}

void DrawWave::Draw()
{
	// �E�`�����l���A���`�����l��
	int Ch1, Ch2;

	// �g�`��`��
	// 1�T���v�����������s��
	for (LONGLONG i = 0; i < SCREEN_W / 2 && i + drawStartSampleCount_ < totalSampleCount_; i++)
	{
		// �g�`�̐U���l���擾
		ReadSoftSoundData(softSoundHandle_, i + drawStartSampleCount_, &Ch1, &Ch2);

		// �U���l�̍����̏c���C����`��
		DrawLine(i, SCREEN_H / 4, i, SCREEN_H / 4 + (Ch1 * (SCREEN_H / 4) / sampleNum_), GetColor(0, 0, 255));
		DrawLine(i, SCREEN_H - SCREEN_H / 4, i, SCREEN_H - SCREEN_H / 4 + (Ch2 * (SCREEN_H / 4) / sampleNum_), GetColor(0, 0, 255));
	}
}
