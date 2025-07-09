#include "bullet.h"
#include "camera.h"
#include "explosion.h"
#include "effect.h"
#include "player.h"
#include "enemy.h"
#include "collision.h"
#include "shadow.h"
#include "particle.h"
#include "sound.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pVtxTexturBullet[BULLETTYPE_MAX] = {};		// �e�N�X�`���̃|�C���^
BULLET g_aBullet[MAX_BULLET];									// �e

//**************************************
// �e�̏�����
//**************************************
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet, NULL);

	VERTEX_3D* pVtx = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_BULLET_SNOW,
		&g_pVtxTexturBullet[BULLETTYPE_SNOW]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_BULLET_SNOW,
		&g_pVtxTexturBullet[BULLETTYPE_SNOW_MEDIUM]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_BULLET_SNOW,
		&g_pVtxTexturBullet[BULLETTYPE_SNOW_BIG]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_BULLET_ICE,
		&g_pVtxTexturBullet[BULLETTYPE_ICE]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_BULLET_GRAVEL,
		&g_pVtxTexturBullet[BULLETTYPE_GRAVEL]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_BULLET_GRAVEL,
		&g_pVtxTexturBullet[BULLETTYPE_GRAVEL_DIFFUSION]);

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		g_aBullet[nCntBl].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBl].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBl].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBl].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBl].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBl].nType = BULLETTYPE_MAX;
		g_aBullet[nCntBl].fLife = 0.0f;
		g_aBullet[nCntBl].bUse = false;

		g_aBullet[nCntBl].fWidth = 0.0f;

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
	g_pVtxBuffBullet->Unlock();
}

//*****************************
// �e�̔j��
//*****************************
void UninitBullet(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	for (int nCnt = 0; nCnt < BULLETTYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_pVtxTexturBullet[nCnt] != NULL)
		{
			g_pVtxTexturBullet[nCnt]->Release();
			g_pVtxTexturBullet[nCnt] = NULL;
		}
	}
}

//*****************************
// �e�̍X�V
//*****************************
void UpdateBullet(void)
{
	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		if (g_aBullet[nCntBl].bUse == true)
		{

			g_aBullet[nCntBl].posOld = g_aBullet[nCntBl].pos;

			switch (g_aBullet[nCntBl].nType)
			{
			case BULLETTYPE_SNOW:	// ��ʏ���
				SnowBall(nCntBl);
				break;

			case BULLETTYPE_SNOW_MEDIUM:	// ��ʒ�����
				SnowBallMidium(nCntBl);
				break;

			case BULLETTYPE_SNOW_BIG:	// ��ʑ又��
				SnowBallBig(nCntBl);
				break;

			case BULLETTYPE_ICE:	// �X�ʏ���
				IceBall(nCntBl);
				break;

			case BULLETTYPE_GRAVEL:	// �����ʏ���
				GravelBall(nCntBl);
				break;

			case BULLETTYPE_GRAVEL_DIFFUSION:	// �g�U�����ʏ���
				GravelBallDiffusion(nCntBl);
				break;
			}

			// �e�̈ʒu�X�V
			SetPositionShadow(g_aBullet[nCntBl].nShadowIdx, g_aBullet[nCntBl].pos);
		}
	}
}

//*****************************
// �e�̕`��
//*****************************
void DrawBullet(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,254);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		if (g_aBullet[nCntBl].bUse == true)
		{// �g���Ă���
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBullet[nCntBl].mtxWorld);

			// �r���[�}�g���b�N�X�擾
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// �J�����̋t�s���ݒ�
			g_aBullet[nCntBl].mtxWorld._11 = mtxview._11;
			g_aBullet[nCntBl].mtxWorld._12 = mtxview._21;
			g_aBullet[nCntBl].mtxWorld._13 = mtxview._31;
			g_aBullet[nCntBl].mtxWorld._21 = mtxview._12;
			g_aBullet[nCntBl].mtxWorld._22 = mtxview._22;
			g_aBullet[nCntBl].mtxWorld._23 = mtxview._32;
			g_aBullet[nCntBl].mtxWorld._31 = mtxview._13;
			g_aBullet[nCntBl].mtxWorld._32 = mtxview._23;
			g_aBullet[nCntBl].mtxWorld._33 = mtxview._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBl].pos.x, g_aBullet[nCntBl].pos.y, g_aBullet[nCntBl].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBl].mtxWorld, &g_aBullet[nCntBl].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBl].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pVtxTexturBullet[g_aBullet[nCntBl].nType]);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBl, 2);
		}
	}

	// �A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//*****************************
