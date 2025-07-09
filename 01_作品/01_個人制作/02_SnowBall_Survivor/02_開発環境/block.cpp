#include "block.h"
#include "player.h"
#include "readtext.h"
#include "writetext.h"
#include "keyboard.h"
#include "edit.h"

// �O���[�o���ϐ��錾
BLOCK g_aBlock[MAX_BLOCK];		// �u���b�N���
BLOCKMANAGER g_blockManager;	// �u���b�N�Ǘ�
BLOCKCONTROLLER g_blockCont;	// �u���b�N������

//********************************************
//�u���b�N�̏�����
//********************************************
void InitBlock(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �u���b�N�Ǘ���񏉊���
	g_blockManager.nBlockNum = 0;

	// �u���b�N�{����񏉊���	
	g_blockCont.nNextBlType = BLOCKTYPE_SNOW;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// �e��ϐ��̏�����
		g_aBlock[nCntBlock].apTextureBlock[0] = {};
		g_aBlock[nCntBlock].pMeshBlock = NULL;
		g_aBlock[nCntBlock].pBuffMatBlock = NULL;
		g_aBlock[nCntBlock].dwNumMatBlock = 0;
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f ,0.0f, 0.0f);
		g_aBlock[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].vtxMaxBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].vtxMinBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].nType = BLOCKTYPE_MAX;
		g_aBlock[nCntBlock].bUse = false;
	}

	ReadText();

	g_blockCont.nCntNowBlock = g_blockManager.nBlockNum - 1;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			int nNumVtx;	// ���_��
			WORD sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y�f�[�^
			BYTE* pVtxBuff;	// ���_�o�b�t�@�̃|�C���^

			// ���_���̎擾
			nNumVtx = g_aBlock[nCntBlock].pMeshBlock->GetNumVertices();

			// ���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_aBlock[nCntBlock].pMeshBlock->GetFVF());

			// ���_�o�b�t�@�̃��b�N
			g_aBlock[nCntBlock].pMeshBlock->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
			{
				// ���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
				//[���_���W���r���ă��f���̍ő�ŏ����擾]

				if (g_aBlock[nCntBlock].vtxMaxBlock.x <= vtx.x)
				{// �ő�lX
					g_aBlock[nCntBlock].vtxMaxBlock.x = vtx.x;
				}

				if (g_aBlock[nCntBlock].vtxMaxBlock.y <= vtx.y)
				{// �ő�lY
					g_aBlock[nCntBlock].vtxMaxBlock.y = vtx.y;
				}

				if (g_aBlock[nCntBlock].vtxMaxBlock.z <= vtx.z)
				{// �ő�lZ
					g_aBlock[nCntBlock].vtxMaxBlock.z = vtx.z;
				}

				if (g_aBlock[nCntBlock].vtxMinBlock.x >= vtx.x)
				{// �ŏ��lX
					g_aBlock[nCntBlock].vtxMinBlock.x = vtx.x;
				}

				if (g_aBlock[nCntBlock].vtxMinBlock.y >= vtx.y)
				{// �ŏ��lY
					g_aBlock[nCntBlock].vtxMinBlock.y = vtx.y;
				}

				if (g_aBlock[nCntBlock].vtxMinBlock.z >= vtx.z)
				{// �ŏ��lZ
					g_aBlock[nCntBlock].vtxMinBlock.z = vtx.z;
				}

				// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
				pVtxBuff += sizeFVF;
			}

			// ���_�o�b�t�@�̃A�����b�N
			g_aBlock[nCntBlock].pMeshBlock->UnlockVertexBuffer();
		}
	}
}

//********************************************
// �u���b�N�̏I������
//********************************************
void UninitBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// ���b�V���̔j��
		if (g_aBlock[nCntBlock].pMeshBlock != NULL)
		{
			g_aBlock[nCntBlock].pMeshBlock->Release();
			g_aBlock[nCntBlock].pMeshBlock = NULL;
		}

		// �}�e���A���̔j��
		if (g_aBlock[nCntBlock].pBuffMatBlock != NULL)
		{
			g_aBlock[nCntBlock].pBuffMatBlock->Release();
			g_aBlock[nCntBlock].pBuffMatBlock = NULL;
		}

		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			// �}�e���A���̔j��
			if (g_aBlock[nCntBlock].apTextureBlock[nCnt] != NULL)
			{
				g_aBlock[nCntBlock].apTextureBlock[nCnt]->Release();
				g_aBlock[nCntBlock].apTextureBlock[nCnt] = NULL;
			}
		}
	}
}

