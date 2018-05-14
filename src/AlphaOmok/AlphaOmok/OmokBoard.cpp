#include "stdafx.h"
#include "OmokBoard.h"



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

void OmokBoard::Render(CDC* pDC) {
	printf("render");
	CBrush boardBrush(RGB(230, 172, 0));
	CBrush *oldBrush;

	
	oldBrush = pDC->SelectObject(&boardBrush);
	m_RowSpace = BOARD_SIZE / ROW - 1 ;

	pDC->Rectangle(m_Point.x, m_Point.y, m_Size, m_Size);
	pDC->SelectObject(oldBrush);

	for (int i = 0; i < ROW - 1; i++) {
		pDC->MoveTo(m_Point.x + (i*m_RowSpace), m_Point.y);
		pDC->LineTo(m_Point.x + (i*m_RowSpace),  BOARD_SIZE);
	}

	for (int j = 0; j < COL - 1; j++) {
		pDC->MoveTo(m_Point.x, m_Point.y + (j*m_RowSpace));
		pDC->LineTo(BOARD_SIZE, m_Point.y + (j*m_RowSpace));
	}
}