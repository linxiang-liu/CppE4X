/// @brief E4XCell Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#pragma once


namespace E4X
{
	class E4XIterator;

	/// @class E4XCell
	/// @brief ��Ϊ����E4X�ڵ���Ļ��࣬�ṩ�����Ľӿ������ʵ�֡�

	class E4XCell
	{
	protected:
		friend class E4XIterator;
		
		/// Default Constructor
		/// @param	nType	E4X_TYPE���͡� ÿ����ͬ���͵Ľڵ㣬��Ҫʹ�ò�ͬ��E4X_TYPEֵ����ʼ����
		E4XCell(E4X_TYPE nType);

	public:
		/// Destructor
		virtual ~E4XCell(void);

		/// @brief ȡ�ø��ڵ�ָ��
		/// @retval	���ظ��ڵ�ָ��
		/// @retval 0: �����ڸ��ڵ�(�ýڵ��Ѿ��Ƕ��ڵ�)
		E4XCell* parent();

		///	@brief	����xml�ַ���
		/// @param	xmldata	������ַ���
		/// @return	����parse��ɺ��ָ�롣�ɹ�parse�󣬸�ֵ��ָ����δparse�����ݲ��֡� ������0ʱ��parseʧ��
		virtual const char* parse( const char* xmldata) = 0;

		/// @brief ����ansi��ʽ��xml�ַ���.
		/// @param xmldata �����ansi��ʽ�ַ��������ַ�����ϵͳ��ǰʹ�õ�Ĭ�ϱ�����ء�
		/// @return	����parse��ɺ��ָ�롣�ɹ�parse�󣬸�ֵ��ָ����δparse�����ݲ��֡� ������0ʱ��parseʧ��
		const char* parseAnsi(const char* xmldata);

		/// @brief ���л���xml�ַ���
		/// @param strXml	������ַ������á����л��ĺ���ַ��������ӵ��ô��С�
		/// @param nIndent �����ȼ���ÿ������һ��TAB
		/// @return	strXml������
		virtual std::string& toXmlStringInternal( std::string& strXml, int nIndent) = 0;


		/// @brief	��ȡ�ڵ��name
		/// @note	����E4XDocument,������xml�ļ���
		virtual const std::string getName();

		/// @brief ��ȡ�ڵ��value
		/// @note ����E4XElement,�ú��������������E4XText�ڵ������
		virtual const std::string getValue();

		/// @brief	���ýڵ��name
		/// @note	����E4XDocument,�������µ�xml�ļ��������ڱ���XML�ļ���
		virtual void setName(const std::string& name);

		/// @brief	���ýڵ�value
		/// @note	����E4XElement,���޸��������E4XText�ڵ�����ݡ�
		virtual void setValue(const std::string& value);

		/// @brief	clone a E4XCell
		virtual E4XCell& copy() = 0;

		/// @brief	���ٿ�¡������E4XCell����
		virtual void destroy();	


		/// @brief	���ýڵ����л���xml�ַ���, ��ʹ�����������������������д���
		/// @sa	toAnsiXmlString(), toXmlStringInternal() 
		const std::string toXmlString();

		/// @brief ���ýڵ����л���ansi�����xml�ַ�������ʹ�����������������������д���
		const std::string toAnsiXmlString();

		/// @brief ��øýڵ������
		E4X_TYPE type();

		/// @brief ׷���µ��ӽڵ�
		/// @param pCell	�ӽڵ��ָ��
		/// @warning pCell��ʧȥ���������Ȩ���Ժ��ɸ��ڵ��ͷ�����Դ��
		void appendChild( E4XCell* pCell);

		/// @brief	׷���µ��ӽڵ�
		/// @param	cell	�ӽڵ������
		/// @warning cell��ʧȥ���������Ȩ���Ժ��ɸ��ڵ��ͷ�����Դ��
		void appendChild( E4XCell& cell);

