#include <DxLib.h>
#include "DrawWave.h"

// �X�N���[���̑傫��
constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;

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

void DrawWave::DrawSoundWave()
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
