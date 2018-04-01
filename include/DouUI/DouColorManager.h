#pragma once
class CDouColorManager
{
public:
	CDouColorManager()
	{
		m_ColorMap.clear();
		std::vector<TDouColorInfo> arrColorInfo;
		CAppResource::GetColorResInfo(arrColorInfo);
		size_t iLen = arrColorInfo.size();
		for (size_t iIndex = 0; iIndex < iLen; iIndex++)
		{
			switch (arrColorInfo[iIndex].enumColorType)
			{
			case ColorType::HexColor:
			{
				DWORD dwColor = arrColorInfo[iIndex].dwHexColor;
				m_ColorMap[arrColorInfo[iIndex].strID] = RGB(GetBValue(dwColor), GetGValue(dwColor), GetRValue(dwColor));
			}
				break;
			case ColorType::RGBColor:
				m_ColorMap[arrColorInfo[iIndex].strID] = arrColorInfo[iIndex].rgbColor;
				break;
			}
		}
	}
	~CDouColorManager()
	{
		m_ColorMap.clear();
	}
	static CDouColorManager& Instance()
	{
		static CDouColorManager colorManagerInstance;
		return colorManagerInstance;
	}
	COLORREF GetColor(String strID)
	{
		return (m_ColorMap[strID] == NULL) ? 0 : m_ColorMap[strID];
	}
private:
	std::map<String, COLORREF> m_ColorMap;
};

#define gColorManager CDouColorManager::Instance()