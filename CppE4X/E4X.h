#pragma once

#include "config.h"

// stl
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <algorithm>
#include <cassert>

// c
#include <string.h>		// compatible with fedora
#include <stdio.h>

// e4x

namespace E4X
{
	class E4XCell;
	typedef std::list< E4XCell*> CELL_LIST;
};


#include "E4XType.h"
#include "E4XException.h"
#include "E4XCell.h"
#include "E4XAttribute.h"
#include "E4XComment.h"
#include "E4XDeclaration.h"
#include "E4XElement.h"
#include "E4XDocument.h"
#include "E4XText.h"
#include "E4XIterator.h"


namespace E4X
{
	typedef E4XException& E4XExceptionRef;
	typedef E4XCell&	E4XCellRef;
	typedef E4XAttribute&	E4XAttributeRef;
	typedef E4XComment&	E4XCommentRef;
	typedef E4XDeclaration&	E4XDeclarationRef;
	typedef E4XElement&	E4XElementRef;
	typedef E4XDocument& E4XDocumentRef;
	typedef E4XText&	E4XTextRef;
};


