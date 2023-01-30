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
	/// �T�E���h���Z�b�g����
	/// </summary>
	/// <param name="fileName">�ϊ�����t�@�C����</param>
	/// <param name="genelateFlag"></param>
	void SetBGM(const wchar_t* fileName, bool genelateFlag);

	// �Đ��E�ꎞ��~
	void Play(void);

	// �T�E���h�n���h��
	int SoftSoundHandle;
	int SoundHandle;


	// ���g���擾
	int frequency;

	// �Đ��ʒu
	long long TotalSampleCount;
	long long DrawStartSampleCount;

	// �U���X�y�N�g��
	std::vector<float> paramList;
	long long samplePos;

	// ���݂̍Đ�����
	int mmSecondSoundTime;

	// �{�����[��
	int volume = 255;

	std::unique_ptr<PitchUp> pitchUp = std::make_unique<PitchUp>(0.8);

	std::unique_ptr<SoundObjMag> soundObjMag_;

	int count = 0;

	// �͂������������������ꂽ���̊m�F
	bool flag = false;

	SceneMag();
	~SceneMag();
};

