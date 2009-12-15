/// @brief E4XDocument Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#pragma once

namespace E4X
{

	/// @brief xml document node
	/// 一个 E4XDocument 至多包含一个 E4XElement 和 一个 E4XDeclaration
	/// @warning 为了方便操作(并尽量兼容TinyXml)，某些版本的CppE4X可能允许包含多个E4XElement,但这是不推荐的。

	class E4XDocument :
		public E4XCell
	{
	public:
		/// Default constructor
		E4XDocument(void);

		/// Constructor with xml file name
		E4XDocument(const std::string& strName);

		/// Destructor
		virtual ~E4XDocument(void);

		/// load xml data from xml file
		/// @param xmlfile	加载的xml文件的路径
		/// @retval	true: 加载成功	false: 加载失败
		/// @warning:	目前版本中，可能抛出E4XException异常。
		bool loadFile( const char* xmlfile);

		/// save xml data to xml file
		/// @param	xmlfile	保存的xml文件的路径
		/// @retval	true: 保存成功。 false: 保存失败
		bool saveFile(const char* xmlfile = 0);

		virtual E4XDocument& copy();

	protected:
		std::string& toXmlStringInternal( std::string& strXml, int nIndent = 0);

	public:
		const char* parse( const char* xmldata);
	};

}  // namespace

