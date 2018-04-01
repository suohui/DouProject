#pragma once

class CDouButtonObject : public CDouControlBase, public CDouButtonFourStateAttr,
						 public CDouImageInfoBase, public CDouImageSingleStateAttr,
						 public CDouTextInfoBase, public CDouTextFourStateAttr
{
public:
	CDouButtonObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		m_ControlType = DouControlType::DouButton;
	}
	~CDouButtonObject()
	{
	}

	void SetImageRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcImage.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
	}

	void SetTextRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcText.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
	}
protected:
	void DrawControl(HDC hdc)
	{
		String strBkgImageResID;
		String strColorResID;
		String strFontResID;
		switch (m_iCurState)
		{
		case Hover:
			strBkgImageResID = GetButtonHoverResID();
			strColorResID = GetTextHoverColorID();
			strFontResID = GetTextHoverFontID();
			break;
		case Press:
			strBkgImageResID = GetButtonPressResID();
			strColorResID = GetTextPressColorID();
			strFontResID = GetTextPressFontID();
			break;
		case Disable:
			strBkgImageResID = GetButtonDisableResID();
			strColorResID = GetTextDisableColorID();
			strFontResID = GetTextDisableFontID();
			break;
		default:
			strBkgImageResID = GetButtonNormalResID();
			strColorResID = GetTextNormalColorID();
			strFontResID = GetTextNormalFontID();
			break;
		}
		CRect rcButton = GetControlPaintRect();
		CDouRender::DrawImage(hdc, rcButton, gBmpManager.GetBmpSrcInfo(strBkgImageResID), IsButtonStretch());
		CRect rcImage(CPoint(rcButton.left + m_rcImage.left, rcButton.top + m_rcImage.top), CSize(m_rcImage.Width(), m_rcImage.Height()));
		if (!rcImage.IsRectEmpty())
		{
			CDouRender::DrawImage(hdc, rcImage, gBmpManager.GetBmpSrcInfo(GetImageResID()), GetImagePaintStyle(), IsImageStretch());
		}
		CRect rcText(CPoint(rcButton.left + m_rcText.left, rcButton.top + m_rcText.top), CSize(m_rcText.Width(), m_rcText.Height()));
		if (!rcText.IsRectEmpty())
		{
			CDouRender::DouDrawText(hdc, GetText(), rcText, gColorManager.GetColor(strColorResID), strFontResID, GetTextPaintStyle(), FALSE, 0);
		}
	}
private:
	CRect m_rcImage;
	CRect m_rcText;
};