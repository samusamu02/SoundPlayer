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
	// 各オブジェクのトインスタンス
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
	// 現在のメニューセレクトの状態
	nowSelect_ = static_cast<int>(Effect::PitchUp);

	// キーとエフェクトの管理
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
	// エフェクト名
	effectNames_ =
	{
		L"1.ピッチアップ",
		L"2.ピッチダウン",
		L"3.ワウ",
		L"4.リバーブ",
		L"5.イコライザー (低音引き上げ)",
		L"6.イコライザー (中音引き上げ)",
		L"7.イコライザー (高音引き上げ)"
	};
}

void GenelateEffectScene::Init_StringPos(void)
{
	// それぞれの文字列の位置
	// X座標
	selecterPosX_ = 20;				// セレクターの文字列の位置
	stringPosX_ = 40;				// エフェクトの文字列の共通の位置X

	// Y座標
	// それぞれのY座標を格納
	y_Coordinates_ =
	{
		pitchUpPosY_ = 100,					// ピッチアップの文字列の位置Y
		pitchDownPosY_ = 140,				// ピッチダウンの文字列の位置Y
		wahPosY_ = 180,						// ワウの文字列の位置Y
		reverbPosY_ = 220,					// リバーブの文字列の位置Y
		equalizerPosY_Bass_ = 260,			// イコライザー(低音)の文字列の位置Y
		equalizerPosY_Middle_ = 300,		// イコライザー(中音)の文字列の位置Y
		equalizerPosY_Treble_ = 340,		// イコライザー(高音)の文字列の位置Y
	};

	// セレクターのY座標
	selecterPosY_ = pitchUpPosY_;
}

void GenelateEffectScene::Init_Image(void)
{
	// 画像のロード
	loadingImg_ = LoadGraph(L"image/loading.png");

	// 画像の座標
	auto screenSizeX = lpScenMag.GetScreen_W();
	auto screenSizeY = lpScenMag.GetScreen_H();
	imagPosX_ = screenSizeX - 60;
	imagPosY_ = screenSizeY - 60;

	// 拡大率
	rate_ = 0.1;

	// 回転
	angele_ = 1.0;
	angleSpeed_ = 0.05;
}

uniqueBase GenelateEffectScene::Update(uniqueBase ownScene)
{
	DrawOwnScreen();

	// 選択項目の状態の更新
	ChangeSelect();

	// 関数オブジェクト
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

	// 画像の回転
	angele_ += angleSpeed_;

	return ownScene;
}

void GenelateEffectScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	DrawFormatString(0, 0, 0xffffff, L"エフェクトを選択してください");
	DrawFormatString(0, 20, 0xffffff, L"1～7のキーを押して、エンターで決定します");

	// エフェクト名の描画
	for (int i = 0; i < effectNames_.size(); i++)
	{
		DrawFormatString(stringPosX_, y_Coordinates_[i], 0xffffff, effectNames_[i].c_str());
	}

	// セレクター描画
	selecterPosY_ = (nowSelect_ >= 0 && nowSelect_ < y_Coordinates_.size()) ? y_Coordinates_[nowSelect_] : 0;
	DrawFormatString(selecterPosX_, selecterPosY_, 0xffffff, L"■");

	// ロード画像の描画
	DrawRotaGraph(imagPosX_, imagPosY_, rate_, angele_, loadingImg_, true);
}

void GenelateEffectScene::ChangeSelect(void)
{
	// キー入力があった場合に、対応するエフェクトの選択項目をnowSelect_に保存
	for (auto& key : keyEffects_)
	{
		if (CheckHitKey(key.first) != 0)
		{
			nowSelect_ = static_cast<int>(key.second);
		}
	}
}
