#include "stdafx.h"
#include "DouUI.h"
#include "DouBitmapManager.h"

CDouBitmapManager::CDouBitmapManager()
{
	struct
	{
		String strID;
		DouResIDType enumIDType;
		String strPathOrOwner;
		union
		{
			int iItemIndex;
			DouBitmapType enumBmpType;
		};
	} arrBmpResInfo[] =
	{
		{ L"MainWnd.Bkg.Titlebar", DouResIDType::Bitmap, L"������\\������.png", DouBitmapType::OnlyOne },
	{ L"MainWnd.Btn.Menu", DouResIDType::ItemList, L"������\\�˵�.png", DouBitmapType::ThreeInOne },	//��������ItemList������SubItem
	{ L"MainWnd.Btn.Menu.normal", DouResIDType::SubItem, L"MainWnd.Btn.Menu", 1 },
	{ L"MainWnd.Btn.Menu.hover", DouResIDType::SubItem, L"MainWnd.Btn.Menu", 2 },
	{ L"MainWnd.Btn.Menu.press", DouResIDType::SubItem, L"MainWnd.Btn.Menu", 3 },
	{ L"MainWnd.Btn.Min", DouResIDType::ItemList, L"������\\��С��.png", DouBitmapType::ThreeInOne },
	{ L"MainWnd.Btn.Min.normal", DouResIDType::SubItem, L"MainWnd.Btn.Min", 1 },
	{ L"MainWnd.Btn.Min.hover", DouResIDType::SubItem, L"MainWnd.Btn.Min", 2 },
	{ L"MainWnd.Btn.Min.press", DouResIDType::SubItem, L"MainWnd.Btn.Min", 3 },
	{ L"MainWnd.Btn.Close", DouResIDType::ItemList, L"������\\������.png", DouBitmapType::ThreeInOne },
	{ L"MainWnd.Btn.Close.normal", DouResIDType::SubItem, L"MainWnd.Btn.Close", 1 },
	{ L"MainWnd.Btn.Close.hover", DouResIDType::SubItem, L"MainWnd.Btn.Close", 2 },
	{ L"MainWnd.Btn.Close.press", DouResIDType::SubItem, L"MainWnd.Btn.Close", 3 },
	};

	m_BmpFileInfoMap.clear();
	m_BmpSrcInfoMap.clear();
	CDouZipUtils zipUtils(CDouUtils::GetImageZipPath());
	for (size_t iIndex = 0; iIndex < sizeof(arrBmpResInfo) / sizeof(arrBmpResInfo[0]); iIndex++)
	{
		DouBitmapFileInfo* pBmpFileInfo = NULL;
		switch (arrBmpResInfo[iIndex].enumIDType)
		{
		case DouResIDType::Bitmap:
			pBmpFileInfo = zipUtils.GetBitmapFileInfo(arrBmpResInfo[iIndex].strPathOrOwner, arrBmpResInfo[iIndex].enumBmpType);
			m_BmpFileInfoMap[arrBmpResInfo[iIndex].strID] = pBmpFileInfo;
			AddToBmpSrcInfoMap(arrBmpResInfo[iIndex].strID, pBmpFileInfo);//�����ļ���������ID�б�
			break;
		case DouResIDType::ItemList:
			pBmpFileInfo = zipUtils.GetBitmapFileInfo(arrBmpResInfo[iIndex].strPathOrOwner, arrBmpResInfo[iIndex].enumBmpType);
			m_BmpFileInfoMap[arrBmpResInfo[iIndex].strID] = pBmpFileInfo;//ֻ�����ļ���������ID�б�
			break;
		case DouResIDType::SubItem:
			if (NULL != m_BmpFileInfoMap[arrBmpResInfo[iIndex].strPathOrOwner])
			{
				pBmpFileInfo = m_BmpFileInfoMap[arrBmpResInfo[iIndex].strPathOrOwner];
				AddToBmpSrcInfoMap(arrBmpResInfo[iIndex].strID, pBmpFileInfo, arrBmpResInfo[iIndex].iItemIndex);//�������ļ���ֻ����ID�б�
			}
			break;
		}
	}
}
CDouBitmapManager::~CDouBitmapManager()
{
	Free();
}

//�����е� new �Ķ�����Ҫdelete�ͷš�
//delete�ͷŶ����ʱ��Ż���ö������������
CDouBitmapManager& CDouBitmapManager::GetInstance()
{
	static CDouBitmapManager bmpManagerInstance;
	return bmpManagerInstance;
}
DouBitmapFileInfo* CDouBitmapManager::FromFile(String strFileName, DouBitmapType enumBmpType)
{
	HANDLE hFile = ::CreateFile(strFileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}
	DWORD dwSize = ::GetFileSize(hFile, NULL);
	if (dwSize == 0)
	{
		return NULL;
	}
	LPBYTE pData = new BYTE[dwSize];
	DWORD dwRead = 0;
	::ReadFile(hFile, pData, dwSize, &dwRead, NULL);
	::CloseHandle(hFile);
	if (dwRead != dwSize)
	{
		delete[] pData;
		pData = NULL;
		return NULL;
	}
	return CDouBitmapManager::FromMemory(pData, dwSize, enumBmpType);
}

