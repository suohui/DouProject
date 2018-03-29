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
		std::map<String, CDouControlBase*>::iterator iterCtrlMap;
		for (iterCtrlMap = m_ControlObjectMap.begin(); iterCtrlMap != m_ControlObjectMap.end(); iterCtrlMap++)
		{
			if (NULL != iterCtrlMap->second)
			{
				delete iterCtrlMap->second;
				iterCtrlMap->second = NULL;
			}
		}
		m_ControlObjectMap.clear();
	}
	CDouTextObject* GetTextObject(String strObjID)	//仿FileOpen，如果没有，则创建。如果有，则直接返回
	{
		String strNewObjID = _T("DouText.") + strObjID;
		if (m_ControlObjectMap[strNewObjID] == NULL)
		{
			T* pThis = static_cast<T*>(this);
			m_ControlObjectMap[strNewObjID] = new CDouTextObject(pThis->m_hWnd);
		}
		return dynamic_cast<CDouTextObject*>(m_ControlObjectMap[strNewObjID]);
	}
	CDouImageObject* GetImageObject(String strObjID)
	{
		String strNewObjID = _T("DouImage.") + strObjID;
		if (m_ControlObjectMap[strNewObjID] == NULL)
		{
			T* pThis = static_cast<T*>(this);
			m_ControlObjectMap[strNewObjID] = new CDouImageObject(pThis->m_hWnd);
		}
		return dynamic_cast<CDouImageObject*>(m_ControlObjectMap[strNewObjID]);
	}
	CDouButtonObject* GetButtonObject(String strObjID)
	{
		String strNewObjID = _T("DouButton.") + strObjID;
		if (m_ControlObjectMap[strNewObjID] == NULL)
		{
			T* pThis = static_cast<T*>(this);
			m_ControlObjectMap[strNewObjID] = new CDouButtonObject(pThis->m_hWnd);
		}
		return dynamic_cast<CDouButtonObject*>(m_ControlObjectMap[strNewObjID]);
	}

	void DrawAllObject(HDC hDC)
	{
		//先将主窗体上的控件按ZOrder递增排序
		//std::map<String, CDouControlBase*>::iterator iterCtrlMap;
		//std::vector<StringIntPair> vecZorder;
		//for (iterCtrlMap = m_ControlObjectMap.begin(); iterCtrlMap != m_ControlObjectMap.end(); iterCtrlMap++)
		//{
		//	CDouControlBase* pCtrlObj = iterCtrlMap->second;
		//	if ((NULL != pCtrlObj) && (pCtrlObj->GetOwnerControl() == NULL))
		//	{
		//		vecZorder.push_back(make_pair(iterCtrlMap->first, pCtrlObj->GetZOrder()));
		//	}
		//}
		//sort(vecZorder.begin(), vecZorder.end(), CmpByValue());
		//size_t vecLen = vecZorder.size();
		//for (size_t iIndex = 0; iIndex < vecLen; iIndex++)
		//{
		//	CDouControlBase* pCtrlObj = m_ControlObjectMap[vecZorder[iIndex].first];
		//	if ((NULL != pCtrlObj) && pCtrlObj->GetOwnerControl() == NULL)
		//	{
		//		pCtrlObj->Draw(hDC);
		//	}
		//}
		
		std::map<String, CDouControlBase*>::iterator iterCtrlMap;
		for (iterCtrlMap = m_ControlObjectMap.begin(); iterCtrlMap != m_ControlObjectMap.end(); iterCtrlMap++)
		{
			CDouControlBase*  pCtrlObj = iterCtrlMap->second;
			if ((NULL != pCtrlObj) && pCtrlObj->GetOwnerControl() == NULL)
			{
				pCtrlObj->Draw(hDC);
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