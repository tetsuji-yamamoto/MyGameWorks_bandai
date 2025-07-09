#include "enemy.h"
#include "main.h"
#include "particle.h"
#include "player.h"
#include "effect.h"
#include "sound.h"
#include "sword.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "result.h"
#include "hit.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureEnemy[ENEMYTYPE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				//���_�o�b�t�@�ւ̃|�C���^
ENEMY g_aEnemy[MAX_ENEMY];									//�G�̏��
SNAKEHP g_snakeHP;											//�ւ̂���
int g_nNumEnemy = 0;										//�G�̑���

//-------------------
//�G�̏���������
//-------------------
void InitEnemy(void)
{
	int nCntEnemy;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	g_nNumEnemy = 0; 

	g_snakeHP.fLife = 0;
	g_snakeHP.fMaxLife = 0;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pFileName = NULL;							//�t�@�C����
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
		g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
		g_aEnemy[nCntEnemy].rect.bottom = 0;			//�l���_���
		g_aEnemy[nCntEnemy].rect.left = 0;			//�l���_���
		g_aEnemy[nCntEnemy].rect.right = 0;			//�l���_���
		g_aEnemy[nCntEnemy].rect.top = 0;			//�l���_���
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;	//���
		g_aEnemy[nCntEnemy].nType = ENEMYTYPE_MAX;		//���
		g_aEnemy[nCntEnemy].nCntState = 0;				//��ԊǗ��J�E���^�[
		g_aEnemy[nCntEnemy].fLife = 0;					//�̗�
		g_aEnemy[nCntEnemy].fWidth = 0.0f;				//��
		g_aEnemy[nCntEnemy].fHeight = 0.0f;				//����
		g_aEnemy[nCntEnemy].bUse = false;				//�g���Ă��邩�ǂ���
		
		g_aEnemy[nCntEnemy].vertex.BottomLeft = D3DXVECTOR2(0.0f, 0.0f);
		g_aEnemy[nCntEnemy].vertex.BottomRight = D3DXVECTOR2(0.0f, 0.0f);
		g_aEnemy[nCntEnemy].vertex.TopLeft = D3DXVECTOR2(0.0f, 0.0f);
		g_aEnemy[nCntEnemy].vertex.TopRight = D3DXVECTOR2(0.0f, 0.0f);
		g_aEnemy[nCntEnemy].vertex.fAngle = 0.0f;
		g_aEnemy[nCntEnemy].vertex.fLength = 0.0f;
		g_aEnemy[nCntEnemy].vertex.fLot = 0.0f;

		g_aEnemy[nCntEnemy].snake.posFrontUnion = D3DXVECTOR2(0.0f, 0.0f);
		g_aEnemy[nCntEnemy].snake.posAnderUnion = D3DXVECTOR2(0.0f, 0.0f);
		g_aEnemy[nCntEnemy].snake.nCntBody = -2;
		g_aEnemy[nCntEnemy].snake.snakeState = SNAKESTATE_STANDE;
		g_aEnemy[nCntEnemy].snake.nChillTime = 0;
		g_aEnemy[nCntEnemy].snake.bAttack = false;

		g_aEnemy[nCntEnemy].snakeMove.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].snakeMove.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].snakeMove.nCntMoveTime = 0;
		g_aEnemy[nCntEnemy].snakeMove.nCntMotion = 0;
		g_aEnemy[nCntEnemy].snakeMove.nLoopCnt = 0;
		g_aEnemy[nCntEnemy].snakeMove.fLength = 0.0f;
		g_aEnemy[nCntEnemy].snakeMove.fAngle = 0.0f;
		g_aEnemy[nCntEnemy].snakeMove.fLot = 0.0f;

		//���_���W�̐ݒ�												
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aEnemy[nCntEnemy].col;
		pVtx[1].col = g_aEnemy[nCntEnemy].col;
		pVtx[2].col = g_aEnemy[nCntEnemy].col;
		pVtx[3].col = g_aEnemy[nCntEnemy].col;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}
//-------------------
//�G�̏I������
//-------------------
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < ENEMYTYPE_MAX; nCntEnemy++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}

		g_aEnemy[nCntEnemy].bUse = false;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
