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
	// �T���v�������v�f�����m�ۂ���
	paramList.resize(sampleNum_);

	// FFT�̃T���v����
	fftSampleNum_ = 4096;
}

void DrawSpectrum::Update(void)
{
}

void DrawSpectrum::Draw(void)
{
	// �X�N���[���T�C�Y
	auto screen_w = lpScenMag.GetSCREEN_W();	// ��
	auto screen_h = lpScenMag.GetSCREEN_H();	// �L��

	// �X�y�N�g���`��
	// ���݂̍Đ��ʒu������g�����z�𓾂�
	GetFFTVibrationSoftSound(softSoundHandle_, -1, samplePos_, fftSampleNum_, paramList.data(), fftSampleNum_);

	// ���g�����z����ʂ�`�悷��
	int x = -1;
	int j = 0;

	// ���̊Ԋu
	int offset = 15;
	// �T���v�������������s��
	for (int a = 0; a < fftSampleNum_; a++)
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
			DrawBox(((screen_w / 2) + 50) + j * offset, screen_h - (int)(Param * screen_h), ((screen_w / 2) + 50) + j * offset + 4, screen_h, 0x00ff00, true);
		}
	}
}
