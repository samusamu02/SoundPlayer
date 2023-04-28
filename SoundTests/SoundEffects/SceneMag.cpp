#include <DxLib.h>
#include "SceneMag.h"
#include "Scene/SoundSelectScene.h"


// スクリーンの大きさ
constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;

void SceneMag::Run()
{
	// システムが初期化できていなかったら処理を行わない
	if (!sysInit_)
	{
		if (!SysInit())
		{
			return;
		}
	}

	// サウンドオブジェクト管理クラスのインスタンス
	scene_ = std::make_unique<SoundSelectScene>();

	// メインループ
	while (ProcessMessage() == 0)
	{
		// サウンドオブジェクト管理クラスの更新関数呼び出し
		scene_ = scene_->Update(std::move(scene_));

		// 描画先を裏画面に変更
		SetDrawScreen(DX_SCREEN_BACK);

		// 画面を消去
		ClearDrawScreen();

		// 	// サウンドオブジェクト管理クラスの描画関数呼び出し
		scene_->Draw();

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	//Dxlibの終了
	DxLib_End();
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

	SetWindowText(L"サウンドエフェクト研究");

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return false;
	}

	return true;
}

int SceneMag::GetScreen_H(void)
{
	return SCREEN_H;
}

int SceneMag::GetScreen_W(void)
{
	return SCREEN_W;
}

SceneMag::SceneMag()
{
	// システムの状態の取得
	sysInit_ = SysInit();
}

SceneMag::~SceneMag()
{
	// 処理なし
}
