#include "HPGauge.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHPGauge = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apVtxTexturHPGauge[HPGAUGETYPE_MAX] = {};	// �e�N�X�`���̃|�C���^
HPGAUGE g_aHPGauge[MAX_HPGAUGE_POLIGON];	// hp�Q�[�W���

//*****************************************************
// HP�Q�[�W������
//*****************************************************
void InitHPGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_HPGAUGE_POLIGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHPGauge, NULL);

	VERTEX_3D* pVtx = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\HPGauge_Frame_001.png",
		&g_apVtxTexturHPGauge[HPGAUGETYPE_BG]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\HPGauge_Bar_001.png",
		&g_apVtxTexturHPGauge[HPGAUGETYPE_GAUGE]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\HPGauge_Bar_001.png",
		&g_apVtxTexturHPGauge[HPGAUGETYPE_GAUGE_REDZONE]);


	// ���_�o�b�t�@�����b�N
	g_pVtxBuffHPGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBl = 0; nCntBl < MAX_HPGAUGE_POLIGON; nCntBl++)
	{
		g_aHPGauge[nCntBl].pos = D3DXVECTOR3(1.0f,1.0f,1.0f);		// �ʒu
		g_aHPGauge[nCntBl].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);	// �F
		g_aHPGauge[nCntBl].type = HPGAUGETYPE_MAX;		// ���
		g_aHPGauge[nCntBl].nIdxUI = -1;					// �C���f�b�N�X
		g_aHPGauge[nCntBl].fMaxWidth = 0.0f;			// �ő�̂��������@
		g_aHPGauge[nCntBl].fWidth = 0.0f;				// ��
		g_aHPGauge[nCntBl].fHeight = 0.0f;				// ����
		g_aHPGauge[nCntBl].bUse = false;				// �g���Ă܂���

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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffHPGauge->Unlock();
}

//*****************************************************
// HP�Q�[�W�I��
//*****************************************************
void UninitHPGauge(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffHPGauge != NULL)
	{
		g_pVtxBuffHPGauge->Release();
		g_pVtxBuffHPGauge = NULL;
	}

	for (int nCnt = 0; nCnt < HPGAUGETYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_apVtxTexturHPGauge[nCnt] != NULL)
		{
			g_apVtxTexturHPGauge[nCnt]->Release();
			g_apVtxTexturHPGauge[nCnt] = NULL;
		}
	}
}

//*****************************************************
// HP�Q�[�W�X�V
//*****************************************************
void UpdateHPGauge(void)
{

}

//*****************************************************
// HP�Q�[�W�\��
//*****************************************************
void DrawHPGauge(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntBl = 0; nCntBl < MAX_HPGAUGE_POLIGON; nCntBl++)
	{
		if (g_aHPGauge[nCntBl].bUse == true)
		{// �g���Ă���
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aHPGauge[nCntBl].mtxWorld);

			// �r���[�}�g���b�N�X�擾
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// �J�����̋t�s���ݒ�
			g_aHPGauge[nCntBl].mtxWorld._11 = mtxview._11;
			g_aHPGauge[nCntBl].mtxWorld._12 = mtxview._21;
			g_aHPGauge[nCntBl].mtxWorld._13 = mtxview._31;
			g_aHPGauge[nCntBl].mtxWorld._21 = mtxview._12;
			g_aHPGauge[nCntBl].mtxWorld._22 = mtxview._22;
			g_aHPGauge[nCntBl].mtxWorld._23 = mtxview._32;
			g_aHPGauge[nCntBl].mtxWorld._31 = mtxview._13;
			g_aHPGauge[nCntBl].mtxWorld._32 = mtxview._23;
			g_aHPGauge[nCntBl].mtxWorld._33 = mtxview._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aHPGauge[nCntBl].pos.x, g_aHPGauge[nCntBl].pos.y, g_aHPGauge[nCntBl].pos.z);
			D3DXMatrixMultiply(&g_aHPGauge[nCntBl].mtxWorld, &g_aHPGauge[nCntBl].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aHPGauge[nCntBl].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffHPGauge, 0, sizeof(VERTEX_3D));

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apVtxTexturHPGauge[g_aHPGauge[nCntBl].type]);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBl, 2);
		}
	}

	// �A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//*****************************************************
