//****************************************************************************
// 
// 入力処理
// Author tetuji yamamoto
// 
//****************************************************************************
#include "input.h"

// 静的メンバー変数宣言
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//---------------------------------------------------------------------------
// 入力

//****************************************************************************
// 入力コンストラクタ
//****************************************************************************
CInput::CInput()
{
	m_pDevice = NULL;
}

//****************************************************************************
// 入力デストラクタ
//****************************************************************************
CInput::~CInput()
{
}

//****************************************************************************
// 入力初期化処理
//****************************************************************************
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{// ヌルであれば
		// DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			MessageBox(NULL, " CInput::Init() > if (FAILED(DirectInput8Create()) > 失敗", "Error", MB_OK);
			return E_FAIL;
		}
	}

	return S_OK;
}

//****************************************************************************
// 入力終了処理
//****************************************************************************
void CInput::Uninit(void)
{
	// DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//****************************************************************************
// 入力更新処理
//****************************************************************************
void CInput::Update(void)
{

}

//---------------------------------------------------------------------------
// キーボード

//****************************************************************************
// キーボードコンストラクタ
//****************************************************************************
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));
	memset(&m_aOldState[0], 0, sizeof(m_aOldState));
}

//****************************************************************************
// キーボードデストラクタ
//****************************************************************************
CInputKeyboard::~CInputKeyboard()
{
}

//****************************************************************************
// キーボード初期化処理
//****************************************************************************
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// 入力デバイス（キーボード）の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを生成
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//****************************************************************************
// キーボード終了処理
//****************************************************************************
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();

	// 入力デバイスキーボードの破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//****************************************************************************
// キーボード更新処理
//****************************************************************************
void CInputKeyboard::Update(void)
{
	CInput::Update();

	BYTE aKeyState[NUM_KEY_MAX];	// キーボードの入力処理
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aOldState[nCntKey] = m_aKeyState[nCntKey];	// ひとつ前のキーボードプレス情報を保存
	}

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	// きーぼーどのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();	// キーボードへのアクセス権を獲得
	}
}

//---------------------------------------------------------------------------
// マウス

//****************************************************************************
// マウスコンストラクタ
//****************************************************************************
CInputMouse::CInputMouse()
{
	memset(&m_mouse,0,sizeof(DIMOUSESTATE));
	memset(&m_mouseMove, 0, sizeof(DIMOUSESTATE));
	memset(&m_mouseOld, 0, sizeof(DIMOUSESTATE));
	memset(&m_mouseTrigger, 0, sizeof(DIMOUSESTATE));
	memset(&m_mouseRelease, 0, sizeof(DIMOUSESTATE));
}

//****************************************************************************
// マウスデストラクタ
//****************************************************************************
CInputMouse::~CInputMouse()
{
}

//****************************************************************************
// マウス初期化処理
//****************************************************************************
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// 入力デバイス(マウス)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを生成
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//マウスへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//****************************************************************************
// マウス終了処理
//****************************************************************************
void CInputMouse::Uninit(void)
{
	CInput::Uninit();

	//入力デバイスキーボードの破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//****************************************************************************
// マウス更新処理
//****************************************************************************
void CInputMouse::Update(void)
{
	CInput::Update();

	// 古いマウス情報を更新
	m_mouseOld = m_mouse;

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouse)))
	{
		for (int nCntButn = 0; nCntButn < MOUSEBUTTON_MAX; nCntButn++)
		{
			m_mouseTrigger.rgbButtons[nCntButn] = m_mouse.rgbButtons[nCntButn] & ~m_mouseOld.rgbButtons[nCntButn];
			m_mouseRelease.rgbButtons[nCntButn] = m_mouseOld.rgbButtons[nCntButn] & ~m_mouse.rgbButtons[nCntButn];
		}
	}
	else
	{
		m_pDevice->Acquire();// マウスのアクセス権を獲得
	}

	// マウス座標を取得する
	POINT p;
	GetCursorPos(&p);

	// スクリーン座標をクライアント座標に変換する
	if (ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &p))
	{
		m_mouse.lX = p.x;
		m_mouse.lY = p.y;

		// 移動量を計算
		m_mouseMove.lX = m_mouse.lX - m_mouseOld.lX;
		m_mouseMove.lY = m_mouse.lY - m_mouseOld.lY;
	}
}

//---------------------------------------------------------------------------
// ジョイパッド

