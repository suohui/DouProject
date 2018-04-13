#pragma once

#include <atlmisc.h>    //http://blog.csdn.net/immortal_mcl/article/details/5920138
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#ifdef UNICODE
#define String  std::wstring
#else
#define String  std::string
#endif // !UNICODE

#include <stb_image.h>
#include <XUnzip.h>
#ifdef _UNICODE
#define ZIPENTRY ZIPENTRYW
#endif
////////////////////������ɫ
enum ColorType
{
	HexColor,
	RGBColor
};

struct TDouColorInfo
{
	String strID;
	ColorType enumColorType;
	union
	{
		COLORREF rgbColor;
		DWORD dwHexColor;	// 0xcb8c25
	};
};
////////////////////��������
struct TDouFontInfo
{
	LPCTSTR sID;
	int  iSize;
	BOOL bBold;
	BOOL bUnderLine;
	BOOL bItalic;
};
////////////////////����ͼƬ
//ͼƬ��Դ����
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
struct TDouBitmapInfo
{
	String strID;
	DouResIDType enumIDType;
	String strPathOrOwner;
	union
	{
		int iItemIndex;
		DouBitmapType enumBmpType;
	};
};

#include "DouUtils.h"
#include "AppGlobalRes.h"	//������ɫ�����塢ͼƬ��Դ��APP�Զ���
#include "DouBitmapManager.h"
#include "DouFontManager.h"
#include "DouColorManager.h"
#include "DouZipUtils.h"

#include "DouRender.h"

#include "DouControlBase.h"
#include "DouTextInfoBase.h"
#include "DouImageInfoBase.h"
#include "DouImageObject.h"
#include "DouImageExObject.h"
#include "DouTextObject.h"
#include "DouTextLinkObject.h"
#include "DouButtonObject.h"
#include "DouCheckboxObject.h"

#include "DouControlImpl.h"
#include "DouDlgBase.h"



