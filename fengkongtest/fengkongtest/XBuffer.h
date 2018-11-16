//---------------------------------------------------------------------------
#ifndef XBuffer_H
#define XBuffer_H

#include <string>
#include <vector>


#pragma pack(push, 1)

class XBuffer
{
protected:
    char * m_szBuffer;
    int m_iBufLen;

    std::vector<std::string> m_pvItems;

    char m_cSplitChar;

    bool Process();
public:
    XBuffer();
    ~XBuffer();

    int GetItemCount();

    char GetSplitChar() {return m_cSplitChar;};
    void SetSplitChar(char cSplitChar) {m_cSplitChar = cSplitChar;};

    void Clear();

    bool Set(const char * szBuffer, int iLen);
    bool Set(const char * szFormat, ...);
    bool Set(std::string str);

    const char * GetItem(int iItem);
    const char * GetItem(int iItem, char * szBuffer, int iMaxLen);
	const char * GetItem(int iItem, std::string & strBuffer);
    const char * toString(void);
};

#pragma pack(pop)

#endif
