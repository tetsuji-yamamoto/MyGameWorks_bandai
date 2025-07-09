#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "main.h"

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UpdataKeyboard(void);
void UninitKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeyboardTrigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);
#endif // !_KEYBOARD_H_