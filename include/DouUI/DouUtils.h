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
	static String GetTextNormalColorID()	//��ȡ����Normalɫ
	{
		return _T("color.textlink.normal");
	}
	static String GetTextHoverColorID()	//��ȡ����Hoverɫ
	{
		return _T("color.textlink.normal");
	}
	static String GetTextPressColorID()	//��ȡ����Pressɫ
	{
		return _T("color.textlink.normal");
	}
	static String GetTextDisabledColorID()	//��ȡ����Disabledɫ
	{
		return _T("color.textlink.normal");
	}
	static UINT GetTextFormatStyle()	//��ȡ�ı�������ʽ
	{
		return DOU_LEFT | DOU_TOP;
	}
	static int GetTextRowSpan()	//��ȡ�����ı����о�
	{
		return 3;
	}
};