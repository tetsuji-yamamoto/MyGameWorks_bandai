#ifndef _MOUSE_H
#define _MOUSE_H

#include "main.h"

// マウスボタンの種類列挙
typedef enum
{
	MOUSEBUTTON_LEFT = 0,	// 左クリック
	MOUSEBUTTON_RIGHT,		// 模擬クリック
	MOUSEBUTTON_CENTER,		// ホイールボタン
	MOUSEBUTTON_MAX
}MOUSEBUTTON;

//プロトタイプ宣言
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void UpdateMouse(void);
void UninitMouse(void);
bool MouseButtonRepeat(MOUSEBUTTON mouseButtton);
bool MouseButtonTrigger(MOUSEBUTTON mouseButtton);
bool MouseButtonRelease(MOUSEBUTTON mouseButtton);
D3DXVECTOR3 GetMouseVelocity(void);
D3DXVECTOR3 GetMousePosition(void);
#endif // !_MOUSE_H