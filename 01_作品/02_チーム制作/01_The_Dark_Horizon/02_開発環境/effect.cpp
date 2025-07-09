#include "effect.h"
#include "camera.h"
#include "shadow.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_aPVtxTexturEffect[EFFECT_TEXTURETYPE_MAX] = {};	// �e�N�X�`���̃|�C���^
EFFECT g_aEffect[MAX_EFFECT];											// �G�t�F�N�g

//**************************************
// �G�t�F�N�g�̏�����
//**************************************
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect, NULL);

	VERTEX_3D* pVtx = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\shadow\\shadow000.jpg",
		&g_aPVtxTexturEffect[EFFECT_TEXTURETYPE_NOMAL]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\effect\\smoke000.png",
		&g_aPVtxTexturEffect[EFFECT_TEXTURETYPE_SMOKE]);

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].type = EFFECTTYPE_NOMAL;					// �^�C�v
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
		g_aEffect[nCntEffect].gravity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �d��
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);		// �F
		g_aEffect[nCntEffect].nLife = 0;								// ����
		g_aEffect[nCntEffect].nMaxLife = 0;								// �����̍ő吔
		g_aEffect[nCntEffect].nCntAmin = 0;								// �A�j���[�V�����J�E���^�[
		g_aEffect[nCntEffect].nCntPttern = 0;							// �A�j���[�V�����p�^�[��
		g_aEffect[nCntEffect].fSize = 0;								// �傫��
		g_aEffect[nCntEffect].bUse = false;								// �g���Ă܂����H
		g_aEffect[nCntEffect].bShadow = false;							// �e����܂����H
		g_aEffect[nCntEffect].bSubtractive = true;						// ���Z����

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
	g_pVtxBuffEffect->Unlock();
}

//*****************************
// �G�t�F�N�g�̔j��
//*****************************
void UninitEffect(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

	for (int nCnt = 0; nCnt < EFFECT_TEXTURETYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_aPVtxTexturEffect[nCnt] != NULL)
		{
			g_aPVtxTexturEffect[nCnt]->Release();
			g_aPVtxTexturEffect[nCnt] = NULL;
		}
	}
}

//*****************************
// �G�t�F�N�g�̍X�V
//*****************************
void UpdateEffect(void)
{

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{

			switch (g_aEffect[nCntEffect].type)
			{
			case EFFECTTYPE_NOMAL:		// �ʏ�
				break;

			case EFFECTTYPE_TRAJECTORY:	// �O��
				UpdateEffectTrajectory(nCntEffect, pVtx);
				break;

			case EFFECTTYPE_SMOKE:		// ��
				UpdateEffectSmoke(nCntEffect, pVtx);
				break;

			default:
				break;
			}

			if (g_aEffect[nCntEffect].bShadow)
			{// �e����܂�����,�e�̈ʒu�X�V
				SetPositionShadow(g_aEffect[nCntEffect].nShadowIdx, g_aEffect[nCntEffect].pos);
			}
			
			if (g_aEffect[nCntEffect].nLife <= 0)
			{// �������Ȃ��Ȃ�����,�g�p��Ԃ�����
				g_aEffect[nCntEffect].bUse = false;

				if (g_aEffect[nCntEffect].bShadow)
				{// �e������Ȃ��,�e������
					EndShadow(g_aEffect[nCntEffect].nShadowIdx);
				}
			}
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//*****************************
// �G�t�F�N�g�̕`��
//*****************************
void DrawEffect(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Z�̔�r���@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// Z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	for (int nCntEX = 0; nCntEX < MAX_EFFECT; nCntEX++)
	{
		if (g_aEffect[nCntEX].bUse == true)
		{// �g���Ă���

			

			if (g_aEffect[nCntEX].bSubtractive == false)
			{// ���Z������������
				// ���Z�����̐ݒ�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}

			switch (g_aEffect[nCntEX].type)
			{// �^�C�v�ɂ���Ē���e�N�X�`����ς���

			case EFFECTTYPE_SMOKE:		// ��
				//���u�����f�B���O�����ɖ߂�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				break;
			}

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCntEX].mtxWorld);

			// �r���[�}�g���b�N�X�擾
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// �J�����̋t�s���ݒ�
			g_aEffect[nCntEX].mtxWorld._11 = mtxview._11;
			g_aEffect[nCntEX].mtxWorld._12 = mtxview._21;
			g_aEffect[nCntEX].mtxWorld._13 = mtxview._31;
			g_aEffect[nCntEX].mtxWorld._21 = mtxview._12;
			g_aEffect[nCntEX].mtxWorld._22 = mtxview._22;
			g_aEffect[nCntEX].mtxWorld._23 = mtxview._32;
			g_aEffect[nCntEX].mtxWorld._31 = mtxview._13;
			g_aEffect[nCntEX].mtxWorld._32 = mtxview._23;
			g_aEffect[nCntEX].mtxWorld._33 = mtxview._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEX].pos.x, g_aEffect[nCntEX].pos.y, g_aEffect[nCntEX].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEX].mtxWorld, &g_aEffect[nCntEX].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEX].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			switch (g_aEffect[nCntEX].type)
			{// �^�C�v�ɂ���Ē���e�N�X�`����ς���
			case EFFECTTYPE_NOMAL:		// �ʏ�
				pDevice->SetTexture(0, g_aPVtxTexturEffect[EFFECT_TEXTURETYPE_NOMAL]);
				break;

			case EFFECTTYPE_TRAJECTORY:	// �O��
				pDevice->SetTexture(0, g_aPVtxTexturEffect[EFFECT_TEXTURETYPE_NOMAL]);
				break;

			case EFFECTTYPE_SMOKE:		// ��
				pDevice->SetTexture(0, g_aPVtxTexturEffect[EFFECT_TEXTURETYPE_SMOKE]);
				break;

			default:
				pDevice->SetTexture(0, g_aPVtxTexturEffect[EFFECT_TEXTURETYPE_NOMAL]);
				break;
			}

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �G�t�F�N�g�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEX, 2);

			switch (g_aEffect[nCntEX].type)
			{// �^�C�v�ɂ���Ē���e�N�X�`����ς���

			case EFFECTTYPE_SMOKE:		// ��
				// ���Z�����ɖ߂�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;
			}

			if (g_aEffect[nCntEX].bSubtractive == false)
			{// ���Z������������
				// ���Z�����ɐݒ�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}
		}
	}

	// Z�̔�r���@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// Z�o�b�t�@�ɏ�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//*****************************
