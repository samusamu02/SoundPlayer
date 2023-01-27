#include <DxLib.h>
#include "DrawBG.h"

DrawBG::DrawBG()
{
}

DrawBG::~DrawBG()
{
}

void DrawBG::Draw(void)
{
	// 画面のセンターライン
	DrawLine(SCREEN_W / 2, 0, SCREEN_W / 2, SCREEN_W, 0xffffff);

	// 左チャンネルと右チャンネルを区切るラインを描画
	DrawLine(0, SCREEN_H / 2, SCREEN_W / 2, SCREEN_H / 2, 0xffffff);

	// 左チャンネルと右チャンネルのセンターラインを描画
	DrawLine(0, SCREEN_H / 4, SCREEN_W / 2, SCREEN_H / 4,0x0000ff);
	DrawLine(0, SCREEN_H - SCREEN_H / 4, SCREEN_W / 2, SCREEN_H - SCREEN_H / 4,0x0000ff);
}
