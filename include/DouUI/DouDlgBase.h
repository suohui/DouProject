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

	// Overrideables//����̳У�����ĳ�ʼ������
	void InitDialog()
	{
		// must be implemented
		ATLASSERT(FALSE);
	}
	////���ñ���ͼƬ·��
	//void SetBkgndFilePath(String strFilePath)
	//{
	//	m_pBkgndImageInfo = CXKnowRender::LoadImageFromFile(strFilePath);
	//}
	//���ñ�����ɫ
	void SetBkgndColorID(String strColorID)
	{
		m_strBkgndColorID = strColorID;
	}
	//����LOGO
	void SetLogoImageID(String strLogoImageID)
	{
		m_strLogoImageID = strLogoImageID;
	}
	void SetLogoImageRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcLogo.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
	}
	//���ñ���
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
	//��ȡ����ͼƬ���
	//HBITMAP GetBkgndHBitmap()
	//{
	//	if (m_pBkgndImageInfo == NULL)
	//		return NULL;
	//	else
	//		return m_pBkgndImageInfo->hBitmap;
	//}
	//��ȡ������ɫ
	String GetBkgndColorID()
	{
		return m_strBkgndColorID;
	}
protected:
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		T* pThis = static_cast<T*>(this);
		pThis->SetMsgHandled(TRUE);

		//�޸Ĵ�������
		pThis->SetWindowLong(GWL_STYLE, pThis->GetWindowLong(GWL_STYLE) & (~WS_BORDER) & WS_POPUP);//�ޱ߿���
		pThis->SetWindowLong(GWL_EXSTYLE, pThis->GetWindowLong(GWL_EXSTYLE) | WS_EX_APPWINDOW);    //��ʾ��������
																								   //����ĳ�ʼ�����������಻����ӦWM_INITDIALOG��ֻ����дInitDialog()�����Ϳ�����
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
		//��������ɫ
		if (!m_strBkgndColorID.empty())
		{
			CDouRender::DrawColor(dcMem, rcClient, gColorManager.GetColor(m_strBkgndColorID));
		}

		//��LOGO
		if (!m_strLogoImageID.empty())
		{
			CDouRender::DrawImage(dcMem, m_rcLogo, gBmpManager.GetBmpSrcInfo(m_strLogoImageID), DOU_LEFT | DOU_TOP);
		}
		//������
		if (!m_TitleInfoBase.GetText().empty())
		{
			CDouRender::DouDrawText(dcMem, m_TitleInfoBase.GetText(), m_rcTitle, gColorManager.GetColor(m_TitleInfoAttr.GetTextColorID()), m_TitleInfoAttr.GetTextFontID(), m_TitleInfoBase.GetTextPaintStyle(), FALSE, 0);
		}
		//���ؼ�
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

	//�ޱ߿�����϶�https://www.cnblogs.com/findumars/p/5312594.html
	LRESULT OnNcHitTest(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		return HTCAPTION;
	}
private:
	String m_strBkgndColorID;
	String m_strLogoImageID;
	String m_strTitle;
	CRect m_rcLogo;
	
	//����
	CDouTextInfoBase m_TitleInfoBase;
	CDouTextSingleStateAttr m_TitleInfoAttr;
	CRect m_rcTitle;
};