// �e�̐ݒ�
//*****************************
void SetBullet(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int nBlType)
{
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		if (nBlType == -1)
		{// �^�C�v�Ȃ���������Ȃ�
			break;
		}

		if (g_aBullet[nCntBl].bUse == false)
		{
			float fSize = 10.0f;

			g_aBullet[nCntBl].pos.x = pos.x;
			g_aBullet[nCntBl].pos.y = pos.y;
			g_aBullet[nCntBl].pos.z = pos.z;

			g_aBullet[nCntBl].dir = rot;
			g_aBullet[nCntBl].nType = nBlType;
			
			g_aBullet[nCntBl].fWidth = fSize;

			g_aBullet[nCntBl].bUse = true;

			switch (nBlType)
			{
			case BULLETTYPE_SNOW:	// ���
				g_aBullet[nCntBl].move.x = sinf(rot.y) * BULLET_SPEED;
				g_aBullet[nCntBl].move.y = 2.0f;
				g_aBullet[nCntBl].move.z = cosf(rot.y) * BULLET_SPEED;
				g_aBullet[nCntBl].fLife = 120;
				break;

			case BULLETTYPE_SNOW_MEDIUM:	// ����
				g_aBullet[nCntBl].move.x = sinf(rot.y) * BULLET_SPEED * 0.5f;
				g_aBullet[nCntBl].move.y = 5.0f;
				g_aBullet[nCntBl].move.z = cosf(rot.y) * BULLET_SPEED * 0.5f;
				g_aBullet[nCntBl].fLife = 180;
				fSize *= 1.5f;
				g_aBullet[nCntBl].fWidth = fSize;
				break;

			case BULLETTYPE_SNOW_BIG:	// ���
				g_aBullet[nCntBl].move.x = sinf(rot.y) * BULLET_SPEED * 0.5f;
				g_aBullet[nCntBl].move.y = 0.0f;
				g_aBullet[nCntBl].move.z = cosf(rot.y) * BULLET_SPEED * 0.5f;
				g_aBullet[nCntBl].fLife = 240;
				g_aBullet[nCntBl].pos.y = pos.y + 20.0f;
				fSize *= 2.0f;
				g_aBullet[nCntBl].fWidth = fSize;
				break;

			case BULLETTYPE_ICE:	// �X��
				g_aBullet[nCntBl].move.x = sinf(rot.y) * BULLET_SPEED;
				g_aBullet[nCntBl].move.y = 2.0f;
				g_aBullet[nCntBl].move.z = cosf(rot.y) * BULLET_SPEED;
				g_aBullet[nCntBl].fLife = 120;
				break;

			case BULLETTYPE_GRAVEL:	// ������
				g_aBullet[nCntBl].move.x = sinf(rot.y) * 2.0f;
				g_aBullet[nCntBl].move.y = BULLET_SPEED;
				g_aBullet[nCntBl].move.z = cosf(rot.y) * 2.0f;
				g_aBullet[nCntBl].fLife = 60;
				break;

			case BULLETTYPE_GRAVEL_DIFFUSION:	// �����ʊg�U�e
				float fAngle = (float)((rand() % 628 - 314) * 0.01f);
				g_aBullet[nCntBl].move.x = rot.x + sinf(fAngle) * (float)((rand() % 150 - 75) * 0.05f);
				g_aBullet[nCntBl].move.y = rot.y;
				g_aBullet[nCntBl].move.z = rot.z + cosf(fAngle) * (float)((rand() % 150 - 75) * 0.05f);
				g_aBullet[nCntBl].fLife = 120;
				fSize *= 0.5f;
				g_aBullet[nCntBl].fWidth = fSize;
				break;
			}

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

			// �e�ݒ�
			g_aBullet[nCntBl].nShadowIdx = SetShadw(g_aBullet[nCntBl].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fSize);

			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//*****************************
// ��ʏ����̐ݒ�
//*****************************
void SnowBall(int nCntBl)
{
	ENEMY* pEnemy = GetEnemy();	// �G�l�~�[�擾

	g_aBullet[nCntBl].move.y -= (float)BULLET_GRAVITY;

	g_aBullet[nCntBl].pos.x += g_aBullet[nCntBl].move.x;
	g_aBullet[nCntBl].pos.y += g_aBullet[nCntBl].move.y;
	g_aBullet[nCntBl].pos.z += g_aBullet[nCntBl].move.z;

	g_aBullet[nCntBl].fLife -= 1.0f;

	SetEffect(EFFECTTYPE_TRAJECTORY,		// �^�C�v
		g_aBullet[nCntBl].pos,				// �ʒu
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �ړ���
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �d��
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// �F
		30,									// ����
		20.0f,								// �傫��
		false,								// �e�̎d�l�L��
		true								// ���Z����
	);

	if (g_aBullet[nCntBl].fLife > 0)
	{
		if (CollisionBlock(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move) || g_aBullet[nCntBl].fLife <= 0.0f)
		{// �u���b�N�Ƃ̓����蔻��
			g_aBullet[nCntBl].bUse = false;

			// �����ݒ�
			SETEXPLO setExplo;
			setExplo.pos = g_aBullet[nCntBl].pos;
			setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);

			SetExplosion(setExplo);

			// �e�̏I��
			EndShadow(g_aBullet[nCntBl].nShadowIdx);


			D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
			D3DXVec3Normalize(&patiMove,&patiMove);

			// �p�[�e�B�N������
			SetParticle(EFFECTTYPE_TRAJECTORY,	// �^�C�v
				g_aBullet[nCntBl].pos,			// �ʒu
				patiMove,						// �d��
				D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// �F
				50,								// �o����
				60,								// ����
				5.0f,							// �傫��
				3.0f,							// ���x
				false,							// �e�̗L��
				true							// ���Z���������Z������
			);

			// ��ʂ����鉹
			PlaySound(SOUND_LABEL_SE_BREAKSNOWBALL);
		}

		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (g_aBullet[nCntBl].bUse == false)
			{// �e�g���ĂȂ�������
				break;
			}

			if (pEnemy->bUse == false)
			{// �G�g���ĂȂ�������
				continue;
			}

			for (int nCntPosi = 0; nCntPosi < pEnemy->charParam.nNumModel; nCntPosi++)
			{
				if (CollisionSphere(&g_aBullet[nCntBl].pos, &pEnemy->aColiPoint[nCntPosi].pos, g_aBullet[nCntBl].fWidth, pEnemy->aColiPoint[nCntPosi].fRadius + 20, false))
				{// �G�̊e�p�[�c�̓����蔻��
					g_aBullet[nCntBl].bUse = false;

					// �����ݒ�
					SETEXPLO setExplo;
					setExplo.pos = g_aBullet[nCntBl].pos;
					setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
					SetExplosion(setExplo);

					// �G�̃q�b�g����
					HitEnemy(nCntEnemy,BULLET_ATTACK_SNOW);

					// �e�̏I��
					EndShadow(g_aBullet[nCntBl].nShadowIdx);

					D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
					D3DXVec3Normalize(&patiMove, &patiMove);

					// �p�[�e�B�N������
					SetParticle(EFFECTTYPE_TRAJECTORY,	// �^�C�v
						g_aBullet[nCntBl].pos,			// �ʒu
						patiMove,						// �d��
						D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// �F
						50,								// �o����
						60,								// ����
						5.0f,							// �傫��
						3.0f,							// ���x
						false,							// �e�̗L��
						true							// ���Z���������Z������
					);

					// ��ʂ����鉹
					PlaySound(SOUND_LABEL_SE_BREAKSNOWBALL);

					break;
				}
			}
		}
	}
}

