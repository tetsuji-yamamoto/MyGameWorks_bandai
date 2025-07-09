#include "mouse.h"

// グローバル変数宣言
LPDIRECTINPUT8 g_mouseInput;
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;
DIMOUSESTATE g_mouse;			// マウス情報
DIMOUSESTATE g_mouseMove;		// マウスの移動量情報
DIMOUSESTATE g_mouseOld;		// 古いマウス情報
DIMOUSESTATE g_mouseTrigger;	// マウストリガー情報
DIMOUSESTATE g_mouseRelease;	// マウスリリース情報

//******************************************
// マウスの初期化処理
//******************************************
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_mouseInput, NULL)))
	{
		return E_FAIL;
	}

	// 入力デバイス(マウス)の生成
	if (FAILED(g_mouseInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを生成
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//マウスへのアクセス権を獲得
	g_pDevMouse->Acquire();

	return S_OK;
}

//******************************************
// マウスの終了処理
//******************************************
void UninitMouse(void)
{
	//入力デバイスキーボードの破棄
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire();
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}
	//DirectInputオブジェクトの破棄
	if (g_mouseInput != NULL)
	{
		g_mouseInput->Release();
		g_mouseInput = NULL;
	}
}

//******************************************
// マウスの更新処理
//******************************************
void UpdateMouse(void)
{
	// 古いマウス情報を更新
	g_mouseOld = g_mouse;

	// 入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE), &g_mouse)))
	{
		for (int nCntButn = 0; nCntButn < MOUSEBUTTON_MAX; nCntButn++)
		{
			g_mouseTrigger.rgbButtons[nCntButn] = g_mouse.rgbButtons[nCntButn] & ~g_mouseOld.rgbButtons[nCntButn];
			g_mouseRelease.rgbButtons[nCntButn] = g_mouseOld.rgbButtons[nCntButn] & ~g_mouse.rgbButtons[nCntButn];
		}
	}
	else
	{
		g_pDevMouse->Acquire();// マウスのアクセス権を獲得
	}

	// マウス座標を取得する
	POINT p;
	GetCursorPos(&p);

	// スクリーン座標をクライアント座標に変換する
	if (ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &p))
	{
		g_mouse.lX = p.x;
		g_mouse.lY = p.y;

		// 移動量を計算
		g_mouseMove.lX = g_mouse.lX - g_mouseOld.lX;
		g_mouseMove.lY = g_mouse.lY - g_mouseOld.lY;
	}
}

//******************************************
// マウスのボタンを押している間
//******************************************
bool MouseButtonRepeat(MOUSEBUTTON mouseButtton)
{
	return g_mouse.rgbButtons[mouseButtton] & (0x80) ? true : false;
}

//******************************************
// マウスのボタンを押した瞬間
//******************************************
bool MouseButtonTrigger(MOUSEBUTTON mouseButtton)
{
	return g_mouseTrigger.rgbButtons[mouseButtton] & (0x80) ? true : false;
}

//******************************************
// マウスのボタンを離した瞬間
//******************************************
bool MouseButtonRelease(MOUSEBUTTON mouseButtton)
{
	return g_mouseRelease.rgbButtons[mouseButtton] & (0x80) ? true : false;
}

//******************************************
// マウスの移動量を取得
//******************************************
D3DXVECTOR3 GetMouseVelocity(void)
{
	return D3DXVECTOR3((float)g_mouseMove.lX, (float)g_mouseMove.lY, (float)g_mouseMove.lZ);
}

//******************************************
// マウスの位置を取得
//******************************************
D3DXVECTOR3 GetMousePosition(void)
{
	return D3DXVECTOR3((float)g_mouse.lX, (float)g_mouse.lY, (float)g_mouse.lZ);
}