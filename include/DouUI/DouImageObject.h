#pragma once
//Iconͼ����Ϣ�����࣬��һͼƬ��Ϣ�����磺��ť�ϵı�ʶͼ�ꡢ����LOGO��
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
		DouBitmapSrcInfo* pBmpSrcInfo = gBmpManager.GetBmpSrcInfo(m_strID);
		if (m_bVisible && !m_rcControl.IsRectEmpty() && (NULL != pBmpSrcInfo))
		{
			CDouRender::DrawImage(hdc, m_rcControl, pBmpSrcInfo, FALSE);
		}
	}
private:
	String m_strID;
};