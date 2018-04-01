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
	// center the dialog on the screen
	int iWidth = 370;
	int iHeight = 600;
	MoveWindow(0, 0, iWidth, iHeight);
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

	SetBkgndColorID(_T("system.white"));
	SetLogoImageID(_T("MainWnd.Logo"));
	SetLogoImageRect(12, 11, 14, 13);

	SetTitle(_T("共享赚宝"));
	SetTitleRect(12 + 14 + 6, 8, 200, 14);
	SetTitleColorID(_T("MainPanel.TextColor.Major"));
	SetTitleFontID(_T("Font13"));
	//三个系统按钮
	CDouButtonObject* pButtonObj = GetButtonObject(_T("MainWnd.Btn.Menu"));
	pButtonObj->SetButtonHoverResID(_T("MainWnd.SystemBtn.Hover"));
	pButtonObj->SetButtonPressResID(_T("MainWnd.SystemBtn.Hover"));
	pButtonObj->SetControlRect(iWidth - 12 - 15 - 11 - 15 - 11 - 15, 1, 25, 25);
	pButtonObj->SetImageRect(0, 0, 25, 25);
	pButtonObj->SetImagePaintStyle(DOU_CENTER | DOU_BOTTOM);
	pButtonObj->SetImageResID(_T("MainWnd.Btn.Menu"));

	pButtonObj = GetButtonObject(_T("MainWnd.Btn.Min"));
	pButtonObj->SetButtonHoverResID(_T("MainWnd.SystemBtn.Hover"));
	pButtonObj->SetButtonPressResID(_T("MainWnd.SystemBtn.Hover"));
	pButtonObj->SetControlRect(iWidth - 12 - 15 - 11 - 15, 1, 25, 25);
	pButtonObj->SetImageRect(0, 0, 25, 25);
	pButtonObj->SetImagePaintStyle(DOU_CENTER | DOU_BOTTOM);
	pButtonObj->SetImageResID(_T("MainWnd.Btn.Min"));

	pButtonObj = GetButtonObject(_T("MainWnd.Btn.Close"));
	pButtonObj->SetButtonHoverResID(_T("MainWnd.SystemBtn.Hover"));
	pButtonObj->SetButtonPressResID(_T("MainWnd.SystemBtn.Hover"));
	pButtonObj->SetControlRect(iWidth - 12 - 15, 1, 25, 25);
	pButtonObj->SetImageRect(0, 0, 25, 25);
	pButtonObj->SetImagePaintStyle(DOU_CENTER | DOU_BOTTOM);
	pButtonObj->SetImageResID(_T("MainWnd.Btn.Close"));


	//标签按钮
	CDouImageObject* pImageObj = GetImageObject(_T("MainWnd.BottomPanel"));
	pImageObj->SetImageResID(_T("MainWnd.Bkg.BottomPanel"));
	pImageObj->SetControlRect(1, iHeight - 112, iWidth - 2, 111);
	//三个标签按钮
	pButtonObj = GetButtonObject(_T("MainWnd.BottomPanel.Income"));
	pButtonObj->SetButtonStandardResID(_T("MainWnd.Btn.Income"));
	pButtonObj->SetControlRect(56, 111 - 30 - 42, 42, 60);
	pButtonObj->SetTextRect(0, 0, 42, 60);
	pButtonObj->SetText(_T("收益"));
	pButtonObj->SetTextNormalColorID(_T("MainPanel.TextColor.BottomPanel"));
	pButtonObj->SetTextHoverColorID(_T("MainPanel.TextColor.BottomPanel"));
	pButtonObj->SetTextPressColorID(_T("MainPanel.TextColor.BottomPanel"));
	pButtonObj->SetTextNormalFontID(_T("Font13"));
	pButtonObj->SetTextHoverFontID(_T("Font13"));
	pButtonObj->SetTextPressFontID(_T("Font13"));
	pButtonObj->SetTextPaintStyle(DOU_CENTER | DOU_BOTTOM);
	pButtonObj->SetOwnerControl(pImageObj);

	pButtonObj = GetButtonObject(_T("MainWnd.BottomPanel.Earn"));
	pButtonObj->SetButtonStandardResID(_T("MainWnd.Btn.Earn"));
	pButtonObj->SetControlRect(56 + 42 + 65, 111 - 30 - 42, 42, 60);
	pButtonObj->SetTextRect(0, 0, 42, 60);
	pButtonObj->SetText(_T("赚宝"));
	pButtonObj->SetTextNormalColorID(_T("MainPanel.TextColor.BottomPanel"));
	pButtonObj->SetTextHoverColorID(_T("MainPanel.TextColor.BottomPanel"));
	pButtonObj->SetTextPressColorID(_T("MainPanel.TextColor.BottomPanel"));
	pButtonObj->SetTextNormalFontID(_T("Font13"));
	pButtonObj->SetTextHoverFontID(_T("Font13"));
	pButtonObj->SetTextPressFontID(_T("Font13"));
	pButtonObj->SetTextPaintStyle(DOU_CENTER | DOU_BOTTOM);
	pButtonObj->SetOwnerControl(pImageObj);

	pButtonObj = GetButtonObject(_T("MainWnd.BottomPanel.Withdrawal"));
	pButtonObj->SetButtonStandardResID(_T("MainWnd.Btn.Withdrawal"));
	pButtonObj->SetControlRect(56 + 42 + 65 + 42 + 65, 111 - 30 - 42, 42, 60);
	pButtonObj->SetTextRect(0, 0, 42, 60);
	pButtonObj->SetText(_T("提现"));
	pButtonObj->SetTextNormalColorID(_T("MainPanel.TextColor.BottomPanel"));
	pButtonObj->SetTextHoverColorID(_T("MainPanel.TextColor.BottomPanel"));
	pButtonObj->SetTextPressColorID(_T("MainPanel.TextColor.BottomPanel"));
	pButtonObj->SetTextNormalFontID(_T("Font13"));
	pButtonObj->SetTextHoverFontID(_T("Font13"));
	pButtonObj->SetTextPressFontID(_T("Font13"));
	pButtonObj->SetTextPaintStyle(DOU_CENTER | DOU_BOTTOM);
	pButtonObj->SetOwnerControl(pImageObj);
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
	CAboutDlg dlg;
	dlg.DoModal();
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
