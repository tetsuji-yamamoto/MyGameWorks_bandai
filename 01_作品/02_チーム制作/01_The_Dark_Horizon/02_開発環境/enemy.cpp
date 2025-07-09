#include "enemy.h"
#include "block.h"
#include "result.h"
#include "fade.h"
#include "collision.h"
#include "player.h"
#include "edit.h"
#include "effect.h"
#include "smoke.h"
#include "sound.h"

// �O���[�o���ϐ��錾
ENEMY g_aEnemy[MAX_ENEMY];							// �G�l�~�[���
ENEMY g_aEnemy_EX[ENEMYTYPE_MAX];					// �G�l�~�[�̎�ނ��Ƃ̏��
MODELCOLER g_aModelCol[ENEMYTYPE_MAX][10][6];		// �֗��ȕۑ��ꏊ
ENEMY_MANAGER g_EnemyMane;							// �G�l�~�[�Ǘ�

//**************************************************
// �G�l�~�[�̏�����
//**************************************************
void InitEnemy(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_EnemyMane.nNumEnemy = 0;	// �G�l�~�[�̑���

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		// �e��ϐ��̏�����
		g_aEnemy[nCnt].pos = D3DXVECTOR3(100.0f, 40.0f, 0.0f);	// �ʒu
		g_aEnemy[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
		g_aEnemy[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
		g_aEnemy[nCnt].bUse = false;							// �g���Ă܂���
		g_aEnemy[nCnt].nShadowIdx = 0;							// �e�̃C���f�b�N�X
		g_aEnemy[nCnt].naSmokeIdx[0] = -1;						// ���̃C���f�b�N�X
		g_aEnemy[nCnt].naSmokeIdx[1] = -1;						// ���̃C���f�b�N�X

		g_aEnemy[nCnt].charParam.nNumModel = 0;							// �p�[�c�̑���
		g_aEnemy[nCnt].charParam.fWidth = 0.0f;							// ��
		g_aEnemy[nCnt].charParam.fHeigt = 0.0f;							// ����
		g_aEnemy[nCnt].charParam.fJamp = 2.0f;							// �W�����v��
		g_aEnemy[nCnt].charParam.nLife = 10;							// �̗�
		g_aEnemy[nCnt].charParam.nState = MOTIONTYPE_ENEMY_NEUTRAL;		// ���
		g_aEnemy[nCnt].charParam.nCntState = 0;							// ��ԊǗ��J�E���^�[
		g_aEnemy[nCnt].charParam.nCntOcc = 0;							// �����Ǘ��J�E���^�[

		g_aEnemy[nCnt].motion.bLoopMotion = true;
		g_aEnemy[nCnt].motion.nNumKey = 2;
		g_aEnemy[nCnt].motion.nKey = 0;
		g_aEnemy[nCnt].motion.nCounterMotion = 0;
		g_aEnemy[nCnt].motion.nNextKey = g_aEnemy[nCnt].motion.nKey + 1;
		g_aEnemy[nCnt].motion.nNowMotiType = -1;

		g_aEnemy[nCnt].myTerrtry.fRadius = 300.0f;
		g_aEnemy[nCnt].myTerrtry.nTimer = 0;
		g_aEnemy[nCnt].myTerrtry.nPatrolTimer = 0;						// ����^�C�}�[�[��
		g_aEnemy[nCnt].myTerrtry.nPatrolRimit = 0;						// ����[�����E�J�E���^�[
		g_aEnemy[nCnt].myTerrtry.nAngerTimer = 0;						// �{��J�E���^�[

	}

	for (int nCntEX = 0; nCntEX < ENEMYTYPE_MAX; nCntEX++)
	{
		switch (nCntEX)
		{
		case ENEMYTYPE_NOMAL:
			// ���[�V�����e�L�X�g�ǂݍ���
			ReadMotionText("date\\motion\\yukiotoko\\motion.txt", &g_aEnemy_EX[nCntEX].aModel[0], &g_aEnemy_EX[nCntEX].motion, &g_aEnemy_EX[nCntEX].charParam);
			break;

		case ENEMYTYPE_REMOATE:
			// ���[�V�����e�L�X�g�ǂݍ���
			ReadMotionText("date\\motion\\yukiotoko\\motion.txt", &g_aEnemy_EX[nCntEX].aModel[0], &g_aEnemy_EX[nCntEX].motion, &g_aEnemy_EX[nCntEX].charParam);
			break;

		default:
			// ���[�V�����e�L�X�g�ǂݍ���
			ReadMotionText("date\\motion\\yukiotoko\\motion.txt", &g_aEnemy_EX[nCntEX].aModel[0], &g_aEnemy_EX[nCntEX].motion, &g_aEnemy_EX[nCntEX].charParam);
			break;
		}

		for (int nCntPosi = 0; nCntPosi < g_aEnemy_EX[nCntEX].charParam.nNumModel; nCntPosi++)
		{
			g_aEnemy_EX[nCntEX].aColiPoint[nCntPosi].pos = g_aEnemy_EX[nCntEX].aModel[nCntPosi].pos;
			g_aEnemy_EX[nCntEX].aColiPoint[nCntPosi].fRadius = 10.0f;
		}

		for (int nCntModel = 0; nCntModel < g_aEnemy_EX[nCntEX].charParam.nNumModel; nCntModel++)
		{
			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_aEnemy_EX[nCntEX].aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aEnemy_EX[nCntEX].aModel[nCntModel].dwNumMat; nCntMat++)
			{
				g_aModelCol[nCntEX][nCntModel][nCntMat].fR = pMat[nCntMat].MatD3D.Diffuse.r;
				g_aModelCol[nCntEX][nCntModel][nCntMat].fG = pMat[nCntMat].MatD3D.Diffuse.g;
				g_aModelCol[nCntEX][nCntModel][nCntMat].fB = pMat[nCntMat].MatD3D.Diffuse.b;
				g_aModelCol[nCntEX][nCntModel][nCntMat].fA = pMat[nCntMat].MatD3D.Diffuse.a;

			}
		}
	}

	if (GetMode() == MODE_GAME)
	{
		BLOCK block = BlockSearch(BLOCKTYPE_TERRITRY_POINT, 0);	// �ق����u���b�N�Q�b�g��
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			block.pos.x += 40.0f * nCnt;
			block.pos.z += 40.0f * nCnt;
			SetEnemy(block.pos, ENEMYTYPE_NOMAL);
		}

		block = BlockSearch(BLOCKTYPE_TERRITRY_POINT, 1);	// �ق����u���b�N�Q�b�g��
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			block.pos.x += 40.0f * nCnt;
			block.pos.z += 40.0f * nCnt;
			SetEnemy(block.pos, ENEMYTYPE_NOMAL);
		}

		block = BlockSearch(BLOCKTYPE_TERRITRY_POINT, 2);	// �ق����u���b�N�Q�b�g��
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			block.pos.x += 40.0f * nCnt;
			block.pos.z += 40.0f * nCnt;
			SetEnemy(block.pos, ENEMYTYPE_NOMAL);
		}

		block = BlockSearch(BLOCKTYPE_TERRITRY_POINT, 3);	// �ق����u���b�N�Q�b�g��
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			block.pos.x += 40.0f * nCnt;
			block.pos.z += 40.0f * nCnt;
			SetEnemy(block.pos, ENEMYTYPE_NOMAL);
		}
	}
	else if (GetMode() == MODE_TUTORIAL)
	{
		BLOCK block = BlockSearch(BLOCKTYPE_TERRITRY_POINT, 0);	// �ق����u���b�N�Q�b�g��
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			block.pos.x += 40.0f * nCnt;
			block.pos.y += 40.0f;
			block.pos.z += 40.0f * nCnt;
			SetEnemy(block.pos, ENEMYTYPE_NOMAL);
		}

		block = BlockSearch(BLOCKTYPE_TERRITRY_POINT, 1);	// �ق����u���b�N�Q�b�g��
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			block.pos.x += 40.0f * nCnt;
			block.pos.y += 40.0f;
			block.pos.z += 40.0f * nCnt;
			SetEnemy(block.pos, ENEMYTYPE_NOMAL);
		}

		block = BlockSearch(BLOCKTYPE_TERRITRY_POINT, 2);	// �ق����u���b�N�Q�b�g��
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			block.pos.x += 40.0f * nCnt;
			block.pos.y += 40.0f;
			block.pos.z += 40.0f * nCnt;
			SetEnemy(block.pos, ENEMYTYPE_NOMAL);
		}
	}
}

