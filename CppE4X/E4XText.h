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

		/// parse a xml text node data
		/// @param xmldata	传入的字符串
		/// @return 返回parse完成后的指针。成功parse后，该值将指向尚未parse的数据部分。 当返回0时，parse失败
		const char* parse( const char* xmldata);

		///	指向可能存在的xml字符串头	"<![CDATA["
		static const std::string m_pszTextBegin;
		/// 指向可能存在的xml字符串尾	"]]>"
		static const std::string m_pszTextEnd;

	protected:
		/// @brief 序列化到xml字符串
		/// @param strXml	输入的字符串引用。序列化的后的字符串将附加到该串中。
		/// @param nIndent 缩进等级。对E4XText无效。
		/// @return	strXml的引用
		std::string& toXmlStringInternal( std::string& strXml, int nIndent);

	private:

		/// 是否需要进行xml字符转义
		bool m_bNeedEncode;
	};

}  // namespace

