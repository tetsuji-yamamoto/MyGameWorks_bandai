#include "cylinder.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffcylinder = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pVtxTexturcylinder = NULL;		// �e�N�X�`���̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffcylinder = NULL;	// �C���f�b�N�X�ւ̃|�C���^
D3DXVECTOR3 g_poscylinder;							// �ʒu
D3DXVECTOR3 g_rotcylinder;							// ����
D3DXMATRIX g_mtxWorldcylinder;						// ���[���h�}�g���b�N�X

D3DXVECTOR3 g_aPos[MESH_PLYGON_AII][3];	// ��|���S�����Ƃ̂R���_�ۑ��ϐ�

//**************************************
// ���b�V���t�B�[���h�̏�����
//**************************************
void Initcylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESH_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffcylinder, NULL);

	VERTEX_3D* pVtx = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\billboard\\mountain002.png",
		&g_pVtxTexturcylinder);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESH_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffcylinder,
		NULL);

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffcylinder->Lock(0, 0, (void**)&pVtx, 0);

	float fX = (float)FIELD_X / (float)MESH_X;
	float fZ = (float)FIELD_Z / (float)MESH_Z;

	float fRadius = 5000.0f;	// ���a

	float fAngle = (D3DX_PI * 2.0f) / (float)MESH_X;

	float fposX = 0.0f;
	float fposZ = 0.0f;

	float fTexX = 1.0f / (float)MESH_X;
	float fTexY = 1.0f / (float)MESH_Z;

	int nCntVtx = 0;

	// �ʒu�ƌ����̏�����
	g_poscylinder = D3DXVECTOR3(0.0f,-500.0f,0.0f);
	g_rotcylinder = D3DXVECTOR3(0.0f,0.0f,0.0f);

	D3DXVECTOR3 VtxEX[MESH_VERTEX] = {};
	D3DXVECTOR2 bbb[MESH_VERTEX] = {};
	D3DXVECTOR3 test;

	for (int nCntV = 0; nCntV <= MESH_Z; nCntV++)
	{
		for (int nCntH = 0; nCntH <= MESH_X; nCntH++)
		{

			// ���_���̏�����
			pVtx[nCntVtx].pos.x = g_poscylinder.x + sinf(-fAngle * nCntH) * fRadius;
			pVtx[nCntVtx].pos.y = g_poscylinder.y + 5000.0f * nCntV;
			pVtx[nCntVtx].pos.z = g_poscylinder.z + cosf(-fAngle * nCntH) * fRadius;

			test = pVtx[nCntVtx].pos;

			// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			D3DXVec3Normalize( &pVtx[nCntVtx].nor, &test);

			// ���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[nCntVtx].tex.x = -fTexX * nCntH;
			pVtx[nCntVtx].tex.y = -fTexY * nCntV;

			nCntVtx++;
		}
	}

	nCntVtx = 0;

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffcylinder->Unlock();

	// �C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	g_pIdxBuffcylinder->Lock(0, 0, (void**)&pIdx, 0);

	int naIdxEX[MESH_INDEX];// �C���f�b�N�X�i�[�p

	int nVtx = 0;
	int nIdxA = MESH_X + 1;	// �����C���f�b�N�X
	int nIdxB = 0;		// �E���C���f�b�N�X

	for (int nCntA = 0; nCntA < MESH_Z; nCntA++)
	{
		for (int nCntB = 0; nCntB <= MESH_X; nCntB++)
		{
			pIdx[nVtx] = nIdxA;
			naIdxEX[nVtx] = nIdxA;
			nVtx++;
			pIdx[nVtx] = nIdxB;
			naIdxEX[nVtx] = nIdxB;
			nVtx++;
			nIdxA++;
			nIdxB++;
		}

		if (nCntA < MESH_Z - 1)
		{// ���S���u
			pIdx[nVtx] = nIdxB - 1;
			naIdxEX[nVtx] = nIdxB - 1;
			nVtx++;
			pIdx[nVtx] = nIdxA;
			naIdxEX[nVtx] = nIdxA;
			nVtx++;
		}
	}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffcylinder->Unlock();

	//nVtx = 0;
	//int nCntPoli = 0;
	//int nCntNor = 0;

	//for (nCntPoli = 0; nCntPoli < MESH_PLYGON_AII; nCntPoli++)
	//{// �|���S������
	//	// �e���_�̍��W�������Ă���
	//	g_aPos[nCntPoli][0] = VtxEX[naIdxEX[nVtx]];
	//	g_aPos[nCntPoli][1] = VtxEX[naIdxEX[nVtx + 1]];
	//	g_aPos[nCntPoli][2] = VtxEX[naIdxEX[nVtx + 2]];
	//	nVtx++;
	//}

	//nCntPoli = 0;
	//nVtx = 0;
}

