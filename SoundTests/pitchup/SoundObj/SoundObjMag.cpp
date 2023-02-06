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
	// 変換を行うかどうかのチェック
	auto YESNO = MessageBox(nullptr, L"変換を行いますか?", L"ピッチアップ", MB_YESNO);

	if (YESNO == IDYES)
	{

		YESNOflag_ = true;
	}
	else
	{
		YESNOflag_ = false;
	}

	if (YESNOflag_ == true)
	{
		MessageBox(nullptr, L"変換を行います", L"変換中", 0);
	}

	// サウンドの初期化
	lpSoundSet.SoundInit(soundFile_.beforeFileName,YESNOflag_);

	// サウンドの再生
	auto soundHandle = lpSoundSet.GetSoundHandle();
	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);

	// カウントの初期化
	loopCount_ = 0;

	// 描画管理クラスの初期化関数呼び出し
	drawObjMag_->Init();
}

void SoundObjMag::Update(void)
{
	// 終了チェック
	if (loopCount_ == 0)
	{
		// 変換前のサウンドハンドルの取得
		auto beforesoundHandle = lpSoundSet.GetSoundHandle();
		// 総サンプル数の取得
		auto totalSampleCount = lpSoundSet.GetTotalSampleCount();
		// 現在のサウンド数の取得
		auto samplePos = GetCurrentPositionSoundMem(beforesoundHandle);

		// 最後まで再生されるか右矢印キーを入力すると変換後のサウンドを再生する
		if (samplePos == totalSampleCount || 
			CheckHitKey(KEY_INPUT_RIGHT))
		{
			// 変換後のサウンドを再生する
			// 変換前のサウンドハンドルの削除
			DeleteSoundMem(beforesoundHandle);
			// 新しくサウンドハンドルのセット
			lpSoundSet.SoundInit(soundFile_.afterFilenName, false);	
			// 変換後のサウンドハンドルの取得
			auto afuterSoundHandle = lpSoundSet.GetSoundHandle();
			// 再生
			PlaySoundMem(afuterSoundHandle, DX_PLAYTYPE_BACK);
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

bool SoundObjMag::GetYESNOFlag(void)
{
	return YESNOflag_;
}