// �G�t�F�N�g�̐ݒ�
//*****************************
void SetEffect(EFFECTTYPE effectType,D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 gravity, D3DXCOLOR col,int nLife, float fSize,bool bShadow,bool bSubtractive)
{
	VERTEX_3D* pVtx = NULL;
	int nCntEffect = 0;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse)
		{
			pVtx += 4;
			continue;
		}

		g_aEffect[nCntEffect].type = effectType;	// �^�C�v
		g_aEffect[nCntEffect].pos = pos;			// �ʒu
		g_aEffect[nCntEffect].move = move;			// �ړ���
		g_aEffect[nCntEffect].gravity = gravity;	// �d��
		g_aEffect[nCntEffect].col = col;			// �F
		g_aEffect[nCntEffect].nLife = nLife;		// ����
		g_aEffect[nCntEffect].nMaxLife = nLife;		// �����̍ő吔
		g_aEffect[nCntEffect].nCntAmin = 0;			// �A�j���[�V�����J�E���^�[
		g_aEffect[nCntEffect].nCntPttern = 0;		// �A�j���[�V�����p�^�[��
		g_aEffect[nCntEffect].fSize = fSize;		// �傫��
		g_aEffect[nCntEffect].bUse = true;			// �g���Ă܂����H
		g_aEffect[nCntEffect].bShadow = bShadow;	// �e����܂����H
		g_aEffect[nCntEffect].bSubtractive = bSubtractive;	// �e����܂����H

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = -fSize;
		pVtx[0].pos.y = fSize;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = fSize;
		pVtx[1].pos.y = fSize;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = -fSize;
		pVtx[2].pos.y = -fSize;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = fSize;
		pVtx[3].pos.y = -fSize;
		pVtx[3].pos.z = 0.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = col;
		pVtx[1].col = col;
		pVtx[2].col = col;
		pVtx[3].col = col;

		// �e�N�X�`�����W�̐ݒ�
		switch (effectType)
		{// �^�C�v�ɂ���ĕ�����
		case EFFECTTYPE_NOMAL:
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			break;

		case EFFECTTYPE_TRAJECTORY:
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			break;

		case EFFECTTYPE_SMOKE:
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);
			break;

		default:
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			break;
		}

		if (bShadow)
		{// �e��ݒ肷��Ȃ��
			g_aEffect[nCntEffect].nShadowIdx = SetShadw(pos,D3DXVECTOR3(0.0f,0.0f,0.0f),fSize);
		}

		break;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//*****************************
