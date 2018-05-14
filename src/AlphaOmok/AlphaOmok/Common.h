#pragma once

const char BLACK = 'X';
const char WHITE = 'O';
const char EMPTY = '-';
const int ROW = 15;
const int COL = 15;
const int BOARD_SIZE = 500;

typedef struct Point {
	int x;
	int y;
} Point;