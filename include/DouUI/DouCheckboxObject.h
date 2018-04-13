#pragma once

class CDouCheckboxObject : public CDouControlBase,
	public CDouButtonFourStateAttr,
	public CDouTextInfoBase, public CDouTextSingleStateAttr
{
public:
	CDouCheckboxObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		m_ControlType = DouControlType::DouCheckBox;
		m_bChecked = FALSE;
	}

	void SetCheckboxImageRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcCheckboxImage.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
	}

	void SetTextRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcText.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
	}

	void SetChecked(BOOL bCheck = TRUE)
	{
		m_bChecked = bCheck;
	}

	BOOL IsChecked()
	{
		return m_bChecked;
	}
protected:
	void DrawControl(HDC hdc)
	{
		String strBkgImageResID;
		if (m_bChecked)
		{
			switch (m_iCurState)
			{
			case Press:
				strBkgImageResID = GetButtonNormalResID();
				m_bChecked = !m_bChecked;
				break;
			default:
				strBkgImageResID = GetButtonPressResID();
				break;
			}
		}
		else
		{
			switch (m_iCurState)
			{
			case Hover:
				strBkgImageResID = GetButtonHoverResID();
				break;
			case Press:
				strBkgImageResID = GetButtonPressResID();
				m_bChecked = !m_bChecked;
				break;
			case Disable:
				strBkgImageResID = GetButtonDisableResID();
				break;
			default:
				strBkgImageResID = GetButtonNormalResID();
				break;
			}
		}
		CRect rcButton = GetControlPaintRect();
		CRect rcImage(CPoint(rcButton.left + m_rcCheckboxImage.left, rcButton.top + m_rcCheckboxImage.top), CSize(m_rcCheckboxImage.Width(), m_rcCheckboxImage.Height()));
		CDouRender::DrawImage(hdc, rcImage, gBmpManager.GetBmpSrcInfo(strBkgImageResID), IsButtonStretch());

		CRect rcText(CPoint(rcButton.left + m_rcText.left, rcButton.top + m_rcText.top), CSize(m_rcText.Width(), m_rcText.Height()));
		if (!rcText.IsRectEmpty())
		{
			String strColorResID = GetTextColorID();
			String strFontResID = GetTextFontID();
			CDouRender::DouDrawText(hdc, GetText(), rcText, gColorManager.GetColor(strColorResID), strFontResID, GetTextPaintStyle(), FALSE, 0);
		}
	}
private:
	CRect m_rcCheckboxImage;
	CRect m_rcText;
	BOOL m_bChecked;
};