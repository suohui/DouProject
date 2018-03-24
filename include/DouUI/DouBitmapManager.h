#ifndef __DOUBITMAPMANAGER_H__
#define __DOUBITMAPMANAGER_H__
#pragma once

//图
enum DouResIDType
{
	Bitmap = 0,
	ItemList,
	SubItem	//下标从1开始
};
//图片格式
enum DouBitmapType
{
	OnlyOne = -1,
	TwoInOne = -2,
	ThreeInOne = -3,
	FourInOne = -4
};
//位图文件信息，需要释放句柄
struct DouBitmapFileInfo
{
	HBITMAP hBitmap;
	int iWidth;
	int iHeight;
	BOOL bAlpha;
	DouBitmapType enumBmpType;
};
//位图源信息，不释放句柄
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