//-------------------
//�G�̍X�V����
//--------------------
void UpdateEnemy(void)
{
	Player* pPlayer = GetPlayer();	//�v���C���[�擾

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���[���ɂ���
	g_snakeHP.fLife = 0.0f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	
#ifdef _DEBUG	//�f�o�b�O�������g�p�\

	if (KeyboardTrigger(DIK_6) == true)
	{
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
		{
			g_aEnemy[nCntEnemy].fLife -= g_aEnemy[nCntEnemy].fLife;
		}
	}

#endif
	//�X�V����
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//�G�̈Ⴂ�ɂ��X�V
			switch (g_aEnemy[nCntEnemy].nType)
			{

			case ENEMYTYPE_PUNCHINGBAG://�T���h�o�b�O
				//���_���W�̐ݒ�
				pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].rect.left;
				pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].rect.top;
				pVtx[0].pos.z = 0.0f;
				pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].rect.right;
				pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].rect.top;
				pVtx[1].pos.z = 0.0f;
				pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].rect.left;
				pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].rect.bottom;
				pVtx[2].pos.z = 0.0f;
				pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].rect.right;
				pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].rect.bottom;
				pVtx[3].pos.z = 0.0f;
				break;

			case ENEMYTYPE_SNAKE://��
				UpDateSnake(nCntEnemy);
 				break;
			}

			//��Ԃɂ�鏈��
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				//�ʏ���
				if (g_aEnemy[nCntEnemy].fLife <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_DEATH;	//�f�X
					g_aEnemy[nCntEnemy].bUse = false;
					g_nNumEnemy--;
				}
				break;
					
			case ENEMYSTATE_DAMAGE:
				//�_���[�W���
				
				//�J�E���^�[�����炷
				g_aEnemy[nCntEnemy].nCntState--;

				if (g_aEnemy[nCntEnemy].nCntState <= 0)
				{//�J�E���^�[���[���ɂȂ�����
					g_aEnemy[nCntEnemy].nCntState = 0;								//�J�E���^�[���[��
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;					//�ʏ��Ԃ�
					g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�ʏ�̐F��
				}
				else
				{
					g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);	//�ԐF�ɂ���
				}

				break;

			case ENEMYSTATE_DEATH:
				//���S���
				
				break;
			}

			if (pPlayer->state == PLAYERSTATE_NOMAL)
			{
				//�v���C���[�ƓG�̓����蔻��
				if (HitBox(g_aEnemy[nCntEnemy].rect, pPlayer->rect, g_aEnemy[nCntEnemy].pos, pPlayer->pos, ANCHORPOINT_CENTER, ANCHORPOINT_BOTTOMCENTER) == true)
				{
					float fDistance = pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x;
					if (fDistance < 0)
					{//�}�C�i�X��������
						pPlayer->move.x -= 100.0f;
					}
					else if (fDistance > 0)
					{//�v���X��������
						pPlayer->move.x += 100.0f;
					}
					HitPlayer(1.0f);
				}
			}

			g_snakeHP.fLife += g_aEnemy[nCntEnemy].fLife;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aEnemy[nCntEnemy].col;
			pVtx[1].col = g_aEnemy[nCntEnemy].col;
			pVtx[2].col = g_aEnemy[nCntEnemy].col;
			pVtx[3].col = g_aEnemy[nCntEnemy].col;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

	if (g_nNumEnemy <= 0 && GetGameState() == GAMESTATE_NORMAL)
	{
		SetGameState(GAMESTATE_END);		//�Q�[���I���
		SetResult(RESULTTYPE_GAMECREAR);	//�Q�[���N���A
	}
}
//-------------------
//�G�̕`�揈��
//--------------------
void DrawEnemy(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			//�G�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntEnemy,							//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);										//�`�悷��v���~�e�B�u�i�G�j��
		}
	}
}

