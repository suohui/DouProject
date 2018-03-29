#pragma once

#define WM_DOUCONTROLCLICK	WM_USER + 1024
#define WM_DOUCONTROLMOUSEMOVE	WM_USER + 1025
#define WM_DOUCONTROLMOUSELEAVE	WM_USER + 1026
typedef std::pair<String, int> StringIntPair;
struct CmpByValue
{
	bool operator()(const StringIntPair& left, const StringIntPair& right)
	{
		return left.second < right.second;
	}
};

template <class T>
class CDouControlImpl : public CMessageMap
{
public:
	CDouControlImpl()
	{
		m_bTracking = FALSE;
		m_DouControlPress = NULL;
		m_ControlObjectMap.clear();
	}
	~CDouControlImpl()
	{
		std::map<String, CDouControlBase*>::iterator iterControlBase;
		for (iterControlBase = m_ControlObjectMap.begin(); iterControlBase != m_ControlObjectMap.end(); iterControlBase++)
		{
			if (NULL != iterControlBase->second)
			{
				delete iterControlBase->second;
				iterControlBase->second = NULL;
			}
		}
		m_ControlObjectMap.clear();
	}
	CDouTextObject* GetTextObject(String strObjID)	//仿FileOpen，如果没有，则创建。如果有，则直接返回
	{
		if (m_ControlObjectMap[strObjID] == NULL)
		{
			T* pThis = static_cast<T*>(this);
			m_ControlObjectMap[strObjID] = new CDouTextObject(pThis->m_hWnd);
		}
		return dynamic_cast<CDouTextObject*>(m_ControlObjectMap[strObjID]);
	}
	CDouImageObject* GetImageObject(String strObjID)
	{
		if (m_ControlObjectMap[strObjID] == NULL)
		{
			T* pThis = static_cast<T*>(this);
			m_ControlObjectMap[strObjID] = new CDouImageObject(pThis->m_hWnd);
		}
		return dynamic_cast<CDouImageObject*>(m_ControlObjectMap[strObjID]);
	}
	CDouButtonObject* GetButtonObject(String strObjID)
	{
		if (m_ControlObjectMap[strObjID] == NULL)
		{
			T* pThis = static_cast<T*>(this);
			m_ControlObjectMap[strObjID] = new CDouButtonObject(pThis->m_hWnd);
		}
		return dynamic_cast<CDouButtonObject*>(m_ControlObjectMap[strObjID]);
	}

	void DrawAllObject(HDC hDC)
	{
		std::map<String, CDouControlBase*>::iterator iterControlBase;
		for (iterControlBase = m_ControlObjectMap.begin(); iterControlBase != m_ControlObjectMap.end(); iterControlBase++)
		{
			CDouControlBase*  pControlBase = iterControlBase->second;
			if ((NULL != pControlBase) && pControlBase->GetOwnerControl() == NULL)
			{
				pControlBase->Draw(hDC);
			}
		}
	}

