// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "MainDlg.h"

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{
	UIUpdateChildWindows();
	return FALSE;
}

void CMainDlg::InitDialog()
{
	MoveWindow(0, 0, 681, 451);
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(hIconSmall, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);

	m_iCurrencyLeft = 40;
	m_iCurrencyDescriptionLeft = m_iCurrencyLeft + 32 + 7;
	m_iPriceLeft = m_iCurrencyDescriptionLeft + 116 + 35;
	m_iSpeedLeft = m_iPriceLeft + 116 + 45;

	SetBkgndColorID(L"system.white");

	CDouImageObject *pTitlebar = GetImageObject(L"Titlebar");
	pTitlebar->SetImageResID(L"MainWnd.Bkg.Titlebar");
	pTitlebar->SetControlRect(0, 0, 681, 56);

	CDouTextObject *pTextObj = GetTextObject(L"Title");
	pTextObj->SetText(L"我是标题");
	pTextObj->SetControlRect(300, 0, 50, 20);
	pTextObj->SetTextColorID(L"color.textlink.normal");
	pTextObj->SetOwnerControl(pTitlebar);

	CDouImageObject *pLogo = GetImageObject(L"Logo");
	pLogo->SetImageResID(L"MainWnd.Logo");
	pLogo->SetControlRect(22, 0, 167, 56);
	pLogo->SetOwnerControl(pTitlebar);

	CDouButtonObject *pBtnObj = GetButtonObject(L"Menu");
	pBtnObj->SetStandardResID(L"MainWnd.Btn.Menu");
	pBtnObj->SetControlRect(681 - 12 - 6 * 2 - 28 * 3, 14, 28, 28);
	pBtnObj->SetOwnerControl(pTitlebar);

	pBtnObj = GetButtonObject(L"Min");
	pBtnObj->SetStandardResID(L"MainWnd.Btn.Min");
	pBtnObj->SetControlRect(681 - 12 - 6 * 1 - 28 * 2, 14, 28, 28);
	pBtnObj->SetOwnerControl(pTitlebar);

	pBtnObj = GetButtonObject(L"Close");
	pBtnObj->SetStandardResID(L"MainWnd.Btn.Close");
	pBtnObj->SetControlRect(681 - 12 - 28, 14, 28, 28);
	pBtnObj->SetOwnerControl(pTitlebar);

	//列表头
	CDouImageObject *pHeaderObject = GetImageObject(L"SheetHeader");
	//pHeaderObject->SetImageResID(_T("MainWnd.Bkg.Titlebar"));
	//pHeaderObject->SetStretch(TRUE);
	pHeaderObject->SetControlRect(0, 56, 681, 40);

	//pTextObj = GetTextObject(L"Currency");
	//pTextObj->SetText(L"Currency");
	//pTextObj->SetControlRect(m_iCurrencyLeft, 0, 116, 40);
	//pTextObj->SetTextColorID(_T("MainPanel.Currency.Minor"));
	//pTextObj->SetTextFontID(_T("Font14"));
	//pTextObj->SetPaintStyle(DOU_VCENTER);
	//pTextObj->SetOwnerControl(pHeaderObject);

	//pTextObj = GetTextObject(L"Price");
	//pTextObj->SetText(L"Balance / Price");
	//pTextObj->SetControlRect(m_iPriceLeft, 0, 116, 40);
	//pTextObj->SetTextColorID(_T("MainPanel.Currency.Minor"));
	//pTextObj->SetTextFontID(_T("Font14"));
	//pTextObj->SetPaintStyle(DOU_VCENTER);
	//pTextObj->SetOwnerControl(pHeaderObject);

	//pTextObj = GetTextObject(L"Speed");
	//pTextObj->SetText(L"Speed");
	//pTextObj->SetControlRect(m_iSpeedLeft, 0, 116, 40);
	//pTextObj->SetTextColorID(_T("MainPanel.Currency.Minor"));
	//pTextObj->SetTextFontID(_T("Font14"));
	//pTextObj->SetPaintStyle(DOU_VCENTER);
	//pTextObj->SetOwnerControl(pHeaderObject);

	//第一个Panel
	//SetCurrencyPanel(_T("ETC"), 56 + 40, DouControlState::Hover);
	//SetCurrencyLogo(_T("ETC"), _T("Ethereum Classic"), DouControlState::Hover);
	//SetCurrencyPrice(_T("ETC"), L"0.00826479", L"29.880", DouControlState::Hover);
	//SetCurrencySpeed(_T("ETC"), L"0.00826479", L"29", DouControlState::Hover);
	//SetCurrencyButton(_T("ETC"), DouControlState::Hover);

	//第二个Panel
	SetCurrencyPanel(_T("ZEC"), 56 + 40 + 64);
	SetCurrencyLogo(_T("ZEC"), _T("ZCash"));
	SetCurrencyPrice(_T("ZEC"), L"0", L"15.880");
	SetCurrencySpeed(_T("ZEC"), L"0", L"15");
	SetCurrencyButton(_T("ZEC"));

	//第三个Panel
	//SetCurrencyPanel(_T("XMR"), 56 + 40 + 64 + 64, DouControlState::Press);
	//SetCurrencyLogo(_T("XMR"), _T("MONERO"), DouControlState::Press);
	//SetCurrencyPrice(_T("XMR"), L"0.78", L"25.880", DouControlState::Press);
	//SetCurrencySpeed(_T("XMR"), L"0.78", L"25", DouControlState::Press);
	//SetCurrencyButton(_T("XMR"), DouControlState::Press);

	//底部状态栏
	CDouImageObject *pStatusObject = GetImageObject(L"StatusBar");
	pStatusObject->SetImageResID(_T("MainWnd.Bkg.PanelSelect"));
	pStatusObject->SetStretch(TRUE);
	pStatusObject->SetControlRect(0, 451-32, 681, 32);
}

