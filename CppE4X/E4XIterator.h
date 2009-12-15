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
		/// @param	cell	������Cell���ӽڵ������
		/// @param strName	�õ�������Ҫ�Ĳ�ѯ��������strNameΪĬ�ϲ���ʱ������ĵ�����������ö�������ӽڵ㡣
		///					��strName���ʿ�ʱ����strName��'@'Ϊ��ʱ��������attribute node,��������element node
		E4XIterator(E4XCell& cell, const std::string& strName=std::string());

		/// destructor
		~E4XIterator(void);

		/// �Ƿ�����һ������Ҫ��Ľڵ㡣
		/// @note	�ú��������ƶ�������
		bool hasNext();

		/// ������һ������Ҫ��Ľڵ㡣
		/// ���������ƶ�ָ����һ���ڵ㡣
		E4XCell& next();

		/// �Ƴ��õ�����ָ��Ľڵ㡣
		/// ��������ָ����һ���ڵ㡣
		void remove();

		///	���ط��������Ľڵ�����
		int count();

		/// ���ص�����ָ���E4XCell����
		E4XCell& getCell();


		/// ������һ���ӽڵ�
		/// @param strName	���ӽڵ�Ľڵ���
		/// @retval	���ӽڵ�ĵ�����
		/// @warning	���ӽڵ㲻����ʱ���������Ϊ��ǰ�����ż�һ�������ɸýڵ㡣���򣬽��׳�ERROR_OUT_BOUND�쳣
		E4XIterator operator/( const std::string& strName);
		
		/// ������һ���ڵ�(�����ӽڵ�)��
		/// @param index	���ӽڵ�����
		/// @retval	���ӽڵ�ĵ�����
		/// @warning	���ӽڵ㲻����ʱ���������Ϊ��ǰ�����ż�һ�������ɸýڵ㡣���򣬽��׳�ERROR_OUT_BOUND�쳣
		E4XCell& operator/( int index);

		/// ������һ���ӽڵ�
		/// @param strName	���ӽڵ�Ľڵ���
		/// @retval	���ӽڵ�ĵ�����
		/// @warning	���ӽڵ㲻����ʱ���������Ϊ��ǰ�����ż�һ�������ɸýڵ㡣���򣬽��׳�ERROR_OUT_BOUND�쳣
		E4XIterator operator[]( const std::string& strName);

		/// ������һ���ڵ�(�����ӽڵ�)��
		/// @param nIndex	���ӽڵ�����
		/// @retval	���ӽڵ�ĵ�����
		/// @warning	���ӽڵ㲻����ʱ���������Ϊ��ǰ�����ż�һ�������ɸýڵ㡣���򣬽��׳�ERROR_OUT_BOUND�쳣
		E4XCell& operator[](int nIndex);


		/// ���صĲ��������������E4XCell����
		operator E4XCell&();

		/// ����xml�ַ���
		/// ���һ��E4XIteratorָ�������������Ľڵ㣬���������ڵ��xml����
		/// @retval ���ؽڵ��xml�ַ���
		const std::string toXmlString();

		/// ����ansi�����xml�ַ���
		/// @see toXmlString()
		const std::string toAnsiXmlString();

		// ����

		// ɾ��

		// ��ֵ
		/// ģ�帳ֵ����
		///	@param t �������
		template<typename T> E4XIterator& operator = ( T t);

		// ʵ��E4XCell��һ���ַ���
		/// ��E4XIteratorָ���E4XCell��ֵ��ת��Ϊint����
		int toNumber();
		/// ��E4XIteratorָ���E4XCell��ֵ��ת��Ϊlong long����
		long long toBigNumber();
		/// ��E4XIteratorָ���E4XCell��ֵ��ת��Ϊbool����
		bool toBoolean();
		/// ��E4XIteratorָ���E4XCell��ֵ��ת��Ϊdouble����
		double toFloat();
		/// ��E4XIteratorָ���E4XCell��ֵ��ת��Ϊstring����
		const std::string toString();

		/// ����ָ���E4XCell������(name)
		const std::string getName();
		/// ����ָ���E4XCell��value
		const std::string getValue();


	private:
		/// Default constructor
		/// @note ���ṩ
		E4XIterator();

		///	��ʼ��E4XIterator
		void initInternalIterator();

		/// ����һ���ӽڵ�
		/// @retval	�ӽڵ������
		E4XCell& generalASubCell();

		/// �����һ������������ �ڵ�ָ�� ������
		/// @retval �ڵ�ָ���������
		CELL_LIST::iterator nearest(CELL_LIST::iterator it);

	private:

		/// ָ��Ľڵ�
		E4XCell* m_pCell;

		/// ָ����ӽڵ�
		E4XCell* m_pSubCell;

		/// �ڵ����
		int m_nCount;

		/// �ڵ�����
		/*const*/ std::string m_strName;

		/// ��ǰ �ڵ�ָ�� ������
		CELL_LIST::iterator m_itCurrent;

		/// ��һ�� �ڵ�ָ�� �� ������
		CELL_LIST::iterator m_itNext;
	};

}  // namespace

