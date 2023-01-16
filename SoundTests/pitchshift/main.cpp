#include <DxLib.h>
#include <vector>
#include <shlobj.h>
#include <string>
#include <memory>
#include "PitchShift/PitchUp.h"
#include "Wave/Wave.h"

// �X�N���[���̑傫��
constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;

// �T���v����
constexpr int sampleNum = 32768;
constexpr int fftsampleNam = 4096;

// �T�E���h�n���h��
int SoftSoundHandle;
int SoundHandle;

// ���[�v�t���O
bool loopFlag = false;

// �T�E���h�̈ꎞ��~�t���O
bool topPositionflag;

// ���g���擾
int frequency;

// �Đ��ʒu
LONGLONG TotalSampleCount;
LONGLONG DrawStartSampleCount = 0;

// �U���X�y�N�g��
std::vector<float> paramList(sampleNum);
LONGLONG samplePos;

// ���݂̍Đ�����
int mmSecondSoundTime;

// �{�����[��
int volume = 255;

std::unique_ptr<PitchUp> pitchUp = std::make_unique<PitchUp>();

// �֐�
// �������֐�
void SetBGM(void)
{
	pitchUp->GenelatePitchUpWaveFile();

	// �T�E���h�t�@�C���̓ǂݍ���
	SoftSoundHandle = LoadSoftSound(L"Sound/ex11_5.wav");

	// �\�t�g�T�E���h�n���h������T�E���h�n���h�����쐬
	SoundHandle = LoadSoundMemFromSoftSound(SoftSoundHandle);

	// �T�E���h�t�@�C���̒������擾
	TotalSampleCount = GetSoftSoundSampleNum(SoftSoundHandle);

	// �T�E���h�t�@�C���̎��g���𓾂�
	frequency = GetFrequencySoundMem(SoundHandle);

	// �{�����[���̃Z�b�g
	SetVolumeMusicMem(volume, SoundHandle);
}

// �Đ��E�ꎞ��~
void Play(void)
{
	// �T�E���h�̍Đ�
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		topPositionflag = false;
		PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK, topPositionflag);
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

	// ���g���ύX
	int changeWave = 0;		// �ǂݍ��񂾃T�E���h�̎��g����ύX����p�̕ϐ�
	int changeWaveSpeed = 1000;	// �ǂꂭ�ꂢ���g����ύX���邩

	int count = 0;

	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		// ��ʂ�����
		ClearDrawScreen();

		if (CheckHitKey(KEY_INPUT_F5))
		{
			// ��U�폜����
			DeleteSoundMem(SoundHandle);
			// BGM ���Z�b�g���Ȃ���
			SetBGM();

			// ������x�Đ�������
			topPositionflag;
			PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK, topPositionflag);
			count = 0;
		}

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
		mmSecondSoundTime = GetSoundCurrentTime(SoundHandle);
		auto sec = mmSecondSoundTime / mmSec;			// �b
		DrawFormatString(0, SCREEN_H - 15, 0xffffff, L"�Đ�����: %d�b", sec);

		int MinMax = 20000;

		// ���g���ύX
		if (CheckHitKey(KEY_INPUT_UP))
		{
			if (changeWave < MinMax)
			{
				changeWave += changeWaveSpeed;
			}
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			if (changeWave > -MinMax)
			{
				changeWave -= changeWaveSpeed;
			}
		}
		// �ǂꂭ�炢���g����ύX���Ă��邩���킩��₷��
		auto ChangeWave = changeWave / 1000;
		DrawFormatString(0, 60, 0xffffff, L"�� ���L�[:�{���E�ᑬ �l %d", ChangeWave);

		// �Ȃ��I��������A�擪����������g�������Ƃɖ߂�
		if (samplePos >= TotalSampleCount || samplePos == 0)
		{
			changeWave = 0;
		}

		// ���݂̎��g��
		auto nowWave = frequency + changeWave;
		SetFrequencySoundMem(nowWave, SoundHandle);

		// ���[�v�t���O�̃I���I�t
		if (CheckHitKey(KEY_INPUT_1))
		{
			loopFlag = true;
		}

		if (CheckHitKey(KEY_INPUT_2))
		{
			loopFlag = false;
		}

		// �Đ��ʒu�̈ړ�
		if (samplePos <= TotalSampleCount)
		{
			if (CheckHitKey(KEY_INPUT_RIGHT))
			{
				// ��U�Đ����~�߂�
				StopSoundMem(SoundHandle);
				// ���݂̍Đ����Ԃ��擾
				int nowTime = GetSoundCurrentTime(SoundHandle);
				// ���Ԏw��
				LONGLONG time = 0 * 1000;
				time += 1000;
				SetStreamSoundCurrentTime(nowTime + time, SoundHandle);
			}
			if (CheckHitKey(KEY_INPUT_LEFT))
			{
				StopSoundMem(SoundHandle);
				// ���݂̍Đ����Ԃ��擾
				int nowTime = GetSoundCurrentTime(SoundHandle);
				// ���Ԏw��
				LONGLONG time = 0 * 1000;
				time -= 1000;
				SetStreamSoundCurrentTime(nowTime + time, SoundHandle);
			}
		}
		DrawFormatString(300, 60, 0xffffff, L"�� �� �L�[:�Đ����Ԃ�߂��E�i�߂�");

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

		// ���[�v����(�Đ����������珈��������j
		if (loopFlag == true)
		{
			// �Ȃ̏I��������
			if (samplePos == TotalSampleCount || samplePos == 0)
			{
				topPositionflag = true;
				PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK, topPositionflag);
			}
		}

		DrawFormatString(0, 90, 0xffffff, L"1�L�[: ���[�v�t���O ON\n2�L�[: ���[�v�t���O OFF");
		if (loopFlag)
		{
			DrawFormatString(0, 140, 0xffffff, L"���[�v: ON");
		}
		else
		{
			DrawFormatString(0, 140, 0xffffff, L"���[�v: OFF");
		}

		DrawFormatString(0, 0, 0xffffff, L"F5: BGM�I��");
		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	// �c�w���C�u�����̌�n��
	DxLib_End();

	return 0;
}
