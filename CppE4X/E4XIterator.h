/// @brief E4XIterator Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#pragma once
//#include "E4XCell.h"

namespace E4X
{
	class E4XCell;


	/// xml iterator
	class E4XIterator
	{
	public:
		///	copy constructor
		E4XIterator(const E4XIterator& itSrc);

		/// constructor from E4XCell
		/// @param	cell	构建该Cell的子节点迭代期
		/// @param strName	该迭代器需要的查询参数。当strName为默认参数时，构造的迭代器可用于枚举所有子节点。
		///					当strName不问空时，若strName以'@'为首时，将搜索attribute node,否则，搜索element node
		E4XIterator(E4XCell& cell, const std::string& strName=std::string());

		/// destructor
		~E4XIterator(void);

		/// 是否还有下一个符合要求的节点。
		/// @note	该函数并不移动迭代器
		bool hasNext();

		/// 返回下一个符合要求的节点。
		/// 迭代器将移动指向下一个节点。
		E4XCell& next();

		/// 移除该迭代器指向的节点。
		/// 迭代器将指向下一个节点。
		void remove();

		///	返回符合条件的节点总数
		int count();

		/// 返回迭代器指向的E4XCell引用
		E4XCell& getCell();


		/// 查找下一个子节点
		/// @param strName	该子节点的节点名
		/// @retval	该子节点的迭代期
		/// @warning	当子节点不存在时，如果正好为当前最大序号加一，将生成该节点。否则，将抛出ERROR_OUT_BOUND异常
		E4XIterator operator/( const std::string& strName);
		
		/// 查找下一个节点(并非子节点)。
		/// @param index	该子节点的序号
		/// @retval	该子节点的迭代期
		/// @warning	当子节点不存在时，如果正好为当前最大序号加一，将生成该节点。否则，将抛出ERROR_OUT_BOUND异常
		E4XCell& operator/( int index);

		/// 查找下一个子节点
		/// @param strName	该子节点的节点名
		/// @retval	该子节点的迭代期
		/// @warning	当子节点不存在时，如果正好为当前最大序号加一，将生成该节点。否则，将抛出ERROR_OUT_BOUND异常
		E4XIterator operator[]( const std::string& strName);

		/// 查找下一个节点(并非子节点)。
		/// @param nIndex	该子节点的序号
		/// @retval	该子节点的迭代期
		/// @warning	当子节点不存在时，如果正好为当前最大序号加一，将生成该节点。否则，将抛出ERROR_OUT_BOUND异常
		E4XCell& operator[](int nIndex);


		/// 重载的操作运算符，返回E4XCell引用
		operator E4XCell&();

		/// 返回xml字符串
		/// 如果一个E4XIterator指向多个符合条件的节点，则将输出多个节点的xml集合
		/// @retval 返回节点的xml字符串
		const std::string toXmlString();

		/// 返回ansi编码的xml字符串
		/// @see toXmlString()
		const std::string toAnsiXmlString();

		// 插入

		// 删除

		// 赋值
		/// 模板赋值函数
		///	@param t 输入参数
		template<typename T> E4XIterator& operator = ( T t);

		// 实现E4XCell的一部分方法
		/// 将E4XIterator指向的E4XCell的值，转换为int类型
		int toNumber();
		/// 将E4XIterator指向的E4XCell的值，转换为long long类型
		long long toBigNumber();
		/// 将E4XIterator指向的E4XCell的值，转换为bool类型
		bool toBoolean();
		/// 将E4XIterator指向的E4XCell的值，转换为double类型
		double toFloat();
		/// 将E4XIterator指向的E4XCell的值，转换为string类型
		const std::string toString();

		/// 返回指向的E4XCell的名称(name)
		const std::string getName();
		/// 返回指向的E4XCell的value
		const std::string getValue();


	private:
		/// Default constructor
		/// @note 不提供
		E4XIterator();

		///	初始化E4XIterator
		void initInternalIterator();

		/// 生成一个子节点
		/// @retval	子节点的引用
		E4XCell& generalASubCell();

		/// 获得下一个符合条件的 节点指针 迭代器
		/// @retval 节点指针迭代器。
		CELL_LIST::iterator nearest(CELL_LIST::iterator it);

	private:

		/// 指向的节点
		E4XCell* m_pCell;

		/// 指向的子节点
		E4XCell* m_pSubCell;

		/// 节点个数
		int m_nCount;

		/// 节点名称
		/*const*/ std::string m_strName;

		/// 当前 节点指针 迭代器
		CELL_LIST::iterator m_itCurrent;

		/// 下一个 节点指针 的 迭代器
		CELL_LIST::iterator m_itNext;
	};

}  // namespace

