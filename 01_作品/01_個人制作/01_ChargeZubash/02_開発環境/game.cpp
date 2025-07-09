#include "input.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"
#include "background.h"
#include "pause.h"
#include "player.h"
#include "block.h"
#include "effect.h"
#include "particle.h"
#include "thunder.h"
#include "charge.h"
#include "sword.h"
#include "enemy.h"
#include "score.h"
#include "HPbar.h"
#include "timer.h"
#include "lain.h"

//�O���[�o���ϐ��錾
GAMESTATE g_gameState = GAMESTATE_NONE;	//�Q�[�����
int g_nCounterGameState = 0;			//��ԊǗ��J�E���^�[
bool g_bPause = false; 

//===========================================
//�Q�[����ʂ̏���������
//===========================================
void InitGame(void)
{
	int nCnt;

	InitPlayer();	//�v���C���[
	InitBlock();	//�u���b�N
	InitPause();	//�|�[�Y
	InitEffect();	//�G�t�F�N�g
	InitParticle();	//�p�[�e�B�N��
	InitThunder();	//��
	InitCharge();	//�[�d
	InitSword();	//��
	InitEnemy();	//�G
	InitHPbar();	//HP�o�[
	InitTimer();	//�^�C�}�[
	InitLain();		//�J


	//�u���b�N�ݒu
	//����i��
	for (nCnt = 0; nCnt < 22; nCnt++)
	{
		SetBlock(D3DXVECTOR3(-BLOCK_WIDTH + BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}

	//����i��
	for (nCnt = 0; nCnt < 22; nCnt++)
	{
		SetBlock(D3DXVECTOR3(-BLOCK_WIDTH + BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT * 3.0f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}

	//����i��1
	for (nCnt = 0; nCnt < 3; nCnt++)
	{
		SetBlock(D3DXVECTOR3(BLOCK_WIDTH * 3.0f + BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT*0.5f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}

	//����i��2
	for (nCnt = 0; nCnt < 6; nCnt++)
	{
		SetBlock(D3DXVECTOR3(SCREEN_WIDTH + BLOCK_WIDTH - BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT * 0.5f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}

	//�ւ����Ă�
	for (int nCntEnemy = 0; nCntEnemy < MAX_SNAKE_BODY; nCntEnemy++)
	{
		SetEnemy(FILE_TEX_SNAKE, D3DXVECTOR3(800.0f, 300.0f, 0.0f), ENEMYTYPE_SNAKE, 4, SNAKE_WIDTH, SNAKE_HEIGHT);
	}

	//SetEnemy(FILE_TEX_SNAKE, D3DXVECTOR3(-800.0f, -300.0f, 0.0f), ENEMYTYPE_PUNCHINGBAG, 4, SNAKE_WIDTH, SNAKE_HEIGHT);


	SetBlock(D3DXVECTOR3(BLOCK_WIDTH + (BLOCK_WIDTH * 12.0f),  SCREEN_HEIGHT * 0.5f + (BLOCK_WIDTH * 4.0f),0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);

	SetBlock(D3DXVECTOR3(BLOCK_WIDTH + (BLOCK_WIDTH * 18.0f),  SCREEN_HEIGHT * 0.5f,0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	SetBlock(D3DXVECTOR3(BLOCK_WIDTH + (BLOCK_WIDTH * 20.0f),  SCREEN_HEIGHT * 0.5f,0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);

	SetBlock(D3DXVECTOR3(BLOCK_WIDTH + (BLOCK_WIDTH * 26.0f),  SCREEN_HEIGHT * 0.5f + (BLOCK_WIDTH * 4.0f),0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	
	//�w�i
	SetBackground(FALE_TEX_BG_TITLE_CLOUDY_1, BGTYPE_CLOUDY_0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetBackground(FALE_TEX_BG_TITLE_CLOUDY_2, BGTYPE_CLOUDY_1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	g_gameState = GAMESTATE_NORMAL;	//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;		//�J�E���^�[���[��
	g_bPause = false;				//�|�[�Y����
}

//===========================================
//�Q�[����ʂ̏I������
//===========================================
void UninitGame(void)
{
	UninitPlayer();		//�v���C���[
	UninitBlock();		//�u���b�N
	UninitPause();		//�|�[�Y
	UninitEffect();		//�G�t�F�N�g
	UninitParticle();	//�p�[�e�B�N��
	UninitThunder();	//��
	UninitCharge();		//�[�d
	UninitSword();		//��
	UninitEnemy();		//�G
	UninitHPbar();		//HP�o�[
	UninitTimer();		//�^�C�}�[
	UninitLain();	//�J

	//���~�߂�
	StopSound();

	//�w�i�̏I���
	EndBackground(BGTYPE_CLOUDY_0);
	EndBackground(BGTYPE_CLOUDY_1);
}

//===========================================
//�Q�[����ʂ̍X�V����
//===========================================
void UpdateGame(void)
{
	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y���̍X�V����
		UpdatePause();
	}
	else
	{//�|�[�Y���łȂ����
		UpdateBlock();		//�u���b�N
		UpdateThunder();	//��
		UpdatePlayer();		//�v���C���[
		UpdateSword();		//��
		UpdateCharge();		//�[�d
		UpdateEnemy();		//�G
		UpdateEffect();		//�G�t�F�N�g
		UpdateParticle();	//�p�[�e�B�N��
		UpdateHPbar();		//HP�o�[
		UpdateTimer();		//�^�C�}�[
		UpdateLain();		//�J


	}
	
	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_BACK) == true)
	{//�|�[�Y�L�[�iP�j�������ꂽ
		g_bPause = g_bPause ? false : true;
	}

	////��ʑJ��
	//if (KeyboardTrigger(DIK_RETURN) == true)
	//{
	//	SetFade(MODE_RESULT);
	//}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL://�ʏ���

		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_nCounterGameState = 0;
			g_gameState = GAMESTATE_NONE;	//�������Ă��Ȃ���Ԃɐݒ�
			SetFade(MODE_RESULT);
		}
		break;
	}
}

//===========================================
//�Q�[����ʂ̕`�揈��
//===========================================
void DrawGame(void)
{
	DrawThunder();	//��
	DrawBlock();	//�u���b�N
	DrawEnemy();	//�G
	DrawSword();	//��
	DrawPlayer();	//�v���C���[
	DrawCharge();	//�[�d
	DrawParticle();	//�p�[�e�B�N��
	DrawEffect();	//�G�t�F�N�g
	DrawLain();		//�J
	DrawHPbar();	//HP�o�[
	DrawTimer();	//�^�C�}�[

	//�|�[�Y��
	if (g_bPause == true)
	{
		//�|�[�Y�̕`��
		DrawPause();
	}
}

//===========================================
//�Q�[����Ԃ̐ݒ�
//===========================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	g_nCounterGameState = 0;
}

//===========================================
//�Q�[����Ԃ̎擾
//===========================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//===========================================
//�|�[�Y�̗L�������ݒ�
//===========================================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}