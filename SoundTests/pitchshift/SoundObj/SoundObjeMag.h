#pragma once
#include <memory>
#include "DrawObj/DrawObjMag.h"

class SoundObjeMag
{
public:
	SoundObjeMag();
	~SoundObjeMag();

	void Init();
	void Upadate();
	void Draw();
private:
	std::unique_ptr<DrawObjMag> drawObjmag_;
};

