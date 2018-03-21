#pragma once

typedef pair<String, int> StringIntPair;
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
		m_ImageObjectMap.clear();
	}

	CDouImageObject* GetImageObject(String strObjID)
	{
		if (m_ImageObjectMap[strObjID] == NULL)
		{
			T* pThis = static_cast<T*>(this);
			m_ImageObjectMap[strObjID] = new CDouImageObject(pThis->m_hWnd);
		}
		return m_ImageObjectMap[strObjID];
	}

	void DrawAllObject(HDC hDC)
	{
		//��ͼƬ,�Ƚ�ZOrder��������
		map<String, CDouImageObject*>::iterator iterImage;
		vector<StringIntPair> vecZorder;
		for (iterImage = m_ImageObjectMap.begin(); iterImage != m_ImageObjectMap.end(); iterImage++)
		{
			CDouImageObject* pImageObject = iterImage->second;
			if ((NULL != pImageObject) && (pImageObject->IsControlVisible()) /*&& (pImageObject->GetImageResID()) */&& !pImageObject->GetControlRect().IsRectEmpty())
			{
				vecZorder.push_back(make_pair(iterImage->first, pImageObject->GetZOrder()));
			}
		}
		sort(vecZorder.begin(), vecZorder.end(), CmpByValue());
		vector<StringIntPair>::iterator iterZOrder;
		for (iterZOrder = vecZorder.begin(); iterZOrder != vecZorder.end(); iterZOrder++)	//ZOrder���������
		{
			CDouImageObject* pImageObject = m_ImageObjectMap[iterZOrder->first];
			pImageObject->Draw(hDC);
		}
		//��Button
		//map<String, CDouControlBase1*>::iterator iterControlBase;
		//for (iterControlBase = m_ClickedObjectMap.begin(); iterControlBase != m_ClickedObjectMap.end(); iterControlBase++)
		//{
		//	CDouControlBase1*  pControlBase = iterControlBase->second;
		//	pControlBase->Draw(hDC);
		//}
		//������
		//map<String, CDouTextObject*>::iterator iterText;
		//for (iterText = m_TextObjectMap.begin(); iterText != m_TextObjectMap.end(); iterText++)
		//{
		//	CDouTextObject* pTextInfo = iterText->second;
		//	pTextInfo->Draw(hDC);
		//}
	}

	BEGIN_MSG_MAP(CDouControlImpl)
		//MESSAGE_HANDLER(WM_NCMOUSEMOVE, OnNcMouseMove)
		//MESSAGE_HANDLER(WM_NCMOUSELEAVE, OnNcMouseLeave)
		//MESSAGE_HANDLER(WM_NCLBUTTONDOWN, OnNcLButtonDown)
		//MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	END_MSG_MAP()
private:
	map<String, CDouImageObject*> m_ImageObjectMap;
};