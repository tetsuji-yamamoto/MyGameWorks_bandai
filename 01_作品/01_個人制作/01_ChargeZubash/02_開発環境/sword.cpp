//===================================================================================
//
//���̏���
//
//===================================================================================
#include "main.h"
#include "sword.h"
#include "input.h"
#include "player.h"
#include "thunder.h"
#include "charge.h"
#include "particle.h"
#include "effect.h"
#include "hit.h"
#include "enemy.h"
#include "sound.h"

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureSword = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVteBuffSword = NULL;	//���_�o�b�t�@�ւ̃|�C���^
SWORD g_Sword;									//���̏��
SWORDANIM g_aSwordAnim[SWORDANIMTYPE_MAX];		//���̃A�j���[�V�������

//====================
//Sword�̏���������
//====================
void InitSword(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		SWORD_TEX,
		&g_pTextureSword);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVteBuffSword,
		NULL);

	VERTEX_2D* pVtx;

	//���b�N
	g_pVteBuffSword->Lock(0, 0, (void**)&pVtx, 0);

	//������
	g_Sword.pos = D3DXVECTOR3(600.0f, 400.0f, 0.0f);	//�ʒu
	g_Sword.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
	g_Sword.TopLeft = D3DXVECTOR2(0.0f,0.0f);			//0
	g_Sword.TopRight = D3DXVECTOR2(0.0f, 0.0f);			//1
	g_Sword.BottomLeft = D3DXVECTOR2(0.0f, 0.0f);		//2
	g_Sword.BottomRight = D3DXVECTOR2(0.0f, 0.0f);		//3
	g_Sword.rectHitBox = {};				//�����蔻��̎l�p
	g_Sword.nMoveCnt = 0;				//�U���̌㌄�J�E���g
	g_Sword.nState = SWORDANIMTYPE_NONE;	//�ʏ���
	g_Sword.fLength = 0.0f;					//�Ίp��
	g_Sword.fAngle = 0.0f;					//�p�x
	g_Sword.fLot = 0.0f;					//�p�x
	g_Sword.fKeepLot = 0.0f;				//�L�[�v�p�x
	g_Sword.fPositionX = PLAYER_WIDTH;		//���̈ʒu����
	g_Sword.bUse = false;					//�g�p���Ȃ�
	g_Sword.bHit = false;					//������Ȃ�
	g_Sword.bJustDisCharge = false;			//�W���X�g����Ȃ�

	//�r�[���\�[�h
	g_Sword.beamSword.Andercol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Sword.beamSword.Floatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Sword.beamSword.tracecol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Sword.beamSword.fBSWidth = 0.0f;
	g_Sword.beamSword.fBSHeight = 0.0f;
	g_Sword.beamSword.bBeamSword = false;
	g_Sword.beamSword.bBeamSword = false;	//�������Ȃ�

	for (int nCnt = 0;nCnt < SWORDANIMTYPE_MAX;nCnt++)
	{
		g_aSwordAnim[nCnt].nAnimTurn = SWORDATTACK_PREMOVE;	//�U�����
		g_aSwordAnim[nCnt].fAnimCnt1 = 0;					//�A�j���[�V�����J�E���g1
		g_aSwordAnim[nCnt].fAnimCnt2 = 0;					//�A�j���[�V�����J�E���g2
		g_aSwordAnim[nCnt].fAnimCnt3 = 0;					//�A�j���[�V�����J�E���g3
		g_aSwordAnim[nCnt].fBetweenLot = 0.0f;				//�ړI�̒l���獡�̒l�̊Ԃ̊p�x
		g_aSwordAnim[nCnt].fDesiredValueLot1 = 0.0f;		//�ړI�̒l1
		g_aSwordAnim[nCnt].fDesiredValueLot2 = 0.0f;		//�ړI�̒l2
		g_aSwordAnim[nCnt].fDesiredValueLot3 = 0.0f;		//�ړI�̒l3
		g_aSwordAnim[nCnt].bSetAnim = false;				//�v�Z���邩�ǂ���
	}

	//���W
	pVtx[0].pos.x = g_Sword.pos.x - SWORD_WIDTH;
	pVtx[0].pos.y = g_Sword.pos.y - SWORD_HEIGHT;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_Sword.pos.x + SWORD_WIDTH;
	pVtx[1].pos.y = g_Sword.pos.y - SWORD_HEIGHT;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_Sword.pos.x - SWORD_WIDTH;
	pVtx[2].pos.y = g_Sword.pos.y;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_Sword.pos.x + SWORD_WIDTH;
	pVtx[3].pos.y = g_Sword.pos.y;
	pVtx[3].pos.z = 0.0f;
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = g_Sword.col;
	pVtx[1].col = g_Sword.col;
	pVtx[2].col = g_Sword.col;
	pVtx[3].col = g_Sword.col;
	//�e�N�X�`�����W�̐ݒ�@�@
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//�A�����b�N
	g_pVteBuffSword->Unlock();

	SetSword(D3DXVECTOR3(600.0f, 300.0f, 0.0f));
	
}
//====================
//Sword�̏I������
//====================
void UninitSword(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSword != NULL)
	{
		g_pTextureSword->Release();
		g_pTextureSword = NULL;
	}

	if (g_pVteBuffSword != NULL)
	{
		g_pVteBuffSword->Release();
		g_pVteBuffSword = NULL;
	}
}
//====================
//Sword�̍X�V����
//====================
void UpdateSword(void)
{
	float fLot = 0.0f; //�p�x
	float fEMPos = 0.0f;
	D3DXVECTOR3 Epos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 hitSwordpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	Player* pPlayer = GetPlayer();	//�v���C���[���擾
	ENEMY* pEnemy = GetEnemy();		//�G�l�~�[�擾

	VERTEX_2D* pVtx;

	//��Ԃɂ�鏈��
	switch (g_Sword.nState)
	{
		//�ʏ���--------------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_NONE:
		EquipmentSword();//��ʒu�ɖ߂�

		if (KeyboardTrigger(DIK_E) == true || GetJoypadTrigger(JOYKEY_X) == true)
		{//�ʏ�U��
			g_Sword.nState = SWORDANIMTYPE_ATTACK;		//�U�����[�h��
		}
		else if (KeyboardTrigger(DIK_F) == true || GetJoypadTrigger(JOYKEY_Y) == true)
		{//���o
			g_Sword.nState = SWORDANIMTYPE_DISCHARGE;	//���o���[�h��
		}
		break;

		//�U�����--------------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_ATTACK:
		SetSwordAnim(g_Sword.nState, 7.0f,3.0f,15.0f, D3DX_PI * 0.4f, -D3DX_PI * 0.6f, D3DX_PI * 0.6f);//���Z�b�g
		SwordAnimation(SWORDANIMTYPE_ATTACK);//�U���A�j���[�V�����ɂ���

		//�ʏ�U���̓����蔻��̑傫��
		g_Sword.rectHitBox.bottom = g_Sword.pos.y;
		g_Sword.rectHitBox.left = g_Sword.pos.x;
		g_Sword.rectHitBox.right = sinf(D3DX_PI + fLot) * SWORD_HEIGHT;
		g_Sword.rectHitBox.top = cosf(D3DX_PI - fLot) * SWORD_HEIGHT;
		break;

		//�`���[�W���----------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_CHARGE:
		SetSwordAnim(g_Sword.nState, 15.0f, 60.0f, 15.0f, -D3DX_PI * 2.0f, -D3DX_PI * 2.0f, D3DX_PI * 0.3f);	//���Z�b�g
		SwordAnimation(SWORDANIMTYPE_CHARGE);	//�`���[�W�A�j���[�V�����ɂ���
		if (HitThunder(g_Sword.pos, SWORD_HEIGHT) == true)
		{
			ChargePower(THUNDER_DAMAGE);
		}
		break;

		//���o���--------------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_DISCHARGE:
		SetSwordAnim(g_Sword.nState, 60.0f,120.0f, 60.0f, D3DX_PI * 2.6f, -D3DX_PI * 0.9f, -D3DX_PI * 0.9f);//���Z�b�g
		SwordAnimation(SWORDANIMTYPE_DISCHARGE);	//���o�A�j���[�V�����ɂ���
		BeamSwordGeneration(g_aSwordAnim[SWORDANIMTYPE_DISCHARGE].nAnimTurn);	//�r�[���\�[�h����

		//�r�[���\�[�h�̓����蔻��
		g_Sword.rectHitBox.right = sinf(D3DX_PI + fLot) * g_Sword.beamSword.fBSHeight;
		g_Sword.rectHitBox.top = cosf(D3DX_PI - fLot) * g_Sword.beamSword.fBSHeight;
		break;

		//�W���X�g���o----------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_JUSTDISCHARGE:
		SwordAnimation(SWORDANIMTYPE_JUSTDISCHARGE);	//�W���X�g���o�A�j���[�V�����ɂ���
		BeamSwordGeneration(g_aSwordAnim[SWORDANIMTYPE_JUSTDISCHARGE].nAnimTurn);	//�r�[���\�[�h����
		break;

	default:
		break;
	}

	//���Ƃ̓����蔻��
	if (HitThunder(pPlayer->pos, PLAYER_HEIGHT) == true )
	{
		if (g_Sword.nState == SWORDANIMTYPE_DISCHARGE)
		{//���o��ԁH
			if (g_aSwordAnim[SWORDANIMTYPE_DISCHARGE].bSetAnim == true &&
				g_aSwordAnim->nAnimTurn == SWORDATTACK_PREMOVE &&
				g_Sword.nMoveCnt <= DISCHARGE_TIMING)
			{//���������^�C�~���O���ǂ�������
				g_aSwordAnim[SWORDANIMTYPE_DISCHARGE].nAnimTurn = SWORDATTACK_PREMOVE;
				g_aSwordAnim[SWORDANIMTYPE_DISCHARGE].bSetAnim = false;	//�Z�b�g�ł����Ԃ�
				g_Sword.bJustDisCharge = true;
				g_Sword.nState = SWORDANIMTYPE_JUSTDISCHARGE;			//�W���X�g���o���
				SetSwordAnim(g_Sword.nState, 5.0f, 30.0f, 7.0f, D3DX_PI * 0.3f, -D3DX_PI * 0.9f, D3DX_PI * 0.3f);//���Z�b�g
			}
		}
	}

	//���b�N
	g_pVteBuffSword->Lock(0, 0, (void**)&pVtx, 0);

	//�ʒu�ݒ�
	g_Sword.pos.y = pPlayer->pos.y - PLAYER_HEIGHT * 0.5f;	

	if (pPlayer->bDirection == false)
	{//������
		g_Sword.pos.x = pPlayer->pos.x - g_Sword.fPositionX;	//�ʒu
		fLot = g_Sword.fLot * -1.0f;							//����
	}
	else if (pPlayer->bDirection == true)
	{//�E����
		g_Sword.pos.x = pPlayer->pos.x + g_Sword.fPositionX;	//�ʒuX
		fLot = g_Sword.fLot;									//����
	}

	g_Sword.fKeepLot = fLot;

	if (g_Sword.fLot >= D3DX_PI * 2.0f)
	{
		g_Sword.fLot = 0.0f;
	}
	else if (g_Sword.fLot >= D3DX_PI * 2.0f)
	{
		g_Sword.fLot = 0.0f;
	}

	g_Sword.TopLeft.x = sinf(-D3DX_PI * 0.5f + g_Sword.fAngle - fLot) * g_Sword.fLength;	//0X
	g_Sword.TopLeft.y = cosf(D3DX_PI * 0.5f + g_Sword.fAngle - fLot) * g_Sword.fLength;		//0Y
	g_Sword.TopRight.x = sinf(D3DX_PI * 0.5f + g_Sword.fAngle + fLot) * g_Sword.fLength;	//1X
	g_Sword.TopRight.y = cosf(D3DX_PI * 0.5f + g_Sword.fAngle + fLot) * g_Sword.fLength;	//1Y
	g_Sword.BottomLeft.x = sinf(-D3DX_PI * 0.5f - fLot) * SWORD_WIDTH;						//2X
	g_Sword.BottomLeft.y = cosf(-D3DX_PI * 0.5f + fLot) * SWORD_WIDTH;						//2Y
	g_Sword.BottomRight.x = sinf(D3DX_PI * 0.5f - fLot) * SWORD_WIDTH;						//3X
	g_Sword.BottomRight.y = cosf(-D3DX_PI + 0.5f - fLot) * SWORD_WIDTH;						//3Y

	//�����蔻��
	switch (g_Sword.nState)
	{//��Ԃɂ�鏈��
		//�ʏ���--------------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_NONE:
		g_Sword.rectHitBox.bottom = g_Sword.pos.y;
		g_Sword.rectHitBox.left = g_Sword.pos.x;
		g_Sword.rectHitBox.right = 0.0f;
		g_Sword.rectHitBox.top = 0.0f;
		break;

		//�U�����--------------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_ATTACK:
		//�ʏ�U���̓����蔻��̑傫��
		g_Sword.rectHitBox.right = sinf(D3DX_PI + fLot) * SWORD_HEIGHT * 0.5f;
		g_Sword.rectHitBox.top = cosf(D3DX_PI - fLot) * SWORD_HEIGHT * 0.5f;
		break;

		//�`���[�W���----------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_CHARGE:
		break;

		//���o���--------------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_DISCHARGE:
		//�r�[���\�[�h�̓����蔻��
		g_Sword.rectHitBox.right = sinf(D3DX_PI + fLot) * g_Sword.beamSword.fBSHeight * 0.5f;
		g_Sword.rectHitBox.top = cosf(D3DX_PI - fLot) * g_Sword.beamSword.fBSHeight * 0.5f;
		break;

		//�W���X�g���o----------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_JUSTDISCHARGE:
		g_Sword.rectHitBox.right = sinf(D3DX_PI + fLot) * g_Sword.beamSword.fBSHeight * 0.5f;
		g_Sword.rectHitBox.top = cosf(D3DX_PI - fLot) * g_Sword.beamSword.fBSHeight * 0.5f;
		break;

	default:
		break;
	}

	//���N�g�����
	hitSwordpos.x = g_Sword.pos.x + g_Sword.rectHitBox.right;
	hitSwordpos.y = g_Sword.pos.y + g_Sword.rectHitBox.top;

	SetEffect(g_Sword.pos,						//�ʒu
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//�ړ���
		D3DXCOLOR(0.0f, 0.9f, 1.0f, 0.5f),		//�F
		EFFECTTYPE_NOMAL,						//�ʏ�G�t�F�N�g
		5.0f,									//�|���S���T�C�Y
		0.0f,									//����
		0.0f,									//��
		0.01f,									//�|���S���T�C�Y������
		0.0f,									//�ړ��ʌ�����
		10.0f,									//����
		0.0f,									//�p�x
		-1										//�������
	);

	if (g_Sword.rectHitBox.right < 0)
	{//�}�C�i�X�l�ɂȂ�Ȃ��悤�ɂ���
		g_Sword.rectHitBox.right *= -1.0f;
	}

	if (g_Sword.rectHitBox.top < 0)
	{//�}�C�i�X�l�ɂȂ�Ȃ��悤�ɂ���
		g_Sword.rectHitBox.top *= -1.0f;
	}
	
	g_Sword.rectHitBox.bottom = g_Sword.rectHitBox.top;
	g_Sword.rectHitBox.left = g_Sword.rectHitBox.right;

	if (g_Sword.bHit == true)
	{//�������Ԃ�������
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{//�T��
			if (pEnemy->bUse == true)
			{//�g���Ă�����
				if (HitBox(g_Sword.rectHitBox, pEnemy->rect, hitSwordpos, pEnemy->pos, ANCHORPOINT_CENTER, ANCHORPOINT_CENTER) == true)
				{//�������Ă���
					if (g_Sword.beamSword.bBeamSword == true && pEnemy->state == ENEMYSTATE_NORMAL)
					{//�r�[���U����������
						//�p�[�e�B�N������
						SetParticle(pEnemy->pos,					//�ʒu
							D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f),		//�F
							EFFECTTYPE_NOMAL,	//���
							20,					//�o����
							314,				//�o���p�x
							100.0f,				//����
							0.0f,				//�ړ��ʌ�����
							4.0f,				//�|���S���T�C�Y
							0.0f,				//�|���S���T�C�Y������
							0.0f,				//�_���̊p�x
							60,					//����
							5.0f,				//�Œ�̈ړ���
							0.0f,				//��
							0.0f,				//����
							-1);
					}

					//�G�_���[�W����
					HitEnemy(nCntEnemy, 1);
				}
			}
		}
	}
	
	//���W
	pVtx[0].pos.x = g_Sword.pos.x + g_Sword.TopLeft.x;
	pVtx[0].pos.y = g_Sword.pos.y + g_Sword.TopLeft.y;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_Sword.pos.x + g_Sword.TopRight.x;
	pVtx[1].pos.y = g_Sword.pos.y + g_Sword.TopRight.y;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_Sword.pos.x + g_Sword.BottomLeft.x;
	pVtx[2].pos.y = g_Sword.pos.y + g_Sword.BottomLeft.y;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_Sword.pos.x + g_Sword.BottomRight.x;
	pVtx[3].pos.y = g_Sword.pos.y + g_Sword.BottomRight.y;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = g_Sword.col;
	pVtx[1].col = g_Sword.col;
	pVtx[2].col = g_Sword.col;
	pVtx[3].col = g_Sword.col;

	//�e�N�X�`�����W�̐ݒ�@�@
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�A�����b�N
	g_pVteBuffSword->Unlock();
}

