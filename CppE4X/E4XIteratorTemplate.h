/// @brief E4XCell inline / template functions.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///


namespace E4X
{

	template<typename T>
	E4XIterator& E4XIterator::operator = ( T t)
	{
		getCell() = t;
		return *this;
	}
}
