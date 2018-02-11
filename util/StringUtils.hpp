#ifndef DENGINE_STRING_UTILS_HPP
#define DENGINE_STRING_UTILS_HPP

#include <cstdarg>
#include <string>
#include <vector>
#include <iostream>

/**
* Convert to string, alternative implementation for
* android. Android NDK is have broken std::to_string.
*/
#ifdef __ANDROID__

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}

#endif

/**
* Formats a string in a printf-like fashion and returns
* the results as a std::string.
*/
std::string strprintf(const char *fmt, ...);

void printWithLineNumbers(std::ostream &os, const char *str);
void printWithLineNumbers(std::ostream &os, const std::string &str);

/**
* A string of bytes.
*/
class String
{
protected:

	/**
	* Length of the string in bytes, not including the terminating '\0'
	* character.
	*/
	size_t m_length = 0;

	/**
	* Pointer to the character data, terminated by the '\0' character.
	* For an empty string, this pointer *may* be null.
	*/
	char *m_data = nullptr;

public:

	/**
	* Default constructor. Produces an empty string.
	*/
	String() {}

	/**
	* Copy constructor.
	*
	* \note If the source string has zero size, the newly produced copy
	* has zero size _and_ its data pointer is null.
	*/
	String(const String &src);

	/**
	* Move constructor.
	*/
	String(String &&src);

	/**
	* Constructs a String object from the given C-style string.
	* As a special case, if \a src is null, an empty string results.
	*/
	String(const char *src);

	~String();

	/**
	* Equality test operator.
	*
	* Strings are compared as sequences of bytes, and are only considered
	* equal if they are binary identical up to the terminating '\0' character.
	* (Empty strings are always identical.)
	*/
	bool operator==(const String &b) const;

	/**
	* Inverse of the equality test operator.
	*/
	bool operator!=(const String &b) const { return !operator==(b); }

	/**
	* Returns the length of the string in characters (not including
	* the terminating NUL character).
	*/
	size_t length() const { return m_length; }

	/**
	* Returns true if the string is empty (has zero size),
	* false otherwise.
	*/
	bool isEmpty() const { return m_length == 0; }

	/**
	* Returns a C-style string pointer to the string data.
	* If the string is empty, a pointer to a statically allocated
	* empty string is returned (never null).
	*/
	const char *cstr() const { return (m_length > 0) ? m_data : ""; }

	/**
	* Returns the character at the given zero-based index, counting
	* from the start.
	*
	* If the index is negative or exceeds the length of the string,
	* the '\0' character is returned.
	*/
	char at(int i) const;
};

#endif