//====================
//Sword�̕`�揈��
//====================
void DrawSword(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�g�p���Ă�����\������
	if (g_Sword.bUse == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVteBuffSword, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSword);

		//���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			0,										//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);										//�`�悷��v���~�e�B�u�i���j��
	}
}
//=========================
//���̐ݒ�
//=========================
void SetSword(D3DXVECTOR3 pos)
{
	if (g_Sword.bUse == false)
	{
		VERTEX_2D* pVtx;

		//���b�N
		g_pVteBuffSword->Lock(0, 0, (void**)&pVtx, 0);

		//������
		g_Sword.pos = pos;																				//�ʒu
		g_Sword.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);												//�F
		g_Sword.fAngle = atan2f(SWORD_HEIGHT, SWORD_WIDTH);												//�p�x
		g_Sword.fLength = sqrtf((SWORD_WIDTH * SWORD_WIDTH) + (SWORD_HEIGHT * SWORD_HEIGHT));			//�Ίp��
		g_Sword.fLot = 0.0f;																			//�p�x
		g_Sword.TopLeft.x = sinf(-D3DX_PI * 0.5f + g_Sword.fAngle - g_Sword.fLot) * g_Sword.fLength;	//0X
		g_Sword.TopLeft.y = cosf(D3DX_PI * 0.5f + g_Sword.fAngle - g_Sword.fLot) * g_Sword.fLength;		//0Y
		g_Sword.TopRight.x = sinf(D3DX_PI * 0.5f + g_Sword.fAngle + g_Sword.fLot) * g_Sword.fLength;	//1X
		g_Sword.TopRight.y = cosf(D3DX_PI * 0.5f + g_Sword.fAngle + g_Sword.fLot) * g_Sword.fLength;	//1Y
		g_Sword.BottomLeft.x = sinf(-D3DX_PI * 0.5 - g_Sword.fLot) * SWORD_WIDTH;						//2X
		g_Sword.BottomLeft.y = cosf(-D3DX_PI * 0.5 + g_Sword.fLot) * SWORD_WIDTH;						//2Y
		g_Sword.BottomRight.x = sinf(D3DX_PI * 0.5 - g_Sword.fLot) * SWORD_WIDTH;						//3X
		g_Sword.BottomRight.y = cosf(-D3DX_PI * 0.5 - g_Sword.fLot) * SWORD_WIDTH;						//3Y
		g_Sword.bUse = true;																			//�g�p����

		//���W
		pVtx[0].pos.x = g_Sword.pos.x + g_Sword.TopLeft.x;
		pVtx[0].pos.y = g_Sword.pos.y + g_Sword.TopLeft.y;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_Sword.pos.x + g_Sword.TopRight.x;
		pVtx[1].pos.y = g_Sword.pos.y + g_Sword.TopRight.y;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_Sword.pos.x + g_Sword.BottomLeft.x;
		pVtx[2].pos.y = g_Sword.pos.y + g_Sword.BottomLeft.y;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_Sword.pos.x + g_Sword.BottomRight.x;
		pVtx[3].pos.y = g_Sword.pos.y + g_Sword.BottomRight.y;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = g_Sword.col;
		pVtx[1].col = g_Sword.col;
		pVtx[2].col = g_Sword.col;
		pVtx[3].col = g_Sword.col;

		//�e�N�X�`�����W�̐ݒ�@�@
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�A�����b�N
		g_pVteBuffSword->Unlock();
	}
}

