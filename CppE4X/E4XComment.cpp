/// 
/// @brief CppE4X Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#include "E4X.h"

namespace E4X
{

	const std::string E4XComment::m_pszCommentBegin = "<!--";
	const std::string E4XComment::m_pszCommentEnd = "-->";

	E4XComment::E4XComment(void): E4XCell( E4X_COMMENT)
	{
	}

	E4XComment::E4XComment(const std::string& strValue) : E4XCell( E4X_COMMENT)
	{
		m_strValue = strValue;
	}

	E4XComment::~E4XComment(void)
	{
	}

	const char* E4XComment::parse( const char* xmldata)
	{
		int nBeginSize = m_pszCommentBegin.length();
		int nEndSize = m_pszCommentEnd.length();
		if( !notEnd( xmldata, nBeginSize + nEndSize))	//  not enough size
			return 0;

		if(	memcmp( xmldata, m_pszCommentBegin.c_str(), nBeginSize) != 0)
			return 0;

		const char* pStartPos = xmldata + nBeginSize;

		const char* pEndPos = strstr( pStartPos, m_pszCommentEnd.c_str());
		if( pEndPos == 0) return 0;

		m_strValue.reserve( pEndPos - pStartPos);
		std::copy( pStartPos, pEndPos, std::back_inserter( m_strValue));
		bool bGet = getRealStringWithoutException( m_strValue, m_strValue.c_str());
		if( !bGet) return 0;

		return pEndPos + nEndSize;
	}

	std::string& E4XComment::toXmlStringInternal( std::string& strXml, int /*nIndent*/)
	{
		//int nSubIndent = (nIndent == -1? nIndent : (nIndent + 1) );

		//writeIndent( strXml, nIndent);

		strXml += m_pszCommentBegin + m_strValue + m_pszCommentEnd;

		return strXml;
	}

	E4XComment& E4XComment::copy()
	{
		E4XComment* pCell = new E4XComment;
		pCell->m_strValue = m_strValue;
		return *pCell;
	}

}  // namespace
