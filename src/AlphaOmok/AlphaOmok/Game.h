#pragma once

#include <vector>
#include "Common.h"
#include "Subject.h"
#include "OmokUtil.h"

using namespace std;

typedef struct Lines {
	vector<char> leftUp;
	vector<char> rightUp;
	vector<char> horizontal;
	vector<char> vertical;
} Lines;

const int NO_BAN_METHOD = 1;
const int DOUBLE_3 = 33;
const int DOUBLE_4 = 44;
const int YUKMOK = 6;

class Game:
	public Subject
{

private:
	char m_CurrentTurn;
	vector<Piece> m_History;
	char** m_Board;
	int m_Status;
	Point m_Cursor;

public:
	Game();
	~Game();
	//착수
	bool PutPiece(int row, int col);
	//승리체크 
	bool winCheck(int row, int col);
	//턴변경
	void reserveTurn();
	//새 게임
	void Init();
	char markPiece(Point x, Point current);
	//무르기
	void Undo();
	void printVector(vector<char> line);
	//찍힌점에서 4방향 라인 리턴
	Lines GetLines(int row, int col);
	//보드 리턴 
	char** GetBoard();
	//현재 턴 리턴 
	char GetCurrentTurn();
	//현재 게임 상태 리턴
	int GetStatus();
	//게임 상태 지정
	void SetStatus(int status);
	//현재커서 리턴 
	Point GetCursor();
	//커서 셋팅 
	void SetCursor(Point cursor);
	//현재 히스토리 리턴
	vector<Piece> GetHistory();
	//금수체크
	int banMethodCheck(int row, int col);

	bool isOpen3(vector<char> line);
	bool isOpen4(vector<char> line);
	bool isYukmok(vector<char> line);
};

