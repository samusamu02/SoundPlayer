#pragma once
#include "../SoundObj/SoundObjeMag.h"
#include <memory>

#define lpSceneMag SceneMag::GetInstance()

class SceneMag
{
public:
	static SceneMag& GetInstance()
	{
		static SceneMag sceneMag;
		return sceneMag;
	}
	void Run();
	void Update();
	void Draw();

private:
	bool SysInit();
	bool sysInit_;

	// サウンドオブジェクト
	std::unique_ptr<SoundObjeMag> soundObjMag_;

	// キー操作
	std::unique_ptr<SoundCtl> soundCtl_;

	SceneMag();
	~SceneMag();
};

