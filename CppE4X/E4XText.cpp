#include "E4X.h"

namespace E4X
{

	const std::string E4XText::m_pszTextBegin = "<![CDATA[";
	const std::string E4XText::m_pszTextEnd = "]]>";

	E4XText::E4XText(void) : E4XCell( E4X_TEXT), m_bNeedEncode(true)
	{
	}

	E4XText::E4XText(const std::string& strValue) : E4XCell( E4X_TEXT)
	{
		parse( strValue.c_str());
	}

	E4XText::~E4XText(void)
	{
	}

	const char* E4XText::parse( const char* xmldata)
	{
		int nBeginSize = m_pszTextBegin.length();
		int nEndSize = m_pszTextEnd.length();
		if( NotEnd( xmldata, nBeginSize + nEndSize) )
		{
			if( memcmp( m_pszTextBegin.c_str(), xmldata, nBeginSize) == 0)
			{
				const char* pEndPos = strstr( xmldata + nBeginSize, m_pszTextEnd.c_str());
				if( pEndPos == 0) return 0;
				std::copy( xmldata + nBeginSize, pEndPos, std::back_inserter(m_strValue));
				m_bNeedEncode = false;
				return pEndPos + nEndSize;;
			}
		}

		const char* pNewPos = xmldata;
		while( *pNewPos != 0)
		{
			if( *pNewPos == '<')
			{
				break;
			}
			pNewPos++;
		}

		if( *pNewPos == 0) return 0;

		m_strValue.reserve( pNewPos - xmldata);
		std::copy( xmldata, pNewPos, std::back_inserter(m_strValue));
		m_strValue = getRealString(m_strValue.c_str());

		return pNewPos;
	}

	std::string& E4XText::toXmlStringInternal( std::string& strXml, int /*nIndent*/)
	{
		if( m_bNeedEncode)
		{
			strXml += getXmlString(getValue().c_str());
		}
		else
		{
			strXml += m_pszTextBegin;

			strXml += getValue();

			strXml += m_pszTextEnd;
		}

		return strXml;
	}

	E4XText& E4XText::copy()
	{
		E4XText* pCell = new E4XText;
		pCell->m_strValue = m_strValue;
		pCell->m_bNeedEncode = m_bNeedEncode;	
		return *pCell;
	}

}  // namespace

