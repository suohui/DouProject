#pragma once

//文字信息基础类
class CDouTextObject : public CDouControlBase
{
public:
	CDouTextObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		//设置默认字体ID
		m_strFontID = CDouUtils::GetTextNormalFontID();
		//设置默认字体颜色
		m_dwTextColor = CDouUtils::GetTextNormalColor();
		//设置默认字体绘制样式
		m_uFormatStyle = CDouUtils::GetTextFormatStyle();
		m_bMultiLine = FALSE;
		m_bVisible = TRUE;
		m_bHtmlTagEnable = FALSE;
		m_iRowHeight = CDouUtils::GetTextRowHeight();
	}

	void SetText(String strText)
	{
		m_strText = strText;
		::InvalidateRect(m_hWnd, &m_rcControl, TRUE);
	}
	void EnableHtmlTag(BOOL bTagEnable)
	{
		m_bHtmlTagEnable = bTagEnable;
	}
	void SetTextRowHeight(int iHeight)
	{
		m_iRowHeight = iHeight;
	}

	void SetTextColor(DWORD dwTextColor)
	{
		m_dwTextColor = dwTextColor;
	}

	void SetTextFontID(String strFontID)
	{
		m_strFontID = strFontID;
	}

	void SetTextFormatStyle(UINT uStyle)
	{
		m_uFormatStyle = uStyle;
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

	DWORD GetTextColor()
	{
		return m_dwTextColor;
	}

	String GetTextFontID()
	{
		return m_strFontID;
	}

	UINT GetTextFormatStyle()
	{
		return m_uFormatStyle;
	}

	BOOL IsTextMultiLine()
	{
		return m_bMultiLine;
	}

	void Draw(HDC hdc)
	{
		if (m_bHtmlTagEnable)
		{
			CDouRender::DrawHtmlText(hdc, m_strText, m_rcControl, m_dwTextColor, m_strFontID, m_uFormatStyle, m_bMultiLine, m_iRowHeight);
		}
		else
		{
			CDouRender::DrawText(hdc, m_strText, m_rcControl, m_dwTextColor, m_strFontID, m_uFormatStyle, m_bMultiLine, m_iRowHeight);
		}
	}
private:
	String m_strFontID; //字体ID
	DWORD m_dwTextColor;//字体颜色
	UINT  m_uFormatStyle; //文字绘制样式
	BOOL m_bMultiLine;	//多行。简单起见，单行默认的绘制样式为DT_CENTER | DT_VCENTER | DT_SINGLELINE
	BOOL m_bHtmlTagEnable;//支持THML标签绘制
	int m_iRowHeight;
	String m_strText;	//文字内容
};