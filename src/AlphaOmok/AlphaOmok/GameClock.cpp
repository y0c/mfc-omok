#include "stdafx.h"
#include "GameClock.h"

#define _USE_MATH_DEFINES
#include <math.h>

GameClock::GameClock(CPoint point, int size) {
	m_Point = point;
	m_Size = size;
}

GameClock::GameClock()
{
	m_S = 0;
}


GameClock::~GameClock()
{
}

void GameClock::notify(string eventType, map<string, void*> data) {

}
void GameClock::Render() {

	
	int S1 ;
	int clock_center_x = (m_Point.x + m_Point.x + m_Size)/2;
	int clock_center_y = (m_Point.y + m_Point.y + m_Size) / 2;
	int S_len = m_Size / 2;
	
	int S_degree = m_S * (360 / 30) +10;

	CPen pen;
	pen.CreatePen(PS_DOT, 2, RGB(0, 0,0));    
	CPen* oldPen = m_pDC->SelectObject(&pen);
	CBrush brush1, *oldbrush1;
	brush1.CreateSolidBrush(RGB(240, 240, 240));
	oldbrush1 = m_pDC->SelectObject(&brush1);
	m_pDC->Ellipse(m_Point.x, m_Point.y, m_Point.x + m_Size, m_Point.y + m_Size);
	m_pDC->SelectObject(oldbrush1);
	brush1.DeleteObject();
	m_pDC->SelectObject(oldPen);

	CPen pen1;
	pen1.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	CPen* oldPen1 = m_pDC->SelectObject(&pen1);
	int S_x = clock_center_x + cos((double)S_degree*M_PI / 180.0) * (S_len - 15);
	int S_y = clock_center_y + sin((double)S_degree*M_PI / 180.0) * (S_len - 15);
	m_pDC->MoveTo(clock_center_x, clock_center_y);
	m_pDC->LineTo(S_x, S_y);
	m_pDC->SelectObject(oldPen1);


	for (S1 = 0; S1 < 30; S1++) {
		int S_clock = S1 * (360 / 30) - 90;
		int start_x = clock_center_x + cos((double)S_clock*M_PI / 180.0) * (S_len - 5);
		int start_y = clock_center_y + sin((double)S_clock*M_PI / 180.0) * (S_len - 5);

		int end_x = clock_center_x + cos((double)S_clock*M_PI / 180.0) * (S_len - 10);
		int end_y = clock_center_y + sin((double)S_clock*M_PI / 180.0) * (S_len - 10);
		m_pDC->MoveTo(start_x, start_y);
		m_pDC->LineTo(end_x, end_y);
	}
	

}