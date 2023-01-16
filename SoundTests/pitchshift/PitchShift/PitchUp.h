#pragma once
#include "PitchShift.h"
#include "../Wave/PCM.h"

class PitchUp
	: public PitchShift
{
public:
	PitchUp();
	~PitchUp();

	void GenelatePitchUpWaveFile(void);

private:
};