// HP�Q�[�W�̐ݒ�
//*****************************************************
void SetHPGauge(HPGAUGE_HAVE* pHPGaugeHave, HPGAUGETYPE type, D3DXCOLOR col,float fHeight,float fWidth,int nMaxHP)
{
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffHPGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHP = 0; nCntHP < MAX_HPGAUGE_POLIGON; nCntHP++)
	{// �}�b�N�X����
		if (g_aHPGauge[nCntHP].bUse == false)
		{// �g���ĂȂ�������
			pHPGaugeHave->type = type;
			pHPGaugeHave->nIdxUI = nCntHP;
			pHPGaugeHave->nMaxHP = nMaxHP;

			g_aHPGauge[nCntHP].bUse = true;
			g_aHPGauge[nCntHP].nIdxUI = nCntHP;
			g_aHPGauge[nCntHP].type = type;
			g_aHPGauge[nCntHP].col = col;
			g_aHPGauge[nCntHP].fMaxWidth = fWidth;
			g_aHPGauge[nCntHP].fWidth = fWidth;
			g_aHPGauge[nCntHP].fHeight = fHeight;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = 0.0f;
			pVtx[0].pos.y = fHeight;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = fWidth;
			pVtx[1].pos.y = fHeight;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = 0.0f;
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
			break;
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffHPGauge->Unlock();
}

//*****************************************************
// HP�Q�[�W�̈ʒu�X�V
//*****************************************************
void UpdateHPGaugePos(HPGAUGE_HAVE* pHPGaugeHave,D3DXVECTOR3 pos,float fHeigt,float fSlide)
{
	if (g_aHPGauge[pHPGaugeHave->nIdxUI].bUse == false)
	{// �g���ĂȂ���
		return;
	}

	// �ʒu�ݒ�
	g_aHPGauge[pHPGaugeHave->nIdxUI].pos.x = pos.x - fSlide;
	g_aHPGauge[pHPGaugeHave->nIdxUI].pos.y = pos.y + fHeigt;
	g_aHPGauge[pHPGaugeHave->nIdxUI].pos.z = pos.z;
}

//*****************************************************
// HP�Q�[�W�̒����X�V
//*****************************************************
void UpdateHPGaugeWidth(HPGAUGE_HAVE* pHPGaugeHave, int nowHP)
{
	if (pHPGaugeHave->type != HPGAUGETYPE_GAUGE)
	{// �Q�[�W����Ȃ���
		return;
	}

	if (g_aHPGauge[pHPGaugeHave->nIdxUI].bUse == false)
	{// �g���ĂȂ���
		return;
	}

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffHPGauge->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * pHPGaugeHave->nIdxUI;

	float fMagu = (float)nowHP / (float)pHPGaugeHave->nMaxHP;

	if (fMagu > 1.0f)
	{
		fMagu = 1.0f;
	}

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = -0.0f;
	pVtx[0].pos.y = g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth * fMagu;
	pVtx[1].pos.y = g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = -g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth * fMagu;
	pVtx[3].pos.y = -g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[3].pos.z = 0.0f;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffHPGauge->Unlock();
}

//*****************************************************
// HP�̐ԃQ�[�W�̒����X�V
//*****************************************************
void UpdateHPGaugeRedZoneWidth(HPGAUGE_HAVE* pHPGaugeHave, int nowHP)
{
	if (pHPGaugeHave->type != HPGAUGETYPE_GAUGE_REDZONE)
	{// �ԃQ�[�W����Ȃ���
		return;
	}
	
	if (g_aHPGauge[pHPGaugeHave->nIdxUI].bUse == false)
	{// �g���ĂȂ���
		return;
	}

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffHPGauge->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * pHPGaugeHave->nIdxUI;
	float fMagu = (float)nowHP / (float)pHPGaugeHave->nMaxHP;

	if (fMagu > 1.0f)
	{
		fMagu = 1.0f;
	}

	float fWidthEX = g_aHPGauge[pHPGaugeHave->nIdxUI].fMaxWidth * fMagu;
	float fDiffWidth = g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth - fWidthEX;

	g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth -= fDiffWidth * 0.01f;

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth;
	pVtx[1].pos.y = g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = -g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth;
	pVtx[3].pos.y = -g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[3].pos.z = 0.0f;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffHPGauge->Unlock();
}

//*****************************************************
// �Q�[�W�̒����X�V
//*****************************************************
void UpdateGaugeWidth(HPGAUGE_HAVE* pHPGaugeHave, int nNowNum,bool bOrver)
{
	if (g_aHPGauge[pHPGaugeHave->nIdxUI].bUse == false)
	{// �g���ĂȂ���
		return;
	}

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffHPGauge->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * pHPGaugeHave->nIdxUI;

	float fMagu = (float)nNowNum / (float)pHPGaugeHave->nMaxHP;

	if (fMagu >= 1.0f && bOrver == true)
	{// �I�[�o�[������_��
		fMagu = 1.0f;
	}

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth * fMagu;
	pVtx[1].pos.y = g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = -g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth * fMagu;
	pVtx[3].pos.y = -g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[3].pos.z = 0.0f;

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffHPGauge->Unlock();
}

//*****************************************************
// �Q�[�W�̏I���
//*****************************************************
void EndHPGauge(HPGAUGE_HAVE* pHPGaugeHave)
{
	g_aHPGauge[pHPGaugeHave->nIdxUI].bUse = false;
}
