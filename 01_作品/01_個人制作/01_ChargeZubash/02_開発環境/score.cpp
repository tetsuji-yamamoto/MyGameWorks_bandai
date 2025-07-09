#include "score.h"
#include "player.h"
//�}�N��
#define MAX_NUM (8)			//����
#define MAX_NUM_HEIGHT (50) //������
#define MAX_NUM_WIDTH (50)	//��
//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;		//Direct3D�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posScore;							//�X�R�A�̈ʒu
int g_nScore;									//�X�R�A�̒l
//------------------------
//�X�R�A�̏���������
//------------------------
void InitScore(void)
{
	int nCnt;
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	
	g_posScore = D3DXVECTOR3(SCREEN_WIDTH - 50.0f * MAX_NUM, MAX_NUM_HEIGHT * 0.5f,0.0f);	//�ʒu������������
	g_nScore = 0;															//�l������������

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\SCORE\\number000.png",
		&g_pTextureScore);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D* pVtx; //���_���ւ̂ۂ����
	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{	
		//���_���W�̐ݒ�
		pVtx[0].pos = g_posScore + D3DXVECTOR3(0.0f + (MAX_NUM_WIDTH * nCnt), 0.0f, 0.0f);
		pVtx[1].pos = g_posScore + D3DXVECTOR3(MAX_NUM_WIDTH + (MAX_NUM_WIDTH * nCnt), 0.0f, 0.0f);
		pVtx[2].pos = g_posScore + D3DXVECTOR3(0.0f + (MAX_NUM_WIDTH * nCnt), MAX_NUM_HEIGHT, 0.0f);
		pVtx[3].pos = g_posScore + D3DXVECTOR3(MAX_NUM_WIDTH + (MAX_NUM_WIDTH * nCnt), MAX_NUM_HEIGHT, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//------------------------
//�X�R�A�̏I������
//------------------------
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}
//------------------------
//�X�R�A�̍X�V����
//------------------------
void UpdateScore(void)
{

}
//------------------------
//�X�R�A�̕`�揈��
//------------------------
void DrawScore(void)
{
	int nCnt;
	//�K�v�������̕`��
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureScore);
		//�w�i�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			4 * nCnt,								//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);										//�`�悷��v���~�e�B�u�i�w�i�j��
	}
}
//------------------------
//�X�R�A�̐ݒ菈��
//------------------------
void SetScore(int nScore)
{
	//int aPosTexU[8];//�i���̐������i�[
	g_nScore = nScore;
}
//------------------------
//�X�R�A�̉��Z����
//------------------------
void AddScore(int nValu)
{
	//���_���ւ̂ۂ����
	VERTEX_2D* pVtx; 
	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	int aPosTexU[8] = {};//�i���̐������i�[
	int nData1 = 10000000, nData2 = 1000000;
	int nCnt;
	g_nScore += nValu;
	//�����Ƃɕ�������
	for (nCnt = 0; nCnt < 8; nCnt++)
	{
		if (nCnt == 0)
		{
			aPosTexU[0] = g_nScore / nData1;
		}
		else
		{
			aPosTexU[nCnt] = (g_nScore % nData1 / nData2);
			nData1 /= 10;
			nData2 /= 10;
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt]			, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt]			, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//----------------------
//�X�R�A�擾
//----------------------
int GetScore(void)
{
	return g_nScore;
}