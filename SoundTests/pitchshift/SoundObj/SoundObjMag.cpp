#include "SoundObjMag.h"

SoundObjMag::SoundObjMag()
{
	// インスタンス
	drawObjMag_ = std::make_unique<DrawObjMag>();
}

SoundObjMag::~SoundObjMag()
{
	// 処理なし
}

void SoundObjMag::Init(void)
{
	// 描画管理クラスの初期化関数呼び出し
	drawObjMag_->Init();
}

void SoundObjMag::Update(void)
{
	// 描画管理クラスの更新関数呼び出し
	drawObjMag_->Update();
}

void SoundObjMag::Draw(void)
{
	// 描画管理クラスの描画関数呼び出し
	drawObjMag_->Draw();
}
