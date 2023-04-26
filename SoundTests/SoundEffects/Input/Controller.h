#pragma once
#include <array>
#include <map>
#include <list>
#include <vector>
#include <chrono>

#include "InputID.h"

// 入力の状態
enum class Trg
{
	Now,	// 現在の値
	Old,	// 前回の値
	Max	
};

// Trgの値をインデックスにして、各要素の真偽値のarrayのエイリアス
using TrgBool = std::array<bool, static_cast<size_t>(Trg::Max)>;

// 入力IDをキーとして、TrgBoolを値とするmapのエイリアス
using CntData = std::map<InputID, TrgBool>;

class Controller
{
public:

	// リングバッファの構造体
	struct RingBuf
	{
		int value = 0;								// データの値
		double time = 0.0;							// データの時刻
		RingBuf* before = nullptr;					// 前の要素
		RingBuf* next = nullptr;					// 次の要素
		static RingBuf* Create(int no);				// リングバッファを生成する静的メソッド
		static void Destroy(RingBuf* beginBuf);		// リングバッファを破棄する静的メソッド
	};

	Controller() {};
	virtual ~Controller() {};

	// 更新処理
	virtual void Update(void) = 0;

	// CntDataを取得するメソッド
	const CntData& GetCntData(void)
	{
		return cntData_;
	}

protected:
	// 入力状態のデータ
	CntData cntData_;
	// リングバッファの現在の要素へのポインタ
	RingBuf* ringBuf_ = nullptr;
	// リングバッファの先頭の要素へのポインタ
	RingBuf* startBuf_ = nullptr;

private:
};

