#pragma once
#include "PitchShift.h"
class PitchDown :
    public PitchShift
{
public:
    PitchDown();
    ~PitchDown();
private:
	// ������
	void Init(void) override;

	// �^�C���X�g���b�`
	void Timestretching(void) override;

	// ���T���v�����O
	void Resampling(void) override;
};

