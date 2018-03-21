#pragma once

class CDouRender
{
public:
	//»æÖÆÑÕÉ«
	static void DrawColor(HDC hdc, CRect &rcPaint, DWORD dwColor)
	{
		CDCHandle dc(hdc);
		dc.SetBkColor(RGB(GetBValue(dwColor), GetGValue(dwColor), GetRValue(dwColor)));
		dc.ExtTextOut(0, 0, ETO_OPAQUE, &rcPaint, NULL, 0, NULL);
	}
	//»æÖÆÍ¼Æ¬
	static void DrawImage(HDC hdc, const CRect& rcDst, DouBitmapSrcInfo* pBmpSrcInfo, BOOL bStretch = FALSE)
	{
		CDCHandle dc(hdc);
		CDC memDC;
		memDC.CreateCompatibleDC(dc);
		HBITMAP hOldBmp = memDC.SelectBitmap(pBmpSrcInfo->hBitmap);
		CRect rcBmpInfo = pBmpSrcInfo->rcItem;

		int iMinWidth = min(rcDst.Width(), rcBmpInfo.Width());
		int iMinHeight = min(rcDst.Height(), rcBmpInfo.Height());
		if (pBmpSrcInfo->bAlpha)
		{
			BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
			if (bStretch)
			{
				dc.AlphaBlend(rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), memDC, rcBmpInfo.left, rcBmpInfo.top, rcBmpInfo.Width(), rcBmpInfo.Height(), bf);
			}
			else
			{
				dc.AlphaBlend(rcDst.left, rcDst.top, iMinWidth, iMinHeight, memDC, rcBmpInfo.left, rcBmpInfo.top, iMinWidth, iMinHeight, bf);
			}
		}
		else
		{
			if ((rcBmpInfo.Size() == rcDst.Size()) || !bStretch)
			{
				dc.BitBlt(rcDst.left, rcDst.top, iMinWidth, iMinHeight, memDC, rcBmpInfo.left, rcBmpInfo.top, SRCCOPY);
			}
			else
			{
				dc.StretchBlt(rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), memDC, rcBmpInfo.left, rcBmpInfo.top, rcBmpInfo.Width(), rcBmpInfo.Height(), SRCCOPY);
			}
		}
		memDC.SelectBitmap(hOldBmp);
	}
};