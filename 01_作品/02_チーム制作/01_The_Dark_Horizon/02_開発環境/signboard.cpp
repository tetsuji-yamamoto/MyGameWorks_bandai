#include "signboard.h"
#include "keyboard.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSignboard = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pVtxTexturSignboard[BOARDTYPE_MAX] = {};		// �e�N�X�`���̃|�C���^
SIGNBOARD g_aSignboard[BOARDTYPE_MAX];								// �{�[�h
int nSignBoardIdx = 0;
//**************************************
// �{�[�h�̏�����
//**************************************
void InitSignboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * BOARDTYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSignboard, NULL);

	VERTEX_3D* pVtx = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\TUTORIAL_MOVE.jpg",
		&g_pVtxTexturSignboard[BOARDTYPE_MOVE]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\TUTORIAL_MAKESB.jpg",
		&g_pVtxTexturSignboard[BOARDTYPE_MAKE]);


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\TUTORIAL_SNOW.jpg",
		&g_pVtxTexturSignboard[BOARDTYPE_SROW_SNOW]);


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\TUTORIAL_ICE.jpg",
		&g_pVtxTexturSignboard[BOARDTYPE_SROW_ICE]);


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\TUTORIAL_GRAVEL.jpg",
		&g_pVtxTexturSignboard[BOARDTYPE_SROW_GRAVEL]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\TUTORIAL_MOKUTEKI.jpg",
		&g_pVtxTexturSignboard[BOARDTYPE_MOKUTEKI]);


	// ���_�o�b�t�@�����b�N
	g_pVtxBuffSignboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBoard = 0; nCntBoard < BOARDTYPE_MAX; nCntBoard++)
	{
		g_aSignboard[nCntBoard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSignboard[nCntBoard].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aSignboard[nCntBoard].fHeight = 0.0f;
		g_aSignboard[nCntBoard].fWidth = 0.0f;
		g_aSignboard[nCntBoard].type = BOARDTYPE_MAX;
		g_aSignboard[nCntBoard].bUse = false;

		g_aSignboard[nCntBoard].fWidth = 0.0f;

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = 0.0f;
		pVtx[0].pos.y = 0.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 0.0f;
		pVtx[1].pos.y = 0.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = 0.0f;
		pVtx[2].pos.y = 0.0f;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 0.0f;
		pVtx[3].pos.y = 0.0f;
		pVtx[3].pos.z = 0.0f;

		// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffSignboard->Unlock();

	SetSignBoard(BOARDTYPE_MOVE,
		D3DXVECTOR3(100.0f,120.0f,110.0f),
		D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),
		70.0f,
		70.0f);

	SetSignBoard(BOARDTYPE_MAKE,
		D3DXVECTOR3(520.0f, 150.0f, 140.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		70.0f,
		140.0f);

	SetSignBoard(BOARDTYPE_SROW_SNOW,
		D3DXVECTOR3(920.0f, 150.0f, 140.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		70.0f,
		140.0f);

	SetSignBoard(BOARDTYPE_SROW_ICE,
		D3DXVECTOR3(1320.0f, 150.0f, 140.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		70.0f,
		140.0f);

	SetSignBoard(BOARDTYPE_SROW_GRAVEL,
		D3DXVECTOR3(1730.0f, 150.0f, 140.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		70.0f,
		140.0f);

	SetSignBoard(BOARDTYPE_MOKUTEKI,
		D3DXVECTOR3(1940.0f, 150.0f, 140.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		70.0f,
		140.0f);
}

//*****************************
// �{�[�h�̔j��
//*****************************
void UninitSignboard(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffSignboard != NULL)
	{
		g_pVtxBuffSignboard->Release();
		g_pVtxBuffSignboard = NULL;
	}

	for (int nCnt = 0; nCnt < BOARDTYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_pVtxTexturSignboard[nCnt] != NULL)
		{
			g_pVtxTexturSignboard[nCnt]->Release();
			g_pVtxTexturSignboard[nCnt] = NULL;
		}
	}
}

//*****************************
// �{�[�h�̍X�V
//*****************************
void UpdateSignboard(void)
{
	if (KeyboardRepeat(DIK_I))
	{
		g_aSignboard[nSignBoardIdx].pos.z += 1.0f;
	}
	else if (KeyboardRepeat(DIK_K))
	{
		g_aSignboard[nSignBoardIdx].pos.z -= 1.0f;
	}

	if (KeyboardRepeat(DIK_J))
	{
		g_aSignboard[nSignBoardIdx].pos.x -= 1.0f;
	}
	else if (KeyboardRepeat(DIK_L))
	{
		g_aSignboard[nSignBoardIdx].pos.x += 1.0f;
	}

	if (KeyboardRepeat(DIK_U))
	{
		g_aSignboard[nSignBoardIdx].pos.y += 1.0f;
	}
	else if (KeyboardRepeat(DIK_O))
	{
		g_aSignboard[nSignBoardIdx].pos.y -= 1.0f;
	}

	if (KeyboardTrigger(DIK_M))
	{
		nSignBoardIdx++;

		if (nSignBoardIdx >= BOARDTYPE_MAX)
		{
			nSignBoardIdx = 0;
		}
	}
}

//*****************************
// �{�[�h�̕`��
//*****************************
void DrawSignboard(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 254);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntBoard = 0; nCntBoard < BOARDTYPE_MAX; nCntBoard++)
	{
		if (g_aSignboard[nCntBoard].bUse == true)
		{// �g���Ă���
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aSignboard[nCntBoard].mtxWorld);

			// �r���[�}�g���b�N�X�擾
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// �J�����̋t�s���ݒ�
			g_aSignboard[nCntBoard].mtxWorld._11 = mtxview._11;
			g_aSignboard[nCntBoard].mtxWorld._12 = mtxview._21;
			g_aSignboard[nCntBoard].mtxWorld._13 = mtxview._31;
			g_aSignboard[nCntBoard].mtxWorld._21 = mtxview._12;
			g_aSignboard[nCntBoard].mtxWorld._22 = mtxview._22;
			g_aSignboard[nCntBoard].mtxWorld._23 = mtxview._32;
			g_aSignboard[nCntBoard].mtxWorld._31 = mtxview._13;
			g_aSignboard[nCntBoard].mtxWorld._32 = mtxview._23;
			g_aSignboard[nCntBoard].mtxWorld._33 = mtxview._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aSignboard[nCntBoard].pos.x, g_aSignboard[nCntBoard].pos.y, g_aSignboard[nCntBoard].pos.z);
			D3DXMatrixMultiply(&g_aSignboard[nCntBoard].mtxWorld, &g_aSignboard[nCntBoard].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aSignboard[nCntBoard].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffSignboard, 0, sizeof(VERTEX_3D));

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pVtxTexturSignboard[g_aSignboard[nCntBoard].type]);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �{�[�h�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBoard, 2);
		}
	}

	// �A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//*****************************
