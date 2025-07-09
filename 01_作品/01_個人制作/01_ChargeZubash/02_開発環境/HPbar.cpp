#include "HPbar.h"
#include "effect.h"
#include "enemy.h"
#include "player.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_aPTextureHPbar[HPBARTYPE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHPbar = NULL;				//���_�o�b�t�@�ւ̃|�C���^
HPBAR g_aHPbar[HPBARTYPE_MAX];								//�����o�[���

//======================================
//HPbar��̏�����
//======================================
void InitHPbar(void)
{
	int nCntHPbar;

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * HPBARTYPE_MAX, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHPbar,
		NULL);

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffHPbar->Lock(0, 0, (void**)&pVtx, 0);


	//�u���b�N�̏��̏�����
	for (nCntHPbar = 0; nCntHPbar < HPBARTYPE_MAX; nCntHPbar++)
	{
		g_aHPbar[nCntHPbar].pFile = NULL;
		g_aHPbar[nCntHPbar].pos = D3DXVECTOR3(0.0f,0.0f,0.0);
		g_aHPbar[nCntHPbar].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aHPbar[nCntHPbar].rect.bottom = 0;
		g_aHPbar[nCntHPbar].rect.left = 0;
		g_aHPbar[nCntHPbar].rect.right = 0;
		g_aHPbar[nCntHPbar].rect.top = 0;
		g_aHPbar[nCntHPbar].type = HPBARTYPE_MAX;
		g_aHPbar[nCntHPbar].fVari = 1.0f;

		//�ʒu�̏�����
		pVtx[0].pos.x = g_aHPbar[nCntHPbar].pos.x - g_aHPbar[nCntHPbar].rect.left;;
		pVtx[0].pos.y = g_aHPbar[nCntHPbar].pos.y - g_aHPbar[nCntHPbar].rect.top;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aHPbar[nCntHPbar].pos.x + g_aHPbar[nCntHPbar].rect.right;
		pVtx[1].pos.y = g_aHPbar[nCntHPbar].pos.y - g_aHPbar[nCntHPbar].rect.top;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aHPbar[nCntHPbar].pos.x - g_aHPbar[nCntHPbar].rect.left;
		pVtx[2].pos.y = g_aHPbar[nCntHPbar].pos.y + g_aHPbar[nCntHPbar].rect.bottom;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aHPbar[nCntHPbar].pos.x + g_aHPbar[nCntHPbar].rect.right;
		pVtx[3].pos.y = g_aHPbar[nCntHPbar].pos.y + g_aHPbar[nCntHPbar].rect.bottom;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aHPbar[nCntHPbar].col;
		pVtx[1].col = g_aHPbar[nCntHPbar].col;
		pVtx[2].col = g_aHPbar[nCntHPbar].col;
		pVtx[3].col = g_aHPbar[nCntHPbar].col;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�f�[�^�̃|�C���^���l���i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHPbar->Unlock();

	//�v���C���[
	SetHPbar(FILE_TEX_HPBAR_PLAYER_GAUGE,D3DXVECTOR3(0.0f, SCREEN_HEIGHT - HPBARFRAME_PRAYER_HEIGHT,0.0f), HPBARGAUGE_PRAYER_WIDTH, HPBARGAUGE_PRAYER_HEIGHT,HPBARTYPE_PLAYERGAUGE_BACK);
	SetHPbar(FILE_TEX_HPBAR_PLAYER_GAUGE,D3DXVECTOR3(0.0f, SCREEN_HEIGHT - HPBARFRAME_PRAYER_HEIGHT,0.0f), HPBARGAUGE_PRAYER_WIDTH, HPBARGAUGE_PRAYER_HEIGHT,HPBARTYPE_PLAYERGAUGE);
	SetHPbar(FILE_TEX_HPBAR_PLAYER_FRAME,D3DXVECTOR3(0.0f, SCREEN_HEIGHT - HPBARFRAME_PRAYER_HEIGHT,0.0f), HPBARFRAME_PRAYER_WIDTH, HPBARFRAME_PRAYER_HEIGHT,HPBARTYPE_PLAYERFRAME);
	//�G
	SetHPbar(FILE_TEX_HPBAR_PLAYER_GAUGE,D3DXVECTOR3(SCREEN_WIDTH*0.5f- HPBARFRAME_PRAYER_WIDTH*0.5f, SCREEN_HEIGHT - HPBARFRAME_ENEMY_HEIGHT,0.0f), HPBARGAUGE_ENEMY_WIDTH, HPBARGAUGE_ENEMY_HEIGHT,HPBARTYPE_ENEMYGAUGE_BACK);
	SetHPbar(FILE_TEX_HPBAR_PLAYER_GAUGE,D3DXVECTOR3(SCREEN_WIDTH*0.5f- HPBARFRAME_PRAYER_WIDTH*0.5f, SCREEN_HEIGHT - HPBARFRAME_ENEMY_HEIGHT,0.0f), HPBARGAUGE_ENEMY_WIDTH, HPBARGAUGE_ENEMY_HEIGHT,HPBARTYPE_ENEMYGAUGE);
	SetHPbar(FILE_TEX_HPBAR_ENEMY_FRAME,D3DXVECTOR3(SCREEN_WIDTH*0.5f- HPBARFRAME_PRAYER_WIDTH * 0.5f, SCREEN_HEIGHT - HPBARFRAME_ENEMY_HEIGHT,0.0f), HPBARFRAME_ENEMY_WIDTH, HPBARFRAME_ENEMY_HEIGHT,HPBARTYPE_ENEMYFRAME);
}

//======================================
//HPbar��HPbar��̏I��
//======================================
void UninitHPbar(void)
{
	for (int nCntHPbar = 0; nCntHPbar < HPBARTYPE_MAX; nCntHPbar++)
	{
		//�e�N�X�`���̔j��
		if (g_aPTextureHPbar[nCntHPbar] != NULL)
		{

			g_aPTextureHPbar[nCntHPbar]->Release();
			g_aPTextureHPbar[nCntHPbar] = NULL;
		}
		EndHPbar(nCntHPbar);
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffHPbar != NULL)
	{
		g_pVtxBuffHPbar->Release();
		g_pVtxBuffHPbar = NULL;
	}
}

//======================================
//HPbar��̃A�b�v�f�[�g
//======================================
void UpdateHPbar(void)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffHPbar->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHPbar = 0; nCntHPbar < HPBARTYPE_MAX; nCntHPbar++)
	{
		if (g_aHPbar[nCntHPbar].bUse == true)
		{
			VariHPbar(nCntHPbar);

			switch (g_aHPbar[nCntHPbar].type)
			{

			case HPBARTYPE_PLAYERGAUGE:
			g_aHPbar[nCntHPbar].rect.right = (HPBARFRAME_PRAYER_WIDTH) * g_aHPbar[nCntHPbar].fVari;
				break;

			case HPBARTYPE_ENEMYGAUGE:
				g_aHPbar[nCntHPbar].rect.right = (HPBARFRAME_ENEMY_WIDTH) * g_aHPbar[nCntHPbar].fVari;
				break;

			default:
				break;
			}

			//���_���W�X�V
			pVtx[0].pos.x = g_aHPbar[nCntHPbar].pos.x;
			pVtx[0].pos.y = g_aHPbar[nCntHPbar].pos.y - g_aHPbar[nCntHPbar].rect.top;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aHPbar[nCntHPbar].pos.x + g_aHPbar[nCntHPbar].rect.right;
			pVtx[1].pos.y = g_aHPbar[nCntHPbar].pos.y - g_aHPbar[nCntHPbar].rect.top;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aHPbar[nCntHPbar].pos.x;
			pVtx[2].pos.y = g_aHPbar[nCntHPbar].pos.y + g_aHPbar[nCntHPbar].rect.bottom;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aHPbar[nCntHPbar].pos.x + g_aHPbar[nCntHPbar].rect.right;
			pVtx[3].pos.y = g_aHPbar[nCntHPbar].pos.y + g_aHPbar[nCntHPbar].rect.bottom;
			pVtx[3].pos.z = 0.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aHPbar[nCntHPbar].col;
			pVtx[1].col = g_aHPbar[nCntHPbar].col;
			pVtx[2].col = g_aHPbar[nCntHPbar].col;
			pVtx[3].col = g_aHPbar[nCntHPbar].col;

		}

		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
	}

	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHPbar->Unlock();
}

