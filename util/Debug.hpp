#ifndef DEBUG_HPP
#define DEBUG_HPP

/** \file */

/**
 * \macro THIS_FN
 * Unrolls to a human-readable string (of type const char*) containing
 * the name of the current function/method.
 */

// define a macro that unrolls to the fully qualified name
// of the current function; various compilers have various names for this

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)

    // both Clang and G++ use __PRETTY_FUNCTION__, albeit the exact content
    // differs slightly (but both are human readable)
    #define THIS_FN __PRETTY_FUNCTION__

#elif defined(_MSC_VER)

    // MSVC uses __FUNCSIG__ for a complete function signature
    #define THIS_FN __FUNCSIG__

#else

	// C99-standardized, should work everywhere but only shows the function name
	#define THIS_FN __FUNC__
#endif

/**
 * \macro COMPLAIN(msg)
 * Reports an error, preceding it by the name of the function/method where
 * it occurred.
 *
 * \note The \a msg argument is passed to std::cerr via the "<<"
 * operator so it is possible to pass multiple arguments separated with
 * the "<<" operators, and all will be concatenated and sent to std::cerr.
 */
#define COMPLAIN(msg) do { \
    std::clog << "error: " << THIS_FN << ": " << msg << '\n'; \
} while(false);

#endif
