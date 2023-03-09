#pragma once
#include <vector>
struct ChannelL
{
	double pmin;		// ピークの下限
	double pmax;		// ピークの上限
	double p;			// 波形の周期
	double q;			// 基準時刻の更新
	double offset0;		// 入力音声の開始位置
	double offset1;		// 生成音声の開始位置
	double ta;			// ピッチ変更前のサンプルデータ	
	double tb;			// ピッチ変更後のサンプルデータ

	std::vector<double> x;		// 元の音データを格納
	std::vector<double> y;		// mサンプルずらした音データを格納
	std::vector<double> r;		// xとyの相関関数を求める
};

struct ChannelR
{
	double pmin;		// ピークの下限
	double pmax;		// ピークの上限
	double p;			// 波形の周期
	double q;			// 基準時刻の更新
	double offset0;		// 入力音声の開始位置
	double offset1;		// 生成音声の開始位置
	double ta;			// ピッチ変更前のサンプルデータ	
	double tb;			// ピッチ変更後のサンプルデータ

	std::vector<double> x;		// 元の音データを格納
	std::vector<double> y;		// mサンプルずらした音データを格納
	std::vector<double> r;		// xとyの相関関数を求める
};