#pragma once
//二态图片类，可以响应MouseMove、MouseLeave
class CDouImageExObject : public CDouControlBase, public CDouImageInfoBase, public CDouImageTwoStateAttr
{
public:
	CDouImageExObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		m_ControlType = DouControlType::DouImageEx;
	}
	void DrawControl(HDC hdc)
	{
		String strResID = GetImageNormalResID();
		if (DouControlState::Hover == m_iCurState)
		{
			strResID = GetImageHoverResID();
		}
		DouBitmapSrcInfo* pBmpSrcInfo = gBmpManager.GetBmpSrcInfo(strResID);
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
};