//********************************************
// �u���b�N�̍X�V
//********************************************
void UpdateBlock(void)
{
#ifdef _DEBUG
	if (GetEditMode() == EDITMODE_BLOCK)
	{// �G�f�B�^�[�Q�[�����[�h��������
		BlockControllre();	// �u���b�N����
	}

	if (KeyboardTrigger(DIK_DELETE))
	{
		BlockOllDeliete();
		InitBlock();
	}
#endif
}

//********************************************
// �u���b�N�̕`��
//********************************************
void DrawBlock(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{// �g���Ă�����

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBlock[nCntBlock].mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBlock[nCntBlock].rot.y, g_aBlock[nCntBlock].rot.x, g_aBlock[nCntBlock].rot.z);
			D3DXMatrixMultiply(&g_aBlock[nCntBlock].mtxWorld, &g_aBlock[nCntBlock].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
			D3DXMatrixMultiply(&g_aBlock[nCntBlock].mtxWorld, &g_aBlock[nCntBlock].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBlock[nCntBlock].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].pBuffMatBlock->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].dwNumMatBlock; nCntMat++)
			{
#ifdef _DEBUG
				if (g_blockCont.nCntNowBlock == nCntBlock)
				{
					pMat->MatD3D.Diffuse.a = 0.5f;
				}
#endif

				if (GetEditMode() == EDITMODE_NONE && g_aBlock[nCntBlock].nType == BLOCKTYPE_TERRITRY_POINT)
				{
					D3DXMATERIAL matEX = *pMat;
					matEX.MatD3D.Diffuse.a = 0.0f;

					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&matEX.MatD3D);
				}
				else
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat->MatD3D);
				}

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_aBlock[nCntBlock].apTextureBlock[nCntMat]);

				// �u���b�N(�p�[�c�̕`��)
				g_aBlock[nCntBlock].pMeshBlock->DrawSubset(nCntMat);


			}

			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//********************************************
// �u���b�N�̐ݒ�
//********************************************
void SetBlock(SETBLOCK setBlock,bool bFilenameAstr)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{// �g���ĂȂ�������
			// �ϐ��̐ݒ�
			g_aBlock[nCntBlock].pos = setBlock.pos;
			g_aBlock[nCntBlock].rot = setBlock.rot;
			g_aBlock[nCntBlock].nType = setBlock.nType;
			if (bFilenameAstr)
			{
				if (setBlock.astr[0] == NULL)
				{
					g_aBlock[nCntBlock].pFilename = &g_blockManager.astr[setBlock.nType][0];
				}
				else
				{
					g_aBlock[nCntBlock].pFilename = &setBlock.astr[0];
				}
			}
			else
			{
				g_aBlock[nCntBlock].pFilename = setBlock.pFilename;

				g_blockCont.nCntNowBlock = nCntBlock;
			}

			g_aBlock[nCntBlock].bUse = true;

			for (int nCnt = 0; nCnt < 256; nCnt++)
			{
				g_aBlock[nCntBlock].astr[nCnt] = setBlock.astr[nCnt];
				if (setBlock.astr[nCnt] == '\n')
				{
					break;
				}
			}

			g_blockManager.nBlockNum++;	// �u���b�N�J�E���g

			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(g_aBlock[nCntBlock].pFilename,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_aBlock[nCntBlock].pBuffMatBlock,
				NULL,
				&g_aBlock[nCntBlock].dwNumMatBlock,
				&g_aBlock[nCntBlock].pMeshBlock);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].pBuffMatBlock->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].dwNumMatBlock; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{// �e�N�X�`���t�@�C�������݂���

					// ���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_aBlock[nCntBlock].apTextureBlock[nCntMat]);
				}
			}

			break;
		}
	}
}

