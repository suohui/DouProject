#pragma once
//Iconͼ����Ϣ�����࣬��һͼƬ��Ϣ�����磺��ť�ϵı�ʶͼ�ꡢ����LOGO��
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