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
	void Update(void);
	void Draw(void);

private:
	// 背景オブジェクト
	std::unique_ptr<DrawBG> drawBG_;

	// 波形オブジェクト
	std::unique_ptr<DrawWave> drawWave_;

	// スペクトルオブジェクト
	std::unique_ptr<DrawSpectrum> drawSpectrum_;
};

