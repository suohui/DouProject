#pragma once
class CDouTextLinkObject : public CDouControlBase
{
public:
	CDouTextLinkObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		//设置默认字体ID
		m_strFontID[0] = CDouUtils::GetTextNormalFontID();
		m_strFontID[1] = CDouUtils::GetTextHoverFontID();
		m_strFontID[2] = CDouUtils::GetTextPressFontID();
		m_strFontID[3] = CDouUtils::GetTextDisabledFontID();
		//设置默认字体颜色
		m_strTextColorID[0] = CDouUtils::GetTextNormalColorID();
		m_strTextColorID[1] = CDouUtils::GetTextHoverColorID();
		m_strTextColorID[2] = CDouUtils::GetTextPressColorID();
		m_strTextColorID[3] = CDouUtils::GetTextDisabledColorID();
		//设置默认字体绘制样式
		m_uPaintStyle = CDouUtils::GetTextFormatStyle();
		m_bMultiLine = FALSE;
		m_bVisible = TRUE;
		m_iRowHeight = CDouUtils::GetTextRowHeight();
		m_ControlType = DouControlType::DouTextLink;
	}

	void SetText(String strText)
	{
		m_strText = strText;
	}

	void SetTextRowHeight(int iHeight)
	{
		m_iRowHeight = iHeight;
	}

	void SetTextNormalColorID(String strColorID)
	{
		m_strTextColorID[0] = strColorID;
	}
	void SetTextHoverColorID(String strColorID)
	{
		m_strTextColorID[1] = strColorID;
	}
	void SetTextPressColorID(String strColorID)
	{
		m_strTextColorID[2] = strColorID;
	}
	void SetTextDisableColorID(String strColorID)
	{
		m_strTextColorID[3] = strColorID;
	}

	void SetTextNormalFontID(String strFontID)
	{
		m_strFontID[0] = strFontID;
	}
	void SetTextHoverFontID(String strFontID)
	{
		m_strFontID[1] = strFontID;
	}
	void SetTextPressFontID(String strFontID)
	{
		m_strFontID[2] = strFontID;
	}
	void SetTextDisableFontID(String strFontID)
	{
		m_strFontID[3] = strFontID;
	}

	void SetPaintStyle(UINT uStyle)
	{
		m_uPaintStyle = uStyle;
	}

	void SetTextMultiLine(BOOL bMultiLine)
	{
		m_bMultiLine = bMultiLine;
	}

	String GetText()
	{
		return m_strText;
	}

	int GetTextRowHeight()
	{
		return m_iRowHeight;
	}

	String GetTextNormalFontID()
	{
		return m_strFontID[0];
	}
	String GetTextHoverFontID()
	{
		return m_strFontID[1];
	}
	String GetTextPressFontID()
	{
		return m_strFontID[2];
	}
	String GetTextDisableFontID()
	{
		return m_strFontID[3];
	}

	String GetTextNormalColorID()
	{
		return m_strTextColorID[0];
	}
	String GetTextHoverColorID()
	{
		return m_strTextColorID[1];
	}
	String GetTextPressColorID()
	{
		return m_strTextColorID[2];
	}
	String GetTextDisableColorID()
	{
		return m_strTextColorID[3];
	}

	UINT GetPaintStyle()
	{
		return m_uPaintStyle;
	}

	BOOL IsTextMultiLine()
	{
		return m_bMultiLine;
	}
protected:
	void DrawControl(HDC hdc)
	{
		CDouRender::DrawText(hdc, m_strText, GetControlPaintRect(), gColorManager.GetColor(m_strTextColorID[m_iCurState]), m_strFontID[m_iCurState], m_uPaintStyle, m_bMultiLine, m_iRowHeight);
	}
private:
	String m_strFontID[4]; //字体ID
	String m_strTextColorID[4]; //字体颜色ID
	UINT  m_uPaintStyle; //控件绘制样式
	BOOL m_bMultiLine;	//多行。简单起见，单行默认的绘制样式为DOU_CENTER | DOU_VCENTER
	int m_iRowHeight;
	String m_strText;	//文字内容
};