#pragma once

#include "../PCM/PitchDown.h"
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

	// システムのループ
	void Run();

	// スクリーンサイズの取得
	int GetScreen_H(void);
	int GetScreen_W(void);

private:
	// システムの初期化を行う
	bool SysInit();

	// システムの初期化の状態
	bool sysInit_;
	
	// サウンド関係のオブジェクト
	std::unique_ptr<SoundObjMag> soundObjMag_;

	SceneMag();
	~SceneMag();
};

