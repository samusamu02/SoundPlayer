#include "PCMSet.h"

#include<stdio.h>
#include<stdlib.h>

PCMSet::PCMSet()
{
	// ���ɂȂ�
}

PCMSet::~PCMSet()
{
	// ���ɂȂ�
}

void PCMSet::PCMSetPitchUp(MONO_PCM& after, MONO_PCM& before,double rate)
{

	after.fs = before.fs;										// �W�{�����g��
	after.bits = before.bits;									// �ʎq�����x
	after.length = static_cast<int>(after.length / rate) + 1;				// ���̃f�[�^�̒���
	after.s.resize(after.length);								// ���̃f�[�^

}

void PCMSet::PCMSetPitchUp(STEREO_PCM& after, STEREO_PCM& before,double rate)
{
	
	after.fs = before.fs;										// �W�{�����g��
	after.bits = before.bits;									// �ʎq�����x
	after.length = static_cast<int>(before.length / rate) + 1;				// ���̃f�[�^�̒���
	after.sL.resize(after.length);								// ���̃f�[�^(L)
	after.sR.resize(after.length);								// ���̃f�[�^(R)

}

void PCMSet::PCMSetNormal(MONO_PCM& after, MONO_PCM& before)
{
	after.fs = before.fs;											// �W�{�����g��
	after.bits = before.bits;										// �ʎq�����x
	after.length = before.length;									// ���f�[�^�̒���
	after.s.resize(after.length);									// ���̃f�[�^
}

void PCMSet::PCMSetNormal(STEREO_PCM& after, STEREO_PCM& before)
{
	after.fs = before.fs;											// �W�{�����g��
	after.bits = before.bits;										// �ʎq�����x
	after.length = before.length;									// ���f�[�^�̒���
	after.sL.resize(after.length);									// ���f�[�^(L)
	after.sR.resize(after.length);									// ���f�[�^(R)
}
