
// HistogramDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Histogram.h"
#include "HistogramDlg.h"
#include "afxdialogex.h"
#include "HistogramView.h"

#define M_PI 3.14159265358979353846

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CHistogramDlg 대화 상자



CHistogramDlg::CHistogramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HISTOGRAM_DIALOG, pParent)
	, mpDC1(NULL)
	, mpDC2(NULL)
	, mpDC3(NULL)
	, mbImg(false)
	, width(0)
	, height(0)
	, y(NULL)
	, i(NULL)
	, s(NULL)
	, m_histogramGraph(false)
	, m_filTer(false)
	, m_dlgUnitTable(NULL)
	, h(NULL)
	, cb(NULL)
	, cr(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE1, image1);
	DDX_Control(pDX, IDC_IMAGE2, image2);
	DDX_Control(pDX, IDC_IMAGE3, image3);
}

BEGIN_MESSAGE_MAP(CHistogramDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHistogramDlg::OnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CHistogramDlg::OnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CHistogramDlg::OnClickedButton3)
END_MESSAGE_MAP()


// CHistogramDlg 메시지 처리기

BOOL CHistogramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CHistogramDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CHistogramDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CHistogramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CHistogramDlg::Cliping(double value)
{
	if (value < 0)				// value 그림 밝기
		return 0;
	else if (256 <= value)
		return 255;
	return (int)value;
}

void CHistogramDlg::HistogramYCbCr()
{
	memset(histogram1, 0, sizeof(histogram1)); // 히스토그램 빈도수 256개를 불러오는것
	memset(histogram2, 0, sizeof(histogram2)); // 겹치면 안되니까 배열초기화를 계속해주어야함.

	memset(accHistogram1, 0, sizeof(accHistogram1));

	//YCbCr 저장 배열 포인터로 저장해서 메모리 동적 할당
	y = new int*[height];
	cb = new int*[height];
	cr = new int*[height];

	for (int i = 0; i < height; i++)
	{
		y[i] = new int[width];
		cb[i] = new int[width];
		cr[i] = new int[width];
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//GetPixel(x,y)
			COLORREF color = cimage1.GetPixel(j, i); //원본이미지.갯픽셀얻어옴
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			y[i][j] = Cliping((r * 0.299) + (g * 0.587) + (b * 0.114));   //밝기
			cb[i][j] = Cliping((r * -0.16874) + (g * -0.33126) + (b * 0.5) + 128); //색상값들, R-Y
			cr[i][j] = Cliping((r * 0.5) + (g * -0.41869) + (b * -0.08131) + 128); //색상값들, B-Y
																				   //rgb 를 ycbcr 로 바꾸는 공식
			histogram1[y[i][j]]++; // 히스토그램 빈도수
		}
	}

	accHistogram1[0] = histogram1[0]; // 0값 넣어서 초기화 * 꾸준히 해줘야함

	for (int i = 1; i < 256; i++)
		accHistogram1[i] = histogram1[i] + accHistogram1[i - 1]; //누적빈도수


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			double temp = accHistogram1[y[i][j]] * 255 / (width * height);

			int R = Cliping((temp + 1.402 * (cr[i][j] - 128))); //ycbcr 을 r로 바꾸는
			int G = Cliping((temp + (cb[i][j] - 128) * -0.34414 + (cr[i][j] - 128) * -0.71414)); // g
			int B = Cliping((temp + 1.772 * (cb[i][j] - 128))); // b

			cimage2.SetPixel(j, i, RGB(R, G, B)); //배열로 따진 히스토그램을 픽셀로 나타내기 위해  j i 위치 바뀜

											   //변환 된 히스토그램 기록
			histogram2[Cliping(temp)]++; // 바뀐 히스토그램의 빈도수
		}
	}
}


