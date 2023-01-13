#include <DxLib.h>
#include <shlobj.h>
#include <string>
#include "Definition.h"
#include "PitchUp/PitchUp.h"

PitchUp* pitchUp_ = new PitchUp();

// 初期化関数
void SetBGM(void)
{
	// 元のサウンドファイル
	SoundFileName[0] = L"Sound/Peak_test_A.wav";

	// ピッチ変更後のファイル名の設定
	SoundFileName[1] = L"Sound/PitchUp.wav";

	// ピッチアップの生成
	pitchUp_->GeneratePitchUpWaveFile(SoundFileName[0], SoundFileName[1]);

	// サウンドファイルの読み込み
	for (int i = 0; i < fileNam; i++)
	{
		SoftSoundHandle[i] = LoadSoftSound(SoundFileName[i]);

		// ソフトサウンドハンドルからサウンドハンドルを作成
		SoundHandle[i] = LoadSoundMemFromSoftSound(SoftSoundHandle[i]);

		// サウンドファイルが選択されなかった場合
		if (SoftSoundHandle[i] == -1)
		{
			// 一旦削除する
			DeleteSoundMem(SoundHandle[i]);
			MessageBox(NULL, L"サウンドファイルが見つかりませんでした", L"エラー", MB_OK);
		}
		else
		{
			// サウンドファイルの長さを取得
			TotalSampleCount = GetSoftSoundSampleNum(SoftSoundHandle[i]);
		}

		// ボリュームのセット
		SetVolumeMusicMem(volume, SoundHandle[i]);
	}
}

// 再生
void Play(void)
{
	// サウンドの再生
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		topPositionflag = false;
		PlaySoundMem(SoundHandle[0], DX_PLAYTYPE_BACK, topPositionflag);
	}

	DrawFormatString(0, 30, 0xffffff, L"スペースキー:再生");
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウインドウモードに変更
	ChangeWindowMode(true);

	// 画面解像度を設定
	SetGraphMode(SCREEN_W, SCREEN_H, 32);

	// 背景色を灰色に設定
	SetBackgroundColor(64, 64, 64);

	// バックグラウンド
	SetAlwaysRunFlag(true);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	// 描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);

	// BGMのセット
	SetBGM();

	// メインループ
	while (ProcessMessage() == 0)
	{
		// 画面を消去
		ClearDrawScreen();

		// 再生
		Play();

		// 現在の再生位置を取得
		samplePos = GetCurrentPositionSoundMem(SoundHandle[0]);

		// 取得した再生位置をサンプリングレートで割ってスクロール
		DrawStartSampleCount += samplePos / 44.1;
		// 描画範囲（今回は端から端まで)
		if (DrawStartSampleCount + SCREEN_W > samplePos)
		{
			DrawStartSampleCount = samplePos;
		}

		// 画面のセンターライン
		DrawLine(SCREEN_W / 2, 0, SCREEN_W / 2, SCREEN_W, 0xffffff);

		// 左チャンネルと右チャンネルを区切るラインを描画
		DrawLine(0, SCREEN_H / 2, SCREEN_W / 2, SCREEN_H / 2, GetColor(0, 0, 0));

		// 左チャンネルと右チャンネルのセンターラインを描画
		DrawLine(0, SCREEN_H / 4, SCREEN_W / 2, SCREEN_H / 4, GetColor(0, 0, 255));
		DrawLine(0, SCREEN_H - SCREEN_H / 4, SCREEN_W / 2, SCREEN_H - SCREEN_H / 4, GetColor(0, 0, 255));

		// 右チャンネル、左チャンネル
		int Ch1, Ch2;
		// 波形を描画
		for (LONGLONG i = 0; i < SCREEN_W / 2 && i + DrawStartSampleCount < TotalSampleCount; i++)
		{
			// 波形の振幅値を取得
			ReadSoftSoundData(SoftSoundHandle[0], i + DrawStartSampleCount, &Ch1, &Ch2);

			// 振幅値の高さの縦ラインを描画
			DrawLine(i, SCREEN_H / 4, i, SCREEN_H / 4 + (Ch1 * (SCREEN_H / 4) / sampleNum), GetColor(0, 0, 255));
			DrawLine(i, SCREEN_H - SCREEN_H / 4, i, SCREEN_H - SCREEN_H / 4 + (Ch2 * (SCREEN_H / 4) / sampleNum), GetColor(0, 0, 255));
		}

		// スペクトル描画
		// 現在の再生位置から周波数分布を得る
		GetFFTVibrationSoftSound(SoftSoundHandle[0], -1, samplePos, fftsampleNam, paramList, fftsampleNam);

		// 周波数分布を画面を描画する
		int x = -1;
		int j = 0;
		int offset = 15;
		for (int a = 0; a < fftsampleNam; a++)
		{
			if ((int)(log10((double)a) * 10) != x)
			{
				j++;
				x = (int)(log10((double)a) * 10);

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
		mmSecondSoundTime = GetSoundCurrentTime(SoundHandle[0]);
		auto sec = mmSecondSoundTime / mmSec;			// 秒
		DrawFormatString(0, SCREEN_H - 15, 0xffffff, L"再生時間: %d秒", sec);

		// ループフラグのオンオフ
		if (CheckHitKey(KEY_INPUT_1))
		{
			loopFlag = true;
		}

		if (CheckHitKey(KEY_INPUT_2))
		{
			loopFlag = false;
		}

		// 音量
		if (CheckHitKey(KEY_INPUT_E))
		{
			if (volume < 255)
			{
				volume++;
			}
			ChangeVolumeSoundMem(volume, SoundHandle[0]);
		}

		if (CheckHitKey(KEY_INPUT_Q))
		{
			if (volume > 0)
			{
				volume--;
			}
			ChangeVolumeSoundMem(volume, SoundHandle[0]);
		}

		DrawFormatString(150, SCREEN_H - 15, 0xffffff, L"ボリューム: %d", volume);

		DrawFormatString(0, 90, 0xffffff, L"1キー: ループフラグ ON\n2キー: ループフラグ OFF");
		if (loopFlag)
		{
			DrawFormatString(0, 140, 0xffffff, L"ループ: ON");
		}
		else
		{
			DrawFormatString(0, 140, 0xffffff, L"ループ: OFF");
		}

		// ループ処理(再生中だったら処理をする）
		if (loopFlag == true)
		{
			// 曲の終わりを見る
			if (samplePos == TotalSampleCount || samplePos == 0)
			{
				topPositionflag = true;
				PlaySoundMem(SoundHandle[0], DX_PLAYTYPE_BACK, topPositionflag);
			}
		}

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// ＤＸライブラリの後始末
	DxLib_End();

	return 0;
}
