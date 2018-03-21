#pragma once

class CDouZipUtils
{
public:
	CDouZipUtils(String strZipPath)
	{
		m_hZip = OpenZip((void *)strZipPath.c_str(), 0, 2);	//ZIP_FILENAME
	}
	~CDouZipUtils()
	{
		if (m_hZip != NULL)
		{
			CloseZip(m_hZip);
		}
	}

	DouBitmapFileInfo* GetBitmapFileInfo(String strFileName, DouBitmapType enumBmpType)
	{
		DouBitmapFileInfo* pBitmapFileInfo = NULL;
		if (m_hZip != NULL)
		{
			ZIPENTRY ze;
			int i;
			ZRESULT zRet = FindZipItem(m_hZip, strFileName.c_str(), true, &i, &ze);
			DWORD dwSize = ze.unc_size;
			if ((zRet == ZR_OK) && (dwSize != 0))
			{
				LPBYTE pData = new BYTE[dwSize];
				zRet = UnzipItem(m_hZip, i, pData, dwSize, 3);
				if (zRet == ZR_OK)
				{
					pBitmapFileInfo = CDouBitmapManager::FromMemory(pData, dwSize, enumBmpType);
				}
				else
				{
					delete[] pData;
					pData = NULL;
				}
			}
		}
		return pBitmapFileInfo;
	}
private:
	HZIP m_hZip;
};