//**************************************************
// �G�l�~�[�̏I��
//**************************************************
void UninitEnemy(void)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		// ���b�V���̔j��
		if (g_aEnemy[nCnt].pMeshEnemy != NULL)
		{
			g_aEnemy[nCnt].pMeshEnemy->Release();
			g_aEnemy[nCnt].pMeshEnemy = NULL;
		}

		// �}�e���A���̔j��
		if (g_aEnemy[nCnt].pBuffMatEnemy != NULL)
		{
			g_aEnemy[nCnt].pBuffMatEnemy->Release();
			g_aEnemy[nCnt].pBuffMatEnemy = NULL;
		}

		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			// �e�N�X�`���̔j��
			if (g_aEnemy[nCnt].apTextureEnemy[nCnt] != NULL)
			{
				g_aEnemy[nCnt].apTextureEnemy[nCnt]->Release();
				g_aEnemy[nCnt].apTextureEnemy[nCnt] = NULL;
			}
		}
	}

	for (int nCnt = 0; nCnt < ENEMYTYPE_MAX; nCnt++)
	{
		// ���b�V���̔j��
		if (g_aEnemy_EX[nCnt].pMeshEnemy != NULL)
		{
			g_aEnemy_EX[nCnt].pMeshEnemy->Release();
			g_aEnemy_EX[nCnt].pMeshEnemy = NULL;
		}

		// �}�e���A���̔j��
		if (g_aEnemy_EX[nCnt].pBuffMatEnemy != NULL)
		{
			g_aEnemy_EX[nCnt].pBuffMatEnemy->Release();
			g_aEnemy_EX[nCnt].pBuffMatEnemy = NULL;
		}

		for (int nCntTex = 0; nCntTex < 6; nCntTex++)
		{
			// �e�N�X�`���̔j��
			if (g_aEnemy_EX[nCnt].apTextureEnemy[nCntTex] != NULL)
			{
				g_aEnemy_EX[nCnt].apTextureEnemy[nCntTex]->Release();
				g_aEnemy_EX[nCnt].apTextureEnemy[nCntTex] = NULL;
			}
		}
	}
}

