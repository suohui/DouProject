#pragma once

struct TextInfo
{
	String strText;
	String strFontID;
	COLORREF dwColor;
	int iWidth;
	int iHeight;
};

class CDouRender
{
public:
	//绘制颜色
	static void DrawColor(HDC hdc, CRect &rcPaint, COLORREF clrTextColor)
	{
		CDCHandle dc(hdc);
		dc.SetBkColor(clrTextColor);
		dc.ExtTextOut(0, 0, ETO_OPAQUE, &rcPaint, NULL, 0, NULL);
	}
	//绘制图片
	static void DrawImage(HDC hdc, const CRect rcDst, DouBitmapSrcInfo* pBmpSrcInfo, UINT uFormatStyle, BOOL bStretch = FALSE)
	{
		if (NULL == pBmpSrcInfo)
		{
			return;
		}
		CDCHandle dc(hdc);
		CDC memDC;
		memDC.CreateCompatibleDC(dc);
		HBITMAP hOldBmp = memDC.SelectBitmap(pBmpSrcInfo->hBitmap);
		CRect rcBmpInfo = pBmpSrcInfo->rcItem;

		BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
		if (bStretch)
		{
			if (pBmpSrcInfo->bAlpha)
			{
				dc.AlphaBlend(rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), memDC, rcBmpInfo.left, rcBmpInfo.top, rcBmpInfo.Width(), rcBmpInfo.Height(), bf);
			}
			else
			{
				dc.StretchBlt(rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), memDC, rcBmpInfo.left, rcBmpInfo.top, rcBmpInfo.Width(), rcBmpInfo.Height(), SRCCOPY);
			}
		}
		else
		{
			int iMinWidth = min(rcDst.Width(), rcBmpInfo.Width());
			int iMinHeight = min(rcDst.Height(), rcBmpInfo.Height());
			CSize szDraw(iMinWidth, iMinHeight);
			//获取控件的绘制点和绘制矩形
			CPoint ptCtrlPaintPoint = GetControlPaintPoint(rcDst, szDraw, uFormatStyle);
			//获取图片的起始点和渲染矩形
			CPoint ptBmpPaintPoint = GetControlPaintPoint(pBmpSrcInfo->rcItem, szDraw, uFormatStyle);
			if (pBmpSrcInfo->bAlpha)
			{
				dc.AlphaBlend(ptCtrlPaintPoint.x, ptCtrlPaintPoint.y, szDraw.cx, szDraw.cy, memDC, ptBmpPaintPoint.x, ptBmpPaintPoint.y, szDraw.cx, szDraw.cy, bf);
			}
			else
			{
				dc.BitBlt(ptCtrlPaintPoint.x, ptCtrlPaintPoint.y, szDraw.cx, szDraw.cy, memDC, ptBmpPaintPoint.x, ptBmpPaintPoint.y, SRCCOPY);
			}
		}
		memDC.SelectBitmap(hOldBmp);
	}
	//绘制单行文本
	static void DrawSingleLineText(HDC hdc, String strText, RECT& rcText, COLORREF clrTextColor, String strFontID, UINT uFormat)
	{
		CDCHandle dc(hdc);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(clrTextColor);
		HFONT hOldFont = dc.SelectFont(gFontManager.GetFont(strFontID));
		SIZE szText = { 0, 0 };
		::GetTextExtentPoint32(dc, strText.c_str(), strText.length(), &szText);
		String strPaint = _T("");
		CRect rcTextClient = rcText;
		if (szText.cx > rcTextClient.Width())	//文字太多，绘制不完，以...结束
		{
			String strEndEllipsis = _T("...");
			SIZE szEndEllipsis = { 0, 0 };
			::GetTextExtentPoint32(dc, strEndEllipsis.c_str(), strEndEllipsis.length(), &szEndEllipsis);
			if (szEndEllipsis.cx < rcTextClient.Width()) //如果...也画不了，说明宽度太小了
			{
				int iStart = 0;
				szText = { 0, 0 };
				while (szText.cx < rcTextClient.Width() - szEndEllipsis.cx)
				{
					iStart++;
					::GetTextExtentPoint32(dc, strText.c_str(), iStart, &szText);
				}
				if (szText.cx > rcTextClient.Width() - szEndEllipsis.cx)
				{
					iStart--;
				}
				strPaint = strText.substr(0, iStart) + strEndEllipsis;
			}
		}
		else
			strPaint = strText;

		CPoint ptPaintPoint = GetControlPaintPoint(rcTextClient, szText, uFormat);
		::SetRect(&rcText, ptPaintPoint.x, ptPaintPoint.y, ptPaintPoint.x + szText.cx, ptPaintPoint.y + szText.cy);
		dc.TextOut(ptPaintPoint.x, ptPaintPoint.y, strPaint.c_str(), -1);
		dc.SelectFont(hOldFont);
	}
	//根据控件大小和绘制样式，确定左上角点
	static CPoint GetControlPaintPoint(CRect rcCtrlRect, CSize szText, UINT uFormat)
	{
		CPoint ptLeftTop(rcCtrlRect.left, rcCtrlRect.top);
		if ((uFormat & DOU_RIGHT) != 0)
			ptLeftTop.x = rcCtrlRect.right - szText.cx;
		if ((uFormat & DOU_BOTTOM) != 0)
			ptLeftTop.y = rcCtrlRect.bottom - szText.cy;
		if ((uFormat & DOU_CENTER) != 0)
			ptLeftTop.x = rcCtrlRect.left + (rcCtrlRect.Width() - szText.cx) / 2;
		if ((uFormat & DOU_VCENTER) != 0)
			ptLeftTop.y = rcCtrlRect.top + (rcCtrlRect.Height() - szText.cy) / 2;
		return ptLeftTop;
	}
	//绘制单行HTML文本
	//"<html fontid='' color='#'>简单的绘制，不支持嵌套</html>"
	static void DrawHtmlSingleLineText(HDC hdc, String strText, RECT rcText, COLORREF clrTextColor, String strFontID, UINT uFormat)
	{
		std::vector<TextInfo*> vecTextInfo;
		vecTextInfo.clear();
		int iTotalWidth = 0;
		int iMaxHeight = 0;
		GetHtmlStringExtend(hdc, strText, clrTextColor, strFontID, vecTextInfo, iTotalWidth, iMaxHeight);	//将HTML文本解析出来
		CPoint ptLeftTop = GetControlPaintPoint(rcText, CSize(iTotalWidth, iMaxHeight), uFormat);	//获取绘制的左上角点，由于高度不一致，所以全部用DOU_BOTTOM

		size_t vceLength = vecTextInfo.size();
		int iLeft = ptLeftTop.x;
		int iTop = ptLeftTop.y;
		for (size_t iIndex = 0; iIndex < vceLength; iIndex++)	//逐一绘制
		{
			TextInfo* pTextInfo = vecTextInfo[iIndex];
			CRect rcText(iLeft, iTop, iLeft + pTextInfo->iWidth, iTop + iMaxHeight);
			DrawSingleLineText(hdc, pTextInfo->strText, rcText, pTextInfo->dwColor, pTextInfo->strFontID, DOU_BOTTOM);
			iLeft = iLeft + pTextInfo->iWidth;
		}
	}
	//绘制多行文本
	static void DrawMultiLineText(HDC hdc, String strText, RECT& rcText, COLORREF clrTextColor, String strFontID, int iRowHeight)
	{
		CDCHandle dc(hdc);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(clrTextColor);
		HFONT hOldFont = dc.SelectFont(gFontManager.GetFont(strFontID));

		//将字符串保存起来，加快渲染速度，另外，仅Font和Text会影响绘制
		//第一步：按\r\n分隔字符串
		std::vector<String> vecText;
		vecText.clear();
		size_t iOffset = 0;
		size_t nPos = strText.find(_T("\r\n"), iOffset);
		while (String::npos != nPos)
		{
			String strSubString = strText.substr(iOffset, nPos - iOffset);
			vecText.push_back(strSubString);
			iOffset = nPos + 2;
			nPos = strText.find(_T("\r\n"), iOffset);
		}
		String strSubString = strText.substr(iOffset);
		vecText.push_back(strSubString);
		//第二步：按宽度分隔字符串
		int iPaintWidth = rcText.right - rcText.left;
		int iPaintHeight = rcText.bottom - rcText.top;
		std::vector<String> vecTextLines;
		vecTextLines.clear();
		size_t iTextLines = vecText.size();
		int iHeight = 0;
		int iRowSpan = 4;
		for (size_t iIndex = 0; iIndex < iTextLines; iIndex++)
		{
			String strTextTmp = vecText[iIndex];
			int iTextLen = strTextTmp.length();
			CSize szTextTmp;
			::GetTextExtentPoint32(hdc, strTextTmp.c_str(), iTextLen, &szTextTmp); //获取总宽度
			if (szTextTmp.cx <= iPaintWidth)
			{
				vecTextLines.push_back(strTextTmp);
			}
			else
			{
				//按行来画
				int iEnd = 0;
				LPCTSTR lpTmp = strTextTmp.c_str();
				while (iEnd < iTextLen)
				{
					SIZE szTmp = { 0, 0 };
					int iCount = 0;
					while (szTmp.cx < iPaintWidth && iEnd < iTextLen)
					{
						iCount++;
						::GetTextExtentPoint32(hdc, lpTmp, iCount, &szTmp);
					}
					if (szTmp.cx > iPaintWidth)
					{
						iCount--;
					}
					String str = strTextTmp.substr(iEnd, iCount);
					vecTextLines.push_back(str);
					iEnd += iCount;
					lpTmp = strTextTmp.c_str() + iEnd;
				}
			}
		}
		//第三步：按行高度和行距处理，注意超过的字符
		std::vector<String> vecTextLinesNotify;
		vecTextLinesNotify.clear();
		size_t iLines = vecTextLines.size();
		int iTextHeight = 0;
		for (size_t iIndex = 0; iIndex < iLines; iIndex++)
		{
			String strTmp = vecTextLines[iIndex];
			CSize szTmp;
			::GetTextExtentPoint32(hdc, strTmp.c_str(), strTmp.length(), &szTmp);
			if (iTextHeight + szTmp.cy <= iPaintHeight)
			{
				iTextHeight += szTmp.cy + iRowSpan;
				vecTextLinesNotify.push_back(strTmp);
			}
			else //超过高度，将剩余字符给最后一个字符串
			{
				if (iIndex > 0)
				{
					String strLastLine;
					for (size_t iRemainder = iIndex - 1; iRemainder < iLines; iRemainder++)
					{
						strLastLine.append(vecTextLines[iRemainder]);
					}
					vecTextLinesNotify[iIndex - 1] = strLastLine;
				}
				break;
			}
		}
		if (vecTextLinesNotify.size() >= 2)
		{
			iTextHeight -= iRowSpan;
		}


		//第四步：按格式绘制
		int iTop = rcText.top;
		iLines = vecTextLinesNotify.size();
		for (size_t iIndex = 0; iIndex < iLines; iIndex++)
		{
			String strTmp = vecTextLinesNotify[iIndex];
			CSize szTmp;
			::GetTextExtentPoint32(hdc, strTmp.c_str(), strTmp.length(), &szTmp);
			DrawSingleLineText(hdc, strTmp, CRect(rcText.left, iTop, rcText.right, iTop + szTmp.cy), clrTextColor, strFontID, DOU_LEFT | DOU_TOP);
			iTop += szTmp.cy + iRowSpan;
		}
		dc.SelectFont(hOldFont);
		return;


		//int iIndex = 0;
		//int iTop = rcText.top;
		//int iLines = (rcText.bottom - rcText.top) / iRowHeight;

		//for (size_t i = 0; i < vecText.size(); i++)
		//{
		//	String strTextTmp = vecText[i];
		//	int iLength = strTextTmp.length();
		//	
		//	LPCTSTR lpTmp = strTextTmp.c_str();
		//	
		//	for (int i = iIndex; i < iLines; i++)
		//	{
		//		//按行来画
		//		int iStart = 0;
		//		int iLenTmp = 0;
		//		SIZE size = { 0, 0 };
		//		while (size.cx < rcText.right - rcText.left && iIndex + iLenTmp < iLength)
		//		{
		//			iStart++;
		//			iLenTmp++;
		//			::GetTextExtentPoint32(hdc, lpTmp, iStart, &size);
		//		}
		//		if (size.cx > rcText.right - rcText.left)
		//		{
		//			iStart--;
		//		}
		//		dc.TextOut(rcText.left, iTop, lpTmp, iStart);
		//		iIndex += iStart;
		//		iTop += iRowHeight;
		//		lpTmp = strTextTmp.c_str() + iIndex;
		//		if (iIndex < iLength && i == iLines - 2) //最后一行特殊处理,超出的 就不再画了
		//		{
		//			DrawSingleLineText(hdc, lpTmp, CRect(rcText.left, iTop, rcText.right, rcText.bottom), clrTextColor, strFontID, DOU_LEFT | DOU_TOP);
		//			break;
		//		}
		//	}
		//}

		//dc.SelectFont(hOldFont);
	}

	static void DouDrawText(HDC hdc, String strText, RECT& rcText, COLORREF clrTextColor, String strFontID, UINT uFormat, BOOL bMultipLine, int iRowHeight)
	{
		if (bMultipLine)
		{
			DrawMultiLineText(hdc, strText, rcText, clrTextColor, strFontID, iRowHeight);
		}
		else
		{
			DrawSingleLineText(hdc, strText, rcText, clrTextColor, strFontID, uFormat);
		}
	}
	//绘制HTML文本
	static void DrawHtmlText(HDC hdc, String strText, RECT& rcText, COLORREF clrTextColor, String strFontID, UINT uFormat, BOOL bMultipLine, int iRowHeight)
	{
		if (bMultipLine)
		{
			DrawMultiLineText(hdc, strText, rcText, clrTextColor, strFontID, iRowHeight);
		}
		else
		{
			DrawHtmlSingleLineText(hdc, strText, rcText, clrTextColor, strFontID, uFormat);
		}
	}

	//获取HTML标签的值
	static String GetHtmlTagValue(String strStyleText, String strTag)
	{
		String strRet = _T("");
		size_t iFound = strStyleText.find(strTag);
		if (iFound != String::npos)
		{
			size_t iQuotesLeft = strStyleText.find(_T('\''), iFound);
			if (iQuotesLeft != String::npos)
			{
				size_t iQuotesRight = strStyleText.find(_T('\''), iQuotesLeft + 1);
				if (iQuotesRight != String::npos)
				{
					strRet = strStyleText.substr(iQuotesLeft + 1, iQuotesRight - iQuotesLeft - 1);
				}
			}
		}
		return strRet;
	}
	//创建TextInfo结构
	static TextInfo* GetTextInfo(HDC hdc, String strText, COLORREF clrTextColor, String strFontID)
	{
		CDCHandle dc(hdc);
		HFONT hOldFont = dc.SelectFont(gFontManager.GetFont(strFontID));
		SIZE szText = { 0, 0 };
		::GetTextExtentPoint32(dc, strText.c_str(), strText.length(), &szText);
		dc.SelectFont(hOldFont);
		TextInfo *pTextInfo = new TextInfo;
		pTextInfo->strText = strText;
		pTextInfo->strFontID = strFontID;
		pTextInfo->dwColor = clrTextColor;
		pTextInfo->iWidth = szText.cx;
		pTextInfo->iHeight = szText.cy;
		return pTextInfo;
	}
	//将HTML文件分隔，并获取总宽度 和 最大高度
	static void GetHtmlStringExtend(HDC hdc, String strText, COLORREF clrTextColor, String strDefaultFontID, std::vector<TextInfo *> &vecTextInfoRet, int &iTotalWidth, int &iMaxHeight)
	{
		iTotalWidth = 0;
		iMaxHeight = 0;
		size_t iStart = 0;
		String strTmp = strText;
		do
		{
			size_t nTagStartLeft = strTmp.find(_T("<html"));
			if (nTagStartLeft == String::npos)
			{
				//添加正常的//最后一截
				TextInfo *pNormalTextInfo = GetTextInfo(hdc, strTmp.substr(iStart), clrTextColor, strDefaultFontID);
				iTotalWidth += pNormalTextInfo->iWidth;
				iMaxHeight = max(iMaxHeight, pNormalTextInfo->iHeight);
				vecTextInfoRet.push_back(pNormalTextInfo);
				break;
			}
			else
			{
				size_t nTagStartRight = strTmp.find(_T(">"));
				size_t nTagEnd = strTmp.find(_T("</html>"), nTagStartRight);
				if ((nTagStartRight == String::npos) || (nTagEnd == String::npos))
				{
					break;
				}
				//添加正常的
				String strNormalText = strTmp.substr(iStart, nTagStartLeft);
				if (!strNormalText.empty())
				{
					TextInfo *pNormalTextInfo = GetTextInfo(hdc, strNormalText, clrTextColor, strDefaultFontID);
					iTotalWidth += pNormalTextInfo->iWidth;
					iMaxHeight = max(iMaxHeight, pNormalTextInfo->iHeight);
					vecTextInfoRet.push_back(pNormalTextInfo);
				}
				//添加html修饰的
				String strHtmlText = strTmp.substr(nTagStartRight + 1, nTagEnd - nTagStartRight - 1);
				if (!strHtmlText.empty())
				{
					String strStyle = strTmp.substr(nTagStartLeft + 6, nTagStartRight - nTagStartLeft - 6);
					String strHtmlFontID = GetHtmlTagValue(strStyle, _T("fontid"));
					String strHtmlColor = GetHtmlTagValue(strStyle, _T("color"));
					COLORREF clrColor = clrTextColor;
					if (!strHtmlColor.empty())
					{
						if (strHtmlColor[0] == _T('#'))
						{
							LPTSTR lpEndPtr;
							DWORD dwColor = _tcstol(strHtmlColor.c_str() + 1, &lpEndPtr, 16);
							clrColor = RGB(GetBValue(dwColor), GetGValue(dwColor), GetRValue(dwColor));
						}
						else
						{
							clrColor = gColorManager.GetColor(strHtmlColor);
						}
					}
					String strFont = strHtmlFontID.empty() ? strDefaultFontID : strHtmlFontID;
					TextInfo *pHtmlTextInfo = GetTextInfo(hdc, strHtmlText, clrColor, strFont);
					iTotalWidth += pHtmlTextInfo->iWidth;
					iMaxHeight = max(iMaxHeight, pHtmlTextInfo->iHeight);
					vecTextInfoRet.push_back(pHtmlTextInfo);
					strTmp = strTmp.substr(nTagEnd + 7);
				}
			}
		} while (!strTmp.empty());
	}
};