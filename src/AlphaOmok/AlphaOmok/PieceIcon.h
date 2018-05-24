#pragma once
#include "CanvasElement.h"
#include "Common.h"
class PieceIcon :
	public CanvasElement
{
	char m_Type;
public:
	PieceIcon();
	PieceIcon(CPoint point, int size, char type);
	~PieceIcon();
	void Render();
};

