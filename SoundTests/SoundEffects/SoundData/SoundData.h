#pragma once
#include <memory>
#include "../PCM/PitchShift/PitchUp.h"
#include "../SoundObj/SoundFile.h"

#define lpSoundSet SoundData::GetInstance()

class SoundData 
{
public:
    static SoundData& GetInstance()
    {
        static SoundData s_Instance;
        return s_Instance;
    }

    // サウンドの初期化
    void SoundDataInit(const wchar_t* fileName);

    // ソフトハンドルの取得
    int GetSouftSoundHandle(void);

    // サウンドハンドルの取得
    int GetSoundHandle(void);

    // サンプル総数の取得
    long long GetTotalSampleCount(void);

    // 現在のサンプル数の取得
    long long GetDrawStartSampleCount(void);
private:
    SoundData();
    ~SoundData();

    // サウンドのファイル
    SoundFile soundFile_;

    // サンプル総数
    long long totalSampleCount_;

    // 現在のサンプルの位置の取得
    long long drawStartSampleCount_;

    // ソフトサウンドハンドル
    int softSoundHandle_;

    // サウンドハンドル
    int soundHandle_;
};

