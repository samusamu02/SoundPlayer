#pragma once
#include "PCM.h"
#include "../Wave/PCMDef.h"
#include "PCMSet.h"
#include <memory>

class PitchDown
	: public PCM
{
public:
	PitchDown(double rate);
	~PitchDown();

	/// <summary>
	/// 新しくピッチ変更されたwavファイルを生成する
	/// </summary>
	/// <param name="fileName">変更前</param>
	/// <param name="afterFileName">変更後</param>
	void GenelatePitchDownWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);

private:
	// PCMの初期化のオブジェクト
	std::unique_ptr<PCMSet> pcmSet_;
};