//**************************************************
// �G�l�~�[�̍X�V
//**************************************************
void UpdateEnemy(void)
{
	PLAYER* pPlayer = GetPlayer();	// �v���C���[���Q�b�g

#ifdef _DEBUG
	if (GetEditMode() == EDITMODE_BLOCK)
	{
		return;
	}

#endif

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_aEnemy[nCnt].bUse)
		{
			g_aEnemy[nCnt].posOld = g_aEnemy[nCnt].pos;

			// �d��
			g_aEnemy[nCnt].move.y -= 1.0f;

			g_aEnemy[nCnt].move.x += (0 - g_aEnemy[nCnt].move.x) * 0.1f;
			g_aEnemy[nCnt].move.z += (0 - g_aEnemy[nCnt].move.z) * 0.1f;

			CollisionEnemy(nCnt);
			int nType;

			g_aEnemy[nCnt].pos.y += g_aEnemy[nCnt].move.y;
			// �u���b�N�ւ̓����蔻��
			g_aEnemy[nCnt].blockCollision = CollisionBlockCharacter(&g_aEnemy[nCnt].pos, &g_aEnemy[nCnt].posOld, &g_aEnemy[nCnt].move, &nType, g_aEnemy[nCnt].charParam.fWidth, g_aEnemy[nCnt].charParam.fHeigt);

			g_aEnemy[nCnt].pos.x += g_aEnemy[nCnt].move.x;
			// �u���b�N�ւ̓����蔻��
			g_aEnemy[nCnt].blockCollision = CollisionBlockCharacter(&g_aEnemy[nCnt].pos, &g_aEnemy[nCnt].posOld, &g_aEnemy[nCnt].move, &nType, g_aEnemy[nCnt].charParam.fWidth, g_aEnemy[nCnt].charParam.fHeigt);

			g_aEnemy[nCnt].pos.z += g_aEnemy[nCnt].move.z;
			// �u���b�N�ւ̓����蔻��
			g_aEnemy[nCnt].blockCollision = CollisionBlockCharacter(&g_aEnemy[nCnt].pos, &g_aEnemy[nCnt].posOld, &g_aEnemy[nCnt].move, &nType, g_aEnemy[nCnt].charParam.fWidth, g_aEnemy[nCnt].charParam.fHeigt);


			if (g_aEnemy[nCnt].pos.y <= 0.0f)
			{// ���E�̃[��
				g_aEnemy[nCnt].bUse = false;
			}

			if (TerritryConfirmation(g_aEnemy[nCnt].myTerrtry, g_aEnemy[nCnt].pos) == true)
			{// ���g���e���g���[�O
				g_aEnemy[nCnt].myTerrtry.nTimer = 0;
				GoHomeEnemy(nCnt);	// �A��
			}

			
				if (TerritryConfirmation(g_aEnemy[nCnt].myTerrtry, pPlayer->pos) == true)
				{// �܂��̓v���C���[���e���g���[�ɂ��Ȃ�
					GoHomeEnemy(nCnt);	// �A��
				}

				if (TerritryConfirmation(g_aEnemy[nCnt].myTerrtry, pPlayer->pos) == false ||
					CollisionSphere(&g_aEnemy[nCnt].pos, &pPlayer->pos, 200.0f, 0.0f, false) ||
					g_aEnemy[nCnt].myTerrtry.nAngerTimer > 0)
				{// �v���C���[���e���g���[�ɂ���,�v���C���[���߂��ɂ���
					// �^�C�}�[������
					g_aEnemy[nCnt].myTerrtry.nTimer = 0;	// �^�C�}�[�[��
					g_aEnemy[nCnt].myTerrtry.nAngerTimer--;	// �{��J�E���^�[�}�C�i�X

					// �ҋ@
					NeutralEnemy(nCnt);
					if (GetMode() == MODE_GAME)
					{
						// �ǂ�����
						ChaseEnemy(nCnt);

						// �U��
						AttackEnemy(nCnt);
					}
				}

			// ��ԊǗ�
			EnemyStateManegement(nCnt);

			// ���[�V�����X�V
			UpdateMotion(&g_aEnemy[nCnt].motion, &g_aEnemy[nCnt].aModel[0], g_aEnemy[nCnt].charParam.nState, g_aEnemy[nCnt].charParam.nNumModel);

			for (int nCntPosi = 0; nCntPosi < g_aEnemy[nCnt].charParam.nNumModel; nCntPosi++)
			{
				CollisionPointUpdate(&g_aEnemy[nCnt].aColiPoint[nCntPosi].pos, g_aEnemy[nCnt].aModel[nCntPosi].mtxWorld);
			}

			// �̗̓Q�[�W�̈ʒu�X�V
			UpdateHPGaugePos(&g_aEnemy[nCnt].HPGaugeHave[HPGAUGETYPE_BG], g_aEnemy[nCnt].pos, 110.0f, 50.0f);
			UpdateHPGaugePos(&g_aEnemy[nCnt].HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], g_aEnemy[nCnt].pos, 110.0f, 50.0f);
			UpdateHPGaugePos(&g_aEnemy[nCnt].HPGaugeHave[HPGAUGETYPE_GAUGE], g_aEnemy[nCnt].pos, 110.0f, 50.0f);

			// �̗͐ԃQ�[�W�̒����X�V
			UpdateHPGaugeRedZoneWidth(&g_aEnemy[nCnt].HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], g_aEnemy[nCnt].charParam.nLife);

			// �e�̍X�V
			SetPositionShadow(g_aEnemy[nCnt].nShadowIdx, g_aEnemy[nCnt].pos);
		}
	}
}

