#include "title.h"
#include "fade.h"
#include "sound.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "snowBall.h"
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
#include "sound.h"

// �O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_aPTextureTitle[TITLETYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
TITLE g_aTitle[TITLETYPE_MAX];								// �^�C�g���|���S���̏��
TITLEDIRECTOR g_TitleDirector;

//*********************************************
// �^�C�g����ʂ̏���������
//*********************************************
void InitTitle(void)
{

	int nCntTitle;

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLETYPE_MAX, // �K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	// ���o�\���̏�����
	g_TitleDirector.titleDirect = TITLEDIRECT_LOGODOWN;
	g_TitleDirector.nTimer = 0;
	g_TitleDirector.bBrink = false;

	// ���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// ���̏�����
	for (nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		g_aTitle[nCntTitle].pFileName = NULL;
		g_aTitle[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCntTitle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTitle[nCntTitle].nButtonIdx = -1;
		g_aTitle[nCntTitle].fWidth = 0.0f;
		g_aTitle[nCntTitle].fHeight = 0.0f;
		g_aTitle[nCntTitle].bUse = false;
		g_aTitle[nCntTitle].type = TITLETYPE_MAX;

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	// �^�C�g�����S
	SetTitle(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, -SCREEN_HEIGHT * 0.15f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		TITLETYPE_LOGO,
		BUTTONTYPE_MAX,
		FILE_TEX_TITLE_SBS,
		SCREEN_WIDTH * 0.3f,
		SCREEN_HEIGHT * 0.15f);


	// �X�^�[�g�{�^��
	SetTitle(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.6f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),
		TITLETYPE_START,
		BUTTONTYPE_MAX,
		FILE_TEX_STRTBUTTON,
		SCREEN_WIDTH * 0.1f,
		SCREEN_HEIGHT * 0.05f);

	// �X�^�[�g�{�^����
	SetTitle(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.6f, 0.0f),
		D3DXCOLOR(0.0f, 1.0f, 0.9f, 0.0f),
		TITLETYPE_START_SHINE,
		BUTTONTYPE_MAX,
		FILE_TEX_STRTBUTTON_SHINE,
		SCREEN_WIDTH * 0.1f,
		SCREEN_HEIGHT * 0.05f);

	// �`���[�g���A���{�^��
	SetTitle(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.6f + SCREEN_HEIGHT * 0.1f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),
		TITLETYPE_TUTORIAL,
		BUTTONTYPE_MAX,
		FILE_TEX_TUTORIALBUTTON,
		SCREEN_WIDTH * 0.1f,
		SCREEN_HEIGHT * 0.05f);

	// �`���[�g���A���{�^����
	SetTitle(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.6f + SCREEN_HEIGHT * 0.1f, 0.0f),
		D3DXCOLOR(0.0f, 1.0f, 0.9f, 0.0f),
		TITLETYPE_TUTORIAL_SHINE,
		BUTTONTYPE_MAX,
		FILE_TEX_TUTORIALBUTTON_SHINE,
		SCREEN_WIDTH * 0.1f,
		SCREEN_HEIGHT * 0.05f);
	// UI�̗�
	InitCamera();	// �J����
	InitShadow();	// �e
	InitBlock();	// �u���b�N
	InitLight();	// ���C�g
	InitPlayer();	// �v���C���[

	// ���؂��h��鉹
	PlaySound(SOUND_LABEL_BGM_PLANTS_SWAY);
}
//*********************************************
// �^�C�g����ʂ̏I������
//*********************************************
void UninitTitle(void)
{
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		// �e�N�X�`���̔j��
		if (g_aPTextureTitle[nCntTitle] != NULL)
		{
			g_aPTextureTitle[nCntTitle]->Release();
			g_aPTextureTitle[nCntTitle] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	// UI�̗�
	UninitCamera();	// �J����
	UninitShadow();	// �e
	UninitBlock();	// �u���b�N
	UninitLight();	// ���C�g
	UninitPlayer();	// �v���C���[
}

//*********************************************
// �^�C�g����ʂ̍X�V����
//*********************************************
void UpdateTitle(void)
{
	// ����
	int nResult = -1;

	if (KeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_B) || GetJoypadTrigger(JOYKEY_START))
	{
		if (g_TitleDirector.titleDirect == TITLEDIRECT_STARTBUTTONBRINK)
		{
			// ���艹
			PlaySound(SOUND_LABEL_SE_DESITION);


			g_TitleDirector.bBrink = true;

			SetFade(MODE_GAME);
		}
		else if (g_TitleDirector.titleDirect == TITLEDIRECT_TUTORIALBUTTONBRINK)
		{
			// ���艹
			PlaySound(SOUND_LABEL_SE_DESITION);

			g_TitleDirector.bBrink = true;

			SetFade(MODE_TUTORIAL);
		}

	}

	// �^�C�g�����o
	nResult = TitleManager();


	// UI�̗�
	UpdateCamera();	// �J����
	UpdateShadow();	// �e
	UpdateBlock();	// �u���b�N
	UpdateLight();	// ���C�g
	UpdatePlayer();	// �v���C���[
}

