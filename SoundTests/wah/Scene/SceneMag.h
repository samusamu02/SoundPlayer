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

	// �V�X�e���̃��[�v
	void Run();

	// �X�N���[���T�C�Y�̎擾
	int GetScreen_H(void);
	int GetScreen_W(void);

private:
	// �V�X�e���̏��������s��
	bool SysInit();

	// �V�X�e���̏������̏��
	bool sysInit_;
	
	// �T�E���h�֌W�̃I�u�W�F�N�g
	std::unique_ptr<SoundObjMag> soundObjMag_;

	SceneMag();
	~SceneMag();
};

