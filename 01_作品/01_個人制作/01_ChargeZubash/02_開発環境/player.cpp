//===================================================================================
//
//					�v���C���[�̏���
//
//===================================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "sound.h"
#include "input.h"
#include "block.h"
#include "charge.h"
#include "sword.h"
#include "thunder.h"
#include "result.h"

//����[�΂�錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVteBuffPlayer = NULL;
Player g_player;

//====================
//Player�̏���������
//====================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_PLAYER_002,
		&g_pTexturePlayer);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVteBuffPlayer,
		NULL);

	VERTEX_2D* pVtx;

	//���b�N
	g_pVteBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//������
	g_player.rect.bottom = PLAYER_HEIGHT;
	g_player.rect.left = PLAYER_WIDTH;
	g_player.rect.right = PLAYER_WIDTH;
	g_player.rect.top = PLAYER_HEIGHT;
	g_player.pos = D3DXVECTOR3(300.0f, 200.0f, 0.0f);	//�ʒu
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	g_player.col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);		//�F
	g_player.fLife = MAX_PLAYER_HP;								//�̗�
	g_player.nJanpCounter = 0;							//�W�����v�J�E���g
	g_player.nPatternAnim = 0;							//�A�j���[�V�����p�^�[��
	g_player.nCounterAnim = 0;							//�A�j���[�V�����J�E���^�[
	g_player.nCntSound = 0;								//���J�E���^�[
	g_player.fAnimLine = 0;								//�A�j���[�V�����J�E���^�[
	g_player.fGravity = PLAYER_GRAVITY;					//�d��
	g_player.bDisp = true;								//�\�����邩
	g_player.bJanp = false;								//�W�����v
	g_player.bStand = false;							//�ҋ@��Ԃ��ǂ���
	g_player.bCharge = false;							//�`���[�W���
	g_player.bDirection = true;							//����
	g_player.state = PLAYERSTATE_APPER;					//�v���C���[���
	g_player.pBlock = NULL;								//�Ώۃu���b�N�ւ̃|�C���^

	//���W
	pVtx[0].pos.x = g_player.pos.x - PLAYER_WIDTH;
	pVtx[0].pos.y = g_player.pos.y - PLAYER_HEIGHT;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_player.pos.x + PLAYER_WIDTH;
	pVtx[1].pos.y = g_player.pos.y - PLAYER_HEIGHT;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_player.pos.x - PLAYER_WIDTH;
	pVtx[2].pos.y = g_player.pos.y;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_player.pos.x + PLAYER_WIDTH;
	pVtx[3].pos.y = g_player.pos.y;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = g_player.col;
	pVtx[1].col = g_player.col;
	pVtx[2].col = g_player.col;
	pVtx[3].col = g_player.col;

	//�e�N�X�`�����W�̐ݒ�@�@
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�A�����b�N
	g_pVteBuffPlayer->Unlock();
}
//====================
//Player�̏I������
//====================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	if (g_pVteBuffPlayer != NULL)
	{
		g_pVteBuffPlayer->Release();
		g_pVteBuffPlayer = NULL;
	}
}
//====================
//Player�̍X�V����
//====================
void UpdatePlayer(void)
{
	SWORD* pSword = GetSword();					//�����擾
	SWORDANIM* pSwordAnim = GetSwordAnim();		//���̃A�j���[�V�����擾
	XINPUT_STATE* pStick = GetJoySticAngle();	//�X�e�B�b�N�擾

	VERTEX_2D* pVtx;

	//�A�j���[�V�����x�点
	if (g_player.nCounterAnim >= 10)
	{
		g_player.nCounterAnim = 0;

		//�p�^�[�����J�E���g
		g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 2;
	}

	// ���b�N
	g_pVteBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_player.bDisp == true)
	{
		if (KeyboardRepeat(DIK_A) == true || GetJoypadRepeat(JOYKEY_LEFT) == true || pStick->Gamepad.sThumbLX <= -5000)
		{//���ړ�
			g_player.move.x += - PLAYER_MOVE;//�ړ���
			g_player.nCounterAnim++;		//�A�j���[�V�������J�E���g
			g_player.bDirection = false;	//����
			g_player.nCntSound++;			//���J�E���^�[���Z
		}
		else if (KeyboardRepeat(DIK_D) == true || GetJoypadRepeat(JOYKEY_RIGHT) == true || pStick->Gamepad.sThumbLX >= 5000)
		{//�E�ړ�
			g_player.move.x += PLAYER_MOVE;	//�ړ���
			g_player.nCounterAnim++;		//�A�j���[�V�������J�E���g
			g_player.bDirection = true;		//����
			g_player.nCntSound++;			//���J�E���^�[���Z
		}
		else
		{
			g_player.nPatternAnim = 0;	//�A�j���[�V�������J�E���g
			g_player.nCntSound = 14;	//�������u�ԂȂ�
		}

		//������炷
		if (g_player.nCntSound >= 15)
		{//���ȏ�J�E���g������
			g_player.nCntSound = 0;					//�J�E���g���Z�b�g
			if (g_player.bJanp == false)
			{//�W�����v���ĂȂ�������
				PlaySound(SOUND_LABEL_PLAYERMOVE_SE);	//����
			}
		}

		//�W�����v
		if (KeyboardTrigger(DIK_SPACE) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{
			if (g_player.bJanp == false)
			{
				g_player.move.y -= PLAYER_JUMP;
				g_player.bJanp = true;
				PlaySound(SOUND_LABEL_PLAYERJUMP_SE);
			}
		}

		//����������[�d
		if (HitThunder(g_player.pos, PLAYER_HEIGHT) == true)
		{
			ChargePower(THUNDER_DAMAGE);
			PlaySound(SOUND_LABEL_PLAYERCHARGE_SE);//�`���[�W��
		}

#ifdef _DEBUG //�f�o�b�O�r���h�������g�p�ł���

		if (KeyboardRepeat(DIK_3) == true)
		{//����
			HitPlayer(g_player.fLife);
		}

		if (KeyboardTrigger(DIK_4) == true)
		{
			HitPlayer(1.0f);
		}
		else if (KeyboardTrigger(DIK_5) == true)
		{
			HitPlayer(-1.0f);
		}

		if (KeyboardTrigger(DIK_1) == true)
		{//
			ChargePower(1);
		}
		else if (KeyboardTrigger(DIK_2) == true)
		{//
			ChargePower(-1);
		}
#endif

		//�O��̈ʒu��ۑ�
		g_player.posOld = g_player.pos;

		if (g_player.pBlock != NULL)
		{
			//�u���b�N���ړ������������v���C���[�ɉ��Z����
			g_player.pos += g_player.pBlock->move;
			g_player.posOld += g_player.pBlock->move;
		}

		//�d��
		g_player.move.y += PLAYER_GRAVITY;

		//����
		g_player.move.x += (0 - g_player.move.x * 0.4f);

		//�ړ��ʂ�ǉ�
		g_player.pos.y += g_player.move.y;

		//�u���b�N�Ƃ̓����蔻��
		g_player.bJanp = !CollisionBlockY(&g_player.pos, &g_player.posOld, &g_player.move, PLAYER_HEIGHT, PLAYER_WIDTH,&g_player.pBlock);

		//�ړ��ʂ�ǉ�
		g_player.pos.x += g_player.move.x;

		//�u���b�N�Ƃ̓����蔻��
		CollisionBlockX(&g_player.pos, &g_player.posOld, &g_player.move, PLAYER_HEIGHT, PLAYER_WIDTH,&g_player.pBlock);


		//��ʒ[���甽�Α���
		if (g_player.pos.x - PLAYER_WIDTH > SCREEN_WIDTH)
		{
			g_player.pos.x = 0.0f - PLAYER_WIDTH;
			//�O��̈ʒu��ۑ�
			g_player.posOld = g_player.pos;
		}
		else if (g_player.pos.x + PLAYER_WIDTH < 0.0f)
		{
			g_player.pos.x = SCREEN_WIDTH + PLAYER_WIDTH;
			//�O��̈ʒu��ۑ�
			g_player.posOld = g_player.pos;
		}
		//��ʉ�����
		if (g_player.pos.y > SCREEN_HEIGHT)
		{
			g_player.pos.y = SCREEN_HEIGHT;
			g_player.move.y = 0.0f;
			g_player.bJanp = false;
		}

		//�W�����v��
		if (g_player.bJanp == true)
		{
			//�e�N�X�`��
			g_player.nPatternAnim = 3;
		}

		//��Ԃɂ�鏈��
		switch (g_player.state)
		{
		case PLAYERSTATE_APPER:
			g_player.state = PLAYERSTATE_NOMAL;	//�ʏ��Ԃ�
			break;

		case PLAYERSTATE_NOMAL:
			break;

		case PLAYERSTATE_ATTACK:
			break;

		case PLAYERSTATE_DAMAGE:
			if (g_player.nCounterState > 0)
			{
				g_player.nCounterState--;						//�J�E���^�[������
				g_player.col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);	//�F��ԐF��
			}
			else
			{
				g_player.state = PLAYERSTATE_NOMAL;					//�ʏ��Ԃ�
				g_player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�ʏ�F��
			}
			break;

		case PLAYERSTATE_DETH:
			g_player.bDisp = false;
			if (GetGameState() == GAMESTATE_NORMAL)
			{
				SetFade(MODE_RESULT);
				SetResult(RESULTTYPE_GAMEOVER);	//�Q�[���I�[�o�[
			}
			break;
		}

		//�����ɂ����
		if (g_player.bDirection == true)
		{//�E����
			//�e�N�X�`�����W�̐ݒ�@�@
			pVtx[0].tex = D3DXVECTOR2(0.25f * g_player.nPatternAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f * g_player.nPatternAnim, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.25f * g_player.nPatternAnim, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f * g_player.nPatternAnim, 1.0f);
		}
		else if (g_player.bDirection == false)
		{//������
			//�e�N�X�`�����W�̐ݒ�@�@
			pVtx[0].tex = D3DXVECTOR2(0.25f + 0.25f * g_player.nPatternAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f * g_player.nPatternAnim, 0.0f); 
			pVtx[2].tex = D3DXVECTOR2(0.25f + 0.25f * g_player.nPatternAnim, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f * g_player.nPatternAnim, 1.0f); 
		}

		//���W
		pVtx[0].pos.x = g_player.pos.x - PLAYER_WIDTH;
		pVtx[0].pos.y = g_player.pos.y - PLAYER_HEIGHT;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_player.pos.x + PLAYER_WIDTH;
		pVtx[1].pos.y = g_player.pos.y - PLAYER_HEIGHT;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_player.pos.x - PLAYER_WIDTH;
		pVtx[2].pos.y = g_player.pos.y;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_player.pos.x + PLAYER_WIDTH;
		pVtx[3].pos.y = g_player.pos.y;
		pVtx[3].pos.z = 0.0f;

		//���_�J���[
		pVtx[0].col = g_player.col;
		pVtx[1].col = g_player.col;
		pVtx[2].col = g_player.col;
		pVtx[3].col = g_player.col;
	}

	//�A�����b�N
	g_pVteBuffPlayer->Unlock();
}
//====================
//Player�̕`�揈��
//====================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	if (g_player.bDisp == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVteBuffPlayer, 0, sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			0,										//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);										//�`�悷��v���~�e�B�u�i�v���C���[�j��
	}
}