	BEGIN_MSG_MAP(CDouControlImpl)
		MESSAGE_HANDLER(WM_NCMOUSEMOVE, OnNcMouseMove)
		MESSAGE_HANDLER(WM_NCMOUSELEAVE, OnNcMouseLeave)
		MESSAGE_HANDLER(WM_NCLBUTTONDOWN, OnNcLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	END_MSG_MAP()
protected:
	CDouControlBase * SetDouControlState(CPoint pt, DouControlState ctlState = DouControlState::Normal)
	{
		CDouControlBase* pControlBaseRet = NULL;
		T* pThis = static_cast<T*>(this);
		//是否落在控件上
		std::map<String, CDouControlBase*>::iterator iterObjMap;
		for (iterObjMap = m_ControlObjectMap.begin(); iterObjMap != m_ControlObjectMap.end(); iterObjMap++)
		{
			CDouControlBase*  pCtrl = iterObjMap->second;	///////////////添加可见与可用的判断
			if (pCtrl->IsControlVisible() && pCtrl->IsOwnerControlVisible())
			{
				CRect rcCtrl = pCtrl->GetControlPaintRect();
				switch (pCtrl->GetControlType())
				{
				case DouControlType::DouImage:
				{
					CDouImageObject* pImageObj = dynamic_cast<CDouImageObject*>(pCtrl);
					if (pImageObj->IsMouseEvent())
					{
						if (rcCtrl.PtInRect(pt))
						{
							if (pImageObj->m_iCurState != DouControlState::Hover)
							{
								pImageObj->m_iCurState = DouControlState::Hover;
								::SendMessage(pThis->m_hWnd, WM_DOUCONTROLMOUSEMOVE, 0, (LPARAM)pImageObj);
							}
						}
						else
						{
							if (pImageObj->m_iCurState != DouControlState::Normal)
							{
								pImageObj->m_iCurState = DouControlState::Normal;
								::SendMessage(pThis->m_hWnd, WM_DOUCONTROLMOUSELEAVE, 0, (LPARAM)pImageObj);
							}
						}
					}
				}
				break;
				case DouControlType::DouButton:
				case DouControlType::DouCheckBox:
				case DouControlType::DouHyperLink:
				case DouControlType::DouRadioButton:
					if (rcCtrl.PtInRect(pt))
					{
						if (ctlState == DouControlState::Press)
						{
							pCtrl->m_iCurState = DouControlState::Press;
							pCtrl->DouInvalidateRect();
							pControlBaseRet = pCtrl;
						}
						else if (pCtrl->m_iCurState != DouControlState::Hover)
						{
							pCtrl->m_iCurState = DouControlState::Hover;
							pCtrl->DouInvalidateRect();
						}
					}
					else
					{
						if (pCtrl->m_iCurState != DouControlState::Normal)
						{
							pCtrl->m_iCurState = DouControlState::Normal;
							pCtrl->DouInvalidateRect();
						}
					}
					break;
				}
			}
		}
		return pControlBaseRet;
	}

	LRESULT OnNcMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		if (NULL != m_DouControlPress)	//按下的时候，不响应MouseMove
			return 0;
		T* pThis = static_cast<T*>(this);
		if (!m_bTracking)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE | TME_HOVER | TME_NONCLIENT;
			tme.dwHoverTime = 1;
			tme.hwndTrack = pThis->m_hWnd;
			m_bTracking = ::_TrackMouseEvent(&tme);
		}
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		::ScreenToClient(pThis->m_hWnd, &pt);
		SetDouControlState(pt, DouControlState::Hover);
		return 0;
	}
	LRESULT OnNcMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if (NULL != m_DouControlPress)	//按下的时候，不响应MouseMove
			return 0;
		m_bTracking = FALSE;
		T* pThis = static_cast<T*>(this);
		CPoint pt;
		GetCursorPos(&pt);
		::ScreenToClient(pThis->m_hWnd, &pt);
		SetDouControlState(pt, DouControlState::Normal);
		return 0;
	}
	
	LRESULT OnNcLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pThis = static_cast<T*>(this);
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		::ScreenToClient(pThis->m_hWnd, &pt);
		m_DouControlPress = SetDouControlState(pt, DouControlState::Press);
		if (m_DouControlPress != NULL)
		{
			bHandled = TRUE;	//将消息转往客户区
			T* pThis = static_cast<T*>(this);
			::SetCapture(pThis->m_hWnd);
		}
		return 0;
	}

	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		CDouControlBase* pCtrlPressTmp = m_DouControlPress;
		m_DouControlPress = NULL;
		::ReleaseCapture();
		T* pThis = static_cast<T*>(this);
		CPoint ptCursor(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		if (NULL != pCtrlPressTmp && pCtrlPressTmp->GetControlPaintRect().PtInRect(ptCursor))
		{
			::SendMessage(pThis->m_hWnd, WM_DOUCONTROLCLICK, 0, (LPARAM)pCtrlPressTmp);//鼠标点击消息
		}
		::GetCursorPos(&ptCursor);
		::ScreenToClient(pThis->m_hWnd, &ptCursor);
		SetDouControlState(ptCursor, DouControlState::Normal);
		return 0;
	}
private:
	BOOL m_bTracking;
	CDouControlBase* m_DouControlPress;	//鼠标按下去的控件
	std::map<String, CDouControlBase*> m_ControlObjectMap;
};