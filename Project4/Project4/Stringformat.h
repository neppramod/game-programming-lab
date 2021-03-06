#pragma once

// Reference: http://www.cplusplus.com/faq/sequences/strings/trim/
// Retrieved: 09/01/15
// This file is used to trim string

#include <string>

inline std::string trim_right_copy(
	const std::string& s,
	const std::string& delimiters = " \f\n\r\t\v")
{
	return s.substr(0, s.find_last_not_of(delimiters) + 1);
}

inline std::string trim_left_copy(
	const std::string& s,
	const std::string& delimiters = " \f\n\r\t\v")
{
	std::cout << s;
	return s.substr(s.find_first_not_of(delimiters));
}

inline std::string trim_copy(
	const std::string& s,
	const std::string& delimiters = " \f\n\r\t\v")
{
	return trim_left_copy(trim_right_copy(s, delimiters), delimiters);
}