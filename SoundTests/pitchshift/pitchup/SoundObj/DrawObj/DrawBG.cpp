#include "DrawBG.h"
#include "../../SceneMag.h"

DrawBG::DrawBG()
{
}

DrawBG::~DrawBG()
{
	// 処理なし
}

void DrawBG::Init(void)
{
	// スクリーンの広さ
	screen_w = lpScenMag.GetScreen_W();	// 幅
	screen_h = lpScenMag.GetScreen_H();	// 高さ
}

void DrawBG::Update(void)
{
	// 処理なし
}

void DrawBG::Draw(void)
{
	// 画面のセンターライン
	DrawLine(screen_w / 2, 0, screen_w / 2, screen_w, 0xffffff);

	// 左チャンネルと右チャンネルを区切るラインを描画
	DrawLine(0, screen_h / 2, screen_w / 2, screen_h / 2, 0x000000);

	// 左チャンネルと右チャンネルのセンターラインを描画
	DrawLine(0, screen_h / 4, screen_w / 2, screen_h / 4, 0x0000ff);
	DrawLine(0, screen_h - screen_h / 4, screen_w / 2, screen_h - screen_h / 4, 0x0000ff);
}
