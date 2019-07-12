#include "DxLib.h"
#include "DrawMgr.h"
#include "Defines.h"
#include <math.h>

static unsigned int col[] = {
	0xFFFFFF,
	0xAAAAAA,
	0x555555,
	0x000000
};
static short stage[STAGE_HEIGHT][STAGE_WIDTH];
static unsigned char Parts[][PART_SIZE][PART_SIZE] = {
	{0,0,0,0}
};

void SetColor(unsigned int _Colors[]) {
	for (int i = 0; i < MAX_COLOR; i++)
		col[i] = _Colors[i];
}
void SetStagePart(int x, int y, int _Part, bool setFlag) {
	if (setFlag) stage[y][x] = _Part;
}
int  GetStagePart(int x, int y) {
	return stage[y][x];
}
void setStage(const int _stage[STAGE_HEIGHT][STAGE_WIDTH], int Fill)
{
	for (int x = 0; x < STAGE_WIDTH; x++)
		for (int y = 0; y < STAGE_HEIGHT; y++)
			if (Fill != -2) stage[y][x] = Fill;
			else if (_stage[y][x] != TRNS) stage[y][x] = _stage[y][x];
}
void SetStageScene(char Scene)
{
	switch (Scene) {
	case COPYRIGHT: {
		int _stage[STAGE_HEIGHT][STAGE_WIDTH] = {
		{NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
		{QOTE, BC_T, BC_M, NONE, BC_A, BC_N, BC_D, NONE, CRGT, BC_2, BC_0, BC_1, BC_9, NONE, BC_R, BC_Y, BC_O, BC_G, BC_A, COMA},
		{NONE, NONE, NONE, NONE, BC_T, BC_E, BC_T, BC_R, BC_I, BC_S, NONE, BC_T, BC_Y, BC_P, BC_I, BC_N, BC_G, NONE, NONE, NONE},
		{NONE, NONE, NONE, NONE, NONE, BC_L, BC_I, BC_C, BC_E, BC_N, BC_S, BC_E, BC_D, NONE, BC_T, BC_O, NONE, NONE, NONE, NONE},
		{NONE, NONE, NONE, NONE, BC_R, BC_Y, BC_O, BC_G, BC_A, BCPR, BC_E, BC_X, BC_E, NONE, BC_A, BC_N, BC_D, NONE, NONE, NONE},
		{NONE, NONE, NONE, BC_S, BC_U, BC_B, BCHY, BC_L, BC_I, BC_C, BC_E, BC_N, BC_S, BC_E, BC_D, NONE, BC_T, BC_O, NONE, NONE},
		{NONE, NONE, NONE, NONE, NONE, NONE, BC_T, BC_A, BC_I, BC_R, BC_Y, BC_S, BC_T, BC_D, BCPR, NONE, NONE, NONE, NONE, NONE},
		{NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
		{NONE, CRGT, BC_2, BC_0, BC_1, BC_9, NONE, BC_R, BC_Y, BC_O, BC_G, BC_A, BCPR, BC_E, BC_X, BC_E, NONE, BC_D, BC_O, BC_T},
		{NONE, NONE, NONE, NONE, NONE, NONE, NONE, BC_N, BC_E, BC_T, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
		{NONE, NONE, NONE, CRGT, BC_2, BC_0, BC_1, BC_9, NONE, NTD0, NTD1, NTD2, NTD3, NTD4, NTD5, NTD6, NONE, NONE, NONE, NONE},
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
		{NONE, NONE, NONE, NONE, CRGT, BC_2, BC_0, BC_1, BC_9, NONE, NTD0, NTD1, NTD2, NTD3, NTD4, NTD5, NTD6, NONE, NONE, NONE},
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
		{MN03, MN04, MN04, MN04, MN09, BC_C, BC_O, BC_L, BC_O, BC_R, NONE, BC_T, BC_Y, BC_P, BC_E, MN10, MN04, MN04, MN04, MN05},
		{MN03, MN04, MN11, MN12, MN13, MN33, MN37, MN33, MN37, MN33, MN37, MN33, MN37, MN33, MN37, MN34, MN12, MN16, MN04, MN05},
		{MN03, MN04, MN17, GC_D, GC_E, MN30, GC_1, MN30, GC_2, MN30, GC_3, MN30, GC_4, MN30, GC_5, MN30, GC_6, MN19, MN04, MN05},
		{MN03, MN04, MN20, MN21, MN21, MN35, MN21, MN35, MN21, MN35, MN21, MN35, MN21, MN35, MN21, MN35, MN21, MN22, MN04, MN05},
		{MN03, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN04, MN05},
		{MN03, BC_E, BC_N, BC_T, BC_E, BC_R, NONE, BC_F, BC_O, BC_R, NONE, BC_D, BC_E, BC_F, BC_A, BC_U, BC_L, BC_T, BCPR, MN05},
		{MN03, NONE, NONE, NONE, BC_E, BC_S, BC_C, NONE, BC_T, BC_O, NONE, BC_Q, BC_U, BC_I, BC_T, BCPR, NONE, NONE, NONE, MN05},
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
		{MN03, MN17, BC_1, MN30, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, NONE, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, MN19, MN05},
		{MN03, MN17, BC_2, MN30, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, NONE, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, MN19, MN05},
		{MN03, MN17, BC_3, MN30, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, NONE, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, MN19, MN05},
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
		{MN03, MN17, BC_1, MN30, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, NONE, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, MN19, MN05},
		{MN03, MN17, BC_2, MN30, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, NONE, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, MN19, MN05},
		{MN03, MN17, BC_3, MN30, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, NONE, DTLN, DTLN, DTLN, DTLN, DTLN, DTLN, MN19, MN05},
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
	case GAME_B: {
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
		{BD00, BRC0, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC0, BD13, BD14, BD14, BD14, BD14, BD14, BD15},
		{BD00, BRC2, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC2, BD11, BC_T, BC_I, BC_M, BC_E, NONE, BD12},
		{BD00, BRC1, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC1, BD11, NONE, NONE, BCCO, NONE, NONE, BD12},
		{BD00, BRC0, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRC0, BD16, BD10, BD10, BD10, BD10, BD10, BD17},
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
void drawPart(int _x, int _y, const char _part[PART_SIZE][PART_SIZE], int ZoomRate)
{
	for (int i = 0; i < PART_SIZE; i++)
		for (int j = 0; j < PART_SIZE; j++)
			if (!(_part[j][i] < 0 && _part[j][i] > 3))
				DrawBox(_x + i * ZoomRate, _y + j * ZoomRate, _x + i * ZoomRate + ZoomRate, _y + j * ZoomRate + ZoomRate, col[_part[j][i]], TRUE);
}
void drawPart(int _x, int _y, short PartNumber, char PartType, int ZoomRate)
{
	for (int i = 0; i < PART_SIZE; i++)
		for (int j = 0; j < PART_SIZE; j++)
			DrawBox(_x + i * ZoomRate, _y + j * ZoomRate, _x + i * ZoomRate + ZoomRate, _y + j * ZoomRate + ZoomRate,
				col[PartType == 0 ? (int)(Parts[PartNumber][j][i] / 64) : PartType == 1 ? ((int)(Parts[PartNumber][j][i] / 16)) % 4 :
				PartType == 2 ? ((int)(Parts[PartNumber][j][i] / 4)) % 4 : Parts[PartNumber][j][i] % 4], TRUE);
}
void drawStage()
{
	for (int x = 0; x < STAGE_WIDTH; x++)
		for (int y = 0; y < STAGE_HEIGHT; y++) {
			int X = x * PART_SIZE * ZOOM_RATE, Y = y * PART_SIZE * ZOOM_RATE;
			switch (stage[y][x]) {
			case NONE: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case RGRY: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case DGRY: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case BLAK: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BLCK: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,3,3,3,3,3},
				{3,0,0,0,0,0,0,3},
				{3,0,1,1,1,1,2,3},
				{3,0,1,1,1,1,2,3},
				{3,0,1,1,1,1,2,3},
				{3,0,1,1,1,1,2,3},
				{3,2,2,2,2,2,2,3},
				{3,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BC_0: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,0,0,3,3,0},
				{0,0,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_1: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,3,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_2: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,3,0,0,3,3,3,0},
				{0,0,0,0,3,3,3,0},
				{0,0,3,3,3,3,0,0},
				{0,3,3,3,0,0,0,0},
				{0,3,3,3,3,3,3,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_3: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,3,3,3,3,0,0},
				{0,0,0,0,3,3,3,0},
				{0,0,3,3,3,3,0,0},
				{0,0,0,0,3,3,3,0},
				{0,0,0,0,3,3,3,0},
				{0,3,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_4: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,3,3,0,3,3,0,0},
				{0,3,0,0,3,3,0,0},
				{0,3,0,0,3,3,3,0},
				{0,3,3,3,3,3,3,0},
				{0,0,0,0,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);

			} break;
			case BC_5: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,3,3,3,3,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,3,3,3,0,0},
				{0,0,0,0,3,3,3,0},
				{0,3,0,0,3,3,3,0},
				{0,0,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_6: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,3,3,3,0,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,0,0,3,3,0},
				{0,0,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_7: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,3,3,3,3,3,0},
				{0,0,0,0,0,3,3,0},
				{0,0,0,0,3,3,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,3,3,3,0,0,0},
				{0,0,3,3,3,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_8: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,3,0,0,3,3,3,0},
				{0,0,3,3,3,3,0,0},
				{0,3,0,0,3,3,3,0},
				{0,3,0,0,3,3,3,0},
				{0,0,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_9: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,3,0,0,3,3,3,0},
				{0,3,0,0,3,3,3,0},
				{0,0,3,3,3,3,3,0},
				{0,0,0,0,3,3,3,0},
				{0,0,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_A: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,3,0,0,3,3,3,0},
				{0,3,0,0,3,3,3,0},
				{0,3,3,3,3,3,3,0},
				{0,3,0,0,3,3,3,0},
				{0,3,0,0,3,3,3,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_B: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,3,3,3,3,0,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,3,3,3,0,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_C: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,3,3,0},
				{0,0,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_D: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,3,3,3,3,0,0},
				{0,3,0,0,3,3,3,0},
				{0,3,0,0,3,3,3,0},
				{0,3,0,0,3,3,3,0},
				{0,3,0,0,3,3,3,0},
				{0,3,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_E: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,3,3,3,3,3,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,3,3,3,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,3,3,3,3,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_F: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,3,3,3,3,3,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,3,3,3,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_G: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,3,3,3,0},
				{0,3,3,0,0,3,3,0},
				{0,0,3,3,3,3,3,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_H: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,0,0,0,3,3,0},
				{0,3,0,0,0,3,3,0},
				{0,3,3,3,3,3,3,0},
				{0,3,0,0,0,3,3,0},
				{0,3,0,0,0,3,3,0},
				{0,3,0,0,0,3,3,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_I: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_J: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,3,3,3,3,0},
				{0,0,0,0,3,3,0,0},
				{0,0,0,0,3,3,0,0},
				{0,3,3,0,3,3,0,0},
				{0,3,3,0,3,3,0,0},
				{0,0,3,3,3,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_K: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,0,3,3,0,0},
				{0,3,3,3,3,0,0,0},
				{0,3,3,3,3,0,0,0},
				{0,3,3,0,3,3,0,0},
				{0,3,3,0,0,3,3,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_L: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,3,3,3,3,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_M: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,0,0,0,3,3,0},
				{0,3,3,0,3,3,3,0},
				{0,3,3,3,3,3,3,0},
				{0,3,0,3,0,3,3,0},
				{0,3,0,0,0,3,3,0},
				{0,3,0,0,0,3,3,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_N: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,0,0,0,3,3,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,3,0,3,3,0},
				{0,3,0,3,3,3,3,0},
				{0,3,0,0,3,3,3,0},
				{0,3,0,0,0,3,3,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_O: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,0,0,3,3,0},
				{0,0,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_P: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,3,3,3,3,0,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,3,3,3,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_Q: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,3,3,0,0,0,3,0},
				{0,3,3,0,0,0,3,0},
				{0,3,3,0,3,0,3,0},
				{0,3,3,0,0,3,0,0},
				{0,0,3,3,3,0,3,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_R: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,3,3,3,3,0,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,0,0,3,3,0},
				{0,3,3,3,3,3,0,0},
				{0,3,3,0,3,0,0,0},
				{0,3,3,0,0,3,3,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_S: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,3,3,0,0,0,0,0},
				{0,0,3,3,3,3,0,0},
				{0,0,0,0,3,3,3,0},
				{0,3,0,0,3,3,3,0},
				{0,0,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_T: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,3,3,3,3,3,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_U: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,0,0,0,3,3,0},
				{0,3,0,0,0,3,3,0},
				{0,3,0,0,0,3,3,0},
				{0,3,0,0,0,3,3,0},
				{0,3,0,0,3,3,3,0},
				{0,0,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_V: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,3,0,0,0,3,3,0},
					{0,3,0,0,0,3,3,0},
					{0,3,0,0,0,3,3,0},
					{0,3,0,0,0,3,3,0},
					{0,0,3,0,3,3,0,0},
					{0,0,0,3,3,0,0,0},
					{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_W: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,3,0,0,0,3,3,0},
					{0,3,0,0,0,3,3,0},
					{0,3,0,3,0,3,3,0},
					{0,3,3,3,3,3,3,0},
					{0,3,3,0,3,3,3,0},
					{0,3,0,0,0,3,3,0},
					{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_X: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,3,0,0,0,3,3,0},
					{0,0,3,0,3,3,0,0},
					{0,0,0,3,3,0,0,0},
					{0,0,3,3,3,0,0,0},
					{0,3,3,0,0,3,0,0},
					{0,3,0,0,0,0,3,0},
					{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_Y: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,3,3,0,0,3,3,0},
					{0,3,3,0,0,3,3,0},
					{0,0,3,3,3,3,0,0},
					{0,0,0,3,3,0,0,0},
					{0,0,0,3,3,0,0,0},
					{0,0,0,3,3,0,0,0},
					{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BC_Z: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,3,3,3,3,3,3,0},
					{0,0,0,0,3,3,3,0},
					{0,0,0,3,3,3,0,0},
					{0,0,3,3,3,0,0,0},
					{0,3,3,3,0,0,0,0},
					{0,3,3,3,3,3,3,0},
					{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BCPR: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,3,3,0,0,0,0,0},
					{0,3,3,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BCHY: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,3,3,3,3,0,0},
					{0,0,3,3,3,3,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case CRSS: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,3,0,0,0,3,0},
					{0,0,0,3,0,3,0,0},
					{0,0,0,0,3,0,0,0},
					{0,0,0,3,0,3,0,0},
					{0,0,3,0,0,0,3,0},
					{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case HERT: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,0,3,3,0},
				{0,3,0,1,3,1,1,3},
				{0,3,0,1,1,1,1,3},
				{0,3,1,1,1,1,1,3},
				{0,0,3,1,1,1,3,0},
				{0,0,0,3,1,3,0,0},
				{0,0,0,0,3,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case DTX4: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,0,3,0,3,0,3,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_0: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,0,0,1,1,0},
				{0,0,1,1,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_1: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,1,1,0,0,0},
				{0,0,1,1,1,0,0,0},
				{0,0,0,1,1,0,0,0},
				{0,0,0,1,1,0,0,0},
				{0,0,0,1,1,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_2: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,1,0,0,1,1,1,0},
				{0,0,0,0,1,1,1,0},
				{0,0,1,1,1,1,0,0},
				{0,1,1,1,0,0,0,0},
				{0,1,1,1,1,1,1,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_3: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,1,1,1,1,0,0},
				{0,0,0,0,1,1,1,0},
				{0,0,1,1,1,1,0,0},
				{0,0,0,0,1,1,1,0},
				{0,0,0,0,1,1,1,0},
				{0,1,1,1,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_4: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,1,1,0,1,1,0,0},
				{0,1,0,0,1,1,0,0},
				{0,1,0,0,1,1,1,0},
				{0,1,1,1,1,1,1,0},
				{0,0,0,0,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);

			} break;
			case GC_5: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,1,1,1,1,0,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,1,1,1,0,0},
				{0,0,0,0,1,1,1,0},
				{0,1,0,0,1,1,1,0},
				{0,0,1,1,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_6: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,1,1,1,0,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,0,0,1,1,0},
				{0,0,1,1,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_7: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,1,1,1,1,1,0},
				{0,0,0,0,0,1,1,0},
				{0,0,0,0,1,1,0,0},
				{0,0,0,1,1,0,0,0},
				{0,0,1,1,1,0,0,0},
				{0,0,1,1,1,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_8: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,1,0,0,1,1,1,0},
				{0,0,1,1,1,1,0,0},
				{0,1,0,0,1,1,1,0},
				{0,1,0,0,1,1,1,0},
				{0,0,1,1,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_9: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,1,0,0,1,1,1,0},
				{0,1,0,0,1,1,1,0},
				{0,0,1,1,1,1,1,0},
				{0,0,0,0,1,1,1,0},
				{0,0,1,1,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_A: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,1,0,0,1,1,1,0},
				{0,1,0,0,1,1,1,0},
				{0,1,1,1,1,1,1,0},
				{0,1,0,0,1,1,1,0},
				{0,1,0,0,1,1,1,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_B: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,1,1,1,1,0,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,1,1,1,0,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,1,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_C: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,0,0,1,1,0},
				{0,0,1,1,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_D: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,1,1,1,1,0,0},
				{0,1,0,0,1,1,1,0},
				{0,1,0,0,1,1,1,0},
				{0,1,0,0,1,1,1,0},
				{0,1,0,0,1,1,1,0},
				{0,1,1,1,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_E: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,1,1,1,1,1,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,1,1,1,0,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,1,1,1,1,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_F: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,1,1,1,1,1,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,1,1,1,0,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_G: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,0,1,1,1,0},
				{0,1,1,0,0,1,1,0},
				{0,0,1,1,1,1,1,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_H: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,0,0,0,1,1,0},
				{0,1,0,0,0,1,1,0},
				{0,1,1,1,1,1,1,0},
				{0,1,0,0,0,1,1,0},
				{0,1,0,0,0,1,1,0},
				{0,1,0,0,0,1,1,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_I: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,0,0,1,1,0,0,0},
				{0,0,0,1,1,0,0,0},
				{0,0,0,1,1,0,0,0},
				{0,0,0,1,1,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_J: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,1,1,1,1,0},
				{0,0,0,0,1,1,0,0},
				{0,0,0,0,1,1,0,0},
				{0,1,1,0,1,1,0,0},
				{0,1,1,0,1,1,0,0},
				{0,0,1,1,1,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_K: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,0,1,1,0,0},
				{0,1,1,1,1,0,0,0},
				{0,1,1,1,1,0,0,0},
				{0,1,1,0,1,1,0,0},
				{0,1,1,0,0,1,1,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_L: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,1,1,1,1,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_M: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,0,0,0,1,1,0},
				{0,1,1,0,1,1,1,0},
				{0,1,1,1,1,1,1,0},
				{0,1,0,1,0,1,1,0},
				{0,1,0,0,0,1,1,0},
				{0,1,0,0,0,1,1,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_N: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,0,0,0,1,1,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,1,0,1,1,0},
				{0,1,0,1,1,1,1,0},
				{0,1,0,0,1,1,1,0},
				{0,1,0,0,0,1,1,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_O: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,0,0,1,1,0},
				{0,0,1,1,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_P: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,1,1,1,1,0,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,1,1,1,0,0},
				{0,1,1,0,0,0,0,0},
				{0,1,1,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_Q: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,1,1,0,0,0,1,0},
				{0,1,1,0,0,0,1,0},
				{0,1,1,0,1,0,1,0},
				{0,1,1,0,0,1,0,0},
				{0,0,1,1,1,0,1,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_R: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,1,1,1,1,0,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,0,0,1,1,0},
				{0,1,1,1,1,1,0,0},
				{0,1,1,0,1,0,0,0},
				{0,1,1,0,0,1,1,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_S: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,1,1,0,0,0,0,0},
				{0,0,1,1,1,1,0,0},
				{0,0,0,0,1,1,1,0},
				{0,1,0,0,1,1,1,0},
				{0,0,1,1,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_T: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,1,1,1,1,1,0},
				{0,0,0,1,1,0,0,0},
				{0,0,0,1,1,0,0,0},
				{0,0,0,1,1,0,0,0},
				{0,0,0,1,1,0,0,0},
				{0,0,0,1,1,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_U: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,0,0,0,1,1,0},
				{0,1,0,0,0,1,1,0},
				{0,1,0,0,0,1,1,0},
				{0,1,0,0,0,1,1,0},
				{0,1,0,0,1,1,1,0},
				{0,0,1,1,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_V: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,0,0,0,1,1,0},
				{0,1,0,0,0,1,1,0},
				{0,1,0,0,0,1,1,0},
				{0,1,0,0,0,1,1,0},
				{0,0,1,0,1,1,0,0},
				{0,0,0,1,1,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_W: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,0,0,0,1,1,0},
				{0,1,0,0,0,1,1,0},
				{0,1,0,1,0,1,1,0},
				{0,1,1,1,1,1,1,0},
				{0,1,1,0,1,1,1,0},
				{0,1,0,0,0,1,1,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_X: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,1,0,0,0,1,1,0},
				{0,0,1,0,1,1,0,0},
				{0,0,0,1,1,0,0,0},
				{0,0,1,1,1,0,0,0},
				{0,1,1,0,0,1,0,0},
				{0,1,0,0,0,0,1,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_Y: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,1,1,0,0,1,1,0},
					{0,1,1,0,0,1,1,0},
					{0,0,1,1,1,1,0,0},
					{0,0,0,1,1,0,0,0},
					{0,0,0,1,1,0,0,0},
					{0,0,0,1,1,0,0,0},
					{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GC_Z: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,1,1,1,1,1,1,0},
					{0,0,0,0,1,1,1,0},
					{0,0,0,1,1,1,0,0},
					{0,0,1,1,1,0,0,0},
					{0,1,1,1,0,0,0,0},
					{0,1,1,1,1,1,1,0},
					{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GCHY: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,1,1,1,1,0,0},
					{0,0,1,1,1,1,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case CRGT: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,0,3,3,3,0,0,0},
					{0,3,0,0,0,3,0,0},
					{3,0,3,0,3,0,3,0},
					{3,0,3,0,3,0,3,0},
					{3,0,3,3,3,0,3,0},
					{0,3,0,0,0,3,0,0},
					{0,0,3,3,3,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case QOTE: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,3,3,0,3,3},
					{0,0,0,3,3,0,3,3},
					{0,0,0,0,3,0,0,3},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case COMA: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,3,3,0,0,0,0,0},
					{0,3,3,0,0,0,0,0},
					{0,0,3,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case DTQT: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,3,3,0,3,3},
					{0,0,0,3,3,0,3,3},
					{0,0,0,0,3,0,0,3},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,3,3,0,0,0,0,0},
					{0,3,3,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case DTLN: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{3,0,3,0,3,0,3,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case NTD0: {
				char part[PART_SIZE][PART_SIZE] = {
					{3,3,3,3,3,0,0,0},
					{3,3,0,0,3,3,0,0},
					{3,3,0,0,3,3,0,0},
					{3,3,0,0,3,3,0,3},
					{3,3,3,3,3,0,0,3},
					{3,3,0,0,3,3,0,0},
					{3,3,0,0,3,3,0,0},
					{3,3,0,0,3,3,0,3},
				};
				drawPart(X, Y, part);
			} break;
			case NTD1: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{3,0,3,3,0,0,3,3},
					{3,0,3,3,0,3,3,0},
					{3,3,3,3,0,3,3,0},
					{0,0,3,3,0,3,3,0},
					{3,3,3,3,0,0,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case NTD2: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,3,3,3},
					{3,3,0,0,3,3,0,0},
					{0,3,3,0,3,3,0,0},
					{0,3,3,0,0,3,3,3},
					{0,3,3,0,0,0,0,0},
					{3,3,0,0,0,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case NTD3: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{3,3,0,0,0,0,0,0},
					{3,3,0,0,3,3,3,3},
					{3,3,0,3,3,0,0,3},
					{3,3,0,3,3,0,0,3},
					{3,3,0,3,3,0,0,3},
					{3,0,0,0,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case NTD4: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{3,0,0,0,0,0,3,3},
					{3,0,0,0,0,3,3,0},
					{3,0,0,0,0,3,3,3},
					{3,0,3,3,0,3,3,0},
					{3,0,3,3,0,0,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case NTD5: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{3,3,0,0,3,3,0,0},
					{0,3,3,0,0,3,3,3},
					{3,3,3,0,0,0,3,3},
					{0,0,0,0,0,3,3,3},
					{3,3,3,0,3,3,3,0},
				};
				drawPart(X, Y, part);
			} break;
			case NTD6: {
				char part[PART_SIZE][PART_SIZE] = {
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0},
					{3,3,0,0,3,3,3,0},
					{3,0,0,3,3,0,0,3},
					{0,0,0,3,3,3,3,3},
					{3,0,0,3,3,0,0,0},
					{3,3,0,0,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BRC0: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,3,1,1,1,3},
				{3,3,3,3,3,3,3,3},
				{1,3,0,1,1,3,0,1},
				{1,3,1,1,1,3,1,1},
				{3,3,3,3,3,3,3,3},
				{0,1,1,3,0,1,1,3},
				{1,1,1,3,1,1,1,3},
				{3,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BRC1: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,3,3,3,3,3},
				{0,1,1,3,0,1,1,3},
				{1,1,1,3,1,1,1,3},
				{3,3,3,3,3,3,3,3},
				{1,3,0,1,1,3,0,1},
				{1,3,1,1,1,3,1,1},
				{3,3,3,3,3,3,3,3},
				{0,1,1,3,0,1,1,3},
				};
				drawPart(X, Y, part);
			} break;
			case BRC2: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,3,0,1,1,3,0,1},
				{1,3,1,1,1,3,1,1},
				{3,3,3,3,3,3,3,3},
				{0,1,1,3,0,1,1,3},
				{1,1,1,3,1,1,1,3},
				{3,3,3,3,3,3,3,3},
				{1,3,0,1,1,3,0,1},
				{1,3,1,1,1,3,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case BD00: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,3,3,3,3,0},
				{3,3,3,3,3,3,3,0},
				{3,3,3,3,3,3,3,0},
				{3,3,3,3,3,3,3,0},
				{3,3,3,3,3,3,3,0},
				{3,3,3,3,3,3,3,0},
				{3,3,3,3,3,3,3,0},
				{3,3,3,3,3,3,3,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD01: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,0,0},
				{0,3,3,3,3,0,0,2},
				{0,3,3,3,3,0,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case BD02: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				{2,2,2,2,2,2,2,2},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD03: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{0,0,3,3,3,3,3,3},
				{2,0,0,3,3,3,3,3},
				{2,2,0,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BD04: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,3,3,3,3,0,2,0},
				{0,3,3,3,3,0,2,0},
				{0,3,3,3,3,0,2,0},
				{0,3,3,3,3,0,2,0},
				{0,3,3,3,3,0,2,0},
				{0,0,0,0,0,0,2,0},
				{0,2,2,2,2,0,2,0},
				{0,2,2,2,2,0,2,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD05: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,2,0,3,3,3,3,3},
				{0,2,0,3,3,3,3,3},
				{0,2,0,3,3,3,3,3},
				{0,2,0,3,3,3,3,3},
				{0,2,0,3,3,3,3,3},
				{0,2,0,0,0,0,0,0},
				{0,2,0,2,2,2,2,2},
				{0,2,0,2,2,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case BD06: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,2,2,2,2,0,2,2},
				{0,2,2,2,2,0,0,2},
				{0,2,2,2,2,2,0,0},
				{0,2,2,2,2,2,2,2},
				{0,2,2,2,2,2,2,2},
				{0,0,0,0,0,0,0,0},
				{0,2,2,2,2,2,2,2},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD07: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{2,2,2,2,2,2,2,2},
				{0,0,0,0,0,0,0,0},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{0,0,0,0,0,0,0,0},
				{2,2,2,2,2,2,2,2},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD08: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,2,0,2,2,2,2,2},
				{2,0,0,2,2,2,2,2},
				{0,0,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{0,0,0,0,0,0,0,0},
				{2,2,2,2,2,2,2,2},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD09: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,2,2,2,2,2,2,2},
				{0,0,0,0,0,0,0,0},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BD10: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{2,2,2,2,2,2,2,2},
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BD11: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,3,3,3,3,0,2,0},
				{0,3,3,3,3,0,2,0},
				{0,3,3,3,3,0,2,0},
				{0,3,3,3,3,0,2,0},
				{0,3,3,3,3,0,2,0},
				{0,3,3,3,3,0,2,0},
				{0,3,3,3,3,0,2,0},
				{0,3,3,3,3,0,2,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD12: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,2,0,3,3,3,3,3},
				{0,2,0,3,3,3,3,3},
				{0,2,0,3,3,3,3,3},
				{0,2,0,3,3,3,3,3},
				{0,2,0,3,3,3,3,3},
				{0,2,0,3,3,3,3,3},
				{0,2,0,3,3,3,3,3},
				{0,2,0,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BD13: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,3,3,3,3,0,2,2},
				{0,3,3,3,3,0,0,2},
				{0,3,3,3,3,3,0,0},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,0,0},
				{0,3,3,3,3,0,0,2},
				{0,3,3,3,3,0,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case BD14: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{2,2,2,2,2,2,2,2},
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				{2,2,2,2,2,2,2,2},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD15: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,2,0,3,3,3,3,3},
				{2,0,0,3,3,3,3,3},
				{0,0,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{0,0,3,3,3,3,3,3},
				{2,0,0,3,3,3,3,3},
				{2,2,0,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BD16: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,3,3,3,3,0,2,2},
				{0,3,3,3,3,0,0,2},
				{0,3,3,3,3,3,0,0},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BD17: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,2,0,3,3,3,3,3},
				{2,0,0,3,3,3,3,3},
				{0,0,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BD18: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,1,1,1},
				{3,3,3,3,1,0,0,0},
				{3,3,3,1,0,0,1,2},
				{3,3,3,1,0,1,2,3},
				{3,3,3,1,0,2,3,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD19: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{1,1,1,1,1,1,1,1},
				{0,0,0,0,0,0,0,0},
				{2,2,2,2,2,2,2,2},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD20: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{1,1,1,3,3,3,3,3},
				{0,0,0,1,3,3,3,3},
				{2,1,0,0,1,3,3,3},
				{3,2,1,0,1,3,3,3},
				{0,3,2,0,1,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BD21: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BD22: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,1,0,2,3,0},
				{3,3,3,1,0,2,3,0},
				{3,3,3,1,0,2,3,0},
				{3,3,3,1,0,2,3,0},
				{3,3,3,1,0,2,3,0},
				{3,3,3,1,0,2,3,0},
				{3,3,3,1,0,2,3,0},
				{3,3,3,1,0,2,3,0}
				};
				drawPart(X, Y, part);
			} break;
			case BD23: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,3,2,0,1,3,3,3},
				{0,3,2,0,1,3,3,3},
				{0,3,2,0,1,3,3,3},
				{0,3,2,0,1,3,3,3},
				{0,3,2,0,1,3,3,3},
				{0,3,2,0,1,3,3,3},
				{0,3,2,0,1,3,3,3},
				{0,3,2,0,1,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BD24: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,1,0,2,3,0},
				{3,3,3,1,0,1,2,3},
				{3,3,3,1,0,0,1,2},
				{3,3,3,3,1,0,0,0},
				{3,3,3,3,3,1,1,1},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BD25: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{2,2,2,2,2,2,2,2},
				{0,0,0,0,0,0,0,0},
				{1,1,1,1,1,1,1,1},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BD26: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,3,2,0,1,3,3,3},
				{3,2,1,0,1,3,3,3},
				{2,1,0,0,1,3,3,3},
				{0,0,0,1,3,3,3,3},
				{1,1,1,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BD27: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,3,3,3,3},
				{0,0,0,3,3,3,3,3},
				{0,0,3,3,3,0,0,0},
				{0,0,3,3,0,0,1,1},
				{0,0,3,3,0,1,1,0},
				{0,0,3,3,0,1,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD28: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				{1,1,1,1,1,1,1,1},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD29: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,0,0,0,0},
				{3,3,3,3,3,0,0,0},
				{0,0,0,3,3,3,0,0},
				{1,1,0,0,3,3,0,0},
				{0,1,1,0,3,3,0,0},
				{0,0,1,0,3,3,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD30: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,3,3,0,1,0,0},
				{0,0,3,3,0,1,0,0},
				{0,0,3,3,0,1,0,0},
				{0,0,3,3,0,1,0,0},
				{0,0,3,3,0,1,0,0},
				{0,0,3,3,0,1,0,0},
				{0,0,3,3,0,1,0,0},
				{0,0,3,3,0,1,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD31: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,1,0,3,3,0,0},
				{0,0,1,0,3,3,0,0},
				{0,0,1,0,3,3,0,0},
				{0,0,1,0,3,3,0,0},
				{0,0,1,0,3,3,0,0},
				{0,0,1,0,3,3,0,0},
				{0,0,1,0,3,3,0,0},
				{0,0,1,0,3,3,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD32: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,3,3,0,1,0,0},
				{0,0,3,3,0,1,1,0},
				{0,0,3,3,0,0,1,1},
				{0,0,3,3,3,0,0,0},
				{0,0,0,3,3,3,3,3},
				{0,0,0,0,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD33: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{1,1,1,1,1,1,1,1},
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BD34: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,1,0,3,3,0,0},
				{0,1,1,0,3,3,0,0},
				{1,1,0,0,3,3,0,0},
				{0,0,0,3,3,3,0,0},
				{3,3,3,3,3,0,0,0},
				{3,3,3,3,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case GVER: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,3,3,3,3,3},
				{3,0,0,0,0,0,0,3},
				{3,0,1,1,1,1,2,3},
				{3,0,1,1,1,1,2,3},
				{3,0,1,1,1,1,2,3},
				{3,0,1,1,1,1,2,3},
				{3,2,2,2,2,2,2,3},
				{3,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case LN_G: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN00: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,3,3,3},
				{0,0,3,3,3,3,3,3},
				{0,0,3,3,0,0,0,0},
				{0,0,3,3,0,0,0,0},
				{0,0,3,3,0,0,3,1},
				{0,0,3,3,0,0,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case MN01: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{1,1,1,1,1,1,3,1},
				{1,1,3,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case MN02: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,0,0},
				{3,3,3,3,3,3,0,0},
				{0,0,0,0,3,3,0,0},
				{0,0,0,0,3,3,0,0},
				{1,1,0,0,3,3,0,0},
				{1,1,0,0,3,3,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN03: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,3,3,0,0,1,1},
				{0,0,3,3,0,0,1,1},
				{0,0,3,3,0,0,1,1},
				{0,0,3,3,0,0,1,1},
				{0,0,3,3,0,0,1,1},
				{0,0,3,3,0,0,1,1},
				{0,0,3,3,0,0,3,1},
				{0,0,3,3,0,0,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case MN04: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{1,3,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,3,1,1,1,1},
				{3,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case MN05: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,0,0,3,3,0,0},
				{1,3,0,0,3,3,0,0},
				{1,1,0,0,3,3,0,0},
				{1,1,0,0,3,3,0,0},
				{1,1,0,0,3,3,0,0},
				{3,1,0,0,3,3,0,0},
				{1,1,0,0,3,3,0,0},
				{1,1,0,0,3,3,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN06: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,3,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,3,1,1,1},
				{1,1,1,1,1,1,1,3},
				{1,3,1,1,1,1,3,3},
				{1,1,1,1,1,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case MN07: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,3,1,1},
				{1,3,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN08: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{1,3,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,3,1,1,1,1},
				{3,1,1,1,1,1,1,1},
				{3,3,1,1,1,1,3,1},
				{3,3,3,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case MN09: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,3,3,0},
				{1,3,1,1,1,3,3,0},
				{1,1,1,1,1,3,3,0},
				{1,1,1,1,1,3,3,0},
				{1,1,1,3,1,3,3,0},
				{3,1,1,1,1,3,3,0},
				{1,1,1,1,1,3,3,0},
				{1,1,1,1,1,3,3,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN10: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,3,3,1,1,3,1,1},
				{0,3,3,1,1,1,1,1},
				{0,3,3,1,1,1,3,1},
				{0,3,3,1,1,1,1,1},
				{0,3,3,1,1,1,1,1},
				{0,3,3,1,3,1,1,1},
				{0,3,3,1,1,1,3,1},
				{0,3,3,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case MN11: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,3,1},
				{1,3,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,3,1,1,1},
				{3,1,1,1,1,1,1,1},
				{1,1,1,3,3,3,3,3},
				{1,1,1,3,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN12: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,3,1},
				{1,1,3,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,3,1,1},
				{1,1,1,1,1,1,1,1},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN13: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,3,3,3},
				{1,1,1,3,1,1,3,3},
				{1,1,1,1,1,1,1,3},
				{1,1,1,1,1,1,1,1},
				{1,3,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN14: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,3,1,1,1,1,1},
				{3,3,3,3,3,3,3,3},
				{3,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN15: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,1,1,1,1,1},
				{3,3,1,1,3,1,1,1},
				{3,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,1,1,1,1,1,1},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN16: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,3,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,1,1,1,1,1,1},
				{3,3,3,3,3,1,1,1},
				{0,0,0,0,3,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case MN17: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,3,0,0,0,0},
				{1,1,1,3,0,0,0,0},
				{1,1,1,3,0,0,0,0},
				{1,3,1,3,0,0,0,0},
				{1,1,1,3,0,0,0,0},
				{1,1,1,3,0,0,0,0},
				{1,1,1,3,0,0,0,0},
				{1,1,1,3,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN18: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN19: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,3,1,1,1},
				{0,0,0,0,3,1,3,1},
				{0,0,0,0,3,1,1,1},
				{0,0,0,0,3,1,1,1},
				{0,0,0,0,3,1,1,1},
				{0,0,0,0,3,1,1,1},
				{0,0,0,0,3,1,1,3},
				{0,0,0,0,3,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case MN20: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,3,0,0,0,0},
				{1,1,1,3,3,3,3,3},
				{1,1,1,1,1,1,1,1},
				{1,3,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,3,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case MN21: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,3,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,3,1,1},
				{1,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case MN22: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,3,1,1,1},
				{3,3,3,3,3,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,1,1,1,1,1,1},
				{1,3,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case MN23: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,3,0,0,0,0},
				{1,1,1,3,3,3,3,3},
				{1,1,1,3,2,2,2,2},
				{1,1,1,3,2,2,2,2},
				{1,1,1,3,2,2,2,2},
				{1,1,1,3,2,2,2,2},
				{1,3,1,3,3,3,3,3},
				{1,1,1,3,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN24: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN25: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{3,3,3,3,3,3,3,3},
				{3,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN26: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,3,1,1,1},
				{3,3,3,3,3,1,1,1},
				{2,2,2,2,3,1,1,1},
				{2,2,2,2,3,1,1,1},
				{2,2,2,2,3,1,1,1},
				{2,2,2,2,3,1,1,1},
				{3,3,3,3,3,1,3,1},
				{0,0,0,0,3,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case MN27: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,3,3,0,0,1,1},
				{0,0,3,3,0,0,1,1},
				{0,0,3,3,0,0,0,0},
				{0,0,3,3,0,0,0,0},
				{0,0,3,3,3,3,3,3},
				{0,0,3,3,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN28: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,3,1,1},
				{1,3,1,1,1,1,1,1},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN29: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,0,0,3,3,0,0},
				{1,3,0,0,3,3,0,0},
				{0,0,0,0,3,3,0,0},
				{0,0,0,0,3,3,0,0},
				{3,3,3,3,3,3,0,0},
				{3,3,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN30: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,3,0,0,0},
				{0,0,0,0,3,0,0,0},
				{0,0,0,0,3,0,0,0},
				{0,0,0,0,3,0,0,0},
				{0,0,0,0,3,0,0,0},
				{0,0,0,0,3,0,0,0},
				{0,0,0,0,3,0,0,0},
				{0,0,0,0,3,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN31: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,3,0,0,0},
				{3,3,3,3,3,3,3,3},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN32: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,3,3,3},
				{1,1,1,3,1,1,3,3},
				{1,1,1,1,1,1,1,3},
				{1,1,1,1,1,1,1,1},
				{1,3,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,3,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN33: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,3,1,1,1,1,1},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,3,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN34: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,1,1,1,1,1},
				{3,3,1,1,3,1,1,1},
				{3,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,1,1,1,1,1,1},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,3,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN35: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,3,0,0,0},
				{3,3,3,3,3,3,3,3},
				{1,1,1,1,1,1,3,1},
				{1,1,1,1,1,1,1,1},
				{1,1,3,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case MN36: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,3,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case MN37: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,3,1,1,1,1,1},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN38: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,1,1,1,1,1,1},
				{1,1,3,1,1,1,1,1},
				{1,1,1,1,1,1,3,1},
				{1,1,1,1,1,1,1,1},
				{3,3,3,3,3,3,3,3},
				{0,0,0,0,3,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case MN39: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,3,3,3},
				{1,3,1,1,1,1,3,3},
				{1,1,1,1,1,1,1,3},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{3,1,1,1,1,1,1,1},
				{1,1,1,3,3,3,3,3},
				{1,1,1,3,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case DN00: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{2,2,2,2,2,2,2,2},
				{3,3,3,3,3,3,3,3},
				{2,2,2,2,2,2,2,2},
				{1,1,1,1,1,1,1,1},
				{2,2,2,2,2,2,2,2},
				{1,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case DN01: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,0,0,0},
				{1,1,1,0,0,0,0,0},
				{1,1,0,0,0,0,0,0},
				{1,0,0,0,0,0,0,0},
				{1,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case DN02: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,1,1,1,1,1,1,1},
				{0,0,0,1,1,1,1,1},
				{0,0,0,0,1,1,1,1},
				{0,0,0,0,0,1,1,1},
				{0,0,0,0,0,1,1,1},
				{0,0,0,0,0,0,1,1},
				{0,0,0,0,0,0,1,1},
				{0,0,0,0,0,0,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case DN03: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{1,0,0,0,0,0,0,0},
				{1,0,0,0,0,0,0,0},
				{1,1,0,0,0,0,0,0},
				{1,1,1,0,0,0,0,0},
				{1,1,1,1,1,0,0,0},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case DN04: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,1,1},
				{0,0,0,0,0,1,1,1},
				{0,0,0,0,0,1,1,1},
				{0,0,0,0,1,1,1,1},
				{0,0,0,1,1,1,1,1},
				{0,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case DN05: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,3},
				{1,1,1,1,1,1,3,0},
				{1,1,1,1,1,1,3,0},
				{1,1,1,1,1,3,0,0},
				{1,1,1,1,1,3,0,0},
				{1,1,1,1,1,3,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case DN06: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{0,0,0,0,0,0,0,0},
				{1,1,1,1,1,1,1,1},
				{0,0,0,0,0,0,0,0},
				{1,1,1,1,1,1,1,1},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case DN07: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,3,0},
				{0,0,0,0,0,0,3,0},
				{0,0,0,0,0,0,3,3},
				{0,0,0,0,0,3,0,2},
				{0,0,0,0,3,0,0,2},
				{0,0,0,3,0,0,2,1},
				{0,0,3,0,0,2,2,1},
				{0,3,0,0,2,2,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case DN08: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,0,0,2,2,1,1,1},
				{0,0,2,2,2,1,1,2},
				{0,2,2,2,1,1,1,2},
				{2,2,2,1,1,1,1,2},
				{2,2,1,1,1,1,2,2},
				{2,2,1,1,1,1,2,2},
				{2,1,1,1,1,2,2,2},
				{2,1,1,1,1,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case DN09: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,3,0,0,2,2,2,2},
				{0,3,0,0,2,2,2,2},
				{3,0,0,2,2,2,2,2},
				{3,0,0,2,2,2,2,2},
				{3,0,0,2,2,2,2,2},
				{3,0,0,2,2,2,2,2},
				{3,0,0,2,2,2,2,2},
				{3,0,0,2,2,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case DN10: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,3,1},
				{1,1,1,1,1,1,1,3},
				{1,1,1,1,1,1,1,3},
				{0,0,0,0,0,0,0,3},
				{1,1,1,1,1,1,1,3},
				{0,0,0,0,0,0,0,3},
				{1,1,1,1,1,1,1,3},
				{0,0,0,0,0,0,0,3},
				};
				drawPart(X, Y, part);
			} break;
			case DN11: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,3},
				{0,0,0,0,0,0,3,0},
				{0,0,0,0,0,3,0,0},
				{0,0,0,0,3,0,0,2},
				{0,0,0,3,0,0,2,2},
				{0,0,3,0,0,2,2,2},
				{0,0,3,0,2,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case DN12: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,1,1,1,1,2,2,2},
				{2,1,1,1,1,1,2,2},
				{2,2,1,1,1,1,2,2},
				{2,2,2,1,1,1,1,2},
				{2,2,2,2,1,1,1,1},
				{3,3,3,3,3,3,3,3},
				{1,1,1,1,1,1,1,1},
				{3,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case DN13: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,3,0,2,2,2,2,2},
				{0,3,0,0,2,2,2,2},
				{0,0,3,0,2,2,2,2},
				{0,0,3,0,0,2,2,2},
				{0,0,0,3,0,0,0,2},
				{0,0,0,0,3,3,3,3},
				{0,0,0,0,0,3,0,0},
				{0,0,0,0,0,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case DN14: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,2,2,2},
				{1,1,1,1,2,2,2,2},
				{1,1,1,1,2,2,2,2},
				{1,1,1,1,2,2,2,2},
				{1,1,1,1,2,2,2,2},
				{1,1,1,1,2,2,2,2},
				{1,1,1,1,2,2,2,2},
				{1,1,1,1,1,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case DN15: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,1,0},
				{0,0,0,0,0,0,1,0},
				{0,0,0,0,0,0,1,0},
				{0,0,0,0,0,0,1,0},
				{0,0,0,0,0,0,1,0},
				{0,0,0,0,0,0,1,0},
				{0,0,0,0,0,0,1,0},
				{0,0,0,0,0,0,1,0},
				};
				drawPart(X, Y, part);
			} break;
			case DN16: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,1,1,1,1,1,0,0},
				{0,1,1,1,1,1,0,0},
				{0,1,1,1,1,1,0,0},
				{0,1,1,1,1,1,0,0},
				{0,1,1,1,1,1,0,0},
				{0,1,1,1,1,1,0,0},
				{0,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case DN17: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,1,0,0},
				{0,0,0,0,0,1,0,0},
				{0,0,0,0,0,1,0,0},
				{0,0,0,0,0,1,0,0},
				{0,0,0,0,1,1,1,0},
				{0,0,0,0,1,1,1,0},
				};
				drawPart(X, Y, part);
			} break;
			case DN18: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,1,0,0,0,0},
				{0,0,1,1,1,0,0,0},
				{0,1,1,1,1,1,0,0},
				{1,1,1,1,1,1,1,0},
				{1,1,1,1,1,1,1,0},
				{1,1,1,1,1,1,1,0},
				{0,1,1,1,1,1,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL00: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,0,0,0,0,0},
				{3,3,3,1,0,0,0,0},
				{3,3,3,1,1,0,1,1},
				{3,3,3,1,1,1,0,0},
				{3,3,3,1,1,1,0,2},
				{3,3,3,1,1,1,0,2},
				{3,3,3,1,1,1,0,2},
				{3,3,3,1,1,1,0,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL01: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{1,1,1,1,1,1,1,1},
				{0,0,0,0,0,0,0,0},
				{2,2,2,2,2,2,2,2},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL02: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,3,3,3},
				{0,0,0,0,1,3,3,3},
				{1,1,0,1,1,3,3,3},
				{0,0,1,1,1,3,3,3},
				{2,0,1,1,1,3,3,3},
				{2,0,1,1,1,3,3,3},
				{2,0,1,1,1,3,3,3},
				{2,0,1,1,1,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL03: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,1,1,1,0,2},
				{3,3,3,1,1,1,0,2},
				{3,3,3,1,1,1,0,2},
				{3,3,3,1,1,1,0,2},
				{3,3,3,1,1,1,0,2},
				{3,3,3,1,1,1,0,2},
				{3,3,3,1,1,1,0,2},
				{3,3,3,1,1,1,0,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL04: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,3,3,3},
				{0,0,3,0,0,0,0,0},
				{0,0,3,0,0,0,0,3},
				{0,0,3,0,0,0,3,0},
				{0,0,3,0,0,0,3,0},
				{0,0,3,0,0,3,0,0},
				{0,0,3,1,1,3,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL05: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,0,3,3,3,3,3,3},
				{3,0,3,0,0,0,0,0},
				{0,0,3,0,0,0,0,0},
				{0,0,3,0,0,0,0,0},
				{0,0,3,0,0,0,0,0},
				{0,0,3,0,0,0,0,0},
				{0,0,3,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL06: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,3,0,0,3,3,3,3},
				{3,3,0,0,3,0,0,0},
				{3,3,0,0,3,0,0,0},
				{3,3,0,0,3,0,0,0},
				{3,3,0,0,3,0,0,0},
				{3,3,0,0,3,0,0,0},
				{3,3,0,0,3,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL07: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,0,3,3,0,0,0,3},
				{1,1,3,3,0,0,0,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL08: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,0},
				{3,0,0,0,0,3,3,0},
				{3,0,0,0,0,3,3,0},
				{3,0,0,0,0,3,3,0},
				{3,0,0,0,0,3,3,0},
				{0,0,0,0,0,3,3,0},
				{1,1,1,1,1,3,3,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL09: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,3,3,3,3,3,3},
				{0,3,0,0,0,0,0,3},
				{0,3,0,0,0,0,0,3},
				{0,3,0,0,0,0,0,3},
				{0,3,0,0,0,0,0,3},
				{0,3,0,0,0,0,0,3},
				{0,3,1,1,1,1,1,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL10: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,3,0,0,0,0,0,0},
				{0,3,0,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,3,0,0,0,0},
				{0,3,3,3,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL11: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,3,3,3,3,3},
				{0,0,0,3,0,0,0,0},
				{0,0,0,3,0,0,0,0},
				{0,0,0,3,0,0,0,0},
				{0,0,0,3,0,0,0,0},
				{0,0,0,3,0,0,0,0},
				{0,0,0,3,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL12: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{1,3,3,0,0,0,0,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL13: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,3},
				{0,0,0,0,0,3,3,0},
				{0,0,0,3,3,0,0,0},
				{0,0,3,0,0,0,0,0},
				{0,3,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{1,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL14: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,3,0,3,3,3,0,0},
				{3,3,0,3,0,3,3,3},
				{3,3,0,3,0,0,0,3},
				{3,3,0,3,0,0,0,0},
				{3,3,0,3,0,0,0,0},
				{3,3,0,3,0,0,0,0},
				{3,3,0,3,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL15: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,3,3,3,3},
				{0,0,0,0,0,0,3,0},
				{3,3,0,0,0,0,3,0},
				{0,3,3,0,0,0,3,0},
				{0,0,3,3,0,0,3,0},
				{0,0,0,3,3,0,0,0},
				{1,1,1,1,3,3,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL16: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,0,3,0,0,0,3,0},
				{0,0,3,3,0,3,3,0},
				{0,0,3,0,3,0,3,0},
				{0,0,3,0,0,0,3,0},
				{0,0,3,0,0,0,3,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL17: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,0,1,1,1,3,3,3},
				{2,0,1,1,1,3,3,3},
				{2,0,1,1,1,3,3,3},
				{2,0,1,1,1,3,3,3},
				{2,0,1,1,1,3,3,3},
				{2,0,1,1,1,3,3,3},
				{2,0,1,1,1,3,3,3},
				{2,0,1,1,1,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL18: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,1,1,1,0,2},
				{3,3,3,1,1,1,0,2},
				{3,3,3,1,1,1,0,2},
				{3,3,3,1,1,1,0,2},
				{3,3,3,1,1,1,0,0},
				{3,3,3,1,1,3,3,3},
				{3,3,3,1,3,3,3,3},
				{3,3,3,2,2,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL19: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{2,2,2,2,2,2,2,2},
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{2,2,2,2,2,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL20: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,0,1,1,1,3,3,3},
				{2,0,1,1,1,3,3,3},
				{2,0,1,1,1,3,3,3},
				{2,0,1,1,1,3,3,3},
				{0,0,1,1,1,3,3,3},
				{3,3,3,1,1,3,3,3},
				{3,3,3,3,1,3,3,3},
				{2,2,2,2,2,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL21: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,2,2,2,2,2,2,2},
				{3,3,3,3,3,3,3,3},
				{2,2,2,2,2,2,2,2},
				{2,2,2,2,2,2,2,2},
				{1,1,1,1,1,1,1,1},
				{2,2,2,2,2,2,2,2},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL22: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,2,2,2,2,2,2,2},
				{3,3,3,3,3,3,3,3},
				{2,2,2,2,2,2,2,3},
				{2,2,2,2,2,2,3,0},
				{1,1,1,1,1,1,3,0},
				{2,2,2,2,2,3,0,0},
				{1,1,1,1,1,3,0,0},
				{1,1,1,1,1,3,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL23: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,2,2,2,2,2,2,2},
				{3,3,3,3,3,3,3,3},
				{3,2,2,2,2,2,2,2},
				{0,3,2,2,2,2,2,2},
				{1,3,1,1,1,1,1,1},
				{1,1,3,2,2,2,2,2},
				{1,1,3,1,1,1,1,1},
				{1,2,3,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL24: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,3,1,3,0,0,0},
				{0,0,3,1,3,0,0,0},
				{0,0,3,3,0,0,0,0},
				{0,0,3,3,0,0,0,0},
				{0,0,3,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL25: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,3,1,1,1,1,1},
				{0,0,3,1,1,1,1,1},
				{0,0,3,1,1,1,1,1},
				{0,0,3,1,1,1,1,1},
				{0,0,3,1,1,1,1,1},
				{0,0,3,1,1,1,1,1},
				{0,0,3,1,1,1,1,1},
				{0,0,3,2,2,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL26: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,0,0,0,0,0,3},
				{3,3,0,0,0,0,0,3},
				{3,3,0,0,0,0,0,0},
				{3,3,0,0,0,0,0,0},
				{3,3,0,0,0,0,0,0},
				{3,3,0,0,0,0,0,0},
				{3,3,0,0,0,0,0,0},
				{3,3,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL27: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,3,2,2,2,2,2},
				{0,0,3,2,2,2,2,2},
				{0,0,3,2,2,2,2,2},
				{0,0,3,2,2,2,2,2},
				{0,0,3,2,2,2,2,2},
				{0,0,3,2,2,2,2,2},
				{0,0,3,2,2,2,2,2},
				{0,0,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL28: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,0,0,0,0,0,0},
				{3,3,0,0,0,0,0,0},
				{3,3,0,0,0,0,0,0},
				{3,3,0,0,0,0,0,0},
				{3,3,0,0,0,0,0,0},
				{3,3,0,0,0,0,0,0},
				{3,3,0,0,0,0,0,0},
				{3,3,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL29: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,3,3,3,3,3,3},
				{0,0,3,3,3,3,3,3},
				{0,0,3,3,3,3,3,3},
				{0,0,3,3,3,3,3,3},
				{0,0,3,3,3,3,3,3},
				{0,0,3,3,3,3,3,3},
				{0,0,3,3,3,3,3,3},
				{0,0,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL30: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,3,3,3,0,0},
				{3,3,3,3,3,3,0,0},
				{3,3,3,3,3,3,0,0},
				{3,3,3,3,3,3,0,0},
				{3,3,3,3,3,3,0,0},
				{3,3,3,3,3,3,0,0},
				{3,3,3,3,3,3,0,0},
				{3,3,3,3,3,3,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL31: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,3,0,3,3,3,3,3},
				{3,3,0,3,0,0,0,0},
				{3,3,0,0,3,0,0,0},
				{3,3,0,0,0,3,0,0},
				{3,3,0,0,0,3,0,0},
				{3,3,0,0,0,0,3,0},
				{3,3,0,0,0,0,3,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL32: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,0,0,0,3,1,1},
				{3,3,0,0,0,3,1,1},
				{3,3,0,0,0,0,3,1},
				{3,3,0,0,0,0,3,1},
				{0,3,0,0,0,0,0,3},
				{0,0,0,0,0,0,0,3},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL33: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,3,3,0,3,1},
				{1,1,1,3,3,0,3,1},
				{1,1,1,3,3,0,3,1},
				{1,1,1,1,3,3,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{3,1,1,1,1,1,1,1},
				{3,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL34: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,3,2,2,2,2,2,2},
				{0,3,2,2,2,2,2,2},
				{0,0,3,2,2,2,2,2},
				{0,0,3,2,2,2,2,2},
				{0,0,3,2,2,2,2,2},
				{0,0,3,2,2,2,2,2},
				{0,0,3,2,2,2,2,2},
				{0,0,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL35: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,3,1,1,1,1,1,3},
				{0,3,1,1,1,1,1,3},
				{0,3,1,1,1,1,1,3},
				{0,3,1,1,1,1,1,3},
				{0,3,1,1,1,1,1,3},
				{0,3,1,1,1,1,1,3},
				{0,3,1,1,1,1,1,3},
				{0,3,2,2,2,2,2,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL36: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,3,3,0,0},
				{1,1,1,1,3,3,0,0},
				{1,1,1,3,3,0,0,0},
				{1,1,1,3,3,0,0,0},
				{1,1,3,3,0,0,0,0},
				{1,1,3,3,0,0,0,0},
				{1,3,3,0,0,0,0,0},
				{1,3,3,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL37: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,0,0,0,0,0,0},
				{3,3,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL38: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,0,3,3,3,3,3,0},
				{3,0,3,0,0,0,3,3},
				{3,0,3,0,0,0,0,0},
				{3,0,3,0,0,0,0,0},
				{3,0,3,0,0,0,0,0},
				{3,0,3,0,0,0,0,0},
				{3,0,3,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL39: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,0,3,1,1,1,1,1},
				{3,0,3,1,1,1,1,1},
				{3,0,3,1,1,1,1,1},
				{3,0,3,1,1,1,1,1},
				{3,0,3,1,1,1,1,1},
				{3,0,3,1,1,1,1,1},
				{3,0,3,1,1,1,1,1},
				{3,0,3,2,2,2,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL40: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,0,3,3,2,1,1},
				{0,0,0,0,0,3,1,1},
				{0,0,0,0,0,3,3,3},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,3,3,3,3,3},
				{0,0,0,3,2,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL41: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,3},
				{1,1,1,1,1,1,3,3},
				{1,1,1,1,1,3,3,0},
				{1,1,1,1,3,3,0,0},
				{1,1,1,1,3,3,0,0},
				{1,1,1,3,3,0,0,0},
				{1,1,1,3,3,0,0,0},
				{2,2,2,3,3,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL42: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,2,2,3,3,0,0,0},
				{2,2,2,3,3,0,0,0},
				{2,2,2,3,3,0,0,0},
				{2,2,2,2,3,3,0,0},
				{2,2,2,2,3,3,0,0},
				{2,2,2,2,2,3,3,0},
				{2,2,2,2,2,2,3,3},
				{3,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL43: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,3,2,2,2,2},
				{0,0,0,3,2,2,2,2},
				{0,0,0,3,3,3,3,3},
				{0,0,0,0,0,0,0,3},
				{0,0,0,0,0,0,0,3},
				{0,0,0,0,0,0,3,2},
				{0,0,0,0,0,3,2,2},
				{3,3,0,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL44: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,2,2,2,2,2,3,3},
				{2,2,2,2,2,2,3,3},
				{2,2,2,2,2,2,3,3},
				{2,2,2,2,2,2,3,3},
				{2,2,2,2,2,2,3,3},
				{2,2,2,2,2,3,3,0},
				{2,2,2,2,2,3,3,0},
				{3,3,3,3,3,3,3,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL45: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,3,3,3,0,0},
				{3,3,3,3,3,3,0,0},
				{3,3,3,3,3,0,0,0},
				{3,3,3,3,0,0,0,0},
				{3,3,3,0,0,0,0,0},
				{3,3,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL46: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,0,3,3,3,3,3},
				{3,3,0,3,3,3,3,3},
				{3,3,0,3,3,3,3,3},
				{3,3,0,3,3,3,3,3},
				{3,3,0,3,3,3,3,3},
				{3,3,0,3,3,3,3,3},
				{3,3,0,3,3,3,3,3},
				{3,3,0,3,3,3,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL47: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{3,3,3,3,3,3,3,3},
				{0,3,3,3,3,3,3,3},
				{0,0,3,3,3,3,3,3},
				{0,0,0,3,3,3,3,3},
				{0,0,0,0,0,3,3,3},
				{0,0,0,0,0,0,0,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL48: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,3,2,2,2,2,2,3},
				{0,3,2,2,2,2,2,3},
				{0,3,2,2,2,2,2,3},
				{0,3,2,2,2,2,2,3},
				{0,3,2,2,2,2,2,3},
				{0,3,2,2,2,2,2,3},
				{0,3,2,2,2,2,2,3},
				{0,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL49: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,3,1,3,3,0,0,0},
				{0,3,1,3,3,0,0,0},
				{0,3,1,1,3,3,0,0},
				{0,3,1,1,3,3,0,0},
				{0,3,1,1,1,3,3,0},
				{0,3,1,1,1,3,3,0},
				{0,3,1,1,1,1,3,3},
				{0,0,3,2,2,2,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL50: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,3,2,2,2,2,3},
				{0,0,0,3,2,2,2,3},
				{0,0,0,3,2,2,2,2},
				{0,0,0,0,3,2,2,2},
				{0,0,0,0,3,2,2,2},
				{0,0,0,0,0,3,2,2},
				{0,0,0,0,0,3,2,2},
				{0,0,0,0,0,0,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL51: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,0,3,3,3,3,3},
				{3,3,0,3,3,3,3,3},
				{3,3,0,3,3,3,3,3},
				{3,3,0,3,3,3,3,3},
				{3,3,0,3,3,3,3,3},
				{0,3,0,3,3,3,3,3},
				{0,3,0,3,3,3,3,3},
				{0,0,0,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL52: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,3,3,0,0,0,0,3},
				{1,3,3,0,0,0,3,1},
				{1,3,3,0,0,0,3,1},
				{1,3,3,0,0,0,3,1},
				{1,3,3,0,0,3,1,1},
				{1,3,3,0,0,3,1,1},
				{1,3,3,0,0,3,1,1},
				{2,3,3,0,0,3,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL53: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,3,3,0,0,3,2,2},
				{2,3,3,0,0,3,2,2},
				{2,3,3,0,0,3,2,2},
				{2,3,3,0,0,3,2,2},
				{2,3,3,0,0,3,2,2},
				{2,3,3,0,0,0,3,2},
				{2,3,3,0,0,0,3,2},
				{3,3,3,0,0,0,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL54: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,3,1,1,1,1},
				{0,0,0,3,1,1,1,1},
				{0,0,0,3,1,1,1,1},
				{0,0,0,3,1,1,1,1},
				{0,0,0,3,1,1,1,1},
				{0,0,0,3,1,1,1,1},
				{0,0,0,3,1,1,1,1},
				{0,0,0,3,2,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL55: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,0,0,3,2,2,2,2},
				{3,0,0,3,2,2,2,2},
				{3,3,0,3,2,2,2,2},
				{3,3,0,3,2,2,2,2},
				{2,3,0,3,2,2,2,2},
				{2,3,0,3,2,2,2,2},
				{2,3,0,3,2,2,2,2},
				{3,3,0,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL56: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,0,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL57: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,0,0,1,1,1},
				{1,1,1,0,0,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL58: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,2,1,1},
				{1,1,1,1,1,2,1,1},
				{1,1,1,1,1,2,1,1},
				{1,1,1,1,1,2,1,1},
				{1,1,1,1,2,2,2,1},
				{1,1,1,1,2,2,2,1},
				{1,1,1,1,2,2,2,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL59: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,2,2,2,2,2,1,1},
				{2,2,2,2,2,2,2,1},
				{2,2,2,2,2,2,2,1},
				{2,2,2,2,2,2,2,1},
				{1,2,2,2,2,2,1,1},
				{1,1,1,1,1,1,1,1},
				{1,2,2,2,2,2,1,1},
				{1,2,2,2,2,2,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL60: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,2,1,1,1,1},
				{1,1,2,2,2,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL61: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,2,2,2,1},
				{1,1,1,2,2,2,2,2},
				{1,1,1,2,2,2,2,2},
				{1,1,1,2,2,2,2,2},
				{1,1,1,2,2,2,2,2},
				{1,1,1,2,2,2,2,2},
				{1,2,2,2,2,2,2,2},
				{1,2,2,2,2,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL62: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,2,1,1,1},
				{1,1,1,2,1,2,1,1},
				{1,1,1,1,2,1,1,1},
				{1,1,1,1,2,1,1,1},
				{1,1,1,2,2,2,1,1},
				{1,1,1,2,2,2,1,1},
				{2,1,1,2,2,2,1,1},
				{2,2,2,2,2,2,2,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL63: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,3,1},
				{1,1,1,1,1,1,1,3},
				{1,1,1,1,1,1,1,3},
				{1,1,1,1,1,1,1,3},
				{1,1,1,1,1,1,1,3},
				{1,1,1,1,1,1,1,3},
				{1,1,1,1,1,1,1,3},
				{1,1,1,1,1,1,1,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL64: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,3,1,1,1,1,1,1},
				{3,1,1,1,1,1,1,1},
				{3,1,1,1,1,1,1,1},
				{3,1,1,1,1,1,1,1},
				{3,1,1,1,1,1,1,1},
				{3,1,1,1,1,1,1,1},
				{3,1,1,1,1,1,1,1},
				{3,1,1,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL65: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,3,1,1,1,1,1,1},
				{2,3,1,1,1,1,1,1},
				{3,3,1,1,1,1,1,1},
				{1,2,3,1,1,1,1,1},
				{1,2,2,3,1,1,1,1},
				{1,2,1,2,3,1,1,1},
				{2,2,1,2,2,3,1,1},
				{2,2,1,1,2,2,3,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL66: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,3},
				{1,1,1,1,1,1,3,0},
				{1,1,1,1,1,3,0,0},
				{1,1,1,1,3,0,0,2},
				{1,1,1,3,0,0,2,2},
				{1,1,3,0,0,2,2,2},
				{1,1,3,0,2,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL67: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,3,0},
				{1,1,1,1,1,1,3,0},
				{1,1,1,1,1,1,3,3},
				{1,1,1,1,1,3,0,2},
				{1,1,1,1,3,0,0,2},
				{1,1,1,3,0,0,2,1},
				{1,1,3,0,0,2,2,1},
				{1,3,0,0,2,2,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL68: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,2,2,2},
				{1,1,1,1,2,2,2,2},
				{1,1,1,1,2,2,2,2},
				{1,1,1,1,2,2,2,2},
				{1,1,1,1,2,2,2,2},
				{1,1,1,1,2,2,2,2},
				{1,1,1,1,2,2,2,2},
				{1,1,1,1,1,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL69: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,3,0,0,2,2,2,2},
				{1,3,0,0,2,2,2,2},
				{3,0,0,2,2,2,2,2},
				{3,0,0,2,2,2,2,2},
				{3,0,0,2,2,2,2,2},
				{3,0,0,2,2,2,2,2},
				{3,0,0,2,2,2,2,2},
				{3,0,0,2,2,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL70: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,3,0,2,2,2,2,2},
				{1,3,0,0,2,2,2,2},
				{1,1,3,0,2,2,2,2},
				{1,1,3,0,0,2,2,2},
				{1,1,1,3,0,0,0,2},
				{1,2,1,1,3,3,3,3},
				{2,2,2,2,1,3,0,0},
				{2,2,2,2,2,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL71: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,1,1,1,1,2,2,2},
				{2,1,1,1,1,1,2,2},
				{2,2,1,1,1,1,2,2},
				{2,2,2,1,1,1,1,2},
				{2,2,2,2,1,1,1,1},
				{3,3,3,3,3,3,3,3},
				{1,1,1,1,1,1,1,1},
				{3,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL72: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,2,2,1,1,2,3,1},
				{2,2,2,1,2,2,3,1},
				{2,2,1,1,2,3,1,1},
				{2,2,1,2,2,3,1,1},
				{2,1,2,2,3,1,1,1},
				{3,3,3,3,1,1,2,2},
				{3,1,3,1,1,1,2,2},
				{3,3,3,2,2,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL73: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,2,1,1,2,1,2,3},
				{2,2,1,1,2,2,1,2},
				{2,2,1,1,1,2,1,2},
				{2,1,1,1,1,2,2,1},
				{2,1,1,1,1,2,2,2},
				{2,1,1,1,1,2,2,2},
				{2,1,1,1,1,1,2,2},
				{2,1,1,1,1,1,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL74: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,2,2,2,1,1,1,1},
				{2,2,2,2,1,1,1,1},
				{2,2,2,2,1,1,1,2},
				{2,2,2,2,1,1,1,2},
				{2,2,2,2,2,1,1,2},
				{3,3,3,3,3,3,3,3},
				{1,1,2,2,2,3,2,3},
				{3,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL75: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{3,1,1,1,1,1,1,1},
				{2,3,1,1,1,1,1,1},
				{2,2,3,1,1,1,1,1},
				{1,2,2,3,1,1,1,1},
				{2,1,2,2,3,1,1,1},
				{2,1,1,2,2,3,1,1},
				{2,2,1,1,2,3,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL76: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,0,0,2,1,1,1,1},
				{0,0,2,2,1,1,1,2},
				{0,2,2,1,1,1,1,2},
				{2,2,2,1,1,1,1,2},
				{2,2,1,1,1,1,2,2},
				{2,2,1,1,1,1,2,2},
				{2,1,1,1,1,2,2,2},
				{2,1,1,1,1,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL77: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,2,1,1,2,2,3,1},
				{2,2,2,1,1,2,3,1},
				{2,2,2,2,1,2,2,3},
				{2,2,2,2,1,1,2,3},
				{2,2,2,2,1,1,2,3},
				{2,2,2,2,1,1,2,3},
				{2,2,2,2,1,1,2,3},
				{2,2,2,2,1,2,2,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL78: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,1,1,1,1,1,2,2},
				{2,1,1,1,1,1,1,2},
				{2,1,1,1,1,1,1,2},
				{2,2,1,1,1,1,1,2},
				{2,2,1,1,1,1,1,1},
				{2,2,2,1,1,1,1,1},
				{2,2,2,1,1,1,1,1},
				{2,2,2,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL79: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,3},
				{1,1,1,1,1,1,3,0},
				{1,1,1,1,1,1,3,0},
				{1,1,1,1,1,3,0,0},
				{1,1,1,1,1,3,0,0},
				{1,1,1,1,1,3,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL80: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,1,1},
				{1,1,1,1,1,1,1,1},
				{3,1,1,1,1,1,1,1},
				{0,3,1,1,1,1,1,1},
				{1,3,1,1,1,1,1,1},
				{1,1,3,1,1,1,1,1},
				{1,1,3,1,1,1,1,1},
				{1,2,3,1,1,1,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL81: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,1,1,3,0},
				{1,1,1,1,1,1,3,0},
				{1,2,1,1,1,1,3,3},
				{2,2,2,1,1,3,0,2},
				{1,2,1,1,3,0,0,2},
				{1,2,1,3,0,0,2,1},
				{1,2,3,0,0,2,2,1},
				{2,3,0,0,2,2,1,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL82: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,0,3,2,3,3,3,3},
				{3,0,3,3,3,3,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				{3,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL83: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,3,3},
				{3,0,0,0,0,0,3,0},
				{3,3,0,0,0,0,3,0},
				{0,3,3,0,0,0,3,0},
				{0,0,3,0,0,0,3,0},
				{0,0,3,3,0,0,3,0},
				{1,1,3,3,0,0,3,1},
				};
				drawPart(X, Y, part);
			} break;
			case TL84: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,3,3,0,0,3,1},
				{1,1,3,3,0,0,3,1},
				{1,1,3,3,0,0,3,1},
				{1,1,3,3,0,0,3,1},
				{1,1,3,3,0,0,3,1},
				{1,3,3,0,0,0,3,1},
				{1,3,3,0,0,0,3,1},
				{3,3,0,0,0,0,3,2},
				};
				drawPart(X, Y, part);
			} break;
			case TL85: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,0,0,0,0,0,3,2},
				{0,0,0,0,0,0,3,2},
				{0,0,0,0,0,0,3,2},
				{0,0,0,0,0,0,3,2},
				{0,0,0,0,0,0,3,2},
				{0,0,0,0,0,0,3,2},
				{0,0,0,0,0,0,3,2},
				{0,0,0,0,0,0,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL86: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,3,3},
				{0,0,0,0,0,0,3,3},
				{0,0,0,0,0,0,3,3},
				{0,0,0,0,0,0,3,3},
				{0,0,0,0,0,0,3,3},
				{0,0,0,0,0,0,3,3},
				{0,0,0,0,0,0,3,3},
				{0,0,0,0,0,0,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL87: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,0,0},
				{0,0,0,0,3,3,0,0},
				{0,0,0,0,3,3,0,0},
				{0,0,0,0,3,3,0,0},
				{0,0,0,0,3,3,0,0},
				{0,0,0,0,3,3,0,0},
				{1,1,1,1,3,3,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL88: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,3,3,0,0},
				{1,1,1,1,3,3,0,0},
				{1,1,1,1,3,3,0,0},
				{1,1,1,1,3,3,0,0},
				{1,1,1,1,3,3,0,0},
				{1,1,1,1,3,3,0,0},
				{1,1,1,1,3,3,0,0},
				{2,2,2,2,3,3,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL89: {
				char part[PART_SIZE][PART_SIZE] = {
				{2,2,2,2,3,3,0,0},
				{2,2,2,2,3,3,0,0},
				{2,2,2,2,3,3,0,0},
				{2,2,2,2,3,3,0,0},
				{2,2,2,2,3,3,0,0},
				{2,2,2,2,3,3,0,0},
				{2,2,2,2,3,3,0,0},
				{3,3,3,3,3,3,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL90: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{3,0,0,0,0,0,3,3},
				{3,0,0,0,0,0,3,3},
				{3,0,0,0,0,0,3,3},
				{3,0,0,0,0,0,3,3},
				{3,0,0,0,0,0,3,3},
				{3,1,1,1,1,1,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL91: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,1,1,1,1,1,3,3},
				{3,1,1,1,1,1,3,3},
				{3,1,1,1,1,1,3,3},
				{3,1,1,1,1,1,3,3},
				{3,1,1,1,1,1,3,3},
				{3,1,1,1,1,1,3,3},
				{3,1,1,1,1,1,3,3},
				{3,2,2,2,2,2,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL92: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,2,2,2,2,2,3,3},
				{3,2,2,2,2,2,3,3},
				{3,2,2,2,2,2,3,3},
				{3,2,2,2,2,2,3,3},
				{3,2,2,2,2,2,3,3},
				{3,2,2,2,2,2,3,3},
				{3,2,2,2,2,2,3,3},
				{3,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case TL93: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,3,3},
				{0,0,0,0,0,0,0,3},
				{0,0,0,0,0,0,0,3},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL94: {
				char part[PART_SIZE][PART_SIZE] = {
				{3,3,3,0,0,0,0,3},
				{3,3,3,0,0,0,0,3},
				{3,3,3,0,0,0,0,0},
				{3,3,3,0,0,0,0,0},
				{3,3,3,0,0,0,0,0},
				{3,3,3,0,0,0,0,0},
				{3,3,3,0,0,0,0,0},
				{3,3,3,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case TL95: {
				char part[PART_SIZE][PART_SIZE] = {
				{1,1,1,1,3,3,0,0},
				{1,1,1,1,3,3,0,0},
				{3,3,3,3,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				{2,2,2,2,2,2,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case ARRW: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,3,3,3,0,0,0,0},
				{0,3,3,3,3,0,0,0},
				{0,3,3,3,3,0,0,0},
				{0,3,3,3,0,0,0,0},
				{0,3,3,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case UNDR: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{3,0,3,0,3,0,3,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{2,2,2,2,2,2,2,2},
				};
				drawPart(X, Y, part);
			} break;
			case BCEX: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BCSH: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,0,3,3,0,0},
				{0,3,3,3,3,3,3,0},
				{0,0,3,0,3,3,0,0},
				{0,0,3,0,3,3,0,0},
				{0,3,3,3,3,3,3,0},
				{0,0,3,0,3,3,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BCDR: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,3,3,3,3,3,3,0},
				{0,3,0,3,3,0,0,0},
				{0,3,3,3,3,3,3,0},
				{0,0,0,3,3,0,3,0},
				{0,3,3,3,3,3,3,0},
				{0,0,0,3,3,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BCAN: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,3,0,0,0},
				{0,3,3,0,3,3,0,0},
				{0,0,3,3,3,0,3,3},
				{0,3,3,0,3,3,3,0},
				{3,3,0,0,0,3,3,0},
				{0,3,3,3,3,0,3,3},
				};
				drawPart(X, Y, part);
			} break;
			case BCQE: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,3,3,0,0,0,0},
				{0,3,0,0,3,0,0,0},
				{0,3,0,3,0,0,0,0},
				{0,0,3,0,0,3,0,0},
				{0,3,0,3,0,3,0,0},
				{3,0,0,0,3,0,0,0},
				{0,3,3,3,0,3,3,0},
				};
				drawPart(X, Y, part);
			} break;
			case BCCO: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BCSM: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,0,3,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BCPU: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,3,3,3,3,3,3,0},
				{0,3,3,3,3,3,3,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,3,3,0,0,0},
				{0,0,0,0,0,0,0,0},
				};
				drawPart(X, Y, part);
			} break;
			case BCUN: {
				char part[PART_SIZE][PART_SIZE] = {
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{3,3,3,3,3,3,3,3},
				};
				drawPart(X, Y, part);
			} break;

			default:
				DrawBox(X, Y, X + PART_SIZE * ZOOM_RATE, Y + PART_SIZE * ZOOM_RATE, 0xFF0000, TRUE);
				break;
			}
		}
}
void drawNumbers(int x, int y, int number, int length)
{
	length -= 1;
	bool drawFlag = 0;
	SetStagePart(x + length, y, BC_0);
	for (int i = 0, j = (int)pow(10, length); i <= length || j < 0; i++, j /= 10) {
		if (number / j >= 1) SetStagePart(x + i, y, BC_0 + (int)number / j), drawFlag = 1;
		else if (drawFlag) SetStagePart(x + i, y, BC_0 + (int)number / j);
		int _number = (int)number / j;
		number -= _number * j;
	}
}
bool DrawStringB(char x, char y, const char string[], bool drawFlag)
{
	bool isdraw = true;
	while (*string != '\0') {
		if (*string == ' ') SetStagePart(x, y, NONE, drawFlag);
		else if (*string == '-') SetStagePart(x, y, BCHY, drawFlag);
		else if (*string == '!') SetStagePart(x, y, BCEX, drawFlag);
		else if (*string == '#') SetStagePart(x, y, BCSH, drawFlag);
		else if (*string == '$') SetStagePart(x, y, BCDR, drawFlag);
		else if (*string == '&') SetStagePart(x, y, BCAN, drawFlag);
		else if (*string == '.') SetStagePart(x, y, BCPR, drawFlag);
		else if (*string == ',') SetStagePart(x, y, COMA, drawFlag);
		else if (*string == '\"') SetStagePart(x, y, QOTE, drawFlag);
		else if (*string == ':') SetStagePart(x, y, BCCO, drawFlag);
		else if (*string == ';') SetStagePart(x, y, BCSM, drawFlag);
		else if (*string == '+') SetStagePart(x, y, BCPU, drawFlag);
		else if (*string == '_') SetStagePart(x, y, BCUN, drawFlag);

		else if (*string <= '9' && *string >= '0') SetStagePart(x, y, BC_0 + (*string - 48), drawFlag);
		else if (*string >= 'A' && *string <= 'Z') SetStagePart(x, y, BC_A + (*string - 65), drawFlag);
		else if (*string >= 'a' && *string <= 'z') SetStagePart(x, y, BC_A + (*string - 97), drawFlag);
		else isdraw = false;
		x++;
		string++;
	}
	return !isdraw;
}
bool DrawStringG(char x, char y, const char string[], bool drawFlag)
{
	bool isdraw = true;
	while (*string != '\0') {
		if (*string == ' ') SetStagePart(x, y, NONE, drawFlag);
		if (*string == '-') SetStagePart(x, y, GCHY, drawFlag);
		else if (*string <= '9' && *string >= '0') SetStagePart(x, y, GC_0 + (*string - 48), drawFlag);
		else if (*string >= 'A' && *string <= 'Z') SetStagePart(x, y, GC_A + (*string - 65), drawFlag);
		else if (*string >= 'a' && *string <= 'z') SetStagePart(x, y, GC_A + (*string - 97), drawFlag);
		else isdraw = false;
		x++;
		string++;
	}
	return !isdraw;
}