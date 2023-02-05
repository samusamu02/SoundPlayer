#pragma once
#include "DrawObj.h"
class DrawBG :
    public DrawObj
{
public:
    DrawBG();
    ~DrawBG();

    void Init(void);
    void Draw(void);
private:
};

