#include "stdafx.h"
#include "OmokBoard.h"
#include <math.h>


OmokBoard::OmokBoard()
{


}
OmokBoard::OmokBoard(CPoint point, int size) {
	m_Point = point;
	m_Size = size;
}

OmokBoard::~OmokBoard()
{
}



void OmokBoard::OnClick(CPoint point) {
	printf("\n%d %d rowSpace %d", point.x,point.y, m_RowSpace);
	

	int row = round((point.y - m_Point.y) / (m_RowSpace*1.0));
	int col = round((point.x - m_Point.x) / (m_RowSpace*1.0));
	
	char currentTurn = m_Game->GetCurrentTurn();
	//브러쉬 선택
	
	int status = m_Game->GetStatus();
	Point cursor;
	cursor.x = col;
	cursor.y = row;
	m_Game->SetCursor(cursor);
	map<string, void*> data;
	m_Game->notifyAll("SET_CURSOR", data);
	
}
void OmokBoard::SetGame(Game* game) {
	m_Game = game;
}


void OmokBoard::DrawCursor(CPoint start) {
	
	CBrush brush1, *oldbrush1;
	brush1.CreateSolidBrush(RGB(255, 0, 0));
	oldbrush1 = m_pDC->SelectObject(&brush1);

	const int CIRCLE_R = (m_RowSpace / 2);
	const int GAP = (m_RowSpace / 2) / 2;

	//왼쪽 위 삼각형
	POINT arPt[3] = { { start.x,start.y },{ start.x + GAP,start.y },{ start.x,start.y + GAP } };
	m_pDC->Polygon(arPt, 3);
	//오른쪽 위 삼각형
	POINT arPt1[3] = { { start.x + 2 * CIRCLE_R,start.y },{ start.x + 2 * CIRCLE_R - GAP,start.y },{ start.x + 2 * CIRCLE_R,start.y + GAP } };
	m_pDC->Polygon(arPt1, 3);
	//왼쪽 아래 삼각형 
	POINT arPt2[3] = { { start.x,start.y + (CIRCLE_R * 2) },{ start.x, start.y + (CIRCLE_R * 2) - GAP },{ start.x + GAP,start.y + (CIRCLE_R * 2) } };
	m_pDC->Polygon(arPt2, 3);
	//오른쪽 아래 삼각형
	POINT arPt3[3] = { { start.x + 2 * CIRCLE_R, start.y + (CIRCLE_R * 2) },{ start.x + 2 * CIRCLE_R,start.y + (CIRCLE_R * 2) - GAP },{ start.x + 2 * CIRCLE_R - GAP,  start.y + (CIRCLE_R * 2) } };
	m_pDC->Polygon(arPt3, 3);
	m_pDC->SelectObject(oldbrush1);
	brush1.DeleteObject();
}

void OmokBoard::Render() {
	printf("render");
	CBrush boardBrush(RGB(230, 172, 0));
	CBrush *oldBrush;

	oldBrush = m_pDC->SelectObject(&boardBrush);
	m_RowSpace = BOARD_SIZE / (ROW - 1);
	
	m_pDC->Rectangle(m_Point.x, m_Point.y, m_Size + m_Point.x, m_Size + m_Point.y);
	m_pDC->Rectangle(m_Point.x - (m_RowSpace / 2), m_Point.y - (m_RowSpace / 2), m_Size + m_Point.x + (m_RowSpace / 2), m_Size + m_Point.y + (m_RowSpace / 2));

	m_pDC->SelectObject(oldBrush);

	for (int i = 0; i < ROW ; i++) {
		m_pDC->MoveTo(m_Point.x + (i*m_RowSpace), m_Point.y);
		m_pDC->LineTo(m_Point.x + (i*m_RowSpace), BOARD_SIZE + m_Point.y);
	}

	for (int j = 0; j < COL ; j++) {
		m_pDC->MoveTo(m_Point.x, m_Point.y + (j*m_RowSpace));
		m_pDC->LineTo(BOARD_SIZE + m_Point.x, m_Point.y + (j*m_RowSpace));
	}


	CBrush white_stone(RGB(255, 255, 255)), black_stone(RGB(0, 0, 0)), *old_brush = 0;
	
	for (Piece piece : m_Game->GetHistory()) {

		int x = (piece.x * m_RowSpace) + m_Point.x;
		int y = (piece.y * m_RowSpace) + m_Point.y;

		int startX = x - (m_RowSpace / 2);
		int startY = y - (m_RowSpace / 2);

		int endX = x + (m_RowSpace / 2);
		int endY = y + (m_RowSpace / 2);

		old_brush = m_pDC->SelectObject(piece.type == BLACK ? &black_stone : &white_stone);
		
		m_pDC->Ellipse(startX, startY, endX, endY);
		
	}

	Point cursor = m_Game->GetCursor();
	int cursorX = (cursor.x * m_RowSpace) + m_Point.x;
	int cursorY = (cursor.y * m_RowSpace) + m_Point.y;

	int cursorStartX = cursorX - (m_RowSpace / 2);
	int cursorStartY = cursorY - (m_RowSpace / 2);
	DrawCursor(CPoint(cursorStartX, cursorStartY));
}
