#include "SoundObjMag.h"

SoundObjMag::SoundObjMag()
{
	// インスタンス
	drawObjMag_ = std::make_unique <DrawObjMag>();
}

SoundObjMag::~SoundObjMag()
{
	// 処理なし
}

void SoundObjMag::Init(void)
{
	// 描画管理クラスの初期化関数呼び出し
	drawObjMag_->Init();

	// カウントの初期化
	loopCount_ = 0;
}

void SoundObjMag::Update(void)
{
	// 描画管理クラスの更新処理呼び出し
	drawObjMag_->Update();

	// 終了チェック
	if (loopCount_ == 0)
	{
		// 変換前のサウンドハンドルの取得
		auto beforeSoundHandle = lpSoundSet.GetSoundHandle();
		// 総サンプル数の取得
		auto totalSampleCount = lpSoundSet.GetTotalSampleCount();
		// 現在のサウンド数の取得
		auto samplePos = GetCurrentPositionSoundMem(beforeSoundHandle);

		// 最後まで再生されるか右矢印キーを入力すると変換後のサウンドを再生する
		if (samplePos == totalSampleCount || 
			CheckHitKey(KEY_INPUT_RIGHT))
		{
			// 変換後のサウンドを再生する
			// 変換前のサウンドハンドルの削除
			DeleteSoundMem(beforeSoundHandle);
			// 新しくサウンドハンドルのセット
			lpSoundSet.SoundDataInit(soundFile_.afterFilenName);	
			// 変換後のサウンドハンドルの取得
			auto afterSoundHandle = lpSoundSet.GetSoundHandle();
			// 再生
			PlaySoundMem(afterSoundHandle, DX_PLAYTYPE_BACK);
			// ループカウントを1にする
			loopCount_ = 1;
		}
	}
}

void SoundObjMag::Draw(void)
{
	// 描画管理クラスの描画関数呼び出し
	drawObjMag_->Draw();
}