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
};

