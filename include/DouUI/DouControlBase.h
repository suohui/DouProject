#pragma once
//�ؼ�����
enum DouControlType
{
	TypeError = -1,
	DouButton,
	DouHyperLink,
	DouRadioButton,
	DouCheckBox
};
//�ؼ�״̬
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
		m_iLastState = DouControlState::Normal;
		m_iCurState = DouControlState::Normal;
		m_pOwnerCtrl = NULL;
	}
public:
	void SetControlRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcControl.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
		::InvalidateRect(m_hWnd, &GetControlPaintRect(), TRUE);
	}
	void SetControlVisible(BOOL bVisible = TRUE)
	{
		m_bVisible = bVisible;
		::InvalidateRect(m_hWnd, &GetControlPaintRect(), TRUE);
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
		return (m_pOwnerCtrl == NULL) ? TRUE : m_pOwnerCtrl->IsControlVisible();
	}

	CRect GetControlPaintRect() //�ؼ���ʵ��λ��
	{
		CRect rcTmp = (m_pOwnerCtrl == NULL) ? CRect(0, 0, 0, 0) : m_pOwnerCtrl->GetControlPaintRect();
		return CRect(CPoint(m_rcControl.left + rcTmp.left, m_rcControl.top + rcTmp.top), CSize(m_rcControl.Width(), m_rcControl.Height()));
	}

	CRect GetControlRelativeRect() //�ؼ������λ��
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
			DrawControl(hdc); //���Լ�
			//��children
			size_t iChildrenCount = m_vecChildControl.size();
			for (size_t iIndex = 0; iIndex < iChildrenCount; iIndex++)
			{
				m_vecChildControl[iIndex]->Draw(hdc);
			}
		}
	}

	DouControlState m_iLastState;
	DouControlState m_iCurState;
protected:
	virtual void DrawControl(HDC hdc)
	{
		//����̳�
	}
	HWND m_hWnd;
	BOOL m_bVisible;
	String m_strControlID;
	DouControlType m_ControlType;
	CDouControlBase *m_pOwnerCtrl;	//���ؼ��������ؼ�����ʾ���ӿؼ�һ������ʾ
private:
	CRect m_rcControl; //�ؼ������λ��
	std::vector<CDouControlBase *> m_vecChildControl;
};