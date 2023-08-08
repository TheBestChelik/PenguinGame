#include "structures.h"

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "Board.h"
#include "GUI.h"
#include "Check_ParseData.h"
#include "CheckingGameRules.h"

#define MaxBoardSize 40
#define BoardPosX 200
#define BoardPosY 50
#define BtnStart_id 1
#define BtnStart_id 1
#define BtnNext_id 2
#define BtnColor_id 3
#define BtnPressedEvent 0xffff

void step(Stage *Stage, Player *players, int *CurrentPlayerNum, int *CurrentPenguinNum, int NumPlayers, int NumPengPerPlayer, HWND *MainTextBox, HWND *HintTextBox, HWND *ScoreTable)
{

	if (*Stage != Initialization)
	{
		FILE *ptr;

		ptr = fopen("GameHints.txt", "r");
		if (ptr == NULL)
		{
			SetWindowText(*HintTextBox, "File with hints not found((");
		}
		else
		{
			char *line = NULL;
			size_t len = 0;
			ssize_t read;
			char **lines = NULL;
			int line_count = 0;
			// MessageBox(NULL, "Reading File", "AA", MB_OK);
			while ((read = getline(&line, &len, ptr)) != -1)
			{
				// Allocate memory for each line and copy the content
				char *line_copy = (char *)malloc(read + 1);
				strcpy(line_copy, line);

				lines = realloc(lines, sizeof(char *) * (line_count + 1));
				lines[line_count++] = line_copy;

				line = NULL;
				len = 0;
			}
			fclose(ptr);
			// MessageBox(NULL, "File closed", "AA", MB_OK);
			if (line_count == 0)
			{
				MessageBox(NULL, "no lines", "AA", MB_OK);
				SetWindowText(*HintTextBox, "File with hints is empty(");
			}
			else
			{
				srand(time(0));
				char *result = (char *)malloc(sizeof(char) * 100);
				strcpy(result, "Hint:\n\n");

				strcat(result, lines[rand() % line_count]);

				SetWindowText(*HintTextBox, result);
				free(result);
			}
			// Free the allocated memory for each line
			for (int i = 0; i < line_count; i++)
			{
				free(lines[i]);
			}
			free(lines);
			if (line)
			{
				free(line);
			}
		}
	}
	switch (*Stage)
	{
	case Initialization:
	{
		(*CurrentPlayerNum) += 1;
		if ((*CurrentPlayerNum) == NumPlayers)
		{
			*Stage = Placement;
			*CurrentPlayerNum = 0;
			*CurrentPenguinNum = 0;

			break;
		}
		char buf[45];
		snprintf(buf, 45, "Player %d", *CurrentPlayerNum + 1);
		SetWindowText(*MainTextBox, buf);
		break;
	}
	case Placement:
	{

		*(CurrentPlayerNum) += 1;
		UpdateScoreTable(ScoreTable, players, NumPlayers);
		if (*(CurrentPlayerNum) == NumPlayers)
		{
			*CurrentPlayerNum = 0;
			if (*CurrentPenguinNum == NumPengPerPlayer - 1)
			{
				*Stage = Movement;
				*CurrentPenguinNum = -1;
			}
			else
			{
				*(CurrentPenguinNum) += 1;
			}
		}

		if (*(Stage) == Placement)
		{
			char buf[45];
			snprintf(buf, 45, "%s has to place one penguin", players[*CurrentPlayerNum].Name);
			SetWindowText(*MainTextBox, buf);
		}
		else
		{
			char buf[45];
			snprintf(buf, 45, "%s has to make a move", players[0].Name);
			SetWindowText(*MainTextBox, buf);
		}
		break;
	}
	case Movement:
	{
		*(CurrentPlayerNum) += 1;
		*(CurrentPenguinNum) = -1;
		UpdateScoreTable(ScoreTable, players, NumPlayers);
		if (*CurrentPlayerNum == NumPlayers)
		{
			*CurrentPlayerNum = 0;
		}
		char buf[45];
		snprintf(buf, 45, "%s has to make a move", players[*CurrentPlayerNum].Name);
		SetWindowText(*MainTextBox, buf);
	}
	default:
		break;
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc = {0};
	HDC dc;

	int BoardCreated = 0, WindowW = 200, WindowH = 375, NumPlayers, NumPengPerPlayer;

	Board board;
	Initial_GUI hwnds;
	AskingPlayers_GUI AskingHWNDs;
	///
	HWND ScoreTable, MainTextBox, HintTextBox;

	MSG msg = {0};

	INIT_GUI(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WindowW, WindowH, &dc, &wc, &hwnds);
	AskingHWNDs.hwnd = hwnds.hwnd;

	Player *players;

	Stage Stage = None;
	int CurrentPlayerNum = 0;
	int CurrentPenguinNum = 0;
	Point Start = makePoint(BoardPosX, BoardPosY);

	int ColorSet = 0;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		switch (msg.message)
		{
		case WM_QUIT:
		{
			break;
		}
		case WM_PAINT:
		{
			if (BoardCreated)
			{
				RECT map;
				GetClientRect(hwnds.hwnd, &map);
				if ((map.right - BoardPosX) / board.size.x > (map.bottom - BoardPosY) / board.size.y)
				{
					board.CellSize = (map.bottom - BoardPosY) / board.size.y;
				}
				else
				{
					board.CellSize = (map.right - BoardPosX) / board.size.x;
				}
				DrawBoard(dc, Start, board, players);
			}
			if (Stage == Initialization)
			{
				if (ColorSet)
				{
					HDC memDC = CreateCompatibleDC(dc);
					HBITMAP memBM = CreateCompatibleBitmap(dc, 102, 102);
					SelectObject(memDC, memBM);
					SelectObject(memDC, GetStockObject(DC_BRUSH));
					SetDCBrushColor(memDC, RGB(255, 255, 255));
					Rectangle(memDC, 0, 0, 102, 102);
					SetDCBrushColor(memDC, players[CurrentPlayerNum].PenguinColor);
					Ellipse(memDC, 1, 1, 101, 101);
					BitBlt(dc, 25, 110, 100, 100, memDC, 1, 1, SRCCOPY);

					DeleteDC(memDC);
					DeleteObject(memBM);
				}
			}
			// MessageBox(hwnd, "Paint!", "Painr",MB_OK);
			break;
		}
		case BtnPressedEvent:
		{
			switch (LOWORD(msg.wParam))
			{
			case BtnStart_id:
				/* code */
				GetUserInput(&hwnds.hWidth, &hwnds.hHeight, &hwnds.hCell_Size, &hwnds.hPlayers, &hwnds.hPenguins, &board, &NumPlayers, &NumPengPerPlayer);
				int errCode = CheckData(board, NumPlayers, NumPengPerPlayer);
				if (errCode == 0)
				{
					DeleteControls(&hwnds);
					InitAskPlayersGUI(&AskingHWNDs);

					players = calloc(NumPlayers, sizeof(Player));

					Stage = Initialization;
					char buf[45];
					snprintf(buf, 45, "Player %d", CurrentPlayerNum + 1);
					SetWindowText(AskingHWNDs.MainLabel, buf);
					// step(&Stage, players, &CurrentPlayerNum, &CurrentPenguinNum, NumPlayers, NumPengPerPlayer, &AskingHWNDs.MainLabel, &HintTextBox, &ScoreTable);
				}
				else
				{
					ParseInputError(errCode, &hwnds.hwnd);
				}
				break;
			case BtnColor_id:
			{
				CHOOSECOLOR cc;					// common dialog box structure
				static COLORREF acrCustClr[16]; // array of custom colors
				static DWORD rgbCurrent;		// initial color selection

				// Initialize CHOOSECOLOR
				ZeroMemory(&cc, sizeof(cc));
				cc.lStructSize = sizeof(cc);
				cc.hwndOwner = hwnds.hwnd;
				cc.lpCustColors = (LPDWORD)acrCustClr;
				cc.rgbResult = rgbCurrent;
				cc.Flags = CC_FULLOPEN | CC_RGBINIT;

				if (ChooseColor(&cc) == TRUE)
				{
					ColorSet = 1;
					players[CurrentPlayerNum].PenguinColor = cc.rgbResult;
					SetWindowText(AskingHWNDs.Color, "Color selected");
					HDC memDC = CreateCompatibleDC(dc);
					HBITMAP memBM = CreateCompatibleBitmap(dc, 102, 102);
					SelectObject(memDC, memBM);
					SelectObject(memDC, GetStockObject(DC_BRUSH));
					SetDCBrushColor(memDC, RGB(255, 255, 255));
					Rectangle(memDC, 0, 0, 102, 102);
					SetDCBrushColor(memDC, players[CurrentPlayerNum].PenguinColor);
					Ellipse(memDC, 1, 1, 101, 101);

					BitBlt(dc, 25, 110, 100, 100, memDC, 1, 1, SRCCOPY);

					DeleteDC(memDC);
					DeleteObject(memBM);
				}

				break;
			}
			case BtnNext_id:
			{
				char buff[20] = "";

				GetWindowText(AskingHWNDs.Name, buff, 20);

				if (buff[0] != '\0' && ColorSet)
				{

					strncpy(players[CurrentPlayerNum].Name, buff, 20);

					ColorSet = 0;
					SetWindowText(AskingHWNDs.Name, "");
					SetWindowText(AskingHWNDs.Color, "Select color");
					step(&Stage, &players, &CurrentPlayerNum, &CurrentPenguinNum, NumPlayers, NumPengPerPlayer, &AskingHWNDs.MainLabel, &HintTextBox, &ScoreTable);
					HDC memDC = CreateCompatibleDC(dc);
					HBITMAP memBM = CreateCompatibleBitmap(dc, 102, 102);
					SelectObject(memDC, memBM);
					SelectObject(memDC, GetStockObject(DC_BRUSH));
					SetDCBrushColor(memDC, RGB(255, 255, 255));
					Rectangle(memDC, 0, 0, 102, 102);
					BitBlt(dc, 25, 110, 100, 100, memDC, 1, 1, SRCCOPY);

					DeleteDC(memDC);
					DeleteObject(memBM);
				}
				if (Stage == Placement)
				{
					DeleteAskingGUI(&AskingHWNDs);
					board.grid = calloc(board.size.x * board.size.y, sizeof(int));
					GenerateBoard(board);
					WindowW = (board.CellSize + 1) * board.size.x + BoardPosX + 50;
					if (WindowH <= (board.CellSize + 1) * board.size.y + BoardPosY + 20)
						WindowH = (board.CellSize + 1) * board.size.y + BoardPosY + 20;
					SetWindowPos(hwnds.hwnd, HWND_TOP, 0, 0, WindowW, WindowH, SWP_SHOWWINDOW);
					DrawBoard(dc, Start, board, players);
					BoardCreated = 1;

					INIT_GUI_PLAYING(&hwnds.hwnd, &ScoreTable, &MainTextBox, &HintTextBox);
					char buf[45];
					snprintf(buf, 45, "%s has to place one penguin", players[CurrentPlayerNum].Name);
					SetWindowText(MainTextBox, buf);
					for (int i = 0; i < NumPlayers; i++)
					{
						//	MessageBox(hwnds.hwnd, players[i].Name, "aa", MB_OK);
						AddRow(&ScoreTable, (players + i)->Name, "0", i);
						players[i].penguinsArr = calloc(NumPengPerPlayer, sizeof(Point));
					}
				}
			}
			default:
				break;
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			switch (msg.wParam)
			{
			case MK_LBUTTON:
			{
				switch (Stage)
				{
				case Placement:
				{
					int collum = (GET_X_LPARAM(msg.lParam) - BoardPosX) / board.CellSize;
					int row = (GET_Y_LPARAM(msg.lParam) - BoardPosY) / board.CellSize;
					// char buf[2];
					if (collum >= 0 && row >= 0 && collum < board.size.x && row < board.size.y)
					{
						int errorCode = CanBePlaced(makePoint(collum, row), board.grid, board);
						if (errorCode == 1)
						{
							board.grid[row * board.size.x + collum] = -(CurrentPlayerNum + 1);
							players[CurrentPlayerNum].penguinsArr[CurrentPenguinNum] = makePoint(collum, row);
							players[CurrentPlayerNum].Score += 1;

							DrawBoard(dc, Start, board, players);
							step(&Stage, players, &CurrentPlayerNum, &CurrentPenguinNum, NumPlayers, NumPengPerPlayer, &MainTextBox, &HintTextBox, &ScoreTable);
						}
						else
						{
							SetWindowText(MainTextBox, ParseErrorPlacenet(errorCode));
						}
					}
				}
				break;
				case Movement:
				{

					int collum = (GET_X_LPARAM(msg.lParam) - BoardPosX) / board.CellSize;
					int row = (GET_Y_LPARAM(msg.lParam) - BoardPosY) / board.CellSize;
					if (collum >= 0 && row >= 0 && collum < board.size.x && row < board.size.y)
					{
						if (CurrentPenguinNum == -1)
						{
							if (board.grid[row * board.size.x + collum] < 0)
							{
								if (board.grid[row * board.size.x + collum] == -CurrentPlayerNum - 1)
								{

									for (int i = 0; i < NumPengPerPlayer; i++)
									{
										if (players[CurrentPlayerNum].penguinsArr[i].x == collum &&
											players[CurrentPlayerNum].penguinsArr[i].y == row)
										{
											CurrentPenguinNum = i;
											break;
										}
									}
									if (PenguinCanMove(players[CurrentPlayerNum].penguinsArr[CurrentPenguinNum], board.grid, board))
									{
										board.grid[row * board.size.x + collum] *= 10;
										SetWindowText(MainTextBox, "Now Click on cell, you want to move on");
										DrawBoard(dc, Start, board, players);
									}
									else
									{
										CurrentPenguinNum = -1;
										SetWindowText(MainTextBox, "This penguin cannot move, chose another one!");
									}
								}
							}
						}
						else
						{
							int errorCode = MoveIsLegal(players[CurrentPlayerNum].penguinsArr[CurrentPenguinNum], makePoint(collum, row), board.grid, board);
							if (errorCode == 1)
							{
								int prevX = players[CurrentPlayerNum].penguinsArr[CurrentPenguinNum].x;
								int prevY = players[CurrentPlayerNum].penguinsArr[CurrentPenguinNum].y;
								players[CurrentPlayerNum].penguinsArr[CurrentPenguinNum] = makePoint(collum, row);
								board.grid[prevY * board.size.x + prevX] = 0;
								players[CurrentPlayerNum].Score += board.grid[row * board.size.x + collum];
								board.grid[row * board.size.x + collum] = -CurrentPlayerNum - 1;
								DrawBoard(dc, Start, board, players);
								step(&Stage, players, &CurrentPlayerNum, &CurrentPenguinNum, NumPlayers, NumPengPerPlayer, &MainTextBox, &HintTextBox, &ScoreTable);
								// Checking if any of next players penguins can move

								int stuckPlayers = 0;
								for (int i = 0; i < NumPlayers; i++)
								{
									int stuckPenguins = 0;
									for (int j = 0; j < NumPengPerPlayer; j++)
									{
										if (PenguinCanMove(players[CurrentPlayerNum].penguinsArr[j], board.grid, board) == 0)
										{
											stuckPenguins++;
										}
									}
									if (stuckPenguins == NumPengPerPlayer)
									{
										stuckPlayers++;
										step(&Stage, players, &CurrentPlayerNum, &CurrentPenguinNum, NumPlayers, NumPengPerPlayer, &MainTextBox, &HintTextBox, &ScoreTable);
										// break;
									}
									else
									{
										break;
									}
								}
								if (stuckPlayers == NumPlayers)
								{
									Stage = End;
									int WinnerNum = 0;
									for (int i = 0; i < NumPlayers; i++)
									{
										if (players[i].Score > players[WinnerNum].Score)
										{
											WinnerNum = i;
										}
									}

									char buf[45];

									snprintf(buf, 45, "%s won this game!", players[WinnerNum].Name);
									SetWindowText(MainTextBox, buf);
								}
							}
							else
							{
								SetWindowText(MainTextBox, ParseErrorMovement(errorCode));
							}
						}
					}
				}

				default:

					break;
				}
			}
			default:
				break;
			}

			break;
		}
		case WM_RBUTTONDOWN:
		{
			int collum = (GET_X_LPARAM(msg.lParam) - BoardPosX) / board.CellSize;
			int row = (GET_Y_LPARAM(msg.lParam) - BoardPosY) / board.CellSize;
			if (collum >= 0 && row >= 0 && collum < board.size.x && row < board.size.y)
			{
				if (board.grid[row * board.size.x + collum] >= 0)
				{
					char buf[45];
					snprintf(buf, 45, "%d fish on this cell", board.grid[row * board.size.x + collum]);
					MessageBox(hwnds.hwnd, buf, "Info", MB_OK);
				}
				else
				{
					char buf[45];
					snprintf(buf, 45, "It is %s's penguin", players[-board.grid[row * board.size.x + collum] - 1].Name);
					MessageBox(hwnds.hwnd, buf, "Info", MB_OK);
				}
			}
		}
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