//**************************************************
// �G�l�~�[�̕`��
//**************************************************
void DrawEnemy(void)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_aEnemy[nCnt].bUse)
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
			D3DXMatrixIdentity(&g_aEnemy[nCnt].mtxWorldEnemy);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCnt].rot.y, g_aEnemy[nCnt].rot.x, g_aEnemy[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCnt].mtxWorldEnemy, &g_aEnemy[nCnt].mtxWorldEnemy, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCnt].pos.x, g_aEnemy[nCnt].pos.y, g_aEnemy[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCnt].mtxWorldEnemy, &g_aEnemy[nCnt].mtxWorldEnemy, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCnt].mtxWorldEnemy);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �S���f��(�p�[�c)�̕`��
			for (int nCntModel = 0; nCntModel < g_aEnemy[nCnt].charParam.nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p�}�g���b�N�X
				D3DXMATRIX mtxParent;					// �e�}�g���b�N�X

				// �p�[�c�̃��[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld);

				// �p�[�c�̌����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy[nCnt].aModel[nCntModel].rot.y, g_aEnemy[nCnt].aModel[nCntModel].rot.x, g_aEnemy[nCnt].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld, &g_aEnemy[nCnt].aModel[nCntModel].mtxWorld, &mtxRotModel);

				// �p�[�c�̈ʒu(�I�t�Z�b�g)�𔽉f
				D3DXMatrixTranslation(&mtxTransModel, g_aEnemy[nCnt].aModel[nCntModel].pos.x, g_aEnemy[nCnt].aModel[nCntModel].pos.y, g_aEnemy[nCnt].aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld, &g_aEnemy[nCnt].aModel[nCntModel].mtxWorld, &mtxTransModel);

				// �p�[�c�u�e�̃}�g���b�N�X�v��ݒ�
				if (g_aEnemy[nCnt].aModel[nCntModel].nIdxModelParent != -1)
				{// �e���f��������ꍇ
					mtxParent = g_aEnemy[nCnt].aModel[g_aEnemy[nCnt].aModel[nCntModel].nIdxModelParent].mtxWorld;	// �e���f���̃C���f�b�N�X��ݒ�
				}
				else
				{// �e�̃��f�����Ȃ��ꍇ
					mtxParent = g_aEnemy[nCnt].mtxWorldEnemy;	// �v���C���[�̃}�g���b�N�X��ݒ�
				}

				// �Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�}�g���b�N�X���������킹��
				D3DXMatrixMultiply(&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld,
					&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld,
					&mtxParent);

				// �p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD,
					&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_aEnemy[nCnt].aModel[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCnt].aModel[nCntModel].dwNumMat; nCntMat++)
				{
					if (g_aEnemy[nCnt].charParam.nState == MOTIONTYPE_ENEMY_DAMAGE)
					{
						D3DXMATERIAL damageMat = pMat[nCntMat];
						damageMat.MatD3D.Diffuse.r = 1.0f;
						damageMat.MatD3D.Diffuse.g = 0.0f;
						damageMat.MatD3D.Diffuse.b = 0.0f;
						damageMat.MatD3D.Diffuse.a = 1.0f;

						// �}�e���A���̐ݒ�
						pDevice->SetMaterial(&damageMat.MatD3D);
					}
					else
					{
						// �}�e���A���̐ݒ�
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					}

					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_aEnemy[nCnt].aModel[nCntModel].apTexture[nCntMat]);

					// �p�[�c�̕`��
					g_aEnemy[nCnt].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}
			}

			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//**************************************************
