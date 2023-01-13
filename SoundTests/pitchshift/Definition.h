#pragma once

// �X�N���[���̑傫��
constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;

// �T���v����
constexpr int sampleNum = 32768;
constexpr int fftsampleNam = 4096;

// �t�@�C����
constexpr int fileNam = 2;		

// �T�E���h�n���h��
int SoftSoundHandle[fileNam];
int SoundHandle[fileNam];

// �T�E���h�t�@�C����
const wchar_t* SoundFileName[fileNam];

// ���[�v�t���O
bool loopFlag = false;

// �T�E���h�̈ꎞ��~�t���O
bool topPositionflag;


// �Đ��ʒu
LONGLONG TotalSampleCount;
LONGLONG DrawStartSampleCount = 0;

// �U���X�y�N�g��
float paramList[sampleNum];
LONGLONG samplePos;

// ���݂̍Đ�����
int mmSecondSoundTime;

// �{�����[��
int volume = 255;