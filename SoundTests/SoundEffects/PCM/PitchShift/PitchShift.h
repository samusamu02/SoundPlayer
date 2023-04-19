#pragma once
#include <memory>
#include "../PCM.h"
#include "../PCMSet.h"
#include "../../Wave/PCMDef.h"

class PitchShift
	: public PCM
{
public:
	PitchShift();
	virtual ~PitchShift();

protected:

	struct ChannelL
	{
		double search_min;					// 探索範囲の下限
		double search_max;					// 探索範囲の上限
		double in_pos;						// 入力データの現在の位置
		double out_pos;						// 出力データの現在の位置
		double currentIndex;				// 現在のサンプルのインデックス
		double nextIndex;					// 次のサンプルのインデックス

		std::vector<double> soundData;				// 元の音声データを格納するための変数
		std::vector<double> shiftData;				// サンプルをずらすための変数
		std::vector<double> correlation;			// originalSoundData_とshiftedSoundData_の相関関数を求めるための変数
	};

	struct ChannelR
	{
		double search_min;					// 探索範囲の下限
		double search_max;					// 探索範囲の上限
		double in_pos;						// 入力データの現在の位置
		double out_pos;						// 出力データの現在の位置
		double currentIndex;				// 現在のサンプルのインデックス
		double nextIndex;					// 次のサンプルのインデックス

		std::vector<double> soundData;			// 元の音声データを格納するための変数
		std::vector<double> shiftData;			// サンプルをずらすための変数
		std::vector<double> correlation;		// originalSoundData_とshiftedSoundData_の相関関数を求めるための変数
	};

	// 初期化処理
	virtual void Init(void) = 0;

	// 左チャンネルの変数初期化処理
	virtual void ChannelL_Init(void) = 0;

	// 右チャンネルの変数初期化処理
	virtual void ChannelR_Init(void) = 0;

	// 左チャンネルのタイムストレッチ処理
	virtual void ChannelL_Timestretching(void) = 0;

	// 右チャンネルのタイムストレッチ処理
	virtual void ChannelR_Timestretching(void) = 0;

	// 左チャンネルのリサンプリング処理
	virtual void ChannelL_Resampling(void) = 0;

	// 右チャンネルのリサンプリング処理
	virtual void ChannelR_Resampling(void) = 0;

	/// <summary>
	/// 新しくピッチシフトが適用されたwavファイルを生成する
	/// </summary>
	/// <param name="rate">ピッチ変更の倍率</param>
	/// <param name="fileName">適用前のファイル</param>
	/// <param name="afterFileName">適用後のファイル</param>
	virtual void GenelatePitchShiftWaveFile(const double rate, const wchar_t* fileName, const wchar_t* afterFileName) = 0;

	// PCMの初期化のオブジェクト
	std::unique_ptr<PCMSet> pcmSet_;

	// ピッチシフト用のオブジェクト
	std::unique_ptr<STEREO_PCM> pcm0_;
	std::unique_ptr<STEREO_PCM> pcm1_;
	std::unique_ptr<STEREO_PCM> pcm2_;

	// 左チャンネル
	std::unique_ptr<ChannelL> channelL_;
	// 右チャンネル
	std::unique_ptr<ChannelR> channelR_;

	// 相関関数のピーク
	double peak_;

	// サンプルの時間軸のインデックス
	double timeIndex_;

	// タイムストレッチの伸縮率を求める
	double rate_;

	// ピッチの値
	double pitch_;

	// ハニング窓のサイズ
	int hanningSize_;

	// 相関関数のサイズ
	int correlationSize_;
private:
};

