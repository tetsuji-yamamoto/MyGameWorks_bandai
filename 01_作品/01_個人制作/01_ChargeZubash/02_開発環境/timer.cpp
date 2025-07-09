#include "timer.h"
#include "game.h"
#include "fade.h"
#include "result.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;		//Direct3D�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
TIMER g_Timer;									//�^�C�}�[���

//===================
//�^�C�}�[�̏���������
//===================
void InitTimer(void)
{
	int nCnt;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_NUMBER,
		&g_pTextureTimer);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME_NUM, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	g_Timer.nTimer = MAX_TIME;					//�l������������
	g_Timer.nTimerCount = 0;					//�J�E���g������
	g_Timer.nTaimerState = TIMERSTATE_NOMAL;	//�^�C�}�[�󋵏�����

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx; 

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_TIME_NUM; nCnt++)
	{
		g_Timer.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - MAX_TIME_NUM_WIDTH * 0.4f * 3.0f + MAX_TIME_NUM_WIDTH * nCnt, MAX_TIME_NUM_HEIGHT , 0.0f);	//�ʒu������������
		g_Timer.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);								//�F������������

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Timer.pos.x - MAX_TIME_NUM_WIDTH / 2, g_Timer.pos.y - MAX_TIME_NUM_WIDTH / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Timer.pos.x + MAX_TIME_NUM_WIDTH / 2, g_Timer.pos.y - MAX_TIME_NUM_WIDTH / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Timer.pos.x - MAX_TIME_NUM_WIDTH / 2, g_Timer.pos.y + MAX_TIME_NUM_WIDTH / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Timer.pos.x + MAX_TIME_NUM_WIDTH / 2, g_Timer.pos.y + MAX_TIME_NUM_WIDTH / 2, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_Timer.col;
		pVtx[1].col = g_Timer.col;
		pVtx[2].col = g_Timer.col;
		pVtx[3].col = g_Timer.col;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();
	AddTimer();
}
//===================
//�^�C�}�[�̏I������
//===================
void UninitTimer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}
//===================
//�^�C�}�[�̍X�V����
//===================
void UpdateTimer(void)
{
	int nCnt;

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
	//���Ԑ؂�܂���
	if (g_Timer.nTaimerState == TIMERSTATE_UP)
	{
		for (int nCnt = 0; nCnt < MAX_TIME_NUM; nCnt++)
		{
			g_Timer.pos = D3DXVECTOR3(200.0f + SCREEN_WIDTH * 0.3 * nCnt, SCREEN_HEIGHT * 0.5f, 0.0f);	//�ʒu������������
			g_Timer.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);												//�F������������

			//�ʒu�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_Timer.pos.x - SCREEN_WIDTH * 0.3 * 0.5, g_Timer.pos.y - MAX_TIMEUP_NUM_WIDTH / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Timer.pos.x + SCREEN_WIDTH * 0.3 * 0.5, g_Timer.pos.y - MAX_TIMEUP_NUM_WIDTH / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Timer.pos.x - SCREEN_WIDTH * 0.3 * 0.5, g_Timer.pos.y + MAX_TIMEUP_NUM_WIDTH / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Timer.pos.x + SCREEN_WIDTH * 0.3 * 0.5, g_Timer.pos.y + MAX_TIMEUP_NUM_WIDTH / 2, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_Timer.col;
			pVtx[1].col = g_Timer.col;
			pVtx[2].col = g_Timer.col;
			pVtx[3].col = g_Timer.col;

			pVtx += 4;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();
	//���Ԃ������Ă���
	if (g_Timer.nTimer > 0 && GetGameState() == GAMESTATE_NORMAL)
	{
		g_Timer.nTimerCount++;
		if (g_Timer.nTimerCount >= 60)
		{
			g_Timer.nTimerCount = 0;
			g_Timer.nTimer--;
			AddTimer();
		}
	}
	//�󋵂�ς���
	if(g_Timer.nTimer <= 10)
	{
		g_Timer.nTaimerState = TIMERSTATE_UP;
	}
	//���Ԑ؂�
	if(g_Timer.nTimer <= 0 && GetGameState() == GAMESTATE_NORMAL)
	{
		//�t�F�[�h�A�E�g����
		SetFade(MODE_RESULT);
		SetResult(RESULTTYPE_TIMEOVER);
	}
}
//===================
//�^�C�}�[�̕`�揈��
//===================
void DrawTimer(void)
{
	int nCnt;
	//�K�v�������̕`��
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (nCnt = 0; nCnt < MAX_TIME_NUM; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTimer);
		//�w�i�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			4 * nCnt,								//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);										//�`�悷��v���~�e�B�u�i�w�i�j��
	}
}
//===================
//�^�C�}�[�̉��Z����
//===================
void AddTimer(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx; 

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	int aPosTexU[3] = {};//�i���̐������i�[
	int nData1 = 100, nData2 = 10;
	int nCnt;

	//�����Ƃɕ�������
	for (nCnt = 0; nCnt < MAX_TIME_NUM; nCnt++)
	{
		if (nCnt == 0)
		{
			aPosTexU[0] = g_Timer.nTimer / nData1;
		}
		else
		{
			aPosTexU[nCnt] = (g_Timer.nTimer % nData1 / nData2);
			nData1 /= 10;
			nData2 /= 10;
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();
}
//----------------------
//�^�C�}�[�擾
//----------------------
TIMER* GetTimer(void)
{
	return &g_Timer;
}