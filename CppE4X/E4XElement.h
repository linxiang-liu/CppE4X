/// @brief E4XElement Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#pragma once

namespace E4X
{
	/// xml element node

	class E4XElement :
		public E4XCell
	{
	public:
		E4XElement(void);

		/// constructor with element name
		E4XElement(const std::string& strName);
		virtual ~E4XElement(void);


		virtual void setValue(const std::string& value);
		virtual const std::string getValue();
		virtual E4XElement& operator = ( const std::string& strName);

		virtual	E4XElement& copy();


	protected:
		virtual const char* parseImp( const char* xmldata);
		std::string& toXmlStringInternal( std::string& strXml, int nIndent);
	};

}  // namespace

