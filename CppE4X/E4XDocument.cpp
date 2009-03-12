#include "E4X.h"

#ifdef WIN32
#define LIN_CHAR_SET_USE_STL
#include "LinCharSet.h"
#endif

namespace E4X
{

	E4XDocument::E4XDocument(void) : E4XCell( E4X_DOCUMENT)
	{
	}

	E4XDocument::E4XDocument(const std::string& strName) : E4XCell( E4X_DOCUMENT)
	{
		m_strName = strName;
	}

	E4XDocument::~E4XDocument(void)
	{
	}

	const char* E4XDocument::parse( const char* xmldata)
	{
		bool bDeclare = false;
		bool bElement = false;
		const char* pNewPos = xmldata;

		while( pNewPos != 0)
		{
			
			pNewPos = skipWhiteSpace( pNewPos);
			if( pNewPos == 0) return 0;

			if( *pNewPos=='<')
			{
				//const char* pTemp = skipWhiteSpace( pNewPos + 1);
				const char* pTemp = pNewPos + 1;
				if( *pTemp == 0) return false;
				if( pTemp[0] == '?') // declaration
				{
					if( bDeclare) return 0;
					if( bElement) return 0;		// do NOT move this line
					bDeclare = true;
					E4XDeclaration* pCell = new E4XDeclaration;
					appendChild( pCell);
					pNewPos = pCell->parse( pNewPos);
					if( pNewPos == 0) return 0;
					continue;
				}
				else	// element	comment	// __TODO__ only need loop here
				{
					if( pTemp[0] == '!')
					{
						E4XComment* pCell = new E4XComment;
						appendChild( pCell);
						pNewPos = pCell->parse( pNewPos);
						if( pNewPos == 0) return 0;
					}
					else
					{
						bElement = true;
						E4XElement* pCell = new E4XElement;
						appendChild( pCell);
						pNewPos = pCell->parse( pNewPos);
						if( pNewPos == 0) return 0;
						break;
					}
				}
			}
			else
			{
				// error
				return 0;
			}
		}

		return pNewPos;
	}

	bool E4XDocument::loadFile( const char* xmlfile)
	{
		m_strName = xmlfile;
		std::ifstream file( xmlfile, std::ios::in);
		if( !file) return false;
		std::istreambuf_iterator<char> iter(file);
		std::string readString( iter, (std::istreambuf_iterator<char>()));

		bool has_utf8_mark = false;
		if( readString.length()>=3)
		{
			const unsigned char* begin = reinterpret_cast<const unsigned char*>( readString.c_str());
			if( begin[0]==0xEF && begin[1]==0xBB && begin[2]==0xBF )
				has_utf8_mark = true;
		}

#ifdef WIN32
		USE_LIN_CHAR_SET;
		readString = utf82a( has_utf8_mark? readString.c_str()+3 : readString.c_str());
		has_utf8_mark = false;
#endif
		bool bSuccess = parse( has_utf8_mark? readString.c_str()+3 : readString.c_str())!=0;
		if( !bSuccess)
		{
			removeAllChild();
		}
		return bSuccess;
	}

	std::string& E4XDocument::toXmlStringInternal( std::string& strXml, int nIndent)
	{
		int nSubIndent = (nIndent == -1? nIndent :  0);

		E4XIterator it( *this, std::string());

		while( it.hasNext())
		{
			it.next().toXmlStringInternal( strXml, nSubIndent);
			writeIndent(strXml, nSubIndent);
		}

		return strXml;
	}

	bool E4XDocument::saveFile(const char* xmlfile)
	{
		if( xmlfile == 0)
		{
			assert( m_strName.length() != 0);
			if( m_strName.length() == 0) return false;
			xmlfile = m_strName.c_str();
		}

		std::ofstream file( xmlfile, std::ios::out);

		std::string strXmlString;
		toXmlStringInternal( strXmlString, 0);

#ifdef WIN32		
		USE_LIN_CHAR_SET;

		strXmlString = a2utf8( strXmlString);
#endif
		file << strXmlString;

		return false;
	}

	E4XDocument& E4XDocument::copy()
	{
		E4XDocument* pCell = new E4XDocument;
		for( std::list<E4XCell*>::iterator it= m_lstCell.begin(); it != m_lstCell.end(); it++)
		{
			E4XCell& pSubCell = (*it)->copy();
			pCell->m_lstCell.push_back( &pSubCell);
		}
		return *pCell;
	}

}  // namespace

