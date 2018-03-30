#pragma once

class CDouButtonObject : public CDouControlBase, public CDouButtonFourStateAttr
{
public:
	CDouButtonObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		m_ControlType = DouControlType::DouButton;
	}
	~CDouButtonObject()
	{
	}

protected:
	void DrawControl(HDC hdc)
	{
		String strBkgImageResID;
		switch (m_iCurState)
		{
		case Hover:
			strBkgImageResID = GetButtonHoverResID();
			break;
		case Press:
			strBkgImageResID = GetButtonPressResID();
			break;
		case Disable:
			strBkgImageResID = GetButtonDisableResID();
			break;
		default:
			strBkgImageResID = GetButtonNormalResID();
			break;
		}
		CDouRender::DrawImage(hdc, GetControlPaintRect(), gBmpManager.GetBmpSrcInfo(strBkgImageResID), IsButtonStretch());
	}
};