//==================
//���̏��擾
//==================
SWORD* GetSword(void)
{
	return &g_Sword;
}

//==========================
//���̃A�j���[�V�������擾
//==========================
SWORDANIM* GetSwordAnim(void)
{
	return &g_aSwordAnim[0];
}

//=========================
//���𑕔�
//=========================
void EquipmentSword(void)
{
	//�v���C���[���擾
	Player* pPlayer = GetPlayer();

	g_Sword.fLot = D3DX_PI * 0.3f;	//�p�x
}

//=========================
//���̃��[�V����
//=========================
void SwordAnimation(int nType)
{
	switch (g_aSwordAnim[nType].nAnimTurn)
	{
	case SWORDATTACK_PREMOVE:

		//�v�Z���ĉ�]�����Ă���
		g_Sword.fLot += g_aSwordAnim[nType].fBetweenLot * (1 / g_aSwordAnim[nType].fAnimCnt1);	//�p�x�𑫂��Ă���
 		g_Sword.nMoveCnt++;																		//�J�E���^�[���Z

		if (g_Sword.nMoveCnt >= g_aSwordAnim[nType].fAnimCnt1)
		{//���ȏ�i�񂾂�
			g_aSwordAnim[nType].fBetweenLot = g_aSwordAnim[nType].fDesiredValueLot2 - g_Sword.fLot;//���̖ړI�̒l���獡�̒l�̊Ԃ̒l���v�Z
			g_Sword.bHit = true;									//������悤�ɂ���
			g_Sword.nMoveCnt = 0;									//�J�E���^�[���[��
			g_aSwordAnim[nType].nAnimTurn = SWORDATTACK_MAINMOVE;	//����3
		}
		break;

	case SWORDATTACK_MAINMOVE:

		//�v�Z���ĉ�]�����Ă���
		g_Sword.fLot += g_aSwordAnim[nType].fBetweenLot * (1 / g_aSwordAnim[nType].fAnimCnt2);	//�p�x�������Ă���
		g_Sword.nMoveCnt++;																		//�J�E���^�[���Z

		if (g_Sword.nMoveCnt >= g_aSwordAnim[nType].fAnimCnt2)
		{//���ȏ�i�񂾂�
			g_aSwordAnim[nType].fBetweenLot = g_aSwordAnim[nType].fDesiredValueLot3 - g_Sword.fLot;//���̖ړI�̒l���獡�̒l�̊Ԃ̒l���v�Z
			g_Sword.nMoveCnt = 0;									//�J�E���^�[���[��
			g_aSwordAnim[nType].nAnimTurn = SWORDATTACK_LEARMOVE;	//����
		}
		break;

	case SWORDATTACK_LEARMOVE:

		//�v�Z���ĉ�]�����Ă���
		g_Sword.fLot += g_aSwordAnim[nType].fBetweenLot * (1 / g_aSwordAnim[nType].fAnimCnt3);	//�p�x�𑫂��Ă���
		g_Sword.nMoveCnt++;																		//�J�E���^�[���Z

		if (g_Sword.nMoveCnt >= g_aSwordAnim[nType].fAnimCnt3)
		{//���ȏ�i�񂾂�
			g_Sword.bHit = false;									//������Ȃ��悤�ɂ���
			g_aSwordAnim[nType].bSetAnim = false;					//�Z�b�g�ł����Ԃ�
			g_Sword.nMoveCnt = 0;									//�J�E���^�[���[��
			g_aSwordAnim[nType].nAnimTurn = SWORDATTACK_PREMOVE;	//�ŏ�����
			g_Sword.nState = SWORDANIMTYPE_NONE;					//�ʏ탂�[�h
		}
		break;

	default:
		g_aSwordAnim[nType].bSetAnim = false;					//�Z�b�g�ł����Ԃ�
		g_aSwordAnim[nType].nAnimTurn = SWORDATTACK_PREMOVE;	//�ŏ�����
		g_Sword.nState = SWORDANIMTYPE_NONE;					//�ʏ탂�[�h
		break;
	}
}

