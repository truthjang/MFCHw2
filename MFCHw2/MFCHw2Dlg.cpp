
// MFCHw2Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCHw2.h"
#include "MFCHw2Dlg.h"
#include "afxdialogex.h"
#include <iostream>

using namespace std;

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


// CMFCHw2Dlg 대화 상자



CMFCHw2Dlg::CMFCHw2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCHW2_DIALOG, pParent), 
	m_userRadius(10), m_userThickness(3) // 기본값 설정
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCHw2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_RADIUS, m_userRadius);  // 반지름 값 바인딩
	DDV_MinMaxInt(pDX, m_userRadius, 1, 100);      // 값의 범위 제한 (1~100)
	DDX_Text(pDX, IDC_EDIT_THICKNESS, m_userThickness); // 테두리 값 바인딩
	DDV_MinMaxInt(pDX, m_userThickness, 1, 20); // 값의 범위 제한 (1~20)
	DDX_Control(pDX, IDC_STATIC_P1, m_staticP1);
	DDX_Control(pDX, IDC_STATIC_P2, m_staticP2);
	DDX_Control(pDX, IDC_STATIC_P3, m_staticP3);
}

BEGIN_MESSAGE_MAP(CMFCHw2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCHw2Dlg::OnBnClickedButton1)
	//ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCHw2Dlg 메시지 처리기

BOOL CMFCHw2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	OnBnClickedButton1();  // 이미지 초기화 자동 실행
	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCHw2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCHw2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		//여기서만 이미지 출력
		if (!m_image.IsNull())
		{
			// (예시) 이미지 위치 조절 가능
			int drawX = 0;
			int drawY = 0;

			m_image.Draw(dc.m_hDC, drawX, drawY);
		}

		// 기본 다이얼로그 처리
		CDialogEx::OnPaint();
	}
}


// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCHw2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCHw2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 포커스 이동을 강제로 유도해서 Edit에 입력된 값 반영
	SetFocus();

	// 클릭한 원이 있는지 확인
	for (int i = 0; i < m_clickPoints.size(); i++)
	{
		int dx = point.x - m_clickPoints[i].x;
		int dy = point.y - m_clickPoints[i].y;
		if (dx * dx + dy * dy <= m_userRadius * m_userRadius) // 클릭한 좌표가 원 내부인지 확인
		{
			m_isDragging = true;
			m_dragIndex = i;
			m_prevMousePos = point;
			return;
		}
	}

	// 3개 이상의 클릭은 무시
	if (m_clickPoints.size() >= 3)
		return;

	// **사용자 입력값을 불러오기 전에 먼저 확인**
	if (!UpdateData(TRUE))
	{
		AfxMessageBox(_T("반지름 값이 잘못되었습니다. 1에서 100 사이의 값을 입력하세요."));
		return;
	}

	// 클릭 좌표 저장
	m_clickPoints.push_back(point);

	// 클릭한 좌표를 UI에 표시하는 코드 추가 
	CString str;
	int clickCount = m_clickPoints.size(); // 현재 클릭 개수

	if (clickCount == 1)
	{
		str.Format(_T("P1: (%d, %d)"), point.x, point.y);
		m_staticP1.SetWindowText(str);
	}
	else if (clickCount == 2)
	{
		str.Format(_T("P2: (%d, %d)"), point.x, point.y);
		m_staticP2.SetWindowText(str);
	}
	else if (clickCount == 3)
	{
		str.Format(_T("P3: (%d, %d)"), point.x, point.y);
		m_staticP3.SetWindowText(str);
	}

	// 사용자 입력값 업데이트
	//UpdateData(TRUE); //FALSE, TRUE

	// 원 반지름 (사용자 입력값 사용)
	int radius = m_userRadius;

	// 픽셀 데이터 가져오기
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	// 클릭한 위치에 채워진 원 그리기
	drawCircle(fm, point.x, point.y, radius, 0x00, true, 1); // 검은색 원

															 // 클릭이 3번 완료되면 외접원 계산 후 그리기
	if (m_clickPoints.size() == 3)
	{
		CPoint center;
		int outerRadius;

		if (CalculateCircumcircle(m_clickPoints[0], m_clickPoints[1], m_clickPoints[2], center, outerRadius))
		{
			drawCircle(fm, center.x, center.y, outerRadius, 0x00, false, m_userThickness); // 테두리만 그리기
		}
	}

	// 화면 업데이트
	UpdateDisplay();
	SetCapture(); // 마우스 드래그 감지 고정

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCHw2Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_isDragging = false;
	m_dragIndex = -1;

	ReleaseCapture(); // 마우스 캡처 해제

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCHw2Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_isDragging && m_dragIndex != -1)
	{
		// 이동 거리 계산
		int dx = point.x - m_prevMousePos.x;
		int dy = point.y - m_prevMousePos.y;

		// 원 이동
		m_clickPoints[m_dragIndex].x += dx;
		m_clickPoints[m_dragIndex].y += dy;

		//여기 추가!
		CString str;
		CPoint& p = m_clickPoints[m_dragIndex];
		if (m_dragIndex == 0)
		{
			str.Format(_T("P1: (%d, %d)"), p.x, p.y);
			m_staticP1.SetWindowText(str);
		}
		else if (m_dragIndex == 1)
		{
			str.Format(_T("P2: (%d, %d)"), p.x, p.y);
			m_staticP2.SetWindowText(str);
		}
		else if (m_dragIndex == 2)
		{
			str.Format(_T("P3: (%d, %d)"), p.x, p.y);
			m_staticP3.SetWindowText(str);
		}

		// 이전 마우스 위치 업데이트
		m_prevMousePos = point;

		// 화면 다시 그리기
		InitializeImage();
		unsigned char* fm = (unsigned char*)m_image.GetBits();
		for (CPoint p : m_clickPoints)
			drawCircle(fm, p.x, p.y, m_userRadius, 0x00, true, 1); // 검은색 원 다시 그리기

		if (m_clickPoints.size() == 3)
		{
			CPoint center;
			int outerRadius;
			if (CalculateCircumcircle(m_clickPoints[0], m_clickPoints[1], m_clickPoints[2], center, outerRadius))
			{
				drawCircle(fm, center.x, center.y, outerRadius, 0x00, false, m_userThickness); // 외접원 다시 그리기
			}
		}

		UpdateDisplay();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCHw2Dlg::InitializeImage()
{
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8; // 흑백 이미지

	// CImage 객체 생성
	if (!m_image.IsNull()) {
		m_image.Destroy();  // 기존 이미지 제거
	}
	m_image.Create(nWidth, -nHeight, nBpp);

	if (m_image.IsNull()) {
		AfxMessageBox(_T("CImage 생성 실패!"));
		return;
	}

	// 8bpp일 경우 그레이스케일 팔레트 설정
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	// 픽셀 데이터 가져오기
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	// 모든 픽셀을 흰색(0xFF)으로 채움
	memset(fm, 0xFF, nWidth * nHeight);

	// 화면 업데이트
	UpdateDisplay();
}


bool CMFCHw2Dlg::CalculateCircumcircle(CPoint p1, CPoint p2, CPoint p3, CPoint& center, int& radius)
{
	int ax = p1.x, ay = p1.y;
	int bx = p2.x, by = p2.y;
	int cx = p3.x, cy = p3.y;

	int d = 2 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by));
	if (d == 0) return false; // 세 점이 일직선이면 실패

	int ux = ((ax * ax + ay * ay) * (by - cy) + (bx * bx + by * by) * (cy - ay) + (cx * cx + cy * cy) * (ay - by)) / d;
	int uy = ((ax * ax + ay * ay) * (cx - bx) + (bx * bx + by * by) * (ax - cx) + (cx * cx + cy * cy) * (bx - ax)) / d;

	center.x = ux;
	center.y = uy;

	radius = sqrt((ux - ax) * (ux - ax) + (uy - ay) * (uy - ay));
	return true;
}