		/// @brief	����ǰ�˲����ӽڵ�
		/// @param	pCell	�ӽڵ��ָ��
		/// @warning pCell��ʧȥ���������Ȩ���Ժ��ɸ��ڵ��ͷ�����Դ��
		void prependChild( E4XCell* pCell);

		/// @brief	����ǰ�˲����ӽڵ�
		/// @param	cell	�ӽڵ������
		/// @warning cell��ʧȥ���������Ȩ���Ժ��ɸ��ڵ��ͷ�����Դ��
		void prependChild( E4XCell& cell);

		/// @brief	��ĳ�ڵ������ӽڵ�
		/// @param	exist	Ҫ�����λ�õĽڵ�ָ��
		/// @param	insert	Ҫ����Ľڵ�ָ��
		/// @warning insert��ʧȥ���������Ȩ���Ժ��ɸ��ڵ��ͷ�����Դ��
		void insertChildAfter( E4XCell* exist, E4XCell* insert);

		/// @brief	��ĳ�ڵ������ӽڵ�
		/// @param	exist	Ҫ�����λ�õĽڵ�����
		/// @param	insert	Ҫ����Ľڵ�����
		/// @warning insert��ʧȥ���������Ȩ���Ժ��ɸ��ڵ��ͷ�����Դ��
		void insertChildAfter( E4XCell& exist, E4XCell& insert);

		/// @brief	��ĳ�ڵ�ǰ�����ӽڵ�
		/// @param	exist	Ҫ�����λ�õĽڵ�ָ��
		/// @param	insert	Ҫ����Ľڵ�ָ��
		/// @warning insert��ʧȥ���������Ȩ���Ժ��ɸ��ڵ��ͷ�����Դ��
		void insertChildBefore( E4XCell* exist, E4XCell* insert);

		/// @brief	��ĳ�ڵ�ǰ�����ӽڵ�
		/// @param	exist	Ҫ�����λ�õĽڵ�����
		/// @param	insert	Ҫ����Ľڵ�����
		/// @warning insert��ʧȥ���������Ȩ���Ժ��ɸ��ڵ��ͷ�����Դ��
		void insertChildBefore( E4XCell& exist, E4XCell& insert);

		/// @brief	�Ƴ�ĳ���ӽڵ�
		/// @return	�ɹ�����true�� �����ýڵ㲻����ʱ���ú�������ʧ�ܣ�����false
		bool removeChild( E4XCell* pCell);

		/// @brief �Ƴ����е��ӽڵ�
		void removeAllChild();

		/// @brief	�Ƴ�����Element���Ե��ӽڵ㡣
		void removeAllChildElement();

		/// @brief	�Ӹ��ڵ����Ƴ�
		/// @warning	���øú����󣬽ڵ��������������������Ҫʹ�ã������Ƴ�ǰ������copy()����һ�ݡ�
		void removeFromParent();

		// ���������

		/// @brief	����ĳ�ӽڵ�
		/// @param	strChildName Ҫ���ҵ��ӽڵ����ơ� ��strChileName��'@'��ͷʱ��������E4XAttribute���ͣ��������E4XElement���͡�
		/// @retval	�ҵ����ӽڵ��iterator��
		/// @warning	�������ֵĽڵ㲻����ʱ��������һ��ͬ�����ӽڵ㡣
		///	��strChildName==""ʱ�����ص�iterator������ö���������͵��ӽڵ㡣
		E4XIterator operator/(const std::string& strChildName);

		/// @brief	����ĳ�ӽڵ�
		/// @param	strChildName Ҫ���ҵ��ӽڵ����ơ� ��strChileName��'@'��ͷʱ��������E4XAttribute���ͣ��������E4XElement���͡�
		/// @retval	�ҵ����ӽڵ��iterator��
		/// @warning	�������ֵĽڵ㲻����ʱ��������һ��ͬ�����ӽڵ㡣
		E4XIterator operator[](const std::string& strChildName);
		
		/// @brief	����E4XCell��value
		/// @param	t ���ᱻ���л����ַ����󣬸�ֵ��E4XCell
		template<typename T>
		E4XCell& operator = ( T& t);

