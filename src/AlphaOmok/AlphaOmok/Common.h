#pragma once
#ifndef COMMON_H
#define COMMON_H
using namespace std;

const char BLACK = 'X';
const char WHITE = 'O';
const char EMPTY = '-';
const char CURRENT = 'C';

const int ROW = 15;
const int COL = 15;
const int BOARD_SIZE = 500;


typedef struct Point {
	int x;
	int y;
} Point;

typedef struct Piece {
	int x;
	int y;
	char type;
} Piece;
#endif