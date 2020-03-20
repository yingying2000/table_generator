#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Tag {
public:
	Tag(string string_in);

	string get_name();

	int get_size();

	//��ȡ���ݣ�����ͳ�ƽ��
	void add_value(string string_in);

	//����ظ�����
	//�����ʽΪ����55,66��
	string print_repeat_count();

	string print_sig_letter();

	string get_value(int index);

	int get_repeat_count(int index);

	bool if_question(int highest_point);

private:
	string name;
	vector<string> values;
	vector<int> value_repeat_count;
};