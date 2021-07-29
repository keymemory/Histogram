
// HistogramDlg.h : ��� ����
//

#pragma once
#include "stdafx.h"
#include "HistogramView.h"
#include "afxwin.h"
#include "atlimage.h"


// CHistogramDlg ��ȭ ����
class CHistogramDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CHistogramDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTOGRAM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButton1();
	afx_msg void OnClickedButton2();
	afx_msg void OnClickedButton3();
	CStatic image1;
	CStatic image2;
	CStatic image3;

	CImage cimage1;
	CImage cimage2;

	CDC* mpDC1;
	CDC* mpDC2;
	CDC* mpDC3;

	BOOL mbImg;

	//���� ����
	int width;
	int height;

	//������׷� ���� �迭
	int histogram1[256];
	int histogram2[256];
	int histogram3[256];
	int histogram4[256];

	int accHistogram1[256];
	int accHistogram2[256];

	//YCbCr ���� �迭
	int** y;
	int** cb;
	int** cr;

	//HSI ���� �迭
	double** h;
	double** i;
	double** s;

	bool m_histogramGraph;
	bool m_filTer;

	HistogramView* m_dlgUnitTable;
	
	
	
	int Cliping(double value);
	void HistogramYCbCr();
	void HistogramHSI();
};
