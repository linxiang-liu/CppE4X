/// 
/// @brief CppE4X Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#pragma once

// stl
#include <string>
#include <sstream>
#include <list>
#include <algorithm>

// c
#ifndef WIN32
#include <string.h>		// compatible with fedora
#endif

// e4x
namespace E4X
{
	class E4XCell;
	class E4XText;
	class E4XAttribute;
	class E4XDocument;
	class E4XDeclaration;
	class E4XComment;
	class E4XIterator;

	/// list of E4XCell Pointer
	typedef std::list< E4XCell*> CELL_LIST;
};


#include "E4XType.h"
#include "E4XException.h"
#include "E4XCell.h"
#include "E4XText.h"
#include "E4XAttribute.h"
#include "E4XComment.h"
#include "E4XDeclaration.h"
#include "E4XElement.h"
#include "E4XDocument.h"
#include "E4XIterator.h"
#include "E4XCellTemplate.h"
#include "E4XIteratorTemplate.h"


namespace E4X
{
	/// E4XException Ref
	typedef E4XException& E4XExceptionRef;
	/// E4XCell Ref
	typedef E4XCell&	E4XCellRef;
	/// E4XAttribute Ref
	typedef E4XAttribute&	E4XAttributeRef;
	/// E4XComment Ref
	typedef E4XComment&	E4XCommentRef;
	/// E4XDeclaration Ref
	typedef E4XDeclaration&	E4XDeclarationRef;
	/// E4XElement Ref
	typedef E4XElement&	E4XElementRef;
	/// E4XDocument Ref
	typedef E4XDocument& E4XDocumentRef;
	/// E4XText Ref
	typedef E4XText&	E4XTextRef;
};


