#include <DxLib.h>
#include "BaseScene.h"
#include "../SceneMag.h"

BaseScene::BaseScene()
{
	auto screenX = lpScenMag.GetScreen_W();
	auto screenY = lpScenMag.GetScreen_H();
	SetDrawScreen(DX_SCREEN_BACK);										// �����I�Ƀo�b�N�o�b�t�@���w��
	GetDrawScreenSize(&screenX, &screenY);								// �`���̃T�C�Y���擾����(�o�b�t�@�j
	screenID_ = MakeScreen(screenX, screenY, true);						// �X�N���[���̃T�C�Y
}

BaseScene::~BaseScene()
{
}

void BaseScene::Draw()
{
	DrawGraph(0, 0, screenID_, true);
}
