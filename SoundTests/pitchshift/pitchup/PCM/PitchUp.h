#pragma once
#include "PCM.h"
#include "../Wave/PCMDef.h"
#include "PCMSet.h"
#include <memory>

class PitchUp
	: public PCM
{
public:
	PitchUp(double rate);
	~PitchUp();

	/// <summary>
	/// �V�����s�b�`�ύX���ꂽwav�t�@�C���𐶐�����
	/// </summary>
	/// <param name="fileName">�ύX�O</param>
	/// <param name="afterFileName">�ύX��</param>
	void GenelatePitchUpWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);

private:
	// PCM�̏������̃I�u�W�F�N�g
	std::unique_ptr<PCMSet> pcmSet_;
};

