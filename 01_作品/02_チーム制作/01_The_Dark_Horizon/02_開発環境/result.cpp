#include "result.h"
#include "fade.h"
#include "sound.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "camera.h"
#include "shadow.h"
#include "block.h"
#include "light.h"
#include "player.h"

// �O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
RESULT g_result;									// ���U���g�̏��

//*********************************************
//���U���g��ʂ̏���������
//*********************************************
void InitResult(void)
{
	VERTEX_2D* pVtx;

	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, // �K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	// ���؂̉����~�߂�
	StopSound(SOUND_LABEL_BGM_PLANTS_SWAY);

	g_result.pFileTex = FILE_TEX_RESULT_GAMEOVER;

	switch (g_result.resultType)
	{
	case RESULTTYPE_GAMEOVER:
		// �Q�[���I�[�o�[��
		PlaySound(SOUND_LABEL_SE_GAMEOVER);
		// �Q�[���I�[�o�[�e�N�X�`��
		g_result.pFileTex = FILE_TEX_RESULT_GAMEOVER;
		break;

	case RESULTTYPE_GAMECREAR:
		// �Q�[���N���A��
		PlaySound(SOUND_LABEL_SE_GAMECLEAR);
		// �Q�[���N���A�e�N�X�`��
		g_result.pFileTex = FILE_TEX_RESULT_GAMECREAR;
		break;

	case RESULTTYPE_TIMEOVER:
		// �Q�[���I�[�o�[��
		PlaySound(SOUND_LABEL_SE_GAMEOVER);
		// �Q�[���I�[�o�[�e�N�X�`��
		g_result.pFileTex = FILE_TEX_RESULT_TIMEOVER;
		break;

	default:
		g_result.pFileTex = FILE_TEX_RESULT_DEFAULT;
		break;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		g_result.pFileTex,
		&g_pTextureResult);

	g_result.rect.bottom = (float)SCREEN_HEIGHT * 0.1f;
	g_result.rect.left = (float)SCREEN_WIDTH * 0.3f;
	g_result.rect.right = (float)SCREEN_WIDTH * 0.3f;
	g_result.rect.top = (float)SCREEN_HEIGHT * 0.1f;
	g_result.pos = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f,(float)SCREEN_HEIGHT * 0.2f,0.0f);

	// ���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = g_result.pos + D3DXVECTOR3(-g_result.rect.left, -g_result.rect.top, 0.0f);
	pVtx[1].pos = g_result.pos + D3DXVECTOR3(g_result.rect.right, -g_result.rect.top, 0.0f);
	pVtx[2].pos = g_result.pos + D3DXVECTOR3(-g_result.rect.left, g_result.rect.bottom, 0.0f);
	pVtx[3].pos = g_result.pos + D3DXVECTOR3(g_result.rect.right, g_result.rect.bottom, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	InitCamera();	// �J����
	InitShadow();	// �e
	InitBlock();	// �u���b�N
	InitLight();	// ���C�g
	InitPlayer();	// �v���C���[
}

//*********************************************
// ���U���g��ʂ̏I������
//*********************************************
void UninitResult(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	UninitCamera();	// �J����
	UninitShadow();	// �e
	UninitBlock();	// �u���b�N
	UninitLight();	// ���C�g
	UninitPlayer();	// �v���C���[
}

//*********************************************
// ���U���g��ʂ̍X�V����
//*********************************************
void UpdateResult(void)
{
	if (KeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_START) || GetJoypadTrigger(JOYKEY_A) ||  GetJoypadTrigger(JOYKEY_B))
	{
		// ���ׂẲ����~�߂�
		StopSound();
		// ���艹
		PlaySound(SOUND_LABEL_SE_DESITION);

		SetFade(MODE_TITLE);
	}

	// UI�̗�
	UpdateCamera();	// �J����
	UpdateShadow();	// �e
	UpdateBlock();	// �u���b�N
	UpdateLight();	// ���C�g
	UpdatePlayer();	// �v���C���[

}

//*********************************************
// ���U���g��ʂ̕`�揈��
//*********************************************
void DrawResult(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	// �v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,										// �`�悷��ŏ��̒��_�C���f�b�N�X
		2);										// �`�悷��v���~�e�B�u�i�v���C���[�j��

	// �A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// UI�̗�
	SetCamera();	// �J����
	DrawShadow();	// �e
	DrawBlock();	// �u���b�N
	DrawPlayer();	// �v���C���[
}

//*********************************************
// ���U���g�ݒ�
//*********************************************
void SetResult(RESULTTYPE resultType)
{
	g_result.resultType = resultType;
}

RESULTTYPE GetResult()
{
	return g_result.resultType;
}