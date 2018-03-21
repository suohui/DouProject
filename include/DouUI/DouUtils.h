#pragma once

class CDouUtils
{
public:
	static String GetImageZipPath()
	{
		TCHAR szExePath[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, szExePath, MAX_PATH);
		PathRemoveFileSpec(szExePath);
		TCHAR szImageZipPath[MAX_PATH] = { 0 };
		PathCombine(szImageZipPath, szExePath, _T("skin.zip"));
		return szImageZipPath;
	}
};