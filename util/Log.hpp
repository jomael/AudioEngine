#ifndef LOG_HPP
#define LOG_HPP

#include <string>

/**
* \file
*/

/**
* \macro LOG
* Calls log() with the name of the current function
* as the \a where argument.
*
* \param msg Message to be printed (a const char* or a std::string).
*/
#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)

	// both clang and GCC use __PRETTY_FUNCTION__
	#define LOG(msg) do { log(__PRETTY_FUNCTION__, msg); } while(false)

#elif defined(_MSC_VER)

	// M$ C/C++ uses __FUNCSIG__
	#define LOG(msg) do { log(__FUNCSIG__, msg); } while(false)

#else

	// __func__ works everywhere but only gives a simple name
	#define LOG(msg) do { log(__func__, msg); } while(false)
#endif

void log(const char *where, const char *message);
void log(const char *where, const std::string &message);

#endif
