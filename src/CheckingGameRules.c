#include "structures.h"

int PenguinCanMove(Point penguin, int *grid, Board board)
{
	// YousefCode
	if ((grid[(penguin.y * board.size.y + penguin.x) + 1] > 0) || grid[(penguin.y * board.size.y + penguin.x) - 1] > 0 || grid[((penguin.y - 1) * board.size.y + penguin.x)] > 0 || grid[((penguin.y + 1) * board.size.y + penguin.x)] > 0)
	{
		if ((grid[(penguin.y * board.size.y + penguin.x) + 1] < 3) || grid[(penguin.y * board.size.y + penguin.x) - 1] < 3 || grid[((penguin.y - 1) * board.size.y + penguin.x)] < 3 || grid[((penguin.y + 1) * board.size.y + penguin.x)] < 3)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
int MoveIsLegal(Point penguin, Point move, int *grid, Board board)
{
	int moveIsLegal;
	if ((penguin.x == move.x) || (penguin.y == move.y))
	{
		if(grid[move.y * board.size.y + move.x] < 0)
		{
			moveIsLegal = -2;
		}
		else if (grid[move.y * board.size.y + move.x] == 0)
		{
			moveIsLegal = -4;
		}
		else if (penguin.x < move.x)
		{
			for (int i = penguin.x + 1; i <= move.x; i++)
			{
				if(grid[move.y * board.size.y + i] <= 0)
				{
					moveIsLegal = -3;
					break;
				}
				else
				{
					moveIsLegal = 1;
				}
			}
		}
		else if (penguin.y < move.y)
		{
			for (int i = penguin.y + 1; i <= move.y; i++)
			{
				if(grid[i * board.size.y + move.x] <= 0)
				{
					moveIsLegal = -3;
					break;
				}
				else
				{
					moveIsLegal = 1;
				}
			}
		}
		else if (penguin.x > move.x)
		{
			for (int i = move.x; i < penguin.x; i++)
			{
				if(grid[move.y * board.size.y + i] <= 0)
				{
					moveIsLegal = -3;
					break;
				}
				else
				{
					moveIsLegal = 1;
				}
			}
		}
		else if (penguin.y > move.y)
		{
			for (int i = move.y; i < penguin.y; i++)
			{
				if(grid[i * board.size.y + move.x] <= 0)
				{
					moveIsLegal = -3;
					break;
				}
				else
				{
					moveIsLegal = 1;
				}
			}
		}
		else
		{
		moveIsLegal = 1;
		}
	}
	else 
	{
		moveIsLegal = -1;
	}
	return moveIsLegal;

}
int CanBePlaced(Point pos, int *grid, Board board)
{
	// Yousef's Code
	if (grid[(pos.y * board.size.y + pos.x)] == 1)
	{
		return 1;
	}
	else if (grid[(pos.y * board.size.y + pos.x)] < 0)
	{
		return -1;
	}
	else if (grid[(pos.y * board.size.y + pos.x)] == 0)
	{
		return 0;
	}
	else if (grid[(pos.y * board.size.y + pos.x)] > 1)
	{
		return -2;
	}
}
