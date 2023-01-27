#pragma once
#include <winnt.h>
#include <vector>

class SoundObj
{
public:
	SoundObj();
	virtual ~SoundObj();
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
	// サウンドハンドル
	int softSoundHandle_;
	int soundHandle_;

	// 周波数取得
	int frequency_;

	// サウンドファイル
	const wchar_t* file_ = L"Sound/Peak_test_A.wav";
	const wchar_t* file_2_ = L"Sound/pitchup.wav";

	// ループ内で一回のみ処理を行うよう
	int loopCount_;

	// はいかいいえかを押されたかの確認
	bool YNflag_;
private:
};

