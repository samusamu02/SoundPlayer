#pragma once
#include <memory>
#include "../PCM/PitchDown.h"
#include "SoundFile.h"

#define lpSoundSet SoundSet::GetInstance()

class SoundSet 
{
public:
    static SoundSet& GetInstance()
    {
        static SoundSet s_Instance;
        return s_Instance;
    }

    // サウンドの初期化
    void SoundInit(const wchar_t* fileName, bool genelateFlag);

    // ソフトハンドルの取得
    int GetSouftSoundHandle(void);

    // サウンドハンドルの取得
    int GetSoundHandle(void);

    // サンプル総数の取得
    long long GetTotalSampleCount(void);

    // 現在のサンプル数の取得
    long long GetDrawStartSampleCount(void);
private:
    SoundSet();
    ~SoundSet();

    // ソフトサウンドハンドル
    int softSoundHandle_;
    // サウンドハンドル
    int soundHandle_;

    // サンプル総数
    long long totalSampleCount_;

    // 現在のサンプルの位置の取得
    long long drawStartSampleCount_;

    // ピッチアップのオブジェクト
    std::unique_ptr<PitchDown> pitchDown_;

    // サウンドのファイル
    SoundFile soundFile_;
};

