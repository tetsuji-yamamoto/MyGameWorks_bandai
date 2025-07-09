#include "charge.h"
#include "player.h"
#include "particle.h"
#include "effect.h"
#include "input.h"
#include "sound.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_aPTextureCharger[CHARGEUITYPE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCharger = NULL;				//���_�o�b�t�@�ւ̃|�C���^
CHARGERUI g_aChagerUI[MAX_CHARGERUI];							//�[�d��UI�̍\����
CHARGE g_Charge;												//�[�d�p�����[�^�[�\����

//======================================
//�[�d��̏�����
//======================================
void InitCharge(void)
{
	int nCntCharger;

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_CHARGERUI, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCharger,
		NULL);

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffCharger->Lock(0, 0, (void**)&pVtx, 0);

	g_Charge.fChargrAmount = 0;
	g_Charge.nCntTime = 0;

	//�u���b�N�̏��̏�����
	for (nCntCharger = 0; nCntCharger < MAX_CHARGERUI; nCntCharger++)
	{
		g_aChagerUI[nCntCharger].pFileName = NULL;
		g_aChagerUI[nCntCharger].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aChagerUI[nCntCharger].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aChagerUI[nCntCharger].nType = CHARGEUITYPE_FLAME;
		g_aChagerUI[nCntCharger].nState = CHARGESTATE_NONE;
		g_aChagerUI[nCntCharger].nType = CHARGENUM_ZERO;
		g_aChagerUI[nCntCharger].fHeight = 0.0f;
		g_aChagerUI[nCntCharger].fWidth = 0.0f;
		g_aChagerUI[nCntCharger].bUse = false;

		//�ʒu�̏�����
		pVtx[0].pos.x = g_aChagerUI[nCntCharger].pos.x - g_aChagerUI[nCntCharger].fWidth;
		pVtx[0].pos.y = g_aChagerUI[nCntCharger].pos.y - g_aChagerUI[nCntCharger].fHeight;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aChagerUI[nCntCharger].pos.x + g_aChagerUI[nCntCharger].fWidth;
		pVtx[1].pos.y = g_aChagerUI[nCntCharger].pos.y - g_aChagerUI[nCntCharger].fHeight;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aChagerUI[nCntCharger].pos.x - g_aChagerUI[nCntCharger].fWidth;
		pVtx[2].pos.y = g_aChagerUI[nCntCharger].pos.y + g_aChagerUI[nCntCharger].fHeight;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aChagerUI[nCntCharger].pos.x + g_aChagerUI[nCntCharger].fWidth;
		pVtx[3].pos.y = g_aChagerUI[nCntCharger].pos.y + g_aChagerUI[nCntCharger].fHeight;
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
	g_pVtxBuffCharger->Unlock();

	for (nCntCharger = 0; nCntCharger < MAX_CHARGERUI * 0.5f; nCntCharger++)
	{
		SetCharger(FILE_TEX_CHARGER_FLAME, D3DXVECTOR3(CHARGE_WIDTH + CHARGE_WIDTH * 2 * nCntCharger,SCREEN_HEIGHT - CHARGE_HEIGHT * 3.0f, 0.0f), CHARGEUITYPE_FLAME, nCntCharger, CHARGE_WIDTH);
		SetCharger(FILE_TEX_CHARGER_GAUGE, D3DXVECTOR3(CHARGE_WIDTH + CHARGE_WIDTH * 2 * nCntCharger, SCREEN_HEIGHT - CHARGE_HEIGHT * 3.0f, 0.0f), CHARGEUITYPE_GAUGE, nCntCharger, CHARGE_WIDTH);
	}
}

