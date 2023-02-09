#pragma once
#include "PCM.h"
#include "../Wave/PCMDef.h"
#include "PCMSet.h"
#include <memory>

class Wah
	: public PCM
{
public:
	Wah(double rate);
	~Wah();

	/// <summary>
	/// �V�������E���K�p���ꂽwav�t�@�C���𐶐�����
	/// </summary>
	/// <param name="fileName">�ύX�O</param>
	/// <param name="afterFileName">�ύX��</param>
	void GenelateWahWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);

private:
	// PCM�̏������̃I�u�W�F�N�g
	std::unique_ptr<PCMSet> pcmSet_;
};