// �G�l�~�[�̐ݒ�
//**************************************************
void SetEnemy(D3DXVECTOR3 pos,ENEMYTYPE type)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_aEnemy[nCnt].bUse == false)
		{
			g_aEnemy[nCnt].bUse = true;
			g_aEnemy[nCnt].pos = pos;
			g_aEnemy[nCnt].myTerrtry.pos = pos;


			// �G�̎�ނ��Ƃɐݒ肵�Ă���
			switch (type)
			{
			case ENEMYTYPE_NOMAL:	// �ʏ�̓G
				for (int nCntModel = 0; nCntModel < (int)g_aEnemy_EX[ENEMYTYPE_NOMAL].charParam.nNumModel; nCntModel++)
				{
					g_aEnemy[nCnt].aModel[nCntModel] = g_aEnemy_EX[ENEMYTYPE_NOMAL].aModel[nCntModel];	// ���f������
					g_aEnemy[nCnt].aColiPoint[nCntModel] = g_aEnemy_EX[type].aColiPoint[nCntModel];
				}

				for (int nCntTex = 0; nCntTex < 6; nCntTex++)
				{
					g_aEnemy[nCnt].apTextureEnemy[nCntTex] = g_aEnemy_EX[ENEMYTYPE_NOMAL].apTextureEnemy[nCntTex];
				}
				
				g_aEnemy[nCnt].pMeshEnemy = g_aEnemy_EX[ENEMYTYPE_NOMAL].pMeshEnemy;
				g_aEnemy[nCnt].pBuffMatEnemy = g_aEnemy_EX[ENEMYTYPE_NOMAL].pBuffMatEnemy;
				g_aEnemy[nCnt].mtxWorldEnemy = g_aEnemy_EX[ENEMYTYPE_NOMAL].mtxWorldEnemy;

				g_aEnemy[nCnt].motion = g_aEnemy_EX[ENEMYTYPE_NOMAL].motion;		// ���[�V��������

				g_aEnemy[nCnt].charParam.nNumModel = g_aEnemy_EX[ENEMYTYPE_NOMAL].charParam.nNumModel;	// �p�[�c�̑���
				g_aEnemy[nCnt].charParam.fWidth = g_aEnemy_EX[ENEMYTYPE_NOMAL].charParam.fWidth;		// ��
				g_aEnemy[nCnt].charParam.fHeigt = g_aEnemy_EX[ENEMYTYPE_NOMAL].charParam.fHeigt;		// ����
				g_aEnemy[nCnt].charParam.fJamp = 2.0f;							// �W�����v��
				g_aEnemy[nCnt].charParam.nLife = 10;							// �̗�
				g_aEnemy[nCnt].charParam.nState = MOTIONTYPE_ENEMY_NEUTRAL;		// ���
				g_aEnemy[nCnt].charParam.nCntState = 0;							// ��ԊǗ��J�E���^�[
				g_aEnemy[nCnt].charParam.nCntOcc = 0;							// �����Ǘ��J�E���^�[

				g_aEnemy[nCnt].motion.nNowMotiType =  -1;
				break;

			case ENEMYTYPE_REMOATE:	// ���u�̓G
				break;

				
			}

			// �G�̑����ǉ�
			g_EnemyMane.nNumEnemy++;

			if (GetMode() == MODE_GAME || GetMode() == MODE_TUTORIAL)
			{
				// HP�Q�[�W�̐ݒ�
				SetHPGauge(&g_aEnemy[nCnt].HPGaugeHave[HPGAUGETYPE_BG], HPGAUGETYPE_BG, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f), 5.0f, 100.0f, g_aEnemy[nCnt].charParam.nLife);
				SetHPGauge(&g_aEnemy[nCnt].HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], HPGAUGETYPE_GAUGE_REDZONE, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5.0f, 100.0f, g_aEnemy[nCnt].charParam.nLife);
				SetHPGauge(&g_aEnemy[nCnt].HPGaugeHave[HPGAUGETYPE_GAUGE], HPGAUGETYPE_GAUGE, D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), 5.0f, 100.0f, g_aEnemy[nCnt].charParam.nLife);
			}
			// ����
			g_aEnemy[nCnt].naSmokeIdx[0] = SetSmoke(SMOKETYPE_ATTACH, g_aEnemy[nCnt].pos, 20, 20.0f, true);
			g_aEnemy[nCnt].naSmokeIdx[1] = SetSmoke(SMOKETYPE_ATTACH, g_aEnemy[nCnt].pos, 40, 20.0f, true);

			// �e��ݒ�
			g_aEnemy[nCnt].nShadowIdx = SetShadw(g_aEnemy[nCnt].pos, g_aEnemy[nCnt].rot, g_aEnemy[nCnt].charParam.fWidth);

			break;
		}
	}
}

//**************************************************
// �G�l�~�[�ҋ@
//**************************************************
void NeutralEnemy(int nCntEnemy)
{
	PLAYER* pPlayer = GetPlayer();	// �v���C���[�擾

	if (pPlayer->charParam.bDisp == false)
	{
		g_aEnemy[nCntEnemy].charParam.nState = MOTIONTYPE_ENEMY_NEUTRAL;
	}
}