//*****************************
// ��ʒ������̐ݒ�
//*****************************
void SnowBallMidium(int nCntBl)
{
	ENEMY* pEnemy = GetEnemy();	// �G�l�~�[�擾

	g_aBullet[nCntBl].move.y -= (float)BULLET_GRAVITY;

	g_aBullet[nCntBl].pos.x += g_aBullet[nCntBl].move.x;
	g_aBullet[nCntBl].pos.y += g_aBullet[nCntBl].move.y;
	g_aBullet[nCntBl].pos.z += g_aBullet[nCntBl].move.z;

	g_aBullet[nCntBl].fLife -= 1.0f;

	SetEffect(EFFECTTYPE_TRAJECTORY,		// �^�C�v
		g_aBullet[nCntBl].pos,				// �ʒu
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �ړ���
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �d��
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// �F
		30,									// ����
		25.0f,								// �傫��
		false,								// �e�̎d�l�L��
		true								// ���Z����
	);

	if (g_aBullet[nCntBl].fLife > 0)
	{
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (g_aBullet[nCntBl].bUse == false)
			{// �e�g���ĂȂ�������	
				break;
			}

			if (pEnemy->bUse == false)
			{// �G�g���ĂȂ�������
				continue;
			}

			for (int nCntPosi = 0; nCntPosi < pEnemy->charParam.nNumModel; nCntPosi++)
			{
				if (CollisionSphere(&g_aBullet[nCntBl].pos, &pEnemy->aColiPoint[nCntPosi].pos, g_aBullet[nCntBl].fWidth, pEnemy->aColiPoint[nCntPosi].fRadius + 20, false))
				{// �G�̊e�p�[�c�̓����蔻��
					g_aBullet[nCntBl].bUse = false;

					// �����ݒ�
					SETEXPLO setExplo;
					setExplo.pos = g_aBullet[nCntBl].pos;
					setExplo.size = D3DXVECTOR3(40.0f, 40.0f, 0.0f);

					SetExplosion(setExplo);

					// �G�̃q�b�g����
					HitEnemy(nCntEnemy, BULLET_ATTACK_SNOW_MIDIUM);

					// �e�̏I��
					EndShadow(g_aBullet[nCntBl].nShadowIdx);

					D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
					D3DXVec3Normalize(&patiMove, &patiMove);

					// �p�[�e�B�N������
					SetParticle(EFFECTTYPE_TRAJECTORY,	// �^�C�v
						g_aBullet[nCntBl].pos,			// �ʒu
						patiMove,						// �d��
						D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// �F
						50,								// �o����
						60,								// ����
						10.0f,							// �傫��
						4.0f,							// ���x
						false,							// �e�̗L��
						true							// ���Z���������Z������
					);

					// ��ʂ����鉹
					PlaySound(SOUND_LABEL_SE_BREAKSNOWBALL_MIDI);

					break;
				}
			}
		}

		if (CollisionBlock(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move) || g_aBullet[nCntBl].fLife <= 0.0f)
		{// �u���b�N�Ƃ̓����蔻��
			g_aBullet[nCntBl].bUse = false;

			// �����ݒ�
			SETEXPLO setExplo;
			setExplo.pos = g_aBullet[nCntBl].pos;
			setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);

			SetExplosion(setExplo);

			// �e�̏I��
			EndShadow(g_aBullet[nCntBl].nShadowIdx);

			D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
			D3DXVec3Normalize(&patiMove, &patiMove);

			// �p�[�e�B�N������
			SetParticle(EFFECTTYPE_TRAJECTORY,	// �^�C�v
				g_aBullet[nCntBl].pos,			// �ʒu
				patiMove,						// �d��
				D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// �F
				50,								// �o����
				60,								// ����
				10.0f,							// �傫��
				4.0f,							// ���x
				false,							// �e�̗L��
				true							// ���Z���������Z������
			);

			// ��ʂ����鉹
			PlaySound(SOUND_LABEL_SE_BREAKSNOWBALL_MIDI);
		}
	}
}

