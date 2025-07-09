#include "joypad.h"

XINPUT_STATE g_joyKeyState;			// ジョイパッドの情報
XINPUT_STATE g_JoyKeyStateOld;		// ジョイパッドの古い情報
XINPUT_STATE g_joyKeyStateTrigger;	// ジョイパッドのトリガー情報
XINPUT_STATE g_joyKeyStateRepeat;	// ジョイパッドのリピート情報
XINPUT_STATE g_joyKeyStateRelease;	// ジョイパッドのリリース情報

//***********************************************
// ジョイパッドの初期化処理
//***********************************************
HRESULT InitJoypad(void)
{
	// メモリのクリア
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	// Xinputのステートを設定(有効にする)
	XInputEnable(true);

	return S_OK;
}

//***********************************************
//ジョイパッドの終了処理
//***********************************************
void UninitJoypad(void)
{
	// Xinputのステートを設定(無効にする)
	XInputEnable(false);
}

//***********************************************
// ジョイパッドの更新処理
//***********************************************
void UpdataJoypad(void)
{
	int nCntJoy;

	XINPUT_STATE joyKeyState;	// ジョイパッドの入力処理

	// ひとつ前のキーボードプレス情報を保存
	g_JoyKeyStateOld = g_joyKeyState;

	// ジョイパッドの状態を取得
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		g_joyKeyState = joyKeyState;	// ジョイパッドのプレス情報を保存

		// 情報を渡して
		WORD Button = g_joyKeyState.Gamepad.wButtons;		// 今
		WORD OldButton = g_JoyKeyStateOld.Gamepad.wButtons;	// 昔

		WORD LT = g_joyKeyState.Gamepad.bLeftTrigger;// 今
		WORD RT = g_joyKeyState.Gamepad.bRightTrigger;// 今
		WORD LTOld = g_JoyKeyStateOld.Gamepad.bLeftTrigger;	// 昔
		WORD RTOld = g_JoyKeyStateOld.Gamepad.bRightTrigger;	// 昔

		// 計算結果を代入
		g_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;// 押したとき
		g_joyKeyStateRelease.Gamepad.wButtons = OldButton & ~Button;// 離したとき
		g_joyKeyStateRepeat.Gamepad.wButtons = Button;				// 押している間

		g_joyKeyStateTrigger.Gamepad.bLeftTrigger = LT & ~LTOld;	// 押したとき
		g_joyKeyStateRelease.Gamepad.bLeftTrigger = LTOld & ~LT;	// 離したとき
		g_joyKeyStateRepeat.Gamepad.bLeftTrigger = LT;				// 押している間


		g_joyKeyStateTrigger.Gamepad.bRightTrigger = RT & ~RTOld;	// 押したとき
		g_joyKeyStateRelease.Gamepad.bRightTrigger = RTOld & ~RT;	// 離したとき
		g_joyKeyStateRepeat.Gamepad.bRightTrigger = RT;				// 押している間
	}
}

//***********************************************
//ジョイパッドボタンを押しているとき
//***********************************************
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//***********************************************
//ジョイパッドボタンを押した瞬間
//***********************************************
bool GetJoypadTrigger(JOYKEY key)
{
	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//***********************************************
//ジョイパッドボタンを離したとき
//***********************************************
bool GetJoypadRelease(JOYKEY key)
{
	return (g_joyKeyStateRelease.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//***********************************************
// ジョイパッドボタンを押している間
//***********************************************
bool GetJoypadRepeat(JOYKEY key)
{
	return (g_joyKeyStateRepeat.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//***********************************************
// LT 押したとき
//***********************************************
bool GetLTTrigger(void)
{
	return (g_joyKeyStateTrigger.Gamepad.bLeftTrigger ? true : false);
}

//***********************************************
// LT 離したとき
//***********************************************
bool GetLTRelease(void)
{
	return (g_joyKeyStateRelease.Gamepad.bLeftTrigger ? true : false);
}

//***********************************************
// LT 押している間
//***********************************************
bool GetLTRepeat(void)
{
	return (g_joyKeyStateRepeat.Gamepad.bLeftTrigger ? true : false);
}

//***********************************************
// LR 押したとき
//***********************************************
bool GetRTTrigger(void)
{
	return (g_joyKeyStateTrigger.Gamepad.bRightTrigger ? true : false);
}

//***********************************************
// LR 離したとき
//***********************************************
bool GetRTRelease(void)
{
	return (g_joyKeyStateRelease.Gamepad.bRightTrigger ? true : false);
}

//***********************************************
// LR 押している間
//***********************************************
bool GetRTRepeat(void)
{
	return (g_joyKeyStateRepeat.Gamepad.bRightTrigger ? true : false);
}

//********************************************************************
// Lスティック処理
//********************************************************************
bool GetJoyStickL(void)
{
	bool joykey = false;
	//真ん中じゃなかったら
	if (g_joyKeyState.Gamepad.sThumbLX >= 5000 ||
		g_joyKeyState.Gamepad.sThumbLX <= -5000 ||
		g_joyKeyState.Gamepad.sThumbLY >= 5000 ||
		g_joyKeyState.Gamepad.sThumbLY <= -5000)
	{
		joykey = true;
	}
	return joykey;
}

//********************************************************************
// Rスティック処理
//********************************************************************
bool GetJoyStickR(void)
{
	bool joykey = false;
	//真ん中じゃなかったら
	if (g_joyKeyState.Gamepad.sThumbRX >= 5000 ||
		g_joyKeyState.Gamepad.sThumbRX <= -5000 ||
		g_joyKeyState.Gamepad.sThumbRY >= 5000 ||
		g_joyKeyState.Gamepad.sThumbRY <= -5000)
	{
		joykey = true;
	}
	return joykey;
}

//********************************************************************
// ジョイパッド情報の取得
//********************************************************************
XINPUT_STATE* GetJoypadState(void)
{
	return &g_joyKeyState;
}