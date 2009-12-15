/// @brief E4X_TYPE Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///


#pragma once

namespace E4X
{
	/// type of Xml Node
	enum E4X_TYPE
	{
		/// xml attribute
		E4X_ATTRIBUTE,
		/// xml element
		E4X_ELEMENT,
		///	xml document
		E4X_DOCUMENT,
		/// xml text
		E4X_TEXT,
		/// xml declaration
		E4X_DECLARATION,
		/// xml comment
		E4X_COMMENT
	};
}
