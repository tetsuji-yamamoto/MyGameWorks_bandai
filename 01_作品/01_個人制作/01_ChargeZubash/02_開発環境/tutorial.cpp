#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
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
#include "background.h"
#include "lain.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;				//���_�o�b�t�@�ւ̃|�C���^
TUTORIAL g_tutorial;							//�`���[�g���A���|���S���̏��//�`���[�g���A���|���S���̃e�N�X�`��
bool g_bPauseTuto = false;

//==============================================
//�`���[�g���A����ʂ̏���������
//==============================================
void InitTutorial(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//���̏�����

	g_tutorial.pFileName = FILE_TEX_TUTORIAL_MOVE;
	g_tutorial.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	g_tutorial.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_tutorial.nType = TUTORIALTYPE_MOVE;
	g_tutorial.fWidth = 400.0f;
	g_tutorial.fHeight = 200.0f;
	g_tutorial.bDisp = false;
	g_tutorial.bBrink = false;
	g_tutorial.bInput = false;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		g_tutorial.pFileName,
		&g_pTextureTutorial);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();

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
	for (int nCnt = 0; nCnt < 22; nCnt++)
	{
		SetBlock(D3DXVECTOR3(-BLOCK_WIDTH + BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}

	//��2�i��
	for (int nCnt = 0; nCnt < 22; nCnt++)
	{
		SetBlock(D3DXVECTOR3(-BLOCK_WIDTH + BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT * 3.0f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}
	//------------------------------------
	//����i��1
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		SetBlock(D3DXVECTOR3(-BLOCK_WIDTH + BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT * 7.0f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}

	//����i��1
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		SetBlock(D3DXVECTOR3(-BLOCK_WIDTH + BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT * 5.0f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}
	//------------------------------------
	//����i��1
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		SetBlock(D3DXVECTOR3(SCREEN_WIDTH + BLOCK_WIDTH - BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT * 7.0f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
		SetBlock(D3DXVECTOR3(SCREEN_WIDTH + BLOCK_WIDTH - BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT * 5.0f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}
	//-----------------------------------
	
	//�G�ݒu
	SetEnemy(FILE_TEX_PB, D3DXVECTOR3(1100.0f, 490.0f, 0.0f), ENEMYTYPE_PUNCHINGBAG, 5, PB_WIDTH, PB_HEIGHT);
	
	//�w�i
	SetBackground(FALE_TEX_BG_TITLE_CLOUDY_1, BGTYPE_CLOUDY_0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetBackground(FALE_TEX_BG_TITLE_CLOUDY_2, BGTYPE_CLOUDY_1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}
//==============================================
//�`���[�g���A����ʂ̏I������
//==============================================
void UninitTutorial(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

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
	UninitLain();		//�J


	g_bPauseTuto = false;
}

//==============================================
//�`���[�g���A����ʂ̍X�V����
//==============================================
void UpdateTutorial(void)
{
	Player* pPlayer = GetPlayer();	//�v���C���[�擾

	VERTEX_2D* pVtx;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	if (pPlayer->fLife <= 0)
	{//�̗͖S���Ȃ��猳�ɖ߂��Ă�����
		pPlayer->pos = D3DXVECTOR3(200.0f, -100.0f,0.0f);
		pPlayer->fLife = MAX_PLAYER_HP;
	}
	
	//�����x��ς��Ă���
	if (g_tutorial.bBrink == false)
	{//�Â�������

		g_tutorial.col.a += 0.01f;//���邳�����Ă���

		if (g_tutorial.col.a >= 1.0f)
		{//���xMAX
			g_tutorial.col.a = 1.0f;//���x�����܂�

			//���삳�ꂽ��
			if (TutorialInput() == true)
			{//���͂������ǂ���
				g_tutorial.bBrink = true;//�Â����Ă�����
			}
		}
	}

	//�Â����ėǂ�������
	if (g_tutorial.bBrink == true)
	{//���邩������

		g_tutorial.col.a -= 0.01f;//�Â����Ă���

		if (g_tutorial.col.a <= 0.0f)
		{//���x0
			g_tutorial.col.a = 0.0f;	//�ő喾�x
			g_tutorial.bDisp = true;	//�\�����I�����
			g_tutorial.nType++;			//���̐�����
		}
	}

	//��ʑJ��
	if (KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true)
	{
		if (g_bPauseTuto == false)
		{//	�|�[�Y������Ȃ�������
			SetFade(MODE_GAME);
		}
	}


	//�\����Ԃɂ����
	if (g_tutorial.bDisp == false)
	{//�\�����I����ĂȂ�������


	}
	else if (g_tutorial.bDisp == true)
	{//�\�����I�������

		//���̃e�N�X�`���ɕς���
		switch (g_tutorial.nType)
		{
		case TUTORIALTYPE_JUMP:
			g_tutorial.pFileName = FILE_TEX_TUTORIAL_JUMP;
			break;

		case TUTORIALTYPE_ATTACK:
			g_tutorial.pFileName = FILE_TEX_TUTORIAL_ATTACK;
			break;

		case TUTORIALTYPE_THUNDER:
			g_tutorial.pFileName = FILE_TEX_TUTORIAL_THUNDER;
			break;

		case TUTORIALTYPE_DISCHARGE:
			g_tutorial.pFileName = FILE_TEX_TUTORIAL_DISCHARGE;
			break;

		case TUTORIALTYPE_END:
			g_tutorial.pFileName = FILE_TEX_TUTORIAL_END;
			break;

		}
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			g_tutorial.pFileName,
			&g_pTextureTutorial);

		g_tutorial.bDisp = false;	//�\�����Ă��Ȃ����
		g_tutorial.bBrink = false;	//�Â�����
		g_tutorial.bInput = false;	//���͂��Ă��Ȃ����
	}

	if (g_bPauseTuto == true)
	{//	�|�[�Y��
		//	�|�[�Y���̍X�V����
		UpdatePause();
	}
	else
	{//	�|�[�Y���łȂ����
		UpdateBlock();		//	�u���b�N
		UpdateThunder();	//	��
		UpdatePlayer();		//	�v���C���[
		UpdateSword();		//	��
		UpdateCharge();		//	�[�d
		UpdateEnemy();		//	�G
		UpdateEffect();		//	�G�t�F�N�g
		UpdateParticle();	//	�p�[�e�B�N��
		UpdateHPbar();		//	HP�o�[
		UpdateTimer();		//	�^�C�}�[
		UpdateLain();		//�J

	}

	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_BACK) == true)
	{//�|�[�Y�L�[�iP�j�������ꂽ
		g_bPauseTuto = g_bPauseTuto ? false : true;
	}

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_tutorial.pos.x - g_tutorial.fWidth;
	pVtx[0].pos.y = g_tutorial.pos.y - g_tutorial.fHeight;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_tutorial.pos.x + g_tutorial.fWidth;
	pVtx[1].pos.y = g_tutorial.pos.y - g_tutorial.fHeight;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_tutorial.pos.x - g_tutorial.fWidth;
	pVtx[2].pos.y = g_tutorial.pos.y + g_tutorial.fHeight;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_tutorial.pos.x + g_tutorial.fWidth;
	pVtx[3].pos.y = g_tutorial.pos.y + g_tutorial.fHeight;
	pVtx[3].pos.z = 0.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_tutorial.col;
	pVtx[1].col = g_tutorial.col;
	pVtx[2].col = g_tutorial.col;
	pVtx[3].col = g_tutorial.col;


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();
}

//==============================================
//�`���[�g���A����ʂ̕`�揈��
//==============================================
void DrawTutorial(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorial);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,										//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);										//�`�悷��v���~�e�B�u�i�v���C���[�j��

	DrawThunder();	//��
	DrawBlock();	//�u���b�N
	DrawEnemy();	//�G
	DrawSword();	//��
	DrawPlayer();	//�v���C���[
	DrawParticle();	//�p�[�e�B�N��
	DrawEffect();	//�G�t�F�N�g
	DrawLain();		//�J
	DrawHPbar();	//HP�o�[
	DrawCharge();	//�[�d
	DrawTimer();	//�^�C�}�[

	//�|�[�Y��
	if (g_bPauseTuto == true)
	{
		//�|�[�Y�̕`��
		DrawPause();
	}


}

//===============================
//�`���[�g���A���̐ݒ�
//===============================
void SetTutorial(const char* pFileName, D3DXVECTOR3 pos, D3DXCOLOR col, TUTRIALTYPE type, float fWidth, float fHeight)
{

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);


	g_tutorial.pFileName = pFileName;
	g_tutorial.pos = pos;
	g_tutorial.col = col;
	g_tutorial.nType = type;
	g_tutorial.fWidth = fWidth;
	g_tutorial.fHeight = fHeight;
	

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		g_tutorial.pFileName,
		&g_pTextureTutorial);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_tutorial.pos.x - g_tutorial.fWidth;
	pVtx[0].pos.y = g_tutorial.pos.y - g_tutorial.fHeight;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_tutorial.pos.x + g_tutorial.fWidth;
	pVtx[1].pos.y = g_tutorial.pos.y - g_tutorial.fHeight;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_tutorial.pos.x - g_tutorial.fWidth;
	pVtx[2].pos.y = g_tutorial.pos.y + g_tutorial.fHeight;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_tutorial.pos.x + g_tutorial.fWidth;
	pVtx[3].pos.y = g_tutorial.pos.y + g_tutorial.fHeight;
	pVtx[3].pos.z = 0.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_tutorial.col;
	pVtx[1].col = g_tutorial.col;
	pVtx[2].col = g_tutorial.col;
	pVtx[3].col = g_tutorial.col;


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();
}

//===============================
//�`���[�g���A���̐ݒ�
//===============================
bool TutorialInput(void)
{
	bool bInput = false;

	XINPUT_STATE* pStick = GetJoySticAngle();	//�X�e�B�b�N�擾
	Player* pPlayer = GetPlayer();				//�v���C���[�擾

	//���삵����
	switch (g_tutorial.nType)
	{
	case TUTORIALTYPE_MOVE:
		if (KeyboardRepeat(DIK_A) == true || GetJoypadRepeat(JOYKEY_LEFT) == true || pStick->Gamepad.sThumbLX <= -5000)
		{//���ړ�
			bInput = true;//������
		}
		else if (KeyboardRepeat(DIK_D) == true || GetJoypadRepeat(JOYKEY_RIGHT) == true || pStick->Gamepad.sThumbLX >= 5000)
		{//�E�ړ�
			bInput = true;//������
		}
		break;

	case TUTORIALTYPE_JUMP:
		if (KeyboardTrigger(DIK_SPACE) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{//�W�����v
			bInput = true;//������
		}
		break;

	case TUTORIALTYPE_ATTACK:
		if (KeyboardTrigger(DIK_E) == true || GetJoypadTrigger(JOYKEY_X) == true)
		{//�ʏ�U��
			bInput = true;//������
		}
		break;

	case TUTORIALTYPE_THUNDER:
		//����������[�d
		if (HitThunder(pPlayer->pos, PLAYER_HEIGHT) == true)
		{
			bInput = true;//������
		}
		break;

	case TUTORIALTYPE_DISCHARGE:
		if (KeyboardTrigger(DIK_F) == true || GetJoypadTrigger(JOYKEY_Y) == true)
		{//���o
			bInput = true;//������
		}
		break;

	case TUTORIALTYPE_END:
		break;

	}

	//�t���O��Ԃ�
	return bInput;
}

//===========================================
//�|�[�Y�̗L�������ݒ�
//===========================================
void SetEnablePause2(bool bPause)
{
	g_bPauseTuto = bPause;
}