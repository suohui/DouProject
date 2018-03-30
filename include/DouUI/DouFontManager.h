#pragma once

class CDouFontManager
{
protected:
	CDouFontManager()
	{
		struct FontType
		{
			LPCTSTR sID;
			int  iSize;
			BOOL bBold;
			BOOL bUnderLine;
			BOOL bItalic;
		} arrFontInfo[] = {
			{ _T("default.font"), 12, FALSE, FALSE, FALSE },
		{ _T("Font14"), 14, FALSE, FALSE, FALSE },
		{ _T("Font14.U"), 14, FALSE, TRUE, FALSE },
		{ _T("Font14.B"), 14, TRUE, FALSE, FALSE },
		};

		LOGFONT m_lf;
		::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &m_lf);
		m_lf.lfCharSet = DEFAULT_CHARSET;
		lstrcpy(m_lf.lfFaceName, _T("Î¢ÈíÑÅºÚ"));

		size_t iLen = sizeof(arrFontInfo) / sizeof(arrFontInfo[0]);
		for (size_t i = 0; i < iLen; i++)
		{
			m_lf.lfHeight = -arrFontInfo[i].iSize;
			m_lf.lfWeight = arrFontInfo[i].bBold ? FW_BOLD : 0;
			m_lf.lfUnderline = arrFontInfo[i].bUnderLine;
			m_lf.lfItalic = arrFontInfo[i].bItalic;
			m_hFontMap[arrFontInfo[i].sID] = ::CreateFontIndirect(&m_lf);
		}
	}

	~CDouFontManager()
	{
		DeleteFont();
	}
public:
	HFONT GetFont(String strFontID)
	{
		return m_hFontMap[strFontID];
	}
	
	static CDouFontManager& Instance()
	{
		static CDouFontManager fontManagerInstance;
		return fontManagerInstance;
	}
private:
	void DeleteFont()
	{
		if (!m_hFontMap.empty())
		{
			std::map<String, HFONT>::iterator iter;
			for (iter = m_hFontMap.begin(); iter != m_hFontMap.end(); iter++)
			{
				DeleteObject(iter->second);
			}
			m_hFontMap.clear();
		}
	}
private:
	std::map<String, HFONT> m_hFontMap;
};

#define gFontManager CDouFontManager::Instance()