//*****************************
// ��ʑ又���̐ݒ�
//*****************************
void SnowBallBig(int nCntBl)
{
	ENEMY* pEnemy = GetEnemy();	// �G�l�~�[�擾

	BLOCKCOLLISION blockColiision;

	g_aBullet[nCntBl].move.y -= (float)BULLET_GRAVITY;


	g_aBullet[nCntBl].pos.y += g_aBullet[nCntBl].move.y;
	blockColiision = CollisionBlockBullet(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move,20.0f);

	g_aBullet[nCntBl].pos.x += g_aBullet[nCntBl].move.x;
	blockColiision = CollisionBlockBullet(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move,20.0f);

	g_aBullet[nCntBl].pos.z += g_aBullet[nCntBl].move.z;
	blockColiision = CollisionBlockBullet(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move,20.0f);

	g_aBullet[nCntBl].fLife -= 1.0f;

	SetEffect(EFFECTTYPE_TRAJECTORY,		// �^�C�v
		g_aBullet[nCntBl].pos,				// �ʒu
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �ړ���
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �d��
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// �F
		30,									// ����
		30.0f,								// �傫��
		false,								// �e�̎d�l�L��
		true								// ���Z����
	);

	if (blockColiision.nHitfase == BLOCKFACETYPE_TOP)
	{// ��ʂɓ���������
		g_aBullet[nCntBl].pos.y += 10.0f;
	}

	if (blockColiision.nHitfase == BLOCKFACETYPE_SIDE || g_aBullet[nCntBl].fLife <= 0.0f)
	{// �ǂɓ������Ă���
		g_aBullet[nCntBl].bUse = false;

		// �����ݒ�
		SETEXPLO setExplo;
		setExplo.pos = g_aBullet[nCntBl].pos;
		setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
		SetExplosion(setExplo);

		// �e�̏I��
		EndShadow(g_aBullet[nCntBl].nShadowIdx);

		D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
		D3DXVec3Normalize(&patiMove, &patiMove);

		// �p�[�e�B�N������
		SetParticle(EFFECTTYPE_TRAJECTORY,	// �^�C�v
			g_aBullet[nCntBl].pos,			// �ʒu
			patiMove,						// �d��
			D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// �F
			50,								// �o����
			60,								// ����
			15.0f,							// �傫��
			5.0f,							// ���x
			false,							// �e�̗L��
			true							// ���Z���������Z������
		);

		// ��ʂ����鉹
		PlaySound(SOUND_LABEL_SE_BREAKSNOWBALL_BIG);
	}

	if (g_aBullet[nCntBl].fLife > 0)
	{// �����Ă���
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (g_aBullet[nCntBl].bUse == false)
			{// �e�g���ĂȂ�������
				break;
			}

			if (pEnemy->bUse == false)
			{// �G�g���ĂȂ�������
				continue;
			}

			for (int nCntPosi = 0; nCntPosi < pEnemy->charParam.nNumModel; nCntPosi++)
			{
				if (CollisionSphere(&g_aBullet[nCntBl].pos, &pEnemy->aColiPoint[nCntPosi].pos, g_aBullet[nCntBl].fWidth, pEnemy->aColiPoint[nCntPosi].fRadius + 20, false))
				{// �G�̊e�p�[�c�̓����蔻��
					g_aBullet[nCntBl].bUse = false;

					// �����ݒ�
					SETEXPLO setExplo;
					setExplo.pos = g_aBullet[nCntBl].pos;
					setExplo.size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
					SetExplosion(setExplo);

					// �G�̃q�b�g����
					HitEnemy(nCntEnemy, BULLET_ATTACK_SNOW_BIG);

					// �e�̏I��
					EndShadow(g_aBullet[nCntBl].nShadowIdx);

					D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
					D3DXVec3Normalize(&patiMove, &patiMove);

					// �p�[�e�B�N������
					SetParticle(EFFECTTYPE_TRAJECTORY,	// �^�C�v
						g_aBullet[nCntBl].pos,			// �ʒu
						patiMove,						// �d��
						D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// �F
						50,								// �o����
						60,								// ����
						15.0f,							// �傫��
						5.0f,							// ���x
						false,							// �e�̗L��
						true							// ���Z���������Z������
					);

					// ��ʂ����鉹
					PlaySound(SOUND_LABEL_SE_BREAKSNOWBALL_BIG);

					break;
				}
			}
		}
	}
}

