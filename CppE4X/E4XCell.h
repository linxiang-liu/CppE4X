#pragma once

namespace E4X
{

	class E4XCell
	{
	protected:
		friend class E4XIterator;
		E4XCell(E4X_TYPE nType);
	public:
		virtual ~E4XCell(void);

		// virtual
		virtual const char* parse( const char* xmldata) = 0;
		virtual std::string& toXmlStringInternal( std::string& strXml, int nIndent) = 0;
		std::string toXmlString();
		virtual const std::string& getName();
		virtual const std::string& getValue();
		virtual void setName(const std::string& name);
		virtual void setValue(const std::string& value);
		virtual E4XCell& copy() = 0;
		virtual void destroy();

		// ���������
		E4XIterator operator/(const std::string& strChildName);
		E4XIterator operator[](const std::string& strChildName);
		E4XCell& operator = ( const std::string& strName);
		E4XCell& operator = ( bool bFlag);
		E4XCell& operator = ( int nNumber);

		// ����ת��
		operator E4XIterator();
		int ToNumber();
		bool ToBoolean();
		double ToFloat();
		std::string ToString();

		int GetType();
		E4XCell& GetParent();
		void appendChild( E4XCell* pCell);
		void prependChild( E4XCell* pCell);

		void insertChildAfter( E4XCell* exist, E4XCell* insert);
		void insertChildBefore( E4XCell* exist, E4XCell* insert);

		bool removeChild( E4XCell* pCell);
		void removeAllChild();
		void removeAllChildElement();

		E4XCell* parent();

	protected:
		const char* skipWhiteSpace(const char* pszIn);
		const char* skipValueChars(const char* pszIn);
		std::string& writeIndent( std::string& strXml, int nIndent);
		bool NotEnd(const char* pszBuffer, int nMinSize);

		static std::string getRealString(const char* src);
		static std::string getXmlString(const char* src);

	protected:
		std::string m_strName;
		std::string m_strValue;
		std::list< E4XCell*> m_lstCell;
		E4X_TYPE m_nType;
		E4XCell* m_pParent;

	private:	// ��ֹ�����������
		E4XCell& operator = ( const E4XCell& cell);

	};

}  // namespace

