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
	// ��ʂ̃Z���^�[���C��
	DrawLine(SCREEN_W / 2, 0, SCREEN_W / 2, SCREEN_W, 0xffffff);

	// ���`�����l���ƉE�`�����l������؂郉�C����`��
	DrawLine(0, SCREEN_H / 2, SCREEN_W / 2, SCREEN_H / 2, 0xffffff);

	// ���`�����l���ƉE�`�����l���̃Z���^�[���C����`��
	DrawLine(0, SCREEN_H / 4, SCREEN_W / 2, SCREEN_H / 4,0x0000ff);
	DrawLine(0, SCREEN_H - SCREEN_H / 4, SCREEN_W / 2, SCREEN_H - SCREEN_H / 4,0x0000ff);
}
