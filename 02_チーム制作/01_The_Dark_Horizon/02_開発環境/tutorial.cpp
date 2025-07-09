#include "tutorial.h"
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
#include "score.h"
#include "smoke.h"
#include "signboard.h"

// �O���[�o���ϐ��錾
GAMESTATE g_tutorialState = GAMESTATE_NONE;	// �Q�[�����
int g_nCounterTutorialState = 0;			// ��ԊǗ��J�E���^�[
bool g_bPauseTutorial = false;

//*************************************************
// �`���[�g���A��������
//*************************************************
void InitTutorial(void)
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
	InitGuide();		// �K�C�h
	InitWave();			// �E�F�[�u

	InitSignboard();	// �ē��W��

	g_tutorialState = GAMESTATE_NORMAL;	//�ʏ��Ԃɐݒ�
	g_nCounterTutorialState = 0;		//�J�E���^�[���[��
	g_bPauseTutorial = false;				//�|�[�Y����
}

//*************************************************
// �`���[�g���A���I��
//*************************************************
void UninitTutorial(void)
{
	UninitCamera();		//�J����
	UninitLight();		//���C�g
	UninitShadow();		// �e
	UninitEffect();		// �G�t�F�N�g
	UninitBlock();		// �u���b�N
	UninitPlayer();		// �v���C���[
	UninitEnemy();		// �G�l�~�[
	UninitBullet();		// �e
	UninitExplosion();	// ����
	UninitGuide();		// �K�C�h

	// UI�̗�
	UninitSB();			// ���
	UninitTimer();		// �^�C�}�[
	UninitHPGauge();	// HP�Q�[�W

	UninitPause();	// �|�[�Y

	UninitSignboard();	// �ē��W��
}

//*************************************************
// �`���[�g���A���X�V
//*************************************************
void UpdateTutorial(void)
{
	if (g_bPauseTutorial == true)
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
		UpdateGuide();		// �K�C�h
		UpdateSmoke();		// ��

		// UI�̗�
		UpdateSB();			// ���
		UpdateTimer();		// �^�C�}�[	
		UpdateHPGauge();	// HP�Q�[�W
		UpdateSignboard();	// �ē��W��

		// �E�F�[�u�Ǘ�

	//	WaveAppEnemy();
	}

	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true)
	{//�|�[�Y�L�[�iP�j�������ꂽ
		g_bPauseTutorial = g_bPauseTutorial ? false : true;
	}

	switch (g_tutorialState)
	{
	case GAMESTATE_NORMAL:	// �ʏ���

		break;

	case GAMESTATE_END:
		g_nCounterTutorialState++;
		if (g_nCounterTutorialState >= 60)
		{
			g_nCounterTutorialState = 0;
			g_tutorialState = GAMESTATE_NONE;	// �������Ă��Ȃ���Ԃɐݒ�
			SetFade(MODE_GAME);
		}
		break;
	}
}

//*************************************************
// �`���[�g���A���`��
//*************************************************
void DrawTutorial(void)
{
	SetCamera();		// �J����

#ifdef _DEBUG
	DrawGuide();		// �K�C�h
#endif

	DrawBlock();		// �u���b�N
	DrawShadow();		// �e
	DrawEnemy();		// �G�l�~�[
	DrawPlayer();		// �v���C���[
	DrawExplosion();	// ����
	DrawEffect();		// �G�t�F�N�g
	DrawBullet();		// �e
	DrawSignboard();	// �ē��W��

	if (GetEditMode() == EDITMODE_BLOCK)
	{
	}
	else
	{
		// UI�̗�
		DrawTimer();		// �^�C�}�[
		DrawSB();			// ���
		DrawHPGauge();		// HP�Q�[�W
	}


	// �|�[�Y��
	if (g_bPauseTutorial == true)
	{
		// �|�[�Y�̕`��
		DrawPause();
	}
}

//**************************************************************************************
// �|�[�Y�̗L�������ݒ�
//**************************************************************************************
void SetEnablePauseEX(bool bPause)
{
	g_bPauseTutorial = bPause;
}