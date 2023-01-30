#include "SceneMag.h"
#include <DxLib.h>

// スクリーンの大きさ
constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;

// サンプル数
constexpr int sampleNum_ = 32768;
constexpr int fftsampleNam = 4096;

void SceneMag::Run()
{
	if (!sysInit_)
	{
		if (!SysInit())
		{
			return;
		}
	}

	auto YESNO = MessageBox(nullptr, L"変換を行いますか?", L"ピッチアップ", MB_YESNO);

	if (YESNO == IDYES)
	{

		flag = true;
	}
	else
	{
		flag = false;
	}

	if (flag == true)
	{
		MessageBox(nullptr, L"変換を行います", L"変換中", 0);
	}

	// BGMのセット
	SetBGM(file, flag);

	// サウンドオブジェクト管理クラスのインスタンス
	soundObjMag_ = std::make_unique<SoundObjMag>();

	// サウンドオブジェクト管理クラスの初期化関数呼び出し
	soundObjMag_->Init();

	// メインループ
	while (ProcessMessage() == 0)
	{
		// サウンドオブジェクト管理クラスの更新関数呼び出し
		soundObjMag_->Update();

		// 描画先を裏画面に変更
		SetDrawScreen(DX_SCREEN_BACK);

		// 画面を消去
		ClearDrawScreen();

		// 	// サウンドオブジェクト管理クラスの描画関数呼び出し
		soundObjMag_->Draw();

		// 再生
		Play();

		// 現在の再生位置を取得
		samplePos = GetCurrentPositionSoundMem(SoundHandle);

		paramList.resize(sampleNum_);

		soundObjMag_->Draw();

		// 取得した再生位置をサンプリングレートで割ってスクロール
		DrawStartSampleCount += samplePos / 44.1;
		// 描画範囲（今回は端から端まで)
		if (DrawStartSampleCount + SCREEN_W > samplePos)
		{
			DrawStartSampleCount = samplePos;
		}

		// 右チャンネル、左チャンネル
		int Ch1, Ch2;
		// 波形を描画
		// 1サンプルずつ処理を行う
		for (LONGLONG i = 0; i < SCREEN_W / 2 && i + DrawStartSampleCount < TotalSampleCount; i++)
		{
			// 波形の振幅値を取得
			ReadSoftSoundData(SoftSoundHandle, i + DrawStartSampleCount, &Ch1, &Ch2);

			// 振幅値の高さの縦ラインを描画
			DrawLine(i, SCREEN_H / 4, i, SCREEN_H / 4 + (Ch1 * (SCREEN_H / 4) / sampleNum_), GetColor(0, 0, 255));
			DrawLine(i, SCREEN_H - SCREEN_H / 4, i, SCREEN_H - SCREEN_H / 4 + (Ch2 * (SCREEN_H / 4) / sampleNum_), GetColor(0, 0, 255));
		}

		// スペクトル描画
		// 現在の再生位置から周波数分布を得る
		GetFFTVibrationSoftSound(SoftSoundHandle, -1, samplePos, fftsampleNam, paramList.data(), fftsampleNam);

		// 周波数分布を画面を描画する
		int x = -1;
		int j = 0;

		// 軸の間隔
		int offset = 15;
		// サンプル数分処理を行う
		for (int a = 0; a < fftsampleNam; a++)
		{
			// 対数が同じでない場合のみ値を変える
			auto log = (int)(log10((double)a) * 10);
			if (log != x)
			{
				// 描画位置
				j++;

				// 横軸に対してlogで対数をとる
				x = (int)(log10((double)a) * 10);

				// パラメーター
				float Param;

				// 関数から取得できる値を描画に適した値に調整
				Param = pow(paramList[a], 0.5f) * 0.8f;

				// 振幅スペクトルの描画(右側にずらして描画）
				DrawBox(((SCREEN_W / 2) + 50) + j * offset, SCREEN_H - (int)(Param * SCREEN_H), ((SCREEN_W / 2) + 50) + j * offset + 4, SCREEN_H, 0x00ff00, true);
			}
		}

		// ミリ秒
		int mmSec = 1000;

		// サウンドファイルの秒数
		// 現在の再生位置をミリ秒で取得
		mmSecondSoundTime = GetSoundCurrentTime(SoundHandle);
		auto sec = mmSecondSoundTime / mmSec;	// 秒
		DrawFormatString(0, SCREEN_H - 15, 0xffffff, L"再生時間: %d秒", sec);

		// フラグがtrueのみ処理を行う
		if (flag == true)
		{
			// 1回のみ有効
			if (count == 0)
			{
				// 曲の終わりを見る
				if (samplePos == TotalSampleCount)
				{
					// 曲が終わったらセットしなおし、変換後の曲を再生する
					SetBGM(file_2, false);
					PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
					count = 1;
				}
			}
		}

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// ＤＸライブラリの後始末
	DxLib_End();
}

void SceneMag::Update()
{
}

void SceneMag::Draw()
{
}

bool SceneMag::SysInit()
{
	// ウインドウモードに変更
	ChangeWindowMode(true);

	// 画面解像度を設定
	SetGraphMode(SCREEN_W, SCREEN_H, 32);

	// 背景色を灰色に設定
	SetBackgroundColor(64, 64, 64);

	// バックグラウンド
	SetAlwaysRunFlag(true);

	// アイコンの生成
	SetWindowIconID(001);

	SetWindowText(L"ピッチアップ変更テスト");

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return false;
	}

	return true;
}

void SceneMag::SetBGM(const wchar_t* fileName, bool genelateFlag)
{
	// ピッチアップ(flagがtrueの場合のみ新しくwavファイルを生成する
	if (genelateFlag == true)
	{
		pitchUp->GenelatePitchUpWaveFile(fileName, file_2);
	}

	// サウンドファイルの読み込み
	SoftSoundHandle = LoadSoftSound(fileName);

	// ソフトサウンドハンドルからサウンドハンドルを作成
	SoundHandle = LoadSoundMemFromSoftSound(SoftSoundHandle);

	// サウンドファイルの長さを取得
	TotalSampleCount = GetSoftSoundSampleNum(SoftSoundHandle);

	// サウンドファイルの周波数を得る
	frequency = GetFrequencySoundMem(SoundHandle);

	// ボリュームのセット
	SetVolumeMusicMem(volume, SoundHandle);
}

void SceneMag::Play(void)
{
	// サウンドの再生
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK);
	}

	DrawFormatString(0, 0, 0xffffff, L"スペースキー:再生");
}

int SceneMag::GetSCREEN_H(void)
{
	return SCREEN_H;
}

int SceneMag::GetSCREEN_W(void)
{
	return SCREEN_W;
}


SceneMag::SceneMag()
{
	sysInit_ = SysInit();
}

SceneMag::~SceneMag()
{
}
