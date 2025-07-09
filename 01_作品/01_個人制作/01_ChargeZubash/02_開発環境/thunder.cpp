#include "main.h"
#include "thunder.h"
#include "particle.h"
#include "effect.h"
#include "block.h"
#include "player.h"
#include "charge.h"
#include "sound.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_aPTextureThunder[THUNDERTYPE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffThunder = NULL;				//���_�o�b�t�@�ւ̃|�C���^
THUNDER g_aThunder[MAX_THUNDER];								//���|���S���̏��
int nCntThunderLight;											//������܂ł̊�

//======================================
//��������
//======================================
void InitThunder(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	int nCntThunder;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_THUNDER, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffThunder,
		NULL);

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffThunder->Lock(0, 0, (void**)&pVtx, 0);

	nCntThunderLight = 0;

	//������������
	for (nCntThunder = 0; nCntThunder < MAX_THUNDER; nCntThunder++)
	{
		g_aThunder[nCntThunder].pFileName = NULL;
		g_aThunder[nCntThunder].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aThunder[nCntThunder].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aThunder[nCntThunder].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aThunder[nCntThunder].col = D3DXCOLOR(RGBA_FULLCOLOR);
		g_aThunder[nCntThunder].nType = THUNDERTYPE_NOMAL;
		g_aThunder[nCntThunder].nThunderx = 0;
		g_aThunder[nCntThunder].nDirection = THUNDERDIRECT_XSELECT;
		g_aThunder[nCntThunder].nCntTiming = 0;
		g_aThunder[nCntThunder].nCntStrikeTime = 0;
		g_aThunder[nCntThunder].nEPower = 2;
		g_aThunder[nCntThunder].fThunderHeight = 0.0f;
		g_aThunder[nCntThunder].fThunderWidth = 0.0f;
		g_aThunder[nCntThunder].bUse = false;
		g_aThunder[nCntThunder].bHit = false;
		g_aThunder[nCntThunder].bFell = false;

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

		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffThunder->Unlock();
}
//======================================
//���I��
//======================================
void UninitThunder(void)
{
	for (int nCntThunder = 0; nCntThunder < THUNDERTYPE_MAX; nCntThunder++)
	{
		//�e�N�X�`���̔j��
		if (g_aPTextureThunder[nCntThunder] != NULL)
		{
			g_aPTextureThunder[nCntThunder]->Release();
			g_aPTextureThunder[nCntThunder] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffThunder != NULL)
	{
		g_pVtxBuffThunder->Release();
		g_pVtxBuffThunder = NULL;
	}
}
//======================================
//���X�V
//======================================
void UpdateThunder(void)
{
	VERTEX_2D* pVtx;

	//�����܂ł̃J�E���g�����Z
	nCntThunderLight--;

	if (nCntThunderLight <= 0)
	{//��莞�Ԃ�������

		nCntThunderLight = (rand() % 120) + 60;

		//����ݒ�
		SetThunder(FILE_TEX_THUNDER, THUNDERTYPE_NOMAL);
	}

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffThunder->Lock(0, 0, (void**)&pVtx, 0);

	//�g���Ă��闋���X�V���Ă���
	for (int nCntThunder = 0; nCntThunder < MAX_THUNDER; nCntThunder++)
	{
		if (g_aThunder[nCntThunder].bUse == true)
		{//�g���Ă�����
			//����
			LightningStrike(nCntThunder);

			//�ʒu
			pVtx[0].pos.x = g_aThunder[nCntThunder].pos.x - g_aThunder[nCntThunder].fThunderWidth;
			pVtx[0].pos.y = g_aThunder[nCntThunder].pos.y - g_aThunder[nCntThunder].fThunderHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aThunder[nCntThunder].pos.x + g_aThunder[nCntThunder].fThunderWidth;
			pVtx[1].pos.y = g_aThunder[nCntThunder].pos.y - g_aThunder[nCntThunder].fThunderHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aThunder[nCntThunder].pos.x - g_aThunder[nCntThunder].fThunderWidth;
			pVtx[2].pos.y = g_aThunder[nCntThunder].pos.y;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aThunder[nCntThunder].pos.x + g_aThunder[nCntThunder].fThunderWidth;
			pVtx[3].pos.y = g_aThunder[nCntThunder].pos.y;
			pVtx[3].pos.z = 0.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aThunder[nCntThunder].col;
			pVtx[1].col = g_aThunder[nCntThunder].col;
			pVtx[2].col = g_aThunder[nCntThunder].col;
			pVtx[3].col = g_aThunder[nCntThunder].col;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffThunder->Unlock();

}
//======================================
//���`��
//======================================
void DrawThunder(void)
{
	int nCntThunder;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffThunder, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���̕`��
	for (nCntThunder = 0; nCntThunder < MAX_THUNDER; nCntThunder++)
	{
		if (g_aThunder[nCntThunder].bUse == true)
		{//�����g�p����Ă���

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aPTextureThunder[g_aThunder[nCntThunder].nType]);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntThunder,						//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);
		}
	}
}

//======================================
//���ݒ�
//======================================
void SetThunder(const char* pFileName, THUNDERTYPE type)
{

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffThunder->Lock(0, 0, (void**)&pVtx, 0);

	//������������
	for (int nCntThunder = 0; nCntThunder < MAX_THUNDER; nCntThunder++)
	{
		if (g_aThunder[nCntThunder].bUse == false)
		{
			g_aThunder[nCntThunder].pFileName = pFileName;
			g_aThunder[nCntThunder].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aThunder[nCntThunder].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aThunder[nCntThunder].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aThunder[nCntThunder].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			g_aThunder[nCntThunder].nType = type;
			g_aThunder[nCntThunder].nCntTiming = 0;
			g_aThunder[nCntThunder].nCntStrikeTime = 0;
			g_aThunder[nCntThunder].nEPower = 2;
			g_aThunder[nCntThunder].fThunderWidth = THUNDER_WIDTH;
			g_aThunder[nCntThunder].fThunderHeight = SCREEN_HEIGHT;
			g_aThunder[nCntThunder].bUse = true;
			g_aThunder[nCntThunder].bHit = false;
			g_aThunder[nCntThunder].bFell = false;

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				g_aThunder[nCntThunder].pFileName,
				&g_aPTextureThunder[g_aThunder[nCntThunder].nType]);

			//�ʒu
			pVtx[0].pos.x = g_aThunder[nCntThunder].pos.x - g_aThunder[nCntThunder].fThunderWidth;
			pVtx[0].pos.y = g_aThunder[nCntThunder].pos.y - g_aThunder[nCntThunder].fThunderHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aThunder[nCntThunder].pos.x + g_aThunder[nCntThunder].fThunderWidth;
			pVtx[1].pos.y = g_aThunder[nCntThunder].pos.y - g_aThunder[nCntThunder].fThunderHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aThunder[nCntThunder].pos.x - g_aThunder[nCntThunder].fThunderWidth;
			pVtx[2].pos.y = g_aThunder[nCntThunder].pos.y;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aThunder[nCntThunder].pos.x + g_aThunder[nCntThunder].fThunderWidth;
			pVtx[3].pos.y = g_aThunder[nCntThunder].pos.y;
			pVtx[3].pos.z = 0.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aThunder[nCntThunder].col;
			pVtx[1].col = g_aThunder[nCntThunder].col;
			pVtx[2].col = g_aThunder[nCntThunder].col;
			pVtx[3].col = g_aThunder[nCntThunder].col;

			break;
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffThunder->Unlock();
}

//======================================
//����lightning strike
//======================================
void LightningStrike(int nCntThunder)
{
	//�O�̈ʒu���X�V
	g_aThunder[nCntThunder].posOld = g_aThunder[nCntThunder].pos;

	//���o���ɏ���
	switch (g_aThunder[nCntThunder].nDirection)
	{
	case THUNDERDIRECT_XSELECT:
		//������ꏊ�����߂�
		SelectStrike(nCntThunder);
		g_aThunder[nCntThunder].nDirection = THUNDERDIRECT_PREMONISION;
		break;

	case THUNDERDIRECT_YSELECT:
		g_aThunder[nCntThunder].nDirection = THUNDERDIRECT_PREMONISION;
		break;

	case THUNDERDIRECT_PREMONISION:
		//�\��

		g_aThunder[nCntThunder].pos.y += SCREEN_HEIGHT / 60;

		//�p�[�e�B�N������
		SetParticle(D3DXVECTOR3(g_aThunder[nCntThunder].pos.x, g_aThunder[nCntThunder].pos.y, 0.0f),	//�ʒu
			D3DXCOLOR(1.0f, 0.8f, 0.8f, 1.0f),			//�F
			EFFECTTYPE_THUNDER,	//���
			1,					//�o����
			100,				//�o���p�x
			2.0f,				//����
			0.1f,				//�ړ��ʌ�����
			4.0f,				//�|���S���T�C�Y
			0.001f,				//�|���S���T�C�Y������
			0.0f,				//�_���̊p�x
			300,				//����
			1.0f,				//�Œ�̈ړ���
			0.0f,				//��
			0.0f,				//����
			nCntThunder);

		//�n�ʂɓ������������ׂ�
		g_aThunder[nCntThunder].bHit = CollisionBlock(&g_aThunder[nCntThunder].pos, &g_aThunder[nCntThunder].posOld, &g_aThunder[nCntThunder].move, g_aThunder[nCntThunder].fThunderHeight, g_aThunder[nCntThunder].nCntStrikeTime);

		if (g_aThunder[nCntThunder].bHit == true)
		{//����������
			g_aThunder[nCntThunder].nDirection = THUNDERDIRECT_FALLING;
		}

		if (g_aThunder[nCntThunder].pos.y >= SCREEN_HEIGHT)
		{//��ʉ��܂ł�������
			g_aThunder[nCntThunder].nDirection = THUNDERDIRECT_FALLING;
		}

		break;

	case THUNDERDIRECT_FALLING:
		//����
		ThunderFalling(nCntThunder);
		break;

	case THUNDERDIRECT_END:
		//�I���
		EndEffect(EFFECTTYPE_THUNDER, nCntThunder);
		g_aThunder[nCntThunder].nDirection = THUNDERDIRECT_XSELECT;
		g_aThunder[nCntThunder].bFell = false;	//��������ԏI���
		g_aThunder[nCntThunder].bUse = false;
		break;

	default:
		break;
	}
}

//=================================
//���̗�����X���W�����߂�
//=================================
void SelectStrike(int nCntThunder)
{
	int nSelect = 20;

	//�����_���ŎZ�o
	nSelect = rand() % SCREEN_WIDTH;

	//�o����������
	g_aThunder[nCntThunder].pos.x = nSelect;
}

//=================================
//���̗�����Y���W�����߂�
//=================================
void ThunderFalling(int nCntThunder)
{
	//�^�C�}�[�����Z
	g_aThunder[nCntThunder].nCntStrikeTime++;

	if (g_aThunder[nCntThunder].nCntStrikeTime >= 60)
	{//��莞�Ԃ�������

		//���x��������
		g_aThunder[nCntThunder].col.a += 0.1f;

		if (g_aThunder[nCntThunder].col.a > 1.0f)
		{//���xMAX

			SetParticle(D3DXVECTOR3(g_aThunder[nCntThunder].pos.x, g_aThunder[nCntThunder].pos.y, 0.0f),	//�ʒu
				D3DXCOLOR(1.0f, 0.8f, 0.8f, 1.0f),			//�F
				EFFECTTYPE_NOMAL,	//���
				50,					//�o����
				10,				//�o���p�x
				60.0f,				//����
				0.1f,				//�ړ��ʌ�����
				5.0f,				//�|���S���T�C�Y
				0.001f,				//�|���S���T�C�Y������
				D3DX_PI * 0.55f,				//�_���̊p�x
				60.0f,				//����
				0.0f,				//�Œ�̈ړ���
				0.0f,				//��
				0.0f,				//����
				-1);

			SetParticle(D3DXVECTOR3(g_aThunder[nCntThunder].pos.x, g_aThunder[nCntThunder].pos.y, 0.0f),	//�ʒu
				D3DXCOLOR(1.0f, 0.8f, 0.8f, 1.0f),			//�F
				EFFECTTYPE_NOMAL,	//���
				50,					//�o����
				10,					//�o���p�x
				60.0f,				//����
				0.1f,				//�ړ��ʌ�����
				5.0f,				//�|���S���T�C�Y
				0.001f,				//�|���S���T�C�Y������
				-D3DX_PI * 0.55f,	//�_���̊p�x
				60.0f,				//����
				0.0f,				//�Œ�̈ړ���
				0.0f,				//��
				0.0f,				//����
				-1);

			g_aThunder[nCntThunder].bFell = true;					//���������
			g_aThunder[nCntThunder].nCntStrikeTime = 0;				//�^�C�}�[���[��
			g_aThunder[nCntThunder].nDirection = THUNDERDIRECT_END;	//���o���G���h��
			PlaySound(SOUND_LABEL_THUNDER_SE);
		}
	}
}

//=================================
//���̓����蔻��
//=================================
bool HitThunder(D3DXVECTOR3 pos,float fHeight)
{
	bool bHit = false;//�������ĂȂ�

	for (int nCntThunder = 0; nCntThunder < MAX_THUNDER; nCntThunder++)
	{//�T��
		if (g_aThunder[nCntThunder].bUse == true && g_aThunder[nCntThunder].bFell == true)
		{//�g���Ă�����
			
			if (g_aThunder[nCntThunder].pos.y > pos.y - fHeight &&
				g_aThunder[nCntThunder].pos.x - THUNDER_WIDTH < pos.x &&
				g_aThunder[nCntThunder].pos.x + THUNDER_WIDTH > pos.x)
			{//������ɂ����瓖����
				bHit = true;
			}
		}
	}

	//�l��Ԃ�
	return bHit;
}