DouBitmapFileInfo* CDouBitmapManager::FromMemory(LPBYTE pData, DWORD dwSize, DouBitmapType enumBmpType)
{
	int x = 1, y = 1, n;
	LPBYTE pImage = stbi_load_from_memory(pData, dwSize, &x, &y, &n, 4);
	delete[] pData;
	pData = NULL;
	if (pImage == NULL)
	{
		return NULL;
	}

	BITMAPINFO bmi;
	::ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biWidth = x;
	bmi.bmiHeader.biHeight = -y;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = x * y * 4;

	BOOL bAlpha = false;
	LPBYTE pDest = NULL;
	HBITMAP hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void **)&pDest, NULL, 0);
	if (hBitmap == NULL)
	{
		stbi_image_free(pImage);
		return NULL;
	}

	for (int i = 0; i < x * y; i++)
	{
		pDest[i * 4 + 3] = pImage[i * 4 + 3];
		if (pDest[i * 4 + 3] < 255)
		{
			pDest[i * 4] = (BYTE)(DWORD(pImage[i * 4 + 2])*pImage[i * 4 + 3] / 255);
			pDest[i * 4 + 1] = (BYTE)(DWORD(pImage[i * 4 + 1])*pImage[i * 4 + 3] / 255);
			pDest[i * 4 + 2] = (BYTE)(DWORD(pImage[i * 4])*pImage[i * 4 + 3] / 255);
			bAlpha = TRUE;
		}
		else
		{
			pDest[i * 4] = pImage[i * 4 + 2];
			pDest[i * 4 + 1] = pImage[i * 4 + 1];
			pDest[i * 4 + 2] = pImage[i * 4];
		}
	}
	stbi_image_free(pImage);

	DouBitmapFileInfo* pBmpFileInfo = new DouBitmapFileInfo();
	pBmpFileInfo->hBitmap = hBitmap;
	pBmpFileInfo->iWidth = x;
	pBmpFileInfo->iHeight = y;
	pBmpFileInfo->bAlpha = bAlpha;
	pBmpFileInfo->enumBmpType = enumBmpType;
	return pBmpFileInfo;
}

void CDouBitmapManager::FreeImage(DouBitmapFileInfo *pBmpFileInfo)
{
	if (NULL != pBmpFileInfo)
	{
		::DeleteObject(pBmpFileInfo->hBitmap);
		pBmpFileInfo->hBitmap = NULL;
		delete pBmpFileInfo;
		pBmpFileInfo = NULL;
	}
}

DouBitmapSrcInfo* CDouBitmapManager::GetBmpSrcInfo(String strID)
{
	return m_BmpSrcInfoMap[strID];
}

void CDouBitmapManager::Free()
{
	//λͼ�ļ���Ϣ����Ҫ�ͷž��
	map<String, DouBitmapFileInfo*>::iterator iterBmpFileInfo;
	for (iterBmpFileInfo = m_BmpFileInfoMap.begin(); iterBmpFileInfo != m_BmpFileInfoMap.end(); iterBmpFileInfo++)
	{
		CDouBitmapManager::FreeImage(iterBmpFileInfo->second);
	}
	m_BmpFileInfoMap.clear();
	//λͼԴ��Ϣ�����ͷž��
	map<String, DouBitmapSrcInfo*>::iterator iterBmpSrcInfo;
	for (iterBmpSrcInfo = m_BmpSrcInfoMap.begin(); iterBmpSrcInfo != m_BmpSrcInfoMap.end(); iterBmpSrcInfo++)
	{
		delete iterBmpSrcInfo->second;
	}
	m_BmpSrcInfoMap.clear();
}

void CDouBitmapManager::AddToBmpSrcInfoMap(String strID, DouBitmapFileInfo *pBmpFileInfo, int iIndex/* = 1*/)
{
	if (m_BmpSrcInfoMap[strID] == NULL)
	{
		DouBitmapSrcInfo* pBmpSrcInfo = new DouBitmapSrcInfo;
		pBmpSrcInfo->hBitmap = pBmpFileInfo->hBitmap;
		int iBmpWidth = pBmpFileInfo->iWidth;
		int iBmpHeight = pBmpFileInfo->iHeight;
		switch (pBmpFileInfo->enumBmpType)
		{
		case DouBitmapType::TwoInOne:
			pBmpSrcInfo->rcItem.SetRect((iIndex - 1) * iBmpWidth / 2, 0, iIndex * iBmpWidth / 2, iBmpHeight);
			break;
		case DouBitmapType::ThreeInOne:
			pBmpSrcInfo->rcItem.SetRect((iIndex - 1) * iBmpWidth / 3, 0, iIndex * iBmpWidth / 3, iBmpHeight);
			break;
		case DouBitmapType::FourInOne:
			pBmpSrcInfo->rcItem.SetRect((iIndex - 1) * iBmpWidth / 4, 0, iIndex * iBmpWidth / 4, iBmpHeight);
			break;
		default:
			pBmpSrcInfo->rcItem.SetRect(0, 0, iBmpWidth, iBmpHeight);
			break;
		}
		pBmpSrcInfo->bAlpha = pBmpFileInfo->bAlpha;
		m_BmpSrcInfoMap[strID] = pBmpSrcInfo;
	}
}