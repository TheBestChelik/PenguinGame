#include "structures.h"

int CheckData(Board board, int NumPlayers, int NumPenguinsPerPlayer)
{
	//Checks if user input is correct
	//H - height of the board(in cells)
	//W - width of board(in cells)
	//NumPlayers - Number of players
	//NumPenguins - Number of penguins per one player
	if(board.size.y<10)
		return 1;
	if(board.size.x<10)
		return 2;
	if(board.CellSize<10)
		return 3;
	if(board.size.y>100)
		return 4;
	if(board.size.x>100)
		return 5;
	if(NumPenguinsPerPlayer<1)
		return 6;
	if(NumPlayers<2)
		return 7;
	if(NumPlayers*NumPenguinsPerPlayer>board.size.x*board.size.y*2/3)
		return 8;	
	return 0;
}

char* ParseErrorPlacenet(int ErrorCode)
{
    //Alona's code
    if(ErrorCode == 0)
    {
        return "Penguin can't be placed on a sea block";
    }
    else if(ErrorCode == -1)
    {
        return "There is a penguin on this block already";
    }
    else if(ErrorCode == -2)
    {
        return "Penguin can only be placed on a floe with only 1 fish";
    } 
}
char* ParseErrorMovement(int errorCode){
    if (errorCode == -1)
    {
        return "Penguin can only move in a straight line";
    }
    else if (errorCode == -2)
    {
        return "Chosen block is occupied by another player";
    }
    else if (errorCode == -3)
    {
        return "There is an obstacle in the way";
    }
    else if (errorCode == -4)
    {
        return "Chosen block is a sea block";
    }
}
