#include "E4X.h"

namespace E4X
{
	E4XException::E4XException(E4XErrorCode ec)
		: m_ec( ec)
	{
	}

	E4XException::~E4XException(void)
	{
	}

	int E4XException::getErrorCode()
	{
		return m_ec;
	}

	const char* E4XException::Error(void)
	{
		const char* pchError = 0;
		switch( m_ec)
		{
		case ERROR_INVALID_TYPE:
			pchError = "Invalid Child Type";
			break;
		case ERROR_UNSUPPORTED_EVALUATE:
			pchError = "Unsupported yet :(, use new E4XCell(cell) instead";
			break;
		case ERROR_OUT_BOUND:
			pchError = "Out of bound";
			break;
		case ERROR_HAS_NO_CHILD:
			pchError = "Has no child items";
			break;
		case ERROR_UNSUPPORTED_OPERATOR:
			pchError = "Unsupported operator :(";
			break;
		case ERROR_INVALID_TEXT:
			pchError = "Invalid Text";
			break;
		case ERROR_UNKNOWN:
		default:
			pchError = "Unknown error";
		}

		return pchError;
	}

}  // namespace

