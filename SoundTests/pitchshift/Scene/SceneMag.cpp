#include "SceneMag.h"
#include <DxLib.h>

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

	// サウンドオブジェクト管理クラスのインスタンス
	soundObjMag_ = std::make_unique<SoundObjMag>();

	// サウンドオブジェクト管理クラスの初期化関数呼び出し
	soundObjMag_->Init();

	// メインループ
	while (ProcessMessage() == 0)
	{
		// サウンドオブジェクト管理クラスの更新関数呼び出し
		soundObjMag_->Update();

		// 描画先を裏画面に変更
		SetDrawScreen(DX_SCREEN_BACK);

		// 画面を消去
		ClearDrawScreen();

		// 	// サウンドオブジェクト管理クラスの描画関数呼び出し
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
