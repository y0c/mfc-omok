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
	//Âø¼ö
	bool PutPiece(int row, int col);
	//½Â¸®Ã¼Å© 
	bool winCheck(int row, int col);
	//ÅÏº¯°æ
	void reserveTurn();
	char markPiece(Point x, Point current);
	void printVector(vector<char> line);
	Lines GetLines(int row, int col);
	char** GetBoard();
	char GetCurrentTurn();
	int GetStatus();
	vector<Piece> GetHistory();
};

