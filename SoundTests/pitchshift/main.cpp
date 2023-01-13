#include <DxLib.h>
#include <shlobj.h>
#include <string>
#include "Definition.h"
#include "PitchUp/PitchUp.h"

PitchUp* pitchUp_ = new PitchUp();

// �������֐�
void SetBGM(void)
{
	// ���̃T�E���h�t�@�C��
	SoundFileName[0] = L"Sound/Peak_test_A.wav";

	// �s�b�`�ύX��̃t�@�C�����̐ݒ�
	SoundFileName[1] = L"Sound/PitchUp.wav";

	// �s�b�`�A�b�v�̐���
	pitchUp_->GeneratePitchUpWaveFile(SoundFileName[0], SoundFileName[1]);

	// �T�E���h�t�@�C���̓ǂݍ���
	for (int i = 0; i < fileNam; i++)
	{
		SoftSoundHandle[i] = LoadSoftSound(SoundFileName[i]);

		// �\�t�g�T�E���h�n���h������T�E���h�n���h�����쐬
		SoundHandle[i] = LoadSoundMemFromSoftSound(SoftSoundHandle[i]);

		// �T�E���h�t�@�C�����I������Ȃ������ꍇ
		if (SoftSoundHandle[i] == -1)
		{
			// ��U�폜����
			DeleteSoundMem(SoundHandle[i]);
			MessageBox(NULL, L"�T�E���h�t�@�C����������܂���ł���", L"�G���[", MB_OK);
		}
		else
		{
			// �T�E���h�t�@�C���̒������擾
			TotalSampleCount = GetSoftSoundSampleNum(SoftSoundHandle[i]);
		}

		// �{�����[���̃Z�b�g
		SetVolumeMusicMem(volume, SoundHandle[i]);
	}
}

// �Đ�
void Play(void)
{
	// �T�E���h�̍Đ�
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		topPositionflag = false;
		PlaySoundMem(SoundHandle[0], DX_PLAYTYPE_BACK, topPositionflag);
	}

	DrawFormatString(0, 30, 0xffffff, L"�X�y�[�X�L�[:�Đ�");
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

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	// �`���𗠉�ʂɕύX
	SetDrawScreen(DX_SCREEN_BACK);

	// BGM�̃Z�b�g
	SetBGM();

	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		// ��ʂ�����
		ClearDrawScreen();

		// �Đ�
		Play();

		// ���݂̍Đ��ʒu���擾
		samplePos = GetCurrentPositionSoundMem(SoundHandle[0]);

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
		for (LONGLONG i = 0; i < SCREEN_W / 2 && i + DrawStartSampleCount < TotalSampleCount; i++)
		{
			// �g�`�̐U���l���擾
			ReadSoftSoundData(SoftSoundHandle[0], i + DrawStartSampleCount, &Ch1, &Ch2);

			// �U���l�̍����̏c���C����`��
			DrawLine(i, SCREEN_H / 4, i, SCREEN_H / 4 + (Ch1 * (SCREEN_H / 4) / sampleNum), GetColor(0, 0, 255));
			DrawLine(i, SCREEN_H - SCREEN_H / 4, i, SCREEN_H - SCREEN_H / 4 + (Ch2 * (SCREEN_H / 4) / sampleNum), GetColor(0, 0, 255));
		}

		// �X�y�N�g���`��
		// ���݂̍Đ��ʒu������g�����z�𓾂�
		GetFFTVibrationSoftSound(SoftSoundHandle[0], -1, samplePos, fftsampleNam, paramList, fftsampleNam);

		// ���g�����z����ʂ�`�悷��
		int x = -1;
		int j = 0;
		int offset = 15;
		for (int a = 0; a < fftsampleNam; a++)
		{
			if ((int)(log10((double)a) * 10) != x)
			{
				j++;
				x = (int)(log10((double)a) * 10);

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
		mmSecondSoundTime = GetSoundCurrentTime(SoundHandle[0]);
		auto sec = mmSecondSoundTime / mmSec;			// �b
		DrawFormatString(0, SCREEN_H - 15, 0xffffff, L"�Đ�����: %d�b", sec);

		// ���[�v�t���O�̃I���I�t
		if (CheckHitKey(KEY_INPUT_1))
		{
			loopFlag = true;
		}

		if (CheckHitKey(KEY_INPUT_2))
		{
			loopFlag = false;
		}

		// ����
		if (CheckHitKey(KEY_INPUT_E))
		{
			if (volume < 255)
			{
				volume++;
			}
			ChangeVolumeSoundMem(volume, SoundHandle[0]);
		}

		if (CheckHitKey(KEY_INPUT_Q))
		{
			if (volume > 0)
			{
				volume--;
			}
			ChangeVolumeSoundMem(volume, SoundHandle[0]);
		}

		DrawFormatString(150, SCREEN_H - 15, 0xffffff, L"�{�����[��: %d", volume);

		DrawFormatString(0, 90, 0xffffff, L"1�L�[: ���[�v�t���O ON\n2�L�[: ���[�v�t���O OFF");
		if (loopFlag)
		{
			DrawFormatString(0, 140, 0xffffff, L"���[�v: ON");
		}
		else
		{
			DrawFormatString(0, 140, 0xffffff, L"���[�v: OFF");
		}

		// ���[�v����(�Đ����������珈��������j
		if (loopFlag == true)
		{
			// �Ȃ̏I��������
			if (samplePos == TotalSampleCount || samplePos == 0)
			{
				topPositionflag = true;
				PlaySoundMem(SoundHandle[0], DX_PLAYTYPE_BACK, topPositionflag);
			}
		}

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	// �c�w���C�u�����̌�n��
	DxLib_End();

	return 0;
}
