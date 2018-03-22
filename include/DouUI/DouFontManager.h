#pragma once

typedef std::map<String, HFONT> FONTMAP;
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
		} fts[] = {
			{ _T("default.font"), 12, FALSE, FALSE, FALSE },
		{ _T("default.font13"), 15, FALSE, FALSE, FALSE }
		};

		LOGFONT m_lf;
		::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &m_lf);
		m_lf.lfCharSet = DEFAULT_CHARSET;
		lstrcpy(m_lf.lfFaceName, _T("Î¢ÈíÑÅºÚ"));

		for (size_t i = 0; i < sizeof(fts) / sizeof(fts[0]); i++)
		{
			m_lf.lfHeight = -fts[i].iSize;
			m_lf.lfWeight = fts[i].bBold ? FW_BOLD : 0;
			m_lf.lfUnderline = fts[i].bUnderLine;
			m_lf.lfItalic = fts[i].bItalic;
			m_hFontMap[fts[i].sID] = ::CreateFontIndirect(&m_lf);
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
			FONTMAP::iterator iter;
			for (iter = m_hFontMap.begin(); iter != m_hFontMap.end(); iter++)
			{
				DeleteObject(iter->second);
			}
			m_hFontMap.clear();
		}
	}
private:
	static CDouFontManager* m_pFontManager;
	FONTMAP m_hFontMap;
};

#define gFontManager CDouFontManager::Instance()