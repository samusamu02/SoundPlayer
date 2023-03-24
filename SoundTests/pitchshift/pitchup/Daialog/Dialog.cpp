#include <filesystem>
#include <string>

#include "Dialog.h"

namespace fs = std::filesystem;

void Dialog::DialogView(void)
{
	// COMの初期化
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	// ダイアログボックスの設定
	ofn_ = { 0 };
	szFile_[MAX_PATH] = { 0 };
	ofn_.lStructSize = sizeof(OPENFILENAME);
	ofn_.hwndOwner = nullptr;
	ofn_.lpstrFilter = L"Sound Files\0*.mp3;*.wav\0All Files\0*.*\0";
	ofn_.lpstrFile = szFile_;
	ofn_.nMaxFile = MAX_PATH;
	ofn_.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;

	// ファイル選択ダイアログを表示
	if (GetOpenFileName(&ofn_))
	{
		// ファイルパスの取得
		filePath_ = ofn_.lpstrFile;

		wchar_t fullPath[MAX_PATH];
		GetFullPathName(filePath_.c_str(), MAX_PATH, fullPath, nullptr);
		filePath_ = fullPath;

		// 拡張子の計算
		fileExt_ = filePath_.substr(filePath_.find_last_of(L".") + 1);

		GetCurrentDirectory(MAX_PATH, buffer);

		curentDir = buffer;
		relativePath = filePath_.substr(curentDir.size() + 1);

		if (!(fileExt_ == L"mp3" || fileExt_ == L"wav"))
		{
			MessageBox(nullptr, L"これはサウンドファイルではありません", L"エラー", MB_OK | MB_ICONERROR);
		}
	}

	// COMの解放
	CoUninitialize();
}

std::wstring Dialog::GetFilePath(void)
{
	return filePath_;
}

std::wstring Dialog::GetRelativePath(void)
{
	return relativePath;
}

Dialog::Dialog()
{
}

Dialog::~Dialog()
{
}
