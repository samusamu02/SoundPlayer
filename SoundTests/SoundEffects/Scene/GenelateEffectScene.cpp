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
		// 各オブジェクトインスタンス
		pitchUp_ = std::make_unique<PitchUp>();
		pitchDown_ = std::make_unique<PitchDown>();
		wah_ = std::make_unique<Wah>();
		reverb_ = std::make_unique<Reverb>();
		equalizer_ = std::make_unique<Equalizer>();

		// 現在のメニューセレクトの状態
		nowSelect_ = static_cast<int>(Effect::PitchUp);

		// それぞれの文字列の位置
		selecterPosX_ = 20;		// セレクターの文字列の位置
		stringPosX_ = 40;		// エフェクトの文字列の共通の位置X

		pitchUpPosY_ = 100;		// ピッチアップの文字列の位置Y
		pitchDownPosY_ = 140;	// ピッチダウンの文字列の位置Y
		wahPosY_ = 180;			// ワウの文字列の位置Y
		reverbPosY_ = 220;		// リバーブの文字列の位置Y
		equalizerPosY_ = 260;	// イコライザーの文字列の位置Y
	}

	uniqueBase GenelateEffectScene::Update(uniqueBase ownScene)
	{
		DrawOwnScreen();

		// セレクトの状態の変化
		if (CheckHitKey(KEY_INPUT_DOWN) == 1)
		{
			// セレクトを一つ下げる
			nowSelect_ = (nowSelect_ + 1) % static_cast<int>(Effect::Max);
		}

		if (CheckHitKey(KEY_INPUT_UP) == 1)
		{
			// セレクトを一つ上げる
			nowSelect_ = (nowSelect_ + (static_cast<int>(Effect::Max) - 1)) % static_cast<int>(Effect::Max);
		}

		// 関数オブジェクト
		EffectFunc effects[static_cast<int>(Effect::Max)] =
		{
			[&] {pitchUp_->GenelatePitchShiftWaveFile(0.8, soundFile_.beforeFileName, soundFile_.afterFilenName); },
			[&] {pitchDown_->GenelatePitchShiftWaveFile(1.2, soundFile_.beforeFileName, soundFile_.afterFilenName); },
			[&] {wah_->GenelateWahWaveFile(soundFile_.beforeFileName, soundFile_.afterFilenName); },
			[&] {reverb_->GenelateReverbWaveFile(soundFile_.beforeFileName, soundFile_.afterFilenName); },
			[&] {equalizer_->GenelateEquaLizerWaveFile(soundFile_.beforeFileName, soundFile_.afterFilenName); }
		};

		// 別スレッドとして処理
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

		DrawFormatString(0, 0, 0xffffff, L"エフェクトを選択してください");

		// y座標
		int y = 0;

		// セレクターフォント
		DrawFormatString(stringPosX_, pitchUpPosY_, 0xffffff, L"ピッチアップ");
		DrawFormatString(stringPosX_, pitchDownPosY_, 0xffffff, L"ピッチダウン");
		DrawFormatString(stringPosX_, wahPosY_, 0xffffff, L"ワウ");
		DrawFormatString(stringPosX_, reverbPosY_, 0xffffff, L"リバーブ");
		DrawFormatString(stringPosX_, equalizerPosY_, 0xffffff, L"イコライザー");

		// 状態によりyの変える
		switch (nowSelect_)
		{
		case static_cast<int>(Effect::PitchUp):
			y = pitchUpPosY_;
			break;
		case static_cast<int>(Effect::PitchDown):
			y = pitchDownPosY_;
			break;
		case static_cast<int>(Effect::Wah):
			y = wahPosY_;
			break;
		case static_cast<int>(Effect::Reverb):
			y = reverbPosY_;
			break;
		case static_cast<int>(Effect::Equalizer):
			y = equalizerPosY_;
			break;
		default:
			break;
		}
		DrawFormatString(selecterPosX_, y, 0xffffff, L"■");
	}
