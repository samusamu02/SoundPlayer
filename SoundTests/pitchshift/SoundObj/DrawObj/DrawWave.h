#pragma once
#include "DrawObj.h"

class DrawWave :
    public DrawObj
{
public:
    DrawWave();
    ~DrawWave();
    void Init();
    void DrawSoundWave();
private:

    // �Đ��ʒu
    LONGLONG totalSampleCount_;     // �T���v���̑���
    LONGLONG drawStartSampleCount_; // ���݂̃T���v���ʒu
};
    


