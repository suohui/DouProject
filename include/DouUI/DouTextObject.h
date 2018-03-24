#pragma once

//������Ϣ������
class CDouTextObject : public CDouControlBase
{
public:
	CDouTextObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		//����Ĭ������ID
		m_strFontID = CDouUtils::GetTextNormalFontID();
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
		::InvalidateRect(m_hWnd, &GetControlPaintRect(), TRUE);
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

	String GetTextFontID()
	{
		return m_strFontID;
	}

	String GetTextColorID()
	{
		return m_strTextColorID;
	}

	UINT GetTextFormatStyle()
	{
		return m_uFormatStyle;
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
			CDouRender::DrawHtmlText(hdc, m_strText, GetControlPaintRect(), gColorManager.GetColor(m_strTextColorID), m_strFontID, m_uFormatStyle, m_bMultiLine, m_iRowHeight);
		}
		else
		{
			CDouRender::DrawText(hdc, m_strText, GetControlPaintRect(), gColorManager.GetColor(m_strTextColorID), m_strFontID, m_uFormatStyle, m_bMultiLine, m_iRowHeight);
		}
	}
private:
	String m_strFontID; //����ID
	String m_strTextColorID; //������ɫID
	UINT  m_uFormatStyle; //���ֻ�����ʽ
	BOOL m_bMultiLine;	//���С������������Ĭ�ϵĻ�����ʽΪDT_CENTER | DT_VCENTER | DT_SINGLELINE
	BOOL m_bHtmlTagEnable;//֧��THML��ǩ����
	int m_iRowHeight;
	String m_strText;	//��������
};