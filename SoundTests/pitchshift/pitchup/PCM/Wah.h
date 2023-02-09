#pragma once
#include "PCM.h"
#include "../Wave/PCMDef.h"
#include "PCMSet.h"
#include <memory>

class Wah
	: public PCM
{
public:
	Wah(double rate);
	~Wah();

	/// <summary>
	/// 新しくワウが適用されたwavファイルを生成する
	/// </summary>
	/// <param name="fileName">変更前</param>
	/// <param name="afterFileName">変更後</param>
	void GenelateWahWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);

private:
	// PCMの初期化のオブジェクト
	std::unique_ptr<PCMSet> pcmSet_;
};

