#pragma once
#include "Defines.h"

enum PARTS {
	TRNS = -1,
	NONE, RGRY, DGRY,
	BLAK,

	// Block
	BLCK,

	// Black
	BC_0, BC_1, BC_2, BC_3,
	BC_4, BC_5, BC_6, BC_7,
	BC_8, BC_9, BC_A, BC_B,
	BC_C, BC_D, BC_E, BC_F,
	BC_G, BC_H, BC_I, BC_J,
	BC_K, BC_L, BC_M, BC_N,
	BC_O, BC_P, BC_Q, BC_R,
	BC_S, BC_T, BC_U, BC_V,
	BC_W, BC_X, BC_Y, BC_Z,
	BCPR, BCHY,

	CRSS, HERT,
	DTX4,

	// Gray
	GC_0, GC_1, GC_2, GC_3,
	GC_4, GC_5, GC_6, GC_7,
	GC_8, GC_9, GC_A, GC_B,
	GC_C, GC_D, GC_E, GC_F,
	GC_G, GC_H, GC_I, GC_J,
	GC_K, GC_L, GC_M, GC_N,
	GC_O, GC_P, GC_Q, GC_R,
	GC_S, GC_T, GC_U, GC_V,
	GC_W, GC_X, GC_Y, GC_Z,

	GCHY,

	CRGT, QOTE,
	COMA, DTQT,
	DTLN,

	// Nintendo Logo
	NTD0, NTD1, NTD2, NTD3,
	NTD4, NTD5, NTD6,

	// Game
	BRC0, BRC1, BRC2,

	BD00, BD01, BD02, BD03,
	BD04, BD05, BD06, BD07,
	BD08, BD09, BD10, BD11,
	BD12, BD13, BD14, BD15,
	BD16, BD17, BD18, BD19,
	BD20, BD21, BD22, BD23,
	BD24, BD25, BD26, BD27,
	BD28, BD29, BD30, BD31,
	BD32, BD33, BD34, GVER,
	LN_G,

	// Menu
	MN00, MN01, MN02, MN03,
	MN04, MN05, MN06, MN07,
	MN08, MN09, MN10, MN11,
	MN12, MN13, MN14, MN15,
	MN16, MN17, MN18, MN19,
	MN20, MN21, MN22, MN23,
	MN24, MN25, MN26, MN27,
	MN28, MN29, MN30, MN31,
	MN32, MN33, MN34, MN35,
	MN36, MN37, MN38, MN39,

	// Dance
	DN00, DN01, DN02, DN03,
	DN04, DN05, DN06, DN07,
	DN08, DN09, DN10, DN11,
	DN12, DN13, DN14, DN15,
	DN16, DN17, DN18,

	// Title
	TL00, TL01, TL02, TL03,
	TL04, TL05, TL06, TL07,
	TL08, TL09, TL10, TL11,
	TL12, TL13, TL14, TL15,
	TL16, TL17, TL18, TL19,
	TL20, TL21, TL22, TL23,
	TL24, TL25, TL26, TL27,
	TL28, TL29, TL30, TL31,
	TL32, TL33, TL34, TL35,
	TL36, TL37, TL38, TL39,
	TL40, TL41, TL42, TL43,
	TL44, TL45, TL46, TL47,
	TL48, TL49, TL50, TL51,
	TL52, TL53, TL54, TL55,
	TL56, TL57, TL58, TL59,
	TL60, TL61, TL62, TL63,
	TL64, TL65, TL66, TL67,
	TL68, TL69, TL70, TL71,
	TL72, TL73, TL74, TL75,
	TL76, TL77, TL78, TL79,
	TL80, TL81, TL82, TL83,
	TL84, TL85, TL86, TL87,
	TL88, TL89, TL90, TL91,
	TL92, TL93, TL94, TL95,

	ARRW, UNDR, BCEX, BCSH,
	BCDR, BCAN, BCQE
};
enum SCENES {
	START_UP,
	COPYRIGHT,
	TITLE,
	SETTING,
	MENU_GAME_TYPE,
	MENU_A,
	MENU_B,
	GAME_A,
	GAME_B,
	PAUSE,
	GAMEOVER,
	DANCE,
	DETAIL_SCORE
};

void SetStagePart(int x, int y, int _Part);
int  GetStagePart(int x, int y);
void setStage(const int _stage[STAGE_HEIGHT][STAGE_WIDTH], int Fill);
void drawPart(int _x, int _y, const char _part[PART_SIZE][PART_SIZE], int ZoomRate = ZOOM_RATE);
void drawPart(int _x, int _y, short PartNumber, char PartType, int ZoomRate = ZOOM_RATE);
void drawStage();
void drawNumbers(int x, int y, int number, int length);
void DrawStringB(char x, char y, const char string[]);
void DrawStringG(char x, char y, const char string[]);