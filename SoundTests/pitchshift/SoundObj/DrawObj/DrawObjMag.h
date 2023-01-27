#pragma once
#include <memory>
#include <vector>
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
	std::vector <std::unique_ptr<DrawObj>> drawObj_;
};

