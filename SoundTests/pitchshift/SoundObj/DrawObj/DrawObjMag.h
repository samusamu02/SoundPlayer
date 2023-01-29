#pragma once
#include <memory>
#include "DrawBG.h"
class DrawObjMag
{
public:
	DrawObjMag();
	~DrawObjMag();

	void Init(void);
	void Update(void);
	void Draw(void);

private:
	std::unique_ptr<DrawBG> drawBG_;
};

