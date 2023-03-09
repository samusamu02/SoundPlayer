#include "PCM.h"

PCM::PCM()
{
	// 構造体の初期化
	channelL_ = {};		// 右チャンネル
	channelR_ = {};		// 左チャンネル

	// サウンドデータ
	pcm0_ = {};			
	pcm1_ = {};

	// 初期化

}

PCM::~PCM()
{
	// 特になし
}
