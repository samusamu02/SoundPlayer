#include <DxLib.h>
#include <thread>
#include "GenelateEffectScene.h"
#include "SoundPlayScene.h"

GenelateEffectScene::GenelateEffectScene()
{
	Init();
	DrawOwnScreen();
}

GenelateEffectScene::~GenelateEffectScene()
{
}

void GenelateEffectScene::Init(void)
{
	// �e�I�u�W�F�N�g�C���X�^���X
	pitchUp_ = std::make_unique<PitchUp>();
	pitchDown_ = std::make_unique<PitchDown>();
	wah_ = std::make_unique<Wah>();
	reverb_ = std::make_unique<Reverb>();
	equalizer_ = std::make_unique<Equalizer>();

	// ���݂̃��j���[�Z���N�g�̏��
	nowSelect_ = static_cast<int>(Effect::PitchUp);
}

uniqueBase GenelateEffectScene::Update(uniqueBase ownScene)
{
	DrawOwnScreen();

	// �Z���N�g�̏�Ԃ̕ω�
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		// �Z���N�g���������
		nowSelect_ = (nowSelect_ + 1) % static_cast<int>(Effect::Max);
	}

	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		// �Z���N�g����グ��
		nowSelect_ = (nowSelect_ + (static_cast<int>(Effect::Max) - 1)) % static_cast<int>(Effect::Max);
	}

	// �֐��I�u�W�F�N�g
	EffectFunc effects[static_cast<int>(Effect::Max)] =
	{
		[&] {pitchUp_->GenelatePitchShiftWaveFile(0.8, soundFile_.beforeFileName, soundFile_.afterFilenName); },
		[&] {pitchDown_->GenelatePitchShiftWaveFile(1.2, soundFile_.beforeFileName, soundFile_.afterFilenName); },
		[&] {wah_->GenelateWahWaveFile(soundFile_.beforeFileName, soundFile_.afterFilenName); },
		[&] {reverb_->GenelateReverbWaveFile(soundFile_.beforeFileName, soundFile_.afterFilenName); },
		[&] {equalizer_->GenelateEquaLizerWaveFile(soundFile_.beforeFileName, soundFile_.afterFilenName); }
	};

	// �ʃX���b�h�Ƃ��ď���
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		std::thread thred(effects[nowSelect_]);
		thred.join();
		if (thred.joinable() == false)
		{
			return std::make_unique<SoundPlayScene>();
		}
	}

	return ownScene;
}

void GenelateEffectScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	int y = 0;

	DrawFormatString(280, pitchUpY_, 0xffffff, L"�s�b�`�A�b�v");
	DrawFormatString(280, pitchDownY_, 0xffffff, L"�s�b�`�_�E��");
	DrawFormatString(280, wahY_, 0xffffff, L"���E");
	DrawFormatString(280, reverbY_, 0xffffff, L"���o�[�u");
	DrawFormatString(280, equalizerY_, 0xffffff, L"�C�R���C�U�[");

	switch (nowSelect_)
	{
	case static_cast<int>(Effect::PitchUp):
		y = pitchUpY_;
		break;
	case static_cast<int>(Effect::PitchDown):
		y = pitchDownY_;
		break;
	case static_cast<int>(Effect::Wah):
		y = wahY_;
		break;
	case static_cast<int>(Effect::Reverb):
		y = reverbY_;
		break;
	case static_cast<int>(Effect::Equalizer):
		y = equalizerY_;
		break;
	default:
		break;
	}

	DrawFormatString(250, y, 0xffffff, L"��");
}
