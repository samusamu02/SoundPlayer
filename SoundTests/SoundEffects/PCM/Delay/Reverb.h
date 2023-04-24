#pragma once
#include "Delay.h"
class Reverb :
    public Delay
{
public:
    Reverb();
    ~Reverb();

    // 初期化処理
    virtual void Init(void);

    // リバーブ用の左チャンネルの変数の初期化処理
    virtual void ChannelL_Init(void);

    // リバーブ用の右チャンネルの変数の初期化処理
    virtual void ChannelR_Init(void);

    /// <summary>
    /// 新しくリバーブが適用されたwavファイルを生成する
    /// </summary>
    /// <param name="fileName">適用前のファイル</param>
    /// <param name="afterFileName">適用後のファイル</param>
    void GenelateReverbWaveFile(const wchar_t* fileName, const wchar_t* afterFileName);
private:
};

