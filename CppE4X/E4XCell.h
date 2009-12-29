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
	/// @brief 做为其他E4X节点类的基类，提供公共的接口与操作实现。

	class E4XCell
	{
	protected:
		friend class E4XIterator;
		
		/// Default Constructor
		/// @param	nType	E4X_TYPE类型。 每个不同类型的节点，需要使用不同的E4X_TYPE值来初始化。
		E4XCell(E4X_TYPE nType);

	public:
		/// Destructor
		virtual ~E4XCell(void);

		/// @brief 取得父节点指针
		/// @retval	返回父节点指针
		/// @retval 0: 不存在父节点(该节点已经是顶节点)
		E4XCell* parent();

		///	@brief	解析xml字符串
		/// @param	xmldata	传入的字符串
		/// @return	返回parse完成后的指针。成功parse后，该值将指向尚未parse的数据部分。 当返回0时，parse失败
		virtual const char* parse( const char* xmldata) = 0;

		/// @brief 解析ansi格式的xml字符串.
		/// @param xmldata 传入的ansi格式字符串，该字符串与系统当前使用的默认编码相关。
		/// @return	返回parse完成后的指针。成功parse后，该值将指向尚未parse的数据部分。 当返回0时，parse失败
		const char* parseAnsi(const char* xmldata);

		/// @brief 序列化到xml字符串
		/// @param strXml	输入的字符串引用。序列化的后的字符串将附加到该串中。
		/// @param nIndent 缩进等级。每次缩进一个TAB
		/// @return	strXml的引用
		virtual std::string& toXmlStringInternal( std::string& strXml, int nIndent) = 0;


		/// @brief	获取节点的name
		/// @note	对于E4XDocument,将返回xml文件名
		virtual const std::string getName();

		/// @brief 获取节点的value
		/// @note 对于E4XElement,该函数返回其包含的E4XText节点的内容
		virtual const std::string getValue();

		/// @brief	设置节点的name
		/// @note	对于E4XDocument,将设置新的xml文件名。用于保存XML文件。
		virtual void setName(const std::string& name);

		/// @brief	设置节点value
		/// @note	对于E4XElement,将修改其包含的E4XText节点的内容。
		virtual void setValue(const std::string& value);

		/// @brief	clone a E4XCell
		virtual E4XCell& copy() = 0;

		/// @brief	销毁克隆产生的E4XCell对象
		virtual void destroy();	


		/// @brief	将该节点序列化到xml字符串, 不使用缩进符，以利于在网络中传播
		/// @sa	toAnsiXmlString(), toXmlStringInternal() 
		const std::string toXmlString();

		/// @brief 将该节点序列化到ansi编码的xml字符串。不使用缩进符，以利于在网络中传播
		const std::string toAnsiXmlString();

		/// @brief 获得该节点的类型
		E4X_TYPE type();

		/// @brief 追加新的子节点
		/// @param pCell	子节点的指针
		/// @warning pCell将失去自身的所有权，以后将由父节点释放其资源。
		void appendChild( E4XCell* pCell);

		/// @brief	追加新的子节点
		/// @param	cell	子节点的引用
		/// @warning cell将失去自身的所有权，以后将由父节点释放其资源。
		void appendChild( E4XCell& cell);

		/// @brief	在最前端插入子节点
		/// @param	pCell	子节点的指针
		/// @warning pCell将失去自身的所有权，以后将由父节点释放其资源。
		void prependChild( E4XCell* pCell);

		/// @brief	在最前端插入子节点
		/// @param	cell	子节点的引用
		/// @warning cell将失去自身的所有权，以后将由父节点释放其资源。
		void prependChild( E4XCell& cell);

		/// @brief	在某节点后插入子节点
		/// @param	exist	要插入的位置的节点指针
		/// @param	insert	要插入的节点指针
		/// @warning insert将失去自身的所有权，以后将由父节点释放其资源。
		void insertChildAfter( E4XCell* exist, E4XCell* insert);

		/// @brief	在某节点后插入子节点
		/// @param	exist	要插入的位置的节点引用
		/// @param	insert	要插入的节点引用
		/// @warning insert将失去自身的所有权，以后将由父节点释放其资源。
		void insertChildAfter( E4XCell& exist, E4XCell& insert);

		/// @brief	在某节点前插入子节点
		/// @param	exist	要插入的位置的节点指针
		/// @param	insert	要插入的节点指针
		/// @warning insert将失去自身的所有权，以后将由父节点释放其资源。
		void insertChildBefore( E4XCell* exist, E4XCell* insert);

		/// @brief	在某节点前插入子节点
		/// @param	exist	要插入的位置的节点引用
		/// @param	insert	要插入的节点引用
		/// @warning insert将失去自身的所有权，以后将由父节点释放其资源。
		void insertChildBefore( E4XCell& exist, E4XCell& insert);

		/// @brief	移除某个子节点
		/// @return	成功返回true， 仅当该节点不存在时，该函数运行失败，返回false
		bool removeChild( E4XCell* pCell);

		/// @brief 移除所有的子节点
		void removeAllChild();

		/// @brief	移除所有Element属性的子节点。
		void removeAllChildElement();

		/// @brief	从父节点中移除
		/// @warning	调用该函数后，节点自身将被析构。如果还需要使用，请在移除前，调用copy()复制一份。
		void removeFromParent();

		// 运算符重载

		/// @brief	查找某子节点
		/// @param	strChildName 要查找的子节点名称。 当strChileName以'@'开头时，将查找E4XAttribute类型，否则查找E4XElement类型。
		/// @retval	找到的子节点的iterator。
		/// @warning	当该名字的节点不存在时，将创建一个同名的子节点。
		///	当strChildName==""时，返回的iterator可用于枚举所有类型的子节点。
		E4XIterator operator/(const std::string& strChildName);

		/// @brief	查找某子节点
		/// @param	strChildName 要查找的子节点名称。 当strChileName以'@'开头时，将查找E4XAttribute类型，否则查找E4XElement类型。
		/// @retval	找到的子节点的iterator。
		/// @warning	当该名字的节点不存在时，将创建一个同名的子节点。
		E4XIterator operator[](const std::string& strChildName);
		
		/// @brief	设置E4XCell的value
		/// @param	t 将会被序列化到字符串后，赋值给E4XCell
		template<typename T>
		E4XCell& operator = ( T& t);

		/// @brief  设置E4XCell的值
		/// @param	strValue 字符串
		E4XCell& operator = ( const char* strValue);

		/// @brief	设置E4XCell的值
		E4XCell& operator = ( char* strValue);
		/// @brief	设置E4XCell的值
		E4XCell& operator = ( const std::string& strValue);
		/// @brief	设置E4XCell的值
		E4XCell& operator = ( std::string& strValue);

		/// @brief	设置E4XCell的值
		E4XCell& operator = ( bool bFlag);


		// 类型转换
		
		/// @brief 转换value为int类型
		int toNumber();

		/// @brief	转换value为long long类型
		long long toBigNumber();

		/// @brief	转换value为bool类型
		bool toBoolean();

		/// @brief 转换value为float类型
		double toFloat();

		/// @brief	转换value为string类型
		const std::string toString();

		/// @brief	获取子节点类表
		/// @warning	即将废止，请勿再使用。 如需枚举子节点，可使用 cell[""]来取代。
		/// @retval	E4XCell list array
		/// @warning	废止该函数，可以使用 [""]+循环 来替代
		CELL_LIST& getChildCells();

	protected:
		/// @brief 跳过字符串中的空白字符，如\\b, \\t 等
		const char* skipWhiteSpace(const char* pszIn);

		/// @brief 跳过字符串的非空白符
		const char* skipValueChars(const char* pszIn);

		/// @brief 输入一定量的tab,用于序列化E4XCell到字符串中
		/// @param strXml	附加输出的字符串
		/// @param	nIndent	缩进等级, 如果为5，将缩进5个tab键
		/// @retval	strXml的引用
		std::string& writeIndent( std::string& strXml, int nIndent);


		/// @brief	检查是否到达尾部
		///	@param pszBuffer	被检查的字符串
		/// @param nMinSize 到达字符串结尾前，至少需要保留的字符处
		/// @retval	true	还有足够剩余字符串
		///	@retval	false	空间不足，后续操作需要注意可能边界溢出。
		bool notEnd(const char* pszBuffer, int nMinSize);

		/// @brief	从已经转义的XML字符串数据中，获取转义前的字符串数据。
		/// @param	src 已经转义的xml字符串。
		/// @retval	转义前的原始字符串数据。
		/// @warning 此函数可能产生E4XException异常
		/// @see	getRealStringWithoutException
		static std::string getRealString(const char* src);

		/// @brief	从已经转义的XML字符串数据中，获取转义前的字符串数据。
		/// @param	out 转换成功时，输出转义前的原始字符串数据。
		/// @param	src 已经转义的xml字符串。
		/// @retval	是否成功完成转换。
		/// @see	getRealString
		static bool getRealStringWithoutException(std::string& out, const char* src);

		/// @brief	从普通字符串，转义成为xml字符串格式。
		/// @param	src 原始字符串数据。
		/// @retval	转义为xml格式的字符串。
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
		/// @brief	禁止的 拷贝构造函数
		/// @warning	当需要拷贝的时候，请使用copy函数
		E4XCell& operator = ( const E4XCell& cell);
		//E4XCell& operator = ( E4XCell& cell);

	};

}  // namespace

