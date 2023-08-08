#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <sys/types.h>

#include "commctrl.h"


#define BtnPressedEvent 0xffff
#define BtnStart_id 1
#define BtnNext_id 2
#define BtnColor_id 3

#include <stdio.h>	
#include "structures.h"
#define BoardPosX 200

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//Default windows api parametrs
{
	switch (msg)
	{
	  case WM_COMMAND:
	  {
		
	  	PostMessage(hwnd,0xffff,wParam,lParam);//Translate button pressed event to the main game loop
	 	
	  	break;

	  }

	case WM_DESTROY:
	{
		PostQuitMessage(0);//Send message to stop programm if main window was closed
		return 0;
		break;
	}
	default:
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);//Default function for all other windows api events
		break;
	}
	}
	return 0;
}


void AddControls(Initial_GUI *hwnds)
{

	//Initialization of all controls
    hwnds->size = CreateWindowW(L"static",L"Please, enter size of the board:",WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 10, 150, 40, hwnds->hwnd,NULL,NULL,NULL);
    hwnds->wid = CreateWindowW(L"static",L"Width:",WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 55, 70, 20, hwnds->hwnd,NULL,NULL,NULL);
    hwnds->hei = CreateWindowW(L"static",L"Height:",WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 85, 70, 20, hwnds->hwnd,NULL,NULL,NULL);
    hwnds->cell_size_text = CreateWindowW(L"static",L"Cell size:",WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 115, 65, 20, hwnds->hwnd,NULL,NULL,NULL);

    hwnds->hWidth = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | ES_CENTER | ES_AUTOHSCROLL | WS_BORDER|ES_NUMBER, 120, 55, 40, 20, hwnds->hwnd,NULL,NULL,NULL);
    hwnds->hHeight = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | ES_CENTER | ES_AUTOHSCROLL | WS_BORDER|ES_NUMBER, 120, 85, 40, 20, hwnds->hwnd,NULL,NULL,NULL);
    hwnds->hCell_Size = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | ES_CENTER | ES_AUTOHSCROLL | WS_BORDER|ES_NUMBER, 120, 115, 40, 20, hwnds->hwnd,NULL,NULL,NULL);

    hwnds->info_players =  CreateWindowW(L"static",L"Please, enter info about players:",WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 145, 150, 40, hwnds->hwnd,NULL,NULL,NULL);
    hwnds->num_players =  CreateWindowW(L"static",L"Number of players:",WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 190, 100, 40, hwnds->hwnd,NULL,NULL,NULL);
    hwnds->penq_per_player =  CreateWindowW(L"static",L"Penguins per player:",WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 235, 100, 40, hwnds->hwnd,NULL,NULL,NULL);

    hwnds->hPlayers = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | ES_CENTER | ES_AUTOHSCROLL | WS_BORDER|ES_NUMBER, 120, 200, 40, 20, hwnds->hwnd,NULL,NULL,NULL);
    hwnds->hPenguins = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | ES_CENTER | ES_AUTOHSCROLL | WS_BORDER|ES_NUMBER, 120, 245, 40, 20, hwnds->hwnd,NULL,NULL,NULL);

    hwnds->Start_btn =  CreateWindowW(L"Button",L"Start!",WS_VISIBLE | WS_CHILD , 10, 285, 150, 20, hwnds->hwnd, (HMENU)BtnStart_id, (HINSTANCE)GetWindowLongPtr(hwnds->hwnd, GWLP_HINSTANCE),NULL);
}

