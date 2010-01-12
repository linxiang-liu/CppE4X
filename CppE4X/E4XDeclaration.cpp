/// 
/// @brief CppE4X Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#include "E4X.h"
#include <cassert>

namespace E4X
{

	const std::string E4XDeclaration::m_pszDeclarationBegin = "<?xml";
	const std::string E4XDeclaration::m_pszDeclarationEnd = "?>";
	const std::string E4XDeclaration::m_pszDeclarationName = "#xml";

	E4XDeclaration::E4XDeclaration(void) : E4XCell( E4X_DECLARATION)
	{
	}

	E4XDeclaration::~E4XDeclaration(void)
	{
	}

	const char* E4XDeclaration::parseImp( const char* xmldata)
	{
		m_strName = m_pszDeclarationName;
		int nBeginSize = m_pszDeclarationBegin.length();
		int nEndSize = m_pszDeclarationEnd.length();
		if( !notEnd( xmldata, nBeginSize + nEndSize))
			return 0;

		const char* pData = xmldata;
		if( memcmp( pData, m_pszDeclarationBegin.c_str(), nBeginSize) != 0)
			return 0;

		pData = skipWhiteSpace( pData + nBeginSize );

		while( pData != 0)
		{
			pData = skipWhiteSpace( pData);
			if( *pData == '?')
			{
				pData = skipWhiteSpace( pData + 1);
				if( *pData == '>')
					return pData + 1;
				else
					return 0;
			}
			else
			{
				E4XCell* pCell = new E4XAttribute;
				appendChild( pCell);
				pData = pCell->parseImp( pData);
			}
		}
		return 0;
	}

	std::string& E4XDeclaration::toXmlStringInternal( std::string& strXml, int nIndent)
	{
		assert( nIndent <= 1);

		strXml += m_pszDeclarationBegin;

		E4XIterator it( *this, std::string());

		while( it.hasNext())
		{
			it.next().toXmlStringInternal( strXml, (nIndent == -1? nIndent : nIndent + 1));
		}

		strXml += m_pszDeclarationEnd;

		return strXml;
	}

	E4XDeclaration& E4XDeclaration::copy()
	{
		E4XDeclaration* pCell = new E4XDeclaration();
		pCell->m_strName = m_strName;
		for( std::list<E4XCell*>::iterator it= m_lstCell.begin(); it != m_lstCell.end(); it++)
		{
			E4XCell& pSubCell = (*it)->copy();
			pCell->m_lstCell.push_back( &pSubCell);
		}
		return *pCell;
	}

}  // namespace
