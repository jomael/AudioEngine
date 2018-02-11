#include "Log.hpp"

#include <cstdio>

void log(const char *where, const char *message)
{
	fprintf(stderr, "[%s] %s\n", where, message);
}

void log(const char *where, const std::string &message)
{
	log(where, message.c_str());
}
