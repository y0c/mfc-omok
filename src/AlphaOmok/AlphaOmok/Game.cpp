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

char Game::GetCurrentTurn() {
	return m_CurrentTurn;
}
bool Game::PutPiece(int row, int col) {
	if (m_Board[row][col] == EMPTY) {
		m_Board[row][col] = m_CurrentTurn;
		Piece piece;
		piece.x = col;
		piece.y = row;
		piece.type = m_CurrentTurn;
		m_History.push_back(piece);
		this->reserveTurn();
		map<string, void*> data;
		data.insert(pair<string, void*>("turn",&m_CurrentTurn));
		this->notifyAll("PUT_PIECE",data);
		return true;
	} else {
		return false;
	}
}
vector<Piece> Game::GetHistory() {
	return m_History;
}
void Game::reserveTurn() {
	m_CurrentTurn = m_CurrentTurn == BLACK ? WHITE : BLACK;
}
Game::~Game()
{
}
