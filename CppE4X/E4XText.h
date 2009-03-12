#pragma once

namespace E4X
{

	class E4XText :
		public E4XCell
	{
	public:
		E4XText(void);
		E4XText(const std::string& strValue);
		virtual ~E4XText(void);
		virtual E4XText& copy();

		const char* parse( const char* xmldata);

		static const std::string m_pszTextBegin;
		static const std::string m_pszTextEnd;

	protected:
		std::string& toXmlStringInternal( std::string& strXml, int nIndent);

	private:
		bool m_bNeedEncode;
	};

}  // namespace

