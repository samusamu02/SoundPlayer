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

	// ������
	virtual void Init() = 0;

	/// <summary>
	/// �X�V�����i���̃V�[���֑���)
	/// </summary>
	/// <param name="ownScene">�����̃V�[�����</param>
	/// <returns>�����̃V�[������Ԃ�</returns>
	virtual uniqueBase Update(uniqueBase ownScene) = 0;

	// �`�揈��
	virtual void Draw();

	// �����̃V�[���ł̕`�揈��
	virtual void DrawOwnScreen() = 0;

	// �V�[�����擾
	virtual SceneID GetSceneID(void) = 0;
protected:
	// �X�N���[�����
	int screenID_;
private:

};

