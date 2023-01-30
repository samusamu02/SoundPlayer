#include "SoundObj.h"

SoundObj::SoundObj()
{
}

SoundObj::~SoundObj()
{
}

int SoundObj::GetSoftSoundHandle()
{
	return softSoundHandle_;
}

int SoundObj::GetSoundHandle()
{
	return soundHandle_;
}
