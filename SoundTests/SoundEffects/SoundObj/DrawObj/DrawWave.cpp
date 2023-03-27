#include "DrawWave.h"
#include "../../SceneMag.h"
DrawWave::DrawWave()
{
	// warning�΍�
	drawStartSampleCount_ = 0;
	totalSampleCount_ = 0;
	screen_h_ = 0;
	screen_w_ = 0;
}

DrawWave::~DrawWave()
{
}

void DrawWave::Init(void)
{
	// ������
	screen_w_ = lpScenMag.GetScreen_W();	// ��
	screen_h_ = lpScenMag.GetScreen_H();	// ����

	// ���T���v�����̎擾
	totalSampleCount_ = lpSoundSet.GetTotalSampleCount();

	// ���݂̃T���v�����̏�����
	drawStartSampleCount_ = 0;
}

void DrawWave::Update(void)
{
	// ���݂̃T�E���h�n���h���̎擾
	auto soundHande = lpSoundSet.GetSoundHandle();

	// ���݂̃T���v���̈ʒu
	auto samplePos = GetCurrentPositionSoundMem(soundHande);

	// �擾�����Đ��ʒu���T���v�����O���[�g�Ŋ����ăX�N���[��
	drawStartSampleCount_ = lpSoundSet.GetDrawStartSampleCount();
	drawStartSampleCount_ += samplePos;

	// �`��͈́i�[�܂�)
	if (drawStartSampleCount_ + screen_w_ > samplePos)
	{
		drawStartSampleCount_ = samplePos;
	}
}

void DrawWave::Draw(void)
{
	// ���݂̃\�t�g�T�E���h�n���h���̎擾
	auto softSoundHandle = lpSoundSet.GetSouftSoundHandle();

	// �E�`�����l���A���`�����l��
	int Ch1, Ch2;
	// �g�`��`��
	// 1�T���v�����������s��
	for (LONGLONG i = 0; i < screen_w_ / 2 && i + drawStartSampleCount_ < totalSampleCount_; i++)
	{
		// �g�`�̐U���l���擾
		ReadSoftSoundData(softSoundHandle, i + drawStartSampleCount_, &Ch1, &Ch2);

		// �U���l�̍����̏c���C����`��
		DrawLine(static_cast<int>(i), screen_h_ / 4, static_cast<int>(i), screen_h_ / 4 + (Ch1 * (screen_h_ / 4) / sampleNum_),0x0000ff);
		DrawLine(static_cast<int>(i), screen_h_ - screen_h_ / 4, static_cast<int>(i), screen_h_ - screen_h_ / 4 + (Ch2 * (screen_h_ / 4) / sampleNum_), 0x0000ff);
	}
}