void DeleteControls(Initial_GUI *hwnds)
{
	//Destroying all controls
    DestroyWindow(hwnds->size);
    DestroyWindow(hwnds->wid);
    DestroyWindow(hwnds->hWidth);
    DestroyWindow(hwnds->hei);
    DestroyWindow(hwnds->hHeight);
    DestroyWindow(hwnds->hCell_Size);
	DestroyWindow(hwnds->hPlayers);
	DestroyWindow(hwnds->hPenguins);
	DestroyWindow(hwnds->cell_size_text);
	DestroyWindow(hwnds->info_players);
	DestroyWindow(hwnds->num_players);
	DestroyWindow(hwnds->penq_per_player);
	DestroyWindow(hwnds->Start_btn);
	
}
void INIT_GUI(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow,int WindowW, int WindowH,HDC *dc,WNDCLASS *wc,Initial_GUI *hwnds){
	//Initialization of the main window
	const char CLASS_NAME[] = "PENGUIN";
	(*wc).lpszClassName = CLASS_NAME;
	(*wc).lpfnWndProc = WindowProc;
	(*wc).hInstance = hInstance;
	(*wc).hCursor = LoadCursor(NULL,IDC_ARROW);
	(*wc).style = CS_HREDRAW | CS_VREDRAW;
	(*wc).cbClsExtra = 0;
	(*wc).cbWndExtra = 0;
	(*wc).hCursor = LoadCursor(NULL, IDC_CROSS);
	(*wc).hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	(*wc).lpszMenuName = NULL;
	RegisterClass(wc);
	hwnds->hwnd = CreateWindow(CLASS_NAME, CLASS_NAME, WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, WindowW, WindowH,  NULL,NULL,hInstance,NULL);
	*dc = GetDC(hwnds->hwnd);
	ShowWindow(hwnds->hwnd, nCmdShow);
	
	AddControls(hwnds);
	UpdateWindow(hwnds->hwnd);
}


void GetUserInput(HWND *hWidth,HWND *hHeight, HWND *hCell_Size, HWND *hPlayers, HWND *hPenguins, Board *board, int *NumPlayers, int *NumPenguins){
	//Getting the input from textboxes
	wchar_t Cell_Sizec[5], Widthc[5], Heighc[5], Num_Players[5],NumPenguinsPerPlayer[5];
	GetWindowTextW(*hWidth,Widthc,5);
	GetWindowTextW(*hHeight,Heighc,5);
	GetWindowTextW(*hCell_Size,Cell_Sizec,5);
	GetWindowTextW(*hPlayers,Num_Players,5);
	GetWindowTextW(*hPenguins,NumPenguinsPerPlayer,5);


	board->size.x = _wtoi(Widthc);
	board->size.y = _wtoi(Heighc);
	board->CellSize = _wtoi(Cell_Sizec);
	*NumPlayers = _wtoi(Num_Players);
	*NumPenguins = _wtoi(NumPenguinsPerPlayer);
}


void ParseInputError(int errCode, HWND *hwnd){	//Error code that will be parsed and
												//HWND to display messagebox
	//Parse Error codes function

	switch (errCode)
	{
		case 0:
							
		break;
	case 1:
		MessageBox(*hwnd,"Minimum heigh is 10!","Error",MB_OK);
		break;
	case 2:
		MessageBox(*hwnd,"Minimum wigth is 10!","Error",MB_OK);
		break;
	case 3:
		MessageBox(*hwnd,"Minimum cell size is 10!","Error",MB_OK);
		break;
	case 4:
		MessageBox(*hwnd,"Maximum heigh is 100!","Error",MB_OK);
		break;
	case 5:
		MessageBox(*hwnd,"Maximum wigth is 100!","Error",MB_OK);
		break;
	case 6:
		MessageBox(*hwnd,"Minimum number penguins per player is 1!","Error",MB_OK);
		break;
	case 7:
		MessageBox(*hwnd,"Minimum number of players is 2!","Error",MB_OK);
		break;
	case 8:	
		MessageBox(*hwnd,"The board is too small!","Error",MB_OK);
		break;
	default:
		break;
	}
}