//===============================
//�G�̐ݒ菈��
//===============================
void SetEnemy(const char* pFileName, D3DXVECTOR3 pos, int nType,float fLife,float fWidth,float fHeight)
{
	int nCntEnemy;

	VERTEX_2D* pVtx;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//�g���ĂȂ�������

			g_nNumEnemy++;//�����v���X
			g_aEnemy[nCntEnemy].pFileName = pFileName;
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].fLife = fLife;
			g_aEnemy[nCntEnemy].fWidth = fWidth;
			g_aEnemy[nCntEnemy].fHeight = fHeight;
			g_aEnemy[nCntEnemy].rect.bottom = fHeight;
			g_aEnemy[nCntEnemy].rect.left = fWidth;
			g_aEnemy[nCntEnemy].rect.right = fWidth;
			g_aEnemy[nCntEnemy].rect.top = fHeight;
			g_aEnemy[nCntEnemy].bUse = true;

			g_snakeHP.fMaxLife += g_aEnemy[nCntEnemy].fLife;

			//�e�N�X�`��4�����̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				g_aEnemy[nCntEnemy].pFileName,
				&g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].rect.left;
			pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].rect.top;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].rect.right;
			pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].rect.top;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].rect.left;
			pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].rect.bottom;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].rect.right;
			pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].rect.bottom;
			pVtx[3].pos.z = 0.0f;

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

			break;
		}

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//===============================
//�G�̔�e����
//===============================
void HitEnemy(int nCntEnemy, float fDamage)
{
	if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_NORMAL)
	{
		g_aEnemy[nCntEnemy].fLife -= fDamage;

		if (g_aEnemy[nCntEnemy].fLife > 0)
		{//�����Ă�����
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;	//�_���[�W��Ԃ�
			g_aEnemy[nCntEnemy].nCntState = 30;				//��ԊǗ��J�E���^�[��ݒ�

		}
		else if (g_aEnemy[nCntEnemy].fLife <= 0)
		{//����ł�����
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DEATH;	//�f�X
			g_aEnemy[nCntEnemy].bUse = false;
			g_nNumEnemy--;

			if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_PUNCHINGBAG)
			{
				//�G�ݒu
				g_snakeHP.fMaxLife = 0.0f;	//MAX�̗̓��Z�b�g
				SetEnemy(FILE_TEX_PB, D3DXVECTOR3(1100.0f, 490.0f, 0.0f), ENEMYTYPE_PUNCHINGBAG, 5, PB_WIDTH, PB_HEIGHT);//����������
			}
		}
		PlaySound(SOUND_LABEL_PLAYERATTACK_SE);	//�q�b�g��
	}
}

//===============================
//�G�̐ݒ菈��
//===============================
ENEMY* GetEnemy(void)
{
	return &g_aEnemy[0];
}

SNAKEHP* GetSnakeHP(void)
{
	return &g_snakeHP;
}
//===============================
//�G�̑����̎擾
//===============================
int GetNumEnemy()
{
	return g_nNumEnemy;
}

