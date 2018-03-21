#pragma once

template <class T>
class CDouDlgBase : public CDouControlImpl<T>
{
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
	void SetBkgndColor(DWORD dwColor)
	{
		m_dwBkgndColor = dwColor;
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
	DWORD GetBkgndColor()
	{
		return m_dwBkgndColor;
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
		if (m_dwBkgndColor != 0)
		{
			CDouRender::DrawColor(dcMem, rcClient, m_dwBkgndColor);
		}
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
	DWORD m_dwBkgndColor;	//������ɫ
};