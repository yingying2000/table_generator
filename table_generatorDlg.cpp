
// table_generatorDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "table_generator.h"
#include "table_generatorDlg.h"
#include "afxdialogex.h"
#include "tag.h"
#include "customer.h"
#include "resource.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtablegeneratorDlg 对话框



CtablegeneratorDlg::CtablegeneratorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TABLE_GENERATOR_DIALOG, pParent)
	, bool_top1(FALSE)
	, bool_top2(FALSE)
	, bool_btm1(FALSE)
	, bool_btm2(FALSE)
	, bool_btm3(FALSE)
	, bool_mean(FALSE)
	, highest_point(0)
	, input_file(_T(""))
	, bool_sig(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtablegeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, bool_top1);
	DDX_Check(pDX, IDC_CHECK2, bool_top2);
	DDX_Check(pDX, IDC_CHECK3, bool_btm1);
	DDX_Check(pDX, IDC_CHECK4, bool_btm2);
	DDX_Check(pDX, IDC_CHECK5, bool_btm3);
	DDX_Check(pDX, IDC_CHECK6, bool_mean);
	DDX_Text(pDX, IDC_EDIT2, highest_point);
	//  DDX_Text(pDX, IDC_MFCEDITBROWSE1, input_file);
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, input_file);
	DDX_Check(pDX, IDC_CHECK7, bool_sig);
}

BEGIN_MESSAGE_MAP(CtablegeneratorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CtablegeneratorDlg::OnBnClickedOk)
//	ON_WM_CTLCOLOR()
ON_WM_CTLCOLOR()
//ON_BN_CLICKED(IDC_CHECK3, &CtablegeneratorDlg::OnBnClickedCheck3)
END_MESSAGE_MAP()


// CtablegeneratorDlg 消息处理程序

BOOL CtablegeneratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_CHECK6))->SetCheck(BST_CHECKED);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtablegeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtablegeneratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtablegeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void generate_top1(vector<Tag*>::iterator& q_iter, vector<Tag*>& tags, vector<Customer*>& customers, ostream& fout,
	string& question, int& population, bool is_first_choice) {
	if (is_first_choice) { 
		fout << (*q_iter)->get_name(); 
	}
	else { fout << "  "; }
	fout << ",";
	fout << "Top1,";
	//Top1总数
	int max_point = customers[0]->check_max_point();
	for (int i = 0; i < (*q_iter)->get_size(); i++) {
		if ((*q_iter)->get_value(i) == to_string(max_point)) {
			double total = (*q_iter)->get_repeat_count(i);
			int percentage = total * 100.0 / (double) population + 0.5;
			fout << percentage;
			break;
		}
		else {
			fout << "0";
		}
	}
	//遍历标签
	vector<Tag*>::iterator iter_tag;
	for (iter_tag = tags.begin(); iter_tag != tags.end(); ++iter_tag) {
		//遍历到Question跳过
		if ((*iter_tag)->if_question(max_point)) {
			continue;
		}
		//遍历有意义标签
		if ((*iter_tag)->get_name() != "UID" &&
			(*iter_tag)->get_name() != "\xD3\xC3\xBB\xA7\xC3\xFB" &&
			(*iter_tag)->get_name() != "\xB3\xC7\xCA\xD0" &&
			(*iter_tag)->get_name() != "\xD7\xB4\xCC\xAC") {
			//遍历单个标签的每个特征
			for (int i = 0; i < (*iter_tag)->get_size(); i++) {
				string tag_name = (*iter_tag)->get_name();
				string tag_value = (*iter_tag)->get_value(i);
				//遍历每个客户信息
				int count = 0;
				vector<Customer*>::iterator iter_tag_cus;
				for (iter_tag_cus = customers.begin(); iter_tag_cus != customers.end();
					++iter_tag_cus) {
					if ((*iter_tag_cus)->comp_Top1(question) &&
						(*iter_tag_cus)->check_tag(tag_name, tag_value)) {
						++count;
					}
				}
				int percentage = count * 100.0 / (*iter_tag)->get_repeat_count(i) + 0.5;
				fout << "," << percentage;
			}
		}
	}
}

