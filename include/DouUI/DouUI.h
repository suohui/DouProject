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
////////////////////定义颜色
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
////////////////////定义字体
struct TDouFontInfo
{
	LPCTSTR sID;
	int  iSize;
	BOOL bBold;
	BOOL bUnderLine;
	BOOL bItalic;
};
////////////////////定义图片
//图片资源类型
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
#include "AppGlobalRes.h"	//定义颜色、字体、图片资源，APP自定义
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



