#pragma once
//控件类型
enum DouControlType
{
	TypeError = -1,
	DouText,
	DouImage,
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
		m_ControlType = DouControlType::TypeError;
		m_iCurState = DouControlState::Normal;
		m_pOwnerCtrl = NULL;
		m_vecChildControl.clear();
	}
public:
	void SetControlRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcControl.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
	}
	void SetControlVisible(BOOL bVisible = TRUE)
	{
		m_bVisible = bVisible;
	}
	void SetControlID(String strControlID)
	{
		m_strControlID = strControlID;
	}

	void SetOwnerControl(CDouControlBase *pOwnerCtrl)
	{
		m_pOwnerCtrl = pOwnerCtrl;
		pOwnerCtrl->AddChildControl(this);
	}

	BOOL DouInvalidateRect(BOOL bErase = TRUE)
	{
		return ::InvalidateRect(m_hWnd, &GetControlPaintRect(), bErase);
	}

	void AddChildControl(CDouControlBase *pChildCtrl)
	{
		m_vecChildControl.push_back(pChildCtrl);
	}
	CDouControlBase *GetOwnerControl()
	{
		return m_pOwnerCtrl;
	}

	BOOL IsOwnerControlVisible()
	{
		BOOL bRet = TRUE;
		CDouControlBase* pOwnerCtrlTmp = m_pOwnerCtrl;
		while ((pOwnerCtrlTmp != NULL) && bRet)
		{
			bRet = bRet && pOwnerCtrlTmp->IsControlVisible();
			pOwnerCtrlTmp = pOwnerCtrlTmp->GetOwnerControl();
		}
		return bRet;
	}

	CRect GetControlPaintRect() //控件的实际位置
	{
		CRect rcTmp = (m_pOwnerCtrl == NULL) ? CRect(0, 0, 0, 0) : m_pOwnerCtrl->GetControlPaintRect();
		return CRect(CPoint(m_rcControl.left + rcTmp.left, m_rcControl.top + rcTmp.top), CSize(m_rcControl.Width(), m_rcControl.Height()));
	}

	CRect GetControlRelativeRect() //控件的相对位置
	{
		return m_rcControl;
	}
	BOOL IsControlVisible()
	{
		return m_bVisible;
	}

	String GetControlID()
	{
		return m_strControlID;
	}
	DouControlType GetControlType()
	{
		return m_ControlType;
	}

	void Draw(HDC hdc)
	{
		if (IsOwnerControlVisible() && m_bVisible && !GetControlPaintRect().IsRectEmpty())
		{
			DrawControl(hdc); //画自己
			//画children
			size_t iChildrenCount = m_vecChildControl.size();
			for (size_t iIndex = 0; iIndex < iChildrenCount; iIndex++)
			{
				m_vecChildControl[iIndex]->Draw(hdc);
			}
		}
	}
	DouControlState m_iCurState;
protected:
	virtual void DrawControl(HDC hdc)
	{
		//必须继承
	}
	HWND m_hWnd;
	BOOL m_bVisible;
	String m_strControlID;
	DouControlType m_ControlType;
	CDouControlBase *m_pOwnerCtrl;	//父控件，若父控件不显示，子控件一定不显示
private:
	CRect m_rcControl; //控件的相对位置
	std::vector<CDouControlBase *> m_vecChildControl;
};