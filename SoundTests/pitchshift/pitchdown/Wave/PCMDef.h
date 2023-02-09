#pragma once
#include <vector>

struct MONO_PCM
{
	int fs;       // �W�{�����g�� 
	int bits;     // �ʎq�����x 
	int length;   // ���f�[�^�̒��� 
	std::vector<double> s;    // ���f�[�^ 
};

struct STEREO_PCM
{
	int fs;       // �W�{�����g�� 
	int bits;     // �ʎq�����x 
	int length;   // ���f�[�^�̒��� 
	std::vector<double> sL;   // ���f�[�^�iL�`�����l���j 
	std::vector<double> sR;   // ���f�[�^�iR�`�����l���j 
};