/// @brief E4XDocument Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#pragma once

namespace E4X
{

	class E4XDocument :
		public E4XCell
	{
	public:
		E4XDocument(void);
		E4XDocument(const std::string& strName);
		virtual ~E4XDocument(void);

		bool loadFile( const char* xmlfile);
		bool saveFile(const char* xmlfile = 0);

		virtual E4XDocument& copy();

	protected:
		std::string& toXmlStringInternal( std::string& strXml, int nIndent = 0);

	public:
		const char* parse( const char* xmldata);
	};

}  // namespace

