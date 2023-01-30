#pragma once
#include <memory>
#include "DrawObj/DrawObjMag.h"
class SoundObjMag
{
public:
	SoundObjMag();
	~SoundObjMag();

	void Init(void);
	void Update(void);
	void Draw(void);

private:
	std::unique_ptr<DrawObjMag> drawObjMag_;
};

