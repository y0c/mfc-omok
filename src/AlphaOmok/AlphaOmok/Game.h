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
	//����
	bool PutPiece(int row, int col);
	//�¸�üũ 
	bool winCheck(int row, int col);
	//�Ϻ���
	void reserveTurn();
	//�� ����
	void Init();
	char markPiece(Point x, Point current);
	//������
	void Undo();
	void printVector(vector<char> line);
	//���������� 4���� ���� ����
	Lines GetLines(int row, int col);
	//���� ���� 
	char** GetBoard();
	//���� �� ���� 
	char GetCurrentTurn();
	//���� ���� ���� ����
	int GetStatus();
	//���� ���� ����
	void SetStatus(int status);
	//����Ŀ�� ���� 
	Point GetCursor();
	//Ŀ�� ���� 
	void SetCursor(Point cursor);
	//���� �����丮 ����
	vector<Piece> GetHistory();
	//�ݼ�üũ
	int banMethodCheck(int row, int col);

	bool isOpen3(vector<char> line);
	bool isOpen4(vector<char> line);
	bool isYukmok(vector<char> line);
};