//==================
//�v���C���[�̎擾
//==================
Player* GetPlayer(void)
{
	return &g_player;
}

//=========================
//�v���C���[�̓����蔻��
//=========================
void HitPlayer(float fDamage)
{
	if (g_player.state == PLAYERSTATE_NOMAL)
	{
		g_player.fLife -= fDamage;	//�̗͌��炷
		PlaySound(SOUND_LABEL_PLAYERDAMAGE_SE);//�_���[�W��

		if (g_player.fLife > 0)
		{//�̗͂�������
			g_player.nCounterState = 60;			//��ԃJ�E���^�[��ݒ�
			g_player.state = PLAYERSTATE_DAMAGE;	//�_���[�W��Ԃ�
		}
		else if (g_player.fLife <= 0)
		{//�̗͂Ȃ�
			if (GetMode() != MODE_TUTORIAL)
			{//�`���[�g���A�����[�h����Ȃ�������
				g_player.state = PLAYERSTATE_DETH;	//�f�X��Ԃ�
			}
			g_player.fLife = 0.0f;
		}
	}
}

//=============================
//�W�����v
//=============================
void PlayerJamp(void)
{

	
}

//=============================
//���odischarge
//=============================
void Discharge(void)
{
	CHARGE* pCharge = GetCharge();//�����܂�
}