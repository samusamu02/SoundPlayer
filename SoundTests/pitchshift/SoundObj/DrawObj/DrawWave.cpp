#include <DxLib.h>
#include "DrawWave.h"

DrawWave::DrawWave()
{
	Init();
}

DrawWave::~DrawWave()
{

}

void DrawWave::Init()
{
	totalSampleCount_ = GetSoftSoundSampleNum(softSoundHandle_);
}

void DrawWave::DrawSoundWave()
{
	// �E�`�����l���A���`�����l��
	int Ch1, Ch2;
	// �g�`��`��
	// 1�T���v�����������s��
	for (LONGLONG i = 0; i < SCREEN_W / 2 && i + DrawStartSampleCount < TotalSampleCount; i++)
	{
		// �g�`�̐U���l���擾
		ReadSoftSoundData(SoftSoundHandle, i + DrawStartSampleCount, &Ch1, &Ch2);

		// �U���l�̍����̏c���C����`��
		DrawLine(i, SCREEN_H / 4, i, SCREEN_H / 4 + (Ch1 * (SCREEN_H / 4) / sampleNum), GetColor(0, 0, 255));
		DrawLine(i, SCREEN_H - SCREEN_H / 4, i, SCREEN_H - SCREEN_H / 4 + (Ch2 * (SCREEN_H / 4) / sampleNum), GetColor(0, 0, 255));
	}
}