//*********************************************
// �^�C�g����ʂ̕`�揈��
//*********************************************
void DrawTitle(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�00
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aPTextureTitle[g_aTitle[nCntTitle].type]);

			// �v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				4 * nCntTitle,							// �`�悷��ŏ��̒��_�C���f�b�N�X
				2);										// �`�悷��v���~�e�B�u�i�v���C���[�j��
		}
	}

	// �A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// UI�̗�
	SetCamera();	// �J����
	DrawShadow();	// �e
	DrawBlock();	// �u���b�N
	DrawPlayer();	// �v���C���[
}

//*********************************************
// �^�C�g���̐ݒ�
//*********************************************
void SetTitle(D3DXVECTOR3 pos,D3DXCOLOR col,TITLETYPE type,BUTTONTYPE buttonType,const char* pFileName,float fWidth,float fHeight)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// �T��
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == false)
		{
			g_aTitle[nCntTitle].pFileName = pFileName;
			g_aTitle[nCntTitle].pos = pos;
			g_aTitle[nCntTitle].col = col;
			g_aTitle[nCntTitle].type = type;
			g_aTitle[nCntTitle].nButtonIdx = buttonType;
			g_aTitle[nCntTitle].fWidth = fWidth;
			g_aTitle[nCntTitle].fHeight = fHeight;
			g_aTitle[nCntTitle].bUse = true;

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				g_aTitle[nCntTitle].pFileName,
				&g_aPTextureTitle[type]);

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}

//*********************************************
// �^�C�g���Ǘ�
//*********************************************
int TitleManager(void)
{
	int nResult = -1;

	switch (g_TitleDirector.titleDirect)
	{
	case TITLEDIRECT_LOGODOWN:
		TitleLogoAnimation(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f, 0.0f),
			D3DXVECTOR3(0.0f, 5.0f, 0.0f));
		break;

	case TITLEDIRECT_BUTTONAPPEAR:
		TitleStartButtonAnimation();
		TitleTutorialButtonAnimation();
		break;

	case TITLEDIRECT_STARTBUTTONBRINK:
		TitleStartButtonShine();
		break;

	case TITLEDIRECT_TUTORIALBUTTONBRINK:
		TitleTutorialButtonShine();
		break;
	}

	return nResult;
}

//*********************************************
// �^�C�g�����S�̃A�j���[�V����
//*********************************************
int TitleLogoAnimation(D3DXVECTOR3 posDest,D3DXVECTOR3 move)
{
	VERTEX_2D* pVtx;
	int nResult = -1;	// ����

	// ���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// �T��
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse && g_aTitle[nCntTitle].type == TITLETYPE_LOGO)
		{

			g_aTitle[nCntTitle].pos += move;

			if (g_aTitle[nCntTitle].pos.y >= posDest.y || KeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_B) || GetJoypadTrigger(JOYKEY_START))
			{// �ړI�n�ɂ����Ȃ��
				g_aTitle[nCntTitle].pos = posDest;
				g_TitleDirector.titleDirect = TITLEDIRECT_BUTTONAPPEAR;
				nResult = 1;
			}

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	// ���ʂ�Ԃ�
	return nResult;
}

//*********************************************
// �Q�[���X�^�[�g�̃A�j���[�V����
//*********************************************
int TitleStartButtonAnimation(void)
{
	VERTEX_2D* pVtx;
	int nResult = -1;	// ����

	// ���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// �T��
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse && g_aTitle[nCntTitle].type == TITLETYPE_START)
		{

			g_aTitle[nCntTitle].col.a += 0.1f;

			if (g_aTitle[nCntTitle].col.a >= 1.0f || KeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_B) || GetJoypadTrigger(JOYKEY_START))
			{
				g_aTitle[nCntTitle].col.a = 1.0f;
				g_TitleDirector.titleDirect = TITLEDIRECT_STARTBUTTONBRINK;
			}
			nResult = 1;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	// ���ʂ�Ԃ�
	return nResult;
}

