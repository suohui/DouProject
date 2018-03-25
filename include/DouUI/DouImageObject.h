#pragma once
//Icon图标信息基础类，单一图片信息，例如：按钮上的标识图标、窗体LOGO，
class CDouImageObject : public CDouControlBase
{
public:
	CDouImageObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		m_uPaintStyle = DOU_CENTER | DOU_VCENTER;
		m_bStretch = FALSE;
	}
	~CDouImageObject()
	{
	}
	
	void SetImageResID(String strID)
	{
		m_strID = strID;
		::InvalidateRect(m_hWnd, &GetControlPaintRect(), TRUE);
	}

	void SetPaintStyle(UINT uStyle)
	{
		m_uPaintStyle = uStyle;
	}

	UINT GetPaintStyle()
	{
		return m_uPaintStyle;
	}

	void SetStretch(BOOL bStretch = FALSE)
	{
		m_bStretch = bStretch;
		::InvalidateRect(m_hWnd, &GetControlPaintRect(), TRUE);
	}
protected:
	void DrawControl(HDC hdc)
	{
		DouBitmapSrcInfo* pBmpSrcInfo = gBmpManager.GetBmpSrcInfo(m_strID);
		if (NULL != pBmpSrcInfo)
		{
			if (m_bStretch)
			{
				CDouRender::DrawImage(hdc, GetControlPaintRect(), pBmpSrcInfo, TRUE);
			}
			else
			{
				CSize szImage(pBmpSrcInfo->rcItem.Width(), pBmpSrcInfo->rcItem.Height());
				CRect rcPaintRect = GetControlPaintRect();
				CPoint ptLeftTop = CDouRender::GetControlPaintPoint(rcPaintRect, szImage, m_uPaintStyle);
				CDouRender::DrawImage(hdc, CRect(ptLeftTop, szImage), pBmpSrcInfo, FALSE);
			}
		}
	}
private:
	UINT  m_uPaintStyle; //控件绘制样式
	String m_strID;
	BOOL m_bStretch;
};