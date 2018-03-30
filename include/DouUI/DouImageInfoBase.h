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