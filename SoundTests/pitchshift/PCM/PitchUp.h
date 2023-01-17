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

	void GenelatePitchUpWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);

private:
	std::unique_ptr<PCMSet> pcmSet_;
};