void generate_top2(vector<Tag*>::iterator& q_iter, vector<Tag*>& tags, vector<Customer*>& customers, ostream& fout,
	string& question, int& population, bool is_first_choice) {
	if (is_first_choice) {
		fout << (*q_iter)->get_name();
	}
	else { fout << "  "; }
	fout << ",";

	fout << "Top2,";
	//Top2总数
	int max_point = customers[0]->check_max_point();
	int count_top2 = 0;
	for (int i = 0; i < (*q_iter)->get_size(); i++) {
		if ((*q_iter)->get_value(i) == to_string(max_point) ||
			(*q_iter)->get_value(i) == to_string(max_point - 1)) {
			count_top2 += (*q_iter)->get_repeat_count(i);
		}
	}
	double total = count_top2;
	int percentage = total * 100.0 / (double)population + 0.5;
	fout << percentage;
	//遍历标签
	vector<Tag*>::iterator iter_tag;
	for (iter_tag = tags.begin(); iter_tag != tags.end(); ++iter_tag) {
		//遍历到Question跳过
		if ((*iter_tag)->if_question(max_point)) {
			continue;
		}
		//遍历有意义标签
		if ((*iter_tag)->get_name() != "UID" &&
			(*iter_tag)->get_name() != "\xD3\xC3\xBB\xA7\xC3\xFB" &&
			(*iter_tag)->get_name() != "\xB3\xC7\xCA\xD0" &&
			(*iter_tag)->get_name() != "\xD7\xB4\xCC\xAC") {
			//遍历单个标签的每个特征
			for (int i = 0; i < (*iter_tag)->get_size(); i++) {
				string tag_name = (*iter_tag)->get_name();
				string tag_value = (*iter_tag)->get_value(i);
				//遍历每个客户信息
				int count = 0;
				vector<Customer*>::iterator iter_tag_cus;
				for (iter_tag_cus = customers.begin(); iter_tag_cus != customers.end();
					++iter_tag_cus) {
					if ((*iter_tag_cus)->comp_Top2(question) &&
						(*iter_tag_cus)->check_tag(tag_name, tag_value)) {
						++count;
					}
				}
				int percentage = count * 100.0 / (*iter_tag)->get_repeat_count(i) + 0.5;
				fout << "," << percentage;
			}
		}
	}
}

void generate_btm1(vector<Tag*>::iterator& q_iter, vector<Tag*>& tags, vector<Customer*>& customers, ostream& fout,
	string& question, int& population, bool is_first_choice) {
	if (is_first_choice) {
		fout << (*q_iter)->get_name();
	}
	else { fout << "  "; }
	fout << ",";
	fout << "Btm1,";
	//Btm1总数
	int max_point = customers[0]->check_max_point();
	int count_btm1 = 0;
	for (int i = 0; i < (*q_iter)->get_size(); i++) {
		if ((*q_iter)->get_value(i) == "1") {
			count_btm1 += (*q_iter)->get_repeat_count(i);
		}
	}
	double total = count_btm1;
	int percentage = total * 100.0 / (double)population + 0.5;
	fout << percentage;
	//遍历标签
	vector<Tag*>::iterator iter_tag;
	for (iter_tag = tags.begin(); iter_tag != tags.end(); ++iter_tag) {
		//遍历到Question跳过
		if ((*iter_tag)->if_question(max_point)) {
			continue;
		}
		//遍历有意义标签
		if ((*iter_tag)->get_name() != "UID" &&
			(*iter_tag)->get_name() != "\xD3\xC3\xBB\xA7\xC3\xFB" &&
			(*iter_tag)->get_name() != "\xB3\xC7\xCA\xD0" &&
			(*iter_tag)->get_name() != "\xD7\xB4\xCC\xAC") {
			//遍历单个标签的每个特征
			for (int i = 0; i < (*iter_tag)->get_size(); i++) {
				string tag_name = (*iter_tag)->get_name();
				string tag_value = (*iter_tag)->get_value(i);
				//遍历每个客户信息
				int count = 0;
				vector<Customer*>::iterator iter_tag_cus;
				for (iter_tag_cus = customers.begin(); iter_tag_cus != customers.end();
					++iter_tag_cus) {
					if ((*iter_tag_cus)->comp_Btm1(question) &&
						(*iter_tag_cus)->check_tag(tag_name, tag_value)) {
						++count;
					}
				}
				int percentage = count * 100.0 / (*iter_tag)->get_repeat_count(i) + 0.5;
				fout << "," << percentage;
			}
		}
	}
}