void CMainDlg::SetCurrencyPanel(String strCurrency, int iPanelTop, DouControlState enumState/* = DouControlState::Normal*/)
{
	CDouImageObject *pPanel = GetImageObject(strCurrency + _T(".Panel"));
	pPanel->EnableMouseEvent(TRUE);
	pPanel->SetStretch(TRUE);
	switch (enumState)
	{
	case Hover:
		pPanel->SetImageResID(_T("MainWnd.Bkg.PanelHover"));
		break;
	case Press:
		pPanel->SetImageResID(_T("MainWnd.Bkg.PanelSelect"));
		break;
	default:
		pPanel->SetImageResID(_T(""));
		break;
	}
	pPanel->SetControlRect(0, iPanelTop, 681, 64);
}

void CMainDlg::SetCurrencyLogo(String strCurrency, String strDescription, DouControlState enumState/* = DouControlState::Normal*/)
{
	CDouImageObject *pLogoImageObject = GetImageObject(strCurrency + _T(".Logo"));
	pLogoImageObject->SetImageResID(strCurrency + _T(".Normal.Logo"));
	if (pLogoImageObject->GetOwnerControl() == NULL)
	{
		pLogoImageObject->SetControlRect(m_iCurrencyLeft, 0, 32, 64);
		pLogoImageObject->SetOwnerControl(GetImageObject(strCurrency + _T(".Panel")));
	}

	CDouTextObject* pTextObject = GetTextObject(strCurrency + _T(".Text"));
	pTextObject->SetText(strCurrency);
	if (pTextObject->GetOwnerControl() == NULL)
	{
		pTextObject->SetControlRect(m_iCurrencyDescriptionLeft, 12, 116, 32);
		pTextObject->SetOwnerControl(GetImageObject(strCurrency + _T(".Panel")));
	}

	CDouTextObject* pDescriptionTextObject = GetTextObject(strCurrency + _T(".Description"));
	pDescriptionTextObject->SetText(strDescription);
	if (pDescriptionTextObject->GetOwnerControl() == NULL)
	{
		pDescriptionTextObject->SetControlRect(m_iCurrencyDescriptionLeft, 20, 118, 32);
		pDescriptionTextObject->SetPaintStyle(DOU_BOTTOM);
		pDescriptionTextObject->SetOwnerControl(GetImageObject(strCurrency + _T(".Panel")));
	}
	switch (enumState)
	{
	case Press:
		pTextObject->SetTextFontID(_T("Font14.B"));
		pTextObject->SetTextColorID(_T("MainPanel.Currency.Major"));
		pDescriptionTextObject->SetTextFontID(_T("Font14.B"));
		pDescriptionTextObject->SetTextColorID(_T("MainPanel.Currency.Minor"));
		break;
	case Disable:
		pTextObject->SetTextFontID(_T("Font14"));
		pTextObject->SetTextColorID(_T("MainPanel.Currency.Minor"));
		pDescriptionTextObject->SetTextFontID(_T("Font14"));
		pDescriptionTextObject->SetTextColorID(_T("MainPanel.Currency.Minor"));
		break;
	default:
		pTextObject->SetTextFontID(_T("Font14"));
		pTextObject->SetTextColorID(_T("MainPanel.Currency.Major"));
		pDescriptionTextObject->SetTextFontID(_T("Font14"));
		pDescriptionTextObject->SetTextColorID(_T("MainPanel.Currency.Minor"));
		break;
	}
}

