#include "snowBall.h"
#include "bullet.h"
#include "block.h"

// �O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_aPTextureSB[SNOWBALLTYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSB = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
SNOWBALL_UI_MANAGER g_aSBUIMane[MAX_SB_POLIGON];			// ��ʊǗ����

//*********************************************************
// ��ʂ̏�����
//*********************************************************
void InitSB(void)
{
	int nCnt;

	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\bullet\\SBS_BULLET_SNOW_001.png",
		&g_aPTextureSB[SNOWBALLTYPE_SNOW]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\bullet\\SBS_BULLET_SNOW_001.png",
		&g_aPTextureSB[SNOWBALLTYPE_SNOW_MIDIUM]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\bullet\\SBS_BULLET_SNOW_001.png",
		&g_aPTextureSB[SNOWBALLTYPE_SNOW_BIG]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\bullet\\SBS_BULLET_ICE_001.png",
		&g_aPTextureSB[SNOWBALLTYPE_ICE]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\bullet\\SBS_BULLET_GRAVEL_001.png",
		&g_aPTextureSB[SNOWBALLTYPE_GRAVEL]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SB_POLIGON, // �K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSB,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffSB->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_SB_POLIGON; nCnt++)
	{
		g_aSBUIMane[nCnt].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aSBUIMane[nCnt].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aSBUIMane[nCnt].nType = SNOWBALLTYPE_MAX;
		g_aSBUIMane[nCnt].bUse = false;

		g_aSBUIMane[nCnt].rect.bottom = (long)0.0f;
		g_aSBUIMane[nCnt].rect.left = (long)0.0f;
		g_aSBUIMane[nCnt].rect.right = (long)0.0f;
		g_aSBUIMane[nCnt].rect.top = (long)0.0f;

		// ���_���W�̐ݒ�
		pVtx[0].pos = g_aSBUIMane[nCnt].pos;
		pVtx[1].pos = g_aSBUIMane[nCnt].pos;
		pVtx[2].pos = g_aSBUIMane[nCnt].pos;
		pVtx[3].pos = g_aSBUIMane[nCnt].pos;

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_aSBUIMane[nCnt].col;
		pVtx[1].col = g_aSBUIMane[nCnt].col;
		pVtx[2].col = g_aSBUIMane[nCnt].col;
		pVtx[3].col = g_aSBUIMane[nCnt].col;

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSB->Unlock();
}

//*********************************************************
// ��ʂ̏I��
//*********************************************************
void UninitSB(void)
{
	int nCnt = 0;
	for (nCnt = 0; nCnt < SNOWBALLTYPE_MAX; nCnt++)
	{// �e�N�X�`���ւ̃|�C���^�j��
		if (g_aPTextureSB[nCnt] != NULL)
		{
			g_aPTextureSB[nCnt]->Release();	
			g_aPTextureSB[nCnt] = NULL;
		}
	}

	if (g_pVtxBuffSB != NULL)
	{// ���_�o�b�t�@�ւ̃|�C���^�j��
		g_pVtxBuffSB->Release();
		g_pVtxBuffSB = NULL;
	}
}

//*********************************************************
// ��ʂ̍X�V
//*********************************************************
void UpdateSB(void)
{
	
}

//*********************************************************
// ��ʂ̕`��
//*********************************************************
void DrawSB(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSB, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_SB_POLIGON; nCnt++)
	{
 		if (g_aSBUIMane[nCnt].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aPTextureSB[g_aSBUIMane[nCnt].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				4 * nCnt,								// �`�悷��ŏ��̒��_�C���f�b�N�X
				2);										// �`�悷��v���~�e�B�u��
		}
	}
}

