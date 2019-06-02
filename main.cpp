#include "DxLib.h"
#include "Keyboard.h"
#include "DrawMgr.h"
#include "Defines.h"
#include "FPS.h"
#include <math.h>
#include <ctype.h>
#include <string.h>
TCHAR WindowTitle[] = "Tetris Typing";

int count, countWait, score, types,
	Sounds[9], Musics[6], MusicPosition;
unsigned int col[] = {
	0xFFFFFF,
	0xAAAAAA,
	0x555555,
	0x000000
};
short field[FIELD_HEIGHT][FIELD_WIDTH];
char nowSelect, _music, level[2];
bool _pause, _gameover;
bool WaitingFlug = true;
bool DebugFlag;
char _topscore, nowEntering;

typedef struct {
	char name[3][MAX_NAME_LENGTH];
	int score[3];
}TopScore_t;

unsigned char Parts[][PART_SIZE][PART_SIZE] = {
	{0,0,0,0}
};
unsigned char WM, wordSelect, _wordsize;
char words[WORDS_MAX][WORD_SIZE], inWords[32], nowIn, wordY, wordin;
TopScore_t TopScores[6];

int  WindowInit()
{
	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(WINDOW_WIDTH * ZOOM_RATE, WINDOW_HEIGHT * ZOOM_RATE, 32);
	SetFullScreenScalingMode(DX_FSSCALINGMODE_NEAREST);
	SetWindowText(WindowTitle), SetBackgroundColor(0, 0, 0);
	SetAlwaysRunFlag(TRUE);
	SetWindowStyleMode(7);
	if (ChangeWindowMode(TRUE) != 0 || SetWindowSizeChangeEnableFlag(TRUE) != 0 || DxLib_Init() != 0) {
		MessageBox(
			NULL,
			TEXT("エラーが発生しました。\nウィンドウの生成に失敗しました。"),
			TEXT("ERROR"),
			MB_OK | MB_ICONERROR
		);
		return 1;
	}
	if (SetDrawScreen(DX_SCREEN_BACK) != 0) {
		MessageBox(
			NULL,
			TEXT("エラーが発生しました。\nウィンドウの設定に失敗しました。"),
			TEXT("ERROR"),
			MB_OK | MB_ICONERROR
		);
		DxLib_End();
		return 1;
	}
	return 0;
}
int  LoadMem()
{
	Sounds[0] = LoadSoundMem("Data/Sounds/startup.ogg");
	Sounds[1] = LoadSoundMem("Data/Sounds/menuChange.ogg");
	Sounds[2] = LoadSoundMem("Data/Sounds/menuConfirm.ogg");
	Sounds[3] = LoadSoundMem("Data/Sounds/pause.ogg");
	Sounds[4] = LoadSoundMem("Data/Sounds/minoMove.ogg");
	Sounds[5] = LoadSoundMem("Data/Sounds/minoDrop.ogg");
	Sounds[6] = LoadSoundMem("Data/Sounds/minoRotate.ogg");
	Sounds[7] = LoadSoundMem("Data/Sounds/levelUp.ogg");
	Sounds[8] = LoadSoundMem("Data/Sounds/gameOver.ogg");

	Musics[0] = LoadSoundMem("Data/Musics/Title.ogg");
	Musics[1] = LoadSoundMem("Data/Musics/AType.ogg");
	Musics[2] = LoadSoundMem("Data/Musics/BType.ogg");
	Musics[3] = LoadSoundMem("Data/Musics/CType.ogg");
	Musics[5] = LoadSoundMem("Data/Musics/TopScore.ogg");
	for (int i = 0; i < 7; i++)
		if (Sounds[i] == -1) {
			MessageBox(
				NULL,
				TEXT("File Open Failed.\nData\\Sounds"),
				TEXT("ERROR"),
				MB_OK | MB_ICONERROR
			);
			return 1;
		}
	for (int i = 0; i < 5; i++)
		if (Musics[i] == -1) {
			MessageBox(
				NULL,
				TEXT("File Open Failed.\nData\\Musics"),
				TEXT("ERROR"),
				MB_OK | MB_ICONERROR
			);
			return 1;
		}

	int FileHandle = FileRead_open("Data/Typings/words.txt");
	if (FileHandle == 0){
		FileRead_close(FileHandle);
		MessageBox(
			NULL,
			TEXT("File Open Failed.\nData\\Typings"),
			TEXT("ERROR"),
			MB_OK | MB_ICONERROR
		);
		return 1;
	}
	for (int i = 0; i < WORDS_MAX; i++) {
		for (int j = 0; j < WORD_SIZE; j++) {
			if (FileRead_eof(FileHandle) != 0) break;
			char nextCh = FileRead_getc(FileHandle);
			if (nextCh == ',' || nextCh == '\n') break;
			FileRead_seek(FileHandle, -1, SEEK_CUR);
			words[i][j] = FileRead_getc(FileHandle);
		}
		if (FileRead_eof(FileHandle) != 0) {
			WM = i;
			break;
		}
	}

	FILE *fp;
	if ((fopen_s(&fp, "Top.dat", "rb")) != 0) {
		MessageBox(
			NULL,
			TEXT("File Open Failed.\nTop.dat"),
			TEXT("ERROR"),
			MB_OK | MB_ICONERROR
		);
		return 1;
	}
	fread(&TopScores, sizeof(TopScores), 1, fp);
	fclose(fp);
	
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			if (TopScores[i].name[j][0] == '\0') strcpyDx(TopScores[i].name[j], "*");

	return 0;
}
void GameInit() {
	types = score = count = _pause = _gameover = 0;
	wordY = 0;
	wordin = '\0';
	level[0] = nowSelect;
	wordSelect = GetRand(WM);
	_wordsize = (unsigned char)strlen(words[wordSelect]);
	for (int i = 0; i < FIELD_HEIGHT; i++)
		for (int j = 0; j < FIELD_WIDTH; j++)
			field[i][j] = NONE;
}
void SoftInit() {
	count = countWait = _music = nowSelect = level[0] = level[1] = 0;
	GameInit();
}
void SetStageScene(char Scene);
void setStage(const int _stage[STAGE_HEIGHT][STAGE_WIDTH], int Fill = -2);
char SceneSwitch(char Scene);
void startup(int x, int counting);
void pause();
void EnterPause() {
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1 && !_gameover) {
		_pause ^= 1;
		if (_pause) {
			MusicPosition = GetCurrentPositionSoundMem(Musics[1 + _music]);
			StopSoundMem(Musics[1 + _music]);
			PlaySoundMem(Sounds[3], DX_PLAYTYPE_BACK);
		}
		else {
			SetCurrentPositionSoundMem(MusicPosition, Musics[1 + _music]);
			PlaySoundMem(Musics[1 + _music], DX_PLAYTYPE_LOOP, FALSE);
		}
	}
}
void EnteredWord() {
	if (nowIn == _wordsize) {
		wordSelect = GetRand(WM);
		_wordsize = (unsigned char)strlen(words[wordSelect]);
		nowIn = 0; types++;
		int adding = 0;
		if (wordY < 19) adding = 40;
		if (wordY < 14) adding = 100;
		if (wordY < 9)  adding = 200;
		if (wordY < 5)  adding = 300;
		score += adding * (level[0] + 1);
		wordY = 0;
		if (types % 20 == 0 && level[0] < 20) level[0]++, PlaySoundMem(Sounds[7], DX_PLAYTYPE_BACK);
		for (int i = 0; i < 11; i++)
			inWords[i] = '\0';
		PlaySoundMem(Sounds[2], DX_PLAYTYPE_BACK);
	}
}
char EnterName() {
	wordin = tolower(GetInputChar(TRUE));
	if (wordin == NULL || wordin < CTRL_CODE_CMP) return NULL;

	return wordin; // It will be changed


}
void gameOver(int _height, int _wait);
void GetMouseStage(int *XBuf, int *YBuf) {
	int Mx, My;
	GetMousePoint(&Mx, &My);
	if (Mx < 0) Mx = 0;
	if (Mx > WINDOW_WIDTH * ZOOM_RATE) Mx = WINDOW_WIDTH * ZOOM_RATE -1;
	if (My < 0) My = 0;
	if (My > WINDOW_HEIGHT * ZOOM_RATE) My = WINDOW_HEIGHT * ZOOM_RATE -1;
	*XBuf = (int)Mx / (8 * ZOOM_RATE);
	*YBuf = (int)My / (8 * ZOOM_RATE);
}
int  DataSave() {
	FILE *fp;
	if ((fopen_s(&fp, "Top.dat", "wb")) != 0) {
		MessageBox(
			NULL,
			TEXT("Data Save Failed.\nTop.dat"),
			TEXT("ERROR"),
			MB_OK | MB_ICONERROR
		);
		return 1;
	}
	fwrite(&TopScores, sizeof(TopScores), 1, fp);
	fclose(fp);
	return 0;
}
void DrawDimsStatus(unsigned int _font_color = 0xffffff) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, WINDOW_HEIGHT * ZOOM_RATE / 2, 226, 0x222222, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawFormatString(0, 0  , _font_color, "count      : %d", count);
	DrawFormatString(0, 16 , _font_color, "countWait  : %d", countWait);
	DrawFormatString(0, 32 , _font_color, "nowSelect  : %d", nowSelect);
	DrawFormatString(0, 48 , _font_color, "_music     : %d", _music);
	DrawFormatString(0, 64 , _font_color, "WordSelect : %d", wordSelect);
	DrawFormatString(0, 80 , _font_color, "_wordsize  : %d", _wordsize);
	DrawFormatString(0, 96 , _font_color, "nowIn      : %d", nowIn);
	DrawFormatString(0, 112, _font_color, "wordY      : %d", wordY);
	DrawFormatString(0, 128, _font_color, "wordin     : %c", wordin);
	DrawFormatString(0, 144, _font_color, "WM         : %d", WM);
	DrawFormatString(0, 160, _font_color, "_pause     : %d", _pause);
	DrawFormatString(0, 176, _font_color, "_gameover  : %d", _gameover);
	DrawFormatString(0, 192, _font_color, "_topscore  : %d", _topscore);
	DrawFormatString(0, 208, _font_color, "nowEntering: %d", nowEntering);

}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (WindowInit() || LoadMem()) return 1;
	char Scene = START_UP; count = countWait = _music = nowSelect = level[0] = level[1] = 0;
	DebugFlag = false;

	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !KeyUpdate() && FPSUpdate()) {
		Scene = SceneSwitch(Scene);
		if (_pause) pause();
		
		if (Scene != START_UP) drawStage();

		if (DebugFlag) {
			DrawDimsStatus();
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			DrawBox(WINDOW_WIDTH * ZOOM_RATE - 45, 0, WINDOW_WIDTH * ZOOM_RATE, 21, 0U, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DrawFPSRate(WINDOW_WIDTH * ZOOM_RATE - 40, 3, 0xffff00);
		}
		
		if (Keyboard_Get(KEY_INPUT_F3) == 1) DebugFlag ^= 1;

	}
	InitSoundMem();
	DxLib_End();

	if (_topscore == 0) {
		if (DataSave()) return 1;
	}
	return 0;
}

