#pragma once
#include "SoundObj.h"
#include <memory>
#include "../PCM/PitchUp.h"
class SetSound :
    public SoundObj
{
public:
    SetSound();
    ~SetSound();

    /// <summary>
    /// サウンドハンドルにサウンドファイルをセットする
    /// </summary>
    /// <param name="fileName">サウンドファイル名</param>
    /// <param name="genelateFlag">新しくwavを変換するかどうかのフラグ</param>
    void SetSoundInit(const wchar_t* fileName, bool genelateFlag);
private:
    // ピッチアップ用のオブジェクト
    std::unique_ptr<PitchUp> pitchUp_;
};

