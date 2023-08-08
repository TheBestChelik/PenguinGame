#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>


LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void AddControls(Initial_GUI *hwnds);
void DeleteControls(Initial_GUI *hwnds);
void ReDraw(HDC dc,int StartX, int StartY, int W,int H);
void INIT_GUI(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow,int WindowW, int WindowH,HDC *dc,WNDCLASS *wc,Initial_GUI *hwnds);


void GetUserInput(HWND *hWidth,HWND *hHeight, HWND *hCell_Size, HWND *hPlayers, HWND *hPenguins, Board *board, int *NumPlayers, int *NumPenguins);

void ParseInputError(int errCode, HWND *hwnd);
void INIT_GUI_PLAYING(HWND *hwnd, HWND *ScoreTable, HWND *MainTextBox, HWND *HintTextBox);

void AddRow(HWND *ScoreTable, LPSTR Name, LPSTR Score, int i);

void UpdateScoreTable(HWND *ScoreTable, Player *players, int NumPlayers);   
void InitAskPlayersGUI(AskingPlayers_GUI *AskingHWNDs);
void DeleteAskingGUI(AskingPlayers_GUI *AskingHWNDs);