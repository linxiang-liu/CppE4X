/// @brief E4XCell inline / template functions.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///


namespace E4X
{

	template<typename T>
	E4XCell& E4XCell::operator = ( T& t)
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
}
