#include "DrawSpectrum.h"
#include "../../Scene/SceneMag.h"

DrawSpectrum::DrawSpectrum()
{
}

DrawSpectrum::~DrawSpectrum()
{
}

void DrawSpectrum::Init(void)
{
	// �X�N���[���T�C�Y
	screen_w_ = lpScenMag.GetScreen_W();	// ��
	screen_h_ = lpScenMag.GetScreen_H();	// �L��

	// �T���v�������v�f�����m�ۂ���
	paramList.resize(sampleNum_);

	// FFT�̃T���v����
	fftSampleNum_ = 4096;
}

void DrawSpectrum::Draw(void)
{
	// �T�E���h�n���h���̎擾
	auto softSoundHandle = lpSoundSet.GetSouftSoundHandle();

	// �X�y�N�g���`��
	// ���݂̍Đ��ʒu������g�����z�𓾂�
	// ���݂̃T�E���h�n���h���̎擾
	auto soundHande = lpSoundSet.GetSoundHandle();
	// ���݂̍Đ��ʒu���擾
	auto samplePos = GetCurrentPositionSoundMem(soundHande);
	// FFT�ɂ����g�����z���擾
	GetFFTVibrationSoftSound(softSoundHandle, -1, samplePos, fftSampleNum_, paramList.data(), fftSampleNum_);

	// ���g�����z����ʂ�`�悷��
	int x = -1;
	int j = 0;

	// ���̊Ԋu
	int offset = 15;
	// �T���v�������������s��
	for (int a = 0; a < fftSampleNum_; a++)
	{
		// �ΐ��������łȂ��ꍇ�̂ݒl��ς���
		auto log = static_cast<int>((log10(static_cast<double>(a)) * 10));
		if (log != x)
		{
			// �`��ʒu
			j++;

			// �����ɑ΂���log�őΐ����Ƃ�
			x = static_cast<int>((log10((double)a) * 10));

			// �p�����[�^�[
			float Param;

			// �֐�����擾�ł���l��`��ɓK�����l�ɒ���
			Param = pow(paramList[a], 0.5f) * 0.8f;

			// �U���X�y�N�g���̕`��(�E���ɂ��炵�ĕ`��j
			DrawBox(((screen_w_ / 2) + 50) + j * offset, screen_h_ - (int)(Param * screen_h_), ((screen_w_ / 2) + 50) + j * offset + 4, screen_h_, 0x00ff00, true);
		}
	}
}
