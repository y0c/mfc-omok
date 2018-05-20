#pragma once

#include <vector>
#include "Common.h"
#include "Subject.h"
using namespace std;

class Game:
	public Subject
{

private:
	char m_CurrentTurn;
	vector<Piece> m_History;
	char** m_Board;
public:
	Game();
	~Game();
	//착수
	bool PutPiece(int row, int col);
	//턴변경
	void reserveTurn();
	char** GetBoard();
	char GetCurrentTurn();
	vector<Piece> GetHistory();
};

