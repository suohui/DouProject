// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler,
		public CDouDlgBase<CMainDlg>
{
public:
	enum { IDD = IDD_MAINDLG };

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)

		MESSAGE_HANDLER(WM_DOUCONTROLCLICK, OnDouControlClick)
		//MESSAGE_HANDLER(WM_DOUCONTROLMOUSEMOVE, OnDouControlMouseMove)
		//MESSAGE_HANDLER(WM_DOUCONTROLMOUSELEAVE, OnDouControlMouseLeave)

		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)

		CHAIN_MSG_MAP(CDouDlgBase)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	void InitDialog();
	void SetCurrencyPanel(String strCurrency, int iPanelTop, DouControlState enumState = DouControlState::Normal);
	void SetCurrencyLogo(String strCurrency, String strDescription, DouControlState enumState = DouControlState::Normal);
	void SetCurrencyPrice(String strCurrency, String strBalance, String strPrice, DouControlState enumState = DouControlState::Normal);
	void SetCurrencySpeed(String strCurrency, String strDaySpeed, String strCurSpeed, DouControlState enumState = DouControlState::Normal);
	void SetCurrencyButton(String strCurrency, DouControlState enumState = DouControlState::Normal);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnDouControlClick(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDouControlMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDouControlMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	void CloseDialog(int nVal);

private:
	int m_iCurrencyLeft;
	int m_iCurrencyDescriptionLeft;
	int m_iPriceLeft;
	int m_iSpeedLeft;
};


//待解决的问题：
//1、绘制文本时，会有间隙