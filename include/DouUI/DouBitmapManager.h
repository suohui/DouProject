#ifndef __DOUBITMAPMANAGER_H__
#define __DOUBITMAPMANAGER_H__
#pragma once

//ͼ
enum DouResIDType
{
	Bitmap = 0,
	ItemList,
	SubItem	//�±��1��ʼ
};
//ͼƬ��ʽ
enum DouBitmapType
{
	OnlyOne = -1,
	TwoInOne = -2,
	ThreeInOne = -3,
	FourInOne = -4
};
//λͼ�ļ���Ϣ����Ҫ�ͷž��
struct DouBitmapFileInfo
{
	HBITMAP hBitmap;
	int iWidth;
	int iHeight;
	BOOL bAlpha;
	DouBitmapType enumBmpType;
};
//λͼԴ��Ϣ�����ͷž��
struct DouBitmapSrcInfo
{
	HBITMAP hBitmap;
	CRect rcItem;
	BOOL bAlpha;
};

class CDouBitmapManager
{
private:
	CDouBitmapManager();
	~CDouBitmapManager();

public:
	static CDouBitmapManager& Instance();
	static DouBitmapFileInfo * FromFile(String strFileName, DouBitmapType enumBmpType);
	static DouBitmapFileInfo * FromMemory(LPBYTE pData, DWORD dwSize, DouBitmapType enumBmpType);
	static void FreeImage(DouBitmapFileInfo *pBmpFileInfo);
	DouBitmapSrcInfo* GetBmpSrcInfo(String strID);
private:
	void Free();
	void AddToBmpSrcInfoMap(String strID, DouBitmapFileInfo *pBmpFileInfo, int iIndex = 1);
private:
	std::map<String, DouBitmapFileInfo*>	m_BmpFileInfoMap;
	std::map<String, DouBitmapSrcInfo*>	m_BmpSrcInfoMap;
};

#define gBmpManager CDouBitmapManager::Instance()

#endif //__DOUBITMAPMANAGER_H__