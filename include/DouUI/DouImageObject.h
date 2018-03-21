#pragma once
//Icon图标信息基础类，单一图片信息，例如：按钮上的标识图标、窗体LOGO，
class CDouImageObject : public CDouControlBase
{
public:
	CDouImageObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
	}
	~CDouImageObject()
	{
	}

	void SetImageResID(String strID)
	{
		m_strID = strID;
		::InvalidateRect(m_hWnd, &m_rcControl, TRUE);
	}

	void Draw(HDC hdc)
	{
		CDouRender::DrawImage(hdc, m_rcControl, gBmpManager.GetBmpSrcInfo(m_strID), FALSE);
	}
private:
	String m_strID;
};