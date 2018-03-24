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

	SetBkgndColorID(L"system.white");

	CDouTextObject *pTextObj = GetTextObject(L"Title");
	pTextObj->SetText(L"我是标题");
	pTextObj->SetControlRect(300, 10, 50, 20);
	pTextObj->SetTextColorID(L"color.textlink.normal");

	CDouImageObject *pJewel = GetImageObject(L"Jewel");
	pJewel->SetImageResID(L"MainWnd.Bkg.Titlebar");
	pJewel->SetControlRect(0, 0, 681, 56);
	

	CDouImageObject *pLogo = GetImageObject(L"Logo");
	pLogo->SetImageResID(L"MainWnd.Btn.Close.normal");
	pLogo->SetControlRect(680 - 12 - 28, 14, 28, 28);

	CDouButtonObject *pBtnObj = GetButtonObject(L"menu");
	pBtnObj->SetStandardResID(L"MainWnd.Btn.Menu");
	pBtnObj->SetControlRect(680 - 12 - 6 * 2 - 28 * 3, 14, 28, 28);
	//return TRUE;

	//第一个Panel
	CDouImageObject *pPanel = GetImageObject(L"Panel_1");
	CDouImageObject *pETCLogo = GetImageObject(L"ETC.Logo");
	pETCLogo->SetImageResID(_T("MainWnd.ETC.Logo"));
	pETCLogo->SetControlRect(40, 16, 32, 32);
	pETCLogo->SetOwnerControl(pPanel);

	pPanel->SetImageResID(_T("MainWnd.Bkg.PanelSelect"));
	pPanel->SetStretch(TRUE);
	pPanel->SetControlRect(0, 56+40, 681, 64);
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
	CDouImageObject *pPanel = GetImageObject(L"Panel_1");
	pPanel->SetControlVisible(!pPanel->IsControlVisible());
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