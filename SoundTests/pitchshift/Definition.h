#pragma once

// スクリーンの大きさ
constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;

// サンプル数
constexpr int sampleNum = 32768;
constexpr int fftsampleNam = 4096;

// ファイル数
constexpr int fileNam = 2;		

// サウンドハンドル
int SoftSoundHandle[fileNam];
int SoundHandle[fileNam];

// サウンドファイル名
const wchar_t* SoundFileName[fileNam];

// ループフラグ
bool loopFlag = false;

// サウンドの一時停止フラグ
bool topPositionflag;


// 再生位置
LONGLONG TotalSampleCount;
LONGLONG DrawStartSampleCount = 0;

// 振幅スペクトル
float paramList[sampleNum];
LONGLONG samplePos;

// 現在の再生時間
int mmSecondSoundTime;

// ボリューム
int volume = 255;