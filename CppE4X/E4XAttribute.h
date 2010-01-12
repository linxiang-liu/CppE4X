/// 
/// @brief E4XAttribute Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#pragma once

namespace E4X
{

	/// @class E4XAttribute
	/// @brief	处理XML节点中的属性
	class E4XAttribute :
		public E4XCell
	{
	public:
		/// Default constructor
		E4XAttribute(void);

		/// @brief Constructor with attribute name
		/// @param strName	attribute name
		E4XAttribute(const std::string& strName);

		/// Destuctor
		virtual ~E4XAttribute(void);


		virtual E4XAttribute& copy();

	protected:
		virtual const char* parseImp( const char* xmldata);

		std::string& toXmlStringInternal( std::string& strXml, int nIndent);

	private:
		/// 分割字符，保存当前使用的分隔符。以便匹配嵌入的"\'", "\""
		char m_chSeparator;
	};

}  // namespace

