/// @brief E4XText Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#pragma once

namespace E4X
{

	/// xml text node class
	class E4XText :
		public E4XCell
	{
	public:
		/// Default constructor
		E4XText(void);
		/// Constructor with text value
		E4XText(const std::string& strValue);

		///	Destructor
		virtual ~E4XText(void);

		/// clone a  E4XText
		virtual E4XText& copy();

		///	指向可能存在的xml字符串头	"<![CDATA["
		static const std::string m_pszTextBegin;
		/// 指向可能存在的xml字符串尾	"]]>"
		static const std::string m_pszTextEnd;

	protected:
		virtual const char* parseImp( const char* xmldata);
		std::string& toXmlStringInternal( std::string& strXml, int nIndent);

	private:

		/// 是否需要进行xml字符转义
		bool m_bNeedEncode;
	};

}  // namespace

