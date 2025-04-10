
// MFCHw2Dlg.h: 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "atlimage.h" // CImage 사용을 위해 추가
#include <vector>     // std::vector 사용을 위해 추가

// CMFCHw2Dlg 대화 상자
class CMFCHw2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCHw2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCHW2_DIALOG };
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	int m_userRadius; // 사용자가 입력한 원 반지름 값

private:
	CImage m_image; // 🔹CImage 멤버 변수 추가
	std::vector<CPoint> m_clickPoints; // 클릭 좌표 저장용 벡터
	bool m_isDragging = false; // 드래그 상태 여부
	int m_dragIndex = -1;      // 드래그 중인 원의 인덱스
	CPoint m_prevMousePos;     // 이전 마우스 위치
	CStatic m_staticP1;  // 첫 번째 클릭 좌표 표시용
	CStatic m_staticP2;  // 두 번째 클릭 좌표 표시용
	CStatic m_staticP3;  // 세 번째 클릭 좌표 표시용
	//CStatic m_imageView; //Picture Control

	void InitializeImage(); // 이미지 초기화 함수
	void UpdateDisplay();   // 화면 업데이트 함수
	void drawCircle(unsigned char* fm, int x, int y, int radius, int color, bool filled, int thickness);
	bool isInCircle(int i, int j, int centerX, int centerY, int radius);
	bool CalculateCircumcircle(CPoint p1, CPoint p2, CPoint p3, CPoint& center, int& radius);
	BOOL validImgPos(int x, int y);

public:
	afx_msg void OnBnClickedButton1();
	int m_userThickness;
};
