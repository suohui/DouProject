#pragma once

class CAppResource
{
public:
	static void GetColorResInfo(std::vector<TDouColorInfo>& arrColorInfo)
	{
		arrColorInfo =
		{
			{ _T("system.white"), RGBColor, RGB(255, 255, 255) },
			{ _T("system.black"), RGBColor, RGB(0, 0, 0) },
			{ _T("MainWnd.Color.TitleBar"), RGBColor, RGB(50, 166, 253) },
			{ _T("MainPanel.TextColor.Title"), HexColor, 0x32A7FE },
			{ _T("MainPanel.TextColor.Content"), HexColor, 0x666666 },
		};
	}

	static void GetFontResInfo(std::vector<TDouFontInfo>& arrFontInfo)
	{
		arrFontInfo =
		{
			{ _T("default.font"), 12, FALSE, FALSE, FALSE },
			{ _T("Font13"), 13, FALSE, FALSE, FALSE },
			{ _T("Font14"), 14, FALSE, FALSE, FALSE },
			{ _T("Font18"), 18, FALSE, FALSE, FALSE },
		};
	}

	static void GetBitmapResInfo(std::vector<TDouBitmapInfo>& arrBmpResInfo)
	{
		arrBmpResInfo =
		{
			{ _T("MainWnd.Logo"), DouResIDType::Bitmap, _T("主界面\\Logo.png"), DouBitmapType::OnlyOne },
			{ _T("MainWnd.Btn.Close"), DouResIDType::ItemList, _T("主界面\\关闭按钮.png"), DouBitmapType::ThreeInOne },
			{ _T("MainWnd.Btn.Close.normal"), DouResIDType::SubItem, _T("MainWnd.Btn.Close"), 1 },
			{ _T("MainWnd.Btn.Close.hover"), DouResIDType::SubItem, _T("MainWnd.Btn.Close"), 2 },
			{ _T("MainWnd.Btn.Close.press"), DouResIDType::SubItem, _T("MainWnd.Btn.Close"), 3 },
		};
	}
};