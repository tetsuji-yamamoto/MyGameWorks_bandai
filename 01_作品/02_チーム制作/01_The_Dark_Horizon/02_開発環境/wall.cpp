#include "wall.h"
#include "camera.h"
#include "player.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pVtxTexturWall = NULL;		// �e�N�X�`���̃|�C���^
WALL g_aWall[MAX_WALL];							// �Ǐ��

//**************************************
// �ǂ̏�����
//**************************************
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall, NULL);

	VERTEX_3D* pVtx = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\wall\\wall000.jpg",
		&g_pVtxTexturWall);

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_aWall[nCntWall].size = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_aWall[nCntWall].vecA = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_aWall[nCntWall].vecB = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_aWall[nCntWall].col = D3DXCOLOR(1.0f,1.0f, 1.0f,1.0f);
		g_aWall[nCntWall].bFaB = false;	// �\��(�\)
		g_aWall[nCntWall].bUse = false;

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
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	g_pVtxBuffWall->Unlock();

	// �ǐݒ�
	SetWall(D3DXVECTOR3(0.0f, 50.0f, 150.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f));

	SetWall(D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	SetWall(D3DXVECTOR3(-150.0f, 50.0f, 0.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	SetWall(D3DXVECTOR3(0.0f, 50.0f, -150.0f), D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

}

//**************************************
// �ǂ̔j��
//**************************************
void UninitWall(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pVtxTexturWall != NULL)
	{
		g_pVtxTexturWall->Release();
		g_pVtxTexturWall = NULL;
	}
}

//**************************************
// �ǂ̍X�V
//**************************************
void UpdateWall(void)
{

}

//**************************************
// �ǂ̕`��
//**************************************
void DrawWall(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pVtxTexturWall);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �ǂ̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntWall, 2);
		}
	}
}

//**************************************
// �ǂ̐ݒ�
//**************************************
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 rot)
{
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].size = size;
			g_aWall[nCntWall].col = col;
			g_aWall[nCntWall].bUse = true;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = -g_aWall[nCntWall].size.x;
			pVtx[0].pos.y = g_aWall[nCntWall].size.y;
			pVtx[0].pos.z = g_aWall[nCntWall].size.z;

			pVtx[1].pos.x = g_aWall[nCntWall].size.x;
			pVtx[1].pos.y = g_aWall[nCntWall].size.y;
			pVtx[1].pos.z = g_aWall[nCntWall].size.z;

			pVtx[2].pos.x = -g_aWall[nCntWall].size.x;
			pVtx[2].pos.y = -g_aWall[nCntWall].size.y;
			pVtx[2].pos.z = g_aWall[nCntWall].size.z;

			pVtx[3].pos.x = g_aWall[nCntWall].size.x;
			pVtx[3].pos.y = -g_aWall[nCntWall].size.y;
			pVtx[3].pos.z = g_aWall[nCntWall].size.z;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aWall[nCntWall].col;
			pVtx[1].col = g_aWall[nCntWall].col;
			pVtx[2].col = g_aWall[nCntWall].col;
			pVtx[3].col = g_aWall[nCntWall].col;

			// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			D3DXVECTOR3 vecA ;
			D3DXVECTOR3 vecB;
			D3DXVECTOR3 posEX[4];
			D3DXVECTOR3 Ans;

			posEX[0].x = pos.x + sinf(rot.y - D3DX_PI * 0.5f) * size.x;
			posEX[0].y = pos.y + size.y;
			posEX[0].z = pos.z + cosf(rot.y - D3DX_PI * 0.5f) * size.x;

			posEX[1].x = pos.x - sinf(rot.y - D3DX_PI * 0.5f) * size.x;
			posEX[1].y = pos.y + size.y;
			posEX[1].z = pos.z - cosf(rot.y - D3DX_PI * 0.5f) * size.x;

			posEX[2].x = pos.x + sinf(rot.y - D3DX_PI * 0.5f) * size.x;
			posEX[2].y = pos.y - size.y;
			posEX[2].z = pos.z + cosf(rot.y - D3DX_PI * 0.5f) * size.x;

			posEX[3].x = pos.x - sinf(rot.y - D3DX_PI * 0.5f) * size.x;
			posEX[3].y = pos.y - size.y;
			posEX[3].z = pos.z - cosf(rot.y - D3DX_PI * 0.5f) * size.x;

			g_aWall[nCntWall].posEX[0] = posEX[0];
			g_aWall[nCntWall].posEX[1] = posEX[1];
			g_aWall[nCntWall].posEX[2] = posEX[2];
			g_aWall[nCntWall].posEX[3] = posEX[3];

			vecA = posEX[0] - posEX[2];
			vecB = posEX[3] - posEX[2];

			g_aWall[nCntWall].vecA = vecA;
			g_aWall[nCntWall].vecB = vecB;

			Ans.x = (vecA.y * vecB.z) - (vecA.z * vecB.y);
			Ans.y = (vecA.z * vecB.x) - (vecA.x * vecB.z);
			Ans.z = (vecA.x * vecB.y) - (vecA.y * vecB.x);

			D3DXVec3Normalize(&Ans, &Ans);

			g_aWall[nCntWall].norEX = Ans;

			pVtx[0].nor = Ans;
			pVtx[1].nor = Ans;
			pVtx[2].nor = Ans;
			pVtx[3].nor = Ans;

			break;
		}

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffWall->Unlock();
}

