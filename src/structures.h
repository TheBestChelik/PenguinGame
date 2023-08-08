#include <windows.h>


typedef struct Point
{
    int x;
    int y;
} Point;
typedef struct Board
{
	struct Point size;
	int CellSize;
	int* grid;
} Board;
typedef struct Color
{
	int red;
	int green;
	int blue;
} Color;
typedef struct Player
{
	struct Point *penguinsArr;
	char Name[20];
	COLORREF PenguinColor;
	//struct Color PenguinColor;
	int Score;
} Player;

typedef struct Initial_GUI
{
	HWND hwnd;
	HWND hWidth;
	HWND hHeight;
	HWND hPlayers;
	HWND hPenguins;
	HWND hCell_Size;
	HWND size;
	HWND wid;
	HWND hei;
	HWND play;
	HWND cell_size_text;
	HWND info_players;
	HWND num_players;
	HWND penq_per_player;
	HWND Start_btn;
} Initial_GUI;
typedef struct AskingPlayers_GUI
{
	HWND hwnd;
	HWND MainLabel;
	HWND NameLabel;
	HWND Name;
	HWND Color;
	HWND NextBtn;
} AskingPlayers_GUI;


typedef enum Stage {None = -1,Initialization = 0, Placement = 1, Movement = 2, End = 3} Stage;

struct Point makePoint(int x, int y);
