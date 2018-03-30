#pragma once
class CDouImageInfoBase
{
public:
	CDouImageInfoBase()
	{
		m_uImagePaintStyle = DOU_CENTER | DOU_VCENTER;
		m_bImageStretch = FALSE;
	}
	void SetImagePaintStyle(UINT uStyle)
	{
		m_uImagePaintStyle = uStyle;
	}
	void SetImageStretch(BOOL bStretch = TRUE)
	{
		m_bImageStretch = bStretch;
	}
	UINT GetImagePaintStyle()
	{
		return m_uImagePaintStyle;
	}
	BOOL IsImageStretch()
	{
		return m_bImageStretch;
	}
private:
	UINT  m_uImagePaintStyle; //�ؼ�������ʽ
	BOOL m_bImageStretch;
};
//��̬ͼƬ����
class CDouImageSingleStateAttr
{
public:
	CDouImageSingleStateAttr()
	{
	}
	void SetImageResID(String strResID)
	{
		m_strImageResID = strResID;
	}
	String GetImageResID()
	{
		return m_strImageResID;
	}
private:
	String m_strImageResID;
};
//��̬ͼƬ����
class CDouImageTwoStateAttr
{
public:
	CDouImageTwoStateAttr()
	{
	}
	void SetImageNormalResID(String strResID)
	{
		m_strNormalResID = strResID;
	}
	void SetImageHoverResID(String strResID)
	{
		m_strHoverResID = strResID;
	}
	String GetImageNormalResID()
	{
		return m_strNormalResID;
	}
	String GetImageHoverResID()
	{
		return m_strHoverResID;
	}
private:
	String m_strNormalResID;
	String m_strHoverResID;
};

//��̬��ťͼƬ����
class CDouButtonFourStateAttr
{
public:
	CDouButtonFourStateAttr()
	{
	}
	//��׼��ԴID���Զ��ں������״̬��״̬Сд��
	void SetButtonStandardResID(String strResID)
	{
		SetButtonNormalResID(strResID + _T(".normal"));
		SetButtonHoverResID(strResID + _T(".hover"));
		SetButtonPressResID(strResID + _T(".press"));
		SetButtonDisableResID(strResID + _T(".disable"));
	}

	void SetButtonNormalResID(String strResID)
	{
		m_strBkgResID[0] = strResID;
	}
	void SetButtonHoverResID(String strResID)
	{
		m_strBkgResID[1] = strResID;
	}
	void SetButtonPressResID(String strResID)
	{
		m_strBkgResID[2] = strResID;
	}
	void SetButtonDisableResID(String strResID)
	{
		m_strBkgResID[3] = strResID;
	}

	String GetButtonNormalResID()
	{
		return m_strBkgResID[0];
	}
	String GetButtonHoverResID()
	{
		return m_strBkgResID[1];
	}
	String GetButtonPressResID()
	{
		return m_strBkgResID[2];
	}
	String GetButtonDisableResID()
	{
		return m_strBkgResID[3];
	}

	void SetButtonPaintStyle(UINT uStyle)
	{
		m_BkgImageInfo.SetImagePaintStyle(uStyle);
	}
	void SetButtonStretch(BOOL bStretch = TRUE)
	{
		m_BkgImageInfo.SetImageStretch(bStretch);
	}
	UINT GetButtonPaintStyle()
	{
		return m_BkgImageInfo.GetImagePaintStyle();
	}
	BOOL IsButtonStretch()
	{
		return m_BkgImageInfo.IsImageStretch();
	}
private:
	String m_strBkgResID[4];
	CDouImageInfoBase m_BkgImageInfo;
};