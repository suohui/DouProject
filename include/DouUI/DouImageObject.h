#pragma once
//Icon图标信息基础类，单一图片信息，例如：按钮上的标识图标、窗体LOGO，
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
		if (m_bVisible && !m_rcControl.IsRectEmpty() && (NULL != pBmpSrcInfo) && IsOwnerControlVisible())
		{
			CDouRender::DrawImage(hdc, m_rcControl, pBmpSrcInfo, m_bStretch);
		}
	}
private:
	String m_strID;
	BOOL m_bStretch;
};