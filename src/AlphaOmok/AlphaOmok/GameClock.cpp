#include "stdafx.h"
#include "GameClock.h"

GameClock::GameClock(CPoint point, int size) {
	m_Point = point;
	m_Size = size;
}

GameClock::GameClock()
{
}


GameClock::~GameClock()
{
}

void GameClock::notify(string eventType, map<string, void*> data) {
	cout << eventType << endl;
	char* turn = (char*)data["turn"];
	cout << *turn << endl;
}
void GameClock::Render() {
	m_pDC->Ellipse(m_Point.x, m_Point.y, m_Point.x + m_Size, m_Point.y + m_Size);
}