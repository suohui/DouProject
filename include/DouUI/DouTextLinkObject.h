#pragma once
class CDouTextLinkObject : public CDouControlBase, public CDouTextInfoBase, public CDouTextMultiLineAttr, public CDouTextFourStateAttr
{
public:
	CDouTextLinkObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		m_ControlType = DouControlType::DouTextLink;
	}

	CRect GetIdealRect()
	{
		return m_rcIdealRect;
	}
protected:
	void DrawControl(HDC hdc)
	{
		String strTextColorID, strFontID;
		switch (m_iCurState)
		{
		case DouControlState::Hover:
			strTextColorID = GetTextHoverColorID();
			strFontID = GetTextHoverFontID();
			break;
		case DouControlState::Press:
			strTextColorID = GetTextPressColorID();
			strFontID = GetTextPressFontID();
			break;
		case DouControlState::Disable:
			strTextColorID = GetTextDisableColorID();
			strFontID = GetTextDisableFontID();
			break;
		default:
			strTextColorID = GetTextNormalColorID();
			strFontID = GetTextNormalFontID();
			break;
		}
		m_rcIdealRect = GetControlPaintRect();
		CDouRender::DouDrawText(hdc, GetText(), m_rcIdealRect, gColorManager.GetColor(strTextColorID), strFontID, GetTextPaintStyle(), IsTextMultiLine(), GetTextRowSpan());
	}
private:
	CRect m_rcIdealRect;
};