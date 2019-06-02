#include "DxLib.h"

static int m_Key[256], m_Mouse[2];

int KeyUpdate(int drawKeyCodeFlag) {
	char tmpKey[256];
	int counting = 0;
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++)
		if (tmpKey[i] != 0) {
			m_Key[i]++;
			if (drawKeyCodeFlag) {
				DrawFormatString(0, 16 * counting, 0xffffff, "%d", i);
				counting++;
			}
		}
		else m_Key[i] = 0;
	if (GetMouseInput() & MOUSE_INPUT_LEFT) m_Mouse[0]++;
	else m_Mouse[0] = 0;
	if (GetMouseInput() & MOUSE_INPUT_RIGHT) m_Mouse[1]++;
	else m_Mouse[1] = 0;
	return 0;
}

int Keyboard_Get(int KeyCode) {
	return m_Key[KeyCode];
}

int Mouse_Get(int MFlag) {
	return m_Mouse[MFlag];
}

void Keyboard_Set(int KeyCode, int Num) {
	m_Key[KeyCode] = Num;
}

/*
int GetKeyCode(const char* Char) {
	switch (*Char){
	case 'a':
	case 'A': return KEY_INPUT_A;
	default:
		break;
	}
	return 0;
}
*/