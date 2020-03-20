#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>


#include "pch.h"

using namespace std;

//constructor
Customer::Customer(int point_max_in) 
:point_max(point_max_in){};

//增加新的tag pair
void Customer::add_tag_pair(string key, string value) {
	pair<string, string> pair1;
	pair1.first = key;
	pair1.second = value;
	tags.push_back(pair1);
}

//增加新的answer pair
void Customer::add_answer_pair(string key, int value) {
	pair<string, int> pair1;
	pair1.first = key;
	pair1.second = value;
	answers.push_back(pair1);
}

//自定义比较函数
bool Customer::comp_Top1(string question) {
	for (unsigned i = 0; i < answers.size(); i++) {
		if (answers[i].first == question &&
			answers[i].second == point_max) {
			return true;
		}
	}
	return false;
}

bool Customer::comp_Top2(string question) {
	for (unsigned i = 0; i < answers.size(); i++) {
		if (answers[i].first == question &&
			answers[i].second >= point_max - 1) {
			return true;
		}
	}
	return false;
}

bool Customer::comp_Btm1(string question) {
	for (unsigned i = 0; i < answers.size(); i++) {
		if (answers[i].first == question) {
			if (answers[i].second == 1) {
				return true;
			}
		}
	}
	return false;
}

bool Customer::comp_Btm2(string question) {
	for (unsigned i = 0; i < answers.size(); i++) {
		if (answers[i].first == question) {
			if (answers[i].second <= 2) {
				return true;
			}
		}
	}
	return false;
}

bool Customer::comp_Btm3(string question) {
	for (unsigned i = 0; i < answers.size(); i++) {
		if (answers[i].first == question) {
			if (answers[i].second <= 3) {
				return true;
			}
		}
	}
	return false;
}

//输入tag，tag_value, question, comparator
//如果两个都符合则输出true
bool Customer::check_tag(string tag, string tag_value) {
	for (unsigned i = 0; i < tags.size(); i++) {
		if (tags[i].first == tag && tags[i].second == tag_value) {
			return true;
		}
	}
	return false;
}

int Customer::check_question_answer(string tag) {
	for (unsigned i = 0; i < answers.size(); i++) {
		if (answers[i].first == tag) {
			return answers[i].second;
		}
	}
	return 0;
}

int Customer::check_max_point() {
	return point_max;
}