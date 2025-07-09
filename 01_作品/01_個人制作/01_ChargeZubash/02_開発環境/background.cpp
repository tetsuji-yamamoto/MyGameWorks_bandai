#include "main.h"
#include "background.h"
#include "game.h"

//�w�i�\����
typedef struct
{
	const char* pFileName;	//�t�@�C����
	int nType;				//�^�C�v
	D3DXCOLOR col;			//�F
	float fTexMoveX;		//�e�N�X�`���̓���X
	float fTexMoveY;		//�e�N�X�`���̓���Y
	bool bUse;				//�g�p���Ă邩�ǂ���
}Background;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_aPTextureBG[BGTYPE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Background g_aBG[BGTYPE_MAX];								//�w�i�|���S���̏��

//==============================================
//�w�i��ʂ̏���������
//==============================================
void InitBG(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * BGTYPE_MAX, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//���̏�����
	for (nCntBG = 0; nCntBG < BGTYPE_MAX; nCntBG++)
	{
		g_aBG[nCntBG].nType = BGTYPE_MAX;
		g_aBG[nCntBG].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBG[nCntBG].fTexMoveX = 0.0f;
		g_aBG[nCntBG].fTexMoveY = 0.0f;
		g_aBG[nCntBG].bUse = false;

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			g_aBG[nCntBG].pFileName,
			&g_aPTextureBG[nCntBG]);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}
//==============================================
//�w�i��ʂ̏I������
//==============================================
void UninitBG(void)
{
	for (int nCntBG = 0; nCntBG < BGTYPE_MAX; nCntBG++)
	{
		//�e�N�X�`���̔j��
		if (g_aPTextureBG[nCntBG] != NULL)
		{
			g_aPTextureBG[nCntBG]->Release();
			g_aPTextureBG[nCntBG] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//==============================================
//�w�i��ʂ̍X�V����
//==============================================
void UpdateBG(void)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//�T��
	for (int nCntBG = 0; nCntBG < BGTYPE_MAX; nCntBG++)
	{
		if (g_aBG[nCntBG].bUse == true)
		{
			MoveBackground(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0001f, 0.0f, nCntBG);
			MoveBackground(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0002f, 0.0f, nCntBG);
		}

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aBG[nCntBG].col;
		pVtx[1].col = g_aBG[nCntBG].col;
		pVtx[2].col = g_aBG[nCntBG].col;
		pVtx[3].col = g_aBG[nCntBG].col;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_aBG[nCntBG].fTexMoveX, g_aBG[nCntBG].fTexMoveY);
		pVtx[1].tex = D3DXVECTOR2(1.0f + g_aBG[nCntBG].fTexMoveX, g_aBG[nCntBG].fTexMoveY);
		pVtx[2].tex = D3DXVECTOR2(g_aBG[nCntBG].fTexMoveX, 1.0f + g_aBG[nCntBG].fTexMoveY);
		pVtx[3].tex = D3DXVECTOR2(1.0f + g_aBG[nCntBG].fTexMoveX, 1.0f + g_aBG[nCntBG].fTexMoveY);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//==============================================
//�w�i��ʂ̕`�揈��
//==============================================
void DrawBG(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBG = 0; nCntBG < BGTYPE_MAX; nCntBG++)
	{
		if (g_aBG[nCntBG].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aPTextureBG[nCntBG]);

			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntBG,								//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);										//�`�悷��v���~�e�B�u�i�v���C���[�j��
		}
	}
}

//===============================
//�w�i�̐ݒ�
//===============================
void SetBackground(const char* pFileName,BGTYPE type,D3DXCOLOR col)
{

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//�T��
	for (int nCntBG = 0; nCntBG < BGTYPE_MAX; nCntBG++)
	{
		if (g_aBG[nCntBG].bUse == false)
		{
			g_aBG[nCntBG].pFileName = pFileName;
			g_aBG[nCntBG].col = col;
			g_aBG[nCntBG].nType = type;
			g_aBG[nCntBG].bUse = true;

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				g_aBG[nCntBG].pFileName,
				&g_aPTextureBG[nCntBG]);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col =g_aBG[nCntBG].col;
			pVtx[1].col =g_aBG[nCntBG].col;
			pVtx[2].col =g_aBG[nCntBG].col;
			pVtx[3].col =g_aBG[nCntBG].col;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//===============================
//�w�i�̓���
//===============================
void MoveBackground(D3DXCOLOR col, float texMoveX, float texMoveY, int nCntBG)
{

	g_aBG[nCntBG].fTexMoveX += texMoveX;
	g_aBG[nCntBG].fTexMoveY += texMoveY;

	if (g_aBG[nCntBG].fTexMoveX > 1.0f)
	{//�ő���傫���Ȃ�����
		g_aBG[nCntBG].fTexMoveX = 0.0f;
	}
	else if (g_aBG[nCntBG].fTexMoveX < -1.0f)
	{//�ŏ���菬�����Ȃ�����
		g_aBG[nCntBG].fTexMoveX = 0.0f;
	}

	if (g_aBG[nCntBG].fTexMoveY > 1.0f)
	{//�ő���傫���Ȃ�����
		g_aBG[nCntBG].fTexMoveY = 0.0f;
	}
	else if (g_aBG[nCntBG].fTexMoveY < -1.0f)
	{//�ŏ���菬�����Ȃ�����
		g_aBG[nCntBG].fTexMoveY = 0.0f;
	}
}

//===============================
//�w�i�̏I���
//===============================
void EndBackground(BGTYPE type)
{
	if (type != BGTYPE_MAX)
	{
		//�ʂŏ���
		for (int nCntBG = 0; nCntBG < BGTYPE_MAX; nCntBG++)
		{
			if (g_aBG[nCntBG].bUse == true && g_aBG[nCntBG].nType == type)
			{
				g_aBG[nCntBG].bUse = false;

				break;
			}
		}
	}
	else
	{
		//�S������
		for (int nCntBG = 0; nCntBG < BGTYPE_MAX; nCntBG++)
		{
			g_aBG[nCntBG].bUse = false;
		}
	}
}