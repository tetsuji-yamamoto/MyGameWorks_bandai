#include "player.h"
#include "keyboard.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "particle.h"
#include "joypad.h"
#include "block.h"
#include "wall.h"
#include "enemy.h"
#include "fade.h"
#include "result.h"
#include "edit.h"
#include "smoke.h"
#include "sound.h"

// �O���[�o���ϐ��錾

D3DXMATRIX g_mtxWorldPlayer;				// ���[���h�}�g���b�N�X
PLAYER g_player;							// �v���C���[���
MODELCOLER g_aPlayerModelCol[10][6];		// �֗��ȐF�ۑ��ꏊ
int nIdxShadow = 0;

//************************************************
// �v���C���[������
//************************************************
void InitPlayer(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v���C���[��񏉊���
	
	// �e��ϐ��̏�����
	g_player.pos = D3DXVECTOR3(-100.0f, 100.0f, 0.0f);	// �ʒu
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	g_player.size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);	// �ړ���
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړI����
	g_player.snowBall.nMakeTimerSnow = 0;		// ��ʍ�鎞��
	g_player.snowBall.nMakeTimerSnowMidi = 0;	// ��ʍ�鎞��
	g_player.snowBall.nMakeTimerSnowBig = 0;	// ��ʍ�鎞��
	g_player.snowBall.nMakeTimerIce = 0;		// ��ʍ�鎞��
	g_player.snowBall.nMakeTimerIGravel = 0;	// ��ʍ�鎞��
	g_player.snowBall.bSrow = false;			// �����ĂȂ�

	g_player.nBlockType = 0;				// ����ł�u���b�N
	g_player.snowBall.nSnowBallWeight = 0;	// �ʏd��

	g_player.charParam.nNumModel = 0;		// �p�[�c�̑���
	g_player.charParam.fHeigt = 0.0f;		// ����
	g_player.charParam.fWidth = 0.0f;		// ��
	g_player.charParam.fJamp = PLAYER_JUMP;		// �W�����v��
	g_player.charParam.nLife = PLAYER_HP;			// �̗�
	g_player.charParam.nState = MOTIONTYPE_PLAYER_NEUTRAL;	// �������[�V����
	g_player.charParam.nCntOcc = 0;		// �����J�E���^�[
	g_player.charParam.nCntDura = 0;	// �����J�E���^�[
	g_player.charParam.bMove = false;	// �������ǂ���
	g_player.charParam.bDisp = true;	// �ʂ��܂���
	g_player.charParam.bAttack = false;	// �U�����܂���
	g_player.charParam.bJanp = false;	// �W�����v���܂���

	g_player.motion.bLoopMotion = true;
	g_player.motion.nNumKey = 2;
	g_player.motion.nKey = 0;
	g_player.motion.nCounterMotion = 0;
	g_player.motion.nNextKey = g_player.motion.nKey + 1;

	g_player.nShadowIdx = -1;			// �e�̃C���f�b�N�X
	g_player.naSmokeIdx[0] = -1;		// �e�̃C���f�b�N�X
	g_player.naSmokeIdx[1] = -1;		// �e�̃C���f�b�N�X

	for (int nCnt = 0; nCnt < 12; nCnt++)
	{
		g_player.snowBall.nSnowOrder[nCnt] = -1;
		g_player.snowBall.nIceOrder[nCnt] = -1;
		g_player.snowBall.nGravelOrder[nCnt] = -1;
	}

	// ���[�V�����e�L�X�g�ǂݍ���
	ReadMotionText("date\\motion\\player\\motion.txt", &g_player.aModel[0], &g_player.motion, &g_player.charParam);


	for (int nCntModel = 0; nCntModel < g_player.charParam.nNumModel; nCntModel++)
	{
		g_player.aPlayerColiPoint[nCntModel].fRadius = 10.0f;						// ��
		g_player.aPlayerColiPoint[nCntModel].pos = g_player.aModel[nCntModel].pos;	// �ʒu


		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			
			g_aPlayerModelCol[nCntModel][nCntMat].fR = pMat[nCntMat].MatD3D.Diffuse.r;
			g_aPlayerModelCol[nCntModel][nCntMat].fG = pMat[nCntMat].MatD3D.Diffuse.g;
			g_aPlayerModelCol[nCntModel][nCntMat].fB = pMat[nCntMat].MatD3D.Diffuse.b;
			g_aPlayerModelCol[nCntModel][nCntMat].fA = pMat[nCntMat].MatD3D.Diffuse.a;
		}
	}

	// �e�̐ݒ�
	g_player.nShadowIdx = SetShadw(g_player.pos, g_player.rot,g_player.charParam.fWidth);

	if (GetMode() == MODE_GAME || GetMode() == MODE_TUTORIAL)
	{
		// HP�Q�[�W�̐ݒ�
		SetHPGauge(&g_player.HPGaugeHave[HPGAUGETYPE_BG], HPGAUGETYPE_BG, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.9f), 5.0f, 100.0f, g_player.charParam.nLife);
		SetHPGauge(&g_player.HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], HPGAUGETYPE_GAUGE_REDZONE, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.9f), 5.0f, 100.0f, g_player.charParam.nLife);
		SetHPGauge(&g_player.HPGaugeHave[HPGAUGETYPE_GAUGE], HPGAUGETYPE_GAUGE, D3DXCOLOR(0.5f, 1.0f, 0.0f, 0.9f), 5.0f, 100.0f, g_player.charParam.nLife);

		// ��ʃQ�[�W�̐ݒ�
		SetHPGauge(&g_player.SBGaugeHave[HPGAUGETYPE_BG], HPGAUGETYPE_BG, D3DXCOLOR(0.0f, 0.5f, 0.5f, 0.9f), 5.0f, 100.0f, 1);
		SetHPGauge(&g_player.SBGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], HPGAUGETYPE_GAUGE_REDZONE, D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.9f), 5.0f, 100.0f, 1);

		SetHPGauge(&g_player.SBGaugeHave[HPGAUGETYPE_GAUGE], HPGAUGETYPE_GAUGE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f), 5.0f, 100.0f, SB_MAKETIMER_SNOW);	// ���
		SetHPGauge(&g_player.SBMidiGaugeHave, HPGAUGETYPE_GAUGE, D3DXCOLOR(1.0f, 1.0f, 0.5f, 0.9f), 5.0f, 100.0f, SB_MAKETIMER_SNOW_MIDI - SB_MAKETIMER_SNOW);	// ��ʒ�
		SetHPGauge(&g_player.SBBigGaugeHave, HPGAUGETYPE_GAUGE, D3DXCOLOR(1.0f, 0.5f, 0.5f, 0.9f), 5.0f, 100.0f, SB_MAKETIMER_SNOW_BIG - SB_MAKETIMER_SNOW_MIDI);	// ��ʑ�
		SetHPGauge(&g_player.SBIceGaugeHave, HPGAUGETYPE_GAUGE, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.9f), 5.0f, 100.0f, SB_MAKETIMER_ICE);		// �X��
		SetHPGauge(&g_player.SBGraGaugeHave, HPGAUGETYPE_GAUGE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.9f), 5.0f, 100.0f, SB_MAKETIMER_GRAVEL);	// ������

		SetHPGauge(&g_player.aSBWateGauge[HPGAUGETYPE_BG], HPGAUGETYPE_BG, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.9f), 2.5f, 100.0f, SB_WEIGHT_MAX);
		SetHPGauge(&g_player.aSBWateGauge[HPGAUGETYPE_GAUGE_REDZONE], HPGAUGETYPE_GAUGE_REDZONE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.9f), 2.5f, 100.0f, SB_WEIGHT_MAX);
		SetHPGauge(&g_player.aSBWateGauge[HPGAUGETYPE_GAUGE], HPGAUGETYPE_GAUGE, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.9f), 2.5f, 100.0f, SB_WEIGHT_MAX);
	}
	g_player.naSmokeIdx[0] = SetSmoke(SMOKETYPE_ATTACH,g_player.pos,20, 20.0f,true);
	g_player.naSmokeIdx[1] = SetSmoke(SMOKETYPE_ATTACH,g_player.pos,40, 20.0f,true);
}

