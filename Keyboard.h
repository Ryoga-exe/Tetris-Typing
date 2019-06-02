#pragma once
#define M_LEFT  0
#define M_RIGHT 1

int KeyUpdate(int drawKeyCodeFlag = 0);

int Keyboard_Get(int KeyCode);

int Mouse_Get(int MFlag);

void Keyboard_Set(int KeyCode, int Num);

// int GetKeyCode(const char* Char);