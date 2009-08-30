#pragma once

namespace E4X
{
	class E4XException
	{
	public:
		enum E4XErrorCode
		{
			ERROR_UNKNOWN,
			ERROR_INVALID_TYPE,
			ERROR_INVALID_TEXT,
			ERROR_HAS_NO_CHILD,
			ERROR_OUT_BOUND,
			ERROR_UNSUPPORTED_EVALUATE,
			ERROR_UNSUPPORTED_OPERATOR
		};

	public:
		E4XException(E4XErrorCode ec = ERROR_UNKNOWN);
		~E4XException(void);

		int errorCode();

		const char* Error(void);

	private:
		E4XErrorCode m_ec;
	};

}  // namespace