//*********************************************************
// ���UI�̐ݒ�
//*********************************************************
void SetSBUI(int nType, int nCntOrder)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	if (nCntOrder != -1)
	{
		// ���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
		g_pVtxBuffSB->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < MAX_SB_POLIGON; nCnt++)
		{
			if (g_aSBUIMane[nCnt].bUse == false)
			{
				float fRadius = 20.0f;
				g_aSBUIMane[nCnt].pos.z = 0.0f;
				g_aSBUIMane[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
				g_aSBUIMane[nCnt].nType = nType;
				g_aSBUIMane[nCnt].bUse = true;

				switch (nType)
				{
				case BULLETTYPE_SNOW:	// ���
					g_aSBUIMane[nCnt].pos.x = 20.0f;
					g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * (float)nCntOrder);
					g_aSBUIMane[nCnt].nType = SNOWBALLTYPE_SNOW;
					break;

				case BULLETTYPE_SNOW_MEDIUM:	// ��ʒ����炢
					g_aSBUIMane[nCnt].pos.x = 20.0f;
					g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * (float)nCntOrder);
					g_aSBUIMane[nCnt].nType = SNOWBALLTYPE_SNOW_MIDIUM;
					fRadius *= 1.5f;
					break;

				case BULLETTYPE_SNOW_BIG:// ���
					g_aSBUIMane[nCnt].pos.x = 20.0f;
					g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * (float)nCntOrder);
					g_aSBUIMane[nCnt].nType = SNOWBALLTYPE_SNOW_BIG;
					fRadius *= 2.0f;
					break;

				case BULLETTYPE_ICE:// �X��
					g_aSBUIMane[nCnt].pos.x = 60.0f;
					g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * (float)nCntOrder);
					g_aSBUIMane[nCnt].nType = SNOWBALLTYPE_ICE;
					break;

				case BULLETTYPE_GRAVEL:// ������
					g_aSBUIMane[nCnt].pos.x = 100.0f;
					g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * (float)nCntOrder);
					g_aSBUIMane[nCnt].nType = SNOWBALLTYPE_GRAVEL;
					break;
				}

				g_aSBUIMane[nCnt].rect.bottom = (long)fRadius;
				g_aSBUIMane[nCnt].rect.left = (long)-fRadius;
				g_aSBUIMane[nCnt].rect.right = (long)fRadius;
				g_aSBUIMane[nCnt].rect.top = (long)-fRadius;

				// ���_���W�̐ݒ�
				pVtx[0].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.left;
				pVtx[0].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.top;
				pVtx[0].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;

				pVtx[1].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.right;
				pVtx[1].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.top;
				pVtx[1].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;

				pVtx[2].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.left;
				pVtx[2].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.bottom;
				pVtx[2].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;

				pVtx[3].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.right;
				pVtx[3].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.bottom;
				pVtx[3].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;
				break;
			}
			pVtx += 4;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSB->Unlock();
}

//*********************************************************
// ��ʂ̏I���
//*********************************************************
void EndSBUI(SNOWBALL* pSnowBall, int nType)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffSB->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SB_POLIGON; nCnt++)
	{
		if (g_aSBUIMane[nCnt].bUse == true && g_aSBUIMane[nCnt].nType == nType)
		{
			g_aSBUIMane[nCnt].bUse = false;
			break;
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSB->Unlock();

	// ���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffSB->Lock(0, 0, (void**)&pVtx, 0);

	int nCntOrder = 0;

	for (int nCnt = 0; nCnt < MAX_SB_POLIGON; nCnt++)
	{
		
		switch (nType)
		{
		case BULLETTYPE_SNOW:	// ���
			if (g_aSBUIMane[nCnt].bUse == true && g_aSBUIMane[nCnt].nType == pSnowBall->nSnowOrder[nCntOrder])
			{
				g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * nCntOrder);
				nCntOrder++;
			}
			break;

		case BULLETTYPE_SNOW_MEDIUM:	// ��ʒ����炢
			if (g_aSBUIMane[nCnt].bUse == true && g_aSBUIMane[nCnt].nType == pSnowBall->nSnowOrder[nCntOrder])
			{
				g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * nCntOrder);
				nCntOrder++;
			}
			break;

		case BULLETTYPE_SNOW_BIG:// ���
			if (g_aSBUIMane[nCnt].bUse == true && g_aSBUIMane[nCnt].nType == pSnowBall->nSnowOrder[nCntOrder])
			{
				g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * nCntOrder);
				nCntOrder++;
			}
			break;

		case BULLETTYPE_ICE:	// �X��
			if (g_aSBUIMane[nCnt].bUse == true && g_aSBUIMane[nCnt].nType == pSnowBall->nIceOrder[nCntOrder])
			{
				g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * nCntOrder);
				nCntOrder++;
			}
			break;

		case BULLETTYPE_GRAVEL:	// ������
			if (g_aSBUIMane[nCnt].bUse == true && g_aSBUIMane[nCnt].nType == pSnowBall->nGravelOrder[nCntOrder])
			{
				g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * nCntOrder);
				nCntOrder++;
			}
			break;
		}
		

		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.left;
		pVtx[0].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.top;
		pVtx[0].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;

		pVtx[1].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.right;
		pVtx[1].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.top;
		pVtx[1].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;

		pVtx[2].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.left;
		pVtx[2].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.bottom;
		pVtx[2].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;

		pVtx[3].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.right;
		pVtx[3].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.bottom;
		pVtx[3].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSB->Unlock();
}

