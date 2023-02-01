#include "DrawWave.h"
#include "../../Scene/SceneMag.h"
DrawWave::DrawWave()
{
}

DrawWave::~DrawWave()
{
}

void DrawWave::Init(void)
{
	// ������
	screen_w_ = lpScenMag.GetSCREEN_W();	// ��
	screen_h_ = lpScenMag.GetSCREEN_H();	// ����

	// ���T���v�����̎擾
	totalSampleCount_ = lpSoundSet.GetTotalSampleCount();

	// ���݂̃T���v�����̏�����
	drawStartSampleCount_ = 0;
}

void DrawWave::Update(void)
{
	// ���݂̃T�E���h�n���h���̎擾
	auto soundHande = lpSoundSet.GetSoundHandle();

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
	// �����ōX�V�������Ă�
	Update();

	// ���݂̃\�t�g�T�E���h�n���h���̎擾
	auto softSoundHandle = lpSoundSet.GetSouftSoundHandle();

	// �E�`�����l���A���`�����l��
	int Ch1, Ch2;
	// �g�`��`��
	// 1�T���v�����������s��
	for (long long i = 0; i < screen_w_ / 2 && i + drawStartSampleCount_ < totalSampleCount_; i++)
	{
		// �g�`�̐U���l���擾
		ReadSoftSoundData(softSoundHandle, i + drawStartSampleCount_, &Ch1, &Ch2);

		// �U���l�̍����̏c���C����`��
		DrawLine(i, screen_h_ / 4, i, screen_h_ / 4 + (Ch1 * (screen_h_ / 4) / sampleNum_),0x0000ff);
		DrawLine(i, screen_h_ - screen_h_ / 4, i, screen_h_ - screen_h_ / 4 + (Ch2 * (screen_h_ / 4) / sampleNum_), 0x0000ff);
	}
}
