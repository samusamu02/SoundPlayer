#include "DrawBG.h"
#include "../../Scene/SceneMag.h"
DrawBG::DrawBG()
{
	// �����Ȃ�
}

DrawBG::~DrawBG()
{
	// �����Ȃ�
}

void DrawBG::Init(void)
{
	// �����Ȃ�
}

void DrawBG::Update(void)
{
	// �����Ȃ�
}

void DrawBG::Draw(void)
{
	// �X�N���[���T�C�Y
	auto screen_w = lpScenMag.GetSCREEN_W();	// ��
	auto screen_h = lpScenMag.GetSCREEN_H();	// ����

	// ��ʂ̃Z���^�[���C��
	DrawLine(screen_w / 2, 0, screen_w / 2, screen_w, 0xffffff);

	// ���`�����l���ƉE�`�����l������؂郉�C����`��
	DrawLine(0, screen_h / 2, screen_w / 2, screen_h / 2, GetColor(0, 0, 0));

	// ���`�����l���ƉE�`�����l���̃Z���^�[���C����`��
	DrawLine(0, screen_h / 4, screen_w / 2, screen_h / 4, GetColor(0, 0, 255));
	DrawLine(0, screen_h - screen_h / 4, screen_w / 2, screen_h - screen_h / 4, GetColor(0, 0, 255));
}
