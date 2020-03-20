﻿
// table_generatorDlg.h: 头文件
//

#pragma once


// CtablegeneratorDlg 对话框
class CtablegeneratorDlg : public CDialogEx
{
// 构造
public:
	CtablegeneratorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABLE_GENERATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
public:
	BOOL bool_top1;
	BOOL bool_top2;
	BOOL bool_btm1;
	BOOL bool_btm2;
	BOOL bool_btm3;
	BOOL bool_mean;
	int highest_point;
	afx_msg void OnBnClickedOk();
	CString input_file;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnBnClickedCheck3();
	BOOL bool_sig;
};