void CMFCHw2Dlg::drawCircle(unsigned char* fm, int x, int y, int radius, int color, bool filled, int thickness)
{
	int nPitch = m_image.GetPitch();

	for (int j = y - radius; j <= y + radius; j++)
	{
		for (int i = x - radius; i <= x + radius; i++)
		{
			if (!validImgPos(i, j)) continue;

			int dx = i - x;
			int dy = j - y;
			int distSquared = dx * dx + dy * dy;
			int radiusSquared = radius * radius;

			if (filled)
			{
				if (distSquared <= radiusSquared)
				{
					fm[j * nPitch + i] = color;
				}
			}
			else
			{
				int outer = radius;
				int inner = radius - thickness;
				int outerSquared = outer * outer;
				int innerSquared = inner * inner;

				if (distSquared <= outerSquared && distSquared >= innerSquared)
				{
					fm[j * nPitch + i] = color;
				}
			}
		}
	}
}



BOOL CMFCHw2Dlg::validImgPos(int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	return (x >= 0 && x < nWidth && y >= 0 && y < nHeight);
}


bool CMFCHw2Dlg::isInCircle(int x, int y, int cx, int cy, int radius)
{
	int dx = x - cx;
	int dy = y - cy;
	return (dx * dx + dy * dy) <= (radius * radius);
}


void CMFCHw2Dlg::UpdateDisplay()
{
	Invalidate(FALSE); // 화면을 다시 그리도록 요청
}


void CMFCHw2Dlg::OnBnClickedButton1() //초기화 버튼
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	// 기존 이미지가 있으면 제거
	if (!m_image.IsNull())
		m_image.Destroy();

	// 이미지 생성
	if (FAILED(m_image.Create(nWidth, -nHeight, nBpp))) {
		AfxMessageBox(_T("이미지 생성 실패"));
		return;
	}

	// 팔레트 설정 (8bpp일 경우)
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	// 픽셀 초기화
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	if (fm == nullptr) {
		AfxMessageBox(_T("비트 접근 실패"));
		return;
	}

	memset(fm, 0xFF, nWidth * nHeight);

	// 내부 상태도 초기화
	m_clickPoints.clear();
	m_isDragging = false;
	m_dragIndex = -1;

	UpdateDisplay();
}

