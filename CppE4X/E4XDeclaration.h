/// @brief E4XDeclaration Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#pragma once

namespace E4X
{

	class E4XDeclaration :
		public E4XCell
	{
	public:
		E4XDeclaration(void);
		virtual ~E4XDeclaration(void);

		virtual E4XDeclaration& copy();

		const char* parse( const char* xmldata);

	protected:
		static const std::string m_pszDeclarationName;
		static const std::string m_pszDeclarationBegin;
		static const std::string m_pszDeclarationEnd;

		std::string& toXmlStringInternal( std::string& strXml, int nIndent);
	};

}  // namespace

