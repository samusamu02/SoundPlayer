#pragma once
class SoundObj
{
public:
	SoundObj();
	virtual ~SoundObj();

	// �\�t�g�T�E���h�n���h�����擾
	int GetSoftSoundHandle();
	// �T�E���h�n���h�����擾
	int GetSoundHandle();

protected:
	// �\�t�g�T�E���h�n���h��
	int softSoundHandle_;
	// �T�E���h�n���h��
	int soundHandle_;


	// ���݂̃T���v���̈ʒu�̎擾
	long long totalSampleCount_;
	long long drawStartSampleCount_;
private:
};

