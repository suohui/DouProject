#pragma once

template <class T>
class CDouDlgBase : public CDouControlImpl<T>
{
public:
	CDouDlgBase()
	{
	}
public:
	BEGIN_MSG_MAP(CDouDlgBase)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest)
		CHAIN_MSG_MAP(CDouControlImpl)
	END_MSG_MAP()

	// Overrideables//必须继承，窗体的初始化函数
	void InitDialog()
	{
		// must be implemented
		ATLASSERT(FALSE);
	}
	////设置背景图片路径
	//void SetBkgndFilePath(String strFilePath)
	//{
	//	m_pBkgndImageInfo = CXKnowRender::LoadImageFromFile(strFilePath);
	//}
	//设置背景颜色
	void SetBkgndColorID(String strColorID)
	{
		m_strBkgndColorID = strColorID;
	}
	//设置LOGO
	void SetLogoImageID(String strLogoImageID)
	{
		m_strLogoImageID = strLogoImageID;
	}
	void SetLogoImageRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcLogo.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
	}
	//设置标题
	void SetTitle(String strTitle)
	{
		m_TitleInfoBase.SetText(strTitle);
		T* pThis = static_cast<T*>(this);
		::SetWindowText(pThis->m_hWnd, strTitle.c_str());
	}
	void SetTitleRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcTitle.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
	}
	void SetTitleFontID(String strFontID)
	{
		m_TitleInfoAttr.SetTextFontID(strFontID);
	}
	void SetTitleColorID(String strColorID)
	{
		m_TitleInfoAttr.SetTextColorID(strColorID);
	}
	//获取背景图片句柄
	//HBITMAP GetBkgndHBitmap()
	//{
	//	if (m_pBkgndImageInfo == NULL)
	//		return NULL;
	//	else
	//		return m_pBkgndImageInfo->hBitmap;
	//}
	//获取背景颜色
	String GetBkgndColorID()
	{
		return m_strBkgndColorID;
	}
protected:
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		T* pThis = static_cast<T*>(this);
		pThis->SetMsgHandled(TRUE);

		//修改窗体属性
		pThis->SetWindowLong(GWL_STYLE, pThis->GetWindowLong(GWL_STYLE) & (~WS_BORDER) & WS_POPUP);//无边框窗体
		pThis->SetWindowLong(GWL_EXSTYLE, pThis->GetWindowLong(GWL_EXSTYLE) | WS_EX_APPWINDOW);    //显示在任务栏
																								   //窗体的初始化工作，子类不再响应WM_INITDIALOG，只用重写InitDialog()函数就可以了
		pThis->InitDialog();

		bHandled = pThis->IsMsgHandled();
		return (LRESULT)TRUE;
	}
	void DoPaint(HDC hdc)
	{
		T* pThis = static_cast<T*>(this);
		CRect rcClient;
		pThis->GetClientRect(&rcClient);
		CMemoryDC dcMem(hdc, rcClient);
		//画背景颜色
		if (!m_strBkgndColorID.empty())
		{
			CDouRender::DrawColor(dcMem, rcClient, gColorManager.GetColor(m_strBkgndColorID));
		}

		//画LOGO
		if (!m_strLogoImageID.empty())
		{
			CDouRender::DrawImage(dcMem, m_rcLogo, gBmpManager.GetBmpSrcInfo(m_strLogoImageID), DOU_LEFT | DOU_TOP);
		}
		//画标题
		if (!m_TitleInfoBase.GetText().empty())
		{
			CDouRender::DouDrawText(dcMem, m_TitleInfoBase.GetText(), m_rcTitle, gColorManager.GetColor(m_TitleInfoAttr.GetTextColorID()), m_TitleInfoAttr.GetTextFontID(), m_TitleInfoBase.GetTextPaintStyle(), FALSE, 0);
		}
		//画控件
		DrawAllObject(dcMem);
	}
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if (wParam != NULL)
		{
			DoPaint((HDC)wParam);
		}
		else
		{
			T* pThis = static_cast<T*>(this);
			CPaintDC dc(pThis->m_hWnd);
			DoPaint(dc.m_hDC);
		}
		return 0;
	}
	// no background painting needed (we do it all during WM_PAINT)
	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return TRUE;
	}

	//无边框窗体可拖动https://www.cnblogs.com/findumars/p/5312594.html
	LRESULT OnNcHitTest(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		return HTCAPTION;
	}
private:
	String m_strBkgndColorID;
	String m_strLogoImageID;
	String m_strTitle;
	CRect m_rcLogo;
	
	//标题
	CDouTextInfoBase m_TitleInfoBase;
	CDouTextSingleStateAttr m_TitleInfoAttr;
	CRect m_rcTitle;
};