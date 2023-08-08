#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>

#define MaxBoardSize 40



void GenerateBoard(Board board);


void DrawBoard(HDC dc, Point start, Board board, Player *players);
