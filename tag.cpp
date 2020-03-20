

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "pch.h"

using namespace std;


Tag::Tag(string string_in)
:name(string_in){ };

string Tag::get_name() {
	return name;
}

int Tag::get_size() {
	return values.size();
}

//读取数据，更新统计结果
void Tag::add_value(string string_in) {
	vector<string>::iterator it = find(values.begin(), values.end(), string_in);
	if (it == values.end()) {
		values.push_back(string_in);
		value_repeat_count.push_back(1);
		if (string_in == "\xD2\xBB\xCF\xDF\xB3\xC7\xCA\xD0") {
			reverse(values.begin(),values.end());
			reverse(value_repeat_count.begin(), value_repeat_count.end());
		}
		if (string_in == "\x31\x38\x2D\x32\x35\xCB\xEA") {
			reverse(values.begin(), values.end());
			reverse(value_repeat_count.begin(), value_repeat_count.end());
		}
	}
	else {
		int index = distance(values.begin(), it);
		++value_repeat_count[index];
	}
}

//输出重复数量
//输出格式为“，55,66”
string Tag::print_repeat_count() {
	string init_string = "";
	for (int i = 0; i < get_size(); i++) {
		init_string += ",";
		init_string += to_string(value_repeat_count[i]);
	}
	return init_string;
}

string Tag::print_sig_letter() {
	string init_string = "";
	char ch = 'A';
	for (int i = 0; i < get_size(); i++) {
		init_string += ",";
		init_string += char(ch + i);
	}
	return init_string;
}

string Tag::get_value(int index) {
	return values[index];
}

int Tag::get_repeat_count(int index) {
	return value_repeat_count[index];
}

bool Tag::if_question(int highest_point) {
	if (get_name() == "UID" ||
		get_name() == "\xD3\xC3\xBB\xA7\xC3\xFB" ||
		get_name() == "\xB3\xC7\xCA\xD0" ||
		get_name() == "\xD7\xB4\xCC\xAC") {
		return false;
	}
	vector<string> points;
	for (int i = highest_point; i > 0; i--) {
		points.push_back(to_string(i));
	}
	for (unsigned i = 0; i < values.size(); i++) {
		vector<string>::iterator it = find(points.begin(), points.end(), values[i]);
		if (it == points.end()) {
			return false;
		}
	}
	return true;
}