#pragma once
#include "PCM.h"
#include "../Wave/PCMDef.h"
#include "PCMSet.h"
#include <memory>

class PitchUp
	: public PCM
{
public:
	PitchUp(double rate);
	~PitchUp();

	/// <summary>
	/// サウンドファイルのピッチ処理を行う処理し新しくwavファイルを生成する
	/// </summary>
	/// <param name="fileName">変換前のファイル名</param>
	/// <param name="afterFileName">変換後のファイル名を決める</param>
	void GenelatePitchUpWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);

private:
	// PCMの値をセットする用のオブジェクト
	std::unique_ptr<PCMSet> pcmSet_;
};

