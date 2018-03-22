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





	static String GetTextNormalFontID()	//��ȡNormal����
	{
		return _T("default.font");
	}
	static String GetTextHoverFontID()	//��ȡHover����
	{
		return _T("default.font");
	}
	static String GetTextPressFontID()	//��ȡPress����
	{
		return _T("default.font");
	}
	static String GetTextDisabledFontID()	//��ȡDisabled����
	{
		return _T("default.font");
	}
	static DWORD GetTextNormalColor()	//��ȡ����Normalɫ
	{
		return 0;
	}
	static DWORD GetTextHoverColor()	//��ȡ����Hoverɫ
	{
		return 0;
	}
	static DWORD GetTextPressColor()	//��ȡ����Pressɫ
	{
		return 0;
	}
	static DWORD GetTextDisabledColor()	//��ȡ����Disabledɫ
	{
		return 0;
	}
	static UINT GetTextFormatStyle()	//��ȡ�ı�������ʽ
	{
		return DT_LEFT | DT_TOP;
	}
	static int GetTextRowHeight()	//��ȡ�����ı����и�
	{
		return 12;
	}
};