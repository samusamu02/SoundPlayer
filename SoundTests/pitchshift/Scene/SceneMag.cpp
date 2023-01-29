#include <DxLib.h>
#include "SceneMag.h"
#include <vector>
#include <shlobj.h>
#include <string>
#include <memory>
#include "../PCM/PitchUp.h"
#include "../Wave/Wave.h"
#include "../Scene/SceneMag.h"

// スクリーンの大きさ
constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;


void SceneMag::Run()
{
	if (!sysInit_)
	{
		if (!SysInit())
		{
			return;
		}
	}

	soundObjMag_ = std::make_unique<SoundObjeMag>();

	// 初期化
	soundObjMag_->Init();

	// メインループ
	while (ProcessMessage() == 0)
	{
		// サウンドのオブジェクトの更新関数を呼ぶ
		soundObjMag_->Upadate();

		// キー操作
		soundCtl_->SoundPlay();

		// 描画先を裏画面に変更
		SetDrawScreen(DX_SCREEN_BACK);

		// 画面を消去
		ClearDrawScreen();

		// サウンドの描画関数を呼ぶ
		soundObjMag_->Draw();

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// ＤＸライブラリの後始末
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
	// ウインドウモードに変更
	ChangeWindowMode(true);

	// 画面解像度を設定
	SetGraphMode(SCREEN_W, SCREEN_H, 32);

	// 背景色を灰色に設定
	SetBackgroundColor(64, 64, 64);

	// バックグラウンド
	SetAlwaysRunFlag(true);

	// アイコンの生成
	SetWindowIconID(001);

	SetWindowText(L"ピッチアップ変更テスト");

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return false;
	}

	return true;
}

SceneMag::SceneMag()
{
	// 初期化状態を受け取る
	sysInit_ = SysInit();
}

SceneMag::~SceneMag()
{

}
