//---------------------------------------------------------------------------
#include "XBuffer.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

//---------------------------------------------------------------------------
XBuffer::XBuffer()
{
    m_cSplitChar = '|';

    m_iBufLen = 4096;
    m_szBuffer = new char[m_iBufLen + 1];
    memset(m_szBuffer, 0, m_iBufLen + 1);

}

//---------------------------------------------------------------------------
XBuffer::~XBuffer()
{
    if(m_szBuffer)
    {
        delete m_szBuffer;
        m_szBuffer = NULL;
    }

	m_pvItems.clear();
}

//---------------------------------------------------------------------------
void XBuffer::Clear()
{
    try
    {
        memset(m_szBuffer, 0, m_iBufLen + 1);
		m_pvItems.clear();
    }
    catch(...)
    {
    }
}

//---------------------------------------------------------------------------
bool XBuffer::Process()
{
    char * szStart;
    char * szEnd;

    try
    {

		m_pvItems.clear();

        szStart = m_szBuffer;

        for(;;)
        {
			std::string str = "";
            szEnd = strchr(szStart, m_cSplitChar);
			if (szEnd == NULL)
			{				
				str = std::string(szStart);
				m_pvItems.push_back(str);				
				break;
			}
			else
			{
				*szEnd = 0;
			}

			str = std::string(szStart);
			m_pvItems.push_back(str);

            szStart = szEnd + 1;
        }
    }
    catch(...)
    {
    }

    return true;
}

//---------------------------------------------------------------------------
bool XBuffer::Set(const char * szBuffer, int iLen)
{
    if(iLen > m_iBufLen)
    {
        delete m_szBuffer;

        m_szBuffer = new char[iLen + 1];

    }

    memset(m_szBuffer, 0, m_iBufLen);
    memcpy(m_szBuffer, szBuffer, iLen);
    m_szBuffer[iLen] = 0;

    m_iBufLen = iLen;

    return Process();
}

//---------------------------------------------------------------------------
bool XBuffer::Set(const char * szFormat, ...)
{
    
	char szBuff[4096];

	va_list arg_ptr;

    va_start(arg_ptr, szFormat);
    vprintf(szFormat, arg_ptr);
    va_end(arg_ptr);

	return Set(szBuff, strlen(szBuff));
}

//---------------------------------------------------------------------------
bool XBuffer::Set(std::string strBuffer)
{
    return Set(strBuffer.c_str(), strBuffer.length());
}

//---------------------------------------------------------------------------
int XBuffer::GetItemCount()
{
	return m_pvItems.size();
}

//---------------------------------------------------------------------------
const char * XBuffer::GetItem(int iItem)
{
    if(iItem < 0 || iItem >= GetItemCount())
        return "";
    else
    {
		return m_pvItems[iItem].c_str();
    }
}
//--------------------------------------------------------------------------
const char * XBuffer::toString(void)
{
    std::string strResult;
    int iItemCount = GetItemCount();
    for(int i = 0; i < iItemCount; i++)
    {
       strResult += GetItem(i);
	   if (i < (iItemCount - 1))
		   //strResult += std::string(m_cSplitChar);
		   strResult.append(1, m_cSplitChar);
    }

    return strResult.c_str();
}
//---------------------------------------------------------------------------

