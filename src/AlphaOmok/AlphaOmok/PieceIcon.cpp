#include "stdafx.h"
#include "PieceIcon.h"


PieceIcon::PieceIcon()
{
}


PieceIcon::~PieceIcon()
{
}
PieceIcon::PieceIcon(CPoint point, int size, char type) {
	m_Point = point;
	m_Size = size;
	m_Type = type;
}

void PieceIcon::Render() {
	CBrush white_stone(RGB(255, 255, 255)), black_stone(RGB(0, 0, 0)), *old_brush = 0;
	old_brush = m_pDC->SelectObject(m_Type == BLACK ? &black_stone : &white_stone);

	m_pDC->Ellipse(m_Point.x, m_Point.y, m_Point.x + m_Size, m_Point.y + m_Size);

	m_pDC->SelectObject(&old_brush);
}