//**************************************************
// �G�l�~�[�ǂ�����
//**************************************************
void ChaseEnemy(int nCntEnemy)
{
	PLAYER* pPlayer = GetPlayer();	// �v���C���[�擾

	if (pPlayer->charParam.bDisp)
	{// �v���C���[��������
		g_aEnemy[nCntEnemy].charParam.bMove = true;	// ������

		if (g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_NEUTRAL ||
			g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_MOVE)
		{// ���̏�Ԃ̂Ƃ�
			// �G�l�~�[�ړ����
			EnemyStateChangeMove(nCntEnemy);

			D3DXVECTOR3 vecA = pPlayer->pos - g_aEnemy[nCntEnemy].pos;

			// ���K��
			D3DXVec3Normalize(&vecA, &vecA);

			g_aEnemy[nCntEnemy].move.x = ENEMY_MOVE_SPEED_CHASE * vecA.x;
			g_aEnemy[nCntEnemy].move.y = 0.0f;
			g_aEnemy[nCntEnemy].move.z = ENEMY_MOVE_SPEED_CHASE * vecA.z;

			g_aEnemy[nCntEnemy].rot.y = atan2f(vecA.x, vecA.z);

			
		}
	}
}

//**************************************************
// �G�l�~�[�ǂ����̓����蔻��
//**************************************************
void CollisionEnemy(int nCntEnemy)
{
	PLAYER* pPlayer = GetPlayer();	// �v���C���[�擾

	CollisionSphere(&g_aEnemy[nCntEnemy].pos, &pPlayer->pos, g_aEnemy[nCntEnemy].charParam.fWidth, pPlayer->charParam.fWidth, true);

	for (int nCnt = 0;nCnt < MAX_ENEMY;nCnt++)
	{
		if (g_aEnemy[nCnt].bUse)
		{
			if (nCnt != nCntEnemy)
			{
				if (CollisionSphere(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCnt].pos, g_aEnemy[nCntEnemy].charParam.fWidth, g_aEnemy[nCnt].charParam.fWidth, true))
				{
					g_aEnemy[nCntEnemy].move.y += -1.0f;
				}
			}
		}
	}

}

//**************************************************
// �G�l�~�[�̓������Ƃ�
//**************************************************
void HitEnemy(int nCntEnemy, int nDamage)
{
	if (g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_DAMAGE)
	{
		return;
	}

	// �G�q�b�g��
	PlaySound(SOUND_LABEL_SE_HIT_ENEMY);

	g_aEnemy[nCntEnemy].charParam.nLife -= nDamage;
	g_aEnemy[nCntEnemy].charParam.nState = MOTIONTYPE_ENEMY_DAMAGE;

	// �̗̓Q�[�W�̒����X�V
	UpdateHPGaugeWidth(&g_aEnemy[nCntEnemy].HPGaugeHave[HPGAUGETYPE_GAUGE], g_aEnemy[nCntEnemy].charParam.nLife);

	// �{��^�C�}�[�ݒ�
	g_aEnemy[nCntEnemy].myTerrtry.nAngerTimer = rand() % 360 + 360;

	if (g_aEnemy[nCntEnemy].charParam.nLife <= 0)
	{// �̗͂Ȃ��Ȃ�����
		g_aEnemy[nCntEnemy].bUse = false;

		// �G�̑�������
		g_EnemyMane.nNumEnemy--;

		// HP�Q�[�W�I���
		EndHPGauge(&g_aEnemy[nCntEnemy].HPGaugeHave[HPGAUGETYPE_BG]);
		EndHPGauge(&g_aEnemy[nCntEnemy].HPGaugeHave[HPGAUGETYPE_GAUGE]);
		EndHPGauge(&g_aEnemy[nCntEnemy].HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE]);


		// �e�I��
		EndShadow(g_aEnemy[nCntEnemy].nShadowIdx);

		if (g_EnemyMane.nNumEnemy <= 0 && GetMode() == MODE_GAME)
		{
			//�t�F�[�h�A�E�g����
			SetFade(MODE_RESULT);
			SetResult(RESULTTYPE_GAMECREAR);
		}
	}
}

