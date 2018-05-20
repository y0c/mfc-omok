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
public:
	void Render();
	void notify(string eventType, map<string,void*> data);
	GameClock(CPoint point, int size);
	GameClock();
	~GameClock();
};

