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
		// �e�I�u�W�F�N�̃g�C���X�^���X
		pitchUp_ = std::make_unique<PitchUp>();
		pitchDown_ = std::make_unique<PitchDown>();
		wah_ = std::make_unique<Wah>();
		reverb_ = std::make_unique<Reverb>();
		equalizer_ = std::make_unique<Equalizer>();

		// ���݂̃��j���[�Z���N�g�̏��
		nowSelect_ = static_cast<int>(Effect::PitchUp);

		// ���ꂼ��̕�����̈ʒu
		selecterPosX_ = 20;			// �Z���N�^�[�̕�����̈ʒu
		stringPosX_ = 40;			// �G�t�F�N�g�̕�����̋��ʂ̈ʒuX

		pitchUpPosY_ = 100;				// �s�b�`�A�b�v�̕�����̈ʒuY
		pitchDownPosY_ = 140;			// �s�b�`�_�E���̕�����̈ʒuY
		wahPosY_ = 180;					// ���E�̕�����̈ʒuY
		reverbPosY_ = 220;				// ���o�[�u�̕�����̈ʒuY
		equalizerPosY_Bass_ = 260;		// �C�R���C�U�[(�ቹ)�̕�����̈ʒuY
		equalizerPosY_Middle_ = 300;	// �C�R���C�U�[(����)�̕�����̈ʒuY
		equalizerPosY_Treble_ = 340;	// �C�R���C�U�[(����)�̕�����̈ʒuY

		// ���ꂼ���Y���W���i�[
		y_Coordinates_ =
		{
			pitchUpPosY_,
			pitchDownPosY_,
			wahPosY_,
			reverbPosY_,
			equalizerPosY_Bass_,
			equalizerPosY_Middle_,
			equalizerPosY_Treble_
		};
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
			[&] {equalizer_->GenelateEquaLizerWaveFile(10,50,100,soundFile_.beforeFileName, soundFile_.afterFilenName); },
			[&] {equalizer_->GenelateEquaLizerWaveFile(500,1000,1500,soundFile_.beforeFileName, soundFile_.afterFilenName); },
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

		return ownScene;
	}

	void GenelateEffectScene::DrawOwnScreen(void)
	{
		SetDrawScreen(screenID_);
		ClsDrawScreen();

		DrawFormatString(0, 0, 0xffffff, L"�G�t�F�N�g��I�����Ă�������");

		// �Z���N�^�[�t�H���g
		DrawFormatString(stringPosX_, pitchUpPosY_, 0xffffff, L"�s�b�`�A�b�v");
		DrawFormatString(stringPosX_, pitchDownPosY_, 0xffffff, L"�s�b�`�_�E��");
		DrawFormatString(stringPosX_, wahPosY_, 0xffffff, L"���E");
		DrawFormatString(stringPosX_, reverbPosY_, 0xffffff, L"���o�[�u");
		DrawFormatString(stringPosX_, equalizerPosY_Bass_, 0xffffff, L"�C�R���C�U�[ (�ቹ�����グ)");
		DrawFormatString(stringPosX_, equalizerPosY_Middle_, 0xffffff, L"�C�R���C�U�[ (���������グ)");
		DrawFormatString(stringPosX_, equalizerPosY_Treble_, 0xffffff, L"�C�R���C�U�[ (���������グ)");

		// y���W
		int y = 0;
		if (nowSelect_ >= 0 && nowSelect_ < y_Coordinates_.size())
		{
			// ���݂̍��W����
			y = y_Coordinates_[nowSelect_];
		}

		// �Z���N�^�[�`��
		DrawFormatString(selecterPosX_, y, 0xffffff, L"��");
	}
