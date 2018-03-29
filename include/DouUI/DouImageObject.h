#pragma once
//Iconͼ����Ϣ�����࣬��һͼƬ��Ϣ�����磺��ť�ϵı�ʶͼ�ꡢ����LOGO��
class CDouImageObject : public CDouControlBase
{
public:
	CDouImageObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		m_uPaintStyle = DOU_CENTER | DOU_VCENTER;
		m_bStretch = FALSE;
		m_bEnableMouseEvent = FALSE;
		m_ControlType = DouControlType::DouImage;
	}
	~CDouImageObject()
	{
	}
	
	void SetImageResID(String strID)
	{
		m_strID = strID;
	}

	void SetPaintStyle(UINT uStyle)
	{
		m_uPaintStyle = uStyle;
	}

	void EnableMouseEvent(BOOL bEnableMouseEvent = TRUE)
	{
		m_bEnableMouseEvent = bEnableMouseEvent;
	}

	UINT GetPaintStyle()
	{
		return m_uPaintStyle;
	}

	void SetStretch(BOOL bStretch = FALSE)
	{
		m_bStretch = bStretch;
	}

	BOOL IsMouseEvent()
	{
		return m_bEnableMouseEvent;
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
	UINT  m_uPaintStyle; //�ؼ�������ʽ
	String m_strID;
	BOOL m_bStretch;
	BOOL m_bEnableMouseEvent;	//������ӦMouseMove��MouseLeave��Ϣ 
};