// �O�ՃG�t�F�N�g�̍X�V
//*****************************
void UpdateEffectTrajectory(int nCntEffect, VERTEX_3D* pVtx)
{
	g_aEffect[nCntEffect].nLife--;	// �������炷
	float fMagu = (float)g_aEffect[nCntEffect].nLife / (float)g_aEffect[nCntEffect].nMaxLife;	// �����̂̔{�������߂�

	float fSizeEX = g_aEffect[nCntEffect].fSize * fMagu;	// �傫���ɔ{����������

	D3DXCOLOR colEX = g_aEffect[nCntEffect].col;	// �v�Z��̐F 
	colEX.r *= fMagu * fMagu * fMagu;	// �F�����炷
	colEX.g *= fMagu * fMagu * fMagu;	// �F�����炷
	colEX.b *= fMagu * fMagu * fMagu;	// �F�����炷
	colEX.a *= fMagu * fMagu * fMagu;	// �F�����炷

	D3DXVECTOR3 move;
	g_aEffect[nCntEffect].move += g_aEffect[nCntEffect].gravity;
	move.x = g_aEffect[nCntEffect].move.x * fMagu;
	move.y = g_aEffect[nCntEffect].move.y * fMagu;
	move.z = g_aEffect[nCntEffect].move.z * fMagu;

	// �ړ��ʒǉ�
	g_aEffect[nCntEffect].pos += move;

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = -fSizeEX;
	pVtx[0].pos.y = fSizeEX;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = fSizeEX;
	pVtx[1].pos.y = fSizeEX;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -fSizeEX;
	pVtx[2].pos.y = -fSizeEX;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = fSizeEX;
	pVtx[3].pos.y = -fSizeEX;
	pVtx[3].pos.z = 0.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = colEX;
	pVtx[1].col = colEX;
	pVtx[2].col = colEX;
	pVtx[3].col = colEX;
}

//*****************************
// ���G�t�F�N�g�̍X�V
//*****************************
void UpdateEffectSmoke(int nCntEffect, VERTEX_3D* pVtx)
{
	g_aEffect[nCntEffect].nLife--;	// �������炷
	float fMagu = (float)g_aEffect[nCntEffect].nLife / (float)g_aEffect[nCntEffect].nMaxLife;	// �����̂̔{�������߂�

	float fSizeEX = g_aEffect[nCntEffect].fSize * fMagu;	// �傫���ɔ{����������

	D3DXCOLOR colEX = g_aEffect[nCntEffect].col;	// �v�Z��̐F 
	colEX.r *= fMagu * fMagu * fMagu;	// �F�����炷
	colEX.g *= fMagu * fMagu * fMagu;	// �F�����炷
	colEX.b *= fMagu * fMagu * fMagu;	// �F�����炷
	colEX.a *= fMagu * fMagu * fMagu;	// �F�����炷

	D3DXVECTOR3 move;
	g_aEffect[nCntEffect].move += g_aEffect[nCntEffect].gravity;
	move.x = g_aEffect[nCntEffect].move.x * fMagu;
	move.y = g_aEffect[nCntEffect].move.y * fMagu;
	move.z = g_aEffect[nCntEffect].move.z * fMagu;

	g_aEffect[nCntEffect].nCntAmin++;

	if (g_aEffect[nCntEffect].nCntAmin >= 10)
	{// ��萔�J�E���g������
		g_aEffect[nCntEffect].nCntAmin = 0;	// �J�E���^�[���Z�b�g
		g_aEffect[nCntEffect].nCntPttern++;

		if (g_aEffect[nCntEffect].nCntPttern > 8)
		{// �p�^�[��������𒴂�����[��
			g_aEffect[nCntEffect].nCntPttern = 0;
		}
	}

	// �ړ��ʒǉ�
	g_aEffect[nCntEffect].pos += move;

	// ���_���W�̐ݒ�
	pVtx[0].pos.x = -fSizeEX;
	pVtx[0].pos.y = fSizeEX;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = fSizeEX;
	pVtx[1].pos.y = fSizeEX;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -fSizeEX;
	pVtx[2].pos.y = -fSizeEX;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = fSizeEX;
	pVtx[3].pos.y = -fSizeEX;
	pVtx[3].pos.z = 0.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = colEX;
	pVtx[1].col = colEX;
	pVtx[2].col = colEX;
	pVtx[3].col = colEX;

	// �e�N�X�`�����W�̐ݒ�
	float fTexXA = 0.125f * (float)g_aEffect[nCntEffect].nCntPttern;
	float fTexXB = 0.125f + 0.125f * (float)g_aEffect[nCntEffect].nCntPttern;
	pVtx[0].tex = D3DXVECTOR2(fTexXA, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fTexXB, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fTexXA, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexXB, 1.0f);
}