//*********************************************************
// ��ʍ���
//*********************************************************
int MakeOrderSnowBall(SNOWBALL *pSnowBall,int *nType)
{
	bool bSet = false;
	bool bMakeBall = false;
	int nCnt = 0;
	int nSnoOll = pSnowBall->nMakeTimerSnow + pSnowBall->nMakeTimerSnowMidi + pSnowBall->nMakeTimerSnowBig;	// ��ʂ̍��������

	if (nSnoOll >= SB_MAKETIMER_SNOW)
	{// ���
		*nType = BULLETTYPE_SNOW;
		bMakeBall = true;	// �����
	}

	if (nSnoOll >= SB_MAKETIMER_SNOW_MIDI)
	{// ��ʒ�
		*nType = BULLETTYPE_SNOW_MEDIUM;
		bMakeBall = true;	// �����
	}

	if (nSnoOll >= SB_MAKETIMER_SNOW_BIG)
	{// ��ʑ�
		*nType = BULLETTYPE_SNOW_BIG;
		bMakeBall = true;	// �����
	}

	if (pSnowBall->nMakeTimerIce >= SB_MAKETIMER_ICE)
	{// �X��
		*nType = BULLETTYPE_ICE;
		bMakeBall = true;	// �����
	}

	if (pSnowBall->nMakeTimerIGravel >= SB_MAKETIMER_GRAVEL)
	{// ������
		*nType = BULLETTYPE_GRAVEL;
		bMakeBall = true;	// �����
	}

	if (bMakeBall == false)
	{// ���ĂȂ�
		*nType = -1;
	}

	for (nCnt = 0; nCnt < 10; nCnt++)
	{
		if (*nType == -1)
		{// �J�E���g�s�\���A�^�C�v���Ȃ�������
			nCnt = -1;
			break;
		}

		switch (*nType)
		{
		case BULLETTYPE_SNOW:	// ���
			if (pSnowBall->nSnowOrder[nCnt] == -1)
			{
				pSnowBall->nSnowOrder[nCnt] = BULLETTYPE_SNOW;
				pSnowBall->nSnowBallWeight += SB_WEIGHT_SNOW;
				bSet = true;	// ������
			}
			break;

		case BULLETTYPE_SNOW_MEDIUM:	// ��ʒ����炢
			if (pSnowBall->nSnowOrder[nCnt] == -1)
			{
				pSnowBall->nSnowOrder[nCnt] = BULLETTYPE_SNOW_MEDIUM;
				pSnowBall->nSnowBallWeight += SB_WEIGHT_SNOW_MIDIUM;
				bSet = true;	// ������
			}
			break;

		case BULLETTYPE_SNOW_BIG:// ���
			if (pSnowBall->nSnowOrder[nCnt] == -1)
			{
				pSnowBall->nSnowOrder[nCnt] = BULLETTYPE_SNOW_BIG;
				pSnowBall->nSnowBallWeight += SB_WEIGHT_SNOW_BIG;
				bSet = true;	// ������
			}
			break;

		case BULLETTYPE_ICE:	// �X��
			if (pSnowBall->nIceOrder[nCnt] == -1)
			{
				pSnowBall->nIceOrder[nCnt] = BULLETTYPE_ICE;
				pSnowBall->nSnowBallWeight += SB_WEIGHT_ICE;
				bSet = true;	// ������
			}
			break;

		case BULLETTYPE_GRAVEL:	// ������
			if (pSnowBall->nGravelOrder[nCnt] == -1)
			{
				pSnowBall->nGravelOrder[nCnt] = BULLETTYPE_GRAVEL;
				pSnowBall->nSnowBallWeight += SB_WEIGHT_GRAVEL;
				bSet = true;	// ������
			}
			break;
		}

		if (bSet)
		{// �Z�b�g���I�������
			break;
		}
	}

	if (bSet == false)
	{// �Z�b�g���I�������
		nCnt = -1;
	}

	return nCnt;
}

