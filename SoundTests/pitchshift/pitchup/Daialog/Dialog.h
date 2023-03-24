#pragma once
#include <shlobj.h>
#include <string>

#define lpDaialog Dialog::GetInstance()

class Dialog
{
public:
	static Dialog& GetInstance()
	{
		static Dialog s_Instance;
		return s_Instance;
	}

	void DialogView(void);
	std::wstring GetFilePath(void);
	std::wstring GetRelativePath(void);
	std::wstring NormalizePath(const std::wstring& path);
	std::wstring ConvertBackslashToSlash(const std::wstring& path);

private:
	OPENFILENAME ofn_;
	TCHAR szFile_[MAX_PATH];

	std::wstring filePath_;
	std::wstring fileExt_;
	std::wstring curentDir;
	std::wstring relativePath;

	wchar_t buffer[MAX_PATH];

	Dialog();
	~Dialog();
};

