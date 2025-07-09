#include "block.h"
#include "player.h"
#include "main.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	//���_�o�b�t�@�ւ̃|�C���^
BLOCK g_aBlock[MAX_BLOCK];//�u���b�N�̏��

//------------------
//�u���b�N�̏���������
//------------------
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_BLOCK,
		&g_pTextureBlock);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//�u���b�N�̏��̏�����
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].posGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].nCntTime = 0;
		g_aBlock[nCntBlock].nType = BLOCKTYPE_NOMAL;
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].fTexX = 1.0f;
		g_aBlock[nCntBlock].fTexY = 1.0f;
		g_aBlock[nCntBlock].bUse = false;
		//�ʒu�̏�����
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

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�f�[�^�̃|�C���^���l���i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}
//-------------
//�u���b�N�̏I������
//-------------
void UninitBlock(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureBlock != NULL)
	{

		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//--------------------
//�u���b�N�̍X�V����
//--------------------
void UpdateBlock(void)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//�u���b�N�̏��̏�����
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			switch (g_aBlock[nCntBlock].nType)
			{
			case BLOCKTYPE_MOVEX:
				//�J�E���g����
				g_aBlock[nCntBlock].nCntTime++;

				if (g_aBlock[nCntBlock].nCntTime >= 180)
				{//��萔��������
					g_aBlock[nCntBlock].nCntTime *= -1;
				}

				if (g_aBlock[nCntBlock].nCntTime >= 0)
				{//�v���X��������

					g_aBlock[nCntBlock].move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
				}
				else if (g_aBlock[nCntBlock].nCntTime < 0)
				{//�}�C�i�X��������
					g_aBlock[nCntBlock].move = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
				}
				break;

			case BLOCKTYPE_MOVEY:
				//�J�E���g����
				g_aBlock[nCntBlock].nCntTime++;

				if (g_aBlock[nCntBlock].nCntTime >= 180)
				{//��萔��������
					g_aBlock[nCntBlock].nCntTime *= -1;
				}

				if (g_aBlock[nCntBlock].nCntTime >= 0)
				{//�v���X��������

					g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				}
				else if (g_aBlock[nCntBlock].nCntTime < 0)
				{//�}�C�i�X��������
					g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
				}
				break;
			}
		}
			g_aBlock[nCntBlock].pos += g_aBlock[nCntBlock].move;

			pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth;
			pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth;
			pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth;
			pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth;
			pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;
			pVtx[3].pos.z = 0.0f;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aBlock[nCntBlock].fWidth / BLOCK_WIDTH, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, g_aBlock[nCntBlock].fHeight / BLOCK_HEIGHT);
			pVtx[3].tex = D3DXVECTOR2(g_aBlock[nCntBlock].fWidth / BLOCK_WIDTH, g_aBlock[nCntBlock].fHeight / BLOCK_HEIGHT);

		//���_�f�[�^�̃|�C���^���l���i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//--------------------
