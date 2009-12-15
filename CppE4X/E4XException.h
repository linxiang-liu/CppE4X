/// @brief E4XException Header File.
/// @author Linxiang Liu
/// @version 2.1
/// @date    2008-2009
///

#pragma once

namespace E4X
{
	/// cppe4x exception
	class E4XException
	{
	public:

		/// cppe4x exception code
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
		/// Default construct
		/// @param ec	exception code
		E4XException(E4XErrorCode ec = ERROR_UNKNOWN);

		/// Destructor
		~E4XException(void);

		/// get cppe4x exception code
		/// @retval	exception code
		int errorCode();

		/// get cppe4x exception error text
		/// @retval error description
		const char* Error(void);

	private:
		E4XErrorCode m_ec;
	};

}  // namespace