//======================================
//�[�d��[�d��̏I��
//======================================
void UninitCharge(void)
{
	for (int nCntCharger = 0; nCntCharger < CHARGEUITYPE_MAX; nCntCharger++)
	{
		//�e�N�X�`���̔j��
		if (g_aPTextureCharger[nCntCharger] != NULL)
		{

			g_aPTextureCharger[nCntCharger]->Release();
			g_aPTextureCharger[nCntCharger] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCharger != NULL)
	{
		g_pVtxBuffCharger->Release();
		g_pVtxBuffCharger = NULL;
	}
}

//======================================
//�[�d��̃A�b�v�f�[�g
//======================================
void UpdateCharge(void)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffCharger->Lock(0, 0, (void**)&pVtx, 0);

	g_Charge.nCntTime++;

	//���d
	if (g_Charge.nCntTime >= 600)
	{//��莞�Ԃ�����
		g_Charge.nCntTime = 0.0f;
		ChargePower(-0.5f);
	}

	//������������
	for (int nCntCharger = 0; nCntCharger < MAX_CHARGERUI; nCntCharger++)
	{
		if (g_aChagerUI[nCntCharger].bUse == true)
		{
			//�d�r�t���[���̏�Ԃ��X�V
			ChargerFlameState(nCntCharger);
			//�d�r�Q�[�W�̏�Ԃ��X�V
			ChargerGaugeState(nCntCharger);

			//�ʒu
			pVtx[0].pos.x = g_aChagerUI[nCntCharger].pos.x - g_aChagerUI[nCntCharger].fWidth;
			pVtx[0].pos.y = g_aChagerUI[nCntCharger].pos.y - g_aChagerUI[nCntCharger].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aChagerUI[nCntCharger].pos.x + g_aChagerUI[nCntCharger].fWidth;
			pVtx[1].pos.y = g_aChagerUI[nCntCharger].pos.y - g_aChagerUI[nCntCharger].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aChagerUI[nCntCharger].pos.x - g_aChagerUI[nCntCharger].fWidth;
			pVtx[2].pos.y = g_aChagerUI[nCntCharger].pos.y + g_aChagerUI[nCntCharger].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aChagerUI[nCntCharger].pos.x + g_aChagerUI[nCntCharger].fWidth;
			pVtx[3].pos.y = g_aChagerUI[nCntCharger].pos.y + g_aChagerUI[nCntCharger].fHeight;
			pVtx[3].pos.z = 0.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aChagerUI[nCntCharger].col;
			pVtx[1].col = g_aChagerUI[nCntCharger].col;
			pVtx[2].col = g_aChagerUI[nCntCharger].col;
			pVtx[3].col = g_aChagerUI[nCntCharger].col;
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCharger->Unlock();
}

//======================================
//�[�d��̕`��
//======================================
void DrawCharge(void)
{
	int nCntCharger;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCharger, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�[�d��̕`��
	for (nCntCharger = 0; nCntCharger < MAX_CHARGERUI; nCntCharger++)
	{
		if (g_aChagerUI[nCntCharger].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aPTextureCharger[g_aChagerUI[nCntCharger].nType]);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntCharger,						//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);
		}
	}
}

//======================================
//�[�d
//======================================
void ChargePower(float fEPower)
{
	//�`���[�W
	g_Charge.fChargrAmount += fEPower;
	
	if (g_Charge.fChargrAmount > MAX_ELECTRICPOWER)
	{//�ő���傫�����Ȃ��悤�ɂ���
		g_Charge.fChargrAmount = MAX_ELECTRICPOWER;
	}
	else if (g_Charge.fChargrAmount < 0)
	{//�[����菬�����Ȃ�Ȃ��悤��
		g_Charge.fChargrAmount = 0;
	}
}

//======================================
//�[�d��̃t���[���̏��
//======================================
void ChargerFlameState(int nCntCharger)
{
	if(g_aChagerUI[nCntCharger].nType  == CHARGEUITYPE_FLAME)
	{
		//�ԐF�ɂ���
		g_aChagerUI[nCntCharger].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//�d�͂���ɗΐF�ɂ���
		if (g_aChagerUI[nCntCharger].nNumber < g_Charge.fChargrAmount)
		{
			g_aChagerUI[nCntCharger].col = D3DXCOLOR(0.0f,1.0f,0.0f,1.0f);
		}
	}
}

//======================================
//�[�d��̃Q�[�W�̏��
//======================================
void ChargerGaugeState(int nCntCharger)
{
	if (g_aChagerUI[nCntCharger].nType == CHARGEUITYPE_GAUGE)
	{
		//�����ɂ���
		g_aChagerUI[nCntCharger].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);

		//�d�͂���ɕs�����ɂ���
		if (g_aChagerUI[nCntCharger].nNumber < g_Charge.fChargrAmount)
		{
			g_aChagerUI[nCntCharger].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		}
	}
}

//======================================
//�[�d��ݒ�
//======================================
void SetCharger(const char *pFileName,D3DXVECTOR3 pos,CHARGERUITYPE type, int num, float fWidth)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffCharger->Lock(0, 0, (void**)&pVtx, 0);

	//������������
	for (int nCntCharger = 0; nCntCharger < MAX_CHARGERUI; nCntCharger++)
	{
		if (g_aChagerUI[nCntCharger].bUse == false)
		{
			g_aChagerUI[nCntCharger].pFileName = pFileName;
			g_aChagerUI[nCntCharger].pos = pos;
			g_aChagerUI[nCntCharger].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			g_aChagerUI[nCntCharger].nType = type;
			g_aChagerUI[nCntCharger].nNumber = num;
			g_aChagerUI[nCntCharger].nState = CHARGESTATE_NONE;
			g_aChagerUI[nCntCharger].fWidth = fWidth;
			g_aChagerUI[nCntCharger].fHeight = CHARGE_HEIGHT;
			g_aChagerUI[nCntCharger].bUse = true;

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pFileName,
				&g_aPTextureCharger[g_aChagerUI[nCntCharger].nType]);

			//�ʒu
			pVtx[0].pos.x = g_aChagerUI[nCntCharger].pos.x - g_aChagerUI[nCntCharger].fWidth;
			pVtx[0].pos.y = g_aChagerUI[nCntCharger].pos.y - g_aChagerUI[nCntCharger].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aChagerUI[nCntCharger].pos.x + g_aChagerUI[nCntCharger].fWidth;
			pVtx[1].pos.y = g_aChagerUI[nCntCharger].pos.y - g_aChagerUI[nCntCharger].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aChagerUI[nCntCharger].pos.x - g_aChagerUI[nCntCharger].fWidth;
			pVtx[2].pos.y = g_aChagerUI[nCntCharger].pos.y + g_aChagerUI[nCntCharger].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aChagerUI[nCntCharger].pos.x + g_aChagerUI[nCntCharger].fWidth;
			pVtx[3].pos.y = g_aChagerUI[nCntCharger].pos.y + g_aChagerUI[nCntCharger].fHeight;
			pVtx[3].pos.z = 0.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aChagerUI[nCntCharger].col;
			pVtx[1].col = g_aChagerUI[nCntCharger].col;
			pVtx[2].col = g_aChagerUI[nCntCharger].col;
			pVtx[3].col = g_aChagerUI[nCntCharger].col;

			break;
		}
		pVtx += 4;// ���_�f�[�^�̃|�C���^���l���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCharger->Unlock();
}

//======================================
// ���o
//======================================
void DisCharge(D3DXVECTOR3 pos)
{
	SetParticle(pos,								// �ʒu
		D3DXCOLOR(1.0f, 0.8f, 0.8f, 1.0f),			// �F
		EFFECTTYPE_NOMAL,	//���
		30,											// �o����
		0,											// �o���p�x
		40.0f,										// ����
		0.01f,										// �ړ��ʌ�����
		20.0f,										// �|���S���T�C�Y
		0.01f,										// �|���S���T�C�Y������
		D3DX_PI * 0.75f,							// �_���̒l
		15.0f,										// ����
		0.0f,										//�Œ�̈ړ���
		0.0f,										//��
		0.0f,				//����
		-1);
}

//======================================
// �[�d�����擾
//======================================
CHARGE* GetCharge(void)
{
	return &g_Charge;
}