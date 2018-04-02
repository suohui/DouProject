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

	SetBkgndColorID(_T("system.white"));
	//����������
	CDouImageObject* pTitleBar = GetImageObject(_T("MainWnd.Bkg.TitleBar"));
	pTitleBar->SetImageColorID(_T("MainWnd.Color.TitleBar"));
	pTitleBar->SetControlRect(0, 0, iWidth, 36);
	CDouImageObject* pLogo = GetImageObject(_T("MainWnd.Logo"));
	pLogo->SetImageResID(_T("MainWnd.Logo"));
	pLogo->SetControlRect(9,0,23,36);
	pLogo->SetImagePaintStyle(DOU_LEFT | DOU_VCENTER);
	pLogo->SetOwnerControl(pTitleBar);
	CDouButtonObject* pBtnClose = GetButtonObject(_T("MainWnd.Btn.Close"));
	pBtnClose->SetButtonStandardResID(_T("MainWnd.Btn.Close"));
	pBtnClose->SetControlRect(iWidth - 11 - 10, 13, 10, 10);//SetButtonPaintStyle��Ч
	pBtnClose->SetOwnerControl(pTitleBar);
	//��������
	CDouTextLinkObject* pHyperLink = GetTextLinkObject(_T("MainPanel.Title"));
	pHyperLink->SetText(_T("��ϲ����Ѹ�׻�Ա����졣"));
	pHyperLink->SetControlRect(0, 36 + 15, iWidth, 18);
	pHyperLink->SetTextPaintStyle(DT_TOP | DOU_CENTER);
	pHyperLink->SetTextColorID(_T("MainPanel.TextColor.Title"));
	pHyperLink->SetTextFontID(_T("Font18"));
	
	pHyperLink = GetTextLinkObject(_T("MainPanel.Content"));
	pHyperLink->SetText(_T("Ԥ��������������ɽ���ء�\nԤ����ʱ�䣺Ԥ������ɫ����ר��998Ԫ��Ϸ�����ÿ�ճ齱���л����ȡiphone7"));
	pHyperLink->SetControlRect(25, 88, iWidth, 266);
	pHyperLink->SetTextPaintStyle(DT_TOP | DOU_CENTER);
	pHyperLink->SetTextColorID(_T("MainPanel.TextColor.Content"));
	pHyperLink->SetTextFontID(_T("Font14"));
	pHyperLink->SetTextMultiLine(TRUE);

	//�������ư�ť

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
