#include <DxLib.h>
#include "BaseScene.h"
#include "../SceneMag.h"

BaseScene::BaseScene()
{
	auto screenX = lpScenMag.GetScreen_W();
	auto screenY = lpScenMag.GetScreen_H();
	SetDrawScreen(DX_SCREEN_BACK);										// 明示的にバックバッファを指定
	GetDrawScreenSize(&screenX, &screenY);								// 描画先のサイズを取得する(バッファ）
	screenID_ = MakeScreen(screenX, screenY, true);						// スクリーンのサイズ
}

BaseScene::~BaseScene()
{
}

void BaseScene::Draw()
{
	DrawGraph(0, 0, screenID_, true);
}
