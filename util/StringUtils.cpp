#include "StringUtils.hpp"

#include <cstdio>
#include <iostream>
#include <cstring>

std::string strprintf(const char *fmt, ...)
{
	va_list args1;
	va_start(args1, fmt);

	va_list args2;
	va_copy(args2, args1);
	size_t bytesNeeded = std::vsnprintf(nullptr, 0, fmt, args1);
	std::vector<char> buf(1 + bytesNeeded);
	va_end(args1);

	std::vsnprintf(buf.data(), buf.size(), fmt, args2);
	va_end(args2);

	return std::string(buf.data());
}

void printWithLineNumbers(std::ostream &os, const char *str)
{
	int lineNumber = 1;

	os << '\n' << lineNumber << ": ";
	for (const char *sptr = str; *sptr; sptr++) {
		if (*sptr == '\n') {
			lineNumber++;
			os << '\n' << lineNumber << ": ";
			continue;
		}

		os << *sptr;
	}
}

void printWithLineNumbers(std::ostream &os, const std::string &str)
{
	printWithLineNumbers(os, str.c_str());
}

//---------------------------------------------------------------------------

String::String(const String &src)
{
	if (src.isEmpty()) {
		m_length = 0;
		m_data = nullptr;
	}
	else {
		m_length = src.m_length;
		m_data = static_cast<char*>(malloc(m_length + 1));
		memcpy(m_data, src.m_data, m_length + 1);
	}
}

String::String(String &&src)
{
	m_length = src.m_length;
	m_data = src.m_data;
	src.m_length = 0;
	src.m_data = nullptr;
}

String::String(const char *src)
{
	if (src && src[0]) {
		m_length = strlen(src);
		m_data = static_cast<char*>(malloc(m_length + 1));
		memcpy(m_data, src, m_length + 1);
	}
	else {	// source is empty or null
		m_length = 0;
		m_data = nullptr;
	}
}

String::~String()
{
	if (m_data) {
		free(m_data);
	}
}

bool String::operator==(const String &b) const
{
	// if the lengths differ, the strings cannot be equal
	if (m_length != b.m_length)
		return false;

	// empty strings are always equal
	if (m_length == 0)
		return true;

	// a string is always equal to itself
	if (&b == this)
		return true;

	// compare strings char by char
	return (strcmp(m_data, b.m_data) == 0);
}

char String::at(int i) const
{
	if (i < 0 || i >= m_length)
		return '\0';
	return m_data[i];
}
