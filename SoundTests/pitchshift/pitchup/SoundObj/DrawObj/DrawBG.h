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
    // スクリーンサイズ
    int screen_w;	// 幅
    int screen_h;	// 高さ
};

