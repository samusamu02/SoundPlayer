#pragma once
#include <memory>
#include "SceneID.h"

// �G���[�΍�
class BaseScene;
using uniqueBase = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual void Init() = 0;
	virtual uniqueBase Update(uniqueBase ownScene) = 0;
	virtual void Draw();
	virtual void DrawOwnScreen() = 0;
	virtual SceneID GetSceneID(void) = 0;
protected:
	// �X�N���[�����
	int screenID_;
private:

};

