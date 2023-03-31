#include <DxLib.h>
#include "BaseScene.h"
#include "../SceneMag.h"

BaseScene::BaseScene()
{
	auto screenX = lpScenMag.GetScreen_W();
	auto screenY = lpScenMag.GetScreen_H();

	// �����I�Ƀo�b�N�o�b�t�@���w��
	SetDrawScreen(DX_SCREEN_BACK);		

	// �`���̃T�C�Y���擾����(�o�b�t�@�j
	GetDrawScreenSize(&screenX, &screenY);	

	// �X�N���[���̃T�C�Y
	screenID_ = MakeScreen(screenX, screenY, true);						
}

BaseScene::~BaseScene()
{
}

void BaseScene::Draw()
{
	// �X�N���[���̕`��
	DrawGraph(0, 0, screenID_, true);
}
