#include <DxLib.h>
#include <thread>
#include "../SceneMag.h"
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
	// �e�I�u�W�F�N�̃g�C���X�^���X
	pitchUp_ = std::make_unique<PitchUp>();
	pitchDown_ = std::make_unique<PitchDown>();
	wah_ = std::make_unique<Wah>();
	reverb_ = std::make_unique<Reverb>();
	equalizer_ = std::make_unique<Equalizer>();

	time_ = 0.0;

	Init_Select();
	Init_EffectNames();
	Init_StringPos();
	Init_Image();
}

void GenelateEffectScene::Init_Select(void)
{
	// ���݂̃��j���[�Z���N�g�̏��
	nowSelect_ = static_cast<int>(Effect::PitchUp);

	// �L�[�ƃG�t�F�N�g�̊Ǘ�
	keyEffects_ =
	{
		{KEY_INPUT_1,Effect::PitchUp},
		{KEY_INPUT_2,Effect::PitchDown},
		{KEY_INPUT_3,Effect::Wah},
		{KEY_INPUT_4,Effect::Reverb},
		{KEY_INPUT_5,Effect::Equalizer_Base},
		{KEY_INPUT_6,Effect::Equalizer_Middle},
		{KEY_INPUT_7,Effect::Equalizer_Treble},
	};
}

void GenelateEffectScene::Init_EffectNames(void)
{
	// �G�t�F�N�g��
	effectNames_ =
	{
		L"1.�s�b�`�A�b�v",
		L"2.�s�b�`�_�E��",
		L"3.���E",
		L"4.���o�[�u",
		L"5.�C�R���C�U�[ (�ቹ�����グ)",
		L"6.�C�R���C�U�[ (���������グ)",
		L"7.�C�R���C�U�[ (���������グ)"
	};
}

void GenelateEffectScene::Init_StringPos(void)
{
	// ���ꂼ��̕�����̈ʒu
	// X���W
	selecterPosX_ = 20;				// �Z���N�^�[�̕�����̈ʒu
	stringPosX_ = 40;				// �G�t�F�N�g�̕�����̋��ʂ̈ʒuX

	// Y���W
	// ���ꂼ���Y���W���i�[
	y_Coordinates_ =
	{
		pitchUpPosY_ = 100,					// �s�b�`�A�b�v�̕�����̈ʒuY
		pitchDownPosY_ = 140,				// �s�b�`�_�E���̕�����̈ʒuY
		wahPosY_ = 180,						// ���E�̕�����̈ʒuY
		reverbPosY_ = 220,					// ���o�[�u�̕�����̈ʒuY
		equalizerPosY_Bass_ = 260,			// �C�R���C�U�[(�ቹ)�̕�����̈ʒuY
		equalizerPosY_Middle_ = 300,		// �C�R���C�U�[(����)�̕�����̈ʒuY
		equalizerPosY_Treble_ = 340,		// �C�R���C�U�[(����)�̕�����̈ʒuY
	};

	// �Z���N�^�[��Y���W
	selecterPosY_ = pitchUpPosY_;
}

void GenelateEffectScene::Init_Image(void)
{
	// �摜�̃��[�h
	loadingImg_ = LoadGraph(L"image/loading.png");

	// �摜�̍��W
	auto screenSizeX = lpScenMag.GetScreen_W();
	auto screenSizeY = lpScenMag.GetScreen_H();
	imagPosX_ = screenSizeX - 60;
	imagPosY_ = screenSizeY - 60;

	// �g�嗦
	rate_ = 0.1;

	// ��]
	angele_ = 1.0;
	angleSpeed_ = 0.05;
}

uniqueBase GenelateEffectScene::Update(uniqueBase ownScene)
{
	DrawOwnScreen();

	// �I�����ڂ̏�Ԃ̍X�V
	ChangeSelect();

	// �֐��I�u�W�F�N�g
	EffectFunc effects[static_cast<int>(Effect::Max)] =
	{
		[&] {pitchUp_->GenelatePitchShiftWaveFile(0.8, soundFile_.beforeFileName, soundFile_.afterFilenName); },
		[&] {pitchDown_->GenelatePitchShiftWaveFile(1.2, soundFile_.beforeFileName, soundFile_.afterFilenName); },
		[&] {wah_->GenelateWahWaveFile(soundFile_.beforeFileName, soundFile_.afterFilenName); },
		[&] {reverb_->GenelateReverbWaveFile(soundFile_.beforeFileName, soundFile_.afterFilenName); },
		[&] {equalizer_->GenelateEquaLizerWaveFile(10,50,100,soundFile_.beforeFileName, soundFile_.afterFilenName); },
		[&] {equalizer_->GenelateEquaLizerWaveFile(500,1000,3000,soundFile_.beforeFileName, soundFile_.afterFilenName); },
		[&] {equalizer_->GenelateEquaLizerWaveFile(4000,4500,5000,soundFile_.beforeFileName, soundFile_.afterFilenName); }
	};

	// �G���^�[�������ꂽ�玟�̃V�[����
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		// �ʃX���b�h�Ƃ��ď���
		std::thread thred(effects[nowSelect_]);
		thred.join();
		if (thred.joinable() == false)
		{
			return std::make_unique<SoundPlayScene>();
		}
	}

	// �摜�̉�]
	angele_ += angleSpeed_;

	return ownScene;
}

void GenelateEffectScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	DrawFormatString(0, 0, 0xffffff, L"�G�t�F�N�g��I�����Ă�������");
	DrawFormatString(0, 20, 0xffffff, L"1�`7�̃L�[�������āA�G���^�[�Ō��肵�܂�");

	// �G�t�F�N�g���̕`��
	for (int i = 0; i < effectNames_.size(); i++)
	{
		DrawFormatString(stringPosX_, y_Coordinates_[i], 0xffffff, effectNames_[i].c_str());
	}

	// �Z���N�^�[�`��
	selecterPosY_ = (nowSelect_ >= 0 && nowSelect_ < y_Coordinates_.size()) ? y_Coordinates_[nowSelect_] : 0;
	DrawFormatString(selecterPosX_, selecterPosY_, 0xffffff, L"��");

	// ���[�h�摜�̕`��
	DrawRotaGraph(imagPosX_, imagPosY_, rate_, angele_, loadingImg_, true);
}

void GenelateEffectScene::ChangeSelect(void)
{
	// �L�[���͂��������ꍇ�ɁA�Ή�����G�t�F�N�g�̑I�����ڂ�nowSelect_�ɕۑ�
	for (auto& key : keyEffects_)
	{
		if (CheckHitKey(key.first) != 0)
		{
			nowSelect_ = static_cast<int>(key.second);
		}
	}
}