void AddRow(HWND *ScoreTable, LPSTR Name, LPSTR Score, int i){
	LVITEM lvi;
	lvi.mask = LVIF_TEXT;

	lvi.pszText = Name;
	lvi.iItem = i;
	lvi.iSubItem = 0;
	ListView_InsertItem( *ScoreTable, & lvi );
	ListView_SetItemText( *ScoreTable, i, 1, Score );

}
void INIT_GUI_PLAYING(HWND *hwnd, HWND *ScoreTable, HWND *MainTextBox, HWND *HintTextBox){
	*MainTextBox =  CreateWindowW(L"static",L"Ya pierdolle",WS_VISIBLE | WS_CHILD | SS_CENTER, BoardPosX, 10, 400, 40, *hwnd,NULL,NULL,NULL);
	*ScoreTable = CreateWindow(WC_LISTVIEW, "", 
         WS_VISIBLE|WS_BORDER|WS_CHILD | LVS_REPORT | LVS_EDITLABELS, 
         10, 200, 180, 250, 
         *hwnd, NULL, NULL, NULL);
	LVCOLUMN lvc;
	lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 0;
	lvc.cx = 120;
	lvc.pszText = "Name";
	ListView_InsertColumn( *ScoreTable, 0, & lvc );
	lvc.iSubItem = 1;
	lvc.cx = 60;
	lvc.pszText = "Scores";
	ListView_InsertColumn( *ScoreTable, 1, & lvc );
	
	
	
	//ListView_SetItemText( *ScoreTable, 2, 1, "18" );



	*HintTextBox =  CreateWindowW(L"static",L"Hint:\nВолк не тот кто волк, а тот кто волк!!!",WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 10, 180, 180, *hwnd,NULL,NULL,NULL);
	FILE *ptr;
		
		ptr = fopen("GameHints.txt", "r");
		if (ptr == NULL) {
			SetWindowText(*HintTextBox,"File with hints not found((");
		}else{
			char *line = NULL;
			size_t len = 0;
			ssize_t read;
			char **lines = NULL;
			int line_count = 0;
			while ((read = getline(&line, &len, ptr)) != -1) {
				lines = realloc(lines, sizeof(char *) * (line_count + 1));
				lines[line_count++] = line;
				line = NULL;
				len = 0;
			}
			fclose(ptr);
			
			if(line_count == 0){
				MessageBox(NULL, "no lines","AA", MB_OK);
			
				SetWindowText(*HintTextBox,"File with hints is empty(");
			}else{
				srand(time(0));
				char *result = (char *) malloc(sizeof(char) * 100);
				strcpy(result, "Hint:\n\n");
    			strcat(result, lines[rand()%line_count] );
				SetWindowText(*HintTextBox,result);
				free(result);	
			}
			if (line) {
				free(line);
			}
			
		}
}

void UpdateScoreTable(HWND *ScoreTable, Player *players, int NumPlayers){
	for(int i =0; i<NumPlayers;i++){
		char buf[4];
		snprintf(buf, 4, "%d", (players+i)->Score);
		ListView_SetItemText(*ScoreTable, i, 1,  buf);
	}
}

void InitAskPlayersGUI(AskingPlayers_GUI *AskingHWNDs){
	AskingHWNDs->MainLabel = CreateWindowW(L"static",L"Player 77:",WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 10, 150, 20, AskingHWNDs->hwnd,NULL,NULL,NULL);
	AskingHWNDs->NameLabel = CreateWindowW(L"static",L"Name:",WS_VISIBLE | WS_CHILD | SS_CENTER, 10, 40, 150, 20, AskingHWNDs->hwnd,NULL,NULL,NULL);
	AskingHWNDs->Name = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | ES_CENTER | ES_AUTOHSCROLL | WS_BORDER, 10, 60, 150, 20, AskingHWNDs->hwnd,NULL,NULL,NULL);
	AskingHWNDs->Color = CreateWindowW(L"Button",L"Select color",WS_VISIBLE | WS_CHILD , 10, 80, 150, 20, AskingHWNDs->hwnd, (HMENU)BtnColor_id, (HINSTANCE)GetWindowLongPtr(AskingHWNDs->hwnd, GWLP_HINSTANCE),NULL);

	AskingHWNDs->NextBtn = CreateWindowW(L"Button",L"Next",WS_VISIBLE | WS_CHILD , 10, 285, 150, 20, AskingHWNDs->hwnd, (HMENU)BtnNext_id, (HINSTANCE)GetWindowLongPtr(AskingHWNDs->hwnd, GWLP_HINSTANCE),NULL);
}
void DeleteAskingGUI(AskingPlayers_GUI *AskingHWNDs){
	DestroyWindow(AskingHWNDs->Color);
	DestroyWindow(AskingHWNDs->MainLabel);
    DestroyWindow(AskingHWNDs->NextBtn);
	DestroyWindow(AskingHWNDs->Name);
	DestroyWindow(AskingHWNDs->NameLabel);
} 