//********************************************
// �u���b�N�ƃL�����N�^�[�̓����蔻��
//********************************************
BLOCKCOLLISION CollisionBlockCharacter(D3DXVECTOR3 *pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, int *pBlockType, float fWidth,float fHeight)
{
	BLOCKCOLLISION collision;	// �R���W�������
	collision.bHit = false;
	collision.nCnt = -1;
	collision.nHitfase = -1;
	collision.nType = -1;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].nType != BLOCKTYPE_TERRITRY_POINT && g_aBlock[nCntBlock].nType != BLOCKTYPE_UDD_SNOW)
		{
			if (g_aBlock[nCntBlock].bUse == false)
			{
				continue;
			}

			if (pPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
				pPos->y + fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
			{// �㉺�ȓ�
				// �O���̓����蔻��
				if (pPos->x - fWidth < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
					pPos->x + fWidth > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
				{// X�̕�
					if (pPosOld->z + fWidth <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z &&
						pPos->z + fWidth >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
					{// Z����O���牜�ɂ߂荞��
						pPos->z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z - fWidth;
						collision.bHit = true;
						collision.nCnt = nCntBlock;
						collision.nHitfase = BLOCKFACETYPE_SIDE;
						collision.nType = g_aBlock[nCntBlock].nType;
					}
					else if (pPosOld->z - fWidth >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
						pPos->z - fWidth <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z)
					{// Z���������O�ɂ߂荞�񂾑O
						pPos->z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z + fWidth;
						collision.bHit = true;
						collision.nCnt = nCntBlock;
						collision.nHitfase = BLOCKFACETYPE_SIDE;
						collision.nType = g_aBlock[nCntBlock].nType;
					}
				}

				// ���E�̂߂荞�ݔ���
				if (pPos->z - fWidth < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
					pPos->z + fWidth > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
				{// Z�̕�
					if (pPosOld->x + fWidth <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
						pPos->x + fWidth >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
					{// X��������E�ɂ߂荞��
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x - fWidth;
						collision.bHit = true;
						collision.nCnt = nCntBlock;
						collision.nHitfase = BLOCKFACETYPE_SIDE;
						collision.nType = g_aBlock[nCntBlock].nType;
					}
					else if (pPosOld->x - fWidth >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
						pPos->x - fWidth <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x)
					{// X���E���獶�ɂ߂荞��
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x + fWidth;
						collision.bHit = true;
						collision.nCnt = nCntBlock;
						collision.nHitfase = BLOCKFACETYPE_SIDE;
						collision.nType = g_aBlock[nCntBlock].nType;
					}
				}
			}

			// Y�̓����蔻��
			if (pPos->x - fWidth <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
				pPos->x + fWidth >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
				pPos->z - fWidth <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
				pPos->z + fWidth >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
			{// X�̕���Z�̕���
				if (pPosOld->y >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
					pPos->y <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y)
				{// �ォ�牺
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y;
					pMove->y = 0.0f;
					*pBlockType = g_aBlock[nCntBlock].nType;
					collision.bHit = true;
					collision.nCnt = nCntBlock;
					collision.nHitfase = BLOCKFACETYPE_TOP;
					collision.nType = g_aBlock[nCntBlock].nType;
				}
				else if (pPosOld->y + fHeight <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y &&
					pPos->y + fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
				{// �������
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y - fHeight;
					pMove->y = 0.0f;
					collision.bHit = true;
					collision.nCnt = nCntBlock;
					collision.nHitfase = BLOCKFACETYPE_BOTTOM;
					collision.nType = g_aBlock[nCntBlock].nType;
				}
			}
		}
	}
	return collision;
}

//********************************************
// �u���b�N�̓����蔻��
//********************************************
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove)
{
	bool bCollision = false;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].nType != BLOCKTYPE_TERRITRY_POINT && g_aBlock[nCntBlock].nType != BLOCKTYPE_UDD_SNOW)
		{
			if (g_aBlock[nCntBlock].bUse == false)
			{
				continue;
			}

			if (pPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
				pPos->y >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
			{// �㉺�ȓ�
				// �O���̓����蔻��
				if (pPos->x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
					pPos->x > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
				{// X�̕�
					if (pPosOld->z <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z &&
						pPos->z >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
					{// Z����O���牜�ɂ߂荞��
						pPos->z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z;
						bCollision = true;
					}
					else if (pPosOld->z >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
						pPos->z <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z)
					{// Z���������O�ɂ߂荞�񂾑O
						pPos->z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z;
						bCollision = true;
					}
				}

				// ���E�̂߂荞�ݔ���
				if (pPos->z < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
					pPos->z > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
				{// Z�̕�
					if (pPosOld->x <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
						pPos->x >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
					{// X��������E�ɂ߂荞��
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x;
						bCollision = true;
					}
					else if (pPosOld->x >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
						pPos->x <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x)
					{// X���E���獶�ɂ߂荞��
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x;
						bCollision = true;
					}
				}
			}

			// Y�̓����蔻��
			if (pPos->x <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
				pPos->x >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
				pPos->z <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
				pPos->z >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
			{// X�̕���Z�̕���
				if (pPosOld->y >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
					pPos->y <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y)
				{// �ォ�牺
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y;
					pMove->y = 0.0f;
					bCollision = true;
				}
				else if (pPosOld->y <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y &&
					pPos->y >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
				{// �������
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y;
					pMove->y = 0.0f;
					bCollision = true;
				}
			}
		}
	}
	return bCollision;
}

//********************************************
// �u���b�N�̓����蔻��
//********************************************
BLOCKCOLLISION CollisionBlockBullet(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove,float fSize)
{
	BLOCKCOLLISION Collision;

	Collision.bHit = false;
	Collision.nCnt = -1;
	Collision.nHitfase = -1;
	Collision.nType = -1;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].nType != BLOCKTYPE_TERRITRY_POINT && g_aBlock[nCntBlock].nType != BLOCKTYPE_UDD_SNOW)
		{
			if (g_aBlock[nCntBlock].bUse == false)
			{
				continue;
			}

			if (pPos->y - fSize < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
				pPos->y + fSize >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
			{// �㉺�ȓ�
				// �O���̓����蔻��
				if (pPos->x - fSize< g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
					pPos->x + fSize> g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
				{// X�̕�
					if (pPosOld->z + fSize <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z &&
						pPos->z + fSize >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
					{// Z����O���牜�ɂ߂荞��
						pPos->z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z + fSize;
						Collision.bHit = true;
						Collision.nCnt = nCntBlock;
						Collision.nHitfase = BLOCKFACETYPE_SIDE;
						Collision.nType = g_aBlock[nCntBlock].nType;
					}
					else if (pPosOld->z - fSize >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
						pPos->z - fSize <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z)
					{// Z���������O�ɂ߂荞�񂾑O
						pPos->z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z - fSize;
						Collision.bHit = true;
						Collision.nCnt = nCntBlock;
						Collision.nHitfase = BLOCKFACETYPE_SIDE;
						Collision.nType = g_aBlock[nCntBlock].nType;
					}
				}

				// ���E�̂߂荞�ݔ���
				if (pPos->z - fSize< g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
					pPos->z + fSize> g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
				{// Z�̕�
					if (pPosOld->x + fSize <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
						pPos->x + fSize >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
					{// X��������E�ɂ߂荞��
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x - fSize;
						Collision.bHit = true;
						Collision.nCnt = nCntBlock;
						Collision.nHitfase = BLOCKFACETYPE_SIDE;
						Collision.nType = g_aBlock[nCntBlock].nType;
					}
					else if (pPosOld->x - fSize >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
						pPos->x - fSize <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x)
					{// X���E���獶�ɂ߂荞��
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x + fSize;
						Collision.bHit = true;
						Collision.nCnt = nCntBlock;
						Collision.nHitfase = BLOCKFACETYPE_SIDE;
						Collision.nType = g_aBlock[nCntBlock].nType;
					}
				}
			}

			// Y�̓����蔻��
			if (pPos->x - fSize <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
				pPos->x + fSize >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
				pPos->z - fSize <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
				pPos->z + fSize >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
			{// X�̕���Z�̕���
				if (pPosOld->y - fSize >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
					pPos->y - fSize < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y)
				{// �ォ�牺
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y + fSize;
					pMove->y = 0.0f;
					Collision.bHit = true;
					Collision.nCnt = nCntBlock;
					Collision.nHitfase = BLOCKFACETYPE_TOP;
					Collision.nType = g_aBlock[nCntBlock].nType;
				}
				else if (pPosOld->y + fSize <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y &&
					pPos->y + fSize >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
				{// �������
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y - fSize;
					pMove->y = 0.0f;
					Collision.bHit = true;
					Collision.nCnt = nCntBlock;
					Collision.nHitfase = BLOCKFACETYPE_BOTTOM;
					Collision.nType = g_aBlock[nCntBlock].nType;
				}
			}
		}
	}
	return Collision;
}

//********************************************
// �u���b�N�����ǋ��̔���
//********************************************
BLOCKCOLLISION CollisionBlockSpher(D3DXVECTOR3 posA, float fSizeA, int nBreakType, bool bBreak)
{
	BLOCKCOLLISION collision;
	collision.bHit = false;
	collision.nCnt = -1;
	collision.nHitfase = -1;
	collision.nType = -1;
	float fRange = fSizeA + 40.0f;		// ���a�Ɣ��a�𑫂����l
	D3DXVECTOR3 vecA;					// �x�N�g��A

	// ���������߂�
	float fLength = sqrtf((vecA.x * vecA.x) + (vecA.y * vecA.y) + (vecA.z * vecA.z));

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (collision.bHit == true)
		{
			continue;
		}

		if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].nType == nBreakType)
		{
			vecA = g_aBlock[nCntBlock].pos - posA;
			fLength = sqrtf((vecA.x * vecA.x) + (vecA.y * vecA.y) + (vecA.z * vecA.z));

			if (fLength <= fRange)
			{// �Z��������
				collision.bHit = true;
				collision.nCnt = nCntBlock;
				collision.nHitfase = -1;
				collision.nType = g_aBlock[nCntBlock].nType;

				if (bBreak && nBreakType == g_aBlock[nCntBlock].nType)
				{// �󂵂ėǂ�������
					g_aBlock[nCntBlock].bUse = false;
				}
			}
		}
	}

	// ���ʂ�Ԃ�
	return collision;
}

//********************************************
// �u���b�N�̔j��
//********************************************
void BlockDestroy(int nCnt)
{
	if (g_aBlock[nCnt].nType == BLOCKTYPE_WALL)
	{// �ǂȂ�j��ł����
		g_aBlock[nCnt].bUse = false;
	}
}

//********************************************
// �u���b�N�̎擾
//********************************************
BLOCK* GetBlock(void)
{
	return &g_aBlock[0];
}

//********************************************
// �u���b�N����̎擾
//********************************************
BLOCKCONTROLLER* GetBlockController(void)
{
	return &g_blockCont;
}

//********************************************
// �u���b�N�Ǘ��̎擾
//********************************************
BLOCKMANAGER* GetBlockManager(void)
{
	return &g_blockManager;
}

//********************************************
// �u���b�N�S������
//********************************************
void BlockOllDeliete(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].bUse = false;
		g_blockManager.nBlockNum--;
	}
}

//********************************************
// �u���b�N�T��
//********************************************
BLOCK BlockSearch(BLOCKTYPE type,int nNumber)
{
	BLOCK block;	// �u���b�N���
	int nCntEX = 0;

	block.apTextureBlock[0] = {};
	block.pMeshBlock = NULL;
	block.pBuffMatBlock = NULL;
	block.dwNumMatBlock = 0;
	block.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	block.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	block.vtxMaxBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	block.vtxMinBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	block.nType = BLOCKTYPE_MAX;
	block.bUse = false;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{// �T��
		 
		if (g_aBlock[nCntBlock].nType == 5)
		{
			int i = 0;
		}

		if (g_aBlock[nCntBlock].bUse == false || g_aBlock[nCntBlock].nType != type)
		{// �g���ĂȂ�������^�C�v���Ⴄ
			continue;
		}

		if (nNumber == nCntEX)
		{// ���ړ��Ă̔ԍ�����������
			block = g_aBlock[nCntBlock];	// �T�������̂��Ԃ�����
			break;
		}

		nCntEX++;
	}

	// ���ʂ�Ԃ�
	return block;
}

//********************************************
// �u���b�N����
//********************************************
void BlockControllre(void)
{
#ifdef _DEBUG
	if (GetEditMode() != EDITMODE_BLOCK)
	{
		return;
	}

#endif

	if (KeyboardTrigger(DIK_RSHIFT))
	{// �u���b�N��V�����z�u

		int OldNumCntBl = g_blockCont.nCntNowBlock;

		for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (g_aBlock[nCntBlock].bUse == false)
			{
				g_blockCont.nCntNowBlock = nCntBlock;
				break;
			}
		}

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_aBlock[OldNumCntBl].pBuffMatBlock->GetBufferPointer();

		pMat->MatD3D.Diffuse.a = 1.0f;

		SETBLOCK setb;
		setb.nType = g_blockCont.nNextBlType;

		switch (setb.nType)
		{
		case BLOCKTYPE_SNOW:
			setb.pFilename = FILE_XFILE_BLOCK_SNOW;
			break;

		case BLOCKTYPE_ICE:
			setb.pFilename = FILE_XFILE_BLOCK_ICE;
			break;

		case BLOCKTYPE_GRAVEL:
			setb.pFilename = FILE_XFILE_BLOCK_GRAVEL;
			break;

		case BLOCKTYPE_WALL:
			setb.pFilename = FILE_XFILE_BLOCK_WALL;
			break;

		case BLOCKTYPE_WALL_ADULT:
			setb.pFilename = FILE_XFILE_BLOCK_WALL_ADULT;
			break;

		case BLOCKTYPE_TERRITRY_POINT:
			setb.pFilename = FILE_XFILE_TERRITORYPOINT;
			break;

		case BLOCKTYPE_UDD_SNOW:
			setb.pFilename = FILE_XFILE_UDD_SNOW;
			break;
		}

		setb.pos = g_aBlock[OldNumCntBl].pos;
		setb.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SetBlock(setb, false);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_aBlock[g_blockCont.nCntNowBlock].pBuffMatBlock->GetBufferPointer();

		pMat->MatD3D.Diffuse.a = 0.5f;
	}
	else if (KeyboardTrigger(DIK_RIGHT))
	{// ���ɔz�u����u���b�N�̎�ނ�ς���

		g_aBlock[g_blockCont.nCntNowBlock].bUse = false;

		g_blockCont.nNextBlType++;

		if (g_blockCont.nNextBlType >= BLOCKTYPE_MAX)
		{// ����s������
			g_blockCont.nNextBlType = 0;
		}


		SETBLOCK setb;
		setb.nType = g_blockCont.nNextBlType;

		switch (setb.nType)
		{
		case BLOCKTYPE_SNOW:
			setb.pFilename = FILE_XFILE_BLOCK_SNOW;
			break;

		case BLOCKTYPE_ICE:
			setb.pFilename = FILE_XFILE_BLOCK_ICE;
			break;

		case BLOCKTYPE_GRAVEL:
			setb.pFilename = FILE_XFILE_BLOCK_GRAVEL;
			break;

		case BLOCKTYPE_WALL:
			setb.pFilename = FILE_XFILE_BLOCK_WALL;
			break;

		case BLOCKTYPE_WALL_ADULT:
			setb.pFilename = FILE_XFILE_BLOCK_WALL_ADULT;
			break;

		case BLOCKTYPE_TERRITRY_POINT:
			setb.pFilename = FILE_XFILE_TERRITORYPOINT;
			break;

		case BLOCKTYPE_UDD_SNOW:
			setb.pFilename = FILE_XFILE_UDD_SNOW;
			break;
		}

		setb.pos = g_aBlock[g_blockCont.nCntNowBlock].pos;
		setb.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SetBlock(setb, false);
	}

	if (KeyboardTrigger(DIK_UP))
	{
		// �}�e���A���f�[�^�ւ̃|�C���^
		D3DXMATERIAL* pMat;
		int nCntBlock = g_blockCont.nCntNowBlock;

		while (1)
		{
			if (g_aBlock[nCntBlock].bUse)
			{
				if (nCntBlock == g_blockCont.nCntNowBlock)
				{
					nCntBlock++;

					if (nCntBlock >= MAX_BLOCK)
					{// �[���ȉ��ɂȂ�����
						nCntBlock = 0;
					}
					continue;
				}
				else
				{
					// �}�e���A���f�[�^�ւ̃|�C���^���擾
					pMat = (D3DXMATERIAL*)g_aBlock[g_blockCont.nCntNowBlock].pBuffMatBlock->GetBufferPointer();

					pMat->MatD3D.Diffuse.a = 1.0f;
				}

				g_blockCont.nCntNowBlock = nCntBlock;

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_aBlock[g_blockCont.nCntNowBlock].pBuffMatBlock->GetBufferPointer();

				pMat->MatD3D.Diffuse.a = 0.5f;

				break;
			}

			nCntBlock++;

			if (nCntBlock >= MAX_BLOCK)
			{// �[���ȉ��ɂȂ�����
				nCntBlock = 0;
			}
		}
	}
	else if (KeyboardTrigger(DIK_DOWN))
	{
		// �}�e���A���f�[�^�ւ̃|�C���^
		D3DXMATERIAL* pMat;
		int nCntBlock = g_blockCont.nCntNowBlock;

		while (1)
		{
			if (g_aBlock[nCntBlock].bUse)
			{
				if (nCntBlock == g_blockCont.nCntNowBlock)
				{
					nCntBlock--;
					if (nCntBlock < 0)
					{// �[���ȉ��ɂȂ�����
						nCntBlock = MAX_BLOCK;
					}
					continue;
				}
				else
				{
					// �}�e���A���f�[�^�ւ̃|�C���^���擾
					pMat = (D3DXMATERIAL*)g_aBlock[g_blockCont.nCntNowBlock].pBuffMatBlock->GetBufferPointer();

					pMat->MatD3D.Diffuse.a = 1.0f;
				}

				g_blockCont.nCntNowBlock = nCntBlock;

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_aBlock[g_blockCont.nCntNowBlock].pBuffMatBlock->GetBufferPointer();

				pMat->MatD3D.Diffuse.a = 0.5f;

				break;
			}

			nCntBlock--;

			if (nCntBlock < 0)
			{// �[���ȉ��ɂȂ�����
				nCntBlock = MAX_BLOCK;
			}

		}
	}

	if (KeyboardTrigger(DIK_BACK) && g_blockManager.nBlockNum > 1)
	{
		g_aBlock[g_blockCont.nCntNowBlock].bUse = false;

		for (int nCntBlock = MAX_BLOCK - 1; nCntBlock >= 0; nCntBlock--)
		{
			if (g_aBlock[nCntBlock].bUse)
			{
				g_blockCont.nCntNowBlock = nCntBlock;

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].pBuffMatBlock->GetBufferPointer();

				pMat->MatD3D.Diffuse.a = 0.5f;

				g_blockManager.nBlockNum--;// ���������炷
				break;
			}
		}
	}

	if (KeyboardTrigger(DIK_RETURN))
	{
		for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (g_aBlock[nCntBlock].bUse)
			{
				if (nCntBlock == g_blockCont.nCntNowBlock)
				{
					continue;
				}

				g_aBlock[nCntBlock].bUse = false;

				g_blockManager.nBlockNum--;// ���������炷
			}
		}
	}

	if (KeyboardTrigger(DIK_W))
	{
		g_aBlock[g_blockCont.nCntNowBlock].pos.z += 80.0f;
	}

	if (KeyboardTrigger(DIK_A))
	{
		g_aBlock[g_blockCont.nCntNowBlock].pos.x -= 80.0f;
	}

	if (KeyboardTrigger(DIK_S))
	{
		g_aBlock[g_blockCont.nCntNowBlock].pos.z -= 80.0f;
	}

	if (KeyboardTrigger(DIK_D))
	{
		g_aBlock[g_blockCont.nCntNowBlock].pos.x += 80.0f;
	}

	if (KeyboardTrigger(DIK_Q))
	{
		g_aBlock[g_blockCont.nCntNowBlock].pos.y += 80.0f;
	}
	else if (KeyboardTrigger(DIK_E))
	{
		g_aBlock[g_blockCont.nCntNowBlock].pos.y -= 80.0f;
	}
}