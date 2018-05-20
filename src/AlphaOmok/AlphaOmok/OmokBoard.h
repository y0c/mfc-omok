#pragma once
#include "CanvasElement.h"
#include "Common.h"
#include "Game.h"
class OmokBoard :
	public CanvasElement
{
	Game* m_Game;
	int m_RowSpace;
public:
	OmokBoard();
	OmokBoard(CPoint point, int size);
	~OmokBoard();
	void Render(CDC* pDC);
	void OnClick(CPoint point);

	void SetGame(Game* game);
};

