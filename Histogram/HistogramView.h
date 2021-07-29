#pragma once
#include "afxwin.h"
#include "atlimage.h"


// HistogramView ��ȭ �����Դϴ�.

class HistogramView : public CDialogEx
{
	DECLARE_DYNAMIC(HistogramView)

public:
	HistogramView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~HistogramView();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTOGRAM_VIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
