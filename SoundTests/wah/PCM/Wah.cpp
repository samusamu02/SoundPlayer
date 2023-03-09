#include "Wah.h"
#include "../Wave/Wave.h"

#include "sinc.h"
#include <Windows.h>

Wah::Wah()
{
	// インスタンス
	pcm0_ = std::make_unique<STEREO_PCM>();
	pcm1_ = std::make_unique<STEREO_PCM>();
	channelL_ = std::make_unique<ChannelL>();
	channelR_ = std::make_unique<ChannelR>();
	pcmSet_ = std::make_unique<PCMSet>();
}

Wah::~Wah()
{
	// スマートポインタで管理しているので解放の処理は書く必要なし
}

void Wah::GenelateWahWaveFile(const wchar_t* fileName, const wchar_t* afterFileName)
{
	// Wavを読み込む
	lpWave.WaveRead(*pcm0_, fileName);

	// 元のサウドデータをコピー
	

	lpWave.WaveWrite(*pcm2_, afterFileName);
	MessageBox(nullptr, L"変換完了が完了しました", L"変換完了", 0);
}