//*****************************
// �X�ʏ����̐ݒ�
//*****************************
void IceBall(int nCntBl)
{
	ENEMY* pEnemy = GetEnemy();	// �G�l�~�[�擾

	BLOCKCOLLISION blockColi;

	// �d��
	g_aBullet[nCntBl].move.y -= (float)BULLET_GRAVITY;
	
	// �ړ��ʒǉ�
	g_aBullet[nCntBl].pos.x += g_aBullet[nCntBl].move.x;
	g_aBullet[nCntBl].pos.y += g_aBullet[nCntBl].move.y;
	g_aBullet[nCntBl].pos.z += g_aBullet[nCntBl].move.z;

	// �������炷
	g_aBullet[nCntBl].fLife -= 1.0f;

	SetEffect(EFFECTTYPE_TRAJECTORY,		// �^�C�v
		g_aBullet[nCntBl].pos,				// �ʒu
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �ړ���
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �d��
		D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f),	// �F
		30,									// ����
		20.0f,								// �傫��
		false,								// �e�̎d�l�L��
		true								// ���Z����
	);

	// �u���b�N�Ƃ̂̓����蔻��
	blockColi = CollisionBlockBullet(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move,10.0f);

	if (blockColi.bHit == true || g_aBullet[nCntBl].fLife <= 0.0f)
	{// �������Ă���
		// �e���g���Ȃ�����
		g_aBullet[nCntBl].bUse = false;

		// �u���b�N�j��
		BlockDestroy(blockColi.nCnt);

		// �����ݒ�
		SETEXPLO setExplo;
		setExplo.pos = g_aBullet[nCntBl].pos;
		setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
		SetExplosion(setExplo);

		// �e�̏I��
		EndShadow(g_aBullet[nCntBl].nShadowIdx);

		D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
		D3DXVec3Normalize(&patiMove, &patiMove);

		// �p�[�e�B�N������
		SetParticle(EFFECTTYPE_TRAJECTORY,	// �^�C�v
			g_aBullet[nCntBl].pos,			// �ʒu
			patiMove,						// �d��
			D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),	// �F
			50,								// �o����
			60,								// ����
			5.0f,							// �傫��
			2.0f,							// ���x
			false,							// �e�̗L��
			true							// ���Z���������Z������
		);

		// �X�ʂ����鉹
		PlaySound(SOUND_LABEL_SE_BREAKICEBALL);
	}

	if (g_aBullet[nCntBl].fLife > 0)
	{// �����Ă���
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (pEnemy->bUse == false)
			{// �G�g���ĂȂ�������
				continue;
			}

			for (int nCntPosi = 0; nCntPosi < pEnemy->charParam.nNumModel; nCntPosi++)
			{// ���f������
				if (CollisionSphere(&g_aBullet[nCntBl].pos, &pEnemy->aColiPoint[nCntPosi].pos, g_aBullet[nCntBl].fWidth, pEnemy->aColiPoint[nCntPosi].fRadius + 20, false))
				{// �G�̊e�p�[�c�̓����蔻��
					// �G�̃q�b�g����
					HitEnemy(nCntEnemy, BULLET_ATTACK_ICE);

					// �e�̏I��
					EndShadow(g_aBullet[nCntBl].nShadowIdx);

					D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
					D3DXVec3Normalize(&patiMove, &patiMove);

					// �p�[�e�B�N������
					SetParticle(EFFECTTYPE_TRAJECTORY,	// �^�C�v
						g_aBullet[nCntBl].pos,			// �ʒu
						D3DXVECTOR3(0.0f,0.0f,0.0f),	// �d��
						D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),	// �F
						50,								// �o����
						60,								// ����
						10.0f,							// �傫��
						3.0f,							// ���x
						false,							// �e�̗L��
						true							// ���Z���������Z������
					);

					// �X�ʂ����鉹
					PlaySound(SOUND_LABEL_SE_BREAKICEBALL);

					break;
				}
			}
		}
	}
	else
	{
		// �����ݒ�
		SETEXPLO setExplo;
		setExplo.pos = g_aBullet[nCntBl].pos;
		setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
		SetExplosion(setExplo);

		// �e�̏I��
		EndShadow(g_aBullet[nCntBl].nShadowIdx);
	}
}

