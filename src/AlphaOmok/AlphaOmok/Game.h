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
	//����
	bool PutPiece(int row, int col);
	//�Ϻ���
	void reserveTurn();
	char** GetBoard();
	char GetCurrentTurn();
	vector<Piece> GetHistory();
};

