/// @brief E4XDocument Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#pragma once

namespace E4X
{

	/// @brief xml document node
	/// һ�� E4XDocument �������һ�� E4XElement �� һ�� E4XDeclaration
	/// @warning Ϊ�˷������(����������TinyXml)��ĳЩ�汾��CppE4X��������������E4XElement,�����ǲ��Ƽ��ġ�

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
		/// @param xmlfile	���ص�xml�ļ���·��
		/// @retval	true: ���سɹ�	false: ����ʧ��
		/// @warning:	Ŀǰ�汾�У������׳�E4XException�쳣��
		bool loadFile( const char* xmlfile);

		/// save xml data to xml file
		/// @param	xmlfile	�����xml�ļ���·��
		/// @retval	true: ����ɹ��� false: ����ʧ��
		bool saveFile(const char* xmlfile = 0);

		virtual E4XDocument& copy();

	protected:
		std::string& toXmlStringInternal( std::string& strXml, int nIndent = 0);

	public:
		const char* parse( const char* xmldata);
	};

}  // namespace

