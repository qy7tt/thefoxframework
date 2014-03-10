﻿#ifndef _THEFOX_STRING_UTIL_H_
#define _THEFOX_STRING_UTIL_H_

#include <base/Types.h>

namespace thefox
{

static const int kMaxStringLen = 100 * 1024;

inline int stoi(const String &str) 
{ 
	return (0 == str.length()) ? 0 : atoi(str.c_str());
}

inline unsigned int stoui(const String &str) 
{ 
	return (0 == str.length()) ? 0 : static_cast<unsigned int>(atoi(str.c_str()));
} 

inline long stol(const String &str) 
{ 
	return (0 == str.length()) ? 0L : atol(str.c_str()); 
}

inline float stof(const String &str)
{ 
	return (0 == str.length()) ? 0.0f : static_cast<float>(atof(str.c_str())); 
}

inline double stod(const String &str) 
{ 
	return (0 == str.length()) ? 0.0 : atof(str.c_str()); 
}

inline bool stob(const String &str) 
{ 
	return (0 == str.length() || str == "0" || str == "false" || str == "FALSE") ? false : true; 
}

inline String toString(const int val)
{
	char buf[32] = {0};
	return _itoa(val, buf, 10);
}

inline String toString(const unsigned int val)
{
	char buf[32] = {0};
	snprintf(buf, sizeof(buf), "%u", val);
	return buf;
}

inline String toString(const long val)
{
	char buf[32] = {0};
	return _ltoa(val, buf, 10);
}

inline String toString(const long long val)
{
	char buf[32] = {0};
	snprintf(buf, sizeof(buf), "%I64u", val);
	return buf;
}

inline String toString(const double val)
{
	char buf[32] = {0};
	snprintf(buf, sizeof(buf), "%f", val);
	return buf;
}

inline String toString(const bool val)
{
	return val ? "1" : "0";
}

inline String &format(String &str, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);

	char *buf = (char *)malloc(kMaxStringLen);
	if (buf) {
		vsnprintf(buf, kMaxStringLen, format, ap);
		str = buf;
		free(buf);
		va_end(ap);
	}
	return str;
}

inline String trimLeft(String &str)
{
	String::size_type index = str.find_first_not_of("\n\r\t");
	if (index != String::npos)
		str = str.substr(index);
	return str;
}

inline String trimRight(String &str)
{
	String::size_type index = str.find_last_not_of("\n\r\t");
	if (index != String::npos)
		str = str.substr(0, index + 1);
	return str;
}

inline String trim(String &str)
{
	return trimRight(trimLeft(str));
}

inline String toLower(String &str)
{
	for (String::size_type i = 0; i < str.length(); ++i)
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 0x20;
	return str;
}

inline String toUpper(String &str)
{
	for (String::size_type i = 0; i < str.length(); ++i)
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 0x20;
	return str;
}

inline bool charIsLetter(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c >= 'z'))
		return true;
	return false;
}

inline bool equalsIgnoreCase(const String &s1, const String &s2)
{
	if (s1.length() != s2.length())
		return false;
	
	for (String::size_type i = 0; i < s1.length(); ++i) {
		if (s1[i] == s2[i])
			continue;
		if (!charIsLetter(s1[i]) || !charIsLetter(s2[i]))
			return false;
		if (0x20 != abs(s1[i] - s2[i]))
			return false;
	}
	return true;
}

inline String replace(String &str, const String &from, const String &to)
{
	String::size_type pos = 0;
	while ((pos = str.find(from, pos)) != -1) {
		str.replace(pos, from.length(), to);
		pos += to.length();
	}
	return str;
}

inline void swap(String &ls, String &rs)
{
	String temp(ls);
	ls = rs;
	rs = temp;
}

inline String operator+(const char *ls, const String &rs)
{
	String buf(ls);
	buf += rs;
	return buf;
}

inline BOOL operator==(const char *ls, const String &rs)
{
	return !rs.compare(ls);
}

inline BOOL operator==(const String &ls, const char *rs)
{
	return !ls.compare(rs);
}

} // namespace thefox

#endif // _THEFOX_STRING_UTIL_H_