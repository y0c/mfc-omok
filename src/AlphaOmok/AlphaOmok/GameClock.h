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
	int m_S;
public:
	void tick() { m_S++;  }
	void SetSeconds(int s) { m_S = s; }
	void Render();
	void notify(string eventType, map<string,void*> data);
	GameClock(CPoint point, int size);
	GameClock();
	~GameClock();
};