//*****************************
// �����ʏ����̐ݒ�
//*****************************
void GravelBall(int nCntBl)
{
	ENEMY* pEnemy = GetEnemy();	// �G�l�~�[�擾

	g_aBullet[nCntBl].move.y -= (float)BULLET_GRAVITY;

	g_aBullet[nCntBl].pos.x += g_aBullet[nCntBl].move.x;
	g_aBullet[nCntBl].pos.y += g_aBullet[nCntBl].move.y;
	g_aBullet[nCntBl].pos.z += g_aBullet[nCntBl].move.z;

	g_aBullet[nCntBl].fLife -= 1.0f;

	SetEffect(EFFECTTYPE_TRAJECTORY,		// �^�C�v
		g_aBullet[nCntBl].pos,				// �ʒu
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �ړ���
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �d��
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// �F
		30,									// ����
		10.0f,								// �傫��
		false,								// �e�̎d�l�L��
		false								// ���Z����
	);

	if (CollisionBlock(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move) || g_aBullet[nCntBl].fLife <= 0.0f)
	{// �u���b�N�ǂ����̓����蔻��
		// �e�ݒ�
		SETBULLET setBlt;

		D3DXVECTOR3 vecA = g_aBullet[nCntBl].pos - g_aBullet[nCntBl].posOld;

		// �����
		setBlt.pos = g_aBullet[nCntBl].pos;
		setBlt.size = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
		setBlt.nType = BULLETTYPE_GRAVEL_DIFFUSION;
		setBlt.fLife = 120.0f;
		setBlt.move.x = vecA.x;
		setBlt.move.y = vecA.y;
		setBlt.move.z = vecA.z;

		for (int nCnt = 0; nCnt < 50; nCnt++)
		{
			// �����ɂԂ�����ŃZ�b�g����
			SetBullet(g_aBullet[nCntBl].pos, vecA,BULLETTYPE_GRAVEL_DIFFUSION);
		}

		g_aBullet[nCntBl].bUse = false;

		// �����ݒ�
		SETEXPLO setExplo;
		setExplo.pos = g_aBullet[nCntBl].pos;
		setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
		SetExplosion(setExplo);

		// �e�̏I��
		EndShadow(g_aBullet[nCntBl].nShadowIdx);

		// �����ʂ����鉹
		PlaySound(SOUND_LABEL_SE_BREAKGRAVELBALL);
	}

	if (g_aBullet[nCntBl].fLife > 0)
	{
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (g_aBullet[nCntBl].bUse == false)
			{// �e�g���ĂȂ�������
				break;
			}

			if (pEnemy->bUse == false)
			{// �G�g���ĂȂ�������
				continue;
			}

			for (int nCntPosi = 0; nCntPosi < pEnemy->charParam.nNumModel; nCntPosi++)
			{
				if (CollisionSphere(&g_aBullet[nCntBl].pos, &pEnemy->aColiPoint[nCntPosi].pos, g_aBullet[nCntBl].fWidth, pEnemy->aColiPoint[nCntPosi].fRadius + 20, false))
				{// �G�̊e�p�[�c�̓����蔻��
					g_aBullet[nCntBl].bUse = false;

					// �����ݒ�
					SETEXPLO setExplo;
					setExplo.pos = g_aBullet[nCntBl].pos;
					setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
					SetExplosion(setExplo);

					// �G�̃q�b�g����
					HitEnemy(nCntEnemy, BULLET_ATTACK_GRAVEL);

					// �e�̏I��
					EndShadow(g_aBullet[nCntBl].nShadowIdx);

					// �����ʂ����鉹
					PlaySound(SOUND_LABEL_SE_BREAKGRAVELBALL);

					break;
				}
			}
		}
	}
}