//======================================
//HPbar��̕`��
//======================================
void DrawHPbar(void)
{
	int nCntHPbar;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHPbar, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//HPbar��̕`��
	for (nCntHPbar = 0; nCntHPbar < HPBARTYPE_MAX; nCntHPbar++)
	{
		if (g_aHPbar[nCntHPbar].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aPTextureHPbar[nCntHPbar]);

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntHPbar,							//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);
		}
	}
}

//======================================
//HPbar��ݒ�
//======================================
void SetHPbar(const char* pFile, D3DXVECTOR3 pos, long lWidth, long lHeight, HPBARTYPE type)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffHPbar->Lock(0, 0, (void**)&pVtx, 0);

	//������������
	for (int nCntHPbar = 0; nCntHPbar < HPBARTYPE_MAX; nCntHPbar++)
	{
		if (g_aHPbar[nCntHPbar].bUse == false)
		{
			g_aHPbar[nCntHPbar].pFile = pFile;
			g_aHPbar[nCntHPbar].pos = pos;
			g_aHPbar[nCntHPbar].rect.bottom = lHeight;
			g_aHPbar[nCntHPbar].rect.left = lWidth;
			g_aHPbar[nCntHPbar].rect.right = lWidth;
			g_aHPbar[nCntHPbar].rect.top = lHeight;
			g_aHPbar[nCntHPbar].type = type;
			g_aHPbar[nCntHPbar].fVari = 1.0f;
			g_aHPbar[nCntHPbar].bUse = true;

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pFile,
				&g_aPTextureHPbar[nCntHPbar]);

			//�ʒu
			pVtx[0].pos.x = g_aHPbar[nCntHPbar].pos.x;
			pVtx[0].pos.y = g_aHPbar[nCntHPbar].pos.y - g_aHPbar[nCntHPbar].rect.top;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aHPbar[nCntHPbar].pos.x + g_aHPbar[nCntHPbar].rect.right;
			pVtx[1].pos.y = g_aHPbar[nCntHPbar].pos.y - g_aHPbar[nCntHPbar].rect.top;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aHPbar[nCntHPbar].pos.x;
			pVtx[2].pos.y = g_aHPbar[nCntHPbar].pos.y;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aHPbar[nCntHPbar].pos.x + g_aHPbar[nCntHPbar].rect.right;
			pVtx[3].pos.y = g_aHPbar[nCntHPbar].pos.y;
			pVtx[3].pos.z = 0.0f;

			break;
		}
		pVtx += 4;// ���_�f�[�^�̃|�C���^���l���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHPbar->Unlock();
}

