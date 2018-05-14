#pragma once
#include "CanvasElement.h"
#include "Common.h"

class OmokBoard :
	public CanvasElement
{
	int m_RowSpace;
public:
	OmokBoard();
	OmokBoard(CPoint point, int size);
	~OmokBoard();
	void Render(CDC* pDC);

};