//*******************************************
// ���b�V���t�B�[���h�̔j��
//*******************************************
void Uninitcylinder(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffcylinder != NULL)
	{
		g_pVtxBuffcylinder->Release();
		g_pVtxBuffcylinder = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pVtxTexturcylinder != NULL)
	{
		g_pVtxTexturcylinder->Release();
		g_pVtxTexturcylinder = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffcylinder != NULL)
	{
		g_pIdxBuffcylinder->Release();
		g_pIdxBuffcylinder = NULL;
	}
}

//*******************************************
// ���b�V���t�B�[���h�̔j��
//*******************************************
void Updatecylinder(void)
{

}

//*******************************************
// ���b�V���t�B�[���h�̕`��
//*******************************************
void Drawcylinder(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldcylinder);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotcylinder.y, g_rotcylinder.x, g_rotcylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldcylinder, &g_mtxWorldcylinder, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_poscylinder.x, g_poscylinder.y, g_poscylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldcylinder, &g_mtxWorldcylinder, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldcylinder);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffcylinder, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffcylinder);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pVtxTexturcylinder);
	
	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0,MESH_VERTEX,0,MESH_PLYGON_AII);
}

//*******************************************
// ���b�V���t�B�[���h�̓����蔻��
//*******************************************
bool CollisionMesh(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove)
{
	D3DXVECTOR3 vecLineA[3];
	D3DXVECTOR3 vecLineB[3];
	float fCloss[3];
	bool bRanding = false;

	for (int nCntPoli = 0; nCntPoli < MESH_PLYGON_AII; nCntPoli++)
	{// �|���S������
		for (int nCntPoliApp = 0; nCntPoliApp < MESH_X * 2; nCntPoliApp++)
		{// ������|���S��
			// ������Ƀx�N�g�������߂�
			vecLineA[0] = g_aPos[nCntPoli][0] - g_aPos[nCntPoli][1];
			vecLineA[1] = g_aPos[nCntPoli][2] - g_aPos[nCntPoli][0];
			vecLineA[2] = g_aPos[nCntPoli][1] - g_aPos[nCntPoli][2];

			// �e���_�Ƃ̃x�N�g��
			vecLineB[0] = *pPos - g_aPos[nCntPoli][1];
			vecLineB[1] = *pPos - g_aPos[nCntPoli][0];
			vecLineB[2] = *pPos - g_aPos[nCntPoli][2];

			// Y�̊O�ς����߂�
			fCloss[0] = (vecLineA[0].z * vecLineB[0].x) - (vecLineA[0].x * vecLineB[0].z);
			fCloss[1] = (vecLineA[1].z * vecLineB[1].x) - (vecLineA[1].x * vecLineB[1].z);
			fCloss[2] = (vecLineA[2].z * vecLineB[2].x) - (vecLineA[2].x * vecLineB[2].z);

			if (fCloss[0] < 0 && fCloss[1] < 0 && fCloss[2] < 0 || 
				fCloss[0] > 0 && fCloss[1] > 0 && fCloss[2] > 0)
			{// ���ׂă}�C�i�X�܂��͂��ׂăv���X�Ȃ�
				D3DXVECTOR3 vecNor;	// �@���x�N�g��
				D3DXVECTOR3 vecC = g_aPos[nCntPoli][0] - g_aPos[nCntPoli][1];	// �|���S���̈�Ӄx�N�g��
				D3DXVECTOR3 vecD = g_aPos[nCntPoli][2] - g_aPos[nCntPoli][1];	// �|���S���̈�Ӄx�N�g��
				D3DXVECTOR3 vecE = *pPos - g_aPos[nCntPoli][0];					// �ǂ����̒��_����|�X�̃x�N�g��
				float fDotY;	// ����
				float faxbx;	// �r����
				float fazbz;	// �r����

				// �@���x�N�g�������߂�
				vecNor.x = (vecC.y * vecD.z) - (vecC.z * vecD.y);
				vecNor.y = (vecC.z * vecD.x) - (vecC.x * vecD.z);
				vecNor.z = (vecC.x * vecD.y) - (vecC.y * vecD.x);

				// ���K��
				D3DXVec3Normalize(&vecNor, &vecNor);

				// ��ԑ傫���̂𗊂�
				if (vecE.y <= vecLineB[0].y)
				{
					vecE = vecLineB[0];
				}

				if (vecE.y <= vecLineB[1].y)
				{
					vecE = vecLineB[1];
				}

				if (vecE.y <= vecLineB[2].y)
				{
					vecE = vecLineB[2];
				}

				// ���ς��[���ɂȂ�Ƃ���Y���W
				faxbx = -(vecNor.x * vecE.x);
				fazbz = -(vecNor.z * vecE.z);

 				fDotY = (faxbx + fazbz) * (1.0f / vecNor.y);

				if (pPos->y <= fDotY)
				{// ���߂��l��菬����������
					// ���߂��ʒu�ɂ���
					pPos->y = fDotY;
					pMove->y = 0.0f;
					bRanding = true;	// ����Ă܂���
				}
			}
			nCntPoli++;	// ��|���S���i�߂�
		}
			nCntPoli += 3;	// �k�ރ|���S�����i�߂�
	}

	// ���ʂ�Ԃ�
	return bRanding;
}