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
		operator E4XCell&();

		const std::string toXmlString();
		const std::string toAnsiXmlString();

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
		long long toBigNumber();
		bool toBoolean();
		double toFloat();
		const std::string toString();

		const std::string getName();
		const std::string getValue();


	private:
		E4XIterator();
		void initInternalIterator();
		E4XCell& generalASubCell();

		CELL_LIST::iterator nearest(CELL_LIST::iterator it);

	private:
		E4XCell* m_pCell;
		E4XCell* m_pSubCell;
		int m_nCount;
		/*const*/ std::string m_strName;
		CELL_LIST::iterator m_itCurrent;
		CELL_LIST::iterator m_itNext;
	};

}  // namespace

