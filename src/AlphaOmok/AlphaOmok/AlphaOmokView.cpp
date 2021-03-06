
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
	ON_COMMAND(ID_BTN_UNDO, &CAlphaOmokView::OnUndoClick)
	ON_COMMAND(ID_BTN_NEW_GAME, &CAlphaOmokView::OnNewGameClick)
	ON_COMMAND(ID_BTN_GIVE_UP, &CAlphaOmokView::OnGiveUpClick)
//	ON_WM_LBUTTONDBLCLK()
ON_WM_LBUTTONDOWN()
ON_WM_KEYDOWN()
ON_WM_TIMER()
ON_COMMAND(ID_10SIZE, &CAlphaOmokView::On10size)
END_MESSAGE_MAP()

// CAlphaOmokView 생성/소멸

CAlphaOmokView::CAlphaOmokView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_Btn_Putpiece = NULL;
	m_Btn_Newgame = NULL;
	m_Btn_Giveup = NULL;
	m_Btn_Undo   = NULL;
	m_S = 0;
	m_Game = new Game();
	OmokBoard* omokBoard = new OmokBoard(CPoint(BOARD_X, BOARD_Y), BOARD_SIZE);
	m_ClockLabel_Black = new ClockLabel(CPoint(BOARD_X + 160, BOARD_Y + BOARD_SIZE + 60 ), 60);
	m_ClockLabel_White = new ClockLabel(CPoint(WINDOW_WIDTH - BOARD_X - 225, BOARD_Y + BOARD_SIZE + 60), 60);
	PieceIcon* blackIcon = new PieceIcon(CPoint(BOARD_X, BOARD_Y + BOARD_SIZE + 60), 50, BLACK);
	PieceIcon* whiteIcon = new PieceIcon(CPoint(WINDOW_WIDTH - BOARD_X*2 -25, BOARD_Y + BOARD_SIZE + 60), 50, WHITE);
	int centerX = WINDOW_WIDTH / 2;
	int clockX = centerX - (CLOCK_SIZE / 2);
	int clockY = (BOARD_Y + BOARD_SIZE + BOARD_Y) - (CLOCK_SIZE / 2);
	m_GameClock = new GameClock(CPoint(clockX-15, clockY+40), CLOCK_SIZE);
	m_Game->registerObserver(m_GameClock);
	m_Game->registerObserver(this);
	omokBoard->SetGame(m_Game);
	_canvasElements.push_back(omokBoard);
	_canvasElements.push_back(m_ClockLabel_Black);
	_canvasElements.push_back(m_ClockLabel_White);
	_canvasElements.push_back(m_GameClock);
	_canvasElements.push_back(blackIcon);
	_canvasElements.push_back(whiteIcon);
	
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
	CRect rect;
	GetClientRect(rect);

	CDC MemDC;
	CBitmap* pOldBitmap;
	CBitmap bmp;

	MemDC.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc, rect.Width(), BOARD_Y+BOARD_SIZE+BOARD_Y+CLOCK_SIZE + 10);
	pOldBitmap = (CBitmap*)MemDC.SelectObject(&bmp);
	MemDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);


	CString msg;
	int interval = BOARD_SIZE / (ROW-1);  
	int alpa = 65;
	for (int i = 0; i < ROW; i++) {
		msg.Format(_T("%d"), i+1);
		MemDC.TextOut(BOARD_X-45, BOARD_X + (interval * i)-5, msg);

		msg.Format(_T("%c"), (char)alpa + i);
		MemDC.TextOut(BOARD_X + (interval * i) -5 , BOARD_X - 45 , msg);
	}

	CAlphaOmokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	vector<CanvasElement*>::iterator iter;

	for (auto iter = _canvasElements.begin(); iter != _canvasElements.end(); iter++) {
		(*iter)->setDC(&MemDC);
		(*iter)->Render();
	}
	
	dc.BitBlt(0, 0, rect.Width(), BOARD_Y+BOARD_SIZE+BOARD_Y+CLOCK_SIZE + 10, &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();
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
		Invalidate(false);
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
		
		if ((objX <= x && (objX + objSize) >= x ) && (objY <= y && (objY + objSize) >= y) ) {
			(*iter)->OnClick(point);
		}
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void CAlphaOmokView::OnInitialUpdate() {
	CView::OnInitialUpdate();

	CString s;
	s.Format(_T("AlphaOmok - %s 차례( %d 수 진행중 )"),
		m_Game->GetCurrentTurn() == BLACK ? _T("백") : _T("흑"),
		m_Game->GetHistory().size());
	GetParent()->SetWindowTextW(s);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_Btn_Putpiece)
		delete m_Btn_Putpiece;
	if (m_Btn_Newgame)
		delete m_Btn_Newgame;
	if (m_Btn_Giveup)
		delete m_Btn_Giveup;
	if (m_Btn_Undo)
		delete m_Btn_Undo;

	int y = BOARD_Y + BOARD_SIZE + BOARD_Y + CLOCK_SIZE + 20;
	int gap = 20;
	int btnWidth = (BOARD_SIZE - (gap * 3)) / 4;
	int btnHeight = 40;

	m_Btn_Putpiece = new CButton;
	m_Btn_Newgame = new CButton;
	m_Btn_Giveup = new CButton;
	m_Btn_Undo = new CButton;

	int gasu = 15; // 개수
	int ganguk = 30;
	CString msg;
	int alpa = 65;
	
	int newGameStartX = BOARD_X;
	int newGameEndX = BOARD_X + btnWidth;
	int giveupStartX = newGameEndX + gap;
	int giveupEndX = giveupStartX + btnWidth;
	int putPieceStartX = giveupEndX + gap;
	int putPieceEndX = putPieceStartX + btnWidth;
	int undoStartX = putPieceEndX + gap;
	int undoEndX = undoStartX + btnWidth;

	m_Btn_Newgame->Create(_T("새 게임"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect( newGameStartX , y, newGameEndX, y + btnHeight), this, ID_BTN_NEW_GAME);
	m_Btn_Giveup->Create(_T("기권"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(giveupStartX, y, giveupEndX, y + btnHeight), this, ID_BTN_GIVE_UP);
	m_Btn_Putpiece->Create(_T("착수"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(putPieceStartX, y, putPieceEndX, y + btnHeight), this, ID_BTN_PUT_PIECE);
	m_Btn_Undo->Create(_T("무르기"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(undoStartX, y, undoEndX, y + btnHeight), this, ID_BTN_UNDO);
	SetTimer(0, 1000, NULL);
}

afx_msg void CAlphaOmokView::OnPutPieceClick() {
	
	Point cursor = m_Game->GetCursor();
	PlaySound((LPCWSTR)MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_ASYNC | SND_RESOURCE);
	if (m_Game->GetStatus() == GAME_ING) {
		int banMethod = m_Game->banMethodCheck(cursor.y, cursor.x);

		if (m_Game->GetCurrentTurn() == BLACK) {
			if (banMethod == DOUBLE_3) {
				AfxMessageBox(_T("흑은 삼삼을 둘 수 없습니다."));
				return;
			}
			else if (banMethod == DOUBLE_4) {
				AfxMessageBox(_T("흑은 사사를 둘 수 없습니다."));
				return;
			}
			else if (banMethod == YUKMOK) {
				AfxMessageBox(_T("흑은 육목을 둘 수 없습니다."));
				return;
			}
		}


		if (m_Game->PutPiece(cursor.y, cursor.x)) {
			m_S = 0;
			
			CString s;
			s.Format(_T("AlphaOmok - %s 차례( %d 수 진행중 )"),
				m_Game->GetCurrentTurn() == BLACK ? _T("백") : _T("흑"),
				m_Game->GetHistory().size());
			GetParent()->SetWindowTextW(s);
			
			
			Invalidate(false);
			if (m_Game->winCheck(cursor.y, cursor.x)) {

				m_S = 0;
				m_GameClock->SetSeconds(m_S);
				m_ClockLabel_Black->SetSeconds(m_S);
				m_ClockLabel_Black->SetSeconds(m_S);
				KillTimer(0);
				Invalidate(false);

				if (m_Game->GetCurrentTurn() == BLACK) {
					AfxMessageBox(_T("흑 승리"));
				}
				else {
					AfxMessageBox(_T("백 승리"));
				}
				CString s;
				s.Format(_T("AlphaOmok - %s 승리"),
					m_Game->GetCurrentTurn() == BLACK ? _T("백") : _T("흑"));
				GetParent()->SetWindowTextW(s);
			}
			m_Game->reserveTurn();
		}
	}
	this->SetFocus();
	
}

afx_msg void CAlphaOmokView::OnUndoClick() {
	if (m_Game->GetStatus() == GAME_ING) {
		m_S = 0;
		m_Game->Undo();
		CString s;
		s.Format(_T("AlphaOmok - %s 차례( %d 수 진행중 )"),
			m_Game->GetCurrentTurn() == BLACK ? _T("백") : _T("흑"),
			m_Game->GetHistory().size());
		GetParent()->SetWindowTextW(s);
		Invalidate(false);
	}
	this->SetFocus();
}

afx_msg void CAlphaOmokView::OnNewGameClick() {
	if (m_Game->GetStatus() == GAME_END) {
		SetTimer(0, 1000, NULL);
	}
	m_Game->Init();
	m_S = 0;
	Invalidate(false);
	this->SetFocus();
}
void CAlphaOmokView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	Point cursor = m_Game->GetCursor();
		switch (nChar)
		{
		case VK_LEFT:
			if (cursor.x > 0){
				cursor.x -= 1;
				m_Game->SetCursor(cursor);
			}
			break;

		case VK_RIGHT:
			if (cursor.x < ROW-1) {
				cursor.x += 1;
				m_Game->SetCursor(cursor);
			}
			break;

		case VK_UP:
			if (cursor.y > 0) {
				cursor.y -= 1;
				m_Game->SetCursor(cursor);
			}
			break;
		case VK_DOWN:
			if (cursor.y < COL-1) {
				cursor.y += 1;
				m_Game->SetCursor(cursor);
			}
			break;
		case VK_SPACE:
			this->OnPutPieceClick();
			break;
		}
		Invalidate(false);

		
	__super::OnKeyDown(nChar, nRepCnt, nFlags);
}

afx_msg void CAlphaOmokView::OnGiveUpClick() {
	m_Game->SetStatus(GAME_END);
	m_S = 0;
	m_GameClock->SetSeconds(m_S);
	m_ClockLabel_Black->SetSeconds(m_S);
	m_ClockLabel_Black->SetSeconds(m_S);
	KillTimer(0);
	Invalidate(false);

	if (m_Game->GetCurrentTurn() == BLACK) {
		AfxMessageBox(_T("백 승리"));
	}
	else {
		AfxMessageBox(_T("흑 승리"));
	}
	CString s;
	s.Format(_T("AlphaOmok - %s 승리"),
		m_Game->GetCurrentTurn() == BLACK ? _T("흑") : _T("백"));
	GetParent()->SetWindowTextW(s);

	Invalidate(false);
	this->SetFocus();
}


afx_msg void CAlphaOmokView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (nIDEvent == 0)
	{
		m_S++;
	
		m_GameClock->SetSeconds(m_S);
		if (m_Game->GetCurrentTurn() == BLACK) {
			m_ClockLabel_Black->SetSeconds(30 - m_S);
			m_ClockLabel_White->SetSeconds(0);
		}
		else {
			m_ClockLabel_White->SetSeconds(30 - m_S);
			m_ClockLabel_Black->SetSeconds(0);
		}
		
		if (m_S == 30) {
			m_Game->SetStatus(GAME_END);
			m_S = 0;
			m_GameClock->SetSeconds(m_S);
			m_ClockLabel_Black->SetSeconds(m_S);
			m_ClockLabel_Black->SetSeconds(m_S);
			KillTimer(0);
			CString s;
			s.Format(_T("AlphaOmok - %s 승리"),
				m_Game->GetCurrentTurn() == BLACK ? _T("백") : _T("흑"));
			GetParent()->SetWindowTextW(s);
			if (m_Game->GetCurrentTurn() == BLACK) {
				AfxMessageBox(_T("착수시간이 초과되어 백이 승리하였습니다."));
			}
			else {
				AfxMessageBox(_T("착수시간이 초과되어 흑이 승리하였습니다."));
			}
		}
		//thirtycount--;
		//if (thirtycount < 0)
		//   thirtycount = 30;
		Invalidate(false);
	}
	__super::OnTimer(nIDEvent);
}


void CAlphaOmokView::On10size()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
