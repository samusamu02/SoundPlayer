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
		// 各オブジェクのトインスタンス
		pitchUp_ = std::make_unique<PitchUp>();
		pitchDown_ = std::make_unique<PitchDown>();
		wah_ = std::make_unique<Wah>();
		reverb_ = std::make_unique<Reverb>();
		equalizer_ = std::make_unique<Equalizer>();

		// 現在のメニューセレクトの状態
		nowSelect_ = static_cast<int>(Effect::PitchUp);

		// それぞれの文字列の位置
		selecterPosX_ = 20;			// セレクターの文字列の位置
		stringPosX_ = 40;			// エフェクトの文字列の共通の位置X

		pitchUpPosY_ = 100;				// ピッチアップの文字列の位置Y
		pitchDownPosY_ = 140;			// ピッチダウンの文字列の位置Y
		wahPosY_ = 180;					// ワウの文字列の位置Y
		reverbPosY_ = 220;				// リバーブの文字列の位置Y
		equalizerPosY_Bass_ = 260;		// イコライザー(低音)の文字列の位置Y
		equalizerPosY_Middle_ = 300;	// イコライザー(中音)の文字列の位置Y
		equalizerPosY_Treble_ = 340;	// イコライザー(高音)の文字列の位置Y

		// それぞれのY座標を格納
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
			[&] {equalizer_->GenelateEquaLizerWaveFile(10,50,100,soundFile_.beforeFileName, soundFile_.afterFilenName); },
			[&] {equalizer_->GenelateEquaLizerWaveFile(500,1000,1500,soundFile_.beforeFileName, soundFile_.afterFilenName); },
			[&] {equalizer_->GenelateEquaLizerWaveFile(4000,4500,5000,soundFile_.beforeFileName, soundFile_.afterFilenName); }

		};

		// エンターが押されたら次のシーンへ
		if (CheckHitKey(KEY_INPUT_RETURN))
		{
			// 別スレッドとして処理
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

		// セレクターフォント
		DrawFormatString(stringPosX_, pitchUpPosY_, 0xffffff, L"ピッチアップ");
		DrawFormatString(stringPosX_, pitchDownPosY_, 0xffffff, L"ピッチダウン");
		DrawFormatString(stringPosX_, wahPosY_, 0xffffff, L"ワウ");
		DrawFormatString(stringPosX_, reverbPosY_, 0xffffff, L"リバーブ");
		DrawFormatString(stringPosX_, equalizerPosY_Bass_, 0xffffff, L"イコライザー (低音引き上げ)");
		DrawFormatString(stringPosX_, equalizerPosY_Middle_, 0xffffff, L"イコライザー (中音引き上げ)");
		DrawFormatString(stringPosX_, equalizerPosY_Treble_, 0xffffff, L"イコライザー (高音引き上げ)");

		// y座標
		int y = 0;
		if (nowSelect_ >= 0 && nowSelect_ < y_Coordinates_.size())
		{
			// 現在の座標を代入
			y = y_Coordinates_[nowSelect_];
		}

		// セレクター描画
		DrawFormatString(selecterPosX_, y, 0xffffff, L"■");
	}