//===============================
//�ւ̍X�V
//===============================
void UpDateSnake(int nCntEnemy)
{
	int nCnt = 0;
	int nCntBody = 0;//�ւ̑̂̏���
	int nState = 0;//���

	g_aEnemy[nCntEnemy].rect.bottom = SNAKE_WIDTH;
	g_aEnemy[nCntEnemy].rect.left = SNAKE_WIDTH;
	g_aEnemy[nCntEnemy].rect.right = SNAKE_WIDTH;
	g_aEnemy[nCntEnemy].rect.top = SNAKE_WIDTH;

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntEnemy;

	//���Ԃ𐮂���
	for (nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_aEnemy[nCnt].bUse == true && g_aEnemy[nCnt].nType == ENEMYTYPE_SNAKE)
		{//������
			g_aEnemy[nCnt].snake.nCntBody = nCntBody;//���Ԃ����Ă�����
			nCntBody++;
		}

		if (nCntBody >= MAX_SNAKE_BODY)
		{//�̂̐��𒴂�����
			break;
		}
	}

	nCntBody = 0;//�����l�ɖ߂�

	//����������
	if (g_aEnemy[nCntEnemy].snake.nCntBody == 0)
	{
		//�U����Ԃ���Ȃ�
		if (g_aEnemy[nCntEnemy].snake.bAttack == false)
		{
			if (g_aEnemy[nCntEnemy].snake.nChillTime <= 0)
			{//��莞�Ԃ�������
				//�����_���Ō��߂�
				nState = rand() % 100;
				//�����_���ŏo���l�ŏ�Ԃ�ς���
				if (nState >= 0 && nState < 60)
				{
					g_aEnemy[nCntEnemy].snake.snakeState = SNAKESTATE_HEADBUTT;
				}
				else if (nState >= 60 && nState < 100)
				{
					g_aEnemy[nCntEnemy].snake.snakeState = SNAKESTATE_TOUR;

				}

				//�A�^�b�N��Ԃɂ���
				g_aEnemy[nCntEnemy].snake.bAttack = true;	//�U�����
				g_aEnemy[nCntEnemy].snake.nChillTime = rand()% 1000;	//�^�C�}�[�[��
			}
			else
			{
				g_aEnemy[nCntEnemy].snake.nChillTime--;	//�J�E���^�[�����Z
				SnakeStand(nCntEnemy);
			}
		}

		//�U�����
		if(g_aEnemy[nCntEnemy].snake.bAttack == true)
		{
			switch (g_aEnemy[nCntEnemy].snake.snakeState)
			{
				break;
			case SNAKESTATE_HEADBUTT:
				SnakeHeadbutt(nCntEnemy);
				break;

			case SNAKESTATE_TOUR:
				SnakeTour(nCntEnemy);
				break;
			}
		}
	}
	
	//���Ԃɂ������Ă���
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_aEnemy[nCnt].bUse == true && g_aEnemy[nCnt].nType == ENEMYTYPE_SNAKE)
		{
			if ((g_aEnemy[nCntBody].snake.nCntBody - g_aEnemy[nCnt].snake.nCntBody) == (-1))
			{//�O�̂�Ƃ̍����}�C�i�X1��������

				g_aEnemy[nCnt].vertex.fLot += (g_aEnemy[nCntBody].vertex.fLot - g_aEnemy[nCnt].vertex.fLot) * 0.01f;
				g_aEnemy[nCnt].pos.x = g_aEnemy[nCntBody].pos.x + sinf(D3DX_PI + g_aEnemy[nCntBody].vertex.fLot) * SNAKE_HEIGHT;
				g_aEnemy[nCnt].pos.y = g_aEnemy[nCntBody].pos.y + cosf(D3DX_PI + g_aEnemy[nCntBody].vertex.fLot) * SNAKE_HEIGHT;
			}
			nCntBody = nCnt;

			if (g_aEnemy[nCnt].vertex.fLot > D3DX_PI)
			{// �p�x�̐��K��
				float Diff;
				Diff = (g_aEnemy[nCnt].vertex.fLot - D3DX_PI);
				g_aEnemy[nCnt].vertex.fLot = -D3DX_PI + Diff;
			}
			else if (g_aEnemy[nCnt].vertex.fLot < -D3DX_PI)
			{// �p�x�̐��K��
				float Diff;
				Diff = (g_aEnemy[nCnt].vertex.fLot + D3DX_PI);
				g_aEnemy[nCnt].vertex.fLot = D3DX_PI - Diff;
			}
		}

		if (nCntBody >= MAX_SNAKE_BODY)
		{//�̂̐����𒴂�����
			nCntBody = 0;	//�����l�ɖ߂�
			break;
		}
		g_aEnemy[nCntEnemy].vertex.fLength = sqrtf((SNAKE_WIDTH * SNAKE_WIDTH) + (SNAKE_HEIGHT * SNAKE_HEIGHT));
		g_aEnemy[nCntEnemy].vertex.fAngle = atan2f(SNAKE_HEIGHT, SNAKE_WIDTH);

		g_aEnemy[nCntEnemy].vertex.TopLeft.x = sinf(-D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle - g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;
		g_aEnemy[nCntEnemy].vertex.TopLeft.y = cosf(D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle - g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;
		g_aEnemy[nCntEnemy].vertex.TopRight.x = sinf(D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle + g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;
		g_aEnemy[nCntEnemy].vertex.TopRight.y = cosf(D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle + g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;
		g_aEnemy[nCntEnemy].vertex.BottomLeft.x = sinf(-D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle + g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;
		g_aEnemy[nCntEnemy].vertex.BottomLeft.y = cosf(-D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle + g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;
		g_aEnemy[nCntEnemy].vertex.BottomRight.x = sinf(D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle - g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;
		g_aEnemy[nCntEnemy].vertex.BottomRight.y = cosf(-D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle - g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;

	}

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].vertex.TopLeft.x;
	pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].vertex.TopLeft.y;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].vertex.TopRight.x;
	pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].vertex.TopRight.y;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].vertex.BottomLeft.x;
	pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].vertex.BottomLeft.y;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].vertex.BottomRight.x;
	pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].vertex.BottomRight.y;
	pVtx[3].pos.z = 0.0f;

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


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

	SetEffect(pVtx[0].pos,	//�ʒu
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//�ړ���
		D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f),		//�F
		EFFECTTYPE_NOMAL,						//�ʏ�G�t�F�N�g
		10.0f,									//�|���S���T�C�Y
		0.0f,									//����
		0.0f,									//��
		0.0f,									//�|���S���T�C�Y������
		0.0f,									//�ړ��ʌ�����
		5.0f,									//����
		0.0f,									//�p�x
		-1										//�������
		);

	SetEffect(pVtx[1].pos,	//�ʒu
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//�ړ���
		D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f),		//�F
		EFFECTTYPE_NOMAL,						//�ʏ�G�t�F�N�g
		6.0f,									//�|���S���T�C�Y
		0.0f,									//����
		0.0f,									//��
		0.0f,									//�|���S���T�C�Y������
		0.0f,									//�ړ��ʌ�����
		4.0f,									//����
		0.0f,									//�p�x
		-1										//�������
	);

	SetEffect(pVtx[2].pos,	//�ʒu
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//�ړ���
		D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f),		//�F
		EFFECTTYPE_NOMAL,						//�ʏ�G�t�F�N�g
		6.0f,									//�|���S���T�C�Y
		0.0f,									//����
		0.0f,									//��
		0.0f,									//�|���S���T�C�Y������
		0.0f,									//�ړ��ʌ�����
		4.0f,									//����
		0.0f,									//�p�x
		-1										//�������
	);

	SetEffect(pVtx[3].pos,	//�ʒu
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//�ړ���
		D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f),		//�F
		EFFECTTYPE_NOMAL,						//�ʏ�G�t�F�N�g
		6.0f,									//�|���S���T�C�Y
		0.0f,									//����
		0.0f,									//��
		0.0f,									//�|���S���T�C�Y������
		0.0f,									//�ړ��ʌ�����
		4.0f,									//����
		0.0f,									//�p�x
		-1										//�������
	);

	SetEffect(D3DXVECTOR3(g_aEnemy[nCntEnemy].snake.posFrontUnion.x, g_aEnemy[nCntEnemy].snake.posFrontUnion.y, 0.0f),	//�ʒu
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//�ړ���
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),		//�F
		EFFECTTYPE_NOMAL,						//�ʏ�G�t�F�N�g
		6.0f,									//�|���S���T�C�Y
		0.0f,									//����
		0.0f,									//��
		0.0f,									//�|���S���T�C�Y������
		0.0f,									//�ړ��ʌ�����
		4.0f,									//����
		0.0f,									//�p�x
		-1										//�������
	);

	SetEffect(D3DXVECTOR3(g_aEnemy[nCntEnemy].snake.posAnderUnion.x, g_aEnemy[nCntEnemy].snake.posAnderUnion.y, 0.0f),	//�ʒu
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//�ړ���
		D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),		//�F
		EFFECTTYPE_NOMAL,						//�ʏ�G�t�F�N�g
		6.0f,									//�|���S���T�C�Y
		0.0f,									//����
		0.0f,									//��
		0.0f,									//�|���S���T�C�Y������
		0.0f,									//�ړ��ʌ�����
		4.0f,									//����
		0.0f,									//�p�x
		-1										//�������
	);
}

