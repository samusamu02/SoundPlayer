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

}

void DrawWave::Update(void)
{
	// �X�N���[���T�C�Y�̎擾
	auto screen_w = lpScenMag.GetSCREEN_W();

	// �擾�����Đ��ʒu���T���v�����O���[�g�Ŋ����ăX�N���[��
	drawStartSampleCount_ += samplePos_ / 44.1;

	// �`��͈́i�[�܂�)
	if (drawStartSampleCount_ + screen_w > samplePos_)
	{
		drawStartSampleCount_ = samplePos_;
	}
}

void DrawWave::Draw(void)
{
	// �X�N���[���T�C�Y�̎擾
	auto screen_w = lpScenMag.GetSCREEN_W();
	auto screen_h = lpScenMag.GetSCREEN_H();

	// �E�`�����l���A���`�����l��
	int Ch1, Ch2;
	// �g�`��`��
	// 1�T���v�����������s��
	for (long long i = 0; i < screen_w / 2 && i + drawStartSampleCount_ < totalSampleCount_; i++)
	{
		// �g�`�̐U���l���擾
		ReadSoftSoundData(softSoundHandle_, i + drawStartSampleCount_, &Ch1, &Ch2);

		// �U���l�̍����̏c���C����`��
		DrawLine(i, screen_h / 4, i, screen_h / 4 + (Ch1 * (screen_h / 4) / sampleNum_), GetColor(0, 0, 255));
		DrawLine(i, screen_h - screen_h / 4, i, screen_h - screen_h / 4 + (Ch2 * (screen_h / 4) / sampleNum_), GetColor(0, 0, 255));
	}
}