//************************************************
// �v���C���[�̏I��
//************************************************
void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < g_player.charParam.nNumModel; nCnt++)
	{
		// ���b�V���̔j��
		if (g_player.aModel[nCnt].pMesh != NULL)
		{
			g_player.aModel[nCnt].pMesh->Release();
			g_player.aModel[nCnt].pMesh = NULL;
		}

		// �}�e���A���̔j��
		if (g_player.aModel[nCnt].pBuffMat != NULL)
		{
			g_player.aModel[nCnt].pBuffMat->Release();
			g_player.aModel[nCnt].pBuffMat = NULL;
		}

		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			//�e�N�X�`���̔j��
			if (g_player.aModel[nCnt].apTexture[nCnt] != NULL)
			{
				g_player.aModel[nCnt].apTexture[nCnt]->Release();
				g_player.aModel[nCnt].apTexture[nCnt] = NULL;
			}
		}
	}
}

//************************************************
// �v���C���[�̍X�V
//************************************************
void UpdatePlayer(void)
{
#ifdef _DEBUG
	if (GetEditMode() == EDITMODE_BLOCK)
	{
		return;
	}

#endif
	if (GetMode() == MODE_GAME || GetMode() == MODE_TUTORIAL)
	{
		if (g_player.charParam.bDisp && 
			g_player.charParam.nState != MOTIONTYPE_PLAYER_ATTACK && 
			g_player.charParam.nState != MOTIONTYPE_PLAYER_ATTACK_SUPER)
		{
			Camera* pCamera = GetCamera();				// �J�����̎擾
			XINPUT_STATE* pJoypad = GetJoypadState();	// �R���g���[���[���擾
			g_player.charParam.bMove = false;						// �����Ȃ���

			// �L�[����
			if (KeyboardRepeat(DIK_W))
			{// �O�ړ�
				g_player.charParam.bMove = true;	// ������

				if (KeyboardRepeat(DIK_A))
				{// ���ړ�
					g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.25f;	// �ړI�̊p�x��ݒ�
				}
				else if (KeyboardRepeat(DIK_D))
				{// �E�ړ�		
					g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.25f;	// �ړI�̊p�x��ݒ�
				}
				else
				{
					g_player.rotDest.y = pCamera->rot.y;	// �ړI�̊p�x��ݒ�
				}
			}
			else if (KeyboardRepeat(DIK_S))
			{// ���ړ�
				g_player.charParam.bMove = true;	// ������
				if (KeyboardRepeat(DIK_A))
				{// ���ړ�
					g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;	// �ړI�̊p�x��ݒ�
				}
				else if (KeyboardRepeat(DIK_D))
				{// �E�ړ�		
					g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;	// �ړI�̊p�x��ݒ�
				}
				else
				{
					g_player.rotDest.y = pCamera->rot.y + D3DX_PI;	// �ړI�̊p�x��ݒ�
				}
			}
			else if (KeyboardRepeat(DIK_A))
			{// ���ړ�
				g_player.charParam.bMove = true;	// ������
				g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.5f;	// �ړI�̊p�x��ݒ�
			}
			else if (KeyboardRepeat(DIK_D))
			{// �E�ړ�		
				g_player.charParam.bMove = true;	// ������
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.5f;	// �ړI�̊p�x��ݒ�
			}

			if (KeyboardRepeat(DIK_RETURN) || GetJoypadRepeat(JOYKEY_R1))
			{// ��ʍ쐬

				

				int nOllSnow = g_player.snowBall.nMakeTimerSnow + g_player.snowBall.nMakeTimerSnowMidi + g_player.snowBall.nMakeTimerSnowBig;	// ��ʂ̂��ׂĂ̎���
				g_player.charParam.nState = MOTIONTYPE_PLAYER_MAKESNOWBALL;

				if (g_player.snowBall.nMakeType != g_player.nBlockType)
				{// �Ⴄ�u���b�N�Ɉڂ�����
					g_player.snowBall.nMakeType = g_player.nBlockType;	// �^�C�v���X�V
					g_player.snowBall.nMakeTimerSnow = 0;		// �쐬�J�E���g�[��
					g_player.snowBall.nMakeTimerSnowMidi = 0;	// �쐬�J�E���g�[��
					g_player.snowBall.nMakeTimerSnowBig = 0;	// �쐬�J�E���g�[��
					g_player.snowBall.nMakeTimerIce = 0;		// �쐬�J�E���g�[��
					g_player.snowBall.nMakeTimerIGravel = 0;	// �쐬�J�E���g�[��
				}

				switch (g_player.snowBall.nMakeType)
				{
				case BLOCKTYPE_SNOW:

					if (nOllSnow < SB_MAKETIMER_SNOW)
					{// ���
						g_player.snowBall.nMakeTimerSnow++;
					}
					else if (nOllSnow < SB_MAKETIMER_SNOW_MIDI && nOllSnow >= SB_MAKETIMER_SNOW)
					{// ��ʂ���i�K�ڍ�ꂽ��
						g_player.snowBall.nMakeTimerSnowMidi++;
					}
					else if (nOllSnow >= SB_MAKETIMER_SNOW_MIDI)
					{// ��ʂ���i�K�ڍ�ꂽ��
						g_player.snowBall.nMakeTimerSnowBig++;
					}
					else
					{// �J�E���g���Z�b�g
						g_player.snowBall.nMakeTimerSnowMidi = 0;
						g_player.snowBall.nMakeTimerSnowBig = 0;
					}
					break;

				case BLOCKTYPE_ICE:	// �X��
					g_player.snowBall.nMakeTimerIce++;
					break;

				case BLOCKTYPE_GRAVEL:	// ������
					g_player.snowBall.nMakeTimerIGravel++;
					break;
				}
			}
			else if (KeyboardRelease(DIK_RETURN) || GetJoypadRelease(JOYKEY_R1))
			{// �����ďd���Ȃ������Ƃ�
				g_player.charParam.nState = MOTIONTYPE_PLAYER_NEUTRAL;
				if (g_player.snowBall.nSnowBallWeight < SB_WEIGHT_MAX)
				{
					int nCntOrder = -1;
					nCntOrder = MakeOrderSnowBall(&g_player.snowBall, &g_player.nBlockType);	// ���Ԃɕ��ׂ�
					SetSBUI(g_player.nBlockType, nCntOrder);	// UI�Z�b�g
				}
			}
			else
			{// ����ĂȂ��Ƃ�
				g_player.snowBall.nMakeTimerSnow = 0;		// �쐬�J�E���g�[��
				g_player.snowBall.nMakeTimerSnowMidi = 0;	// �쐬�J�E���g�[��
				g_player.snowBall.nMakeTimerSnowBig = 0;	// �쐬�J�E���g�[��
				g_player.snowBall.nMakeTimerIce = 0;		// �쐬�J�E���g�[��
				g_player.snowBall.nMakeTimerIGravel = 0;	// �쐬�J�E���g�[��
			}

			// �R���g���[���[����
			if (GetJoyStickL())
			{// ���X�e�B�b�N
				g_player.charParam.bMove = true;	// ������
				// �ړI�̊p�x���Z�o
				g_player.rotDest.y = pCamera->rot.y + atan2f(pJoypad->Gamepad.sThumbLX, pJoypad->Gamepad.sThumbLY);
			}

			if (KeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_A))
			{// A�W�����v
				if (g_player.charParam.bJanp == false)
				{// �W�����v���ĂȂ�������
					g_player.move.y = g_player.charParam.fJamp;
					g_player.charParam.bJanp = true;	// �W�����v���

					// �W�����v��
					PlaySound(SOUND_LABEL_SE_JUMP);

					// �W�����v��Ԃɕς���
					PlayerStateChangeJump();
				}
			}

			

			if (g_player.charParam.bMove == true)
			{// ������
				g_player.move.x = sinf(g_player.rotDest.y) * PLAYER_MOVE;
				g_player.move.z = cosf(g_player.rotDest.y) * PLAYER_MOVE;

				// �ړ���Ԃɕς���
				PlayerStateChangeMove();
			}

			// �Â��ʒu���X�V
			g_player.posOld.x = g_player.pos.x;
			g_player.posOld.y = g_player.pos.y;
			g_player.posOld.z = g_player.pos.z;

			// �d��
			g_player.move.y -= WORLD_GRAVITY;

			// ����
			g_player.move.x += (0 - g_player.move.x) * 0.3f;
			g_player.move.z += (0 - g_player.move.z) * 0.3f;

			// �ړ���Y�ǉ�
			g_player.pos.y += g_player.move.y;
			if (CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt).nHitfase == BLOCKFACETYPE_TOP)	// �����蔻��
			{
				g_player.charParam.bJanp = false;
			}

			// �ړ���X�ǉ�
			g_player.pos.x += g_player.move.x;
			CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt);	// �����蔻��

			// �ړ���Z�ǉ�
			g_player.pos.z += g_player.move.z;
			CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt);	// �����蔻��

			CollisionWall();	// �ǂ̓����蔻��

			if (g_player.pos.y <= 0.0f)
			{// �n�ʓ˂�����
				g_player.pos.y = 0.0f;
				g_player.move.y = 0.0f;
				g_player.charParam.bJanp = false;	// �W�����v���ĂȂ���
			}

			if (g_player.charParam.bAttack == false)
			{// �U�����ĂȂ��Ƃ�����
				if (KeyboardTrigger(DIK_V) || GetJoypadTrigger(JOYKEY_X))
				{// �e����
					// �����鉹
					PlaySound(SOUND_LABEL_SE_THROWBALL);
					g_player.charParam.bAttack = true;				// �U�����܂�
					g_player.snowBall.nBallType = BULLETTYPE_SNOW;	// ��ʍ��܂�
				}
				else if (KeyboardTrigger(DIK_B) || GetJoypadTrigger(JOYKEY_Y))
				{// �X����
					// �����鉹
					PlaySound(SOUND_LABEL_SE_THROWBALL);
					g_player.charParam.bAttack = true;				// �U�����܂�
					g_player.snowBall.nBallType = BULLETTYPE_ICE;	// �X�ʍ��܂�
				}
				else if (KeyboardTrigger(DIK_N) || GetJoypadTrigger(JOYKEY_B))
				{// ��������
					// �����鉹
					PlaySound(SOUND_LABEL_SE_THROWBALL);
					g_player.charParam.bAttack = true;					// �U�����܂�
					g_player.snowBall.nBallType = BULLETTYPE_GRAVEL;	// �����ʍ��܂�
				}
			}
		}

		// �p�x�̐��K��
		if (g_player.rotDest.y > D3DX_PI)
		{
			g_player.rotDest.y = -D3DX_PI + (g_player.rotDest.y - D3DX_PI);
		}
		else if (g_player.rotDest.y < -D3DX_PI)
		{
			g_player.rotDest.y = D3DX_PI + (g_player.rotDest.y + D3DX_PI);
		}

		// �p�x�̐��K��
		if (g_player.rot.y > D3DX_PI)
		{
			g_player.rot.y = -D3DX_PI + (g_player.rot.y - D3DX_PI);
		}
		else if (g_player.rot.y < -D3DX_PI)
		{
			g_player.rot.y = D3DX_PI + (g_player.rot.y + D3DX_PI);
		}

		// ���f���̊p�x��ړI�̊p�x�ɋ߂Â���
		float fDiff = g_player.rotDest.y - g_player.rot.y;

		if (fDiff > D3DX_PI)
		{
			fDiff = fDiff - D3DX_PI * 2;
		}
		else if (fDiff < -D3DX_PI)
		{
			fDiff = fDiff + D3DX_PI * 2;
		}
		g_player.rot.y += (fDiff) * 0.1f;

		// �e�̍X�V
		SetPositionShadow(g_player.nShadowIdx, g_player.pos);

		// �U�����
		PlayerStateChangeAttack();

		// �v���C���[�̏��
		PlayerStateManegement();

		// ���[�V�����X�V
		UpdateMotion(&g_player.motion, &g_player.aModel[0], g_player.charParam.nState, g_player.charParam.nNumModel);

		for (int nCntPosi = 0; nCntPosi < g_player.charParam.nNumModel; nCntPosi++)
		{
			CollisionPointUpdate(&g_player.aPlayerColiPoint[nCntPosi].pos, g_player.aModel[nCntPosi].mtxWorld);
		}

		// �̗̓Q�[�W�̈ʒu�X�V
		UpdateHPGaugePos(&g_player.HPGaugeHave[HPGAUGETYPE_BG], g_player.pos, 110.0f, 50.0f);
		UpdateHPGaugePos(&g_player.HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], g_player.pos, 110.0f, 50.0f);
		UpdateHPGaugePos(&g_player.HPGaugeHave[HPGAUGETYPE_GAUGE], g_player.pos, 110.0f, 50.0f);

		// �̗͐ԃQ�[�W�̒����X�V
		UpdateHPGaugeRedZoneWidth(&g_player.HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], g_player.charParam.nLife);

		// ��ʃQ�[�W�̈ʒu�X�V
		UpdateHPGaugePos(&g_player.SBGaugeHave[HPGAUGETYPE_BG], g_player.pos, 120.0f, 50.0f);
		UpdateHPGaugePos(&g_player.SBGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], g_player.pos, 120.0f, 50.0f);
		UpdateHPGaugePos(&g_player.SBGaugeHave[HPGAUGETYPE_GAUGE], g_player.pos, 120.0f, 50.0f);
		UpdateHPGaugePos(&g_player.SBMidiGaugeHave, g_player.pos, 120.0f, 50.0f);	// ����
		UpdateHPGaugePos(&g_player.SBBigGaugeHave, g_player.pos, 120.0f, 50.0f);	// ���
		UpdateHPGaugePos(&g_player.SBIceGaugeHave, g_player.pos, 120.0f, 50.0f);	// �X��
		UpdateHPGaugePos(&g_player.SBGraGaugeHave, g_player.pos, 120.0f, 50.0f);	// ������


		UpdateGaugeWidth(&g_player.SBGaugeHave[HPGAUGETYPE_GAUGE], g_player.snowBall.nMakeTimerSnow, true);		// ��ʃQ�[�W
		UpdateGaugeWidth(&g_player.SBMidiGaugeHave, g_player.snowBall.nMakeTimerSnowMidi, true);				// ��ʒ��Q�[�W
		UpdateGaugeWidth(&g_player.SBBigGaugeHave, g_player.snowBall.nMakeTimerSnowBig, true);					// ��ʑ�Q�[�W
		UpdateGaugeWidth(&g_player.SBIceGaugeHave, g_player.snowBall.nMakeTimerIce, true);						// ��ʕX�Q�[�W
		UpdateGaugeWidth(&g_player.SBGraGaugeHave, g_player.snowBall.nMakeTimerIGravel, true);					// ��ʍ����Q�[�W

		// �d���Q�[�W
		UpdateHPGaugePos(&g_player.aSBWateGauge[HPGAUGETYPE_BG], g_player.pos, 125.5f, 50.0f);
		UpdateHPGaugePos(&g_player.aSBWateGauge[HPGAUGETYPE_GAUGE_REDZONE], g_player.pos, 125.5f, 50.0f);
		UpdateHPGaugePos(&g_player.aSBWateGauge[HPGAUGETYPE_GAUGE], g_player.pos, 125.5f, 50.0f);

		// �d���Q�[�W�̒����X�V
		UpdateHPGaugeWidth(&g_player.aSBWateGauge[HPGAUGETYPE_GAUGE], g_player.snowBall.nSnowBallWeight);

		// �d���ԃQ�[�W�̒����X�V
		UpdateHPGaugeRedZoneWidth(&g_player.aSBWateGauge[HPGAUGETYPE_GAUGE_REDZONE], g_player.snowBall.nSnowBallWeight);

	}
	else if (GetMode() == MODE_TITLE)
	{// �^�C�g����������
	// �Â��ʒu���X�V
		g_player.posOld.x = g_player.pos.x;
		g_player.posOld.y = g_player.pos.y;
		g_player.posOld.z = g_player.pos.z;

		// �d��
		g_player.move.y -= WORLD_GRAVITY;

		// �ړ���Y�ǉ�
		g_player.pos.y += g_player.move.y;
		if (CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt).nHitfase == BLOCKFACETYPE_TOP)	// �����蔻��
		{
			g_player.charParam.bJanp = false;
		}

		// �ړ���X�ǉ�
		g_player.pos.x += g_player.move.x;
		CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt);	// �����蔻��

		// �ړ���Z�ǉ�
		g_player.pos.z += g_player.move.z;
		CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt);	// �����蔻��

		// ���[�V�����X�V
		UpdateMotion(&g_player.motion, &g_player.aModel[0], MOTIONTYPE_PLAYER_MAKESNOWBALL, g_player.charParam.nNumModel);
	}
	else if (GetMode() == MODE_RESULT)
	{// �^�C�g����������
	// �Â��ʒu���X�V
		g_player.posOld.x = g_player.pos.x;
		g_player.posOld.y = g_player.pos.y;
		g_player.posOld.z = g_player.pos.z;

		// �d��
		g_player.move.y -= WORLD_GRAVITY;

		// �ړ���Y�ǉ�
		g_player.pos.y += g_player.move.y;
		if (CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt).nHitfase == BLOCKFACETYPE_TOP)	// �����蔻��
		{
			g_player.charParam.bJanp = false;
		}

		// �ړ���X�ǉ�
		g_player.pos.x += g_player.move.x;
		CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt);	// �����蔻��

		// �ړ���Z�ǉ�
		g_player.pos.z += g_player.move.z;
		CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt);	// �����蔻��

		if (GetResult() == RESULTTYPE_GAMECREAR)
		{
			// ���[�V�����X�V
			UpdateMotion(&g_player.motion, &g_player.aModel[0], MOTIONTYPE_PLAYER_WIN, g_player.charParam.nNumModel);
		}
		else if (GetResult() == RESULTTYPE_GAMEOVER)
		{
			// ���[�V�����X�V
			UpdateMotion(&g_player.motion, &g_player.aModel[0], MOTIONTYPE_PLAYER_LOSE, g_player.charParam.nNumModel);
		}
		else if (GetResult() == RESULTTYPE_TIMEOVER)
		{
			// ���[�V�����X�V
			UpdateMotion(&g_player.motion, &g_player.aModel[0], MOTIONTYPE_PLAYER_LOSE, g_player.charParam.nNumModel);
		}
	}
}

