//****************************************************************************
// 
// ���͏���
// Author tetuji yamamoto
// 
//****************************************************************************
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

// �}�N����`
#define NUM_KEY_MAX (256)				//�L�[�̍ő吔
#define MAX_JOYPAD_STICK_ANGLE (32768)	// �W���C�p�b�h�̃A���O��
#define JOYPAD_STICK_DEADZONE (32768 * ((D3DX_PI * 0.01f) / D3DX_PI))	// �W���C�p�b�h�̃f�b�h�]�[��
#define ANGLE_UP (D3DX_PI * 0.0f)			// �A���O����
#define ANGLE_UP_RIGHT (D3DX_PI * 0.25f)	// �A���O���E��
#define ANGLE_UP_LEFT (D3DX_PI * -0.25f)	// �A���O������
#define ANGLE_DOWN (D3DX_PI)				// �A���O����
#define ANGLE_DOWN_RIGHT (D3DX_PI * 0.75f)	// �A���O���E��
#define ANGLE_DOWN_LEFT (D3DX_PI * -0.75f)	// �A���O������
#define ANGLE_RIGHT (D3DX_PI * 0.5f)		// �A���O���E
#define ANGLE_LEFT (D3DX_PI * -0.5f)		// �A���O����

// ���̓N���X
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance,HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void);

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

// �L�[�{�[�h�N���X
class CInputKeyboard : public CInput // CInput�p��
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey) { return (m_aKeyState[nKey] & 0x80) ? true : false; }
	bool GetTrigger(int nKey) { return m_aKeyState[nKey] & 0x80 && !(m_aOldState[nKey] & 0x80) ? true : false; }
	bool GetRelease(int nKey) { return m_aOldState[nKey] & 0x80 && !(m_aKeyState[nKey] & 0x80) ? true : false; }

private:
	BYTE m_aKeyState[NUM_KEY_MAX];	//�L�[�{�[�h�̃v���X���
	BYTE m_aOldState[NUM_KEY_MAX];	//�L�[�{�[�h�̌Â��v���X���
};

// �}�E�X�N���X
class CInputMouse : public CInput // CInput�p��
{
public:
	// �}�E�X�{�^���̎�ޗ�
	typedef enum
	{
		MOUSEBUTTON_LEFT = 0,	// ���N���b�N
		MOUSEBUTTON_RIGHT,		// �͋[�N���b�N
		MOUSEBUTTON_CENTER,		// �z�C�[���{�^��
		MOUSEBUTTON_MAX
	}MOUSEBUTTON;

	CInputMouse();
	~CInputMouse();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetRepeat(MOUSEBUTTON mouseButtton) { return m_mouse.rgbButtons[mouseButtton] & (0x80) ? true : false; }
	bool GetTrigger(MOUSEBUTTON mouseButtton) { return m_mouseTrigger.rgbButtons[mouseButtton] & (0x80) ? true : false; }
	bool GetRelease(MOUSEBUTTON mouseButtton) { return m_mouseRelease.rgbButtons[mouseButtton] & (0x80) ? true : false; }
	D3DXVECTOR3 GetVelocity(void) { return D3DXVECTOR3((float)m_mouseMove.lX, (float)m_mouseMove.lY, (float)m_mouseMove.lZ); }
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3((float)m_mouse.lX, (float)m_mouse.lY, (float)m_mouse.lZ); }

private:
	DIMOUSESTATE m_mouse;			// �}�E�X���
	DIMOUSESTATE m_mouseMove;		// �}�E�X�̈ړ��ʏ��
	DIMOUSESTATE m_mouseOld;		// �Â��}�E�X���
	DIMOUSESTATE m_mouseTrigger;	// �}�E�X�g���K�[���
	DIMOUSESTATE m_mouseRelease;	// �}�E�X�����[�X���
};

// �W���C�p�b�h�N���X
class CInputJoypad : public CInput // CInput�p��
{
public:
	//�L�[�̎��
	typedef enum
	{
		JOYKEY_UP = 0,			//�\���L�[��
		JOYKEY_DOWN,			//�\���L�[��
		JOYKEY_LEFT,			//�\���L�[��
		JOYKEY_RIGHT,			//�\���L�[�E
		JOYKEY_START,			//�X�^�[�g�{�^��
		JOYKEY_BACK,			//�o�b�N�{�^��
		JOYKEY_LSTICK_BUTTON,	//L�X�e�B�b�N�{�^��
		JOYKEY_RSTICK_BUTTON,	//R�X�e�B�b�N�{�^��
		JOYKEY_L1,				//L1�{�^��
		JOYKEY_R1,				//R1�{�^��
		JOYKEY_L2,				//L2�g���K�[
		JOYKEY_R2,				//R2�g���K�[
		JOYKEY_A,				//A�{�^��
		JOYKEY_B,				//B�{�^��
		JOYKEY_X,				//X�{�^��
		JOYKEY_Y,				//Y�{�^��
		JOYKEY_MAX
	}JOYKEY;

	CInputJoypad();
	~CInputJoypad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetkeyPress(JOYKEY key) { return (m_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false; }
	bool GetkeyTrigger(JOYKEY key) { return (m_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false; }
	bool GetkeyRelease(JOYKEY key) { return (m_joyKeyStateRelease.Gamepad.wButtons & (0x01 << key)) ? true : false; }
	bool GetkeyRepeat(JOYKEY key) { return (m_joyKeyStateRepeat.Gamepad.wButtons & (0x01 << key)) ? true : false; }
	bool GetLTTrigger(void) { return (m_joyKeyStateTrigger.Gamepad.bLeftTrigger ? true : false); }
	bool GetLTRelease(void) { return (m_joyKeyStateRelease.Gamepad.bLeftTrigger ? true : false); }
	bool GetLTRepeat(void) { return (m_joyKeyStateRepeat.Gamepad.bLeftTrigger ? true : false); }
	bool GetRTTrigger(void) { return (m_joyKeyStateTrigger.Gamepad.bRightTrigger ? true : false); }
	bool GetRTRelease(void) { return (m_joyKeyStateRelease.Gamepad.bRightTrigger ? true : false); }
	bool GetRTRepeat(void) { return (m_joyKeyStateRepeat.Gamepad.bRightTrigger ? true : false); }

	//�X�e�B�b�N
	bool GetLStick(void);
	bool GetRStick(void);

private:
	XINPUT_STATE m_joyKeyState;			// �W���C�p�b�h�̏��
	XINPUT_STATE m_JoyKeyStateOld;		// �W���C�p�b�h�̌Â����
	XINPUT_STATE m_joyKeyStateTrigger;	// �W���C�p�b�h�̃g���K�[���
	XINPUT_STATE m_joyKeyStateRepeat;	// �W���C�p�b�h�̃��s�[�g���
	XINPUT_STATE m_joyKeyStateRelease;	// �W���C�p�b�h�̃����[�X���
};

#endif
