#pragma once
//#include "E4XCell.h"

namespace E4X
{

	class E4XComment :
		public E4XCell
	{
	public:
		E4XComment(void);
		E4XComment(const std::string& strName);
		virtual ~E4XComment(void);

		static const std::string m_pszCommentBegin;// = "<!--";
		static const std::string m_pszCommentEnd;// = "-->";

		const char* parse( const char* xmldata);
		virtual E4XComment& copy();


	private:
		std::string& toXmlStringInternal( std::string& strXml, int nIndent);
	};

}  // namespace

