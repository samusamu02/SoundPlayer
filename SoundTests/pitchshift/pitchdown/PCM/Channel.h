#pragma once
#include <vector>
struct ChannelL
{
	int pmin;		// ピークの下限
	int pmax;		// ピークの上限
	int p;			// 波形の周期
	int q;			// 基準時刻の更新
	int offset0;	// 入力音声の開始位置
	int offset1;	// 生成音声の開始位置
	int ta;			// ピッチ変更前のサンプルデータ	
	int tb;			// ピッチ変更後のサンプルデータ

	std::vector<double> x;		// 元の音データを格納
	std::vector<double> y;		// mサンプルずらした音データを格納
	std::vector<double> r;		// xとyの相関関数を求める
};

struct ChannelR
{
	int pmin;		// ピークの下限
	int pmax;		// ピークの上限
	int p;			// 波形の周期
	int q;			// 基準時刻の更新
	int offset0;	// 入力音声の開始位置
	int offset1;	// 生成音声の開始位置
	int ta;			// ピッチ変更前のサンプルデータ	
	int tb;			// ピッチ変更後のサンプルデータ

	std::vector<double> x;		// 元の音データを格納
	std::vector<double> y;		// mサンプルずらした音データを格納
	std::vector<double> r;		// xとyの相関関数を求める
};