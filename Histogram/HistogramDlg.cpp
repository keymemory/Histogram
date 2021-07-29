
// HistogramDlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CHistogramDlg ��ȭ ����



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


// CHistogramDlg �޽��� ó����

BOOL CHistogramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CHistogramDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CHistogramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CHistogramDlg::Cliping(double value)
{
	if (value < 0)				// value �׸� ���
		return 0;
	else if (256 <= value)
		return 255;
	return (int)value;
}

void CHistogramDlg::HistogramYCbCr()
{
	memset(histogram1, 0, sizeof(histogram1)); // ������׷� �󵵼� 256���� �ҷ����°�
	memset(histogram2, 0, sizeof(histogram2)); // ��ġ�� �ȵǴϱ� �迭�ʱ�ȭ�� ������־����.

	memset(accHistogram1, 0, sizeof(accHistogram1));

	//YCbCr ���� �迭 �����ͷ� �����ؼ� �޸� ���� �Ҵ�
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
			COLORREF color = cimage1.GetPixel(j, i); //�����̹���.���ȼ�����
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			y[i][j] = Cliping((r * 0.299) + (g * 0.587) + (b * 0.114));   //���
			cb[i][j] = Cliping((r * -0.16874) + (g * -0.33126) + (b * 0.5) + 128); //���󰪵�, R-Y
			cr[i][j] = Cliping((r * 0.5) + (g * -0.41869) + (b * -0.08131) + 128); //���󰪵�, B-Y
																				   //rgb �� ycbcr �� �ٲٴ� ����
			histogram1[y[i][j]]++; // ������׷� �󵵼�
		}
	}

	accHistogram1[0] = histogram1[0]; // 0�� �־ �ʱ�ȭ * ������ �������

	for (int i = 1; i < 256; i++)
		accHistogram1[i] = histogram1[i] + accHistogram1[i - 1]; //�����󵵼�


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			double temp = accHistogram1[y[i][j]] * 255 / (width * height);

			int R = Cliping((temp + 1.402 * (cr[i][j] - 128))); //ycbcr �� r�� �ٲٴ�
			int G = Cliping((temp + (cb[i][j] - 128) * -0.34414 + (cr[i][j] - 128) * -0.71414)); // g
			int B = Cliping((temp + 1.772 * (cb[i][j] - 128))); // b

			cimage2.SetPixel(j, i, RGB(R, G, B)); //�迭�� ���� ������׷��� �ȼ��� ��Ÿ���� ����  j i ��ġ �ٲ�

											   //��ȯ �� ������׷� ���
			histogram2[Cliping(temp)]++; // �ٲ� ������׷��� �󵵼�
		}
	}
}


void CHistogramDlg::HistogramHSI()
{
	memset(histogram3, 0, sizeof(histogram3)); // ������׷� �󵵼� 256���� 0���� �ʱ�ȭ
	memset(histogram4, 0, sizeof(histogram4));

	// ���� ������׷� �󵵼�
	memset(accHistogram2, 0, sizeof(accHistogram2));

	double minimum, radian, cosine;//HSI ���� �ʿ� ����
	double radianTheta1, radianTheta2;
	// 0�� ����, 60�� ���, 120�� ���, 240�� �Ķ�

	//HSI ���� �迭 �����ͷ� �����ؼ� �޸� ���� �Ҵ�
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
			COLORREF color = cimage1.GetPixel(y, x); //�����̹���.���ȼ�����
			double r = GetRValue(color) / 255.0;
			double g = GetGValue(color) / 255.0;
			double b = GetBValue(color) / 255.0;
			I = (r + g + b) / 3.0;//i�� ����.

			if ((r == g) && (r == b))
			{//���� RGB���� ���� ���ٸ�
				S = 0.0;
				H = 0.0;
			}
			else
			{
				minimum = r;//RGB�� ���� ���� �������� ã���ϴ�.
				if (g < minimum)
					minimum = g;
				if (b < minimum)
					minimum = b;
				S = 1.0 - (3.0 / (r + g + b)) * minimum;//S���ϴ� ����.

														//h���ϴ� ����
				cosine = (r - 0.5 * (g + b)) / sqrt((r - g) * (r - g) + (r - b) * (g - b));
				radian = acos(cosine);
				H = 180.0 / M_PI * radian;

				if (b > g)
					H = 360.0 - H;

			}

			h[x][y] = H; //���󰪵�
			s[x][y] = S; //���󰪵�
			i[x][y] = I; //���

			histogram3[(int)(i[x][y] * 255.0)]++; //�󵵼�
		}
	}

	int numberofPixels;//HSI ���� ������׷� ���ϱ�
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

			if (I == 0.0)// i�� ��, ���� 0�̶�� ��ο���̴�.
			{
				r = g = b = 0.0;//rgb�� ��ο� 0�� �ȴ�.
			}
			else
			{
				if (S == 0.0)//ä���� 0 �̶�� ��ä���̹Ƿ�
				{
					r = g = b = I;//rgb�� ���δ� ������ ä�������� ����.
				}
				else
				{
					if (H < 0.0) //������ �������
						H += 360.0;// ���󰪿� 360�� �����ش�.
					if (H <= 120.0)//���� h���� 120�� �̳���� 1������ ����.
					{
						radianTheta1 = M_PI / 180.0 * H;
						radianTheta2 = M_PI / 180.0 * (60.0 - H);
						b = (1.0 - S) / 3.0;
						r = (1.0 + S * cos(radianTheta1) / cos(radianTheta2)) / 3.0;
						g = 1.0 - (r + b);
					}
					else if (H <= 240.0)//2����
					{
						H -= 120.0;
						radianTheta1 = M_PI / 180.0 * H;
						radianTheta2 = M_PI / 180.0 * (60.0 - H);
						r = (1.0 - S) / 3.0;
						g = (1.0 + S * cos(radianTheta1) / cos(radianTheta2)) / 3.0;
						b = 1.0 - (r + g);
					}
					else//�װԾƴ϶�� 3����
					{
						H -= 240.0;
						radianTheta1 = M_PI / 180.0 * H;
						radianTheta2 = M_PI / 180.0 * (60.0 - H);
						g = (1.0 - S) / 3.0;
						b = (1.0 + S * cos(radianTheta1) / cos(radianTheta2)) / 3.0;
						r = 1.0 - (g + b);
					}
					//�߰� ��� ����
					r *= 3.0 * I; g *= 3.0 * I; b *= 3.0 * I;


					//r,g,b,i,s�� 0~1������ ���� ����.
					if (r < 0.0) r = 0.0;//rgb������ 0���� �۴ٸ� 0����
					if (g < 0.0) g = 0.0;
					if (b < 0.0) b = 0.0;
					if (r > 1.0) r = 1.0;//1���� ũ�ٸ� 1��
					if (g > 1.0) g = 1.0;
					if (b > 1.0) b = 1.0;
				}
			}

			int R = (int)(255.0 * r);
			int G = (int)(255.0 * g);
			int B = (int)(255.0 * b);

			cimage2.SetPixel(y, x, RGB(R, G, B)); //�迭�� ���� ������׷��� �ȼ��� ��Ÿ���� ����  j i ��ġ �ٲ�

											   //��ȯ �� ������׷� ���

		}
	}
}

