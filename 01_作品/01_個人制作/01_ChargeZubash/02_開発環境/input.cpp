#include "input.h"

//マクロ定義
#define NUM_KEY_MAX (256) //キーの最大数
//グローバル変数宣言
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX];	//キーボードのプレス情報
BYTE g_aOldState[NUM_KEY_MAX];	//キーボードの古いプレス情報
XINPUT_STATE g_joyKeyState;		//ジョイパッドのプレス情報
XINPUT_STATE g_aOldJoyKeyState;	//ジョイパッドの古いプレス情報
XINPUT_STATE g_joyKeyStateTrigger;//ジョイパッドのトリガー情報
XINPUT_STATE g_joyKeyStateRepeat;//ジョイパッドのリピート情報
XINPUT_STATE g_joyKeyStateRelease;//ジョイパッドのリリース情報
//----------------------
//キーボードの初期化処理
//----------------------
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス（キーボード）の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを生成
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();


	//メモリのクリア
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	return S_OK;
}
//------------------------------
//キーボードの終了処理
//------------------------------
void UninitKeyboard(void)
{
	//入力デバイスキーボードの破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}

	//Xinputのステート設定（無効にする）
	XInputEnable(false);
}
//------------------------------
//キーボードの更新処理
//------------------------------
void UpdataKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//キーボードの入力処理
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey];//ひとつ前のキーボードプレス情報を保存
	}

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//きーぼーどのプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();//キーボードへのアクセス権を獲得
	}
}
//------------------------------
//キーボードのブレス情報を取得
//-----------------------------
bool GetKeyboardPress(int nKey)//押してる間
{
	return (g_aKeyState[nKey] & 0x80) ? true: false;
}
bool KeyboardTrigger(int nKey)//押したとき
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
bool KeyboardRelease(int nKey)//離した時
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
bool KeyboardRepeat(int nKey)//押されている間
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && (g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//----------------------
//ジョイパッドの初期化処理
//----------------------
HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//Xinputのステートを設定(有効にする)
	XInputEnable(true);

	STICK_ANGLE pStick;
	pStick.nStickLX = 0;
	pStick.nStickLY = 0;

	return S_OK;
}
//----------------------
//ジョイパッドの終了処理
//----------------------
void UninitJoypad(void)
{
	//Xinputのステートを設定(無効にする)
	XInputEnable(false);
}
//----------------------
//ジョイパッドの更新処理
//----------------------
void UpdataJoypad(void)
{
	int nCntJoy;

	XINPUT_STATE joyKeyState;//ジョイパッドの入力処理

	//ひとつ前のキーボードプレス情報を保存
	g_aOldJoyKeyState = g_joyKeyState;

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		g_joyKeyState = joyKeyState;//ジョイパッドのプレス情報を保存

		//情報を渡して
		WORD Button = g_joyKeyState.Gamepad.wButtons;
		WORD OldButton = g_aOldJoyKeyState.Gamepad.wButtons;

		//計算結果を代入
		g_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;
		g_joyKeyStateRelease.Gamepad.wButtons = OldButton & ~Button;
		g_joyKeyStateRepeat.Gamepad.wButtons = Button;
	}

	//ジョイパッドの状態を取得
	/*if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		WORD Button = g_joyKeyState.Gamepad.wButtons;
		WORD OldButton = g_joyKeyState.Gamepad.wButtons;
		
		g_joyKeyState.Gamepad.wButtons = Button & ~OldButton;
	}*/
}
//===============================
//ジョイパッドボタンを取得
//===============================
//ボタンの処理-----------------------------------------------------------------------------------------------------------------------------------------
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//押したとき
bool GetJoypadTrigger(JOYKEY key)
{	
	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;

	//return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//離したとき
bool GetJoypadRelease(JOYKEY key)
{
	return (g_joyKeyStateRelease.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//押している間
bool GetJoypadRepeat(JOYKEY key)
{
	return (g_joyKeyStateRepeat.Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//===================================
//L2,R2処理
//===================================
bool GetJoyTrigger(JOYKEY key)
{
	bool JoyStick = false;
	if (key == JOYKEY_L2)
	{
		return (g_joyKeyState.Gamepad.bLeftTrigger) ? true : false;
	}
	else if (key == JOYKEY_R2)
	{
		return (g_joyKeyState.Gamepad.bRightTrigger) ? true : false;
	}
	return JoyStick;

}
bool GetJoyTriggerTrigger(JOYKEY key)//押したとき
{
	bool JoyStick = false;
	if (key == JOYKEY_L2)
	{	
		if ((g_joyKeyState.Gamepad.bLeftTrigger > 0) && !(g_aOldJoyKeyState.Gamepad.bLeftTrigger > 0))
		{
			JoyStick = true;
		}
	}
	else if (key == JOYKEY_R2)
	{
		if ((g_joyKeyState.Gamepad.bRightTrigger > 0) && !(g_aOldJoyKeyState.Gamepad.bRightTrigger > 0))
		{
			JoyStick = true;
		}
	}
	return JoyStick;
}
bool GetJoyTriggerRelease(JOYKEY key)//離したとき
{
	bool JoyStick = false;
	if (key == JOYKEY_L2)
	{
		if ((g_aOldJoyKeyState.Gamepad.bLeftTrigger > 0) && !(g_joyKeyState.Gamepad.bLeftTrigger > 0))
		{
			JoyStick = true;
		}
	}
	else if (key == JOYKEY_R2)
	{
		if ((g_aOldJoyKeyState.Gamepad.bRightTrigger > 0) && !(g_joyKeyState.Gamepad.bRightTrigger > 0))
		{
			JoyStick = true;
		}
	}
	return JoyStick;
}
bool GetJoyTriggerRepeat(JOYKEY key)//押している間
{
	bool JoyStick = false;
	if (key == JOYKEY_L2)
	{
		if ((g_aOldJoyKeyState.Gamepad.bLeftTrigger > 0) && (g_joyKeyState.Gamepad.bLeftTrigger > 0))
		{
			JoyStick = true;
		}
	}
	else if (key == JOYKEY_R2)
	{
		if ((g_aOldJoyKeyState.Gamepad.bRightTrigger > 0) && (g_joyKeyState.Gamepad.bRightTrigger > 0))
		{
			JoyStick = true;
		}
	}
	return JoyStick;
}

//------------------------
//スティック処理
//------------------------
bool GetJoyStick()
{
	bool joykey = false;
	//真ん中じゃなかったら
	if (g_joyKeyState.Gamepad.sThumbLX >= 1000 ||
		g_joyKeyState.Gamepad.sThumbLX <= -1000||
		g_joyKeyState.Gamepad.sThumbLY >= 1000 ||
		g_joyKeyState.Gamepad.sThumbLY <= -1000 )
	{
		joykey = true;
	}
	return joykey;
}

//------------------------
//スティック情報の取得
//------------------------
XINPUT_STATE* GetJoySticAngle(void)
{
	return &g_joyKeyState;
}