#pragma once
//Iconͼ����Ϣ�����࣬��һͼƬ��Ϣ�����磺��ť�ϵı�ʶͼ�ꡢ����LOGO��
class CDouImageObject : public CDouControlBase
{
public:
	CDouImageObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		m_bStretch = FALSE;
	}
	~CDouImageObject()
	{
	}

	void SetImageResID(String strID)
	{
		m_strID = strID;
		::InvalidateRect(m_hWnd, &m_rcControl, TRUE);
	}

	void SetStretch(BOOL bStretch = FALSE)
	{
		m_bStretch = bStretch;
		::InvalidateRect(m_hWnd, &m_rcControl, TRUE);
	}

	void Draw(HDC hdc)
	{
		DouBitmapSrcInfo* pBmpSrcInfo = gBmpManager.GetBmpSrcInfo(m_strID);
		if (m_bVisible && !m_rcControl.IsRectEmpty() && (NULL != pBmpSrcInfo))
		{
			CDouRender::DrawImage(hdc, m_rcControl, pBmpSrcInfo, m_bStretch);
		}
	}
private:
	String m_strID;
	BOOL m_bStretch;
};