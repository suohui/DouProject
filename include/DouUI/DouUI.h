#pragma once

#include <atlmisc.h>    //http://blog.csdn.net/immortal_mcl/article/details/5920138
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
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

#include "DouUtils.h"
#include "DouBitmapManager.h"
#include "DouRender.h"

#include "DouControlBase.h"
#include "DouImageObject.h"

#include "DouControlImpl.h"
#include "DouDlgBase.h"
