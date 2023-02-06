#pragma once
#include <memory>
#include "DrawObj/DrawObjMag.h"
#include "SoundSet.h"
#include "SoundFile.h"

class SoundObjMag
{
public:
	SoundObjMag();
	~SoundObjMag();

	void Init(void);
	void Update(void);
	void Draw(void);

	bool GetYESNOFlag(void);
private:
	// �`��֌W�I�u�W�F�N�g
	std::unique_ptr<DrawObjMag> drawObjMag_;

	// �t�@�C����
	SoundFile soundFile_;

	// ���b�Z�[�W�{�b�N�X�̏��
	bool YESNOflag_;

	// ���[�v�J�E���g
	int loopCount_;
};

