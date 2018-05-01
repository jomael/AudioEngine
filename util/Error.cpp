#include "Error.hpp"

#include <cstdio>
#include <cstdlib>

void panic(const char* from, const char* message)
{
	std::fprintf(stderr, "[%s] PANIC: %s\n", from, message);
	std::exit(2);
}
