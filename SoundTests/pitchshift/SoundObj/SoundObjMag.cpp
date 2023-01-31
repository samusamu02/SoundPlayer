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
	// サウンド本体の初期化
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

	// 描画管理クラスの初期化関数呼び出し
	drawObjMag_->Init();
}

void SoundObjMag::Update(void)
{
	// 描画管理クラスの更新関数呼び出し
	drawObjMag_->Update();

	// サウンドの再生
	auto soundHandle = lpSoundSet.GetSoundHandle();

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
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
