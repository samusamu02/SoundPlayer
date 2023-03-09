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
	// 描画関係オブジェクト
	std::unique_ptr<DrawObjMag> drawObjMag_;

	// ファイル名
	SoundFile soundFile_;

	// ループカウント
	int loopCount_;
};

