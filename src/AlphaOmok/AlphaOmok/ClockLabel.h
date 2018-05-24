#pragma once
#include "CanvasElement.h"
class ClockLabel :
	public CanvasElement
{
	int m_S;
public:
	ClockLabel();
	ClockLabel(CPoint point, int size);
	~ClockLabel();
	void Render();
	void SetSeconds(int s) { m_S = s; }
};