//=========================
//���̃��[�V����
//=========================
void SetSwordAnim(int type, float fCnt1, float fCnt2, float fCnt3, float fDesValuLot1, float fDesValuLot2, float fDesValuLot3)
{
	
	if (g_aSwordAnim[type].bSetAnim == false)
	{
		//�ݒ肵����Ԃɂ���
		g_aSwordAnim[type].bSetAnim = true;
		//�l����
		g_aSwordAnim[type].fDesiredValueLot1 = fDesValuLot1;
		g_aSwordAnim[type].fDesiredValueLot2 = fDesValuLot2;
		g_aSwordAnim[type].fDesiredValueLot3 = fDesValuLot3;
		g_aSwordAnim[type].fAnimCnt1 = fCnt1;
		g_aSwordAnim[type].fAnimCnt2 = fCnt2;
		g_aSwordAnim[type].fAnimCnt3 = fCnt3;
		//�ړI�̒l���獡�̒l�̊Ԃ̒l���v�Z
		g_aSwordAnim[type].fBetweenLot = g_aSwordAnim[type].fDesiredValueLot1 - g_Sword.fLot;
	}
}

//=========================
//���̓����蔻��
//=========================
bool HitSword(D3DXVECTOR3 pos,float fWidth)
{
	bool bHit = false;//�����������ǂ���

	D3DXVECTOR2 hitPos;
	float fNowDistance;
	float fDistance = 0.0f;
	float fXDis = 0.0f;
	float fYDis = 0.0f;

	if (g_Sword.bHit == true)
	{//�������Ԃ�������

		//��Ԃɂ�鏈��
		switch (g_Sword.nState)
		{
			//�ʏ���--------------------------------------------------------------------------------------------------------------------------
		case SWORDANIMTYPE_NONE:
			break;

			//�U�����--------------------------------------------------------------------------------------------------------------------------
		case SWORDANIMTYPE_ATTACK:

			//���̐�[����
			hitPos.x = (sinf(-g_Sword.fLot) * SWORD_HEIGHT);
			hitPos.y = (cosf(D3DX_PI + g_Sword.fLot) * SWORD_HEIGHT);
			hitPos.x += (g_Sword.pos.x);
			hitPos.y += (g_Sword.pos.y);

			//���a�����킹������
			fDistance = SWORD_WIDTH + fWidth;

			//���̋�����
			fXDis = hitPos.x - pos.x;
			fYDis = hitPos.y - pos.y;

			fNowDistance = sqrtf((fXDis * fXDis) + (fYDis * fYDis) * 0.5f);

			//�~�ǂ����̓����蔻��
			if (fNowDistance < fDistance)
			{
				//�����������Ƃɂ���
				bHit = true;
			}
			break;

			//�`���[�W���----------------------------------------------------------------------------------------------------------------------
		case SWORDANIMTYPE_CHARGE:
		
			break;

			//���o���--------------------------------------------------------------------------------------------------------------------------
		case SWORDANIMTYPE_DISCHARGE:
			
			break;

		default:
			break;
		}	
	}

	//�l��Ԃ�
	return bHit;
}

