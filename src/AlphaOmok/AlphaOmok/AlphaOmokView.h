
// AlphaOmokView.h: CAlphaOmokView 클래스의 인터페이스
//

#pragma once

#include "CanvasElement.h"
#include "OmokBoard.h"
#include "GameClock.h"
#include <vector>
#include "Game.h"

using namespace std;

#define ID_BTN_PUT_PIECE 1000

class CAlphaOmokView : public CView,
	public Observer,
	public Subject
{
protected: // serialization에서만 만들어집니다.
	CAlphaOmokView();
	DECLARE_DYNCREATE(CAlphaOmokView)

// 특성입니다.
public:
	CAlphaOmokDoc* GetDocument() const;

// 작업입니다.
private:
	vector<CanvasElement*> _canvasElements;
	Game* m_Game;
	CButton* m_Btn_Putpiece;
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void notify(string eventType, map<string, void*> data);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CAlphaOmokView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPutPieceClick();
	virtual void OnInitialUpdate();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // AlphaOmokView.cpp의 디버그 버전
inline CAlphaOmokDoc* CAlphaOmokView::GetDocument() const
   { return reinterpret_cast<CAlphaOmokDoc*>(m_pDocument); }
#endif

