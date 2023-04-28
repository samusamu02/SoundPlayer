#include <DxLib.h>
#include "SoundPlayScene.h"
#include "SoundSelectScene.h"

SoundPlayScene::SoundPlayScene()
{
	// インスタンス
	soundObjMag_ = std::make_unique<SoundObjMag>();

	Init();

	DrawOwnScreen();
}

SoundPlayScene::~SoundPlayScene()
{

}

void SoundPlayScene::Init(void)
{
	// 初期化処理
	soundObjMag_->Init();

	// サウンドの再生
	auto soundHandle = lpSoundSet.GetSoundHandle();
	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);

	// フラグの初期化
	viewFlag_ = true;
}

uniqueBase SoundPlayScene::Update(uniqueBase ownScene)
{
	// 更新処理
	soundObjMag_->Update();

	// 描画処理
	DrawOwnScreen();

	// スペースが押されたら元のシーンにもどる
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// メモリにあるサウンドデータの削除
		auto soundHandle = lpSoundSet.GetSoundHandle();
		DeleteSoundMem(soundHandle);

		// 最初のシーンに戻る
		return std::make_unique<SoundSelectScene>();
	}

	// 右キーが押されたフラグをfalseにする
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		viewFlag_ = false;
	}

	// 自分のシーンを返す
	return ownScene;
}

void SoundPlayScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	// サウンドオブジェクトの描画処理
	soundObjMag_->Draw();

	// y座標
	int y = 0;

	if (viewFlag_ == true)
	{
		DrawFormatString(10, y, 0xffffff, L"右キーを入力するとエフェクト適用後のサウンドファイルを再生できます");
	}

	// フラグの状態によりy座標を変える
	DrawFormatString(10,viewFlag_ ? 30 : y, 0xffffff, L"スペースキーを入力すると最初のシーンに戻ります");
}
