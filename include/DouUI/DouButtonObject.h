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
	//标准资源ID，自动在后面添加状态（状态小写）
	void SetStandardResID(String strResID)
	{
		SetNormalResID(strResID + _T(".normal"));
		SetHoverResID(strResID + _T(".hover"));
		SetPressResID(strResID + _T(".press"));
		SetDisableResID(strResID + _T(".disable"));
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
protected:
	void DrawControl(HDC hdc)
	{
		CDouRender::DrawImage(hdc, GetControlPaintRect(), gBmpManager.GetBmpSrcInfo(m_strBkgResID[m_iCurState]), true);
	}
private:
	String m_strBkgResID[4];
};