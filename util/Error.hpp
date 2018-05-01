#ifndef ERROR_HPP
#define ERROR_HPP

#include "Debug.hpp"

/**
* \file Error.hpp
* The most low-level error handling routines.
*/

/**
* Prints the message to standard error output and terminates
* the application immediately (does not return).
*/
void panic(const char* from, const char* message);

#endif
