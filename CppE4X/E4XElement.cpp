/// 
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#include "E4X.h"
#include <cassert>

namespace E4X
{

	E4XElement::E4XElement(void) : E4XCell( E4X_ELEMENT)
	{
	}

	E4XElement::E4XElement(const std::string& strName) : E4XCell( E4X_ELEMENT)
	{
		m_strName = strName;
	}

	E4XElement::~E4XElement(void)
	{
	}

	const char* E4XElement::parseImp( const char* xmldata)
	{
		if( xmldata==0 || *xmldata == 0)
		{
			return 0;
		}

		bool bLeft = false;
		assert( *xmldata == '<');
		const char* pNewPos = skipWhiteSpace( xmldata + 1);
		if ( pNewPos == 0) return 0;
		const char* pName = skipValueChars( pNewPos);
		if( pName == 0) return 0;

		m_strName.assign( pNewPos, pName);

		pNewPos = pName;
		while( pNewPos != 0)
		{
			pNewPos = skipWhiteSpace( pNewPos);
			if( pNewPos == 0) return 0;

			if( *pNewPos == '/')
			{
				//pNewPos = skipWhiteSpace( pNewPos + 1);
				//if( pNewPos == 0) return 0;
				if( *(pNewPos+1) == '>')
					return pNewPos + 2;
				else
					return 0;
			}
			else
			{
				if( *pNewPos == '>')
				{
					if( bLeft) return 0;
					bLeft = true;
					pNewPos++;
					continue;
				}
				else
				{
					if( bLeft)
					{
						pNewPos = skipWhiteSpace( pNewPos);
						if( pNewPos == 0) return 0;

						if( *pNewPos == '<')
						{
							const char* pNew = pNewPos;
							pNewPos = skipWhiteSpace( pNewPos + 1);
							if( pNewPos == 0) return 0;
							if( *pNewPos == '/')
							{
								if( !bLeft) return 0;		// __TODO__		no need?
								pNewPos = skipWhiteSpace( pNewPos + 1);
								if( pNewPos == 0) return 0;

								const char* pTemp = skipValueChars( pNewPos);
								if( memcmp( pNewPos, m_strName.c_str(), pTemp - pNewPos) != 0)
									return 0;

								pNewPos = skipWhiteSpace( pTemp);
								if( pNewPos == 0) return 0;
								if( *pNewPos == '>')
									return pNewPos + 1;
							}
							else
							{
								if( *pNewPos == '!')
								{
									int nCommentBeginSize = E4XComment::m_pszCommentBegin.length();
									int nTextBeginSize = E4XText::m_pszTextBegin.length();

									const char* pTemp = pNewPos;
									if( !notEnd( pTemp, nCommentBeginSize)) return 0;

									if( memcmp( pNewPos-1, E4XComment::m_pszCommentBegin.c_str(), nCommentBeginSize) == 0)
									{

										E4XCell* pCell = new E4XComment;
										appendChild( pCell);
										pNewPos = pCell->parseImp( pNew);
										if( pNewPos == 0) return 0;
									}
									else
									{
										if( !notEnd( pTemp, nTextBeginSize)) return 0;
										if( memcmp( pNewPos-1, E4XText::m_pszTextBegin.c_str(), nTextBeginSize) == 0)
										{
											E4XCell* pCell = new E4XText;
											appendChild( pCell);
											pNewPos = pCell->parseImp( pNew);
											if( pNewPos == 0) return 0;
										}
										else
											return 0;
									}
								}
								else
								{
									E4XCell* pCell = new E4XElement;
									appendChild( pCell);
									pNewPos = pCell->parseImp( pNew);
									if( pNewPos == 0) return 0;
								}
							}
							continue;
						}
						else
						{
							E4XCell* pCell = new E4XText;
							appendChild( pCell);
							pNewPos = pCell->parseImp( pNewPos);
							if( pNewPos == 0) return 0;
							continue;
						}
					}
					else
					{
						E4XCell* pCell = new E4XAttribute;
						appendChild( pCell);
						pNewPos = pCell->parseImp( pNewPos);
						if( pNewPos == 0) return 0;
					}
				}
			}
		}

		return 0;
	}

	std::string& E4XElement::toXmlStringInternal( std::string& strXml, int nIndent)
	{
		strXml += ("<" + m_strName);
		int nSubIndent = (nIndent == -1? nIndent : (nIndent + 1) );

		CELL_LIST::iterator it;
		int nAttribCount = 0;

		E4XIterator itAttribute( *this, std::string());
		while( itAttribute.hasNext())
		{
			E4XCell& cell = itAttribute.next();
			if( cell.type() == E4X_ATTRIBUTE)
			{
				nAttribCount++;
				cell.toXmlStringInternal( strXml, nSubIndent);
			}
		}

		if( nAttribCount == itAttribute.count() )
		{
			strXml += "/>";
		}
		else
		{
			strXml += ">";
			bool bNeedIndent = false;
			E4XIterator it2( *this, std::string());
			while( it2.hasNext())
			{
				E4XCell& cell = it2.next();
				if( cell.type() != E4X_ATTRIBUTE)
				{
					if( cell.type() == E4X_TEXT)
					{
						bNeedIndent = false;
					}
					else
					{
						bNeedIndent = true;
						writeIndent(strXml, nSubIndent);
					}

					cell.toXmlStringInternal( strXml, nSubIndent);
				}
			}

			if( bNeedIndent)
				writeIndent( strXml, nIndent);
			strXml += "</" + m_strName + ">";
		}

		return strXml;
	}


	void E4XElement::setValue(const std::string& value)
	{
		E4XIterator it(*this, std::string());
		while( it.hasNext())
		{
			if( it.next().type() == E4X_TEXT)
				it.remove();
		}

		E4XText* pCell = new E4XText(value);
		appendChild( pCell);
		m_strValue = value;
	}


	const std::string E4XElement::getValue()
	{
		m_strValue.clear();
		E4XIterator it(*this, std::string());

		while( it.hasNext())
		{
			E4XCell& cell = it.next();
			if( cell.type() == E4X_TEXT) m_strValue += cell.getValue();
		}

		return m_strValue;
	}

	E4XElement& E4XElement::operator = ( const std::string& strName)
	{
		if( m_strName.length() == 0)
		{
			parse( strName.c_str());
		}
		else
		{
			m_strName = strName;
		}
		return *this;
	}

	E4XElement& E4XElement::copy()
	{
		E4XElement* pCell = new E4XElement;
		pCell->m_strName = m_strName;
		for( std::list<E4XCell*>::iterator it= m_lstCell.begin(); it != m_lstCell.end(); it++)
		{
			E4XCell& pSubCell = (*it)->copy();
			pCell->m_lstCell.push_back( &pSubCell);
		}
		return *pCell;
	}


}  // namespace