void generate_btm2(vector<Tag*>::iterator& q_iter, vector<Tag*>& tags, vector<Customer*>& customers, ostream& fout,
	string& question, int& population, bool is_first_choice) {
	if (is_first_choice) {
		fout << (*q_iter)->get_name();
	}
	else { fout << "  "; }
	fout << ",";
	fout << "Btm2,";
	//Btm2总数
	int max_point = customers[0]->check_max_point();
	int count_btm2 = 0;
	for (int i = 0; i < (*q_iter)->get_size(); i++) {
		if ((*q_iter)->get_value(i) == "1" ||
			(*q_iter)->get_value(i) == "2") {
			count_btm2 += (*q_iter)->get_repeat_count(i);
		}
	}
	double total = count_btm2;
	int percentage = total * 100.0 / (double)population + 0.5;
	fout << percentage;
	//遍历标签
	vector<Tag*>::iterator iter_tag;
	for (iter_tag = tags.begin(); iter_tag != tags.end(); ++iter_tag) {
		//遍历到Question跳过
		if ((*iter_tag)->if_question(max_point)) {
			continue;
		}
		//遍历有意义标签
		if ((*iter_tag)->get_name() != "UID" &&
			(*iter_tag)->get_name() != "\xD3\xC3\xBB\xA7\xC3\xFB" &&
			(*iter_tag)->get_name() != "\xB3\xC7\xCA\xD0" &&
			(*iter_tag)->get_name() != "\xD7\xB4\xCC\xAC") {
			//遍历单个标签的每个特征
			for (int i = 0; i < (*iter_tag)->get_size(); i++) {
				string tag_name = (*iter_tag)->get_name();
				string tag_value = (*iter_tag)->get_value(i);
				//遍历每个客户信息
				int count = 0;
				vector<Customer*>::iterator iter_tag_cus;
				for (iter_tag_cus = customers.begin(); iter_tag_cus != customers.end();
					++iter_tag_cus) {
					if ((*iter_tag_cus)->comp_Btm2(question) &&
						(*iter_tag_cus)->check_tag(tag_name, tag_value)) {
						++count;
					}
				}
				int percentage = count * 100.0 / (*iter_tag)->get_repeat_count(i) + 0.5;
				fout << "," << percentage;
			}
		}
	}
}

