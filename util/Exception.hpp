#ifndef DENGINE_EXCEPTION_HPP
#define DENGINE_EXCEPTION_HPP

#include "Debug.hpp"
#include "StringUtils.hpp"

#include <stdexcept>

/**
 * \file
 * Contains engine-specific exceptions.
 */

//---------------------------------------------------------------------------

using std::out_of_range;
using std::invalid_argument;

/**
 * Thrown when an operation on an object fails because the object is in
 * an unsuitable state, usually not yet initialized, or already initialized
 * (when attempting to initialize it again), or set up in another way
 * (e.g. trying to write to a buffer that was previously set up
 * as read-only).
 */
class bad_object_state : public std::logic_error
{
public:

	bad_object_state(const char* what)
		: std::logic_error(what) {}

	bad_object_state(const std::string& what)
		: std::logic_error(what) {}
};

/**
* Base class for exceptions thrown by the engine and its utility functions.
*/
class Exception : public std::exception
{
protected:

	/**
	* A terse human-readable message of what and where went wrong.
	* Recommended form is "<origin>: <what>" where \a origin is the name
	* of the method that throws, and \a what is a terse description
	* of the problem.
	*
	* \note You can use the THIS_FN macro to get a string containing
	* a fully qualified name of the calling method.
	*/
	std::string m_what;

public:

	/**
	* Constructor.
	* \param message The message to be returned by what().
	*/
	Exception(const std::string &message)
		: m_what(message) {}

	/**
	* Implements the std::exception what() call.
	* Returns a pointer to the m_what string.
	*/
	virtual const char *what() const noexcept override { return m_what.c_str(); }
};

//---------------------------------------------------------------------------

/**
* \def Throw(ExceptionT, message)
*
* A shortcut for throwing objects based on Exception, passing
* the identification of the calling function automatically.
*
* \param ExceptionT Type of the exception to throw (should be derived
* from Exception).
* \param message Message to be associated with the exception (a string).
*/
#define Throw(ExceptionT, message) do { \
	throw ExceptionT(std::string(THIS_FN) + ": " + message); \
} while(0)

//---------------------------------------------------------------------------

/**
* Thrown when a parameter of a call exceeds the valid range for input.
*/
class OutOfRange : public Exception
{
public:

	OutOfRange(const std::string &message)
		: Exception(message) {}
};

//---------------------------------------------------------------------------

/**
* Thrown when the result of a computation exceeds the range of the output
* value.
*/
class ResultOutOfRange : public Exception
{
public:

	ResultOutOfRange(const std::string &message)
		: Exception(message) {}
};

//---------------------------------------------------------------------------

/**
* Thrown when an element of a map, dictionary or similar container
* is not found by its name or key.
*
* Also is thrown on attempt to access a container that is empty.
*
* Also can be thrown when a system object (a process, a file, etc.)
* is not found by its identifier or name.
*/
class NotFound : public Exception
{
public:

	NotFound(const std::string &message)
		: Exception(message) {}
};

//---------------------------------------------------------------------------

/**
* Thrown to indicate that calls were done in illogical order, leaving
* some object in state unsuitable for the next operation.
* This is almost always a programming error (possibly a race condition).
*/
class BadObjectState : public Exception
{
public:

	BadObjectState(const std::string &message)
		: Exception(message) {}
};

//---------------------------------------------------------------------------

/**
 * Thrown to indicate that a call was done on an object that is semantically
 * not of proper type (it was not initially set up to be used in that way).
 * This is almost always a programming error.
 */
class BadObjectType : public Exception
{
public:

	BadObjectType(const std::string &message)
		: Exception(message) {}
};

//---------------------------------------------------------------------------

/**
* Thrown when an argument to a call is inconsistent with the others
* (the message should tell which arguments are in conflict and what kind
* of inconsistency it is). Also used for unexpected null argument.
*/
class InvalidArgument : public Exception
{
public:

	InvalidArgument(const std::string &message)
		: Exception(message) {}

};

//---------------------------------------------------------------------------

/**
* Thrown from a switch-like code that operates on values of an enum
* when the presented value does not match any known value of the enum
* (i.e. it is some out-of-range number incorrectly casted to the enum).
*/
class BadEnumValue : public Exception
{
public:

	BadEnumValue(const std::string &message)
		: Exception(message) {}
};

//---------------------------------------------------------------------------

/**
* Exception reported by platform-specific code.
*/
class PlatformException : public Exception
{
public:

	PlatformException(const std::string &message)
		: Exception(message) {}
};

//---------------------------------------------------------------------------

/**
* Exception that occurs in an I/O operation (not always an error).
*/
class IOException : public Exception
{
public:

	IOException(const std::string &message)
		: Exception(message) {}
};

//---------------------------------------------------------------------------

#endif
