#pragma once
#include "CanvasElement.h"
#include "Observer.h"
#include <string>
#include <iostream>
using namespace std;

class GameClock :
	public CanvasElement, 
	public Observer
{
	int m_S = 0;
public:
	void Tick() { m_S = m_S + 1; }
	void SetSeconds(int s) { m_S = s; }
	int GetSeconds() { return m_S; }
	void Render();
	void notify(string eventType, map<string,void*> data);
	GameClock(CPoint point, int size);
	GameClock();
	~GameClock();
};

