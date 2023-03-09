#pragma once
#include <memory>
#include "PitchShift.h"

class PitchUp
	: public PitchShift
{
public:
	PitchUp();
	~PitchUp();

	// ピッチシフト
	bool GenelatePitchShiftFile(const double rate ,const wchar_t* fileName, const wchar_t* afterFileName) override;

private:
	// 初期化
	void Init(void) override;

	// タイムストレッチ
	void Timestretching(void) override;
	
	// リサンプリング
	void Resampling(void) override;
};

