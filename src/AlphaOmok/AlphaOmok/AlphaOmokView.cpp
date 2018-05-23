
// AlphaOmokView.cpp: CAlphaOmokView 클래스의 구현
//

#include "stdafx.h"
#include <mmsystem.h>

// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "AlphaOmok.h"
#endif

#include "AlphaOmokDoc.h"
#include "AlphaOmokView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAlphaOmokView

IMPLEMENT_DYNCREATE(CAlphaOmokView, CView)

BEGIN_MESSAGE_MAP(CAlphaOmokView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_BTN_PUT_PIECE, &CAlphaOmokView::OnPutPieceClick)
//	ON_WM_LBUTTONDBLCLK()
ON_WM_LBUTTONDOWN()
ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CAlphaOmokView 생성/소멸

CAlphaOmokView::CAlphaOmokView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_Btn_Putpiece = NULL;
	m_Game = new Game();
	OmokBoard* omokBoard = new OmokBoard(CPoint(BOARD_X, BOARD_Y), BOARD_SIZE);
	
	int centerX = WINDOW_WIDTH / 2;
	int clockX = centerX - (CLOCK_SIZE / 2);
	int clockY = (BOARD_Y + BOARD_SIZE + BOARD_Y) - (CLOCK_SIZE / 2);
	GameClock* gameClock = new GameClock(CPoint(clockX-15, clockY), CLOCK_SIZE);
	m_Game->registerObserver(gameClock);
	m_Game->registerObserver(this);
	omokBoard->SetGame(m_Game);
	_canvasElements.push_back(omokBoard);
	_canvasElements.push_back(gameClock);
}

CAlphaOmokView::~CAlphaOmokView()
{
	if(m_Btn_Putpiece)
		delete m_Btn_Putpiece;
}

BOOL CAlphaOmokView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CAlphaOmokView 그리기

void CAlphaOmokView::OnDraw(CDC* pDC)
{
	CClientDC dc(this);
	CAlphaOmokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	vector<CanvasElement*>::iterator iter;

	for (auto iter = _canvasElements.begin(); iter != _canvasElements.end(); iter++) {
		(*iter)->setDC(&dc);
		(*iter)->Render();
	}
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CAlphaOmokView 인쇄

BOOL CAlphaOmokView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CAlphaOmokView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CAlphaOmokView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CAlphaOmokView 진단

#ifdef _DEBUG
void CAlphaOmokView::AssertValid() const
{
	CView::AssertValid();
}

void CAlphaOmokView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAlphaOmokDoc* CAlphaOmokView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{

	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAlphaOmokDoc)));
	return (CAlphaOmokDoc*)m_pDocument;
}
#endif //_DEBUG


// CAlphaOmokView 메시지 처리기

void CAlphaOmokView::notify(string eventType, map<string, void*> data) {
	if (eventType.compare("SET_CURSOR") == 0) {
		Invalidate();
	}
}



void CAlphaOmokView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int x = point.x;
	int y = point.y;

	vector<CanvasElement*>::iterator iter;
	
	for (auto iter = _canvasElements.begin(); iter != _canvasElements.end(); iter++) {
		int objX = (*iter)->GetPoint().x;
		int objY = (*iter)->GetPoint().y;
		int objSize = (*iter)->GetSize();
		
		printf("%d %d %d", objX, objY, objSize);
		if ((objX <= x && (objX + objSize) >= x ) && (objY <= y && (objY + objSize) >= y) ) {
			(*iter)->OnClick(point);
		}
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void CAlphaOmokView::OnInitialUpdate() {
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_Btn_Putpiece)
		delete m_Btn_Putpiece;

	m_Btn_Putpiece = new CButton;
	m_Btn_Putpiece->Create(_T("착수"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(100, 10, 100 + 128, 10 + 32), this, ID_BTN_PUT_PIECE);
}

afx_msg void CAlphaOmokView::OnPutPieceClick() {
	printf("putPieceClick!!");
	Point cursor = m_Game->GetCursor();
	PlaySound((LPCWSTR)MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_ASYNC | SND_RESOURCE);
	if (m_Game->GetStatus() == GAME_ING) {
		if (m_Game->PutPiece(cursor.y, cursor.x)) {
			Invalidate();
			if (m_Game->winCheck(cursor.y, cursor.x)) {

				if (m_Game->GetCurrentTurn() == BLACK) {
					AfxMessageBox(_T("흑 승리"));
				}
				else {
					AfxMessageBox(_T("백 승리"));
				}
			}
			m_Game->reserveTurn();
		}
	}
	
}

void CAlphaOmokView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	Point cursor = m_Game->GetCursor();
		switch (nChar)
		{
			case VK_LEFT:
				cursor.x -= 1;
				m_Game->SetCursor(cursor);
				break;

			case VK_RIGHT:
				cursor.x += 1;
				m_Game->SetCursor(cursor);
				break;

			case VK_UP:
				cursor.y -= 1;
				m_Game->SetCursor(cursor);
				break;
			case VK_DOWN:
				cursor.y += 1;
				m_Game->SetCursor(cursor);
				break;
			case VK_RETURN:
				this->OnPutPieceClick();
				break;
		}
		Invalidate();

		
	__super::OnKeyDown(nChar, nRepCnt, nFlags);
}
