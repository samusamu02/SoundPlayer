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

	// ���݂̍Đ��ʒu���擾
	auto soundHande = lpSoundSet.GetSoundHandle();
	auto samplePos = GetCurrentPositionSoundMem(soundHande);

	// �擾�����Đ��ʒu���T���v�����O���[�g�Ŋ����ăX�N���[��
	auto drawStartSampleCount = lpSoundSet.GetDrawStartSampleCount();
	drawStartSampleCount += samplePos / 44.1;

	
	// �`��͈́i�[�܂�)
	if (drawStartSampleCount + screen_w > samplePos)
	{
		drawStartSampleCount = samplePos;
	}

	// �I���`�F�b�N
	if (loopCount_ == 0)
	{
		// �Ȃ̏I��������
		auto totalSampleCount = lpSoundSet.GetTotalSampleCount();
		if (samplePos == totalSampleCount)
		{
			lpSoundSet.SoundInit(soundFile_.beforeFileName, false);
			PlaySoundMem(soundHande, DX_PLAYTYPE_BACK);
			loopCount_ = 1;
		}
	}
}

void DrawWave::Draw(void)
{
	// �X�N���[���T�C�Y�̎擾
	auto screen_w = lpScenMag.GetSCREEN_W();
	auto screen_h = lpScenMag.GetSCREEN_H();

	auto softSoundHandle = lpSoundSet.GetSouftSoundHandle();

	// �E�`�����l���A���`�����l��
	int Ch1, Ch2;
	// �g�`��`��
	// 1�T���v�����������s��
	auto drawStartSampleCount = lpSoundSet.GetDrawStartSampleCount();
	auto totalSampleCount = lpSoundSet.GetTotalSampleCount();
	for (long long i = 0; i < screen_w / 2 && i + drawStartSampleCount < totalSampleCount; i++)
	{
		// �g�`�̐U���l���擾
		ReadSoftSoundData(softSoundHandle, i + drawStartSampleCount, &Ch1, &Ch2);

		// �U���l�̍����̏c���C����`��
		DrawLine(i, screen_h / 4, i, screen_h / 4 + (Ch1 * (screen_h / 4) / sampleNum_), GetColor(0, 0, 255));
		DrawLine(i, screen_h - screen_h / 4, i, screen_h - screen_h / 4 + (Ch2 * (screen_h / 4) / sampleNum_), GetColor(0, 0, 255));
	}
}