//****************************************************************************
// ジョイパッドコンストラクタ
//****************************************************************************
CInputJoypad::CInputJoypad()
{
	memset(&m_joyKeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_JoyKeyStateOld, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyStateRelease, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyStateRepeat, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyStateTrigger,0,sizeof(XINPUT_STATE));
}

//****************************************************************************
// ジョイパッドデストラクタ
//****************************************************************************
CInputJoypad::~CInputJoypad()
{
}

//****************************************************************************
// ジョイパッド初期化処理
//****************************************************************************
HRESULT CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// メモリのクリア
	memset(&m_joyKeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_JoyKeyStateOld, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyStateRelease, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyStateRepeat, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	// Xinputのステートを設定(有効にする)
	XInputEnable(true);

	return S_OK;
}

//****************************************************************************
// ジョイパッド終了処理
//****************************************************************************
void CInputJoypad::Uninit(void)
{
	CInput::Uninit();

	// Xinputのステートを設定(無効にする)
	XInputEnable(false);

	//入力デバイスジョイパッドの破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//****************************************************************************
// ジョイパッド更新処理
//****************************************************************************
void CInputJoypad::Update(void)
{
	CInput::Update();

	XINPUT_STATE joyKeyState;	// ジョイパッドの入力処理

	// ひとつ前のジョイパッド情報を保存
	m_JoyKeyStateOld = m_joyKeyState;

	// ジョイパッドの状態を取得
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		m_joyKeyState = joyKeyState;	// ジョイパッドのプレス情報を保存

		// 情報を渡して
		WORD Button = m_joyKeyState.Gamepad.wButtons;		// 今
		WORD OldButton = m_JoyKeyStateOld.Gamepad.wButtons;	// 昔

		WORD LT = (WORD)m_joyKeyState.Gamepad.bLeftTrigger;		// 今
		WORD RT = (WORD)m_joyKeyState.Gamepad.bRightTrigger;	// 今
		WORD LTOld = m_JoyKeyStateOld.Gamepad.bLeftTrigger;		// 昔
		WORD RTOld = m_JoyKeyStateOld.Gamepad.bRightTrigger;	// 昔

		// 計算結果を代入
		m_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;// 押したとき
		m_joyKeyStateRelease.Gamepad.wButtons = OldButton & ~Button;// 離したとき
		m_joyKeyStateRepeat.Gamepad.wButtons = Button;				// 押している間

		m_joyKeyStateTrigger.Gamepad.bLeftTrigger = LT & ~LTOld;	// 押したとき
		m_joyKeyStateRelease.Gamepad.bLeftTrigger = LTOld & ~LT;	// 離したとき
		m_joyKeyStateRepeat.Gamepad.bLeftTrigger = (BYTE)LT;				// 押している間


		m_joyKeyStateTrigger.Gamepad.bRightTrigger = RT & ~RTOld;	// 押したとき
		m_joyKeyStateRelease.Gamepad.bRightTrigger = RTOld & ~RT;	// 離したとき
		m_joyKeyStateRepeat.Gamepad.bRightTrigger = (BYTE)RT;				// 押している間
	}
}

//********************************************************************
// Lスティック処理
//********************************************************************
bool CInputJoypad::GetLStick()
{
	bool joykey = false;
	//真ん中じゃなかったら
	if (m_joyKeyState.Gamepad.sThumbLX >= JOYPAD_STICK_DEADZONE ||
		m_joyKeyState.Gamepad.sThumbLX <= -JOYPAD_STICK_DEADZONE ||
		m_joyKeyState.Gamepad.sThumbLY >= JOYPAD_STICK_DEADZONE ||
		m_joyKeyState.Gamepad.sThumbLY <= -JOYPAD_STICK_DEADZONE)
	{
		joykey = true;
	}
	return joykey;
}

//********************************************************************
// Rスティック処理
//********************************************************************
bool CInputJoypad::GetRStick(void)
{
	bool joykey = false;
	//真ん中じゃなかったら
	if (m_joyKeyState.Gamepad.sThumbRX >= JOYPAD_STICK_DEADZONE ||
		m_joyKeyState.Gamepad.sThumbRX <= -JOYPAD_STICK_DEADZONE ||
		m_joyKeyState.Gamepad.sThumbRY >= JOYPAD_STICK_DEADZONE ||
		m_joyKeyState.Gamepad.sThumbRY <= -JOYPAD_STICK_DEADZONE)
	{
		joykey = true;
	}
	return joykey;
}