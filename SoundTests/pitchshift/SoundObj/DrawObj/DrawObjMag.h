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
	// 背景オブジェクト
	std::shared_ptr<DrawBG> drawBG_;

	// 波形オブジェクト
	std::shared_ptr<DrawWave> drawWave_;

	// スペクトルオブジェクト
	std::shared_ptr<DrawSpectrum> drawSpectrum_;
};

