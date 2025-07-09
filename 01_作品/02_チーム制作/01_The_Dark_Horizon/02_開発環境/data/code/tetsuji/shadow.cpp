#include "shadow.h"
#include "block.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pVtxTexturShadow = NULL;		// �e�N�X�`���̃|�C���^
Shadow g_aShadow[MAX_SHADOW];						// �e�̏��

//**************************************
// �e�̏�����
//**************************************
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow, NULL);

	VERTEX_3D* pVtx = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\shadow\\shadow000.jpg",
		&g_pVtxTexturShadow);

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aShadow[nCntShadow].col = D3DXCOLOR(1.0f, 1.0f, 1.0, 1.0f);
		g_aShadow[nCntShadow].branding = false;
		g_aShadow[nCntShadow].bUse = false;

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
		pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_aShadow[nCntShadow].col;
		pVtx[1].col = g_aShadow[nCntShadow].col;
		pVtx[2].col = g_aShadow[nCntShadow].col;
		pVtx[3].col = g_aShadow[nCntShadow].col;

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();
}

//**************************************************************************************
// �e�̔j��
//**************************************************************************************
void UninitShadow(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pVtxTexturShadow != NULL)
	{
		g_pVtxTexturShadow->Release();
		g_pVtxTexturShadow = NULL;
	}
}

//**************************************************************************************
// �e�̍X�V
//**************************************************************************************
void UpdateShadow(void)
{

}

//**************************************************************************************
// �e�̕`��
//**************************************************************************************
void DrawShadow(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true && g_aShadow[nCntShadow].branding == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pVtxTexturShadow);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntShadow,
				2);
		}
	}

	// �A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �ݒ�������ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//**************************************************************************************
// �e�̐ݒ�
//**************************************************************************************
int SetShadw(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float fWidth)
{
	int nCntShadow = 0;

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].bUse = true;
			g_aShadow[nCntShadow].fWidth = fWidth;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = -fWidth;
			pVtx[0].pos.y = pos.y;
			pVtx[0].pos.z = fWidth;

			pVtx[1].pos.x = fWidth;
			pVtx[1].pos.y = pos.y;
			pVtx[1].pos.z = fWidth;

			pVtx[2].pos.x = -fWidth;
			pVtx[2].pos.y = pos.y;
			pVtx[2].pos.z = -fWidth;

			pVtx[3].pos.x = fWidth;
			pVtx[3].pos.y = pos.y;
			pVtx[3].pos.z = -fWidth;

			break;
		}

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;
}

//**************************************************************************************
// �e�̈ʒu�̍X�V����
//**************************************************************************************
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	VERTEX_3D* pVtx = NULL;
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXCOLOR col = g_aShadow[nIdxShadow].col;
	float fMaguA;
	float fMaguB;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nIdxShadow;

	g_aShadow[nIdxShadow].pos.x = pos.x;
	g_aShadow[nIdxShadow].pos.y -= 30.0f;
	g_aShadow[nIdxShadow].pos.z = pos.z;

	g_aShadow[nIdxShadow].branding = false;	// ����ĂȂ�

	if (CollisionBlock(&g_aShadow[nIdxShadow].pos, &pos, &move))
	{
		g_aShadow[nIdxShadow].branding = true;	// ����Ă�
		fMaguA = pos.y / g_aShadow[nIdxShadow].pos.y * 0.9f;
		fMaguB = g_aShadow[nIdxShadow].pos.y / pos.y;

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = -g_aShadow[nIdxShadow].fWidth * fMaguA;
		pVtx[0].pos.y = 0.1f;
		pVtx[0].pos.z = g_aShadow[nIdxShadow].fWidth * fMaguA;

		pVtx[1].pos.x = g_aShadow[nIdxShadow].fWidth * fMaguA;
		pVtx[1].pos.y = 0.1f;
		pVtx[1].pos.z = g_aShadow[nIdxShadow].fWidth * fMaguA;

		pVtx[2].pos.x = -g_aShadow[nIdxShadow].fWidth * fMaguA;
		pVtx[2].pos.y = 0.1f;
		pVtx[2].pos.z = -g_aShadow[nIdxShadow].fWidth * fMaguA;

		pVtx[3].pos.x = g_aShadow[nIdxShadow].fWidth * fMaguA;
		pVtx[3].pos.y = 0.1f;
		pVtx[3].pos.z = -g_aShadow[nIdxShadow].fWidth * fMaguA;

		col.r = g_aShadow[nIdxShadow].col.r * fMaguB;
		col.g = g_aShadow[nIdxShadow].col.g * fMaguB;
		col.b = g_aShadow[nIdxShadow].col.b * fMaguB;
		col.a = g_aShadow[nIdxShadow].col.a * fMaguB;

		if (col.a <= 0.1f)
		{
			col.a = 0.0f;
		}

		// ���_�J���[�̐ݒ�
		pVtx[0].col = col;
		pVtx[1].col = col;
		pVtx[2].col = col;
		pVtx[3].col = col;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();
}

//**************************************************************************************
// �e�̈ʒu�̍X�V����
//**************************************************************************************
void EndShadow(int nIdxShadow)
{
	g_aShadow[nIdxShadow].bUse = false;
}