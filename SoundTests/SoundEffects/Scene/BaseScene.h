#pragma once
#include <memory>
#include "SceneID.h"

// �G���[�΍�
class BaseScene;

// ���N���X��ۑ�
using uniqueBase = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	// ������
	virtual void Init(void) = 0;

	/// <summary>
	/// �X�V�����i���̃V�[���֑���)
	/// </summary>
	/// <param name="ownScene">�����̃V�[�����</param>
	/// <returns>�����̃V�[������Ԃ�</returns>
	virtual uniqueBase Update(uniqueBase ownScene) = 0;

	// �`�揈��
	virtual void Draw(void);

	// �����̃V�[���ł̕`�揈��
	virtual void DrawOwnScreen(void) = 0;

	// �V�[�����擾
	virtual SceneID GetSceneID(void) = 0;
protected:
	// �L�[����
	char keyState_[256];

	// �X�N���[�����
	int screenID_;
private:

};

