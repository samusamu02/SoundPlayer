#pragma once
#include <memory>
#include "PitchShift.h"

class PitchUp
	: public PitchShift
{
public:
	PitchUp();
	~PitchUp();

	// �s�b�`�V�t�g
	bool GenelatePitchShiftFile(const double rate ,const wchar_t* fileName, const wchar_t* afterFileName) override;

private:
	// ������
	void Init(void) override;

	// �^�C���X�g���b�`
	void Timestretching(void) override;
	
	// ���T���v�����O
	void Resampling(void) override;
};

