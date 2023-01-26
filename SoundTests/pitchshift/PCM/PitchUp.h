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
	/// �T�E���h�t�@�C���̃s�b�`�������s���������V����wav�t�@�C���𐶐�����
	/// </summary>
	/// <param name="fileName">�ϊ��O�̃t�@�C����</param>
	/// <param name="afterFileName">�ϊ���̃t�@�C���������߂�</param>
	void GenelatePitchUpWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);

private:
	// PCM�̒l���Z�b�g����p�̃I�u�W�F�N�g
	std::unique_ptr<PCMSet> pcmSet_;
};