//*********************************************
// �e���[�g���A���{�^���̃A�j���[�V����
//*********************************************
int TitleTutorialButtonAnimation(void)
{
	VERTEX_2D* pVtx;
	int nResult = -1;	// ����

	// ���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// �T��
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse && g_aTitle[nCntTitle].type == TITLETYPE_TUTORIAL)
		{

			g_aTitle[nCntTitle].col.a += 0.1f;

			if (g_aTitle[nCntTitle].col.a >= 1.0f || KeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_B) || GetJoypadTrigger(JOYKEY_START))
			{
				g_aTitle[nCntTitle].col.a = 1.0f;
				g_TitleDirector.titleDirect = TITLEDIRECT_STARTBUTTONBRINK;
			}
			nResult = 1;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	// ���ʂ�Ԃ�
	return nResult;
}

//*********************************************
// �X�^�[�g�{�^�����P��
//*********************************************
int TitleStartButtonShine(void)
{
	VERTEX_2D* pVtx;
	int nResult = -1;	// ����

	// ���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// �T��
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse && g_aTitle[nCntTitle].type == TITLETYPE_START_SHINE)
		{

			if (g_TitleDirector.bBrink)
			{
				g_TitleDirector.nTimer++;

				if (g_TitleDirector.nTimer >= 0)
				{
					g_aTitle[nCntTitle].col.a = 1.0f;

					if (g_TitleDirector.nTimer >= 2)
					{
						g_TitleDirector.nTimer *= -1;
					}
				}
				else if(g_TitleDirector.nTimer < 0)
				{
					g_aTitle[nCntTitle].col.a = 0.0f;
				}
			}
			else
			{
				g_aTitle[nCntTitle].col.a = 1.0f;

				if (KeyboardTrigger(DIK_W) || GetJoypadTrigger(JOYKEY_UP))
				{
					// �I����
					PlaySound(SOUND_LABEL_SE_SELECT);

					g_aTitle[nCntTitle].col.a = 0.0f;
					g_TitleDirector.titleDirect = TITLEDIRECT_TUTORIALBUTTONBRINK;
				}
				else if (KeyboardTrigger(DIK_S) || GetJoypadTrigger(JOYKEY_DOWN))
				{
					// �I����
					PlaySound(SOUND_LABEL_SE_SELECT);

					g_aTitle[nCntTitle].col.a = 0.0f;
					g_TitleDirector.titleDirect = TITLEDIRECT_TUTORIALBUTTONBRINK;
				}

			}

		

			nResult = 1;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	// ���ʂ�Ԃ�
	return nResult;
}

//*********************************************
// �`���[�g���A���{�^�����P��
//*********************************************
int TitleTutorialButtonShine(void)
{
	VERTEX_2D* pVtx;
	int nResult = -1;	// ����

	// ���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// �T��
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse && g_aTitle[nCntTitle].type == TITLETYPE_TUTORIAL_SHINE)
		{

			if (g_TitleDirector.bBrink)
			{
				g_TitleDirector.nTimer++;

				if (g_TitleDirector.nTimer >= 0)
				{
					g_aTitle[nCntTitle].col.a = 1.0f;

					if (g_TitleDirector.nTimer >= 2)
					{
						g_TitleDirector.nTimer *= -1;
					}
				}
				else if (g_TitleDirector.nTimer < 0)
				{
					g_aTitle[nCntTitle].col.a = 0.0f;
				}
			}
			else
			{
				g_aTitle[nCntTitle].col.a = 1.0f;

				if (KeyboardTrigger(DIK_W) || GetJoypadTrigger(JOYKEY_UP))
				{
					// �I����
					PlaySound(SOUND_LABEL_SE_SELECT);

					g_aTitle[nCntTitle].col.a = 0.0f;
					g_TitleDirector.titleDirect = TITLEDIRECT_STARTBUTTONBRINK;
				}
				else if (KeyboardTrigger(DIK_S) || GetJoypadTrigger(JOYKEY_DOWN))
				{
					// �I����
					PlaySound(SOUND_LABEL_SE_SELECT);

					g_aTitle[nCntTitle].col.a = 0.0f;
					g_TitleDirector.titleDirect = TITLEDIRECT_STARTBUTTONBRINK;
				}

			}

			nResult = 1;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	// ���ʂ�Ԃ�
	return nResult;
}