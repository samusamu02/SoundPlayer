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
	// ��ʂ̃Z���^�[���C��

	auto screen_w = lpScenMag.GetSCREEN_W();
	auto screen_h = lpScenMag.GetSCREEN_H();

	DrawLine(screen_w / 2, 0, screen_w / 2, screen_w, 0xffffff);

	// ���`�����l���ƉE�`�����l������؂郉�C����`��
	DrawLine(0, screen_h / 2, screen_w / 2, screen_h / 2, GetColor(0, 0, 0));

	// ���`�����l���ƉE�`�����l���̃Z���^�[���C����`��
	DrawLine(0, screen_h / 4, screen_w / 2, screen_h / 4, GetColor(0, 0, 255));
	DrawLine(0, screen_h - screen_h / 4, screen_w / 2, screen_h - screen_h / 4, GetColor(0, 0, 255));
}
