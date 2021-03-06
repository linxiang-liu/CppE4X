/// 
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

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
		setValue( strValue);
	}

	E4XText::~E4XText(void)
	{
	}

	const char* E4XText::parseImp( const char* xmldata)
	{
		int nBeginSize = m_pszTextBegin.length();
		int nEndSize = m_pszTextEnd.length();
		if( notEnd( xmldata, nBeginSize + nEndSize) )
		{
			if( memcmp( m_pszTextBegin.c_str(), xmldata, nBeginSize) == 0)
			{
				const char* pEndPos = strstr( xmldata + nBeginSize, m_pszTextEnd.c_str());
				if( pEndPos == 0) return 0;
				m_strValue.assign( xmldata + nBeginSize, pEndPos);
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

		m_strValue.assign( xmldata, pNewPos);
		bool bGet = getRealStringWithoutException( m_strValue, m_strValue.c_str());
		if( !bGet) return 0;

		return pNewPos;
	}

	std::string& E4XText::toXmlStringInternal( std::string& strXml, int /*nIndent*/)
	{
		if( m_bNeedEncode)
		{
			strXml += getXmlString(m_strValue.c_str());
		}
		else
		{
			strXml += m_pszTextBegin;

			strXml += m_strValue;

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

