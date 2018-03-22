#pragma once

class CDouButtonObject : public CDouControlBase
{
public:
	CDouButtonObject(HWND hWndOwner) : CDouControlBase(hWndOwner)
	{
		m_ControlType = DouControlType::DouButton;
	}
	~CDouButtonObject()
	{
	}

	void SetNormalResID(String strResID)
	{
		m_strBkgResID[0] = strResID;
	}
	void SetHoverResID(String strResID)
	{
		m_strBkgResID[1] = strResID;
	}
	void SetPressResID(String strResID)
	{
		m_strBkgResID[2] = strResID;
	}
	void SetDisableResID(String strResID)
	{
		m_strBkgResID[3] = strResID;
	}
	void Draw(HDC hdc)
	{
		CDouRender::DrawImage(hdc, m_rcControl, gBmpManager.GetBmpSrcInfo(m_strBkgResID[m_iCurState]), true);
	}
private:
	String m_strBkgResID[4];
};