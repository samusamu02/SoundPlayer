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
	// �T�E���h�n���h��
	int softSoundHandle_;
	int soundHandle_;

	// ���g���擾
	int frequency_;

	// �T�E���h�t�@�C��
	const wchar_t* file_ = L"Sound/Peak_test_A.wav";
	const wchar_t* file_2_ = L"Sound/pitchup.wav";

	// ���[�v���ň��̂ݏ������s���悤
	int loopCount_;

	// �͂������������������ꂽ���̊m�F
	bool YNflag_;
private:
};

