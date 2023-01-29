#include "DrawBG.h"
#include "../../Scene/SceneMag.h"
DrawBG::DrawBG()
{
}

DrawBG::~DrawBG()
{
}

void DrawBG::Draw(void)
{
	// 画面のセンターライン

	auto screen_w = lpScenMag.GetSCREEN_W();
	auto screen_h = lpScenMag.GetSCREEN_H();

	DrawLine(screen_w / 2, 0, screen_w / 2, screen_w, 0xffffff);

	// 左チャンネルと右チャンネルを区切るラインを描画
	DrawLine(0, screen_h / 2, screen_w / 2, screen_h / 2, GetColor(0, 0, 0));

	// 左チャンネルと右チャンネルのセンターラインを描画
	DrawLine(0, screen_h / 4, screen_w / 2, screen_h / 4, GetColor(0, 0, 255));
	DrawLine(0, screen_h - screen_h / 4, screen_w / 2, screen_h - screen_h / 4, GetColor(0, 0, 255));
}
