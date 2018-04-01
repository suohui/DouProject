#pragma once

//��̬�����С�֧��html��ǩ
class CDouTextObject : public CDouControlBase, public CDouTextInfoBase, public CDouTextMultiLineAttr, public CDouTextSingleStateAttr
{
public:
	CDouTextObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		m_ControlType = DouControlType::DouText;
		m_bHtmlTagEnable = FALSE;
	}

	void EnableHtmlTag(BOOL bTagEnable)
	{
		m_bHtmlTagEnable = bTagEnable;
	}

	BOOL IsHtmlTagEnable()
	{
		return m_bHtmlTagEnable;
	}
protected:
	void DrawControl(HDC hdc)
	{
		if (m_bHtmlTagEnable)
		{
			CDouRender::DrawHtmlText(hdc, GetText(), GetControlPaintRect(), gColorManager.GetColor(GetTextColorID()), GetTextFontID(), GetTextPaintStyle(), IsTextMultiLine(), GetTextRowHeight());
		}
		else
		{
			CDouRender::DouDrawText(hdc, GetText(), GetControlPaintRect(), gColorManager.GetColor(GetTextColorID()), GetTextFontID(), GetTextPaintStyle(), IsTextMultiLine(), GetTextRowHeight());
		}
	}
private:
	BOOL m_bHtmlTagEnable;//֧��THML��ǩ����
};