//*********************************************************
// ��ʍ���
//*********************************************************
int BreakOrderSnowBall(SNOWBALL* pSnowBall, int nType)
{
	int nBallType = -1;

	// ��ԌÂ�����g����
	switch (nType)
	{
	case BULLETTYPE_SNOW:	// ���
		if (pSnowBall->nSnowOrder[0] != -1)
		{// �Ȃ񂩂�������
			nBallType = pSnowBall->nSnowOrder[0];			// �ۑ����ꂽ�^�C�v����
			pSnowBall->nSnowOrder[0] = -1;					// �Ȃ���
		}
		break;

	case BULLETTYPE_ICE:	// �X��
		if (pSnowBall->nIceOrder[0] != -1)
		{// �Ȃ񂩂�������
			nBallType = pSnowBall->nIceOrder[0];			// �ۑ����ꂽ�^�C�v����
			pSnowBall->nIceOrder[0] = -1;					// �Ȃ���
		}
		break;

	case BULLETTYPE_GRAVEL:	// ������
		if (pSnowBall->nGravelOrder[0] != -1)
		{// �Ȃ񂩂�������
			nBallType = pSnowBall->nGravelOrder[0];			// �ۑ����ꂽ�^�C�v����
			pSnowBall->nGravelOrder[0] = -1;				// �Ȃ���
		}
		break;
	}

	if (nBallType != -1)
	{
		// �d�����炵�܂���
		switch (nBallType)
		{
		case BULLETTYPE_SNOW:	// ���
			pSnowBall->nSnowBallWeight -= SB_WEIGHT_SNOW;	// �d�����炷
			break;

		case BULLETTYPE_SNOW_MEDIUM:	// ����
			pSnowBall->nSnowBallWeight -= SB_WEIGHT_SNOW_MIDIUM;	// �d�����炷
			break;

		case BULLETTYPE_SNOW_BIG:	// ���
			pSnowBall->nSnowBallWeight -= SB_WEIGHT_SNOW_BIG;	// �d�����炷
			break;

		case BULLETTYPE_ICE:	// �X��
			pSnowBall->nSnowBallWeight -= SB_WEIGHT_ICE;	// �d�����炷
			break;

		case BULLETTYPE_GRAVEL:	// ������
			pSnowBall->nSnowBallWeight -= SB_WEIGHT_GRAVEL;	// �d�����炷
			break;
		}

		// ���ג���
		for (int nCnt = 1; nCnt < 12; nCnt++)
		{
			switch (nType)
			{
			case BULLETTYPE_SNOW:	// ���
				pSnowBall->nSnowOrder[nCnt - 1] = pSnowBall->nSnowOrder[nCnt];
				break;

			case BULLETTYPE_SNOW_MEDIUM:	// ����
				pSnowBall->nSnowOrder[nCnt - 1] = pSnowBall->nSnowOrder[nCnt];
				break;

			case BULLETTYPE_SNOW_BIG:	// ���
				pSnowBall->nSnowOrder[nCnt - 1] = pSnowBall->nSnowOrder[nCnt];
				break;

			case BULLETTYPE_ICE:	// �X��
				pSnowBall->nIceOrder[nCnt - 1] = pSnowBall->nIceOrder[nCnt];
				break;

			case BULLETTYPE_GRAVEL:	// ������
				pSnowBall->nGravelOrder[nCnt - 1] = pSnowBall->nGravelOrder[nCnt];
				break;
			}
		}
	}

	// ���ʂ�Ԃ�
	return nBallType;
}

//*********************************************************
// ��ʍ�鎞�Ԍv��
//*********************************************************
void MakeSnowBall(SNOWBALL* pSnowBall,int nMakeType)
{
	//if (nMakeType != pSnowBall->nMakeType)
	//{// ����Ă��ވ������
	//	pSnowBall->nMakeType = nMakeType;	// ���C�N�^�C�v�ύX
	//	pSnowBall->nMakeTimer = 0;			// �J�E���g���Z�b�g
	//}

	//pSnowBall->nMakeTimer++;	// �J�E���g�ǉ�
}