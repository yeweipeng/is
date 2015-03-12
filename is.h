#ifndef _IS_H_
#define _IS_H_
#include <string>
#include <iostream>
#include <sstream>
#include <boost/regex.hpp>
using namespace std;

template<typename T> std::string to_str(const T& t)
{
	std::ostringstream s;
	s << t;
	return s.str();
}

template<typename T> T from_str(const std::string& s)
{
	std::istringstream is(s);
	T t;
	is >> t;
	return t;
}

inline void to_upper(string& str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
}

inline void to_lower(string& str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
}
 
class Is {
	public:
		Is(const char* str) : _str(str) {};
		Is(string str = "") : _str(str) {};

		bool number(string num = "");
		bool decimal(string num = "");
		bool integer(string num = "");
		bool even(string num = "");
		bool odd(string num = "");
		bool positive(string num = "");
		bool negative(string num = "");
		bool within(int min, int max, string num = "");
		bool in_set(string set_str, string str = "");
		bool under(int upper_limit, string num = "");
		bool above(int lower_limit, string num = "");

		bool boolean(string b = "");
		bool date(string date = "");
		bool time(string time = "");
		bool datetime(string datetime = "");
	private:
		string _str;
	private:
		string _getInput(string str);
};

#endif