//===============================
//�ւ̓��˂�
//===============================
void SnakeHeadbutt(int nSnakeHead)
{
	int nCntEnemy = 0;
	float fLoty = 0.0f;
	float distance, distance1 = 0.0f;

	D3DXVECTOR3 fMovey = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Player* pPlayer = GetPlayer();	//�v���C���[�擾

	switch (g_aEnemy[nSnakeHead].snakeMove.nCntMotion)
	{
	case 0://�ړI�n�ւ̊p�x�����߂�
	//���̏ꏊ����ړI�̒l�܂ł̊Ԃ𒲂ׂ�
		distance = (SCREEN_WIDTH * 0.5f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT - g_aEnemy[nSnakeHead].pos.y);
		//�ړI�̊p�x�����߂�
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);
		//�ړI�̊p�x���獡�̊p�x�̊Ԃ𒲂ׂ�
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 30.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;
		break;

	case 1://�_���������֓���������
		g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime++;

		if (g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime >= 30)
		{//��莞�Ԃ�������
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;		//���̃��[�V�����փJ�E���g
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//�^�C�}�[�[��
		}
		else
		{//�p�x�𑫂�������
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		break;

	case 2://�_���������ɐi��ł���
		//���̏ꏊ����ړI�̒l�܂ł̊Ԃ𒲂ׂ�
		distance = (SCREEN_WIDTH * 0.5f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT - g_aEnemy[nSnakeHead].pos.y);
		//�ړI�n�܂ł̊p�x�Ƌ��������߂�
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);

		if (g_aEnemy[nSnakeHead].snakeMove.fLength >= 10)
		{//�߂��Ȃ�������
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
		}
		else
		{//�߂��Ȃ�����
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;//���̃��[�V�����փJ�E���g

		}
		break;

	case 3://�v���C���[�ɑ_�����
		//���̏ꏊ����v���C���[�܂ł̊Ԃ𒲂ׂ�
		distance = (pPlayer->pos.x - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (pPlayer->pos.y - g_aEnemy[nSnakeHead].pos.y);

		//�ړI�̊p�x�����߂�
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);

		//�ړI�̊p�x���獡�̊p�x�̊Ԃ𒲂ׂ�
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 60.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;	//���̃��[�V�����փJ�E���g
		break;

	case 4:
		g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime++;	//���̃��[�V�����փJ�E���g

		if (g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime >= 60)
		{//��莞�Ԃ�������
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;		//���̃��[�V�����փJ�E���g
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//�^�C�}�[�[��
			PlaySound(SOUND_LABEL_SNAKE_VOIS_SE);				//�ւ̐�

		}
		else
		{//�p�x�𑫂�������
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		break;

	case 5://�ːi
		//�v���C���[�Ƃ̋����𑪂�
		distance = (pPlayer->pos.x - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (pPlayer->pos.y - g_aEnemy[nSnakeHead].pos.y);
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;

		if (g_aEnemy[nSnakeHead].snakeMove.fLength <= SCREEN_HEIGHT)
		{//�v���C���[�Ƃ̋������Z��������
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
		}
		else
		{//�����Ȃ�����
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 0;	//���[�V�������Z�b�g
			g_aEnemy[nSnakeHead].snake.snakeState = SNAKESTATE_STANDE;//��Ԃ�ҋ@��Ԃ�
			g_aEnemy[nSnakeHead].snake.bAttack = false;//�ҋ@���
		}
		
		break;
	}
	
}

//===============================
//�ւ̃c�A�[
//===============================
void SnakeTour(int nSnakeHead)
{
	int nCntEnemy = 0;
	float fLoty = 0.0f;
	float distance, distance1 = 0.0f;

	D3DXVECTOR3 fMovey = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Player* pPlayer = GetPlayer();	//�v���C���[�擾

	switch (g_aEnemy[nSnakeHead].snakeMove.nCntMotion)
	{
	case 0://�ړI�n�ւ̊p�x�����߂�
		//���̏ꏊ����ړI�̒l�܂ł̊Ԃ𒲂ׂ�
		distance = (SCREEN_WIDTH * 0.5f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT * 0.5f - g_aEnemy[nSnakeHead].pos.y);
		//�ړI�̊p�x�����߂�
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);
		//�ړI�̊p�x���獡�̊p�x�̊Ԃ𒲂ׂ�
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 30.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;
		break;

	case 1://�_���������֓���������
		g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime++;

		if (g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime >= 30)
		{//��莞�Ԃ�������
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;		//���̃��[�V�����փJ�E���g
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//�^�C�}�[�[��

		}
		else
		{//�p�x�𑫂�������
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		break;

	case 2://�_���������ɓ�������
	//���̏ꏊ����ړI�̒l�܂ł̊Ԃ𒲂ׂ�
		distance = (SCREEN_WIDTH * 0.5f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT * 0.5f - g_aEnemy[nSnakeHead].pos.y);

		//�ړI�̊p�x�����߂�
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);

		//�ړI�̊p�x���獡�̊p�x�̊Ԃ𒲂ׂ�
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 30.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;
		break;

	case 3://���S�փS�[
	//���̏ꏊ����ړI�̒l�܂ł̊Ԃ𒲂ׂ�
		distance = (SCREEN_WIDTH * 0.5f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT * 0.5f - g_aEnemy[nSnakeHead].pos.y);
		//�ړI�n�܂ł̊p�x�Ƌ��������߂�
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);

		if (g_aEnemy[nSnakeHead].snakeMove.fLength >= 30)
		{//�߂��Ȃ�������
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		else
		{//�߂��Ȃ�����
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;//���̃��[�V�����փJ�E���g
			PlaySound(SOUND_LABEL_SNAKE_VOIS_SE);				//�ւ̐�
		}
		break;

	case 4://�ړI�n�ւ̊p�x�����߂�
		//���̏ꏊ����ړI�̒l�܂ł̊Ԃ𒲂ׂ�
		distance = (SCREEN_WIDTH * 0.5f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (-SCREEN_HEIGHT - g_aEnemy[nSnakeHead].pos.y);
		//�ړI�̊p�x�����߂�
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);
		//�ړI�̊p�x���獡�̊p�x�̊Ԃ𒲂ׂ�
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 30.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;
		break;

	case 5://��������
		g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime++;

		if (g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime >= 30)
		{//��莞�Ԃ�������
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;		//���̃��[�V�����փJ�E���g
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//�^�C�}�[�[��
			PlaySound(SOUND_LABEL_SNAKE_VOIS_SE);				//�ւ̐�

		}
		else
		{//�p�x�𑫂�������
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		break;

	case 6://
		//���̏ꏊ����ړI�̒l�܂ł̊Ԃ𒲂ׂ�
		distance = (SCREEN_WIDTH * 0.5f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (-SCREEN_HEIGHT * 2.0f- g_aEnemy[nSnakeHead].pos.y);
		//�ړI�n�܂ł̊p�x�Ƌ��������߂�
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);

		if (g_aEnemy[nSnakeHead].snakeMove.fLength >= 30)
		{//�߂��Ȃ�������
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
		}
		else
		{//�߂��Ȃ�����
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;//���̃��[�V�����փJ�E���g
		}
		break;

	case 7://�ړI�n�ւ̊p�x�����߂�
		g_aEnemy[nSnakeHead].pos = D3DXVECTOR3(SCREEN_WIDTH * 2.0f,SCREEN_HEIGHT * 0.4f,0.0f);
	//���̏ꏊ����ړI�̒l�܂ł̊Ԃ𒲂ׂ�
		distance = (-SCREEN_WIDTH * 2.0f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT * 0.4f - g_aEnemy[nSnakeHead].pos.y);
		//�ړI�̊p�x�����߂�
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);
		//�ړI�̊p�x���獡�̊p�x�̊Ԃ𒲂ׂ�
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 30.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;
		break;

	case 8://��������

		if (g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime >= 30)
		{//��莞�Ԃ�������
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;		//���̃��[�V�����փJ�E���g
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//�^�C�}�[�[��
			PlaySound(SOUND_LABEL_SNAKE_VOIS_SE);				//�ւ̐�

		}
		else
		{//�p�x�𑫂�������
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime++;//�^�C�}�[�J�E���g
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		break;

	case 9://�����փS�[
	//���̏ꏊ����ړI�̒l�܂ł̊Ԃ𒲂ׂ�
		distance = (-SCREEN_WIDTH * 2.0f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT * 0.4f - g_aEnemy[nSnakeHead].pos.y);
		//�ړI�n�܂ł̊p�x�Ƌ��������߂�
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);

		if (g_aEnemy[nSnakeHead].snakeMove.fLength >= 30)
		{//�߂��Ȃ�������
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 2.0f;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 2.0f;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
		}
		else
		{//�߂��Ȃ�����
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;//���̃��[�V�����փJ�E���g
		}
		break;

	case 10://�ړI�n�ւ̊p�x�����߂�
		g_aEnemy[nSnakeHead].pos = D3DXVECTOR3(-SCREEN_WIDTH * 2.0f, SCREEN_HEIGHT * 0.7f, 0.0f);
		//���̏ꏊ����ړI�̒l�܂ł̊Ԃ𒲂ׂ�
		distance = (SCREEN_WIDTH * 2.0f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT * 0.8f - g_aEnemy[nSnakeHead].pos.y);
		//�ړI�̊p�x�����߂�
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);
		//�ړI�̊p�x���獡�̊p�x�̊Ԃ𒲂ׂ�
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 30.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;
		break;

	case 11://��������

		if (g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime >= 30)
		{//��莞�Ԃ�������
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;		//���̃��[�V�����փJ�E���g
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//�^�C�}�[�[��
			PlaySound(SOUND_LABEL_SNAKE_VOIS_SE);				//�ւ̐�

		}
		else
		{//�p�x�𑫂�������
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime++;

		}

		break;

	case 12://�����փS�[
		//���̏ꏊ����ړI�̒l�܂ł̊Ԃ𒲂ׂ�
		distance = (SCREEN_WIDTH * 2.0f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT * 0.8f - g_aEnemy[nSnakeHead].pos.y);
		//�ړI�n�܂ł̊p�x�Ƌ��������߂�
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);

		if (g_aEnemy[nSnakeHead].snakeMove.fLength >= 30)
		{//�߂��Ȃ�������
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 2.0f;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 2.0f;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
		}
		else
		{//�߂��Ȃ�����
			g_aEnemy[nSnakeHead].snakeMove.nLoopCnt++;
			if (g_aEnemy[nSnakeHead].snakeMove.nLoopCnt >= 1)
			{
				//�I���
				g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 0;//���̃��[�V�����փJ�E���g
				g_aEnemy[nSnakeHead].snake.snakeState = SNAKESTATE_STANDE;//��Ԃ�ҋ@��Ԃ�
				g_aEnemy[nSnakeHead].snake.bAttack = false;//�ҋ@���
			}
			else
			{
				//�J��Ԃ�
				g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 7;
			}
		}
		break;
	}
}

