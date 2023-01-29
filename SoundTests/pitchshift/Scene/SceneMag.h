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

	// �T�E���h�I�u�W�F�N�g
	std::unique_ptr<SoundObjeMag> soundObjMag_;

	// �L�[����
	std::unique_ptr<SoundCtl> soundCtl_;

	SceneMag();
	~SceneMag();
};

