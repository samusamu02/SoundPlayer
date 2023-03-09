#pragma once
#include <memory>
#include "DrawObj/DrawObjMag.h"
#include "../SoundData/SoundData.h"
class SoundObjMag
{
public:
	SoundObjMag();
	~SoundObjMag();

	void Init(void);
	void Update(void);
	void Draw(void);
private:
	// �`��֌W�I�u�W�F�N�g
	std::unique_ptr<DrawObjMag> drawObjMag_;

	// �t�@�C����
	SoundFile soundFile_;

	// ���[�v�J�E���g
	int loopCount_;
};