//************************************************
// �v���C���[�̕\��
//************************************************
void DrawPlayer(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �S���f��(�p�[�c)�̕`��
	for (int nCntModel = 0; nCntModel < g_player.charParam.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;					// �e�}�g���b�N�X

		// �p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		// �p�[�c�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		// �p�[�c�̈ʒu(�I�t�Z�b�g)�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		// �p�[�c�u�e�̃}�g���b�N�X�v��ݒ�
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{// �e���f��������ꍇ
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;	// �e���f���̃C���f�b�N�X��ݒ�
		}
		else
		{// �e�̃��f�����Ȃ��ꍇ
			mtxParent = g_mtxWorldPlayer;	// �v���C���[�̃}�g���b�N�X��ݒ�
		}

		// �Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
			&g_player.aModel[nCntModel].mtxWorld,
			&mtxParent);

		// �p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD,
			&g_player.aModel[nCntModel].mtxWorld);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			if (g_player.charParam.nState == MOTIONTYPE_PLAYER_DAMAGE)
			{// �_���[�W��Ԃ�������
				D3DXMATERIAL DamageMat = pMat[nCntMat];
				DamageMat.MatD3D.Diffuse.r = 1.0f;
				DamageMat.MatD3D.Diffuse.g = 0.0f;
				DamageMat.MatD3D.Diffuse.b = 0.0f;
				DamageMat.MatD3D.Diffuse.a = 1.0f;

				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&DamageMat.MatD3D);

			}
			else
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			}

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_player.aModel[nCntModel].apTexture[nCntMat]);

			// �p�[�c�̕`��
			g_player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//**************************************************
// �v���C���[�̏�ԊǗ�
//**************************************************
void PlayerStateManegement(void)
{
	switch (g_player.charParam.nState)
	{
	case MOTIONTYPE_PLAYER_NEUTRAL:
		break;

	case MOTIONTYPE_PLAYER_MOVE:
		if (UpdateAttachSmoke(g_player.naSmokeIdx[0], g_player.aPlayerColiPoint[MODELPOSITION_PLAYER_FOOT_L].pos))	// ��
		{// ���o���Ƃ�
			// ����
			PlaySound(SOUND_LABEL_SE_WALKONTHESNOW_L);
		}

		if(UpdateAttachSmoke(g_player.naSmokeIdx[1],g_player.aPlayerColiPoint[MODELPOSITION_PLAYER_FOOT_R].pos))		// ��
		{// ���o���Ƃ�
			// ����
			PlaySound(SOUND_LABEL_SE_WALKONTHESNOW_R);
		}

		if (g_player.charParam.bMove == false)
		{// �����ĂȂ�������
			g_player.charParam.nState = MOTIONTYPE_PLAYER_NEUTRAL;	// �ҋ@��� 
		}
		break;

	case MOTIONTYPE_PLAYER_JUMP:
		if (g_player.charParam.bJanp == false)
		{// �W�����v���ĂȂ�������
			if (g_player.charParam.bMove == false)
			{// �����Ă���
				g_player.charParam.nState = MOTIONTYPE_PLAYER_MOVE;	// ������
			}
			else
			{
				g_player.charParam.nState = MOTIONTYPE_PLAYER_NEUTRAL;	// �ҋ@
			}
		}
		break;

	case MOTIONTYPE_PLAYER_ATTACK:
		g_player.charParam.nCntState++;		// �J�E���g�v���X
		if (g_player.charParam.nCntState >= 45)
		{// �J�E���g����萔�ɂȂ�����
			g_player.charParam.nCntState = 0;	// �J�E���g���Z�b�g
			g_player.charParam.nState = MOTIONTYPE_PLAYER_NEUTRAL;	// �ʏ���
			g_player.charParam.bAttack = false;	// �U�����ĂȂ���
			g_player.snowBall.bSrow = false;
		}
		break;

	case MOTIONTYPE_PLAYER_ATTACK_SUPER:
		g_player.charParam.nCntState++;		// �J�E���g�v���X
		if (g_player.charParam.nCntState >= 120)
		{// �J�E���g����萔�ɂȂ�����
			g_player.charParam.nCntState = 0;	// �J�E���g���Z�b�g
			g_player.charParam.nState = MOTIONTYPE_PLAYER_NEUTRAL;	// �ʏ���
			g_player.charParam.bAttack = false;	// �U�����ĂȂ���
			g_player.snowBall.bSrow = false;
		}
		break;

	case MOTIONTYPE_PLAYER_DAMAGE:
		g_player.charParam.nCntState++;	// �J�E���g�v���X
		if (g_player.charParam.nCntState >= 60)
		{// �J�E���g����萔�ɂȂ�����
			g_player.charParam.nCntState = 0;	// �J�E���g���Z�b�g
			g_player.charParam.nState = MOTIONTYPE_PLAYER_NEUTRAL;	// �ʏ���
		}
		break;

	case MOTIONTYPE_PLAYER_DEATH:
		break;
	}
}

//*********************���*****************************
// �v���C���[�̈ړ�
//**************************************************
void PlayerStateChangeMove(void)
{
	if (g_player.charParam.bMove)
	{
		if (g_player.charParam.nState == MOTIONTYPE_PLAYER_NEUTRAL ||
			g_player.charParam.nState == MOTIONTYPE_PLAYER_RANDING)
		{// ���̏�Ԃ̂Ƃ�
			g_player.charParam.nState = MOTIONTYPE_PLAYER_MOVE;	// �ړ����
		}
	}
}

//**************************************************
// �v���C���[�̃W�����v���
//**************************************************
void PlayerStateChangeJump(void)
{
	if (g_player.charParam.nState == MOTIONTYPE_PLAYER_NEUTRAL ||
		g_player.charParam.nState == MOTIONTYPE_PLAYER_RANDING || 
		g_player.charParam.nState == MOTIONTYPE_PLAYER_MOVE)
	{// ���̏�Ԃ̂Ƃ�
		g_player.charParam.nState = MOTIONTYPE_PLAYER_JUMP;	// �W�����v���
	}
}

//**************************************************
// �v���C���[�̍U�����
//**************************************************
void PlayerStateChangeAttack(void)
{
	if (g_player.charParam.bAttack)
	{
		if (g_player.charParam.nState == MOTIONTYPE_PLAYER_NEUTRAL ||
			g_player.charParam.nState == MOTIONTYPE_PLAYER_RANDING ||
			g_player.charParam.nState == MOTIONTYPE_PLAYER_MOVE ||
			g_player.charParam.nState == MOTIONTYPE_PLAYER_JUMP)
		{// ���̏�Ԃ̂Ƃ�
			g_player.charParam.nState = MOTIONTYPE_PLAYER_ATTACK;	// �U�����
			g_player.charParam.nCntOcc = 20;		// �����J�E���^�[�[��
			g_player.charParam.nCntDura = 0;	// �����J�E���^�[�[��
		}

		if (g_player.charParam.nState == MOTIONTYPE_PLAYER_ATTACK ||
			g_player.charParam.nState == MOTIONTYPE_PLAYER_ATTACK_SUPER)
		{// �U����ԂȂ�
			g_player.charParam.nCntOcc--;	// �����J�E���^�[�ǉ�

			if (g_player.charParam.nCntOcc <= 0 && g_player.snowBall.bSrow == false)
			{
				int nBulletType;	// �Ԃ��ꂽ��ʂ̏��

				switch (g_player.snowBall.nBallType)
				{
				case BULLETTYPE_SNOW:	// ���
					nBulletType = BreakOrderSnowBall(&g_player.snowBall, BULLETTYPE_SNOW);	// ��ʍ��܂����H

					if (nBulletType == BULLETTYPE_SNOW_BIG)
					{
						g_player.charParam.nState = MOTIONTYPE_PLAYER_ATTACK_SUPER;
						g_player.snowBall.nBallType = BULLETTYPE_SNOW_BIG;
					}
					else
					{
						EndSBUI(&g_player.snowBall, nBulletType);			// UI����
						SetBullet(g_player.aPlayerColiPoint[MODELPOSITION_PLAYER_HAND_R].pos, g_player.rotDest, nBulletType);	// �e�ݒ�
						g_player.snowBall.bSrow = true;
					}

					break;

				case BULLETTYPE_SNOW_BIG:	// ���
					if (g_player.charParam.nCntOcc == -50 && g_player.charParam.nState == MOTIONTYPE_PLAYER_ATTACK_SUPER)
					{

						EndSBUI(&g_player.snowBall, BULLETTYPE_SNOW_BIG);			// UI����
						SetBullet(g_player.aPlayerColiPoint[MODELPOSITION_PLAYER_HAND_R].pos, g_player.rotDest, BULLETTYPE_SNOW_BIG);	// �e�ݒ�
						g_player.snowBall.bSrow = true;
					}
					break;

				case BULLETTYPE_ICE:	// �X
					nBulletType = BreakOrderSnowBall(&g_player.snowBall, BULLETTYPE_ICE);	// ��ʍ��܂����H
					EndSBUI(&g_player.snowBall, nBulletType);			// UI����
					SetBullet(g_player.aPlayerColiPoint[MODELPOSITION_PLAYER_HAND_R].pos, g_player.rotDest, nBulletType);	// �e�ݒ�
					g_player.snowBall.bSrow = true;
					break;

				case BULLETTYPE_GRAVEL:	// ������
					nBulletType = BreakOrderSnowBall(&g_player.snowBall, BULLETTYPE_GRAVEL);	// ��ʍ��܂����H
					EndSBUI(&g_player.snowBall, nBulletType);			// UI����
					SetBullet(g_player.aPlayerColiPoint[MODELPOSITION_PLAYER_HAND_R].pos, g_player.rotDest, nBulletType);	// �e�ݒ�
					g_player.snowBall.bSrow = true;
					break;

				default:
					break;
				}
			}
		}
	}
}

//**************************************************
// �v���C���[�̃_���[�W����
//**************************************************
void HitPlayer(int nDamage)
{
	if (g_player.charParam.nState == MOTIONTYPE_PLAYER_NEUTRAL ||
		g_player.charParam.nState == MOTIONTYPE_PLAYER_RANDING ||
		g_player.charParam.nState == MOTIONTYPE_PLAYER_MOVE ||
		g_player.charParam.nState == MOTIONTYPE_PLAYER_JUMP ||
		g_player.charParam.nState == MOTIONTYPE_PLAYER_ATTACK)
	{// ���̏�Ԃ̂Ƃ���

		g_player.charParam.nLife -= nDamage;	// �_���[�W�ǉ�
		g_player.charParam.nState = MOTIONTYPE_PLAYER_DAMAGE;	// �_���[�W���
		g_player.charParam.nCntState = 0;	// �J�E���^�[�[��

		// �̗̓Q�[�W�̒����X�V
		UpdateHPGaugeWidth(&g_player.HPGaugeHave[1], g_player.charParam.nLife);

		// �_���[�W��
		PlaySound(SOUND_LABEL_SE_HIT_PLAYER);
	}

	if (g_player.charParam.nLife <= 0)
	{// �̗͂Ȃ��Ȃ�����
		g_player.charParam.nState = MOTIONTYPE_PLAYER_DEATH;	// ����

		//�t�F�[�h�A�E�g����
		SetFade(MODE_RESULT);
		SetResult(RESULTTYPE_GAMEOVER);

		// �e�I��
		EndShadow(g_player.nShadowIdx);

		// HP�Q�[�W�I���
		EndHPGauge(&g_player.HPGaugeHave[HPGAUGETYPE_BG]);
		EndHPGauge(&g_player.HPGaugeHave[HPGAUGETYPE_GAUGE]);
		EndHPGauge(&g_player.HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE]);
	}
}

//************************************************
// �v���C���[�̎擾
//************************************************
PLAYER* GetPlayer(void)
{
	return &g_player;
}