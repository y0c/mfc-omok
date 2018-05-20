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
	
	if (m_Game->PutPiece(row, col)) {

	}
	
	
}
void OmokBoard::SetGame(Game* game) {
	m_Game = game;
}

void OmokBoard::Render() {
	printf("render");
	CBrush boardBrush(RGB(230, 172, 0));
	CBrush *oldBrush;

	
	oldBrush = m_pDC->SelectObject(&boardBrush);
	m_RowSpace = BOARD_SIZE / (ROW - 1);

	m_pDC->Rectangle(m_Point.x, m_Point.y, m_Size + m_Point.x, m_Size + m_Point.y);
	m_pDC->SelectObject(oldBrush);

	for (int i = 0; i < ROW - 1; i++) {
		m_pDC->MoveTo(m_Point.x + (i*m_RowSpace), m_Point.y);
		m_pDC->LineTo(m_Point.x + (i*m_RowSpace),  BOARD_SIZE + m_Point.y);
	}

	for (int j = 0; j < COL - 1; j++) {
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
}
