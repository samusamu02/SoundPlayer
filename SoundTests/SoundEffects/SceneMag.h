#pragma once
#include "PCM/PitchShift/PitchUp.h"
#include <vector>
#include <memory>
#include "SoundObj/SoundObjMag.h"
#include "Scene/SoundPlayScene.h"

#define lpScenMag SceneMag::GetInstance()

class SceneMag
{
public:
	static SceneMag& GetInstance()
	{
		static SceneMag s_Instance;
		return s_Instance;
	}

	// システムのループ
	void Run();

	// スクリーンサイズの取得
	int GetScreen_H(void);
	int GetScreen_W(void);

private:
	// システムの初期化処理
	bool SysInit();

	// システムの初期化の状態
	bool sysInit_;
	
	// サウンド関係のオブジェクト
	uniqueBase scene_;

	SceneMag();
	~SceneMag();
};

