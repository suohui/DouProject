#pragma once
//������Ϣ������
class CDouTextInfoBase
{
public:
	CDouTextInfoBase()
	{
		m_uTextPaintStyle = CDouUtils::GetTextFormatStyle();
	}
	void SetText(String strText)
	{
		m_strText = strText;
	}
	void SetTextPaintStyle(UINT uStyle)
	{
		m_uTextPaintStyle = uStyle;
	}
	String GetText()
	{
		return m_strText;
	}
	UINT GetTextPaintStyle()
	{
		return m_uTextPaintStyle;
	}
private:
	UINT  m_uTextPaintStyle; //�ؼ�������ʽ
	String m_strText;	//��������
};
//�����ı�����
class CDouTextMultiLineAttr
{
public:
	CDouTextMultiLineAttr()
	{
		m_bMultiLine = FALSE;
		m_RowSpan = CDouUtils::GetTextRowSpan();
	}
	void SetTextMultiLine(BOOL bMultiLine)
	{
		m_bMultiLine = bMultiLine;
	}
	void SetTextRowSpan(int iRowSpan)
	{
		m_RowSpan = iRowSpan;
	}
	BOOL IsTextMultiLine()
	{
		return m_bMultiLine;
	}
	int GetTextRowSpan()
	{
		return m_RowSpan;
	}
private:
	BOOL m_bMultiLine;	//���С������������Ĭ�ϵĻ�����ʽΪDOU_CENTER | DOU_VCENTER
	int m_RowSpan;	//�о�
};
//��̬�ı�����
class CDouTextSingleStateAttr
{
public:
	CDouTextSingleStateAttr()
	{
		m_strFontID = CDouUtils::GetTextNormalFontID();
		m_strTextColorID = CDouUtils::GetTextNormalColorID();
	}
	void SetTextColorID(String strColorID)
	{
		m_strTextColorID = strColorID;
	}

	void SetTextFontID(String strFontID)
	{
		m_strFontID = strFontID;
	}
	String GetTextFontID()
	{
		return m_strFontID;
	}
	String GetTextColorID()
	{
		return m_strTextColorID;
	}
private:
	String m_strFontID; //����ID
	String m_strTextColorID; //������ɫID
};
//��̬�ı�����
class CDouTextFourStateAttr
{
public:
	CDouTextFourStateAttr()
	{
		//����Ĭ������ID
		m_strFontID[0] = CDouUtils::GetTextNormalFontID();
		m_strFontID[1] = CDouUtils::GetTextHoverFontID();
		m_strFontID[2] = CDouUtils::GetTextPressFontID();
		m_strFontID[3] = CDouUtils::GetTextDisabledFontID();
		//����Ĭ��������ɫ
		m_strTextColorID[0] = CDouUtils::GetTextNormalColorID();
		m_strTextColorID[1] = CDouUtils::GetTextHoverColorID();
		m_strTextColorID[2] = CDouUtils::GetTextPressColorID();
		m_strTextColorID[3] = CDouUtils::GetTextDisabledColorID();
	}
	//��׼��ԴID���Զ��ں������״̬��״̬Сд��
	void SetTextStandardColorID(String strResID)
	{
		SetTextNormalColorID(strResID + _T(".normal"));
		SetTextHoverColorID(strResID + _T(".hover"));
		SetTextPressColorID(strResID + _T(".press"));
		SetTextDisableColorID(strResID + _T(".disable"));
	}
	void SetTextColorID(String strResID)
	{
		SetTextNormalColorID(strResID);
		SetTextHoverColorID(strResID);
		SetTextPressColorID(strResID);
		SetTextDisableColorID(strResID);
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
	//��׼��ԴID���Զ��ں������״̬��״̬Сд��
	void SetTextStandardFontID(String strResID)
	{
		SetTextNormalFontID(strResID + _T(".normal"));
		SetTextHoverFontID(strResID + _T(".hover"));
		SetTextPressFontID(strResID + _T(".press"));
		SetTextDisableFontID(strResID + _T(".disable"));
	}
	void SetTextFontID(String strResID)
	{
		SetTextNormalFontID(strResID);
		SetTextHoverFontID(strResID);
		SetTextPressFontID(strResID);
		SetTextDisableFontID(strResID);
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
private:
	String m_strFontID[4]; //����ID
	String m_strTextColorID[4]; //������ɫID
};