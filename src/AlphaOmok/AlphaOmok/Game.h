#pragma once

#include <vector>
#include "Common.h"
using namespace std;

class Game
{

private:
	char m_CurrentTurn;
	vector<Piece> m_History;
	char** m_Board;
public:
	Game();
	~Game();
	bool PutPiece(int row, int col);
	char** GetBoard();

};

