/// 
/// @brief CppE4X Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#include "E4X.h"

namespace E4X
{
	E4XAttribute::E4XAttribute(void)  : E4XCell( E4X_ATTRIBUTE), m_chSeparator('\"')
	{
	}

	E4XAttribute::E4XAttribute(const std::string& strName) : E4XCell( E4X_ATTRIBUTE), m_chSeparator('\"')
	{
		m_strName = strName;
	}

	E4XAttribute::~E4XAttribute(void)
	{
	}

	const char* E4XAttribute::parseImp( const char* xmldata)
	{
		removeAllChild();
		const char* pNewPos = skipValueChars( xmldata);
		if( pNewPos == 0) return 0;

		m_chSeparator = '\"';

		m_strName.assign( xmldata, pNewPos);

		pNewPos = skipWhiteSpace( pNewPos);
		if( pNewPos == 0) return 0;
		if( *pNewPos != '=') return 0;

		pNewPos++;
		pNewPos = skipWhiteSpace( pNewPos);
		if( pNewPos == 0) return 0;
		if( *pNewPos!='\"' && *pNewPos!='\'' ) return 0;
		m_chSeparator = *pNewPos;

		const char* pValue = pNewPos;
		do
		{
			const char* pTemp = pNewPos + 1;
			pNewPos = skipValueChars( pTemp);
		}
		while( *pNewPos !=0 && *pNewPos != m_chSeparator);

		if( pNewPos == 0) return 0;
		if( *pNewPos!=m_chSeparator ) return 0;

		m_strValue.assign( pValue+1, pNewPos);
		bool bGet = getRealStringWithoutException( m_strValue, m_strValue.c_str());
		if( !bGet) return 0;

		return ++pNewPos;
	}

	std::string& E4XAttribute::toXmlStringInternal( std::string& strXml, int /*nIndent*/)
	{
		strXml +=( " " + m_strName + "=" + m_chSeparator +  getXmlString(m_strValue.c_str()) + m_chSeparator);
		return strXml;
	}

	E4XAttribute& E4XAttribute::copy()
	{
		E4XAttribute* pCell = new E4XAttribute();
		pCell->m_strName = m_strName;
		pCell->m_strValue = m_strValue;
		pCell->m_chSeparator = m_chSeparator;
		return *pCell;
	}

}  // namespace
