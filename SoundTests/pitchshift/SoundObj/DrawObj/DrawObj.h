#pragma once
#include "../SoundObj.h"

// �X�N���[���̑傫��
constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;

class DrawObj :
    public SoundObj
{
public:
    DrawObj();
    ~DrawObj();
protected:

    // �T���v����
    const int sampleNum_ = 32768;

    // ���݂̃T���v���̈ʒu
    LONGLONG samplePos_;
private:
};

