#pragma once
//#include "E4XCell.h"

namespace E4X
{
	class E4XCell;

	class E4XIterator
	{
	public:
		E4XIterator(const E4XIterator&);
		E4XIterator(E4XCell& cell, const std::string& strName=std::string());
		~E4XIterator(void);

		bool hasNext();
		E4XCell& next();
		void remove();

		int count();
		E4XCell& getCell();

		E4XIterator operator/( const std::string& strName);
		E4XCell& operator/( int index);
		E4XIterator operator[]( const std::string& strName);
		E4XCell& operator[](int nIndex);
		//operator E4XCell&();

		std::string toXmlString();

		// 插入

		// 删除

		// 赋值
		template<typename T> E4XIterator& operator = ( T t)
		{
			getCell() = t;
			return *this;
		}

		// 实现E4XCell的一部分方法
		int toNumber();
		bool toBoolean();
		double toFloat();
		std::string toString();

		std::string getName();
		std::string getValue();


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