//**************************************************
// �G�l�~�[�̏�ԊǗ�
//**************************************************
void EnemyStateManegement(int nCnt)
{
	switch (g_aEnemy[nCnt].charParam.nState)
	{
	case MOTIONTYPE_ENEMY_NEUTRAL:
		break;

	case MOTIONTYPE_ENEMY_MOVE:
		UpdateAttachSmoke(g_aEnemy[nCnt].naSmokeIdx[0], g_aEnemy[nCnt].aColiPoint[MODELPOSITION_PLAYER_FOOT_L].pos);		// ��
		UpdateAttachSmoke(g_aEnemy[nCnt].naSmokeIdx[1], g_aEnemy[nCnt].aColiPoint[MODELPOSITION_PLAYER_FOOT_R].pos);		// ��
		break;

	case MOTIONTYPE_ENEMY_ATTACK:
		g_aEnemy[nCnt].charParam.nCntState++;	// �J�E���g�v���X

		if (g_aEnemy[nCnt].charParam.nCntState >= 90)
		{// �J�E���g����萔�ɂȂ�����
			g_aEnemy[nCnt].charParam.nCntState = 0;	// �J�E���g���Z�b�g
			g_aEnemy[nCnt].charParam.nState = MOTIONTYPE_ENEMY_NEUTRAL;	// �ʏ���
		}
		break;

	case MOTIONTYPE_ENEMY_DAMAGE:
		g_aEnemy[nCnt].charParam.nCntState++;	// �J�E���g�v���X
		if (g_aEnemy[nCnt].charParam.nCntState >= 30)
		{// �J�E���g����萔�ɂȂ�����
			g_aEnemy[nCnt].charParam.nCntState = 0;	// �J�E���g���Z�b�g
			g_aEnemy[nCnt].charParam.nState = MOTIONTYPE_ENEMY_NEUTRAL;	// �ʏ���
		}
		break;

	case MOTIONTYPE_ENEMY_DAETH:
		break;
	}
}

//**************************************************
// �G�l�~�[�̈ړ����
//**************************************************
void EnemyStateChangeMove(int nCntEnemy)
{
	if (g_aEnemy[nCntEnemy].charParam.bMove)
	{
		if (g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_PLAYER_NEUTRAL ||
			g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_PLAYER_RANDING)
		{// ���̏�Ԃ̂Ƃ�
			g_aEnemy[nCntEnemy].charParam.nState = MOTIONTYPE_PLAYER_MOVE;	// �ړ����
		}
	}
}

//**************************************************
// �G�l�~�[�̍U��
//**************************************************
void AttackEnemy(int nCntEnemy)
{
	PLAYER* pPlayer = GetPlayer();	// �v���C���[�̎擾

	if (g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_MOVE ||
		g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_NEUTRAL)
	{// ���̏�Ԃ̂Ƃ�

		if (CollisionSphere(&g_aEnemy[nCntEnemy].pos, &pPlayer->pos, 60.0f, pPlayer->charParam.fWidth, false))
		{// �v���C���[�ɋ߂�
			g_aEnemy[nCntEnemy].charParam.nState = MOTIONTYPE_ENEMY_ATTACK;	// �U����Ԃɂ���
			g_aEnemy[nCntEnemy].charParam.nCntState = 0;					// �J�E���g���Z�b�g
			g_aEnemy[nCntEnemy].charParam.nCntOcc = 0;						// �����J�E���^�[�[��
		}
	}
	else if (CollisionBlockSpher(g_aEnemy[nCntEnemy].pos, 10.0f, BLOCKTYPE_WALL, false).nType == BLOCKTYPE_WALL)
	{
		g_aEnemy[nCntEnemy].charParam.nState = MOTIONTYPE_ENEMY_ATTACK;	// �U����Ԃɂ���
		g_aEnemy[nCntEnemy].charParam.nCntState = 0;					// �J�E���g���Z�b�g
		g_aEnemy[nCntEnemy].charParam.nCntOcc = 0;						// �����J�E���^�[�[��
	}

	if (g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_ATTACK)
	{// �U���Ȃ�
		g_aEnemy[nCntEnemy].charParam.nCntOcc++;	// �����J�E���^�[�ǉ�
		if (g_aEnemy[nCntEnemy].charParam.nCntOcc >= 40)
		{// ��萔�ȏ�Ȃ�����
			g_aEnemy[nCntEnemy].charParam.nCntDura++;	// �����J�E���^�[�ǉ�

			BLOCKCOLLISION blockCollision[2];

			for (int nCntPModel = 0; nCntPModel < pPlayer->charParam.nNumModel; nCntPModel++)
			{// ���f������
				if (CollisionSphere(&g_aEnemy[nCntEnemy].aColiPoint[MODELPOSITION_ENEMY_HAND_L].pos, &pPlayer->aPlayerColiPoint[nCntPModel].pos, g_aEnemy[nCntEnemy].aColiPoint[MODELPOSITION_ENEMY_HAND_R].fRadius, pPlayer->aPlayerColiPoint[nCntPModel].fRadius, false))
				{
					// �v���C���[�̃q�b�g����
					HitPlayer(5);
				}

				if (CollisionSphere(&g_aEnemy[nCntEnemy].aColiPoint[MODELPOSITION_ENEMY_HAND_R].pos, &pPlayer->aPlayerColiPoint[nCntPModel].pos, g_aEnemy[nCntEnemy].aColiPoint[MODELPOSITION_ENEMY_HAND_R].fRadius, pPlayer->aPlayerColiPoint[nCntPModel].fRadius, false))
				{
					// �v���C���[�̃q�b�g����
					HitPlayer(5);
				}

			}

			blockCollision[0] = CollisionBlockSpher(g_aEnemy[nCntEnemy].aColiPoint[MODELPOSITION_ENEMY_HAND_L].pos, 10.0f, BLOCKTYPE_WALL, true);
			blockCollision[1] = CollisionBlockSpher(g_aEnemy[nCntEnemy].aColiPoint[MODELPOSITION_ENEMY_HAND_R].pos, 10.0f, BLOCKTYPE_WALL, true);
			if (blockCollision[0].bHit || blockCollision[1].bHit)
			{// �ǂ������������Ă���
			}
		}
	}
}