//======================================
//HPbar��ω�
//======================================
void VariHPbar(int nCntHPbar)
{
	Player* pPlayer = GetPlayer();		//�v���C���[�擾
	ENEMY* pEnemy = GetEnemy();			//�G�l�~�[�擾
	SNAKEHP* pSnakeHP = GetSnakeHP();	//�ւ̑�HP
	switch (g_aHPbar[nCntHPbar].type)
	{
	case HPBARTYPE_PLAYERGAUGE_BACK:
		g_aHPbar[nCntHPbar].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);//���F
		break;

	case HPBARTYPE_PLAYERGAUGE:
		
		g_aHPbar[nCntHPbar].fVari = pPlayer->fLife / MAX_PLAYER_HP;

		if ((pPlayer->fLife / MAX_PLAYER_HP) * 100.0f >= 50.0f)
		{//�����ȏ㍇������
			g_aHPbar[nCntHPbar].col = D3DXCOLOR(0.0f,1.0f,1.0f,1.0f);//�F
		}
		else if ((pPlayer->fLife / MAX_PLAYER_HP) * 100.0f < 50.0f &&
			(pPlayer->fLife / MAX_PLAYER_HP) * 100.0f >= 30.0f)
		{//50%���������
			g_aHPbar[nCntHPbar].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);//���F
		}
		else if ((pPlayer->fLife / MAX_PLAYER_HP) * 100.0f < 30.0f &&
			(pPlayer->fLife / MAX_PLAYER_HP) * 100.0f >= 0.0f)
		{//30%���������
			g_aHPbar[nCntHPbar].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//�ԐF
		}

		break;

	case HPBARTYPE_PLAYERFRAME:
		g_aHPbar[nCntHPbar].col = D3DXCOLOR(0.4f, 0.6f, 0.6f, 1.0f);//���F
		break;

	case HPBARTYPE_ENEMYGAUGE_BACK:
		g_aHPbar[nCntHPbar].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);//���F
		break;

	case HPBARTYPE_ENEMYGAUGE:
		g_aHPbar[nCntHPbar].fVari = pSnakeHP->fLife / pSnakeHP->fMaxLife;
		g_aHPbar[nCntHPbar].col = D3DXCOLOR(0.9f, 1.0f, 0.0f, 1.0f);//���ΐF
		break;

		case HPBARTYPE_ENEMYFRAME:
			g_aHPbar[nCntHPbar].col = D3DXCOLOR(0.9f, 1.0f, 0.0f, 1.0f);//���ΐF
			break;
	default:
		break;
	}
}

//======================================
//HPbar�̏I��
//======================================
void EndHPbar(int nCntHPbar)
{
	g_aHPbar[nCntHPbar].bUse = false;
}

//======================================
//�G��HPbar�̍X�V
//======================================

