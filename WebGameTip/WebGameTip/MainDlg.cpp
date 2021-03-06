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
	int iWidth = 312;
	int iHeight = 213;
	MoveWindow(0, 0, iWidth, iHeight);
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

	//SetBkgndColorID(_T("system.white"));
	SetBkgndResID(_T("MainWnd.Bkg.PureText"));
	//创建标题栏
	CDouTextObject* pTitleObj = GetTextObject(_T("MainWnd.Title"));
	pTitleObj->SetText(_T("影音游戏见面礼"));
	pTitleObj->SetControlRect(38,0,300,36);
	pTitleObj->SetTextColorID(_T("system.white"));
	pTitleObj->SetTextFontID(_T("Font14"));
	pTitleObj->SetTextPaintStyle(DOU_LEFT | DOU_VCENTER);

	CDouButtonObject* pBtnClose = GetButtonObject(_T("MainWnd.Btn.Close"));
	pBtnClose->SetButtonStandardResID(_T("MainWnd.Btn.Close"));
	pBtnClose->SetControlRect(iWidth - 11 - 10, 13, 10, 10);//SetButtonPaintStyle无效
	//创建正文
	CDouTextLinkObject* pHyperLink = GetTextLinkObject(_T("MainPanel.Title"));
	pHyperLink->SetText(_T("恭喜您，迅雷会员免费领。"));
	pHyperLink->SetControlRect(0, 36 + 15, iWidth, 18);
	pHyperLink->SetTextPaintStyle(DT_TOP | DOU_CENTER);
	pHyperLink->SetTextColorID(_T("MainPanel.TextColor.Title"));
	pHyperLink->SetTextFontID(_T("Font18"));
	
	pHyperLink = GetTextLinkObject(_T("MainPanel.Content"));
	pHyperLink->SetText(_T("预创建服务器：《山海关》\r\n对于共享单车的资金存管问题，网贷平台爱钱帮联合创始人赵静婷认为，在网贷行业发展初期，资金池是导致平台卷款跑路的最大问题，监管部门把银行存管作为合规运营的重要门槛之一，自此网贷资金池的问题得到有效解"));
	pHyperLink->SetControlRect(25, 88, iWidth - 50, 100);
	pHyperLink->SetTextPaintStyle(DT_TOP | DOU_CENTER);
	pHyperLink->SetTextColorID(_T("MainPanel.TextColor.Content"));
	pHyperLink->SetTextFontID(_T("Font14"));
	pHyperLink->SetTextMultiLine(TRUE);
	pHyperLink->SetTextRowSpan(0);

	//创建控制按钮
	CDouCheckboxObject* pCheckboxObj = GetCheckboxObject(_T("MainWnd.Checkbox.ReceiveIcons"));
	pCheckboxObj->SetButtonStandardResID(_T("MainWnd.Checkbox.ReceiveIcons"));
	pCheckboxObj->SetControlRect(200, iHeight - 18, 129, 16);
	pCheckboxObj->SetCheckboxImageRect(2, 2, 12, 12);
	pCheckboxObj->SetText(_T("铺游戏图标"));
	pCheckboxObj->SetTextFontID(_T("default.font"));
	pCheckboxObj->SetTextColorID(_T("MainPanel.TextColor.Content"));
	pCheckboxObj->SetTextRect(2 + 12 + 2, 0, 100, 12);
	pCheckboxObj->SetTextPaintStyle(DOU_LEFT | DOU_TOP);
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

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CDouCheckboxObject* pCheckboxObj = GetCheckboxObject(_T("MainWnd.Checkbox.ReceiveIcons"));
	BOOL bCheck = pCheckboxObj->IsChecked();
	if (bCheck)
	{
		CAboutDlg dlg;
		dlg.DoModal();
	}
	return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	CloseDialog(wID);
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
