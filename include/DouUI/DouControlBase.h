#pragma once
//控件类型
enum DouControlType
{
	TypeError = -1,
	DouButton,
	DouHyperLink,
	DouRadioButton,
	DouCheckBox
};
//控件状态
enum DouControlState
{
	Normal = 0,
	Hover,
	Press,
	Disable
};

class CDouControlBase
{
public:
	CDouControlBase(HWND hWnd = NULL)
	{
		m_hWnd = hWnd;
		m_bVisible = TRUE;
		m_iZOrder = 0;
		m_ControlType = DouControlType::TypeError;
		m_iLastState = DouControlState::Normal;
		m_iCurState = DouControlState::Normal;
		m_pOwnerCtrl = NULL;
	}
public:
	void SetControlRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcControl.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
		::InvalidateRect(m_hWnd, &m_rcControl, TRUE);
	}
	void SetControlVisible(BOOL bVisible = TRUE)
	{
		m_bVisible = bVisible;
		::InvalidateRect(m_hWnd, &m_rcControl, TRUE);
	}
	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}
	void SetControlID(String strControlID)
	{
		m_strControlID = strControlID;
	}

	void SetOwnerControl(CDouControlBase *pOwnerCtrl)
	{
		m_pOwnerCtrl = pOwnerCtrl;
		m_ptControlOffset = m_pOwnerCtrl->GetControlRect().TopLeft;
	}

	BOOL IsOwnerControlVisible()
	{
		return (m_pOwnerCtrl == NULL) ? TRUE : m_pOwnerCtrl->IsControlVisible();
	}

	CRect GetControlRect()
	{
		return m_rcControl;
	}
	BOOL IsControlVisible()
	{
		return m_bVisible;
	}
	int GetZOrder()
	{
		return m_iZOrder;
	}
	String GetControlID()
	{
		return m_strControlID;
	}
	DouControlType GetControlType()
	{
		return m_ControlType;
	}

	virtual void Draw(HDC hdc)
	{
		//必须继承
	}

	void DouInvalidateRect(BOOL bErase = TRUE)
	{
		::InvalidateRect(m_hWnd, &m_rcControl, bErase);
	}

	DouControlState m_iLastState;
	DouControlState m_iCurState;
protected:
	HWND m_hWnd;
	BOOL m_bVisible;
	int m_iZOrder;
	CRect m_rcControl;
	String m_strControlID;
	DouControlType m_ControlType;
	CPoint m_ptControlOffset;
	CRect m_rcAbsolute;

	CDouControlBase *m_pOwnerCtrl;	//父控件，若父控件不显示，子控件一定不显示
};