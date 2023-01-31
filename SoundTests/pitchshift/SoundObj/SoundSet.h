#pragma once
#include <memory>
#include "../PCM/PitchUp.h"
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

    void SoundInit(const wchar_t* fileName, bool genelateFlag);

    int GetSouftSoundHandle(void);
    int GetSoundHandle(void);
    long long GetTotalSampleCount(void);
    long long GetDrawStartSampleCount(void);
private:
    SoundSet();
    ~SoundSet();

    // ソフトサウンドハンドル
    int softSoundHandle_;
    // サウンドハンドル
    int soundHandle_;

    // 現在のサンプルの位置の取得
    long long totalSampleCount_;
    long long drawStartSampleCount_;

    std::unique_ptr<PitchUp> pitchUp_;
    SoundFile soundFile_;
};

