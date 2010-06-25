/// 
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#include "E4X.h"
#include "E4XCharSet.h"
#include <cassert>

namespace E4X
{

	//E4XIterator::E4XIterator():m_pCell( 0),m_nCount( 0),m_pSubCell(0)
	//{
	//	initInternalIterator();
	//}

	E4XIterator::E4XIterator(const E4XIterator &itSrc, bool reset)
		:m_pCell( itSrc.m_pCell),
		m_nCount( itSrc.m_nCount), 
		m_strName( itSrc.m_strName),
		m_pSubCell( itSrc.m_pSubCell)
	{
		if( reset)
		{
			this->reset();
		}
		else
		{
			m_itCurrent = itSrc.m_itCurrent;
			m_itNext = itSrc.m_itNext;
		}
	}

	E4XIterator::E4XIterator(E4XCell& cell, const std::string& strName): m_pCell( &cell), m_nCount( -1), m_strName( strName),m_pSubCell(0)
	{
		reset();
	}

	E4XIterator& E4XIterator::operator=( const E4XIterator& it)
	{
		if( &it != this)
		{
			m_pCell = it.m_pCell;
			m_nCount = it.m_nCount;
			m_strName = it.m_nCount;
			m_pSubCell = it.m_pSubCell;
			m_itCurrent = it.m_itCurrent;
			m_itNext = it.m_itNext;			
		}

		return *this;
	}

	void E4XIterator::reset()
	{
		if( m_pCell == 0) return;

		m_itCurrent = m_pCell->m_lstCell.begin();

		if( m_strName.length() == 0)
		{
			m_itNext = m_itCurrent;
		}
		else
		{
			m_itNext = nearest( m_itCurrent);
		}
	}

	E4XIterator::~E4XIterator(void)
	{
	}

	bool E4XIterator::hasNext()
	{
		if( m_pCell == 0) return false;

		if( m_itNext == m_pCell->m_lstCell.end()) return false;

		return true;
	}


	E4XCell& E4XIterator::next()
	{
		m_itCurrent = m_itNext;

		m_itNext = nearest( ++m_itNext);

		return *(*m_itCurrent);
	}

	std::list< E4XCell*>::iterator E4XIterator::nearest(CELL_LIST::iterator it)
	{
		if( m_strName.length() != 0)
		{
			const char* pchName = m_strName.c_str();
			if( pchName[0] == '@')	// attribute
			{
				const char* strAttribName = pchName + 1;
				while( it != m_pCell->m_lstCell.end())
				{
					if( (*it)->type()==E4X_ATTRIBUTE && (*it)->m_strName == strAttribName)
						break;
					it++;
				}
			}
			else	// element
			{
				while( it != m_pCell->m_lstCell.end())
				{
					// 注意，并没有验证声明在文件中的位置，是否正确。( Declaration应该位于XML最前端)
					if( (*it)->type() == E4X_DECLARATION && (*it)->m_strName == m_strName)
						break;

					if((*it)->type()==E4X_ELEMENT && (*it)->m_strName == m_strName)
						break;
					
					it++;
				}
			}
		}

		return it;
	}

	void E4XIterator::remove()
	{
		E4XIterator it( *this, true);
		while( it.hasNext())
		{
			it.next().removeFromParent();
		}

		m_itCurrent = m_pCell->m_lstCell.end();
		m_itNext = m_pCell->m_lstCell.end();
		return;
	}

	E4XIterator E4XIterator::operator/( const std::string& strName)
	{
		return (*this)[strName];
	}


	E4XCell& E4XIterator::operator/( int index)
	{
		return operator[](index);
	}


	E4XIterator E4XIterator::operator []( const std::string& strName)
	{
		E4XIterator it( *this, true);
		if( it.hasNext())
		{
			E4XCell& cell = it.next();
			return E4XIterator( cell, strName);
		}

		generalASubCell();

		return E4XIterator( *m_pSubCell, strName);
	}

	E4XCell& E4XIterator::operator[](int nIndex)
	{
		E4XIterator itTemp( *this, true);

		int nCurrentIndex = 0;

		while( itTemp.hasNext())
		{
			if( nCurrentIndex == nIndex)
				return itTemp.next();
			itTemp.next();
			nCurrentIndex++;
		}

		if( nCurrentIndex == nIndex)
		{
			generalASubCell();
			return operator[](nIndex);
		}

		throw( E4XException(E4XException::ERROR_OUT_BOUND));
	}

	int E4XIterator::count()
	{
		m_nCount = 0;
		if( m_pCell != 0)
		{
			if( m_strName.length() == 0)
			{
				m_nCount = m_pCell->m_lstCell.size();
				return m_nCount;
			}

			for( CELL_LIST::iterator it = m_pCell->m_lstCell.begin(); it != m_pCell->m_lstCell.end(); it++)
			{
				if( (*it)->m_strName == m_strName)
				{
					m_nCount++;
				}
			}
		}

		return m_nCount;
	}

	E4XCell& E4XIterator::getCell()
	{
		E4XIterator it( *this, true);

		if( it.hasNext())
		{
			return it.next();
		}

		return generalASubCell();
	}

	E4XIterator::operator E4XCell&()
	{
		E4XIterator it( *this, true);

		if( it.hasNext())
		{
			return it.next();
		}

		return generalASubCell();
	}

	E4XCell& E4XIterator::generalASubCell()
	{
		assert( m_pCell != 0);

		//if( m_strName.length() == 0)
		//	E4XIterator(*this);

		const char* pchName = m_strName.c_str();

		if( pchName[0] == '@')
		{
			m_pSubCell = new E4XAttribute( pchName + 1);
		}
		else
		{
			m_pSubCell = new E4XElement( m_strName);
		}

		m_pCell->appendChild( m_pSubCell);
		return *m_pSubCell;
	}

	const std::string E4XIterator::toXmlString()
	{
		std::string strXml;

		E4XIterator it( *this, true);

		while( it.hasNext())
		{
			strXml += it.next().toXmlString();
		}

		return strXml;
	}

	const std::string E4XIterator::toAnsiXmlString()
	{
		return e4x_utf82a( toXmlString());
	}

	int E4XIterator::toNumber()
	{
		return getCell().toNumber();
	}

	long long E4XIterator::toBigNumber()
	{
		return getCell().toBigNumber();
	}

	bool E4XIterator::toBoolean()
	{
		return getCell().toBoolean();
	}

	double E4XIterator::toFloat()
	{
		return getCell().toFloat();
	}

	const std::string E4XIterator::toString()
	{
		return getCell().toString();
	}

	const std::string E4XIterator::getName()
	{
		return getCell().getName();
	}

	const std::string E4XIterator::getValue()
	{
		return getCell().getValue();
	}
}  // namespace


