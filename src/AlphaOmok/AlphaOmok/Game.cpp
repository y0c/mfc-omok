#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	m_CurrentTurn = BLACK;
	
	m_Board = new char*[ROW];
	for (int i = 0; i < ROW; i++) {
		m_Board[i] = new char[COL];
		for (int j = 0; j < COL; j++) {
			m_Board[i][j] = EMPTY;
		}
	}
}

char** Game::GetBoard() {
	return m_Board;
}

Game::~Game()
{
}