void CMainDlg::SetCurrencyPrice(String strCurrency, String strBalance, String strPrice, DouControlState enumState/* = DouControlState::Normal*/)
{
	CDouTextObject* pBalanceTextObject = GetTextObject(strCurrency + _T(".Balance"));
	pBalanceTextObject->SetText(strBalance + _T(" <html color='MainPanel.Currency.Minor'>") + strCurrency + _T("</html>"));
	if (pBalanceTextObject->GetOwnerControl() == NULL)
	{
		pBalanceTextObject->EnableHtmlTag(TRUE);
		pBalanceTextObject->SetControlRect(m_iPriceLeft, 12, 116, 32);
		pBalanceTextObject->SetOwnerControl(GetImageObject(strCurrency + _T(".Panel")));
	}

	CDouTextObject* pPriceTextObject = GetTextObject(strCurrency + _T(".Price"));
	pPriceTextObject->SetText(_T("Price $") + strPrice);
	if (pPriceTextObject->GetOwnerControl() == NULL)
	{
		pPriceTextObject->SetControlRect(m_iPriceLeft, 20, 116, 32);
		pPriceTextObject->SetPaintStyle(DOU_BOTTOM);
		pPriceTextObject->SetOwnerControl(GetImageObject(strCurrency + _T(".Panel")));
	}
	switch (enumState)
	{
	case Press:
		pBalanceTextObject->SetTextFontID(_T("Font14.B"));
		pBalanceTextObject->SetTextColorID(_T("MainPanel.Currency.Major"));
		pPriceTextObject->SetTextFontID(_T("Font14.B"));
		pPriceTextObject->SetTextColorID(_T("MainPanel.Currency.Minor"));
		break;
	case Disable:
		pBalanceTextObject->SetTextFontID(_T("Font14"));
		pBalanceTextObject->SetTextColorID(_T("MainPanel.Currency.Minor"));
		pPriceTextObject->SetTextFontID(_T("Font14"));
		pPriceTextObject->SetTextColorID(_T("MainPanel.Currency.Minor"));
		break;
	default:
		pBalanceTextObject->SetTextFontID(_T("Font14"));
		pBalanceTextObject->SetTextColorID(_T("MainPanel.Currency.Major"));
		pPriceTextObject->SetTextFontID(_T("Font14"));
		pPriceTextObject->SetTextColorID(_T("MainPanel.Currency.Minor"));
		break;
	}
}

void CMainDlg::SetCurrencySpeed(String strCurrency, String strDaySpeed, String strCurSpeed, DouControlState enumState/* = DouControlState::Normal*/)
{
	CDouTextObject* pDaySpeedTextObject = GetTextObject(strCurrency + _T(".DaySpeed"));
	pDaySpeedTextObject->SetText(strDaySpeed + _T(" <html color='MainPanel.Currency.Minor'>") + strCurrency + _T("/d</html>"));
	if (pDaySpeedTextObject->GetOwnerControl() == NULL)
	{
		pDaySpeedTextObject->EnableHtmlTag(TRUE);
		pDaySpeedTextObject->SetTextFontID(_T("Font14.B"));
		pDaySpeedTextObject->SetTextColorID(_T("MainPanel.Currency.Major"));
		pDaySpeedTextObject->SetControlRect(m_iSpeedLeft, 12, 132, 32);
		pDaySpeedTextObject->SetOwnerControl(GetImageObject(strCurrency + _T(".Panel")));
	}

	CDouTextObject* pCurSpeedTextObject = GetTextObject(strCurrency + _T(".CurSpeed"));
	pCurSpeedTextObject->SetText(strCurSpeed + _T(" SOL/s"));
	if (pCurSpeedTextObject->GetOwnerControl() == NULL)
	{
		pCurSpeedTextObject->SetTextFontID(_T("Font14.B"));
		pCurSpeedTextObject->SetTextColorID(_T("MainPanel.Currency.Minor"));
		pCurSpeedTextObject->SetControlRect(m_iSpeedLeft, 20, 132, 32);
		pCurSpeedTextObject->SetPaintStyle(DOU_BOTTOM);
		pCurSpeedTextObject->SetOwnerControl(GetImageObject(strCurrency + _T(".Panel")));
	}

	switch (enumState)
	{
	case Press:
		pDaySpeedTextObject->SetControlVisible(TRUE);
		pCurSpeedTextObject->SetControlVisible(TRUE);
		break;
	default:
		pDaySpeedTextObject->SetControlVisible(FALSE);
		pCurSpeedTextObject->SetControlVisible(FALSE);
		break;
	}
}

