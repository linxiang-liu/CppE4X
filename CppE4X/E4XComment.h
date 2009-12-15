/// @brief E4XComment Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#pragma once
//#include "E4XCell.h"

namespace E4X
{

	/// @brief xml comment node

	class E4XComment :
		public E4XCell
	{
	public:
		E4XComment(void);

		/// consturtor with comment value
		/// @param strValue	comment value
		E4XComment(const std::string& strValue);
		virtual ~E4XComment(void);

		/// comment begin text: "<!--"
		static const std::string m_pszCommentBegin;
		/// comment end text: "-->"
		static const std::string m_pszCommentEnd;

		const char* parse( const char* xmldata);
		virtual E4XComment& copy();


	private:
		std::string& toXmlStringInternal( std::string& strXml, int nIndent);
	};

}  // namespace

