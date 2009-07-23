#pragma once
//#include "E4XCell.h"

namespace E4X
{
	class E4XCell;

	class E4XIterator
	{
	public:
		E4XIterator(const E4XIterator&);
		E4XIterator(E4XCell& cell, const std::string& strName);
		~E4XIterator(void);

		bool hasNext();
		E4XCell& next();
		void remove();

		int count();

		E4XIterator operator/( const std::string& strName);
		E4XIterator operator[]( const std::string& strName);
		E4XCell& operator[](int nIndex);
		operator E4XCell&();

		std::string toXmlString();

		// ¸³Öµ
		template<typename T> E4XIterator& operator = ( T t)
		{
			getCell() = t;
			return *this;
		}
		//E4XIterator& operator = ( const std::string& strName);
		//E4XIterator& operator = ( const char* strName);
		//E4XIterator& operator = ( bool bFlag);
		//E4XIterator& operator = ( int nNumber);

		E4XCell& getCell();

	private:
		E4XIterator();
		void initInternalIterator();
		E4XCell& generalASubCell();

		std::list< E4XCell*>::iterator nearest(std::list< E4XCell*>::iterator it);

	private:
		E4XCell* m_pCell;
		E4XCell* m_pSubCell;
		int m_nCount;
		/*const*/ std::string m_strName;
		std::list< E4XCell*>::iterator m_itCurrent;
		std::list< E4XCell*>::iterator m_itNext;
	};

}  // namespace

