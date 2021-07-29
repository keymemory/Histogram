#pragma once
#include "afxwin.h"
#include "atlimage.h"


// HistogramView 대화 상자입니다.

class HistogramView : public CDialogEx
{
	DECLARE_DYNAMIC(HistogramView)

public:
	HistogramView(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~HistogramView();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTOGRAM_VIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void HistogramGraph();
	void MaxHistogram();

	CStatic himage1;
	CStatic himage2;
	CStatic himage3;

	CImage image;

	int** picture1;
	int** picture2;

	int maxHistogram1;
	int maxHistogram2;
	int maxHistogram3;

	CDC* pDC3;
};
