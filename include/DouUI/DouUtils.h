#pragma once

#define DOU_TOP                      0x00000000
#define DOU_LEFT                     0x00000000
#define DOU_CENTER                   0x00000001
#define DOU_RIGHT                    0x00000002
#define DOU_VCENTER                  0x00000004
#define DOU_BOTTOM                   0x00000008

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
	static String GetTextNormalColorID()	//获取文字Normal色
	{
		return _T("color.textlink.normal");
	}
	static String GetTextHoverColorID()	//获取文字Hover色
	{
		return _T("color.textlink.normal");
	}
	static String GetTextPressColorID()	//获取文字Press色
	{
		return _T("color.textlink.normal");
	}
	static String GetTextDisabledColorID()	//获取文字Disabled色
	{
		return _T("color.textlink.normal");
	}
	static UINT GetTextFormatStyle()	//获取文本绘制样式
	{
		return DOU_LEFT | DOU_TOP;
	}
	static int GetTextRowSpan()	//获取多行文本的行距
	{
		return 3;
	}
};