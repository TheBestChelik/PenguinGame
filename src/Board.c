#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include "structures.h"

void GenerateBoard(Board board)
{
	// Genarate board function
	for (int x = 0; x < board.size.x; x++)
	{
		board.grid[0 * board.size.y + x] = 0;
	}
	for (int x = 0; x < board.size.x; x++)
	{
		board.grid[(board.size.y - 1) * board.size.y + x] = 0;
	}
	for (int x = 0; x < board.size.y; x++)
	{
		board.grid[x * board.size.y + 0] = 0;
	}
	for (int x = 0; x < board.size.y; x++)
	{
		board.grid[x * board.size.y + (board.size.x - 1)] = 0;
	}
	for (int y = 1; y < board.size.y - 1; y++)
	{
		for (int x = 1; x < board.size.x - 1; x++)
		{
			// Generates a random number of fish between 0 and 3
			int fish = rand() % 4;
			board.grid[y * board.size.y + x] = fish;
		}
	}
}
void DrawBoard(HDC dc, Point start, Board board, Player *players)
{
	// DrwaBoard function draws the board on the main window
	// dc - object where we are going to draw
	// PosX - X coordinate of start of the board
	// PosY - Y coordinate of start of the board
	// cellSize - size(in px) of one cell
	// boardWidth - width of the board (in cells)
	// boardHeight - height of the board (in cells)
	// board[][] - the board, where 0 means no fish, and 1-3 means num of fish
	HDC memDC = CreateCompatibleDC(dc);
	HBITMAP memBM = CreateCompatibleBitmap(dc, board.size.x * board.CellSize, board.size.y * board.CellSize);
	SelectObject(memDC, memBM);
	SelectObject(memDC, GetStockObject(DC_BRUSH));
	int selected = 0, X ,Y;
	for (int y = 0; y < board.size.y; y++)
	{
		for (int x = 0; x < board.size.x; x++)
		{
			switch (board.grid[y * board.size.x + x])
			{
			case 0:
				// Draws a sea block
				SetDCBrushColor(memDC, RGB(0, 0, 255));
				Rectangle(memDC, x * board.CellSize, y * board.CellSize, board.CellSize * (x + 1), board.CellSize * (y + 1));
				break;
			case 1:
				// Draws an ice floe
				SetDCBrushColor(memDC, RGB(0, 230, 255));
				Rectangle(memDC, x * board.CellSize, y * board.CellSize, board.CellSize * (x + 1), board.CellSize * (y + 1));
				SetDCBrushColor(memDC, RGB(0, 0, 255));
				// Draws one fish
				Rectangle(memDC, x * board.CellSize + board.CellSize * 0.4, y * board.CellSize + board.CellSize * 0.4, board.CellSize * x + board.CellSize * 0.6, board.CellSize * y + board.CellSize * 0.6);
				break;
			case 2:
				// Draws an ice floe
				SetDCBrushColor(memDC, RGB(0, 230, 255));
				Rectangle(memDC, x * board.CellSize, y * board.CellSize, board.CellSize * (x + 1), board.CellSize * (y + 1));
				SetDCBrushColor(memDC, RGB(0, 0, 255));
				// Draws 2 fish on ice floe
				Rectangle(memDC, x * board.CellSize + board.CellSize * 0.6, y * board.CellSize + board.CellSize * 0.4, board.CellSize * x + board.CellSize * 0.8, board.CellSize * y + board.CellSize * 0.6);
				Rectangle(memDC, x * board.CellSize + board.CellSize * 0.2, y * board.CellSize + board.CellSize * 0.4, board.CellSize * x + board.CellSize * 0.4, board.CellSize * y + board.CellSize * 0.6);
				break;
			case 3:
				// Draws an ice floe
				SetDCBrushColor(memDC, RGB(0, 230, 255));
				Rectangle(memDC, x * board.CellSize, y * board.CellSize, board.CellSize * (x + 1), board.CellSize * (y + 1));
				SetDCBrushColor(memDC, RGB(0, 0, 255));
				// Draws 3 fish on ice floe
				Rectangle(memDC, x * board.CellSize + board.CellSize * 0.4, y * board.CellSize + board.CellSize * 0.2, board.CellSize * x + board.CellSize * 0.6, board.CellSize * y + board.CellSize * 0.4);
				Rectangle(memDC, x * board.CellSize + board.CellSize * 0.2, y * board.CellSize + board.CellSize * 0.6, board.CellSize * x + board.CellSize * 0.4, board.CellSize * y + board.CellSize * 0.8);
				Rectangle(memDC, x * board.CellSize + board.CellSize * 0.6, y * board.CellSize + board.CellSize * 0.6, board.CellSize * x + board.CellSize * 0.8, board.CellSize * y + board.CellSize * 0.8);
				break;
			default:
				SetDCBrushColor(memDC, RGB(0, 230, 255));
				Rectangle(memDC, x * board.CellSize, y * board.CellSize, board.CellSize * (x + 1), board.CellSize * (y + 1));
				//Draw the player's penguin
				if(selected == 0){
					selected = (board.grid[y * board.size.x + x]<-9);
					if(selected){
						(board.grid[y * board.size.x + x]) = (board.grid[y * board.size.x + x])/10;
						X = x;
						Y = y;
						break;
					}
				}
				
				int playerNum  = - (board.grid[y * board.size.x + x]) -1;
				
				SetDCBrushColor(memDC, players[playerNum].PenguinColor);
				
				Ellipse(memDC, x * board.CellSize, y * board.CellSize, board.CellSize * (x + 1), board.CellSize * (y + 1));
				
				
				
				break;
			}
			// Rectangle(memDC, x * board.CellSize, y * board.CellSize, board.CellSize * (x + 1), board.CellSize * (y + 1));
		}
	}
	if(selected){
		int playerNum  = -(board.grid[Y * board.size.x + X]) -1;
		SetDCBrushColor(memDC, (players+playerNum)->PenguinColor);	
				
		Ellipse(memDC, X * board.CellSize-board.CellSize/4, Y * board.CellSize-board.CellSize/4, board.CellSize * (X+1) + board.CellSize/4, board.CellSize * (Y + 1)+ board.CellSize/4);
	}		
	BitBlt(dc, start.x, start.y, board.size.x * board.CellSize, board.size.y * board.CellSize, memDC, 0, 0, SRCCOPY);

	DeleteDC(memDC);
	DeleteObject(memBM);
}

