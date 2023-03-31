#include <DxLib.h>
#include "BaseScene.h"
#include "../SceneMag.h"

BaseScene::BaseScene()
{
	auto screenX = lpScenMag.GetScreen_W();
	auto screenY = lpScenMag.GetScreen_H();

	// 明示的にバックバッファを指定
	SetDrawScreen(DX_SCREEN_BACK);		

	// 描画先のサイズを取得する(バッファ）
	GetDrawScreenSize(&screenX, &screenY);	

	// スクリーンのサイズ
	screenID_ = MakeScreen(screenX, screenY, true);						
}

BaseScene::~BaseScene()
{
}

void BaseScene::Draw()
{
	// スクリーンの描画
	DrawGraph(0, 0, screenID_, true);
}
