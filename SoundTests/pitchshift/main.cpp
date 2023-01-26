#include <DxLib.h>
#include <vector>
#include <shlobj.h>
#include <string>
#include <memory>
#include "PCM/PitchUp.h"
#include "Wave/Wave.h"

// �X�N���[���̑傫��
constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;


// �Đ��E�ꎞ��~
void Play(void)
{
	// �T�E���h�̍Đ�
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
	}

	DrawFormatString(0, 0, 0xffffff, L"�X�y�[�X�L�[:�Đ�");
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �E�C���h�E���[�h�ɕύX
	ChangeWindowMode(true);

	// ��ʉ𑜓x��ݒ�
	SetGraphMode(SCREEN_W, SCREEN_H, 32);

	// �w�i�F���D�F�ɐݒ�
	SetBackgroundColor(64, 64, 64);

	// �o�b�N�O���E���h
	SetAlwaysRunFlag(true);

	// �A�C�R���̐���
	SetWindowIconID(001);

	SetWindowText(L"�s�b�`�A�b�v�ύX�e�X�g");

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	// �`���𗠉�ʂɕύX
	SetDrawScreen(DX_SCREEN_BACK);

	auto YESNO = MessageBox(nullptr, L"�ϊ����s���܂���?", L"�s�b�`�A�b�v", MB_YESNO);

	if (YESNO == IDYES)
	{

		flag = true;
	}
	else
	{
		flag = false;
	}

	if (flag == true)
	{
		MessageBox(nullptr, L"�ϊ����s���܂�", L"�ϊ���",0);
	}

	// BGM�̃Z�b�g
	SetBGM(file, flag);

	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		// ��ʂ�����
		ClearDrawScreen();

		// �Đ�
		Play();

		// ���݂̍Đ��ʒu���擾
		samplePos = GetCurrentPositionSoundMem(SoundHandle);

		// �擾�����Đ��ʒu���T���v�����O���[�g�Ŋ����ăX�N���[��
		DrawStartSampleCount += samplePos / 44.1;
		// �`��͈́i����͒[����[�܂�)
		if (DrawStartSampleCount + SCREEN_W > samplePos)
		{
			DrawStartSampleCount = samplePos;
		}

		// ��ʂ̃Z���^�[���C��
		DrawLine(SCREEN_W / 2, 0, SCREEN_W / 2, SCREEN_W, 0xffffff);

		// ���`�����l���ƉE�`�����l������؂郉�C����`��
		DrawLine(0, SCREEN_H / 2, SCREEN_W / 2, SCREEN_H / 2, GetColor(0, 0, 0));

		// ���`�����l���ƉE�`�����l���̃Z���^�[���C����`��
		DrawLine(0, SCREEN_H / 4, SCREEN_W / 2, SCREEN_H / 4, GetColor(0, 0, 255));
		DrawLine(0, SCREEN_H - SCREEN_H / 4, SCREEN_W / 2, SCREEN_H - SCREEN_H / 4, GetColor(0, 0, 255));

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

		// �X�y�N�g���`��
		// ���݂̍Đ��ʒu������g�����z�𓾂�
		GetFFTVibrationSoftSound(SoftSoundHandle, -1, samplePos, fftsampleNam, paramList.data(), fftsampleNam);

		// ���g�����z����ʂ�`�悷��
		int x = -1;
		int j =	0;

		// ���̊Ԋu
		int offset = 15;
		// �T���v�������������s��
		for (int a = 0; a < fftsampleNam; a++)
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
				Param = pow(paramList[a], 0.5f) * 0.8f;

				// �U���X�y�N�g���̕`��(�E���ɂ��炵�ĕ`��j
				DrawBox(((SCREEN_W / 2) + 50) + j * offset, SCREEN_H - (int)(Param * SCREEN_H), ((SCREEN_W / 2) + 50) + j * offset + 4, SCREEN_H, 0x00ff00, true);
			}
		}

		// �~���b
		int mmSec = 1000;

		// �T�E���h�t�@�C���̕b��
		// ���݂̍Đ��ʒu���~���b�Ŏ擾
		mmSecondSoundTime = GetSoundCurrentTime(SoundHandle);
		auto sec = mmSecondSoundTime / mmSec;	// �b
		DrawFormatString(0, SCREEN_H - 15, 0xffffff, L"�Đ�����: %d�b", sec);

		// ����
		if (CheckHitKey(KEY_INPUT_E))
		{
			if (volume < 255)
			{
				volume++;
			}
			ChangeVolumeSoundMem(volume, SoundHandle);
		}

		if (CheckHitKey(KEY_INPUT_Q))
		{
			if (volume > 0)
			{
				volume--;
			}
			ChangeVolumeSoundMem(volume, SoundHandle);
		}

		DrawFormatString(150, SCREEN_H - 15, 0xffffff, L"�{�����[��: %d", volume);

		// �t���O��true�̂ݏ������s��
		if (flag == true)
		{
			// 1��̂ݗL��
			if (count == 0)
			{
				// �Ȃ̏I��������
				if (samplePos == TotalSampleCount)
				{
					// �Ȃ��I�������Z�b�g���Ȃ����A�ϊ���̋Ȃ��Đ�����
					SetBGM(file_2, false);
					PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
					count = 1;
				}
			}
		}

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	// �c�w���C�u�����̌�n��
	DxLib_End();

	return 0;
}