// �{�[�h�̐ݒ�
//*****************************
void SetSignBoard(BOARDTYPE type,D3DXVECTOR3 pos,D3DXCOLOR col,float fWidth,float fHeight)
{

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffSignboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBoard = 0; nCntBoard < BOARDTYPE_MAX; nCntBoard++)
	{
		if (g_aSignboard[nCntBoard].bUse == false)
		{
			g_aSignboard[nCntBoard].pos = pos;
			g_aSignboard[nCntBoard].col = col;
			g_aSignboard[nCntBoard].fHeight = fHeight;
			g_aSignboard[nCntBoard].fWidth = fWidth;
			g_aSignboard[nCntBoard].type = type;
			g_aSignboard[nCntBoard].bUse = true;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = -fWidth;
			pVtx[0].pos.y = fHeight;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = fWidth;
			pVtx[1].pos.y = fHeight;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = -fWidth;
			pVtx[2].pos.y = -fHeight;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = fWidth;
			pVtx[3].pos.y = -fHeight;
			pVtx[3].pos.z = 0.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffSignboard->Unlock();
}

//*****************************
// �{�[�h�̐ݒ�
//*****************************
SIGNBOARD* GetSignBoard(void)
{
	return &g_aSignboard[0];
}

int GetSignBoardContllore(void)
{
	return nSignBoardIdx;
}