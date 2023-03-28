#include <DxLib.h>
#include "SoundPlayScene.h"
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
}

uniqueBase SoundPlayScene::Update(uniqueBase ownScene)
{
	// 更新処理
	soundObjMag_->Update();

	// 描画処理
	DrawOwnScreen();

	// 自分のシーンを返す
	return ownScene;
}

void SoundPlayScene::DrawOwnScreen(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	// サウンドオブジェクトの描画処理
	soundObjMag_->Draw();
}
