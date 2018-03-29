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
		m_TextObjectMap.clear();
		m_ImageObjectMap.clear();
		m_ClickedObjectMap.clear();
		m_DouControlPress = NULL;
		m_ControlObjectMap.clear();
	}
	~CDouControlImpl()
	{
		std::map<String, CDouTextObject*>::iterator iterText;
		for (iterText = m_TextObjectMap.begin(); iterText != m_TextObjectMap.end(); iterText++)
		{
			if (NULL != iterText->second)
			{
				delete iterText->second;
				iterText->second = NULL;
			}
		}
		m_TextObjectMap.clear();

		std::map<String, CDouImageObject*>::iterator iterImage;
		for (iterImage = m_ImageObjectMap.begin(); iterImage != m_ImageObjectMap.end(); iterImage++)
		{
			if (NULL != iterImage->second)
			{
				delete iterImage->second;
				iterImage->second = NULL;
			}
		}
		m_ImageObjectMap.clear();

		std::map<String, CDouControlBase*>::iterator iterControlBase;
		for (iterControlBase = m_ClickedObjectMap.begin(); iterControlBase != m_ClickedObjectMap.end(); iterControlBase++)
		{
			if (NULL != iterControlBase->second)
			{
				delete iterControlBase->second;
				iterControlBase->second = NULL;
			}
		}
		m_ClickedObjectMap.clear();
	}
	CDouTextObject* GetTextObject(String strObjID)	//仿FileOpen，如果没有，则创建。如果有，则直接返回
	{
		if (m_TextObjectMap[strObjID] == NULL)
		{
			T* pThis = static_cast<T*>(this);
			m_TextObjectMap[strObjID] = new CDouTextObject(pThis->m_hWnd);
			m_ControlObjectMap[strObjID] = m_TextObjectMap[strObjID];
		}
		return m_TextObjectMap[strObjID];
	}
	CDouImageObject* GetImageObject(String strObjID)
	{
		if (m_ImageObjectMap[strObjID] == NULL)
		{
			T* pThis = static_cast<T*>(this);
			m_ImageObjectMap[strObjID] = new CDouImageObject(pThis->m_hWnd);
			m_ControlObjectMap[strObjID] = m_ImageObjectMap[strObjID];
		}
		return m_ImageObjectMap[strObjID];
	}
	CDouButtonObject* GetButtonObject(String strObjID)
	{
		if (m_ClickedObjectMap[strObjID] == NULL)
		{
			T* pThis = static_cast<T*>(this);
			m_ClickedObjectMap[strObjID] = new CDouButtonObject(pThis->m_hWnd);
			m_ControlObjectMap[strObjID] = m_ClickedObjectMap[strObjID];
		}
		return dynamic_cast<CDouButtonObject*>(m_ClickedObjectMap[strObjID]);
	}

	void DrawAllObject(HDC hDC)
	{
		//画图片
		std::map<String, CDouImageObject*>::iterator iterImage;
		std::vector<StringIntPair> vecZorder;
		for (iterImage = m_ImageObjectMap.begin(); iterImage != m_ImageObjectMap.end(); iterImage++)
		{
			CDouImageObject* pImageObject = iterImage->second;
			if ((NULL != pImageObject) && pImageObject->GetOwnerControl() == NULL)
			{
				pImageObject->Draw(hDC);
			}
		}
		//画Button
		std::map<String, CDouControlBase*>::iterator iterControlBase;
		for (iterControlBase = m_ClickedObjectMap.begin(); iterControlBase != m_ClickedObjectMap.end(); iterControlBase++)
		{
			CDouControlBase*  pControlBase = iterControlBase->second;
			if ((NULL != pControlBase) && pControlBase->GetOwnerControl() == NULL)
			{
				pControlBase->Draw(hDC);
			}
		}
		//画文字
		std::map<String, CDouTextObject*>::iterator iterText;
		for (iterText = m_TextObjectMap.begin(); iterText != m_TextObjectMap.end(); iterText++)
		{
			CDouTextObject* pTextInfo = iterText->second;
			if ((NULL != pTextInfo) && pTextInfo->GetOwnerControl() == NULL)
			{
				pTextInfo->Draw(hDC);
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
	CDouControlBase * SetDouControlState(CPoint pt, DouControlState ctlState)
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
								::SendMessage(pThis->m_hWnd, WM_DOUCONTROLMOUSEMOVE, 0, (LPARAM)pImageObj);
								pImageObj->m_iCurState = DouControlState::Hover;
							}
						}
						else
						{
							if (pImageObj->m_iCurState != DouControlState::Normal)
							{
								::SendMessage(pThis->m_hWnd, WM_DOUCONTROLMOUSELEAVE, 0, (LPARAM)pImageObj);
								pImageObj->m_iCurState = DouControlState::Normal;
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
						pCtrl->m_iLastState = pCtrl->m_iCurState;
						pCtrl->m_iCurState = ctlState;
						if (pCtrl->m_iLastState != pCtrl->m_iCurState)
							pCtrl->DouInvalidateRect();
						pControlBaseRet = pCtrl;
					}
					else
					{
						if (pCtrl->m_iCurState != DouControlState::Normal)
						{
							pCtrl->DouInvalidateRect();
						}
						pCtrl->m_iCurState = DouControlState::Normal;
						pCtrl->m_iLastState = DouControlState::Normal;
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
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		::ScreenToClient(pThis->m_hWnd, &pt);
		SetDouControlState(pt, DouControlState::Hover);
		if (!m_bTracking)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE | TME_HOVER | TME_NONCLIENT;
			tme.dwHoverTime = 10;
			tme.hwndTrack = pThis->m_hWnd;
			m_bTracking = ::_TrackMouseEvent(&tme);
		}
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
		ReleaseCapture();
		T* pThis = static_cast<T*>(this);
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		if (NULL != m_DouControlPress && m_DouControlPress->GetControlPaintRect().PtInRect(pt))
		{
			//鼠标点击消息
			::SendMessage(pThis->m_hWnd, WM_DOUCONTROLCLICK, 0, (LPARAM)m_DouControlPress);
		}
		m_DouControlPress = NULL;
		SetDouControlState(pt, DouControlState::Normal);

		return 0;
	}
private:
	BOOL m_bTracking;
	std::map<String, CDouTextObject*> m_TextObjectMap;
	std::map<String, CDouImageObject*> m_ImageObjectMap;
	std::map<String, CDouControlBase*> m_ClickedObjectMap;
	CDouControlBase* m_DouControlPress;	//鼠标按下去的控件

	std::map<String, CDouControlBase*> m_ControlObjectMap;
};