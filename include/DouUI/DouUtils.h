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





	static String GetTextNormalFontID()	//获取Normal字体
	{
		return _T("default.font");
	}
	static String GetTextHoverFontID()	//获取Hover字体
	{
		return _T("default.font");
	}
	static String GetTextPressFontID()	//获取Press字体
	{
		return _T("default.font");
	}
	static String GetTextDisabledFontID()	//获取Disabled字体
	{
		return _T("default.font");
	}
	static DWORD GetTextNormalColor()	//获取文字Normal色
	{
		return 0;
	}
	static DWORD GetTextHoverColor()	//获取文字Hover色
	{
		return 0;
	}
	static DWORD GetTextPressColor()	//获取文字Press色
	{
		return 0;
	}
	static DWORD GetTextDisabledColor()	//获取文字Disabled色
	{
		return 0;
	}
	static UINT GetTextFormatStyle()	//获取文本绘制样式
	{
		return DT_LEFT | DT_TOP;
	}
	static int GetTextRowHeight()	//获取多行文本的行高
	{
		return 12;
	}
};