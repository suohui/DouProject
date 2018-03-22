#pragma once

//������Ϣ������
class CDouTextObject : public CDouControlBase
{
public:
	CDouTextObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		//����Ĭ������ID
		m_strFontID = CDouUtils::GetTextNormalFontID();
		//����Ĭ��������ɫ
		m_dwTextColor = CDouUtils::GetTextNormalColor();
		//����Ĭ�����������ʽ
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
	String m_strFontID; //����ID
	DWORD m_dwTextColor;//������ɫ
	UINT  m_uFormatStyle; //���ֻ�����ʽ
	BOOL m_bMultiLine;	//���С������������Ĭ�ϵĻ�����ʽΪDT_CENTER | DT_VCENTER | DT_SINGLELINE
	BOOL m_bHtmlTagEnable;//֧��THML��ǩ����
	int m_iRowHeight;
	String m_strText;	//��������
};