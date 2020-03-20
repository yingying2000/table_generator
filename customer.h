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

	//�����µ�tag pair
	void add_tag_pair(string key, string value);

	//�����µ�answer pair
	void add_answer_pair(string key, int value);

	//�Զ���ȽϺ���
	bool comp_Top1(string question);

	bool comp_Top2(string question);

	bool comp_Btm1(string question);

	bool comp_Btm2(string question);

	bool comp_Btm3(string question);

	//����tag��tag_value, question, comparator
	//������������������true
	bool check_tag(string tag, string tag_value);

	int check_question_answer(string tag);

	int check_max_point();

private:
	vector<pair<string, string>> tags;
	vector<pair<string, int>> answers;
	int point_max;
};