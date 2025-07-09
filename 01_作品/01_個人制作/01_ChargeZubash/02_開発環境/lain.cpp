#include "lain.h"
#include "sound.h"
//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureLain = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLain = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Lain g_lain;										//�J�|���S���̏��

//==============================================
//�J��ʂ̏���������
//==============================================
void InitLain(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLain,
		NULL);

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffLain->Lock(0, 0, (void**)&pVtx, 0);

	//���̏�����

	g_lain.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
	g_lain.fTexMoveX = 0.0f;
	g_lain.fTexMoveY = 0.0f;
	g_lain.bUse = true;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\LAIN\\Lein_001.png",
		&g_pTextureLain);

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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLain->Unlock();

	//�J��
	PlaySound(SOUND_LABEL_LEIN_BGM);
}
//==============================================
//�J��ʂ̏I������
//==============================================
void UninitLain(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureLain != NULL)
	{
		g_pTextureLain->Release();
		g_pTextureLain = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLain != NULL)
	{
		g_pVtxBuffLain->Release();
		g_pVtxBuffLain = NULL;
	}

	g_lain.bUse = false;//�g�p���Ȃ�
}

//==============================================
//�J��ʂ̍X�V����
//==============================================
void UpdateLain(void)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffLain->Lock(0, 0, (void**)&pVtx, 0);

	if (g_lain.bUse == true)
	{
		g_lain.fTexMoveX += 0.001f;
		g_lain.fTexMoveY -=0.05f;

		if (g_lain.fTexMoveX > 1.0f)
		{//�ő���傫���Ȃ�����
			g_lain.fTexMoveX = 0.0f;
		}
		else if (g_lain.fTexMoveX < -1.0f)
		{//�ŏ���菬�����Ȃ�����
			g_lain.fTexMoveX = 0.0f;
		}

		if (g_lain.fTexMoveY > 1.0f)
		{//�ő���傫���Ȃ�����
			g_lain.fTexMoveY = 0.0f;
		}
		else if (g_lain.fTexMoveY < -1.0f)
		{//�ŏ���菬�����Ȃ�����
			g_lain.fTexMoveY = 0.0f;
		}
	}

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_lain.col;
	pVtx[1].col = g_lain.col;
	pVtx[2].col = g_lain.col;
	pVtx[3].col = g_lain.col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_lain.fTexMoveX, g_lain.fTexMoveY);
	pVtx[1].tex = D3DXVECTOR2(1.0f + g_lain.fTexMoveX, g_lain.fTexMoveY);
	pVtx[2].tex = D3DXVECTOR2(g_lain.fTexMoveX, 1.0f + g_lain.fTexMoveY);
	pVtx[3].tex = D3DXVECTOR2(1.0f + g_lain.fTexMoveX, 1.0f + g_lain.fTexMoveY);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLain->Unlock();
}

//==============================================
//�J��ʂ̕`�揈��
//==============================================
void DrawLain(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLain, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_lain.bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureLain);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			0,										//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);										//�`�悷��v���~�e�B�u�i�v���C���[�j��
	}

}