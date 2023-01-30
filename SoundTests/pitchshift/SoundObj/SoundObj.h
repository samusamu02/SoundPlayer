#pragma once
class SoundObj
{
public:
	SoundObj();
	virtual ~SoundObj();

	// ソフトサウンドハンドルを取得
	int GetSoftSoundHandle();
	// サウンドハンドルを取得
	int GetSoundHandle();

protected:
	// ソフトサウンドハンドル
	int softSoundHandle_;
	// サウンドハンドル
	int soundHandle_;


	// 現在のサンプルの位置の取得
	long long totalSampleCount_;
	long long drawStartSampleCount_;
private:
};

