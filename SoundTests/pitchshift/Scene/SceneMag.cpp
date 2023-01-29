#include "SceneMag.h"
#include <DxLib.h>

// �X�N���[���̑傫��
constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;

// �T���v����
constexpr int sampleNum = 32768;
constexpr int fftsampleNam = 4096;

void SceneMag::Run()
{
	if (!sysInit_)
	{
		if (!SysInit())
		{
			return;
		}
	}

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
		MessageBox(nullptr, L"�ϊ����s���܂�", L"�ϊ���", 0);
	}

	// BGM�̃Z�b�g
	SetBGM(file, flag);

	soundObjMag_ = std::make_unique<SoundObjMag>();

	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		// �`���𗠉�ʂɕύX
		SetDrawScreen(DX_SCREEN_BACK);

		// ��ʂ�����
		ClearDrawScreen();

		// �Đ�
		Play();

		// ���݂̍Đ��ʒu���擾
		samplePos = GetCurrentPositionSoundMem(SoundHandle);

		paramList.resize(sampleNum);

		soundObjMag_->Draw();

		// �擾�����Đ��ʒu���T���v�����O���[�g�Ŋ����ăX�N���[��
		DrawStartSampleCount += samplePos / 44.1;
		// �`��͈́i����͒[����[�܂�)
		if (DrawStartSampleCount + SCREEN_W > samplePos)
		{
			DrawStartSampleCount = samplePos;
		}

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
		int j = 0;

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
}

void SceneMag::Update()
{
}

void SceneMag::Draw()
{
}

bool SceneMag::SysInit()
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
		return false;
	}

	return true;
}

void SceneMag::SetBGM(const wchar_t* fileName, bool genelateFlag)
{
	// �s�b�`�A�b�v(flag��true�̏ꍇ�̂ݐV����wav�t�@�C���𐶐�����
	if (genelateFlag == true)
	{
		pitchUp->GenelatePitchUpWaveFile(fileName, file_2);
	}

	// �T�E���h�t�@�C���̓ǂݍ���
	SoftSoundHandle = LoadSoftSound(fileName);

	// �\�t�g�T�E���h�n���h������T�E���h�n���h�����쐬
	SoundHandle = LoadSoundMemFromSoftSound(SoftSoundHandle);

	// �T�E���h�t�@�C���̒������擾
	TotalSampleCount = GetSoftSoundSampleNum(SoftSoundHandle);

	// �T�E���h�t�@�C���̎��g���𓾂�
	frequency = GetFrequencySoundMem(SoundHandle);

	// �{�����[���̃Z�b�g
	SetVolumeMusicMem(volume, SoundHandle);
}

void SceneMag::Play(void)
{
	// �T�E���h�̍Đ�
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
	}

	DrawFormatString(0, 0, 0xffffff, L"�X�y�[�X�L�[:�Đ�");
}

int SceneMag::GetSCREEN_H(void)
{
	return SCREEN_H;
}

int SceneMag::GetSCREEN_W(void)
{
	return SCREEN_W;
}


SceneMag::SceneMag()
{
	sysInit_ = SysInit();
}

SceneMag::~SceneMag()
{
}
