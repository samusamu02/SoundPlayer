#pragma once
#include <memory>
#include "DrawBG.h"
#include "DrawWave.h"
#include "DrawSpectrum.h"

class DrawObjMag
{
public:
	DrawObjMag();
	~DrawObjMag();

	void Init(void);
	void Draw(void);

private:
	// �w�i�I�u�W�F�N�g
	std::shared_ptr<DrawBG> drawBG_;

	// �g�`�I�u�W�F�N�g
	std::shared_ptr<DrawWave> drawWave_;

	// �X�y�N�g���I�u�W�F�N�g
	std::shared_ptr<DrawSpectrum> drawSpectrum_;
};