//*****************************
// �����ʏ����̐ݒ�
//*****************************
void GravelBallDiffusion(int nCntBl)
{
	ENEMY* pEnemy = GetEnemy();	// �G�l�~�[�擾

	g_aBullet[nCntBl].move.y -= (float)BULLET_GRAVITY;

	g_aBullet[nCntBl].pos.x += g_aBullet[nCntBl].move.x;
	g_aBullet[nCntBl].pos.y += g_aBullet[nCntBl].move.y;
	g_aBullet[nCntBl].pos.z += g_aBullet[nCntBl].move.z;

	g_aBullet[nCntBl].fLife -= 1.0f;

	SetEffect(EFFECTTYPE_TRAJECTORY,		// �^�C�v
		g_aBullet[nCntBl].pos,				// �ʒu
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �ړ���
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �d��
		D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f),	// �F
		60,									// ����
		5.0f,								// �傫��
		false,								// �e�̎d�l�L��
		false								// ���Z����
	);

	if (CollisionBlock(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move) || g_aBullet[nCntBl].fLife <= 0.0f)
	{// �u���b�N�Ƃ̓����蔻��
		g_aBullet[nCntBl].bUse = false;

		// �����ݒ�
		SETEXPLO setExplo;
		setExplo.pos = g_aBullet[nCntBl].pos;
		setExplo.size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		SetExplosion(setExplo);

		// �e�̏I��
		EndShadow(g_aBullet[nCntBl].nShadowIdx);

		D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
		D3DXVec3Normalize(&patiMove, &patiMove);

		// �p�[�e�B�N������
		SetParticle(EFFECTTYPE_TRAJECTORY,		// �^�C�v
			g_aBullet[nCntBl].pos,				// �ʒu
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �d��
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// �F
			50,									// �o����
			60,									// ����
			10.0f,								// �傫��
			5.0f,								// ���x
			false,								// �e�̗L��
			false								// ���Z���������Z������
		);

		// �����ʂ����鉹
		PlaySound(SOUND_LABEL_SE_BREAKGRAVELBALL);
	}

	if (g_aBullet[nCntBl].fLife > 0)
	{
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (g_aBullet[nCntBl].bUse == false)
			{// �e�g���ĂȂ�������
				break;
			}

			if (pEnemy->bUse == false)
			{// �G�g���ĂȂ�������
				continue;
			}

			for (int nCntPosi = 0; nCntPosi < pEnemy->charParam.nNumModel; nCntPosi++)
			{
				if (CollisionSphere(&g_aBullet[nCntBl].pos, &pEnemy->aColiPoint[nCntPosi].pos, g_aBullet[nCntBl].fWidth, pEnemy->aColiPoint[nCntPosi].fRadius + 20, false))
				{// �G�̊e�p�[�c�̓����蔻��
					g_aBullet[nCntBl].bUse = false;

					// �����ݒ�
					SETEXPLO setExplo;
					setExplo.pos = g_aBullet[nCntBl].pos;
					setExplo.size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
					SetExplosion(setExplo);

					// �G�̃q�b�g����
					HitEnemy(nCntEnemy, BULLET_ATTACK_GRAVEL_DIFFSION);

					// �e�̏I��
					EndShadow(g_aBullet[nCntBl].nShadowIdx);

					D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
					D3DXVec3Normalize(&patiMove, &patiMove);

					// �p�[�e�B�N������
					SetParticle(EFFECTTYPE_TRAJECTORY,		// �^�C�v
						g_aBullet[nCntBl].pos,				// �ʒu
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �d��
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// �F
						50,									// �o����
						60,									// ����
						10.0f,								// �傫��
						3.0f,								// ���x
						false,								// �e�̗L��
						false								// ���Z���������Z������
					);

					// �����ʂ����鉹
					PlaySound(SOUND_LABEL_SE_BREAKGRAVELBALL);

					break;
				}
			}
		}
	}

}

