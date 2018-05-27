#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	
	m_Board = new char*[ROW];
	for (int i = 0; i < ROW; i++) {
		m_Board[i] = new char[COL];
		for (int j = 0; j < COL; j++) {
			m_Board[i][j] = EMPTY;
		}
	}
	this->Init();
}

void Game::Init() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			m_Board[i][j] = EMPTY;
		}
	}
	m_History.clear();
	m_CurrentTurn = BLACK;
	m_Status = GAME_ING;
	PutPiece(ROW / 2, COL / 2);
	reserveTurn();
	Point cursor;
	cursor.x = COL / 2;
	cursor.y = ROW / 2;
	this->SetCursor(cursor);
}

char** Game::GetBoard() {
	return m_Board;
}

char Game::GetCurrentTurn() {
	return m_CurrentTurn;
}
bool Game::PutPiece(int row, int col) {
	if (m_Status == GAME_ING) {
		if (m_Board[row][col] == EMPTY) {
			m_Board[row][col] = m_CurrentTurn;
			Piece piece;
			piece.x = col;
			piece.y = row;
			piece.type = m_CurrentTurn;
			m_History.push_back(piece);
			return true;
		}
		else {
			return false;
		}
	}
}
char Game::markPiece(Point p, Point current) {
	if (p.x == current.x  && p.y == current.y) {
		return CURRENT;
	}
	else {
		return m_Board[p.y][p.x];
	}
}

Lines Game::GetLines(int row, int col) {
	Lines lines;
	Point leftUpStart, leftUpEnd, rightUpStart, rightUpEnd;
	Point vStart, hStart;
	Point current;

	current.x = col;
	current.y = row;

	leftUpStart.y = leftUpEnd.y = rightUpStart.y = rightUpEnd.y = row;
	leftUpStart.x = leftUpEnd.x = rightUpStart.x = rightUpEnd.x = col;


	if (!(row == 0 || col == 0)) {
		while (--leftUpStart.y > 0 & --leftUpStart.x > 0);
		while (--rightUpStart.y > 0 & ++rightUpStart.x < (COL - 1));
	}

	if (!(row == ROW || col == COL)) {
		while (++leftUpEnd.y < (ROW - 1) & ++leftUpEnd.x < (COL - 1));
		while (++rightUpEnd.y < (ROW - 1) & --rightUpEnd.x > 0);
	}


	while (leftUpStart.y <= leftUpEnd.y && leftUpStart.x <= leftUpEnd.x) {
		lines.leftUp.push_back(markPiece(leftUpStart, current));
		leftUpStart.x++;
		leftUpStart.y++;
	}

	while (rightUpStart.y <= rightUpEnd.y && rightUpStart.x >= rightUpEnd.x) {
		lines.rightUp.push_back(markPiece(rightUpStart, current));
		rightUpStart.x--;
		rightUpStart.y++;
	}

	for (int i = 0; i < ROW; i++) {
		vStart.x = col;
		vStart.y = i;
		lines.vertical.push_back(markPiece(vStart, current));
	}

	for (int i = 0; i < COL; i++) {
		hStart.x = i;
		hStart.y = row;
		lines.horizontal.push_back(markPiece(hStart, current));
	}

	return lines;
}

void Game::printVector(vector<char> line) {
	for (char c : line) {
		printf("%c ",c);
	}
	printf("\n");
}

bool Game::winCheck(int row, int col) {

	if (m_Status == GAME_ING) {
		Lines line = GetLines(row, col);
		OmokUtil::replaceCurrent(line.horizontal, m_CurrentTurn);
		OmokUtil::replaceCurrent(line.vertical, m_CurrentTurn);
		OmokUtil::replaceCurrent(line.leftUp, m_CurrentTurn);
		OmokUtil::replaceCurrent(line.rightUp, m_CurrentTurn);

		if (OmokUtil::getMaxContinueCharacterCount(line.horizontal, m_CurrentTurn) == 5 ||
			OmokUtil::getMaxContinueCharacterCount(line.vertical, m_CurrentTurn) == 5 ||
			OmokUtil::getMaxContinueCharacterCount(line.leftUp, m_CurrentTurn) == 5 ||
			OmokUtil::getMaxContinueCharacterCount(line.rightUp, m_CurrentTurn) == 5) {
			m_Status = GAME_END;
			return true;
		}

		m_Status = GAME_ING;
		return false;
	}
}
void Game::Undo() {
	Piece piece = m_History.back();
	m_Board[piece.y][piece.x] = EMPTY;
	m_History.pop_back();
	this->reserveTurn();
}

int Game::GetStatus() {
	return m_Status;
}

vector<Piece> Game::GetHistory() {
	return m_History;
}
void Game::reserveTurn() {
	m_CurrentTurn = m_CurrentTurn == BLACK ? WHITE : BLACK;
}

void Game::SetCursor(Point cursor) {
	m_Cursor = cursor;
}

void Game::SetStatus(int status ) {
	m_Status = status;
}

Point Game::GetCursor() {
	return m_Cursor;
}

Game::~Game()
{
}
