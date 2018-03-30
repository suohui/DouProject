#pragma once
class CDouTextLinkObject : public CDouControlBase, public CDouTextInfoBase, public CDouTextMultiLineAttr, public CDouTextFourStateAttr
{
public:
	CDouTextLinkObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		m_ControlType = DouControlType::DouTextLink;
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
		CDouRender::DrawText(hdc, GetText(), GetControlPaintRect(), gColorManager.GetColor(strTextColorID), strFontID, GetTextPaintStyle(), IsTextMultiLine(), GetTextRowHeight());
	}
};