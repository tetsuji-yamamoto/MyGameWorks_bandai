#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "pause.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "block.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"
#include "guide.h"
#include "enemy.h"
#include "snowBall.h"
#include "edit.h"
#include "timer.h"
#include "HPGauge.h"
#include "wave.h"
#include "smoke.h"
#include "cylinder.h"

// �O���[�o���ϐ��錾
GAMESTATE g_gameState = GAMESTATE_NONE;	// �Q�[�����
int g_nCounterGameState = 0;			// ��ԊǗ��J�E���^�[
bool g_bPause = false; 

//**************************************************************************************
// �Q�[����ʂ̏���������
//**************************************************************************************
void InitGame(void)
{
	// UI�̗�
	InitSB();		// ���
	InitTimer();	// �^�C�}�[
	InitHPGauge();	// HP�Q�[�W
	InitPause();	// �|�[�Y

	// �G�t�F�N�g��
	InitShadow();	// �e
	InitEffect();	// �G�t�F�N�g
	InitParticle();	// �p�[�e�B�N��
	InitSmoke();	// ��

	InitCamera();	// �J����
	InitBlock();	// �u���b�N
	InitLight();	// ���C�g
	InitPlayer();	// �v���C���[
	InitEnemy();	// �G�l�~�[
	InitBullet();		// �e
	InitExplosion();	// ����
#ifdef _DEBUG

	InitGuide();		// �K�C�h
#endif // _DEBUG

	//Initcylinder();		// �R


	g_gameState = GAMESTATE_NORMAL;	//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;		//�J�E���^�[���[��
	g_bPause = false;				//�|�[�Y����
}

//**************************************************************************************
// �Q�[����ʂ̏I������
//**************************************************************************************
void UninitGame(void)
{
	UninitShadow();		// �e
	UninitEffect();		// �G�t�F�N�g
	UninitBlock();		// �u���b�N
	UninitPlayer();		// �v���C���[
	UninitEnemy();		// �G�l�~�[
	UninitBullet();		// �e
	UninitExplosion();	// ����
#ifdef _DEBUG

	UninitGuide();		// �K�C�h
#endif
	//Uninitcylinder();	// �R

	// UI�̗�
	UninitSB();			// ���
	UninitTimer();		// �^�C�}�[
	UninitHPGauge();	// HP�Q�[�W

	UninitPause();	// �|�[�Y

}

//**************************************************************************************
// �Q�[����ʂ̍X�V����
//**************************************************************************************
void UpdateGame(void)
{


	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y���̍X�V����
		UpdatePause();
	}
	else
	{//�|�[�Y���łȂ����
		UpdateCamera();		//�J����
		UpdateLight();		//���C�g
		UpdatePlayer();		// �v���C���[
		UpdateEnemy();		// �G�l�~�[
		UpdateShadow();		// �e
		UpdateBlock();		// �u���b�N
		UpdateBullet();		// �e
		UpdateExplosion();	// ����
		UpdateEffect();		// �G�t�F�N�g
		UpdateParticle();	// �p�[�e�B�N��
#ifdef _DEBUG

		UpdateGuide();		// �K�C�h
#endif
		UpdateSmoke();		// ��
	//	Updatecylinder();	// �R

		// UI�̗�
		UpdateSB();			// ���
		UpdateHPGauge();	// HP�Q�[�W

		if (GetEditMode() == EDITMODE_NONE)
		{
			UpdateTimer();		// �^�C�}�[	
		}
	}
	
	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true)
	{//�|�[�Y�L�[�iP�j�������ꂽ
		g_bPause = g_bPause ? false : true;
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:	// �ʏ���

		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_nCounterGameState = 0;
			g_gameState = GAMESTATE_NONE;	// �������Ă��Ȃ���Ԃɐݒ�
			SetFade(MODE_RESULT);
		}
		break;
	}
}

//**************************************************************************************
// �Q�[����ʂ̕`�揈��
//**************************************************************************************
void DrawGame(void)
{
	SetCamera();		// �J����

#ifdef _DEBUG
	DrawGuide();		// �K�C�h
#endif

	//Drawcylinder();		// �R
	DrawBlock();		// �u���b�N
	DrawShadow();		// �e
	DrawTimer();		// �^�C�}�[
	DrawEnemy();		// �G�l�~�[
	DrawPlayer();		// �v���C���[
	DrawExplosion();	// ����
	DrawEffect();		// �G�t�F�N�g
	DrawBullet();		// �e

	// UI�̗�
	DrawHPGauge();		// HP�Q�[�W
	DrawSB();			// ���


	// �|�[�Y��
	if (g_bPause == true)
	{
		// �|�[�Y�̕`��
		DrawPause();
	}
}

//**************************************************************************************
// �Q�[����Ԃ̐ݒ�
//**************************************************************************************
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	g_nCounterGameState = 0;
}

//**************************************************************************************
// �Q�[����Ԃ̎擾
//**************************************************************************************
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//**************************************************************************************
// �|�[�Y�̗L�������ݒ�
//**************************************************************************************
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}