void CMainDlg::SetCurrencyButton(String strCurrency, DouControlState enumState/* = DouControlState::Normal*/)
{
	CDouButtonObject* pStartBtnObj = GetButtonObject(strCurrency + L".Btn.Start");
	if (pStartBtnObj->GetOwnerControl() == NULL)
	{
		pStartBtnObj->SetStandardResID(L"MainWnd.Btn.Start");
		pStartBtnObj->SetControlRect(681 - 34 - 28 * 2 - 15, 18, 28, 28);
		pStartBtnObj->SetOwnerControl(GetImageObject(strCurrency + _T(".Panel")));
	}

	CDouButtonObject* pPauseBtnObj = GetButtonObject(strCurrency + L".Btn.Pause");
	if (pPauseBtnObj->GetOwnerControl() == NULL)
	{
		pPauseBtnObj->SetStandardResID(L"MainWnd.Btn.Pause");
		pPauseBtnObj->SetControlRect(681 - 34 - 28 * 2 - 15, 18, 28, 28);
		pPauseBtnObj->SetOwnerControl(GetImageObject(strCurrency + _T(".Panel")));
	}

	CDouButtonObject* pWidthdrawalBtnObj = GetButtonObject(strCurrency + L".Btn.Withdrawal");
	if (pWidthdrawalBtnObj->GetOwnerControl() == NULL)
	{
		pWidthdrawalBtnObj->SetStandardResID(L"MainWnd.Btn.Withdrawal");
		pWidthdrawalBtnObj->SetControlRect(681 - 34 - 28, 18, 28, 28);
		pWidthdrawalBtnObj->SetOwnerControl(GetImageObject(strCurrency + _T(".Panel")));
	}

	switch (enumState)
	{
	case Normal:
		pStartBtnObj->SetControlVisible(FALSE);
		pPauseBtnObj->SetControlVisible(FALSE);
		pWidthdrawalBtnObj->SetControlVisible(FALSE);
		break;
	case Hover:
		pStartBtnObj->SetControlVisible(TRUE);
		pPauseBtnObj->SetControlVisible(FALSE);
		pWidthdrawalBtnObj->SetControlVisible(TRUE);
		break;
	case Press:
		pStartBtnObj->SetControlVisible(FALSE);
		pPauseBtnObj->SetControlVisible(TRUE);
		pWidthdrawalBtnObj->SetControlVisible(TRUE);
		break;
	}
}

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	return 0;
}

LRESULT CMainDlg::OnDouControlClick(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	CDouControlBase* pCtrl = (CDouControlBase*)lParam;
	switch (pCtrl->GetControlType())
	{
	case DouControlType::DouButton:
		if (pCtrl == GetButtonObject(_T("Min")))
		{
			ShowWindow(SW_MINIMIZE);
		}
		else if (pCtrl == GetButtonObject(_T("Close")))
		{
			CloseDialog(0);
		}
		break;
	default:
		break;
	}
	return 0;
}

LRESULT CMainDlg::OnDouControlMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	CDouImageObject* pCtrl = (CDouImageObject*)lParam;
	if (pCtrl == GetImageObject(_T("ZEC.Panel")))
	{
		pCtrl->SetImageResID(_T("MainWnd.Bkg.PanelSelect"));
		pCtrl->DouInvalidateRect();
	}
	return 0;
}
LRESULT CMainDlg::OnDouControlMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	CDouImageObject* pCtrl = (CDouImageObject*)lParam;
	if (pCtrl == GetImageObject(_T("ZEC.Panel")))
	{
		pCtrl->SetImageResID(_T(""));
		pCtrl->DouInvalidateRect();
	}
	return 0;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CDouImageObject *pPanel = GetImageObject(L"XMR.Panel");
	pPanel->SetControlVisible(!pPanel->IsControlVisible());
	pPanel->DouInvalidateRect();
	// TODO: Add validation code 
	//CloseDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog(wID);
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}