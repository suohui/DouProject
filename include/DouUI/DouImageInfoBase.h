#pragma once
class CDouImageInfoBase
{
public:
	CDouImageInfoBase()
	{
		m_uImagePaintStyle = DOU_CENTER | DOU_VCENTER;
		m_bImageStretch = FALSE;
	}
	void SetImageResID(String strID)
	{
		m_strID = strID;
	}

	void SetImagePaintStyle(UINT uStyle)
	{
		m_uImagePaintStyle = uStyle;
	}

	void SetImageStretch(BOOL bStretch = TRUE)
	{
		m_bImageStretch = bStretch;
	}

	String GetImageResID()
	{
		return m_strID;
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
	String m_strID;
	BOOL m_bImageStretch;
};