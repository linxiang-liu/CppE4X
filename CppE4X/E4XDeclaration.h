/// @brief E4XDeclaration Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#pragma once

namespace E4X
{

	/// @brief xml declaration node
	/// 只可能为E4XDocument的子节点,且只存在一份。

	class E4XDeclaration :
		public E4XCell
	{
	public:
		E4XDeclaration(void);
		virtual ~E4XDeclaration(void);

		virtual E4XDeclaration& copy();


	protected:
		virtual const char* parseImp( const char* xmldata);

		/// declaration node name: "#xml"
		static const std::string m_pszDeclarationName;
		/// declaration begin text: "<?xml"
		static const std::string m_pszDeclarationBegin;
		/// declaration begin text: "?>"
		static const std::string m_pszDeclarationEnd;

		std::string& toXmlStringInternal( std::string& strXml, int nIndent);
	};

}  // namespace

