#pragma once
//Iconͼ����Ϣ�����࣬��һͼƬ��Ϣ�����磺��ť�ϵı�ʶͼ�ꡢ����LOGO��
class CDouImageObject : public CDouControlBase, public CDouImageInfoBase
{
public:
	CDouImageObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		m_bEnableMouseEvent = FALSE;
		m_ControlType = DouControlType::DouImage;
	}
	~CDouImageObject()
	{
	}

	void EnableMouseEvent(BOOL bEnableMouseEvent = TRUE)
	{
		m_bEnableMouseEvent = bEnableMouseEvent;
	}

	BOOL IsMouseEvent()
	{
		return m_bEnableMouseEvent;
	}
protected:
	void DrawControl(HDC hdc)
	{
		DouBitmapSrcInfo* pBmpSrcInfo = gBmpManager.GetBmpSrcInfo(GetImageResID());
		if (NULL != pBmpSrcInfo)
		{
			if (IsImageStretch())
			{
				CDouRender::DrawImage(hdc, GetControlPaintRect(), pBmpSrcInfo, TRUE);
			}
			else
			{
				CSize szImage(pBmpSrcInfo->rcItem.Width(), pBmpSrcInfo->rcItem.Height());
				CRect rcPaintRect = GetControlPaintRect();
				CPoint ptLeftTop = CDouRender::GetControlPaintPoint(rcPaintRect, szImage, GetImagePaintStyle());
				CDouRender::DrawImage(hdc, CRect(ptLeftTop, szImage), pBmpSrcInfo, FALSE);
			}
		}
	}
private:
	BOOL m_bEnableMouseEvent;	//������ӦMouseMove��MouseLeave��Ϣ 
};