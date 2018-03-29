#pragma once

//文字信息基础类
class CDouTextObject : public CDouControlBase
{
public:
	CDouTextObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		//设置默认字体ID
		m_strFontID = CDouUtils::GetTextNormalFontID();
		//设置默认字体绘制样式
		m_uPaintStyle = CDouUtils::GetTextFormatStyle();
		m_bMultiLine = FALSE;
		m_bVisible = TRUE;
		m_bHtmlTagEnable = FALSE;
		m_iRowHeight = CDouUtils::GetTextRowHeight();
		m_ControlType = DouControlType::DouText;
	}

	void SetText(String strText)
	{
		m_strText = strText;
	}
	void EnableHtmlTag(BOOL bTagEnable)
	{
		m_bHtmlTagEnable = bTagEnable;
	}
	void SetTextRowHeight(int iHeight)
	{
		m_iRowHeight = iHeight;
	}

	void SetTextColorID(String strColorID)
	{
		m_strTextColorID = strColorID;
	}

	void SetTextFontID(String strFontID)
	{
		m_strFontID = strFontID;
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

	BOOL IsHtmlTagEnable()
	{
		return m_bHtmlTagEnable;
	}

	int GetTextRowHeight()
	{
		return m_iRowHeight;
	}

	String GetTextFontID()
	{
		return m_strFontID;
	}

	String GetTextColorID()
	{
		return m_strTextColorID;
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
		if (m_bHtmlTagEnable)
		{
			CDouRender::DrawHtmlText(hdc, m_strText, GetControlPaintRect(), gColorManager.GetColor(m_strTextColorID), m_strFontID, m_uPaintStyle, m_bMultiLine, m_iRowHeight);
		}
		else
		{
			CDouRender::DrawText(hdc, m_strText, GetControlPaintRect(), gColorManager.GetColor(m_strTextColorID), m_strFontID, m_uPaintStyle, m_bMultiLine, m_iRowHeight);
		}
	}
private:
	String m_strFontID; //字体ID
	String m_strTextColorID; //字体颜色ID
	UINT  m_uPaintStyle; //控件绘制样式
	BOOL m_bMultiLine;	//多行。简单起见，单行默认的绘制样式为DOU_CENTER | DOU_VCENTER
	BOOL m_bHtmlTagEnable;//支持THML标签绘制
	int m_iRowHeight;
	String m_strText;	//文字内容
};