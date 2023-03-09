#pragma once
#include "PitchShift.h"
class PitchDown :
    public PitchShift
{
public:
    PitchDown();
    ~PitchDown();
private:
	// 初期化
	void Init(void) override;

	// タイムストレッチ
	void Timestretching(void) override;

	// リサンプリング
	void Resampling(void) override;
};

