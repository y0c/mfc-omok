#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	
	m_Board = new char*[ROW];
	for (int i = 0; i <= ROW; i++) {
		m_Board[i] = new char[COL];
		for (int j = 0; j <= COL; j++) {
			m_Board[i][j] = EMPTY;
		}
	}
	Init();
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
bool Game::isBothClosed(vector<char> line, Group g) {
	char reverseTurn = (m_CurrentTurn == WHITE) ? BLACK : WHITE;
	//양쪽다 두칸전이 있는경우 
	if (g.startIndex - 1 > 0 && g.endIndex + 1 < line.size() - 1) {
		return line[g.startIndex - 1] == reverseTurn && line[g.endIndex + 1] == reverseTurn;
	}
	else if (g.startIndex - 1 < 0) {
		return line[g.endIndex + 1] == reverseTurn;
	}
	else if (g.endIndex + 1 > line.size() - 1) {
		return line[g.startIndex - 1] == reverseTurn;
	}

	return false;
}
bool Game::isOpen3(vector<char> line) {
	return line[0] == EMPTY &&
		line[line.size() - 1] == EMPTY &&
		OmokUtil::getCharacterCount(line, m_CurrentTurn) == 3;
}

bool Game::isOpen4(vector<char> line) {
	if ((line[0] != EMPTY &&
		line[line.size() - 1] != EMPTY) &&
		OmokUtil::getMaxContinueCharacterCount(line,m_CurrentTurn) == 4){
		return false;
	} 
	
	return OmokUtil::getCharacterCount(line, m_CurrentTurn) == 4;
}

bool Game::isYukmok(vector<char> line) {
	return OmokUtil::getCharacterCount(line, m_CurrentTurn) == 6;
}

int Game::banMethodCheck(int row, int col) {
	Lines lines = GetLines(row,col);

	int open3Cnt = 0;
	int open4Cnt = 0;
	int yukmokCnt = 0;
	 
	vector<vector<char>> lineArr;

	lineArr.push_back(lines.horizontal);
	lineArr.push_back(lines.leftUp);
	lineArr.push_back(lines.rightUp);
	lineArr.push_back(lines.vertical);

	for (int i = 0; i < lineArr.size(); i++) {
		vector<char> line = lineArr[i];
		int currentIndex = OmokUtil::getCurrentIndexOf(line);
		OmokUtil::replaceCurrent(line, m_CurrentTurn);
		Group currentGroup = OmokUtil::getSamePieceGroup(line, m_CurrentTurn, currentIndex);
		Group result = currentGroup;

		if ( currentGroup.startIndex - 1 > -1 && line[currentGroup.startIndex - 1] == EMPTY) {
			if (currentGroup.startIndex - 2 > -1 && line[currentGroup.startIndex - 2] == m_CurrentTurn) {
				//한칸 떨어진곳에 같은 돌 그룹
				Group distanceGroup = OmokUtil::getSamePieceGroup(line, m_CurrentTurn, currentGroup.startIndex - 2);
				//떨어진 돌 그룹이있다면
				result.startIndex = distanceGroup.startIndex;
			}
		}
		
		if ( currentGroup.endIndex + 1 < line.size() && line[currentGroup.endIndex + 1] == EMPTY) {
			if (currentGroup.endIndex + 2 < line.size() && line[currentGroup.endIndex + 2] == m_CurrentTurn) {
				Group distanceGruop = OmokUtil::getSamePieceGroup(line, m_CurrentTurn, currentGroup.endIndex + 2);
				result.endIndex = distanceGruop.endIndex;
			}
		}


		if (result.startIndex - 1 >= 0) {
			result.startIndex--;
		}
		if (result.endIndex + 1 <= line.size() - 1) {
			result.endIndex++;
		}
	
	
			
		vector<char> pieceGroup = OmokUtil::sliceLine(line, result.startIndex, result.endIndex + 1);


		if ( isOpen3(pieceGroup) && !isBothClosed(line,result)) {
			open3Cnt++;
		}

		if ( isOpen4(pieceGroup)) {
			open4Cnt++;
		}

		if ( isYukmok(pieceGroup)) {
			yukmokCnt++;
		}

	}	

	if (open3Cnt >= 2) {
		return DOUBLE_3;
	}

	if (open4Cnt >= 2) {
		return DOUBLE_4;
	}

	if (yukmokCnt >= 1) {
		return YUKMOK;
	}

	return NO_BAN_METHOD;
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
