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
	//������ɫ
	static void DrawColor(HDC hdc, CRect &rcPaint, COLORREF clrTextColor)
	{
		CDCHandle dc(hdc);
		dc.SetBkColor(clrTextColor);
		dc.ExtTextOut(0, 0, ETO_OPAQUE, &rcPaint, NULL, 0, NULL);
	}
	//����ͼƬ
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
			//��ȡ�ؼ��Ļ��Ƶ�ͻ��ƾ���
			CPoint ptCtrlPaintPoint = GetControlPaintPoint(rcDst, szDraw, uFormatStyle);
			//��ȡͼƬ����ʼ�����Ⱦ����
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






		//int iMinWidth = min(rcDst.Width(), rcBmpInfo.Width());
		//int iMinHeight = min(rcDst.Height(), rcBmpInfo.Height());
		//if (pBmpSrcInfo->bAlpha)
		//{
		//	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
		//	if (bStretch)
		//	{
		//		dc.AlphaBlend(rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), memDC, rcBmpInfo.left, rcBmpInfo.top, rcBmpInfo.Width(), rcBmpInfo.Height(), bf);
		//	}
		//	else
		//	{
		//		dc.AlphaBlend(rcDst.left, rcDst.top, iMinWidth, iMinHeight, memDC, rcBmpInfo.left, rcBmpInfo.top, iMinWidth, iMinHeight, bf);
		//	}
		//}
		//else
		//{
		//	if ((rcBmpInfo.Size() == rcDst.Size()) || !bStretch)
		//	{
		//		dc.BitBlt(rcDst.left, rcDst.top, iMinWidth, iMinHeight, memDC, rcBmpInfo.left, rcBmpInfo.top, SRCCOPY);
		//	}
		//	else
		//	{
		//		dc.StretchBlt(rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), memDC, rcBmpInfo.left, rcBmpInfo.top, rcBmpInfo.Width(), rcBmpInfo.Height(), SRCCOPY);
		//	}
		//}
		memDC.SelectBitmap(hOldBmp);
	}
	//���Ƶ����ı�
	static void DrawSingleLineText(HDC hdc, String strText, RECT rcText, COLORREF clrTextColor, String strFontID, UINT uFormat)
	{
		CDCHandle dc(hdc);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(clrTextColor);
		HFONT hOldFont = dc.SelectFont(gFontManager.GetFont(strFontID));
		SIZE szText = { 0, 0 };
		::GetTextExtentPoint32(dc, strText.c_str(), strText.length(), &szText);
		String strPaint = _T("");
		CRect rcTextClient = rcText;
		if (szText.cx > rcTextClient.Width())	//����̫�࣬���Ʋ��꣬��...����
		{
			String strEndEllipsis = _T("...");
			SIZE szEndEllipsis = { 0, 0 };
			::GetTextExtentPoint32(dc, strEndEllipsis.c_str(), strEndEllipsis.length(), &szEndEllipsis);
			if (szEndEllipsis.cx < rcTextClient.Width()) //���...Ҳ�����ˣ�˵�����̫С��
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
		dc.TextOut(ptPaintPoint.x, ptPaintPoint.y, strPaint.c_str(), -1);
		dc.SelectFont(hOldFont);
	}
	//���ݿؼ���С�ͻ�����ʽ��ȷ�����Ͻǵ�
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
	//���Ƶ���HTML�ı�
	//"<html fontid='' color='#'>�򵥵Ļ��ƣ���֧��Ƕ��</html>"
	static void DrawHtmlSingleLineText(HDC hdc, String strText, RECT rcText, COLORREF clrTextColor, String strFontID, UINT uFormat)
	{
		std::vector<TextInfo*> vecTextInfo;
		vecTextInfo.clear();
		int iTotalWidth = 0;
		int iMaxHeight = 0;
		GetHtmlStringExtend(hdc, strText, clrTextColor, strFontID, vecTextInfo, iTotalWidth, iMaxHeight);	//��HTML�ı���������
		CPoint ptLeftTop = GetControlPaintPoint(rcText, CSize(iTotalWidth, iMaxHeight), uFormat);	//��ȡ���Ƶ����Ͻǵ㣬���ڸ߶Ȳ�һ�£�����ȫ����DOU_BOTTOM

		size_t vceLength = vecTextInfo.size();
		int iLeft = ptLeftTop.x;
		int iTop = ptLeftTop.y;
		for (size_t iIndex = 0; iIndex < vceLength; iIndex++)	//��һ����
		{
			TextInfo* pTextInfo = vecTextInfo[iIndex];
			CRect rcText(iLeft, iTop, iLeft + pTextInfo->iWidth, iTop + iMaxHeight);
			DrawSingleLineText(hdc, pTextInfo->strText, rcText, pTextInfo->dwColor, pTextInfo->strFontID, DOU_BOTTOM);
			iLeft = iLeft + pTextInfo->iWidth;
		}
	}
	//���ƶ����ı�
	static void DrawMultiLineText(HDC hdc, String strText, RECT rcText, COLORREF clrTextColor, String strFontID, int iRowHeight)
	{
		CDCHandle dc(hdc);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(clrTextColor);
		HFONT hOldFont = dc.SelectFont(gFontManager.GetFont(strFontID));
		{
			int iLength = strText.length();
			int iIndex = 0;
			LPCTSTR lpTmp = strText.c_str();
			int iTop = 0;

			int iLines = (rcText.bottom - rcText.top) / iRowHeight;
			for (int i = 0; i < iLines; i++)
			{
				//��������
				int iStart = 0;
				int iLenTmp = 0;
				SIZE size = { 0, 0 };
				while (size.cx < rcText.right - rcText.left && iIndex + iLenTmp < iLength)
				{
					iStart++;
					iLenTmp++;
					::GetTextExtentPoint32(hdc, lpTmp, iStart, &size);
				}
				if (size.cx > rcText.right - rcText.left)
				{
					iStart--;
				}
				dc.TextOut(0, iTop, lpTmp, iStart);
				iIndex += iStart;
				iTop += iRowHeight;
				lpTmp = strText.c_str() + iIndex;
				if (iIndex < iLength && i == iLines - 2) //���һ�����⴦��,������ �Ͳ��ٻ���
				{
					DrawSingleLineText(hdc, lpTmp, CRect(0, iTop, rcText.right, rcText.bottom), clrTextColor, strFontID, DOU_LEFT | DOU_TOP);
					break;
				}
			}
		}

		dc.SelectFont(hOldFont);
	}

	static void DrawText(HDC hdc, String strText, RECT& rcText, COLORREF clrTextColor, String strFontID, UINT uFormat, BOOL bMultipLine, int iRowHeight)
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
	//����HTML�ı�
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

	//��ȡHTML��ǩ��ֵ
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
	//����TextInfo�ṹ
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
	//��HTML�ļ��ָ�������ȡ�ܿ�� �� ���߶�
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
				//���������//���һ��
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
				//���������
				String strNormalText = strTmp.substr(iStart, nTagStartLeft);
				if (!strNormalText.empty())
				{
					TextInfo *pNormalTextInfo = GetTextInfo(hdc, strNormalText, clrTextColor, strDefaultFontID);
					iTotalWidth += pNormalTextInfo->iWidth;
					iMaxHeight = max(iMaxHeight, pNormalTextInfo->iHeight);
					vecTextInfoRet.push_back(pNormalTextInfo);
				}
				//���html���ε�
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