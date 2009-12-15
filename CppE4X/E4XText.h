/// @brief E4XText Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#pragma once

namespace E4X
{

	/// xml text node class
	class E4XText :
		public E4XCell
	{
	public:
		/// Default constructor
		E4XText(void);
		/// Constructor with text value
		E4XText(const std::string& strValue);

		///	Destructor
		virtual ~E4XText(void);

		/// clone a  E4XText
		virtual E4XText& copy();

		/// parse a xml text node data
		/// @param xmldata	������ַ���
		/// @return ����parse��ɺ��ָ�롣�ɹ�parse�󣬸�ֵ��ָ����δparse�����ݲ��֡� ������0ʱ��parseʧ��
		const char* parse( const char* xmldata);

		///	ָ����ܴ��ڵ�xml�ַ���ͷ	"<![CDATA["
		static const std::string m_pszTextBegin;
		/// ָ����ܴ��ڵ�xml�ַ���β	"]]>"
		static const std::string m_pszTextEnd;

	protected:
		/// @brief ���л���xml�ַ���
		/// @param strXml	������ַ������á����л��ĺ���ַ��������ӵ��ô��С�
		/// @param nIndent �����ȼ�����E4XText��Ч��
		/// @return	strXml������
		std::string& toXmlStringInternal( std::string& strXml, int nIndent);

	private:

		/// �Ƿ���Ҫ����xml�ַ�ת��
		bool m_bNeedEncode;
	};

}  // namespace

