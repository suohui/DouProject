#pragma once
//Icon图标信息基础类，单一图片信息，例如：按钮上的标识图标、窗体LOGO，
class CDouImageObject : public CDouControlBase, public CDouImageInfoBase, public CDouImageSingleStateAttr
{
public:
	CDouImageObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		m_ControlType = DouControlType::DouImage;
	}
	~CDouImageObject()
	{
	}
protected:
	void DrawControl(HDC hdc)
	{
		if (!GetImageColorID().empty())
		{
			CDouRender::DrawColor(hdc, GetControlPaintRect(), gColorManager.GetColor(GetImageColorID()));
		}
		DouBitmapSrcInfo* pBmpSrcInfo = gBmpManager.GetBmpSrcInfo(GetImageResID());
		CDouRender::DrawImage(hdc, GetControlPaintRect(), pBmpSrcInfo, GetImagePaintStyle(), IsImageStretch());
	}
};