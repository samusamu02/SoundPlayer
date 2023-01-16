#include <DxLib.h>
#include <vector>
#include <shlobj.h>
#include <string>
#include <memory>
#include "PitchShift/PitchUp.h"
#include "Wave/Wave.h"

// スクリーンの大きさ
constexpr int SCREEN_W = 1280;
constexpr int SCREEN_H = 720;

// サンプル数
constexpr int sampleNum = 32768;
constexpr int fftsampleNam = 4096;

// サウンドハンドル
int SoftSoundHandle;
int SoundHandle;

// ループフラグ
bool loopFlag = false;

// サウンドの一時停止フラグ
bool topPositionflag;

// 周波数取得
int frequency;

// 再生位置
LONGLONG TotalSampleCount;
LONGLONG DrawStartSampleCount = 0;

// 振幅スペクトル
std::vector<float> paramList(sampleNum);
LONGLONG samplePos;

// 現在の再生時間
int mmSecondSoundTime;

// ボリューム
int volume = 255;

std::unique_ptr<PitchUp> pitchUp = std::make_unique<PitchUp>();

// 関数
// 初期化関数
void SetBGM(void)
{
	pitchUp->GenelatePitchUpWaveFile();

	// サウンドファイルの読み込み
	SoftSoundHandle = LoadSoftSound(L"Sound/ex11_5.wav");

	// ソフトサウンドハンドルからサウンドハンドルを作成
	SoundHandle = LoadSoundMemFromSoftSound(SoftSoundHandle);

	// サウンドファイルの長さを取得
	TotalSampleCount = GetSoftSoundSampleNum(SoftSoundHandle);

	// サウンドファイルの周波数を得る
	frequency = GetFrequencySoundMem(SoundHandle);

	// ボリュームのセット
	SetVolumeMusicMem(volume, SoundHandle);
}

// 再生・一時停止
void Play(void)
{
	// サウンドの再生
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		topPositionflag = false;
		PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK, topPositionflag);
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

	// 周波数変更
	int changeWave = 0;		// 読み込んだサウンドの周波数を変更する用の変数
	int changeWaveSpeed = 1000;	// どれくれい周波数を変更するか

	int count = 0;

	// メインループ
	while (ProcessMessage() == 0)
	{
		// 画面を消去
		ClearDrawScreen();

		if (CheckHitKey(KEY_INPUT_F5))
		{
			// 一旦削除する
			DeleteSoundMem(SoundHandle);
			// BGM をセットしなおす
			SetBGM();

			// もう一度再生をする
			topPositionflag;
			PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK, topPositionflag);
			count = 0;
		}

		// 再生
		Play();

		// 現在の再生位置を取得
		samplePos = GetCurrentPositionSoundMem(SoundHandle);

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
			ReadSoftSoundData(SoftSoundHandle, i + DrawStartSampleCount, &Ch1, &Ch2);

			// 振幅値の高さの縦ラインを描画
			DrawLine(i, SCREEN_H / 4, i, SCREEN_H / 4 + (Ch1 * (SCREEN_H / 4) / sampleNum), GetColor(0, 0, 255));
			DrawLine(i, SCREEN_H - SCREEN_H / 4, i, SCREEN_H - SCREEN_H / 4 + (Ch2 * (SCREEN_H / 4) / sampleNum), GetColor(0, 0, 255));
		}

		// スペクトル描画
		// 現在の再生位置から周波数分布を得る
		GetFFTVibrationSoftSound(SoftSoundHandle, -1, samplePos, fftsampleNam, paramList.data(), fftsampleNam);

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
		mmSecondSoundTime = GetSoundCurrentTime(SoundHandle);
		auto sec = mmSecondSoundTime / mmSec;			// 秒
		DrawFormatString(0, SCREEN_H - 15, 0xffffff, L"再生時間: %d秒", sec);

		int MinMax = 20000;

		// 周波数変更
		if (CheckHitKey(KEY_INPUT_UP))
		{
			if (changeWave < MinMax)
			{
				changeWave += changeWaveSpeed;
			}
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			if (changeWave > -MinMax)
			{
				changeWave -= changeWaveSpeed;
			}
		}
		// どれくらい周波数を変更しているかをわかりやすく
		auto ChangeWave = changeWave / 1000;
		DrawFormatString(0, 60, 0xffffff, L"↑ ↓キー:倍速・低速 値 %d", ChangeWave);

		// 曲が終わったか、先頭だったら周波数をもとに戻す
		if (samplePos >= TotalSampleCount || samplePos == 0)
		{
			changeWave = 0;
		}

		// 現在の周波数
		auto nowWave = frequency + changeWave;
		SetFrequencySoundMem(nowWave, SoundHandle);

		// ループフラグのオンオフ
		if (CheckHitKey(KEY_INPUT_1))
		{
			loopFlag = true;
		}

		if (CheckHitKey(KEY_INPUT_2))
		{
			loopFlag = false;
		}

		// 再生位置の移動
		if (samplePos <= TotalSampleCount)
		{
			if (CheckHitKey(KEY_INPUT_RIGHT))
			{
				// 一旦再生を止める
				StopSoundMem(SoundHandle);
				// 現在の再生時間を取得
				int nowTime = GetSoundCurrentTime(SoundHandle);
				// 時間指定
				LONGLONG time = 0 * 1000;
				time += 1000;
				SetStreamSoundCurrentTime(nowTime + time, SoundHandle);
			}
			if (CheckHitKey(KEY_INPUT_LEFT))
			{
				StopSoundMem(SoundHandle);
				// 現在の再生時間を取得
				int nowTime = GetSoundCurrentTime(SoundHandle);
				// 時間指定
				LONGLONG time = 0 * 1000;
				time -= 1000;
				SetStreamSoundCurrentTime(nowTime + time, SoundHandle);
			}
		}
		DrawFormatString(300, 60, 0xffffff, L"← → キー:再生時間を戻す・進める");

		// 音量
		if (CheckHitKey(KEY_INPUT_E))
		{
			if (volume < 255)
			{
				volume++;
			}
			ChangeVolumeSoundMem(volume, SoundHandle);
		}

		if (CheckHitKey(KEY_INPUT_Q))
		{
			if (volume > 0)
			{
				volume--;
			}
			ChangeVolumeSoundMem(volume, SoundHandle);
		}

		DrawFormatString(150, SCREEN_H - 15, 0xffffff, L"ボリューム: %d", volume);

		// ループ処理(再生中だったら処理をする）
		if (loopFlag == true)
		{
			// 曲の終わりを見る
			if (samplePos == TotalSampleCount || samplePos == 0)
			{
				topPositionflag = true;
				PlaySoundMem(SoundHandle, DX_PLAYTYPE_BACK, topPositionflag);
			}
		}

		DrawFormatString(0, 90, 0xffffff, L"1キー: ループフラグ ON\n2キー: ループフラグ OFF");
		if (loopFlag)
		{
			DrawFormatString(0, 140, 0xffffff, L"ループ: ON");
		}
		else
		{
			DrawFormatString(0, 140, 0xffffff, L"ループ: OFF");
		}

		DrawFormatString(0, 0, 0xffffff, L"F5: BGM選択");
		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// ＤＸライブラリの後始末
	DxLib_End();

	return 0;
}