//�u���b�N�̕`�揈��
//--------------------
void DrawBlock(void)
{
	int nCntBlock;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�u���b�N�̕`��
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�u���b�N���g�p����Ă���

				//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntBlock,							//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);
		}
	}
}

//----------------
//���܂̐ݒ菈��
//----------------
void SetBlock(D3DXVECTOR3 pos, int nType, float width, float height)
{
	int nCntBlock;

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ�

			g_aBlock[nCntBlock].pos = pos;			//�ʒu
			g_aBlock[nCntBlock].nType = nType;		//���
			g_aBlock[nCntBlock].fWidth = width;		//��
			g_aBlock[nCntBlock].fHeight = height;	//����
			g_aBlock[nCntBlock].bUse = true;		//�g�p���Ă����Ԃɂ���

			//���_���p�̐ݒ�
			pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth;
			pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth;
			pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth;
			pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth;
			pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;
			pVtx[3].pos.z = 0.0f;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aBlock[nCntBlock].fWidth / BLOCK_WIDTH, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, g_aBlock[nCntBlock].fHeight / BLOCK_HEIGHT);
			pVtx[3].tex = D3DXVECTOR2(g_aBlock[nCntBlock].fWidth / BLOCK_WIDTH, g_aBlock[nCntBlock].fHeight / BLOCK_HEIGHT);
			break;
		}

		//���_�f�[�^�̃|�C���^���l���i�߂�
		pVtx += 4;

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//====================================
//�u���b�N�̓����蔻��
//====================================
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPMove, float fHeight, float fWidth)
{
	bool bLanding = false;	//���n���Ă��邩�ǂ���

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->y - PLAYER_HEIGHT < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
				pPos->y  > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight)
			{//�v���C���[�̏㑤���u���b�N�̏㉺���ʂ̒�,�v���C���[�̉������u���b�N�̏㉺���ʂ̒�

				if (pPosOld->x - PLAYER_WIDTH >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth &&
					pPos->x - PLAYER_WIDTH <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
				{//�E���獶�ւ̓����蔻��,�I���h�|�X���u���b�N�E�ʈȏ�E�A�|�X���u���b�N�E�ʈȉ���

					//�E���ʓ����蔻��
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + PLAYER_WIDTH;
					pPMove->x = 0.0f;
				}
				else if (pPosOld->x + PLAYER_WIDTH <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth &&
					pPos->x + PLAYER_WIDTH >= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth)
				{//������E�ւ̓����蔻��,�I���h�|�X���u���b�N���ʈȉ��A�|�X���u���b�N���ʈȏ�

					//�����ʓ����蔻��
					pPos->x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - PLAYER_WIDTH;
					pPMove->x = 0.0f;
				}
			}

			if (pPos->x + PLAYER_WIDTH > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth &&
				pPos->x - PLAYER_WIDTH < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
			{//�v���C���[�̉E�����u���b�N�̍��E���ʂ̒�,�v���C���[�̍������u���b�N�̍��E���ʂ̒�

				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight &&
					pPos->y >= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight)
				{//�ォ�牺�ւ̓����蔻��,�I���h�|�X���u���b�N��ʈȏ�A�|�X���u���b�N��ʈȉ�

					//��ʓ����蔻��
					bLanding = true;
					pPos->y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;
					pPMove->y = 0.0f;
				}
				else if (pPosOld->y - PLAYER_HEIGHT >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
					pPos->y - PLAYER_HEIGHT <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{//�������ւ̓����蔻��,�I���h�|�X���u���b�N��ʈȏ�A�|�X���u���b�N��ʈȉ�

					//���ʓ����蔻��
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT;
					pPMove->y = 0.0f;
				}
			}
		}
	}

	return bLanding;
}

//====================================
//�u���b�N�̓����蔻��X
//====================================
void CollisionBlockX(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPMove, float fHeight, float fWidth, BLOCK** pBlock)
{
	bool bLanding = false;	//���n���Ă��邩�ǂ���

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->y - PLAYER_HEIGHT < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
				pPos->y  > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight)
			{//�v���C���[�̏㑤���u���b�N�̏㉺���ʂ̒�,�v���C���[�̉������u���b�N�̏㉺���ʂ̒�

				if (pPosOld->x - PLAYER_WIDTH >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth &&
					pPos->x - PLAYER_WIDTH <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
				{//�E���獶�ւ̓����蔻��,�I���h�|�X���u���b�N�E�ʈȏ�E�A�|�X���u���b�N�E�ʈȉ���

					//�E���ʓ����蔻��
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + PLAYER_WIDTH;
					pPMove->x = 0.0f;
				}
				else if (pPosOld->x + PLAYER_WIDTH <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth &&
					pPos->x + PLAYER_WIDTH >= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth)
				{//������E�ւ̓����蔻��,�I���h�|�X���u���b�N���ʈȉ��A�|�X���u���b�N���ʈȏ�

					//�����ʓ����蔻��
					pPos->x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - PLAYER_WIDTH;
					pPMove->x = 0.0f;
				}
			}
		}
	}
}

//====================================
//�u���b�N�̓����蔻��Y
//====================================
bool CollisionBlockY(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPMove, float fHeight, float fWidth, BLOCK** pBlock)
{
	bool bLanding = false;	//���n���Ă��邩�ǂ���

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->x + PLAYER_WIDTH > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth &&
				pPos->x - PLAYER_WIDTH < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
			{//�v���C���[�̉E�����u���b�N�̍��E���ʂ̒�,�v���C���[�̍������u���b�N�̍��E���ʂ̒�

				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight &&
					pPos->y >= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight)
				{//�ォ�牺�ւ̓����蔻��,�I���h�|�X���u���b�N��ʈȏ�A�|�X���u���b�N��ʈȉ�

					//��ʓ����蔻��
					bLanding = true;
					pPos->y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;
					pPMove->y = 0.0f;

					if (pBlock != NULL)
					{//�u���b�N�̃A�h���X������ꏊ������
						*pBlock = &g_aBlock[nCntBlock];//�u���b�N�̃A�h���X����
					}
				}
				else if (pPosOld->y - PLAYER_HEIGHT >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
					pPos->y - PLAYER_HEIGHT <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{//�������ւ̓����蔻��,�I���h�|�X���u���b�N��ʈȏ�A�|�X���u���b�N��ʈȉ�

					//���ʓ����蔻��
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT;
					pPMove->y = 0.0f;
				}
			}
		}
	}

	return bLanding;
}

//============================
//�u���b�N�擾
//============================
BLOCK* GetBlock(void)
{
	return &g_aBlock[0];
}
