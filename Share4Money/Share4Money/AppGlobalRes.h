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
			{ _T("color.textlink.normal"), HexColor, 0x0084ff },
			{ _T("MainPanel.TextColor.Major"), HexColor, 0x6D5539 },
			{ _T("MainPanel.TextColor.Minor"), HexColor, 0xA9A9A9 },
			{ _T("MainPanel.TextColor.Vital"), HexColor, 0xCB8C25 },
			{ _T("MainPanel.TextColor.Hint"), HexColor, 0xE39C29 },
			{ _T("MainPanel.TextColor.BottomPanel"), HexColor, 0xFFF0B5 },
		};
	}

	static void GetFontResInfo(std::vector<TDouFontInfo>& arrFontInfo)
	{
		arrFontInfo =
		{
			{ _T("default.font"), 12, FALSE, FALSE, FALSE },
			{ _T("Font13"), 13, FALSE, FALSE, FALSE },
			{ _T("Font14"), 14, FALSE, FALSE, FALSE },
			{ _T("Font14.U"), 14, FALSE, TRUE, FALSE },
			{ _T("Font14.B"), 14, TRUE, FALSE, FALSE },
		};
	}

	static void GetBitmapResInfo(std::vector<TDouBitmapInfo>& arrBmpResInfo)
	{
		arrBmpResInfo =
		{
			{ _T("MainWnd.Btn.Menu"), DouResIDType::Bitmap, _T("主界面\\更多.png"), DouBitmapType::OnlyOne },	//必须先有ItemList，后有SubItem
			{ _T("MainWnd.Btn.Min"), DouResIDType::Bitmap, _T("主界面\\最小化.png"), DouBitmapType::OnlyOne },
			{ _T("MainWnd.Btn.Close"), DouResIDType::Bitmap, _T("主界面\\关闭.png"), DouBitmapType::OnlyOne },
			{ _T("MainWnd.SystemBtn.Hover"), DouResIDType::Bitmap, _T("主界面\\按钮hover选中滑块.png"), DouBitmapType::OnlyOne },
			{ _T("MainWnd.Logo"), DouResIDType::Bitmap, _T("主界面\\Logo.png"), DouBitmapType::OnlyOne },
			{ _T("MainWnd.Bkg.BottomPanel"), DouResIDType::Bitmap, _T("主界面\\主页面背景2.png"), DouBitmapType::OnlyOne },
			{ _T("MainWnd.Btn.Earn"), DouResIDType::ItemList, _T("主界面\\赚宝按钮.png"), DouBitmapType::ThreeInOne },
			{ _T("MainWnd.Btn.Earn.normal"), DouResIDType::SubItem, _T("MainWnd.Btn.Earn"), 1 },
			{ _T("MainWnd.Btn.Earn.hover"), DouResIDType::SubItem, _T("MainWnd.Btn.Earn"), 2 },
			{ _T("MainWnd.Btn.Earn.press"), DouResIDType::SubItem, _T("MainWnd.Btn.Earn"), 3 },
			{ _T("MainWnd.Btn.Income"), DouResIDType::ItemList, _T("主界面\\收益按钮.png"), DouBitmapType::ThreeInOne },
			{ _T("MainWnd.Btn.Income.normal"), DouResIDType::SubItem, _T("MainWnd.Btn.Income"), 1 },
			{ _T("MainWnd.Btn.Income.hover"), DouResIDType::SubItem, _T("MainWnd.Btn.Income"), 2 },
			{ _T("MainWnd.Btn.Income.press"), DouResIDType::SubItem, _T("MainWnd.Btn.Income"), 3 },
			{ _T("MainWnd.Btn.Withdrawal"), DouResIDType::ItemList, _T("主界面\\提现按钮.png"), DouBitmapType::ThreeInOne },
			{ _T("MainWnd.Btn.Withdrawal.normal"), DouResIDType::SubItem, _T("MainWnd.Btn.Withdrawal"), 1 },
			{ _T("MainWnd.Btn.Withdrawal.hover"), DouResIDType::SubItem, _T("MainWnd.Btn.Withdrawal"), 2 },
			{ _T("MainWnd.Btn.Withdrawal.press"), DouResIDType::SubItem, _T("MainWnd.Btn.Withdrawal"), 3 },
		};
	}
};