//*****************************
// ��ʂ̓����蔻��
//*****************************
bool CollisionSpharBullet(int nCnt)
{
	ENEMY *pEnemy = GetEnemy();// �G�l�~�[�̎擾

	bool bCollision = false;
	float fAx_Bx = g_aBullet[nCnt].pos.x - pEnemy->pos.x;
	float fAy_By = g_aBullet[nCnt].pos.y - pEnemy->pos.y;
	float fAz_Bz = g_aBullet[nCnt].pos.z - pEnemy->pos.z;
	float fLength = sqrtf((fAx_Bx * fAx_Bx) + (fAy_By * fAy_By) + (fAz_Bz * fAz_Bz));
	float fRange = 20.0f + 10.0f;

	switch (g_aBullet[nCnt].nType)
	{
	case BULLETTYPE_SNOW_MEDIUM:	// ����
		fRange = 20.0f + 15.0f;
		break;

	case BULLETTYPE_SNOW_BIG:	// ���
		fRange = 20.0f + 20.0f;
		break;

	case BULLETTYPE_GRAVEL_DIFFUSION:	// �����ʊg�U�e
		fRange = 20.0f + 5.0f;
		break;
	}

	if (CollisionSphere(&g_aBullet[nCnt].pos, &pEnemy->pos, 10.0f, 20.0f,false))
	{// �����锻����Z��������
		bCollision = true;
		//HitEnemy();
	}

	// ���ʂ�Ԃ�
	return bCollision;
}