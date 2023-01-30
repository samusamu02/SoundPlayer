#pragma once
#include <DxLib.h>
#include "../SoundObj.h"



class DrawObj :
    public SoundObj
{
public:
    DrawObj();
    ~DrawObj();

    virtual void Init(void);
    virtual void Update(void) = 0;
    virtual void Draw(void) = 0;
protected:
    // 現在のサンプルの位置を取得
    long long samplePos_;

    // サンプル数
    int sampleNum_;
private:
};

