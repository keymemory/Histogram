// HistogramView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Histogram.h"
#include "HistogramView.h"
#include "afxdialogex.h"
#include "HistogramDlg.h"


// HistogramView 대화 상자입니다.

IMPLEMENT_DYNAMIC(HistogramView, CDialogEx)

HistogramView::HistogramView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HISTOGRAM_VIEW, pParent)
	, picture1(NULL)
	, picture2(NULL)
	, maxHistogram1(0)
	, maxHistogram2(0)
	, pDC3(NULL)
	, maxHistogram3(0)
{

}

HistogramView::~HistogramView()
{
}

void HistogramView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HIMAGE1, himage1);
	DDX_Control(pDX, IDC_HIMAGE2, himage2);
	DDX_Control(pDX, IDC_HIMAGE3, himage3);
}


BEGIN_MESSAGE_MAP(HistogramView, CDialogEx)
END_MESSAGE_MAP()


// HistogramView 메시지 처리기입니다.


void HistogramView::HistogramGraph()
{
	CHistogramDlg* pDlg = (CHistogramDlg*)AfxGetMainWnd();
	image.Create(256, 256, 32);

	int value;
	CRect rect;

	MaxHistogram();

	for (int i = 0; i< 256; i++) //히스토그램 그래프 그리기
	{ // 가로

		// 값 계산
		value = (int)(((float)pDlg->histogram1[i] / maxHistogram1) * 255);

		for (int j = 0; j<256; j++)
		{ // 높이
			if (value > 0)
			{
				image.SetPixel(i, 255 - j, RGB(255, 255, 255)); //255-j = 밑에서 부터 올라가기 위해서 
				//SetPixel(x,y,rgb)
				value--;
			}
			else
				image.SetPixel(i, 255 - j, RGB(0, 0, 0));
		}
	}

	himage1.GetClientRect(&rect);
	pDC3 = himage1.GetDC();
	image.Draw(pDC3->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, 256, 256);

	for (int i = 0; i<256; i++)
	{
		value = (int)(((float)pDlg->histogram2[i] / maxHistogram2) * 255);

		for (int j = 0; j<256; j++)
		{
			if (value > 0)
			{
				image.SetPixel(i, 255 - j, RGB(255, 255, 255));
				value--;
			}
			else
				image.SetPixel(i, 255 - j, RGB(0, 0, 0));
		}
	}

	himage2.GetClientRect(&rect);
	pDC3 = himage2.GetDC();
	image.Draw(pDC3->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, 256, 256);

	for (int i = 0; i<256; i++)
	{
		value = (int)(((float)pDlg->histogram4[i] / maxHistogram3) * 255);

		for (int j = 0; j<256; j++)
		{
			if (value > 0)
			{
				image.SetPixel(i, 255 - j, RGB(255, 255, 255));
				value--;
			}
			else
				image.SetPixel(i, 255 - j, RGB(0, 0, 0));
		}
	}

	himage3.GetClientRect(&rect);
	pDC3 = himage3.GetDC();
	image.Draw(pDC3->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, 256, 256);

}


void HistogramView::MaxHistogram()
{
	CHistogramDlg* pDlg = (CHistogramDlg*)AfxGetMainWnd();

	maxHistogram1 = pDlg->histogram1[0];
	maxHistogram2 = pDlg->histogram2[0];
	maxHistogram3 = pDlg->histogram4[0];

	for (int i = 1; i < 256; i++)
	{
		maxHistogram1 = maxHistogram1 > pDlg->histogram1[i] ? maxHistogram1 : pDlg->histogram1[i];
		maxHistogram2 = maxHistogram2 > pDlg->histogram2[i] ? maxHistogram2 : pDlg->histogram2[i];
		maxHistogram3 = maxHistogram3 > pDlg->histogram4[i] ? maxHistogram3 : pDlg->histogram4[i];
	}
}
