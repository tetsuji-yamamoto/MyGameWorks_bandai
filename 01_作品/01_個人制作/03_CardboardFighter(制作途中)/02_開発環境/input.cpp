//****************************************************************************
// 
// ���͏���
// Author tetuji yamamoto
// 
//****************************************************************************
#include "input.h"

// �ÓI�����o�[�ϐ��錾
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//---------------------------------------------------------------------------
// ����

//****************************************************************************
// ���̓R���X�g���N�^
//****************************************************************************
CInput::CInput()
{
	m_pDevice = NULL;
}

//****************************************************************************
// ���̓f�X�g���N�^
//****************************************************************************
CInput::~CInput()
{
}

//****************************************************************************
// ���͏���������
//****************************************************************************
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{// �k���ł����
		// DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			MessageBox(NULL, " CInput::Init() > if (FAILED(DirectInput8Create()) > ���s", "Error", MB_OK);
			return E_FAIL;
		}
	}

	return S_OK;
}

//****************************************************************************
// ���͏I������
//****************************************************************************
void CInput::Uninit(void)
{
	// DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//****************************************************************************
// ���͍X�V����
//****************************************************************************
void CInput::Update(void)
{

}

//---------------------------------------------------------------------------
// �L�[�{�[�h

//****************************************************************************
// �L�[�{�[�h�R���X�g���N�^
//****************************************************************************
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));
	memset(&m_aOldState[0], 0, sizeof(m_aOldState));
}

//****************************************************************************
// �L�[�{�[�h�f�X�g���N�^
//****************************************************************************
CInputKeyboard::~CInputKeyboard()
{
}

//****************************************************************************
// �L�[�{�[�h����������
//****************************************************************************
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�𐶐�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//****************************************************************************
// �L�[�{�[�h�I������
//****************************************************************************
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();

	// ���̓f�o�C�X�L�[�{�[�h�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//****************************************************************************
// �L�[�{�[�h�X�V����
//****************************************************************************
void CInputKeyboard::Update(void)
{
	CInput::Update();

	BYTE aKeyState[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏���
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aOldState[nCntKey] = m_aKeyState[nCntKey];	// �ЂƂO�̃L�[�{�[�h�v���X����ۑ�
	}

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	// ���[�ځ[�ǂ̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//---------------------------------------------------------------------------
// �}�E�X

//****************************************************************************
// �}�E�X�R���X�g���N�^
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
// �}�E�X�f�X�g���N�^
//****************************************************************************
CInputMouse::~CInputMouse()
{
}

//****************************************************************************
// �}�E�X����������
//****************************************************************************
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X(�}�E�X)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�𐶐�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�}�E�X�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//****************************************************************************
// �}�E�X�I������
//****************************************************************************
void CInputMouse::Uninit(void)
{
	CInput::Uninit();

	//���̓f�o�C�X�L�[�{�[�h�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//****************************************************************************
// �}�E�X�X�V����
//****************************************************************************
void CInputMouse::Update(void)
{
	CInput::Update();

	// �Â��}�E�X�����X�V
	m_mouseOld = m_mouse;

	// ���̓f�o�C�X����f�[�^���擾
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
		m_pDevice->Acquire();// �}�E�X�̃A�N�Z�X�����l��
	}

	// �}�E�X���W���擾����
	POINT p;
	GetCursorPos(&p);

	// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
	if (ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &p))
	{
		m_mouse.lX = p.x;
		m_mouse.lY = p.y;

		// �ړ��ʂ��v�Z
		m_mouseMove.lX = m_mouse.lX - m_mouseOld.lX;
		m_mouseMove.lY = m_mouse.lY - m_mouseOld.lY;
	}
}

//---------------------------------------------------------------------------
// �W���C�p�b�h

//****************************************************************************
// �W���C�p�b�h�R���X�g���N�^
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
// �W���C�p�b�h�f�X�g���N�^
//****************************************************************************
CInputJoypad::~CInputJoypad()
{
}

//****************************************************************************
// �W���C�p�b�h����������
//****************************************************************************
HRESULT CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// �������̃N���A
	memset(&m_joyKeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_JoyKeyStateOld, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyStateRelease, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyStateRepeat, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	// Xinput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	return S_OK;
}

//****************************************************************************
// �W���C�p�b�h�I������
//****************************************************************************
void CInputJoypad::Uninit(void)
{
	CInput::Uninit();

	// Xinput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);

	//���̓f�o�C�X�W���C�p�b�h�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//****************************************************************************
// �W���C�p�b�h�X�V����
//****************************************************************************
void CInputJoypad::Update(void)
{
	CInput::Update();

	XINPUT_STATE joyKeyState;	// �W���C�p�b�h�̓��͏���

	// �ЂƂO�̃W���C�p�b�h����ۑ�
	m_JoyKeyStateOld = m_joyKeyState;

	// �W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		m_joyKeyState = joyKeyState;	// �W���C�p�b�h�̃v���X����ۑ�

		// ����n����
		WORD Button = m_joyKeyState.Gamepad.wButtons;		// ��
		WORD OldButton = m_JoyKeyStateOld.Gamepad.wButtons;	// ��

		WORD LT = (WORD)m_joyKeyState.Gamepad.bLeftTrigger;		// ��
		WORD RT = (WORD)m_joyKeyState.Gamepad.bRightTrigger;	// ��
		WORD LTOld = m_JoyKeyStateOld.Gamepad.bLeftTrigger;		// ��
		WORD RTOld = m_JoyKeyStateOld.Gamepad.bRightTrigger;	// ��

		// �v�Z���ʂ���
		m_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;// �������Ƃ�
		m_joyKeyStateRelease.Gamepad.wButtons = OldButton & ~Button;// �������Ƃ�
		m_joyKeyStateRepeat.Gamepad.wButtons = Button;				// �����Ă����

		m_joyKeyStateTrigger.Gamepad.bLeftTrigger = LT & ~LTOld;	// �������Ƃ�
		m_joyKeyStateRelease.Gamepad.bLeftTrigger = LTOld & ~LT;	// �������Ƃ�
		m_joyKeyStateRepeat.Gamepad.bLeftTrigger = (BYTE)LT;				// �����Ă����


		m_joyKeyStateTrigger.Gamepad.bRightTrigger = RT & ~RTOld;	// �������Ƃ�
		m_joyKeyStateRelease.Gamepad.bRightTrigger = RTOld & ~RT;	// �������Ƃ�
		m_joyKeyStateRepeat.Gamepad.bRightTrigger = (BYTE)RT;				// �����Ă����
	}
}

//********************************************************************
// L�X�e�B�b�N����
//********************************************************************
bool CInputJoypad::GetLStick()
{
	bool joykey = false;
	//�^�񒆂���Ȃ�������
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
// R�X�e�B�b�N����
//********************************************************************
bool CInputJoypad::GetRStick(void)
{
	bool joykey = false;
	//�^�񒆂���Ȃ�������
	if (m_joyKeyState.Gamepad.sThumbRX >= JOYPAD_STICK_DEADZONE ||
		m_joyKeyState.Gamepad.sThumbRX <= -JOYPAD_STICK_DEADZONE ||
		m_joyKeyState.Gamepad.sThumbRY >= JOYPAD_STICK_DEADZONE ||
		m_joyKeyState.Gamepad.sThumbRY <= -JOYPAD_STICK_DEADZONE)
	{
		joykey = true;
	}
	return joykey;
}