//=========================
//�r�[�����̐ݒ�
//=========================
void BeamSwordGeneration(int nTurn)
{
	CHARGE* pCharge = GetCharge();//�`���[�W�擾

	

	if (g_Sword.bJustDisCharge == true)
	{//�W���X�g��������
		g_Sword.beamSword.Andercol = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
		g_Sword.beamSword.Floatcol = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);
		g_Sword.beamSword.tracecol = D3DXCOLOR(1.0f, 0.8f, 0.8f, 0.1f);
	}
	else
	{
		g_Sword.beamSword.Andercol = D3DXCOLOR(1.0f, 1.0f, 0.3f, 1.0f);
		g_Sword.beamSword.Floatcol = D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f);
		g_Sword.beamSword.tracecol = D3DXCOLOR(1.0f, 1.0f, 0.8f, 0.1f);
	}

	switch (nTurn)
	{

	case SWORDATTACK_PREMOVE:
		if (pCharge->fChargrAmount != 0)
		{//�`���[�W����Ă���
			g_Sword.beamSword.fBSHeight = (BEAMSWORD_HEIGHT / MAX_ELECTRICPOWER) * pCharge->fChargrAmount + SWORD_HEIGHT;	//����
		}
		else if (pCharge->fChargrAmount == 0)
		{//�`���[�W����ĂȂ�������
			g_Sword.beamSword.fBSHeight = 0.0f;	//����
		}
		break;

	case SWORDATTACK_MAINMOVE:

		if (g_Sword.beamSword.bBeamSword == false)
		{//�g���ĂȂ�������
			g_Sword.beamSword.bBeamSword = true;	//��������
			ChargePower((pCharge->fChargrAmount) * -1);


			g_Sword.beamSword.fBSWidth = 15.0f;		//��

			SetEffect(g_Sword.pos,						//�ʒu
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//�ړ���
				g_Sword.beamSword.Andercol,				//�F
				EFFECTTYPE_BEAMSWORD,					//�ʏ�G�t�F�N�g
				0.0f,									//�|���S���T�C�Y
				g_Sword.beamSword.fBSHeight,			//����
				15.0f,									//��
				0.0f,									//�|���S���T�C�Y������
				0.0f,									//�ړ��ʌ�����
				1.0f,									//����
				0.0f,									//�p�x
				BEAMBEAMBEAM										//�������
			);

			SetEffect(g_Sword.pos,						//�ʒu
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//�ړ���
				g_Sword.beamSword.Floatcol,				//�F
				EFFECTTYPE_BEAMSWORD,					//�ʏ�G�t�F�N�g
				0.0f,									//�|���S���T�C�Y
				g_Sword.beamSword.fBSHeight,			//����
				6,										//��
				0.0f,									//�|���S���T�C�Y������
				0.0f,									//�ړ��ʌ�����
				1.0f,									//����
				0.0f,									//�p�x
				BEAMBEAMBEAM										//�������
			);

			PlaySound(SOUND_LABEL_BEAMSWORD_GENERATE_SE);//�r�[����
		}

		//�p�[�e�B�N������
		SetParticle(g_Sword.pos,				//�ʒu
			g_Sword.beamSword.tracecol,			//�F
			EFFECTTYPE_BEAM,					//���
			2,			//�o����
			314,		//�o���p�x
			5,			//����
			1.0f,		//�ړ��ʌ�����
			0.0f,		//�|���S���T�C�Y
			0.0f,		//�|���S���T�C�Y������
			0.0f,		//�_���̒l
			7,			//����
			2.0f,		//�Œ�̈ړ���
			10.0f,		//��
			300.0f,		//����
			BEAMBEAMBEAM);
		break;

	case SWORDATTACK_LEARMOVE:
		g_Sword.beamSword.bBeamSword = false;	//�������Ă��Ȃ�
		g_Sword.beamSword.fBSHeight = 0.0f;		//�����[��
		EndEffect(EFFECTTYPE_BEAMSWORD, BEAMBEAMBEAM);		//�r�[���\�[�h����
		StopSound(SOUND_LABEL_BEAMSWORD_GENERATE_SE);		//�r�[��������
		break;

	}
}
