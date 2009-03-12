#pragma once

namespace E4X
{

	class E4XAttribute :
		public E4XCell
	{
	public:
		E4XAttribute(void);
		E4XAttribute(const std::string& strName);
		virtual ~E4XAttribute(void);

		const char* parse( const char* xmldata);

		virtual E4XAttribute& copy();

	protected:
		std::string& toXmlStringInternal( std::string& strXml, int nIndent);

	private:
		char m_chSeparator;
	};

}  // namespace

