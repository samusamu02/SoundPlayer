#pragma once

// 円周率
#define M_PI 3.14159265359

class PCM
{
public:
	PCM();
	virtual ~PCM();
protected:
	/// <summary>
	/// 新しくエフェクトが適用されたwavファイルを生成する
	/// </summary>
	/// <param name="fileName">エフェクト適用前のファイル</param>
	/// <param name="afterFileName">エフェクト適用後のファイル</param>
	/// <returns></returns>
	virtual bool GenelateEffectWaveFile(const wchar_t* fileName, const wchar_t* afterFileName) = 0;

	/// <summary>
	/// 新しくエフェクトが適用されたwavファイルを生成する
	/// </summary>
	/// <param name="rate">ピッチ変更の倍率</param>
	/// <param name="fileName">エフェクト適用前のファイル</param>
	/// <param name="afterFileName">エフェクト適用後のファイル</param>
	virtual bool GenelateEffectWaveFile(const double rate, const wchar_t* fileName, const wchar_t* afterFileName) = 0;
private:
};

