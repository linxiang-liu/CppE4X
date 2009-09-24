#pragma once


namespace E4X
{
	class E4XText;
	class E4XIterator;

	class E4XCell
	{
	protected:
		friend class E4XIterator;
		E4XCell(E4X_TYPE nType);
	public:
		virtual ~E4XCell(void);

		E4XCell* parent();

		// virtual
		virtual const char* parse( const char* xmldata) = 0;
		const char* parseAnsi(const char* xmldata);
		virtual std::string& toXmlStringInternal( std::string& strXml, int nIndent) = 0;
		virtual const std::string getName();
		virtual const std::string getValue();
		virtual void setName(const std::string& name);
		virtual void setValue(const std::string& value);
		virtual E4XCell& copy() = 0;			// clone 函数
		virtual void destroy();					// 销毁由copy产生的对象。
		const std::string toXmlString();
		const std::string toAnsiXmlString();

		int type();
		void appendChild( E4XCell* pCell);
		void appendChild( E4XCell& cell);
		void prependChild( E4XCell* pCell);
		void prependChild( E4XCell& cell);

		void insertChildAfter( E4XCell* exist, E4XCell* insert);
		void insertChildAfter( E4XCell& exist, E4XCell& insert);

		void insertChildBefore( E4XCell* exist, E4XCell* insert);
		void insertChildBefore( E4XCell& exist, E4XCell& insert);

		bool removeChild( E4XCell* pCell);
		void removeAllChild();
		void removeAllChildElement();

		// 运算符重载
		E4XIterator operator/(const std::string& strChildName);
		E4XIterator operator[](const std::string& strChildName);
		
		template<typename T>
		E4XCell& operator = ( T& t)
		{
			std::stringstream stream;
			stream << t;
			stream >> m_strValue;
			if( type() == E4X_ELEMENT)
			{
				E4XCell* cell= new E4XText( m_strValue);
				this->appendChild( cell);
			}
			return *this;
		};

		E4XCell& operator = ( const char* strName);
		E4XCell& operator = ( char* strName);
		E4XCell& operator = ( const std::string& value);
		E4XCell& operator = ( std::string& value);

		E4XCell& operator = ( bool bFlag);


		// 类型转换
		//operator E4XIterator();
		int toNumber();
		bool toBoolean();
		double toFloat();
		const std::string toString();

	protected:
		const char* skipWhiteSpace(const char* pszIn);
		const char* skipValueChars(const char* pszIn);
		std::string& writeIndent( std::string& strXml, int nIndent);
		bool notEnd(const char* pszBuffer, int nMinSize);

		static std::string getRealString(const char* src);
		static std::string getXmlString(const char* src);

	protected:
		std::string m_strName;
		std::string m_strValue;
		std::list< E4XCell*> m_lstCell;
		E4X_TYPE m_nType;
		E4XCell* m_pParent;

	private:	// 禁止的运算符重载
		E4XCell& operator = ( const E4XCell& cell);

	};

}  // namespace