void CHistogramDlg::OnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// �ʱ�ȭ
	memset(histogram1, 0, sizeof(histogram1)); // ������׷� �󵵼� 256���� �ҷ����°�
	memset(histogram2, 0, sizeof(histogram2)); // ��ġ�� �ȵǴϱ� �迭�ʱ�ȭ�� ������־����.
	memset(histogram3, 0, sizeof(histogram3));
	memset(histogram4, 0, sizeof(histogram4));


	if (mpDC1 != NULL) {
		mpDC1->DeleteDC(); //DC�� �ʱ�ȭ
		mpDC2->DeleteDC();
		mpDC3->DeleteDC();
	}

	CFileDialog openDig(TRUE);		// Ȯ���� ��� ���� CFile�� �ҷ���.
	CRect rect;
	CString strPath;

	if (openDig.DoModal() == IDOK)
	{
		strPath = openDig.GetPathName();
	}
	else {
		MessageBox(_T("CFileDailg �����Դϴ�.", MB_OK));
		return;
	}

	//�ε�
	if (mbImg == TRUE) {
		cimage1.Destroy();
		cimage2.Destroy();
		mbImg = FALSE;
	}                  //�ٽúҷ�����
	cimage1.Load(strPath);
	cimage2.Load(strPath);
	mbImg = TRUE;// �׸��� �ҷ����� Ʈ�簡 �ȴ�

				  //���� �ʺ�
	width = cimage1.GetWidth();
	height = cimage1.GetHeight();

	//���� �׸���
	image1.GetClientRect(&rect);
	mpDC1 = image1.GetDC();
	cimage1.Draw(mpDC1->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, width, height);
}


void CHistogramDlg::OnClickedButton2()
{
	CRect rect;

	//������׷� ��Ȱȭ �Լ�
	HistogramYCbCr();

	//YCbCr��Ȱȭ ���� �׸���
	image2.GetClientRect(&rect);
	mpDC2 = image2.GetDC();
	cimage2.Draw(mpDC2->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, width, height);

	//������׷� ��Ȱȭ �Լ�
	HistogramHSI();

	//HSI��Ȱȭ ���� �׸���
	image3.GetClientRect(&rect);
	mpDC3 = image3.GetDC();
	cimage2.Draw(mpDC3->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, width, height);
}


void CHistogramDlg::OnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (!m_histogramGraph)
	{
		m_dlgUnitTable = new HistogramView();

		m_dlgUnitTable->Create(IDD_HISTOGRAM_VIEW, this);

		CRect rectMain, rectUnitTable;
		GetWindowRect(&rectMain);

		m_dlgUnitTable->GetWindowRect(&rectUnitTable);
		m_dlgUnitTable->MoveWindow(rectMain.right, rectMain.top, rectUnitTable.Width(), rectUnitTable.Height());

		m_dlgUnitTable->ShowWindow(SW_SHOW);
		m_dlgUnitTable->HistogramGraph();  // ���ھȿ� �׸��� �Լ��� ã�ƿ��� ��
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



