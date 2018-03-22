#pragma once

class CDouZipUtils
{
public:
	CDouZipUtils(String strZipPath);
	~CDouZipUtils();
	DouBitmapFileInfo* GetBitmapFileInfo(String strFileName, DouBitmapType enumBmpType);
private:
	HZIP m_hZip;
};