//===============================
//�ւ̑ҋ@���
//===============================
void SnakeStand(int nSnakeHead)
{
	int nCntEnemy = 0;
	float fLoty = 0.0f;
	float distance, distance1 = 0.0f;

	D3DXVECTOR3 fMovey = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Player* pPlayer = GetPlayer();	//�v���C���[�擾

	switch (g_aEnemy[nSnakeHead].snakeMove.nCntMotion)
	{
	case 0://�ړI�n�ւ̊p�x�����߂�
		//���̏ꏊ����ړI�̒l�܂ł̊Ԃ𒲂ׂ�
		distance = (pPlayer->pos.x - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (pPlayer->pos.y - g_aEnemy[nSnakeHead].pos.y);
		//�ړI�̊p�x�����߂�
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);
		//�ړI�̊p�x���獡�̊p�x�̊Ԃ𒲂ׂ�
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 15.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;
		break;

	case 1://�_���������֓���������
		g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime++;
		//���̏ꏊ����ړI�̒l�܂ł̊Ԃ𒲂ׂ�
		distance = (pPlayer->pos.x - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (pPlayer->pos.y - g_aEnemy[nSnakeHead].pos.y);
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;

		if (g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime >= 15)
		{//��莞�Ԃ�������
			if (g_aEnemy[nSnakeHead].snakeMove.fLength >= 200)
			{//����Ă�����
				g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 2;		//���̃��[�V�����փJ�E���g
				g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//�^�C�}�[�[��
			}
			else if (g_aEnemy[nSnakeHead].snakeMove.fLength < 100)
			{//�߂�������
				g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 3;		//���̃��[�V�����փJ�E���g
				g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//�^�C�}�[�[��
			}
			else
			{//�ǂ���ł��Ȃ�
				g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 0;		//���̃��[�V�����փJ�E���g
				g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//�^�C�}�[�[��
			}
		}
		else
		{//�p�x�𑫂�������
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		break;

	case 2://�߂Â�
		//���̏ꏊ����ړI�̒l�܂ł̊Ԃ𒲂ׂ�
		distance = (pPlayer->pos.x - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (pPlayer->pos.y - g_aEnemy[nSnakeHead].pos.y);
		//�ړI�̊p�x�����߂�
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);
		//�����𒲂ׂ�
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;
		//�ړI�̊p�x���獡�̊p�x�̊Ԃ𒲂ׂ�
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle);

		if (g_aEnemy[nSnakeHead].snakeMove.fLength < 200)
		{//�߂Â��Ă�����
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 0;		//���̃��[�V�����փJ�E���g
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//�^�C�}�[�[��
		}
		else
		{
			//�����Ă�������Ɉړ�������
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 0.6f;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 0.6f;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
			g_aEnemy[nSnakeHead].vertex.fLot = g_aEnemy[nSnakeHead].snakeMove.fLot;

		}
		break;

	case 3://���������
		//���̏ꏊ����ړI�̒l�܂ł̊Ԃ𒲂ׂ�
		distance = (pPlayer->pos.x - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (pPlayer->pos.y - g_aEnemy[nSnakeHead].pos.y);
		//�ړI�̊p�x�����߂�
		g_aEnemy[nSnakeHead].snakeMove.fAngle =- atan2f(distance, distance1);
		//�����𒲂ׂ�
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;
		//�ړI�̊p�x���獡�̊p�x�̊Ԃ𒲂ׂ�
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle);

		if (g_aEnemy[nSnakeHead].snakeMove.fLength >= 500)
		{//�����Ȃ�����
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 0;		//���̃��[�V�����փJ�E���g
		}
		else
		{
			//�����Ă�������Ɉړ�������
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 0.6f;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 0.6f;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
			g_aEnemy[nSnakeHead].vertex.fLot = g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		break;
	}
}