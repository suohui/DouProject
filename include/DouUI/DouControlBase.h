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
		::InvalidateRect(m_hWnd, &GetControlPaintRect(), TRUE);
	}
	void SetControlVisible(BOOL bVisible = TRUE)
	{
		m_bVisible = bVisible;
		::InvalidateRect(m_hWnd, &GetControlPaintRect(), TRUE);
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
		CRect rcTmp = m_pOwnerCtrl == NULL ? CRect(0, 0, 0, 0) : m_pOwnerCtrl->GetControlPaintRect();
		m_ptOwnerPaintPoint = CPoint(rcTmp.left, rcTmp.top);
	}

	BOOL IsOwnerControlVisible()
	{
		return (m_pOwnerCtrl == NULL) ? TRUE : m_pOwnerCtrl->IsControlVisible();
	}

	CRect GetControlPaintRect() //�ؼ���ʵ��λ��
	{
		return CRect(CPoint(m_rcControl.left, m_rcControl.top) + m_ptOwnerPaintPoint, CSize(m_rcControl.Width(), m_rcControl.Height()));
	}

	CRect GetControlRelativeRect() //�ؼ������λ��
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

	void Draw(HDC hdc)
	{
		if (IsOwnerControlVisible() && m_bVisible && !GetControlPaintRect().IsRectEmpty())
		{
			DrawControl(hdc);
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
	int m_iZOrder;
	String m_strControlID;
	DouControlType m_ControlType;
	CDouControlBase *m_pOwnerCtrl;	//���ؼ��������ؼ�����ʾ���ӿؼ�һ������ʾ
private:
	CRect m_rcControl; //�ؼ������λ��
	CPoint m_ptOwnerPaintPoint; //���ؼ��ľ���λ��
};