void generate_btm3(vector<Tag*>::iterator& q_iter, vector<Tag*>& tags, vector<Customer*>& customers, ostream& fout,
	string& question, int& population, bool is_first_choice) {
	if (is_first_choice) {
		fout << (*q_iter)->get_name();
	}
	else { fout << "  "; }
	fout << ",";
	fout << "Btm3,";
	//Btm3总数
	int max_point = customers[0]->check_max_point();
	int count_btm3 = 0;
	for (int i = 0; i < (*q_iter)->get_size(); i++) {
		if ((*q_iter)->get_value(i) == "1" ||
			(*q_iter)->get_value(i) == "2" ||
			(*q_iter)->get_value(i) == "3") {
			count_btm3 += (*q_iter)->get_repeat_count(i);
		}
	}
	double total = count_btm3;
	int percentage = total * 100.0 / (double)population + 0.5;
	fout << percentage;
	//遍历标签
	vector<Tag*>::iterator iter_tag;
	for (iter_tag = tags.begin(); iter_tag != tags.end(); ++iter_tag) {
		//遍历到Question跳过
		if ((*iter_tag)->if_question(max_point)) {
			continue;
		}
		//遍历有意义标签
		if ((*iter_tag)->get_name() != "UID" &&
			(*iter_tag)->get_name() != "\xD3\xC3\xBB\xA7\xC3\xFB" &&
			(*iter_tag)->get_name() != "\xB3\xC7\xCA\xD0" &&
			(*iter_tag)->get_name() != "\xD7\xB4\xCC\xAC") {
			//遍历单个标签的每个特征
			for (int i = 0; i < (*iter_tag)->get_size(); i++) {
				string tag_name = (*iter_tag)->get_name();
				string tag_value = (*iter_tag)->get_value(i);
				//遍历每个客户信息
				int count = 0;
				vector<Customer*>::iterator iter_tag_cus;
				for (iter_tag_cus = customers.begin(); iter_tag_cus != customers.end();
					++iter_tag_cus) {
					if ((*iter_tag_cus)->comp_Btm3(question) &&
						(*iter_tag_cus)->check_tag(tag_name, tag_value)) {
						++count;
					}
				}
				int percentage = count * 100.0 / (*iter_tag)->get_repeat_count(i) + 0.5;
				fout << "," << percentage;
			}
		}
	}
}

void generate_mean(vector<Tag*>::iterator& q_iter, vector<Tag*>& tags, vector<Customer*>& customers, int& sample_size, ostream& fout,
	string& question, bool is_first_choice) {
	if (is_first_choice) {
		fout << (*q_iter)->get_name();
	}
	else { fout << "  "; }
	fout << ",";
	fout << "Mean,";
	//一个题目的mean
	int max_point = customers[0]->check_max_point();
	int sum = 0;
	for (int i = 0; i < (*q_iter)->get_size(); i++) {
		sum += stoi((*q_iter)->get_value(i)) * (*q_iter)->get_repeat_count(i);
	}
	double mean = (double)sum / (double)sample_size;
	fout << setprecision(3) << mean;
	//遍历标签
	vector<Tag*>::iterator iter_tag;
	for (iter_tag = tags.begin(); iter_tag != tags.end(); ++iter_tag) {
		//遍历到Question跳过
		if ((*iter_tag)->if_question(max_point)) {
			continue;
		}
		//遍历有意义标签
		if ((*iter_tag)->get_name() != "UID" &&
			(*iter_tag)->get_name() != "\xD3\xC3\xBB\xA7\xC3\xFB" &&
			(*iter_tag)->get_name() != "\xB3\xC7\xCA\xD0" &&
			(*iter_tag)->get_name() != "\xD7\xB4\xCC\xAC") {
			//遍历单个标签的每个特征
			for (int i = 0; i < (*iter_tag)->get_size(); i++) {
				string tag_name = (*iter_tag)->get_name();
				string tag_value = (*iter_tag)->get_value(i);
				int point_sum = 0;
				//遍历每个客户信息
				vector<Customer*>::iterator iter_tag_cus;
				for (iter_tag_cus = customers.begin(); iter_tag_cus != customers.end();
					++iter_tag_cus) {
					if ((*iter_tag_cus)->check_tag(tag_name, tag_value)) {
						point_sum += (*iter_tag_cus)->check_question_answer((*q_iter)->get_name());
					}
				}
				double point_average = (double)point_sum / (double)(*iter_tag)->get_repeat_count(i);
				fout << "," << setprecision(3) << point_average;
			}
		}
	}
}

std::string escaped(const std::string& input)
{
	std::string output;
	output.reserve(input.size());
	for (const char c : input) {
		switch (c) {
		case '\a':  output += "\\a";        break;
		case '\b':  output += "\\b";        break;
		case '\f':  output += "\\f";        break;
		case '\n':  output += "\\n";        break;
		case '\r':  output += "\\r";        break;
		case '\t':  output += "\\t";        break;
		case '\v':  output += "\\v";        break;
		default:    output += c;            break;
		}
	}

	return output;
}

void CtablegeneratorDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();//更新成员变量
	int choices = bool_top1 + bool_top2 + bool_btm1 + bool_btm2 + bool_btm3 + bool_mean;

	string input_file_updated = CW2A(input_file.GetString());
	input_file_updated = escaped(input_file_updated);
	ifstream fin(input_file_updated);//打开文件

	//检查文件是否打开
	if (!fin.is_open()) {
		MessageBox(_T("Error：文件名不存在于同一文件夹或输入错误"));
		return;
	}
	
	//检查文件是否打开
	if (choices == 0) {
		MessageBox(_T("Error：请至少选择一个模块"));
		return;
	}

	//打开新文件
	string output_file;
	output_file = CW2A(input_file.GetString());
	output_file = output_file.insert(output_file.length() - 4, "_result");
	ofstream fout(output_file);
	int sample_size = 0;

	//生成标签向量
	vector<Tag*> tags;
	string first_line;
	string tag_name;
	getline(fin, first_line);
	istringstream stringIn1(first_line);
	while (getline(stringIn1, tag_name, ',')) {
		while (tag_name.back() == ' ') {
			tag_name.pop_back();
		}
		while (tag_name.front() == ' ') {
			tag_name.erase(0, 1);
		}
		tags.push_back(new Tag(tag_name));
	}

	//读取用户信息
	vector<Customer*> customers;
	string line;
	string val;
	while (getline(fin, line)) {
		Customer* CusPtr = new Customer(highest_point);
		istringstream stringIn2(line);
		int i = 0;
		while (getline(stringIn2, val, ',')) {
			while (val.back() == ' ') {
				val.pop_back();
			}
			while (val.front() == ' ') {
				val.erase(0, 1);
			}
			tags[i]->add_value(val);
			if (tags[i]->if_question(highest_point)) {
				CusPtr->add_answer_pair(tags[i]->get_name(), stoi(val));
			}
			else {
				CusPtr->add_tag_pair(tags[i]->get_name(), val);
			}
			i++;
		}
		customers.push_back(CusPtr);
		++sample_size;
	}

	//生成表头第一行
	fout << "  ,   ,   ";
	vector<Tag*>::iterator iter1;
	for (iter1 = tags.begin(); iter1 != tags.end(); ++iter1) {
		//检查是否为无意义项
		if ((*iter1)->get_name() != "UID" &&
			(*iter1)->get_name() != "\xD3\xC3\xBB\xA7\xC3\xFB" &&
			(*iter1)->get_name() != "\xB3\xC7\xCA\xD0" &&
			(*iter1)->get_name() != "\xD7\xB4\xCC\xAC") {
			//检查是否为Question
			if ((*iter1)->if_question(highest_point)) {
				continue;
			}
			fout << "," << (*iter1)->get_name();
			for (int i = 0; i < (*iter1)->get_size() - 1; i++) {
				fout << ",  ";
			}
		}
	}
	fout << endl;

	//生成表头第二行
	fout << "  ,base,total";
	vector<Tag*>::iterator iter2;
	for (iter2 = tags.begin(); iter2 != tags.end(); ++iter2) {
		if ((*iter2)->get_name() != "UID" &&
			(*iter2)->get_name() != "\xD3\xC3\xBB\xA7\xC3\xFB" &&
			(*iter2)->get_name() != "\xB3\xC7\xCA\xD0" &&
			(*iter2)->get_name() != "\xD7\xB4\xCC\xAC") {
			if ((*iter2)->if_question(highest_point)) {
				continue;
			}
			for (int i = 0; i < (*iter2)->get_size(); i++) {
				fout << "," << (*iter2)->get_value(i);
			}
		}
	}
	fout << endl;

	//生成表头第三行
	fout << "  ,  ," << sample_size;
	vector<Tag*>::iterator iter3;
	for (iter3 = tags.begin(); iter3 != tags.end(); ++iter3) {
		if ((*iter3)->get_name() != "UID" &&
			(*iter3)->get_name() != "\xD3\xC3\xBB\xA7\xC3\xFB" &&
			(*iter3)->get_name() != "\xB3\xC7\xCA\xD0" &&
			(*iter3)->get_name() != "\xD7\xB4\xCC\xAC") {
			if ((*iter3)->if_question(highest_point)) {
				continue;
			}
			fout << (*iter3)->print_repeat_count();
		}
	}
	fout << endl;

	//生成表头第四行
	fout << "  ,sig,  ";
	vector<Tag*>::iterator iter4;
	for (iter4 = tags.begin(); iter4 != tags.end(); ++iter4) {
		if ((*iter4)->get_name() != "UID" &&
			(*iter4)->get_name() != "\xD3\xC3\xBB\xA7\xC3\xFB" &&
			(*iter4)->get_name() != "\xB3\xC7\xCA\xD0" &&
			(*iter4)->get_name() != "\xD7\xB4\xCC\xAC") {
			if ((*iter4)->if_question(highest_point)) {
				continue;
			}
			fout << (*iter4)->print_sig_letter();
		}
	}
	fout << endl;

	//生成剩余表格内容
	//遍历每个问题
	vector<Tag*>::iterator q_iter;
	for (q_iter = tags.begin(); q_iter != tags.end(); ++q_iter) {
		if ((*q_iter)->if_question(highest_point)) {
			string question = ((*q_iter)->get_name());
			//根据不同表格模板生成表格
			if (bool_top1 == 1) {
				generate_top1(q_iter, tags, customers, fout, question, sample_size, 1);
				fout << endl;
			}
			if (bool_top2 == 1) {
				generate_top2(q_iter, tags, customers, fout, question, sample_size, !bool_top1);
				fout << endl;
			}
			if (bool_btm1 == 1) {
				generate_btm1(q_iter, tags, customers, fout, question, sample_size, !bool_top1 && !bool_top2);
				fout << endl;
			}
			if (bool_btm2 == 1) {
				generate_btm2(q_iter, tags, customers, fout, question, sample_size, !bool_top1 && !bool_top2 && !bool_btm1);
				fout << endl;
			}
			if (bool_btm3 == 1) {
				generate_btm3(q_iter, tags, customers, fout, question, sample_size, !bool_top1 && !bool_top2 && !bool_btm1 && !bool_btm2);
				fout << endl;
			}
			if (bool_mean == 1) {
				generate_mean(q_iter, tags, customers, sample_size, fout, question, !bool_top1 && !bool_top2 && !bool_btm1 && !bool_btm2 
					&& !bool_btm3);
				fout << endl;
			}
			fout << endl;
		}
	}

	//关闭文件
	fin.close();
	fin.clear();
	fout.close();
	fout.clear();

	//如果勾选sig
	if (bool_sig) {
		//读取刚刚输出的表格
		fin.open(output_file);
		string line1;
		string line2;
		getline(fin, line1);
		getline(fin, line2);

		//读取第三行bases
		vector<string> bases;
		string line3;
		string base;
		getline(fin, line3);
		istringstream stringIn3(line3);
		while (getline(stringIn3, base, ',')) {
			bases.push_back(base);
		}
		reverse(bases.begin(), bases.end());
		bases.pop_back();
		bases.pop_back();
		bases.pop_back();
		reverse(bases.begin(), bases.end());

		//读取第四行category
		vector<string> categories;
		string line4;
		string category;
		getline(fin, line4);
		istringstream stringIn4(line4);
		while (getline(stringIn4, category, ',')) {
			categories.push_back(category);
		}
		reverse(categories.begin(), categories.end());
		categories.pop_back();
		categories.pop_back();
		categories.pop_back();
		reverse(categories.begin(), categories.end());


		//读取剩余表格内容
		vector<vector<string> > data;
		string datum;
		string victim;
		
		while (getline(fin, victim)) {
			//跳过空行
			if (victim == "") {
				continue;
			}
			vector<string> data_line;
			istringstream stringIn5(victim);
			while (getline(stringIn5, datum, ',')) {
				data_line.push_back(datum);
			}
			reverse(data_line.begin(), data_line.end());
			data_line.pop_back();
			data_line.pop_back();
			data_line.pop_back();
			reverse(data_line.begin(), data_line.end());
			data.push_back(data_line);
		}

		//处理数据
		for (unsigned a_col = 0; a_col < bases.size() - 1; a_col++) {
			for (unsigned b_col = a_col + 1; b_col < bases.size(); b_col++) {
				//遍历到新的组别停止
				if (categories[b_col] == "A") {
					break;
				}

				int base_a = stoi(bases[a_col]);
				int base_b = stoi(bases[b_col]);
				for (unsigned row = 0; row < data.size(); row++) {
					//如果选择了mean， 则跳过mean（每个板块的最后一行）
					if (bool_mean == 1 && (row + 1) % choices == 0) {
						continue;
					}
					double per_a = stoi(data[row][a_col]) / 100.0;
					double per_b = stoi(data[row][b_col]) / 100.0;
					double p_1 = (per_a * base_a + per_b * base_b) / ((double)base_a + (double)base_b);
					//如果该行无意义，跳过该行
					if (p_1 == 0) {
						continue;
					}
					double sig = abs(per_a - per_b) / sqrt(p_1 * (1 - p_1) * (1 / (double)base_a + 1 / (double)base_b));
					if (sig > 1.96) {
						if (per_a > per_b) {
							data[row][a_col] += categories[b_col];
						}
						else {
							data[row][b_col] += categories[a_col];
						}
					}
				}
			}
		}

		//输出第二份表格
		
		string output_file_2 = output_file;
		output_file_2 = output_file_2.insert(output_file_2.length() - 4, "_with_sig");
		fout.open(output_file_2);
		fout << line1 <<endl;
		fout << line2 << endl;
		fout << line3 << endl;
		fout << line4 << endl;

		int data_iter = 0;
		for (q_iter = tags.begin(); q_iter != tags.end(); ++q_iter) {
			if ((*q_iter)->if_question(highest_point)) {
				string question = (*q_iter)->get_name();
				//根据不同表格模板生成表格
				if (bool_top1 == 1) {
					fout << question;
					fout << ",Top1,";
					//Top1总数
					int max_point = customers[0]->check_max_point();
					for (int i = 0; i < (*q_iter)->get_size(); i++) {
						if ((*q_iter)->get_value(i) == to_string(max_point)) {
							double total = (*q_iter)->get_repeat_count(i);
							int percentage = total * 100.0 / (double)sample_size + 0.5;
							fout << percentage;
							break;
						}
						else {
							fout << "0";
						}
					}
					//剩余data
					for (unsigned i = 0; i < data[0].size(); i++) {
						fout << "," << data[data_iter][i];
					}
					fout << endl;
					++data_iter;
				}
				if (bool_top2 == 1) {
					if (bool_top1) {
						fout << "  ";
					}
					else { fout << question; }
					fout << ",Top2,";
					//Top2总数
					int max_point = customers[0]->check_max_point();
					int count_top2 = 0;
					for (int i = 0; i < (*q_iter)->get_size(); i++) {
						if ((*q_iter)->get_value(i) == to_string(max_point) ||
							(*q_iter)->get_value(i) == to_string(max_point - 1)) {
							count_top2 += (*q_iter)->get_repeat_count(i);
						}
					}
					double total = count_top2;
					int percentage = total * 100.0 / (double)sample_size + 0.5;
					fout << percentage;
					//剩余data
					for (unsigned i = 0; i < data[0].size(); i++) {
						fout << "," << data[data_iter][i];
					}
					fout << endl;
					++data_iter;
				}
				if (bool_btm1 == 1) {
					if (bool_top1 || bool_top2) {
						fout << "  ";
					}
					else { fout << question; }
					fout << ",Btm1,";
					//Btm1总数
					int max_point = customers[0]->check_max_point();
					int count_btm1 = 0;
					for (int i = 0; i < (*q_iter)->get_size(); i++) {
						if ((*q_iter)->get_value(i) == "1") {
							count_btm1 += (*q_iter)->get_repeat_count(i);
						}
					}
					double total = count_btm1;
					int percentage = total * 100.0 / (double)sample_size + 0.5;
					fout << percentage;
					//剩余data
					for (unsigned i = 0; i < data[0].size(); i++) {
						fout << "," << data[data_iter][i];
					}
					fout << endl;
					++data_iter;
				}
				if (bool_btm2 == 1) {
					if (bool_top1 || bool_top2 || bool_btm1) {
						fout << "  ";
					}
					else { fout << question; }
					fout << ",Btm2,";
					//Btm2总数
					int max_point = customers[0]->check_max_point();
					int count_btm2 = 0;
					for (int i = 0; i < (*q_iter)->get_size(); i++) {
						if ((*q_iter)->get_value(i) == "1" ||
							(*q_iter)->get_value(i) == "2") {
							count_btm2 += (*q_iter)->get_repeat_count(i);
						}
					}
					double total = count_btm2;
					int percentage = total * 100.0 / (double)sample_size + 0.5;
					fout << percentage;
					//剩余data
					for (unsigned i = 0; i < data[0].size(); i++) {
						fout << "," << data[data_iter][i];
					}
					fout << endl;
					++data_iter;
				}
				if (bool_btm3 == 1) {
					if (bool_top1 || bool_top2 || bool_btm1 || bool_btm2) {
						fout << "  ";
					}
					else { fout << question; }
					fout << ",Btm3,";
					//Btm3总数
					int max_point = customers[0]->check_max_point();
					int count_btm3 = 0;
					for (int i = 0; i < (*q_iter)->get_size(); i++) {
						if ((*q_iter)->get_value(i) == "1" ||
							(*q_iter)->get_value(i) == "2" ||
							(*q_iter)->get_value(i) == "3") {
							count_btm3 += (*q_iter)->get_repeat_count(i);
						}
					}
					double total = count_btm3;
					int percentage = total * 100.0 / (double)sample_size + 0.5;
					fout << percentage;
					//剩余data
					for (unsigned i = 0; i < data[0].size(); i++) {
						fout << "," << data[data_iter][i];
					}
					fout << endl;
					++data_iter;
				}
				if (bool_mean == 1) {
					if (bool_top1 || bool_top2 || bool_btm1 || bool_btm2 || bool_btm3) {
						fout << "  ";
					}
					else { fout << question; }
					fout << ",Mean,";
					//一个题目的mean
					int max_point = customers[0]->check_max_point();
					int sum = 0;
					for (int i = 0; i < (*q_iter)->get_size(); i++) {
						sum += stoi((*q_iter)->get_value(i)) * (*q_iter)->get_repeat_count(i);
					}
					double mean = (double)sum / (double)sample_size;
					fout << setprecision(3) << mean;
					//剩余data
					for (unsigned i = 0; i < data[0].size(); i++) {
						fout << "," << data[data_iter][i];
					}
					fout << endl;
					++data_iter;
				}
				fout << endl;
			}
		}

	}

	//清除动态数据
	for (unsigned i = 0; i < customers.size(); i++) {
		delete customers[i];
	}
	for (unsigned i = 0; i < tags.size(); i++) {
		delete tags[i];
	}

	MessageBox(_T("Success！成功输出表格"));
	CDialogEx::OnOK();

}


HBRUSH CtablegeneratorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (IDC_STATIC4 == pWnd->GetDlgCtrlID()||
		IDC_STATIC8 == pWnd->GetDlgCtrlID()|| 
		IDC_STATIC9 == pWnd->GetDlgCtrlID()) {
		pDC->SetTextColor(RGB(0, 0, 255));//设置文本颜色为蓝色
		pDC->SetBkMode(OPAQUE);//设置文本背景模式为透明
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}