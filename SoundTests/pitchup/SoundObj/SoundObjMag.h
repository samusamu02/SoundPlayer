#pragma once
#include <memory>
#include "DrawObj/DrawObjMag.h"
#include "SoundSet.h"
#include "SoundFile.h"

class SoundObjMag
{
public:
	SoundObjMag();
	~SoundObjMag();

	void Init(void);
	void Update(void);
	void Draw(void);

	bool GetYESNOFlag(void);
private:
	// 描画関係オブジェクト
	std::unique_ptr<DrawObjMag> drawObjMag_;

	// ファイル名
	SoundFile soundFile_;

	// メッセージボックスの状態
	bool YESNOflag_;

	// ループカウント
	int loopCount_;
};