		/// @brief  ����E4XCell��ֵ
		/// @param	strValue �ַ���
		E4XCell& operator = ( const char* strValue);

		/// @brief	����E4XCell��ֵ
		E4XCell& operator = ( char* strValue);
		/// @brief	����E4XCell��ֵ
		E4XCell& operator = ( const std::string& strValue);
		/// @brief	����E4XCell��ֵ
		E4XCell& operator = ( std::string& strValue);

		/// @brief	����E4XCell��ֵ
		E4XCell& operator = ( bool bFlag);


		// ����ת��
		
		/// @brief ת��valueΪint����
		int toNumber();

		/// @brief	ת��valueΪlong long����
		long long toBigNumber();

		/// @brief	ת��valueΪbool����
		bool toBoolean();

		/// @brief ת��valueΪfloat����
		double toFloat();

		/// @brief	ת��valueΪstring����
		const std::string toString();

		/// @brief	��ȡ�ӽڵ����
		/// @warning	������ֹ��������ʹ�á� ����ö���ӽڵ㣬��ʹ�� cell[""]��ȡ����
		/// @retval	E4XCell list array
		/// @warning	��ֹ�ú���������ʹ�� [""]+ѭ�� �����
		CELL_LIST& getChildCells();

	protected:
		/// @brief �����ַ����еĿհ��ַ�����\\b, \\t ��
		const char* skipWhiteSpace(const char* pszIn);

		/// @brief �����ַ����ķǿհ׷�
		const char* skipValueChars(const char* pszIn);

		/// @brief ����һ������tab,�������л�E4XCell���ַ�����
		/// @param strXml	����������ַ���
		/// @param	nIndent	�����ȼ�, ���Ϊ5��������5��tab��
		/// @retval	strXml������
		std::string& writeIndent( std::string& strXml, int nIndent);


		/// @brief	����Ƿ񵽴�β��
		///	@param pszBuffer	�������ַ���
		/// @param nMinSize �����ַ�����βǰ��������Ҫ�������ַ���
		/// @retval	true	�����㹻ʣ���ַ���
		///	@retval	false	�ռ䲻�㣬����������Ҫע����ܱ߽������
		bool notEnd(const char* pszBuffer, int nMinSize);

		/// @brief	���Ѿ�ת���XML�ַ��������У���ȡת��ǰ���ַ������ݡ�
		/// @param	src �Ѿ�ת���xml�ַ�����
		/// @retval	ת��ǰ��ԭʼ�ַ������ݡ�
		/// @warning �˺������ܲ���E4XException�쳣
		/// @see	getRealStringWithoutException
		static std::string getRealString(const char* src);

		/// @brief	���Ѿ�ת���XML�ַ��������У���ȡת��ǰ���ַ������ݡ�
		/// @param	out ת���ɹ�ʱ�����ת��ǰ��ԭʼ�ַ������ݡ�
		/// @param	src �Ѿ�ת���xml�ַ�����
		/// @retval	�Ƿ�ɹ����ת����
		/// @see	getRealString
		static bool getRealStringWithoutException(std::string& out, const char* src);

		/// @brief	����ͨ�ַ�����ת���Ϊxml�ַ�����ʽ��
		/// @param	src ԭʼ�ַ������ݡ�
		/// @retval	ת��Ϊxml��ʽ���ַ�����
		static std::string getXmlString(const char* src);

	protected:

		///	cell name
		std::string m_strName;

		/// cell value
		std::string m_strValue;

		/// list of subcell pointer
		CELL_LIST m_lstCell;

		/// type
		E4X_TYPE m_nType;

		/// parent node
		E4XCell* m_pParent;

	private:
		/// @brief	��ֹ�� �������캯��
		/// @warning	����Ҫ������ʱ����ʹ��copy����
		E4XCell& operator = ( const E4XCell& cell);
		//E4XCell& operator = ( E4XCell& cell);

	};

}  // namespace

