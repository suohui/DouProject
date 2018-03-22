#pragma once

class CDouColorManager
{
public:
	CDouColorManager()
	{
		enum ColorType
		{
			HexColor,
			RGBColor
		};
		m_ColorMap.clear();
		struct
		{
			String strID;
			ColorType enumColorType;
			union
			{
				COLORREF rgbColor;
				DWORD dwHexColor;	// 0xcb8c25
			};
		} arrColorInfo[] = 
		{
		{L"system.white", RGBColor, RGB(255, 255, 255)},
		{L"system.black", RGBColor, RGB(0, 0, 0)},
		{L"color.textlink.normal", HexColor, 0x0084ff},
		{L"MainPanel.NormalColor", HexColor, 0xcb8c25}
		};
		size_t iLen = sizeof(arrColorInfo) / sizeof(arrColorInfo[0]);
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