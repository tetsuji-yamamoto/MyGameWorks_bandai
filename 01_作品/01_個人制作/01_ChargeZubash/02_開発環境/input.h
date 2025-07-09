#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
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
//�X�e�B�b�N�̎��
enum STICK
{
	JOYSTICK_UP = 0,
	JOYSTICK_DOWN,
	JOYSTICK_LEFT,
	JOYSTICK_RIGHT,
	JOYSTICK_MAX
};
//�X�e�B�b�N�̍\����
typedef struct
{
	int nStickLX;
	int nStickLY;
}STICK_ANGLE;
//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UpdataKeyboard(void);
void UninitKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeyboardTrigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);

HRESULT InitJoypad(void);
void UpdataJoypad(void);
void UninitJoypad(void);
//�{�^��
bool GetJoypadPress(JOYKEY key);	//�����Ă���Ƃ�
bool GetJoypadTrigger(JOYKEY key);	//�������u��
bool GetJoypadRelease(JOYKEY key);	//�������Ƃ�
bool GetJoypadRepeat(JOYKEY key);	//�����Ă����
//�g���K�[
bool GetJoyTrigger(JOYKEY key);			//�����Ă���Ƃ�
bool GetJoyTriggerTrigger(JOYKEY key);	//�������Ƃ�
bool GetJoyTriggerRelease(JOYKEY key);	//�������Ƃ�
bool GetJoyTriggerRepeat(JOYKEY key);	//�����Ă����
//�X�e�B�b�N
bool GetJoyStick(void);
XINPUT_STATE* GetJoySticAngle(void);
#endif