//**************************************
// �ǂ̓����蔻��
//**************************************
void CollisionWall(void)
{
	PLAYER* pPlayer = GetPlayer();	// �v���C���[���擾

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_aWall[nCnt].bUse)
		{
			D3DXVECTOR3 aPos[2];
			aPos[0] = g_aWall[nCnt].posEX[0];
			aPos[1] = g_aWall[nCnt].posEX[1];
			D3DXVECTOR3 vecA = aPos[1] - aPos[0];
			D3DXVECTOR3 vecB = pPlayer->pos - aPos[0];

			float vecAXvecB = (vecA.z * vecB.x) - (vecA.x * vecB.z);

			if (vecAXvecB < 0)
			{// �}�C�i�X(����������)
				float fnorRot = atan2f(g_aWall[nCnt].norEX.x, g_aWall[nCnt].norEX.z);
				float fz = fnorRot + D3DX_PI * 0.5f;
				float fPlayerRot = pPlayer->rotDest.y - fz;

				pPlayer->pos = pPlayer->posOld;
			}
		}
	}
}

//**************************************
// �ǂ̓����蔻��
//**************************************
void CollisionWallX(void)
{
	PLAYER* pPlayer = GetPlayer();	// �v���C���[���擾

	D3DXVECTOR3 aPos[2];
	aPos[0] = g_aWall[0].posEX[1];
	aPos[1] = g_aWall[0].posEX[0];
	D3DXVECTOR3 vecA = aPos[1] - aPos[0];
	D3DXVECTOR3 vecB = pPlayer->pos - aPos[0];

	float vecAXvecB = (vecA.z * vecB.x) - (vecA.x * vecB.z);

	if (vecAXvecB < 0)
	{// �}�C�i�X(����������)

		pPlayer->pos.x -= pPlayer->move.x;
	}
}

//**************************************
// �ǂ̓����蔻��
//**************************************
void CollisionWallZ(void)
{
	PLAYER* pPlayer = GetPlayer();	// �v���C���[���擾

	D3DXVECTOR3 aPos[2];
	aPos[0] = g_aWall[0].posEX[1];
	aPos[1] = g_aWall[0].posEX[0];
	D3DXVECTOR3 vecA = aPos[1] - aPos[0];
	D3DXVECTOR3 vecB = pPlayer->pos - aPos[0];

	float vecAXvecB = (vecA.z * vecB.x) - (vecA.x * vecB.z);

	if (vecAXvecB < 0)
	{// �}�C�i�X(����������)
		pPlayer->pos.z -= pPlayer->move.z;
	}
}