void CHistogramDlg::HistogramHSI()
{
	memset(histogram3, 0, sizeof(histogram3)); // 히스토그램 빈도수 256개를 0으로 초기화
	memset(histogram4, 0, sizeof(histogram4));

	// 누적 히스토그램 빈도수
	memset(accHistogram2, 0, sizeof(accHistogram2));

	double minimum, radian, cosine;//HSI 공식 필요 변수
	double radianTheta1, radianTheta2;
	// 0도 빨강, 60도 노랑, 120도 녹색, 240도 파랑

	//HSI 저장 배열 포인터로 저장해서 메모리 동적 할당
	h = new double*[height];
	i = new double*[height];
	s = new double*[height];

	for (int x = 0; x < height; x++)
	{
		h[x] = new double[width];
		i[x] = new double[width];
		s[x] = new double[width];
	}

	// RGB -> HSI
	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < width; y++)
		{
			double H, S, I;
			COLORREF color = cimage1.GetPixel(y, x); //원본이미지.갯픽셀얻어옴
			double r = GetRValue(color) / 255.0;
			double g = GetGValue(color) / 255.0;
			double b = GetBValue(color) / 255.0;
			I = (r + g + b) / 3.0;//i는 명도값.

			if ((r == g) && (r == b))
			{//만약 RGB값이 서로 같다면
				S = 0.0;
				H = 0.0;
			}
			else
			{
				minimum = r;//RGB중 값이 가장 낮은것을 찾습니다.
				if (g < minimum)
					minimum = g;
				if (b < minimum)
					minimum = b;
				S = 1.0 - (3.0 / (r + g + b)) * minimum;//S구하는 공식.

														//h구하는 공식
				cosine = (r - 0.5 * (g + b)) / sqrt((r - g) * (r - g) + (r - b) * (g - b));
				radian = acos(cosine);
				H = 180.0 / M_PI * radian;

				if (b > g)
					H = 360.0 - H;

			}

			h[x][y] = H; //색상값들
			s[x][y] = S; //색상값들
			i[x][y] = I; //밝기

			histogram3[(int)(i[x][y] * 255.0)]++; //빈도수
		}
	}

	int numberofPixels;//HSI 누적 히스토그램 구하기
	int sum;
	double scale;

	numberofPixels = width*height;
	sum = 0;
	scale = 255.0 / numberofPixels;

	for (int x = 0; x<256; x++)
	{
		sum += histogram3[x];
		accHistogram2[x] = (int)(sum * scale + 0.5);
	}

	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < width; y++)
		{
			i[x][y] = (double)(accHistogram2[(int)(i[x][y] * 255.0)]) / 255.0;
		}
	}

	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < width; y++)
		{
			histogram4[(int)(i[x][y] * 255.0)]++;
		}
	}

	// HSI -> RGB
	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < width; y++)
		{
			double r, g, b;
			double H, S, I;
			H = h[x][y];
			S = s[x][y];
			I = i[x][y];

			if (I == 0.0)// i의 값, 명도가 0이라면 어두운것이니.
			{
				r = g = b = 0.0;//rgb가 어두운 0이 된다.
			}
			else
			{
				if (S == 0.0)//채도가 0 이라면 무채색이므로
				{
					r = g = b = I;//rgb를 전부다 동일한 채도값으로 세팅.
				}
				else
				{
					if (H < 0.0) //색상값이 음수라면
						H += 360.0;// 색상값에 360을 더해준다.
					if (H <= 120.0)//만약 h값이 120도 이내라면 1차식을 적용.
					{
						radianTheta1 = M_PI / 180.0 * H;
						radianTheta2 = M_PI / 180.0 * (60.0 - H);
						b = (1.0 - S) / 3.0;
						r = (1.0 + S * cos(radianTheta1) / cos(radianTheta2)) / 3.0;
						g = 1.0 - (r + b);
					}
					else if (H <= 240.0)//2차식
					{
						H -= 120.0;
						radianTheta1 = M_PI / 180.0 * H;
						radianTheta2 = M_PI / 180.0 * (60.0 - H);
						r = (1.0 - S) / 3.0;
						g = (1.0 + S * cos(radianTheta1) / cos(radianTheta2)) / 3.0;
						b = 1.0 - (r + g);
					}
					else//그게아니라면 3차식
					{
						H -= 240.0;
						radianTheta1 = M_PI / 180.0 * H;
						radianTheta2 = M_PI / 180.0 * (60.0 - H);
						g = (1.0 - S) / 3.0;
						b = (1.0 + S * cos(radianTheta1) / cos(radianTheta2)) / 3.0;
						r = 1.0 - (g + b);
					}
					//추가 계산 과정
					r *= 3.0 * I; g *= 3.0 * I; b *= 3.0 * I;


					//r,g,b,i,s는 0~1사이의 값을 가짐.
					if (r < 0.0) r = 0.0;//rgb값들이 0보다 작다면 0으로
					if (g < 0.0) g = 0.0;
					if (b < 0.0) b = 0.0;
					if (r > 1.0) r = 1.0;//1보다 크다면 1로
					if (g > 1.0) g = 1.0;
					if (b > 1.0) b = 1.0;
				}
			}

			int R = (int)(255.0 * r);
			int G = (int)(255.0 * g);
			int B = (int)(255.0 * b);

			cimage2.SetPixel(y, x, RGB(R, G, B)); //배열로 따진 히스토그램을 픽셀로 나타내기 위해  j i 위치 바뀜

											   //변환 된 히스토그램 기록

		}
	}
}

