#include "is.h"

int toInt(string str)
{
	return from_str<int>(str);
}

string toStr(int num)
{
	return to_str<int>(num);
}

string Is::_getInput(string str)
{
	if (str == "") {
		return _str;
	} else {
		return str;
	}
}

bool Is::number(string num)
{
	num = _getInput(num);
	if (num == "") {
		return false;
	}
	char first_char = num.at(0);
	bool sign_flag = false,
		 is_float  = false;
	if (first_char == '+' || first_char == '-') {
		sign_flag = true;
	}
	if (num.find(".") == num.rfind(".")) {
		is_float = true;
	}
	for (size_t i = 0; i != num.size(); ++i) {
		char c = num.at(i);
		if (sign_flag == true && i == 0) {
			continue;
		}
		if (c >= '0' && c <= '9') {
			continue;
		} else if (is_float == true && c == '.'){
			continue;
		} else {
			return false;
		}
	}
	return true;
}

bool Is::decimal(string num) 
{
	return number(num) == true && num.find(".") != num.npos && num.find(".") == num.rfind(".");
}

bool Is::integer(string num) {
	return number(num) == true && num.find(".") == num.npos;
}

bool Is::positive(string num)
{
	if (num == "0") {
		return false;
	}
	return !negative(num);
}

bool Is::negative(string num)
{
	if (number(num) == true) {
		if (num.at(0) == '-') {
			return true;
		}
	}
	return false;
}

bool Is::even(string num)
{
	if (number(num) == true && decimal(num) == false) {
		int even_num = toInt(num);
		if (even_num % 2 == 0) {
			return true;
		}	
	}
	return false;
}

bool Is::odd(string num)
{
	if (number(num) == true && decimal(num) == false) {
		int even_num = toInt(num);
		if (even_num % 2 != 0) {
			return true;
		}
	}
	return false;
}

bool Is::within(int min, int max, string num)
{
	if (number(num) == true) {
		int range_num = toInt(num);
		if (range_num > min && range_num < max) {
			return true;
		}
	} 
	return false;
}

bool Is::in_set(string set_str, string str)
{
	str = _getInput(str);
	if (str == "") {
		return false;
	}
	for (int i = 0; i < str.size(); ++i) {
		string tmp = str.substr(i, 1);
		if (set_str.find(tmp) == set_str.npos) {
			return false;
		}
	}
	return true;
}

bool Is::under(int upper_limit, string num)
{
	return within(std::numeric_limits<int>::min(), upper_limit, num);
}

bool Is::above(int lower_limit, string num)
{
	return within(lower_limit, std::numeric_limits<int>::max(), num);
}

bool Is::boolean(string b)
{
	b = _getInput(b);
	if (b == "") {
		return false;
	}
	to_lower(b);
	if (b == "true" || b == "false")  {
		return true;
	} else {
		return false;
	}
}

bool Is::date(string date)
{
	date = _getInput(date);
	if (date == "") {
		return false;
	}
	int idx_1st = date.find("-"),
		idx_2nd = date.rfind("-");
	int days[] = {29,31,28,31,30,31,30,31,31,30,31,30,31};
	bool is_leap_year = false;
	if (idx_1st == date.npos) {
		return false;
	}

	string year = date.substr(0, idx_1st),
		   month = date.substr(idx_1st + 1, idx_2nd - idx_1st - 1),
		   day = date.substr(idx_2nd + 1, date.size() - idx_2nd - 1);

	if (year.size() != 4 || month.size() > 2 || day.size() > 2) {
		return false;
	}

	if (positive(year) == false || positive(month) == false || positive(day) == false) {
		return false;
	}

	int tmp_year = toInt(year),
		tmp_month = toInt(month);
	if ((tmp_year % 4 == 0 && tmp_year % 100 != 0 )|| tmp_year % 400 == 0 ) {
		is_leap_year = true;
	}

	if (within(1 - 1, 12 + 1, month) == false || within(1 - 1, days[tmp_month == 2 && is_leap_year == true ? 0 : tmp_month] + 1, day) == false) {
		return false;
	}

	return true;
}

bool Is::time(string time)
{
	time = _getInput(time);
	if (time == "") {
		return false;
	}
	int idx_1st = time.find(":"),
		idx_2nd = time.rfind(":");
	if (idx_1st == time.npos) {
		return false;
	}
	string hour = time.substr(0, idx_1st),
		   minus = time.substr(idx_1st + 1, idx_2nd - idx_1st - 1),
		   second = time.substr(idx_2nd + 1, time.size() - idx_2nd - 1);
	string set = "0123456789";

	if (idx_1st == idx_2nd) {
		minus = second;
	}

	if (hour.size() > 2 || minus.size() > 2 || second.size() > 2) {
		return false;
	}

	if (in_set(set, hour) == false || in_set(set, minus) == false || in_set(set, second) == false) {
		return false;
	}

	if (!negative(hour) == false || !negative(minus) == false || !negative(second) == false) {
		return false;
	}

	if (within(0 - 1, 23 + 1, hour) == false || within(0 - 1, 59 + 1, minus) == false || within(0 - 1, 59 + 1, second) == false) {
		return false;
	}

	return true;
}

bool Is::datetime(string datetime)
{
	datetime = _getInput(datetime);
	if (datetime == "") {
		return false;
	}
	int split_idx = datetime.find(" ");
	string d = datetime.substr(0, split_idx),
		   t = datetime.substr(split_idx + 1, datetime.size() - split_idx - 1);
	return date(d) && time(t);
}
