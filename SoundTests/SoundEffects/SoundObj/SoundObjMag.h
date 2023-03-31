#pragma once
#include <memory>
#include "DrawObj/DrawObjMag.h"
#include "../SoundData/SoundData.h"
class SoundObjMag
{
public:
	SoundObjMag();
	~SoundObjMag();

	// 初期化処理
	void Init(void);

	// 更新処理
	void Update(void);

	// 描画処理
	void Draw(void);
private:
	// 描画関係オブジェクト
	std::unique_ptr<DrawObjMag> drawObjMag_;

	// ファイル名
	SoundFile soundFile_;

	// ループカウント
	int loopCount_;
};