void CHistogramDlg::OnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 초기화
	memset(histogram1, 0, sizeof(histogram1)); // 히스토그램 빈도수 256개를 불러오는것
	memset(histogram2, 0, sizeof(histogram2)); // 겹치면 안되니까 배열초기화를 계속해주어야함.
	memset(histogram3, 0, sizeof(histogram3));
	memset(histogram4, 0, sizeof(histogram4));


	if (mpDC1 != NULL) {
		mpDC1->DeleteDC(); //DC를 초기화
		mpDC2->DeleteDC();
		mpDC3->DeleteDC();
	}

	CFileDialog openDig(TRUE);		// 확장자 상관 없이 CFile로 불러옴.
	CRect rect;
	CString strPath;

	if (openDig.DoModal() == IDOK)
	{
		strPath = openDig.GetPathName();
	}
	else {
		MessageBox(_T("CFileDailg 오류입니다.", MB_OK));
		return;
	}

	//로드
	if (mbImg == TRUE) {
		cimage1.Destroy();
		cimage2.Destroy();
		mbImg = FALSE;
	}                  //다시불러오기
	cimage1.Load(strPath);
	cimage2.Load(strPath);
	mbImg = TRUE;// 그림을 불러오면 트루가 된다

				  //높이 너비
	width = cimage1.GetWidth();
	height = cimage1.GetHeight();

	//원본 그리기
	image1.GetClientRect(&rect);
	mpDC1 = image1.GetDC();
	cimage1.Draw(mpDC1->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, width, height);
}


void CHistogramDlg::OnClickedButton2()
{
	CRect rect;

	//히스토그램 평활화 함수
	HistogramYCbCr();

	//YCbCr평활화 영상 그리기
	image2.GetClientRect(&rect);
	mpDC2 = image2.GetDC();
	cimage2.Draw(mpDC2->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, width, height);

	//히스토그램 평활화 함수
	HistogramHSI();

	//HSI평활화 영상 그리기
	image3.GetClientRect(&rect);
	mpDC3 = image3.GetDC();
	cimage2.Draw(mpDC3->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, width, height);
}


void CHistogramDlg::OnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_histogramGraph)
	{
		m_dlgUnitTable = new HistogramView();

		m_dlgUnitTable->Create(IDD_HISTOGRAM_VIEW, this);

		CRect rectMain, rectUnitTable;
		GetWindowRect(&rectMain);

		m_dlgUnitTable->GetWindowRect(&rectUnitTable);
		m_dlgUnitTable->MoveWindow(rectMain.right, rectMain.top, rectUnitTable.Width(), rectUnitTable.Height());

		m_dlgUnitTable->ShowWindow(SW_SHOW);
		m_dlgUnitTable->HistogramGraph();  // 상자안에 그리는 함수를 찾아오는 것
		m_histogramGraph = true;
	}
	else
	{
		m_dlgUnitTable->ShowWindow(SW_HIDE);
		m_dlgUnitTable->DestroyWindow();
		m_histogramGraph = false;
		delete m_dlgUnitTable;
	}
}



