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

const int BOARD_X = 50;
const int BOARD_Y = 50;
const int BOARD_SIZE = 700;
const int CLOCK_SIZE = 80;

const int WINDOW_WIDTH = 830;
const int WINDOW_HEIGHT = 1100;

const int GAME_ING = 0;
const int GAME_END = 1;
typedef struct Point {
	int x;
	int y;
} Point;

typedef struct Piece {
	int x;
	int y;
	char type;
} Piece;

typedef struct Group {
	int startIndex;
	int endIndex;
} Group;

#endif