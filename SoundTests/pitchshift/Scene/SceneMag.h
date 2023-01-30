#pragma once

#include "../PCM/PitchUp.h"
#include <vector>
#include <memory>
#include "../SoundObj/SoundObjMag.h"
#define lpScenMag SceneMag::GetInstance()

class SceneMag
{
public:
	static SceneMag& GetInstance()
	{
		static SceneMag s_Instance;
		return s_Instance;
	}

	void Run();
	void Update();
	void Draw();

	int GetSCREEN_H(void);
	int GetSCREEN_W(void);
private:
	bool SysInit();
	bool sysInit_;

	/// <summary>
	/// サウンドをセットする
	/// </summary>
	/// <param name="fileName">変換するファイル名</param>
	/// <param name="genelateFlag"></param>
	void SetBGM(const wchar_t* fileName, bool genelateFlag);

	// 再生・一時停止
	void Play(void);

	// サウンドハンドル
	int SoftSoundHandle;
	int SoundHandle;


	// 周波数取得
	int frequency;

	// 再生位置
	long long TotalSampleCount;
	long long DrawStartSampleCount;

	// 振幅スペクトル
	std::vector<float> paramList;
	long long samplePos;

	// 現在の再生時間
	int mmSecondSoundTime;

	// ボリューム
	int volume = 255;

	std::unique_ptr<PitchUp> pitchUp = std::make_unique<PitchUp>(0.8);

	std::unique_ptr<SoundObjMag> soundObjMag_;

	int count = 0;

	// はいかいいえかを押されたかの確認
	bool flag = false;

	SceneMag();
	~SceneMag();
};

