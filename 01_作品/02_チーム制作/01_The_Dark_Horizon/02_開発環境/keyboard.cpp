#include "mouse.h"

//マクロ定義
#define NUM_KEY_MAX (256) //キーの最大数

//グローバル変数宣言
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX];	//キーボードのプレス情報
BYTE g_aOldState[NUM_KEY_MAX];	//キーボードの古いプレス情報

//***********************************************
// キーボードの初期化処理
//***********************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	// 入力デバイス（キーボード）の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを生成
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//***********************************************
// キーボードの終了処理
//***********************************************
void UninitKeyboard(void)
{
	// 入力デバイスキーボードの破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//***********************************************
// キーボードの更新処理
//***********************************************
void UpdataKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	// キーボードの入力処理
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey];	// ひとつ前のキーボードプレス情報を保存
	}

	// 入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];	// きーぼーどのプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();	// キーボードへのアクセス権を獲得
	}
}

//***********************************************
// キーボードを押している間
//***********************************************
bool GetKeyboardPress(int nKey)//押してる間
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//***********************************************
// キーボードを押したとき
//***********************************************
bool KeyboardTrigger(int nKey)//押したとき
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//***********************************************
// キーボードを離したとき
//***********************************************
bool KeyboardRelease(int nKey)//離した時
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//***********************************************
// キーボードを押している間
//***********************************************
bool KeyboardRepeat(int nKey)//押されている間
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && (g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}