//**************************************************
// �G�l�~�[�߂�
//**************************************************
void GoHomeEnemy(int nCntEnemy)
{
	if (g_aEnemy[nCntEnemy].myTerrtry.nTimer <= 60)
	{
		if (g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_NEUTRAL ||
			g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_MOVE)
		{// ���̏�Ԃ̂Ƃ�
			// �G�l�~�[�ړ����
			EnemyStateChangeMove(nCntEnemy);
			// �^�C�}�[���Z
			g_aEnemy[nCntEnemy].myTerrtry.nTimer++;

			// �ړI�n�܂ł̕��������߂�
			D3DXVECTOR3 vecA = g_aEnemy[nCntEnemy].myTerrtry.pos - g_aEnemy[nCntEnemy].pos;

			// ���K������
			D3DXVec3Normalize(&vecA, &vecA);

			// �ړ��ʐݒ�
			g_aEnemy[nCntEnemy].move.x = ENEMY_MOVE_SPEED * vecA.x;
			g_aEnemy[nCntEnemy].move.y = 0.0f;
			g_aEnemy[nCntEnemy].move.z = ENEMY_MOVE_SPEED * vecA.z;

			// �����ݒ�
			g_aEnemy[nCntEnemy].rot.y = atan2f(vecA.x, vecA.z);
		}

		if (CollisionBlockSpher(g_aEnemy[nCntEnemy].pos, g_aEnemy[nCntEnemy].charParam.fWidth, BLOCKTYPE_WALL, false).nType == BLOCKTYPE_WALL)
		{
			AttackEnemy(nCntEnemy);
		}
	}
	else
	{
		// �ҋ@���
		PatrolEnemy(nCntEnemy);	// ���񂷂�
	}
}

//**************************************************
// �G�l�~�[����
//**************************************************
void PatrolEnemy(int nCntEnemy)
{
	if (g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_NEUTRAL || 
		g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_MOVE)
	{// ���̏�Ԃ̂Ƃ�
		if (g_aEnemy[nCntEnemy].myTerrtry.nPatrolTimer <= 0)
		{// �^�C�}�[�[���ȉ�

			g_aEnemy[nCntEnemy].myTerrtry.fAngle = (float)(rand() % 628 - 314) * 0.01f;	// �����_���Ō����ݒ�
			g_aEnemy[nCntEnemy].myTerrtry.nPatrolRimit = rand() % 240;					// ���~�b�g�������_���Őݒ�
			g_aEnemy[nCntEnemy].myTerrtry.nBreakTimer = rand() % 240;					// �x�e���Ԃ������_���Őݒ�
		}
		else
		{// �[������
			// �����Ă�����̈ړ��ʐݒ�
			g_aEnemy[nCntEnemy].move.x = sinf(g_aEnemy[nCntEnemy].myTerrtry.fAngle) * ENEMY_MOVE_SPEED;
			g_aEnemy[nCntEnemy].move.y;
			g_aEnemy[nCntEnemy].move.z = cosf(g_aEnemy[nCntEnemy].myTerrtry.fAngle) * ENEMY_MOVE_SPEED;

			// ������ݒ�
			g_aEnemy[nCntEnemy].rot.y = g_aEnemy[nCntEnemy].myTerrtry.fAngle;

			// �ړ���Ԃɂ���
			g_aEnemy[nCntEnemy].charParam.nState = MOTIONTYPE_ENEMY_MOVE;

		}

		// �^�C�}�[���Z
		g_aEnemy[nCntEnemy].myTerrtry.nPatrolTimer++;

		if (g_aEnemy[nCntEnemy].myTerrtry.nPatrolTimer >= g_aEnemy[nCntEnemy].myTerrtry.nPatrolRimit)
		{// ���~�b�g����
			g_aEnemy[nCntEnemy].charParam.nState = MOTIONTYPE_ENEMY_NEUTRAL;

			// �ړ��ʂ��Ȃ���
			g_aEnemy[nCntEnemy].move.x = 0.0f;
			g_aEnemy[nCntEnemy].move.y = 0.0f;
			g_aEnemy[nCntEnemy].move.z = 0.0f;

			if (g_aEnemy[nCntEnemy].myTerrtry.nBreakTimer > 0)
			{
				g_aEnemy[nCntEnemy].myTerrtry.nBreakTimer--;	// �x�e�^�C�}�[���Z
			}
			else
			{
				g_aEnemy[nCntEnemy].myTerrtry.nPatrolTimer = 0;	// �^�C�}�[���Z�b�g
			}
		}
	}
}

//**************************************************
// �G�l�~�[�̎擾
//**************************************************
ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//**************************************************
// �G�l�~�[�̎擾
//**************************************************
ENEMY_MANAGER GetEnemyManager(void)
{
	return  g_EnemyMane;
}