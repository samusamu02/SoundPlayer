#include "DrawBG.h"
#include "../../SceneMag.h"

DrawBG::DrawBG()
{
}

DrawBG::~DrawBG()
{
	// �����Ȃ�
}

void DrawBG::Init(void)
{
	// �X�N���[���̍L��
	screen_w = lpScenMag.GetScreen_W();	// ��
	screen_h = lpScenMag.GetScreen_H();	// ����
}

void DrawBG::Update(void)
{
	// �����Ȃ�
}

void DrawBG::Draw(void)
{
	// ��ʂ̃Z���^�[���C��
	DrawLine(screen_w / 2, 0, screen_w / 2, screen_w, 0xffffff);

	// ���`�����l���ƉE�`�����l������؂郉�C����`��
	DrawLine(0, screen_h / 2, screen_w / 2, screen_h / 2, 0x000000);

	// ���`�����l���ƉE�`�����l���̃Z���^�[���C����`��
	DrawLine(0, screen_h / 4, screen_w / 2, screen_h / 4, 0x0000ff);
	DrawLine(0, screen_h - screen_h / 4, screen_w / 2, screen_h - screen_h / 4, 0x0000ff);
}
