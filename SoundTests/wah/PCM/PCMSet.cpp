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

void PCMSet::PCMSetWah(MONO_PCM& after, MONO_PCM& before)
{
	after.fs = before.fs;											// �W�{�����g��
	after.bits = before.bits;										// �ʎq�����x
	after.length = before.length;									// ���f�[�^�̒���
	after.s.resize(after.length);									// ���̃f�[�^
}

void PCMSet::PCMSetWah(STEREO_PCM& after, STEREO_PCM& before)
{
	after.fs = before.fs;											// �W�{�����g��
	after.bits = before.bits;										// �ʎq�����x
	after.length = before.length;									// ���f�[�^�̒���
	after.sL.resize(after.length);									// ���f�[�^(L)
	after.sR.resize(after.length);									// ���f�[�^(R)
}
