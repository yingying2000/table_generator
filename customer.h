#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Customer {
public:
	Customer(int max_point_in);

	//增加新的tag pair
	void add_tag_pair(string key, string value);

	//增加新的answer pair
	void add_answer_pair(string key, int value);

	//自定义比较函数
	bool comp_Top1(string question);

	bool comp_Top2(string question);

	bool comp_Btm1(string question);

	bool comp_Btm2(string question);

	bool comp_Btm3(string question);

	//输入tag，tag_value, question, comparator
	//如果两个都符合则输出true
	bool check_tag(string tag, string tag_value);

	int check_question_answer(string tag);

	int check_max_point();

private:
	vector<pair<string, string>> tags;
	vector<pair<string, int>> answers;
	int point_max;
};