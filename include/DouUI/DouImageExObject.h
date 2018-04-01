#pragma once
//��̬ͼƬ�࣬������ӦMouseMove��MouseLeave
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
		CDouRender::DrawImage(hdc, GetControlPaintRect(), pBmpSrcInfo, GetImagePaintStyle(), IsImageStretch());
	}
private:
};