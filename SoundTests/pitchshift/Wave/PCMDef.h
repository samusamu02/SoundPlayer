#pragma once

struct MONO_PCM
{
	int fs;       // �W�{�����g�� 
	int bits;     // �ʎq�����x 
	int length;   // ���f�[�^�̒��� 
	double* s;    // ���f�[�^ 
};

struct STEREO_PCM
{
	int fs;       // �W�{�����g�� 
	int bits;     // �ʎq�����x 
	int length;   // ���f�[�^�̒��� 
	double* sL;   // ���f�[�^�iL�`�����l���j 
	double* sR;   // ���f�[�^�iR�`�����l���j 
};