void SetStageScene(char Scene)
{
	switch (Scene) {
	case COPYRIGHT: {
		int _stage[STAGE_HEIGHT][STAGE_WIDTH] = {
		{NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
		{QOTE, BC_T, BC_M, NONE, BC_A, BC_N, BC_D, NONE, CRGT, BC_2, BC_0, BC_1, BC_8, NONE, BC_R, BC_Y, BC_S, BC_T, BC_D, COMA},
		{NONE, NONE, NONE, NONE, BC_T, BC_E, BC_T, BC_R, BC_I, BC_S, NONE, BC_T, BC_Y, BC_P, BC_I, BC_N, BC_G, NONE, NONE, NONE},
		{NONE, NONE, NONE, NONE, NONE, BC_L, BC_I, BC_C, BC_E, BC_N, BC_S, BC_E, BC_D, NONE, BC_T, BC_O, NONE, NONE, NONE, NONE},
		{NONE, NONE, NONE, NONE, BC_R, BC_Y, BC_O, BC_S, BC_T, BC_U, BC_D, BC_I, BC_O, NONE, BC_A, BC_N, BC_D, NONE, NONE, NONE},
		{NONE, NONE, NONE, BC_S, BC_U, BC_B, BCHY, BC_L, BC_I, BC_C, BC_E, BC_N, BC_S, BC_E, BC_D, NONE, BC_T, BC_O, NONE, NONE},
		{NONE, NONE, NONE, NONE, NONE, NONE, BC_T, BC_A, BC_I, BC_R, BC_Y, BC_O, BC_S, BC_T, BCPR, NONE, NONE, NONE, NONE, NONE},
		{NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
		{NONE, CRGT, BC_2, BC_0, BC_1, BC_8, NONE, BC_R, BC_Y, BC_O, BC_S, BC_T, BC_U, BC_D, BC_I, BC_O, NONE, BC_D, BC_O, BC_T},
		{NONE, NONE, NONE, NONE, NONE, NONE, NONE, BC_N, BC_E, BC_T, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
		{NONE, NONE, NONE, CRGT, BC_2, BC_0, BC_1, BC_8, NONE, NTD0, NTD1, NTD2, NTD3, NTD4, NTD5, NTD6, NONE, NONE, NONE, NONE},
		{NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
		{BC_A, BC_L, BC_L, NONE, BC_R, BC_I, BC_G, BC_H, BC_T, BC_S, NONE, BC_R, BC_E, BC_S, BC_E, BC_R, BC_V, BC_E, BC_D, BCPR},
		{NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
		{NONE, NONE, BC_O, BC_R, BC_I, BC_G, BC_I, BC_N, BC_A, BC_L, NONE, BC_C, BC_O, BC_N, BC_C, BC_E, BC_P, BC_T, COMA, NONE},
		{NONE, BC_D, BC_E, BC_S, BC_I, BC_G, BC_N, NONE, BC_A, BC_N, BC_D, NONE, BC_P, BC_R, BC_O, BC_G, BC_R, BC_A, BC_M, NONE},
		{BC_B, BC_Y, NONE, BC_A, BC_L, BC_E, BC_X, BC_E, BC_Y, NONE, BC_P, BC_A, BC_Z, BC_H, BC_I, BC_T, BC_N, BC_O, BC_V, DTQT},
		{NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE}
		};
		setStage(_stage);
	}break;
	case TITLE: {
		int _stage[STAGE_HEIGHT][STAGE_WIDTH] = {
		{BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK},
		{TL00, TL01, TL01, TL01, TL01, TL01, TL01, TL01, TL01, TL01, TL01, TL01, TL01, TL01, TL01, TL01, TL01, TL01, TL01, TL02},
		{TL03, TL04, TL05, TL31, TL06, TL07, TL08, TL09, TL38, TL83, TL87, TL90, TL10, TL11, TL12, TL13, TL14, TL15, TL16, TL17},
		{TL03, TL24, TL25, TL26, TL32, TL33, TL36, TL35, TL39, TL84, TL88, TL91, TL49, TL54, TL52, TL41, TL40, TL95, NONE, TL17},
		{TL03, NONE, TL27, TL28, NONE, TL34, TL37, TL48, TL82, TL85, TL89, TL92, TL50, TL55, TL53, TL42, TL43, TL44, NONE, TL17},
		{TL03, NONE, TL29, TL28, NONE, TL29, MN18, BD21, MN18, TL86, TL30, BLAK, TL93, TL51, TL94, TL47, TL46, TL45, NONE, TL17},
		{TL18, TL19, TL19, TL19, TL19, TL19, TL19, TL19, TL19, TL19, TL19, TL19, TL19, TL19, TL19, TL19, TL19, TL19, TL19, TL20},
		{BLAK, TL21, TL21, TL21, TL21, TL21, TL21, TL21, TL21, TL21, TL21, TL21, TL21, TL21, TL22, TL23, TL21, TL21, TL21, BLAK},
		{BLAK, RGRY, RGRY, DN01, DN02, RGRY, RGRY, TL56, RGRY, RGRY, RGRY, RGRY, RGRY, TL56, TL63, TL64, TL57, RGRY, RGRY, BLAK},
		{BLAK, TL56, RGRY, DN03, DN04, RGRY, RGRY, RGRY, RGRY, TL57, RGRY, RGRY, RGRY, RGRY, TL67, TL65, RGRY, RGRY, RGRY, BLAK},
		{BLAK, RGRY, RGRY, RGRY, RGRY, RGRY, RGRY, RGRY, RGRY, RGRY, RGRY, RGRY, RGRY, TL66, TL76, TL73, TL75, TL79, TL80, BLAK},
		{BLAK, RGRY, RGRY, RGRY, RGRY, TL56, RGRY, RGRY, RGRY, RGRY, TL60, TL58, RGRY, TL69, TL68, TL78, TL77, TL63, TL64, BLAK},
		{BLAK, RGRY, RGRY, RGRY, RGRY, RGRY, RGRY, RGRY, RGRY, TL58, TL59, TL61, TL62, TL70, TL71, TL74, TL72, TL81, TL65, BLAK},
		{BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK},
		{NONE, NONE, BC_1, BC_P, BC_L, BC_A, BC_Y, BC_E, BC_R, NONE, NONE, NONE, BC_S, BC_E, BC_T, BC_T, BC_I, BC_N, BC_G, NONE},
		{NONE, NONE, LN_G, LN_G, LN_G, LN_G, LN_G, LN_G, LN_G, NONE, NONE, NONE, LN_G, LN_G, LN_G, LN_G, LN_G, LN_G, LN_G, NONE},
		{NONE, NONE, NONE, NONE, CRGT, BC_2, BC_0, BC_1, BC_8, NONE, NTD0, NTD1, NTD2, NTD3, NTD4, NTD5, NTD6, NONE, NONE, NONE},
		{NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE}
		};
		setStage(_stage);
	}break;
	case SETTING: {
		int _stage[STAGE_HEIGHT][STAGE_WIDTH] = {
		{MN00, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN02},
		{MN03, BC_S, BC_E, BC_T, BC_T, BC_I, BC_N, BC_G, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN06, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN08, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN09, BC_F, BC_U, BC_L, BC_L, NONE, BC_S, BC_C, BC_R, BC_E, BC_E, BC_N, MN10, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN11, MN13, MN37, MN37, MN37, MN37, MN37, MN37, MN14, MN37, MN37, MN37, MN37, MN15, MN12, MN16, MN04, MN05},
		{MN03, MN04, MN17, NONE, NONE, GC_Y, GC_E, GC_S, NONE, NONE, MN18, NONE, NONE, GC_N, GC_O, NONE, NONE, MN19, MN04, MN05},
		{MN03, MN04, MN20, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN36, MN21, MN21, MN21, MN21, MN21, MN21, MN22, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN06, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN08, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN09, BC_M, BC_U, BC_S, BC_I, BC_C, NONE, BC_T, BC_Y, BC_P, BC_E, MN10, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN11, MN12, MN13, MN37, MN37, MN37, MN37, MN37, MN14, MN37, MN37, MN37, MN37, MN15, MN12, MN16, MN04, MN05},
		{MN03, MN04, MN17, GC_A, GCHY, GC_T, GC_Y, GC_P, GC_E, NONE, MN18, GC_B, GCHY, GC_T, GC_Y, GC_P, GC_E, MN19, MN04, MN05},
		{MN03, MN04, MN23, MN24, MN24, MN24, MN24, MN24, MN24, MN24, MN25, MN24, MN24, MN24, MN24, MN24, MN24, MN26, MN04, MN05},
		{MN03, MN04, MN17, GC_C, GCHY, GC_T, GC_Y, GC_P, GC_E, NONE, MN18, NONE, GC_O, GC_F, GC_F, NONE, NONE, MN19, MN04, MN05},
		{MN03, MN04, MN20, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN36, MN21, MN21, MN21, MN21, MN21, MN21, MN22, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN05},
		{MN27, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN29}
		};
		setStage(_stage);
	}break;
	case MENU_GAME_TYPE: {
		int _stage[STAGE_HEIGHT][STAGE_WIDTH] = {
		{MN00, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN02},
		{MN03, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN06, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN08, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN09, BC_G, BC_A, BC_M, BC_E, NONE, BC_T, BC_Y, BC_P, BC_E, MN10, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN11, MN12, MN13, MN37, MN37, MN37, MN37, MN37, MN14, MN37, MN37, MN37, MN15, MN12, MN12, MN16, MN04, MN05},
		{MN03, MN04, MN17, GC_A, GCHY, GC_T, GC_Y, GC_P, GC_E, NONE, MN18, GC_B, GCHY, GC_T, GC_Y, GC_P, GC_E, MN19, MN04, MN05},
		{MN03, MN04, MN20, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN36, MN21, MN21, MN21, MN21, MN21, MN21, MN22, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN06, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN08, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN09, BC_M, BC_U, BC_S, BC_I, BC_C, NONE, BC_T, BC_Y, BC_P, BC_E, MN10, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN11, MN12, MN13, MN37, MN37, MN37, MN37, MN37, MN14, MN37, MN37, MN37, MN37, MN15, MN12, MN16, MN04, MN05},
		{MN03, MN04, MN17, GC_A, GCHY, GC_T, GC_Y, GC_P, GC_E, NONE, MN18, GC_B, GCHY, GC_T, GC_Y, GC_P, GC_E, MN19, MN04, MN05},
		{MN03, MN04, MN23, MN24, MN24, MN24, MN24, MN24, MN24, MN24, MN25, MN24, MN24, MN24, MN24, MN24, MN24, MN26, MN04, MN05},
		{MN03, MN04, MN17, GC_C, GCHY, GC_T, GC_Y, GC_P, GC_E, NONE, MN18, NONE, GC_O, GC_F, GC_F, NONE, NONE, MN19, MN04, MN05},
		{MN03, MN04, MN20, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN36, MN21, MN21, MN21, MN21, MN21, MN21, MN22, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN05},
		{MN27, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN29}
		};
		setStage(_stage);
	}break;
	case MENU_A: {
		int _stage[STAGE_HEIGHT][STAGE_WIDTH] = {
		{MN00, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN02},
		{MN03, NONE, BC_A, BCHY, BC_T, BC_Y, BC_P, BC_E, NONE, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN04, MN04, MN06, MN07, MN07, MN07, MN07, MN07, MN08, MN04, MN04, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN04, MN04, MN09, BC_L, BC_E, BC_V, BC_E, BC_L, MN10, MN04, MN04, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN11, MN12, MN13, MN37, MN37, MN33, MN37, MN37, MN15, MN12, MN16, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN17, GC_E, GC_A, GC_S, GC_Y, MN30, GC_H, GC_A, GC_R, GC_D, MN19, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN23, MN24, MN24, MN24, MN24, MN31, MN24, MN24, MN24, MN24, MN26, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN17, NONE, GC_E, GC_X, GC_P, GC_E, GC_R, GC_T, NONE, NONE, MN19, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN20, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN22, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN06, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN08, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN09, BC_T, BC_O, BC_P, BCHY, BC_S, BC_C, BC_O, BC_R, BC_E, MN10, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN11, MN12, MN38, MN13, MN37, MN37, MN37, MN37, MN37, MN37, MN37, MN37, MN37, MN15, MN12, MN12, MN12, MN16, MN05},
		{MN03, MN17, BC_1, MN30, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, NONE, NONE, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, MN19, MN05},
		{MN03, MN17, BC_2, MN30, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, NONE, NONE, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, MN19, MN05},
		{MN03, MN17, BC_3, MN30, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, NONE, NONE, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, MN19, MN05},
		{MN03, MN20, MN21, MN35, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN22, MN05},
		{MN27, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN29}
		};
		setStage(_stage);
	}break;
	case MENU_B: {
		int _stage[STAGE_HEIGHT][STAGE_WIDTH] = {
		{MN00, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN01, MN02},
		{MN03, NONE, BC_B, BCHY, BC_T, BC_Y, BC_P, BC_E, NONE, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN06, MN07, MN07, MN07, MN07, MN07, MN08, MN04, MN04, MN06, MN07, MN07, MN07, MN07, MN08, MN04, MN05},
		{MN03, MN04, MN04, MN09, BC_L, BC_E, BC_V, BC_E, BC_L, MN10, MN04, MN04, MN09, BC_H, BC_I, BC_G, BC_H, MN10, MN04, MN05},
		{MN03, MN11, MN12, MN32, MN37, MN33, MN37, MN33, MN37, MN34, MN12, MN16, MN39, MN37, MN33, MN37, MN33, MN15, MN16, MN05},
		{MN03, MN17, GC_0, MN30, GC_1, MN30, GC_2, MN30, GC_3, MN30, GC_4, MN19, MN17, GC_0, MN30, GC_1, MN30, GC_2, MN19, MN05},
		{MN03, MN23, MN24, MN31, MN24, MN31, MN24, MN31, MN24, MN31, MN24, MN26, MN23, MN24, MN31, MN24, MN31, MN24, MN26, MN05},
		{MN03, MN17, GC_5, MN30, GC_6, MN30, GC_7, MN30, GC_8, MN30, GC_9, MN19, MN17, GC_3, MN30, GC_4, MN30, GC_5, MN19, MN05},
		{MN03, MN20, MN21, MN35, MN21, MN35, MN21, MN35, MN21, MN35, MN21, MN22, MN20, MN21, MN35, MN21, MN35, MN21, MN22, MN05},
		{MN03, MN04, MN04, MN04, MN06, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN07, MN08, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN09, BC_T, BC_O, BC_P, BCHY, BC_S, BC_C, BC_O, BC_R, BC_E, MN10, MN04, MN04, MN04, MN04, MN05},
		{MN03, MN11, MN12, MN38, MN13, MN37, MN37, MN37, MN37, MN37, MN37, MN37, MN37, MN37, MN15, MN12, MN12, MN12, MN16, MN05},
		{MN03, MN17, BC_1, MN30, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, NONE, NONE, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, MN19, MN05},
		{MN03, MN17, BC_2, MN30, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, NONE, NONE, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, MN19, MN05},
		{MN03, MN17, BC_3, MN30, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, NONE, NONE, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, MN19, MN05},
		{MN03, MN20, MN21, MN35, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN21, MN22, MN05},
		{MN27, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN28, MN29}
		};
		setStage(_stage);
	}break;
	case GAME_A: {
		int _stage[STAGE_HEIGHT][STAGE_WIDTH] = {
		{BD00, BRC2, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC2, BD01, BD02, BD02, BD02, BD02, BD02, BD03},
		{BD00, BRC1, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC1, BD04, BC_S, BC_C, BC_O, BC_R, BC_E, BD05},
		{BD00, BRC0, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC0, BD06, BD07, BD07, BD07, BD07, BD07, BD08},
		{BD00, BRC2, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC2, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
		{BD00, BRC1, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC1, BD09, BD10, BD10, BD10, BD10, BD10, BD10},
		{BD00, BRC0, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC0, BD01, BD02, BD02, BD02, BD02, BD02, BD03},
		{BD00, BRC2, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC2, BD11, BC_L, BC_E, BC_V, BC_E, BC_L, BD12},
		{BD00, BRC1, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC1, BD11, NONE, NONE, NONE, NONE, NONE, BD12},
		{BD00, BRC0, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC0, BD13, BD14, BD14, BD14, BD14, BD14, BD15},
		{BD00, BRC2, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC2, BD11, BC_W, BC_O, BC_R, BC_D, BC_S, BD12},
		{BD00, BRC1, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC1, BD11, NONE, NONE, NONE, NONE, NONE, BD12},
		{BD00, BRC0, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC0, BD16, BD10, BD10, BD10, BD10, BD10, BD17},
		{BD00, BRC2, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC2, BD21, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK},
		{BD00, BRC1, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC1, BD21, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK},
		{BD00, BRC0, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC0, BD21, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK},
		{BD00, BRC2, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC2, BD21, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK},
		{BD00, BRC1, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC1, BD21, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK},
		{BD00, BRC0, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC0, BD21, BLAK, BLAK, BLAK, BLAK, BLAK, BLAK}
		};
		setStage(_stage);
	}break;

	default:
		break;
	}
}

char SceneSwitch(char Scene)
{
	int MouseX, MouseY;
	SetStageScene(Scene);
	switch (Scene){
	case START_UP:
		startup(21 * ZOOM_RATE, count);
		if (count > ZOOM_RATE * 100) {
			count = 0;
			return COPYRIGHT;
		}
		count+=ZOOM_RATE;
		break;
	case COPYRIGHT:
		if (count > 150) {
			count = 0;
			PlaySoundMem(Musics[0], DX_PLAYTYPE_LOOP);
			return TITLE;
		}
		count++;
		break;
	case TITLE:
		GetMouseStage(&MouseX, &MouseY);
		if (!count) SetStagePart(1, 14, ARRW);
		else SetStagePart(11, 14, ARRW);
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1) count = 0;
		if (Keyboard_Get(KEY_INPUT_RIGHT) == 1) count = 1;
		if (MouseX > 1 && MouseX < 9 && MouseY == 14 && Mouse_Get(M_LEFT) == 1)
			if (count) count = 0;
			else Keyboard_Set(KEY_INPUT_RETURN, 1);
		if (MouseX > 11 && MouseX < 19 && MouseY == 14 && Mouse_Get(M_LEFT) == 1)
			if (!count) count = 1;
			else Keyboard_Set(KEY_INPUT_RETURN, 1);
		if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {
			nowSelect = 0;
			StopSoundMem(Musics[0]);
			if (!count) return MENU_GAME_TYPE;
			else return SETTING;
		}
		break;
	case SETTING:

		break;
	case MENU_GAME_TYPE:
		GetMouseStage(&MouseX, &MouseY);
		if (!CheckSoundMem(Musics[1 + _music]) && _music != 3) PlaySoundMem(Musics[1 + _music], DX_PLAYTYPE_BACK);
		if (count <= 18 || nowSelect > 1)
			if (nowSelect % 2) DrawStringB(11, 5, "B-TYPE");
			else DrawStringB(3, 5, "A-TYPE");
		if (count <= 18 || nowSelect < 2) {
			if (_music == 0) DrawStringB(3, 12, "A-TYPE");
			if (_music == 1) DrawStringB(11, 12, "B-TYPE");
			if (_music == 2) DrawStringB(3, 14, "C-TYPE");
			if (_music == 3) DrawStringB(12, 14, "OFF");
		}
		if (nowSelect < 2) {
			if (Keyboard_Get(KEY_INPUT_RIGHT) == 1 || Keyboard_Get(KEY_INPUT_LEFT) == 1) nowSelect ^= 1, PlaySoundMem(Sounds[1], DX_PLAYTYPE_BACK);
			if (Keyboard_Get(KEY_INPUT_X) == 1 || Keyboard_Get(KEY_INPUT_DOWN) == 1) {
				nowSelect += 2, PlaySoundMem(Sounds[1], DX_PLAYTYPE_BACK);
				Keyboard_Set(KEY_INPUT_DOWN, 2);
				Keyboard_Set(KEY_INPUT_X, 2);
			}
		}
		if (nowSelect > 1) {
			if (Keyboard_Get(KEY_INPUT_RIGHT) == 1 && _music+1 < 4) {
				StopSoundMem(Musics[1 + _music]);
				_music++, PlaySoundMem(Sounds[1], DX_PLAYTYPE_BACK);
			}
			if (Keyboard_Get(KEY_INPUT_LEFT) == 1 && _music-1 >= 0) {
				StopSoundMem(Musics[1 + _music]);
				_music--, PlaySoundMem(Sounds[1], DX_PLAYTYPE_BACK);
			}
			if (Keyboard_Get(KEY_INPUT_DOWN) == 1 && _music+2 < 4) {
				StopSoundMem(Musics[1 + _music]);
				_music += 2, PlaySoundMem(Sounds[1], DX_PLAYTYPE_BACK);
			}
			if (Keyboard_Get(KEY_INPUT_UP) == 1) {
				if (_music - 2 >= 0) {
					StopSoundMem(Musics[1 + _music]);
					_music -= 2, PlaySoundMem(Sounds[1], DX_PLAYTYPE_BACK);
				}
				else nowSelect -= 2;
			}
			if (Keyboard_Get(KEY_INPUT_Z) == 1) nowSelect -= 2;
		}
		if (MouseX > 2 && MouseX < 10 && MouseY == 5 && Mouse_Get(M_LEFT) == 1 && nowSelect != 0) nowSelect = 0, PlaySoundMem(Sounds[1], DX_PLAYTYPE_BACK);
		if (MouseX > 10 && MouseX < 17 && MouseY == 5 && Mouse_Get(M_LEFT) == 1 && nowSelect != 1) nowSelect = 1, PlaySoundMem(Sounds[1], DX_PLAYTYPE_BACK);
		if (Keyboard_Get(KEY_INPUT_RETURN) == 1 || (nowSelect > 1 && Keyboard_Get(KEY_INPUT_X) == 1)) {
			StopSoundMem(Musics[1 + _music]);
			PlaySoundMem(Sounds[2], DX_PLAYTYPE_BACK);
			PlaySoundMem(Musics[1 + _music], DX_PLAYTYPE_LOOP);
			Keyboard_Set(KEY_INPUT_RETURN, 2);
			Keyboard_Set(KEY_INPUT_X, 2);
			if (nowSelect % 2) {
				nowSelect = level[1]; return MENU_B;
			}
			else {
				nowSelect = level[0]; return MENU_A;
			}
		}
		count >= 36 ? count = 0 : count++;

		if (WaitingFlug) {
			countWait++;
			if (CheckHitKeyAll() || Mouse_Get(M_LEFT) > 0) countWait = 0;
			if (countWait > 9000) count = 0;
			if (countWait > MAX_WAIT) {
				StopSoundMem(Musics[1 + _music]);
				SoftInit();
				return START_UP;
			}
		}

		break;
	case MENU_A:
		if (_topscore > 0) {
			if (count <= 18) SetStagePart(4 + nowEntering, 12 + _topscore, UNDR);



			// EnterName();




			if (Keyboard_Get(KEY_INPUT_0) == 1) TopScores[nowSelect].name[_topscore - 1][nowEntering] = 'A';
			if (Keyboard_Get(KEY_INPUT_RETURN) == 1 && nowEntering > 0) {
				_topscore = 0;
			}
		}
		else {
			if (count <= 18) {
				if (nowSelect == 0) DrawStringB(5, 6, "EASY");
				if (nowSelect == 1) DrawStringB(10, 6, "HARD");
				if (nowSelect == 2) DrawStringB(6, 8, "EXPERT");
			}
			if (Keyboard_Get(KEY_INPUT_RIGHT) == 1 && nowSelect + 1 < 3) PlaySoundMem(Sounds[1], DX_PLAYTYPE_BACK), nowSelect++;
			if (Keyboard_Get(KEY_INPUT_LEFT) == 1 && nowSelect - 1 >= 0) PlaySoundMem(Sounds[1], DX_PLAYTYPE_BACK), nowSelect--;
			if (Keyboard_Get(KEY_INPUT_DOWN) == 1 && nowSelect != 2) PlaySoundMem(Sounds[1], DX_PLAYTYPE_BACK), nowSelect = 2;
			if (Keyboard_Get(KEY_INPUT_UP) == 1 && nowSelect != 0) PlaySoundMem(Sounds[1], DX_PLAYTYPE_BACK), nowSelect = 0;
			if (Keyboard_Get(KEY_INPUT_Z) == 1) {
				level[0] = nowSelect;
				nowSelect = 0;
				return MENU_GAME_TYPE;
			}
			if (Keyboard_Get(KEY_INPUT_X) == 1 || Keyboard_Get(KEY_INPUT_RETURN) == 1) {
				GameInit();
				return GAME_A;
			}
		}
		
		for (int i = 0; i < 3; i++) {
			if (TopScores[nowSelect].name[i][0] != '*') DrawStringB(4, 13 + i, TopScores[nowSelect].name[i]);
			if (TopScores[nowSelect].score[i] != 0) drawNumbers(12, 13 + i, TopScores[nowSelect].score[i], 6);
		}

		count >= 36 ? count = 0 : count++;
		break;
	case MENU_B:

		break;
	case GAME_A:
		EnterPause();
		drawNumbers(13, 3, score, 6);
		drawNumbers(16, 7, level[0], 2);
		drawNumbers(15, 10, types, 3);
		for (int i = 0; i < FIELD_HEIGHT; i++)
			for (int j = 2; j < FIELD_WIDTH + 2; j++)
				if (field[i][j - 2] != TRNS) SetStagePart(j, i, field[i][j - 2]);
		if (!_pause && !_gameover) {
			wordin = tolower(GetInputChar(TRUE));
			if (words[wordSelect][nowIn] == wordin && nowIn < 10) {
				inWords[nowIn++] = words[wordSelect][nowIn];
				score++;
				PlaySoundMem(Sounds[4], DX_PLAYTYPE_BACK);
			}
			else if (wordin != NULL && wordin >= CTRL_CODE_CMP) {
				PlaySoundMem(Sounds[6], DX_PLAYTYPE_BACK);
				for (int i = 0; i < 1; i++)
					if (wordY + 1 < 18 && field[wordY + 1][0] == NONE) wordY++;
			}

			EnteredWord();

			DrawStringB(2, wordY, words[wordSelect]);
			DrawStringG(2, wordY, inWords);
			
			if (count % 25 == 0) {
				if (wordY + 1 < 18 && field[wordY + 1][0] == NONE) wordY++, count = 1;
				else {
					for (int i = 0; i < FIELD_HEIGHT; i++)
						for (int j = 0; j < FIELD_WIDTH; j++)
							field[i][j] = GetStagePart(j + 2, i);
					wordSelect = GetRand(WM);
					_wordsize = (unsigned char)strlen(words[wordSelect]);
					wordY = 0; nowIn = 0;
					for (int i = 0; i < 11; i++)
						inWords[i] = '\0';
					PlaySoundMem(Sounds[5], DX_PLAYTYPE_BACK);
				}
				if (field[0][0] != NONE) {
					StopSoundMem(Musics[1 + _music]);
					PlaySoundMem(Sounds[8], DX_PLAYTYPE_BACK);
					_gameover = 1;
					count = 0;
				}
			}
			count++;
		}
		if (_gameover) {
			gameOver(count, 25);
			if (count < 150) count++;
			else if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {
				for (int i = 0; i < 3; i++)
					if (TopScores[nowSelect].score[i] < score) {
						_topscore = i + 1;
						i = 3;
					}
				if (_topscore > 0) {
					if (_topscore < 3){
					TopScores[nowSelect].score[_topscore] = TopScores[nowSelect].score[_topscore - 1];
					strcpyDx(TopScores[nowSelect].name[_topscore], TopScores[nowSelect].name[_topscore - 1]);
					}
					TopScores[nowSelect].score[_topscore - 1] = score;
					strcpyDx(TopScores[nowSelect].name[_topscore - 1], "");
					PlaySoundMem(Musics[5], DX_PLAYTYPE_LOOP);
				}
				else PlaySoundMem(Musics[1 + _music], DX_PLAYTYPE_LOOP);
				nowEntering = 0;
				wordin = '\0';
				return MENU_A;
			}
		}

		break;
	default:
		break;
	}
	/// count++;
	
	return Scene;
}
void startup(int x, int counting)
{
	setStage(nullptr, NONE);
	DrawBox(0, 0, WINDOW_WIDTH * ZOOM_RATE, WINDOW_HEIGHT * ZOOM_RATE, col[0], TRUE);
	char part[][PART_SIZE][PART_SIZE] = {
		{
					{3,3,3,3,3,0,0,0},
					{3,3,0,0,3,3,0,0},
					{3,3,0,0,3,3,0,0},
					{3,3,0,0,3,3,0,3},
					{3,3,3,3,3,0,0,3},
					{3,3,0,0,3,3,0,0},
					{3,3,0,0,3,3,0,0},
					{3,3,0,0,3,3,0,3},
					},{
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{3,0,3,3,0,0,3,3},
					{3,0,3,3,0,3,3,0},
					{3,3,3,3,0,3,3,0},
					{0,0,3,3,0,3,3,0},
					{3,3,3,3,0,0,3,3},
					},{
					{0,0,0,0,0,3,3,3},
					{0,0,0,0,3,3,0,0},
					{0,0,0,0,3,3,0,0},
					{3,3,0,0,0,3,3,0},
					{0,3,3,0,0,0,0,3},
					{0,3,3,0,3,3,0,0},
					{0,3,3,0,3,3,0,0},
					{3,3,0,0,0,3,3,3},
					},{
					{3,0,0,0,0,0,0,0},
					{3,3,0,0,3,3,0,0},
					{3,3,0,3,3,3,3,0},
					{0,0,0,0,3,3,0,0},
					{3,0,0,0,3,3,0,0},
					{3,3,0,0,3,3,0,0},
					{3,3,0,0,3,3,0,0},
					{3,0,0,0,3,3,0,0},
					},{
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{3,3,0,0,3,3,0,0},
					{3,3,0,0,3,3,0,3},
					{3,3,0,0,3,3,0,3},
					{3,3,0,3,3,3,0,3},
					{0,3,3,0,3,3,0,0},
					},{
					{0,0,0,3,3,0,3,3},
					{0,0,0,3,3,0,3,3},
					{0,0,0,3,3,0,0,0},
					{3,3,3,3,3,0,3,3},
					{3,0,0,3,3,0,3,3},
					{3,0,0,3,3,0,3,3},
					{3,0,0,3,3,0,3,3},
					{3,3,3,3,3,0,3,3},
					},{
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,3,3,3,3,0,0},
					{0,3,3,0,0,3,3,0},
					{0,3,3,0,0,3,3,0},
					{0,3,3,0,0,3,3,0},
					{0,0,3,3,3,3,0,0},
					},{
					{0,0,3,3,3,3,0,0},
					{0,3,0,0,0,0,3,0},
					{3,0,3,3,0,0,0,3},
					{3,0,3,0,3,3,0,3},
					{3,0,3,3,0,3,0,3},
					{3,0,0,0,3,3,0,3},
					{0,3,0,0,0,0,3,0},
					{0,0,3,3,3,3,0,0},
					}
	};
	int zoom = ZOOM_RATE * 2;
	if (counting > ZOOM_RATE * 55) counting = ZOOM_RATE * 55;
	if (count == ZOOM_RATE * 55) PlaySoundMem(Sounds[0], DX_PLAYTYPE_BACK);
	for (int i = 0; i < 8; i++) {
		drawPart(x + 16 * ZOOM_RATE * i, counting, part[i], zoom);
		if (i == 6) zoom = ZOOM_RATE;
	}
}
void pause()
{
	int _stage[STAGE_HEIGHT][STAGE_WIDTH] = {
	{TRNS, TRNS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, NONE, NONE, BC_H, BC_I, BC_T, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, NONE, NONE, DTX4, DTX4, DTX4, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, NONE, BC_S, BC_T, BC_A, BC_R, BC_T, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, NONE, DTX4, DTX4, DTX4, DTX4, DTX4, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, NONE, NONE, NONE, BC_T, BC_O, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, NONE, NONE, NONE, DTX4, DTX4, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, BC_C, BC_O, BC_N, BC_T, BC_I, BC_N, BC_U, BC_E, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, DTX4, DTX4, DTX4, DTX4, DTX4, DTX4, DTX4, DTX4, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, NONE, NONE, BC_G, BC_A, BC_M, BC_E, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, NONE, NONE, DTX4, DTX4, DTX4, DTX4, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
	{TRNS, TRNS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS}
	};
	setStage(_stage);
}
void gameOver(int _height, int _wait)
{
	int _stage[STAGE_HEIGHT][STAGE_WIDTH] = {
		{TRNS, TRNS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, BD27, BD28, BD28, BD28, BD28, BD28, BD28, BD29, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, BD30, NONE, NONE, NONE, NONE, NONE, NONE, BD31, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, BD30, NONE, BC_G, BC_A, BC_M, BC_E, NONE, BD31, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, BD30, NONE, LN_G, LN_G, LN_G, LN_G, NONE, BD31, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, BD30, NONE, BC_O, BC_V, BC_E, BC_R, NONE, BD31, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, BD30, NONE, LN_G, LN_G, LN_G, LN_G, NONE, BD31, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, BD32, BD33, BD33, BD33, BD33, BD33, BD33, BD34, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, BC_P, BC_L, BC_E, BC_A, BC_S, BC_E, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, DTX4, DTX4, DTX4, DTX4, DTX4, DTX4, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, NONE, BC_T, BC_R, BC_Y, NONE, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, NONE, DTX4, DTX4, DTX4, NONE, NONE, NONE, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, NONE, NONE, BC_A, BC_G, BC_A, BC_I, BC_N, HERT, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS},
		{TRNS, TRNS, NONE, NONE, NONE, DTX4, DTX4, DTX4, DTX4, DTX4, NONE, NONE, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS}
	};
	if (_height <= FIELD_HEIGHT + _wait) {
		for (int x = 0; x < STAGE_WIDTH; x++)
			for (int y = 0; y < STAGE_HEIGHT; y++)
				_stage[y][x] = TRNS;
		for (int i = FIELD_HEIGHT; i > FIELD_HEIGHT - _height; i--)
			for (int j = 2; j < FIELD_WIDTH + 2; j++)
				_stage[i - 1][j] = GVER;
		setStage(_stage);
	}
	else {
		for (int i = 0; i < FIELD_HEIGHT - (_height - FIELD_HEIGHT - _wait); i++)
			for (int j = 2; j < FIELD_WIDTH + 2; j++)
				_stage[i][j] = GVER;
		setStage(_stage);
	}
}