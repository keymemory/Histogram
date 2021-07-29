
// HistogramDlg.h : 헤더 파일
//

#pragma once
#include "stdafx.h"
#include "HistogramView.h"
#include "afxwin.h"
#include "atlimage.h"


// CHistogramDlg 대화 상자
class CHistogramDlg : public CDialogEx
{
// 생성입니다.
public:
	CHistogramDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTOGRAM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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

	//높이 넓이
	int width;
	int height;

	//히스토그램 저장 배열
	int histogram1[256];
	int histogram2[256];
	int histogram3[256];
	int histogram4[256];

	int accHistogram1[256];
	int accHistogram2[256];

	//YCbCr 저장 배열
	int** y;
	int** cb;
	int** cr;

	//HSI 저장 배열
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
