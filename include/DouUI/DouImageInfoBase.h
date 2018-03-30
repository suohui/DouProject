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
	UINT  m_uImagePaintStyle; //控件绘制样式
	BOOL m_bImageStretch;
};
//单态图片属性
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
//两态图片属性
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