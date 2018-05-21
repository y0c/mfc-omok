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

class Game:
	public Subject
{

private:
	char m_CurrentTurn;
	vector<Piece> m_History;
	char** m_Board;
	int m_Status;

public:
	Game();
	~Game();
	//����
	bool PutPiece(int row, int col);
	//�¸�üũ 
	bool winCheck(int row, int col);
	//�Ϻ���
	void reserveTurn();
	char markPiece(Point x, Point current);
	void printVector(vector<char> line);
	Lines GetLines(int row, int col);
	char** GetBoard();
	char GetCurrentTurn();
	int GetStatus();
	vector<Piece> GetHistory();
};

