#pragma once
#include "DrawObj.h"
class DrawBG :
    public DrawObj
{
public:
    DrawBG();
    ~DrawBG();

    void Init(void);
    void Update(void);
    void Draw(void);
private:
    // �X�N���[���T�C�Y
    int screen_w;	// ��
    int screen_h;	// ����
};

