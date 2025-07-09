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

// グローバル変数宣言
ENEMY g_aEnemy[MAX_ENEMY];							// エネミー情報
ENEMY g_aEnemy_EX[ENEMYTYPE_MAX];					// エネミーの種類ごとの情報
MODELCOLER g_aModelCol[ENEMYTYPE_MAX][10][6];		// 便利な保存場所
ENEMY_MANAGER g_EnemyMane;							// エネミー管理

//**************************************************
// エネミーの初期化
//**************************************************
void InitEnemy(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_EnemyMane.nNumEnemy = 0;	// エネミーの総数

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		// 各種変数の初期化
		g_aEnemy[nCnt].pos = D3DXVECTOR3(100.0f, 40.0f, 0.0f);	// 位置
		g_aEnemy[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量
		g_aEnemy[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
		g_aEnemy[nCnt].bUse = false;							// 使ってません
		g_aEnemy[nCnt].nShadowIdx = 0;							// 影のインデックス
		g_aEnemy[nCnt].naSmokeIdx[0] = -1;						// 煙のインデックス
		g_aEnemy[nCnt].naSmokeIdx[1] = -1;						// 煙のインデックス

		g_aEnemy[nCnt].charParam.nNumModel = 0;							// パーツの総数
		g_aEnemy[nCnt].charParam.fWidth = 0.0f;							// 幅
		g_aEnemy[nCnt].charParam.fHeigt = 0.0f;							// 高さ
		g_aEnemy[nCnt].charParam.fJamp = 2.0f;							// ジャンプ力
		g_aEnemy[nCnt].charParam.nLife = 10;							// 体力
		g_aEnemy[nCnt].charParam.nState = MOTIONTYPE_ENEMY_NEUTRAL;		// 状態
		g_aEnemy[nCnt].charParam.nCntState = 0;							// 状態管理カウンター
		g_aEnemy[nCnt].charParam.nCntOcc = 0;							// 発生管理カウンター

		g_aEnemy[nCnt].motion.bLoopMotion = true;
		g_aEnemy[nCnt].motion.nNumKey = 2;
		g_aEnemy[nCnt].motion.nKey = 0;
		g_aEnemy[nCnt].motion.nCounterMotion = 0;
		g_aEnemy[nCnt].motion.nNextKey = g_aEnemy[nCnt].motion.nKey + 1;
		g_aEnemy[nCnt].motion.nNowMotiType = -1;

		g_aEnemy[nCnt].myTerrtry.fRadius = 300.0f;
		g_aEnemy[nCnt].myTerrtry.nTimer = 0;
		g_aEnemy[nCnt].myTerrtry.nPatrolTimer = 0;						// 巡回タイマーゼロ
		g_aEnemy[nCnt].myTerrtry.nPatrolRimit = 0;						// 巡回ゼロ限界カウンター
		g_aEnemy[nCnt].myTerrtry.nAngerTimer = 0;						// 怒りカウンター

	}

	for (int nCntEX = 0; nCntEX < ENEMYTYPE_MAX; nCntEX++)
	{
		switch (nCntEX)
		{
		case ENEMYTYPE_NOMAL:
			// モーションテキスト読み込み
			ReadMotionText("date\\motion\\yukiotoko\\motion.txt", &g_aEnemy_EX[nCntEX].aModel[0], &g_aEnemy_EX[nCntEX].motion, &g_aEnemy_EX[nCntEX].charParam);
			break;

		case ENEMYTYPE_REMOATE:
			// モーションテキスト読み込み
			ReadMotionText("date\\motion\\yukiotoko\\motion.txt", &g_aEnemy_EX[nCntEX].aModel[0], &g_aEnemy_EX[nCntEX].motion, &g_aEnemy_EX[nCntEX].charParam);
			break;

		default:
			// モーションテキスト読み込み
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
			//マテリアルデータへのポインタを取得
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
		BLOCK block = BlockSearch(BLOCKTYPE_TERRITRY_POINT, 0);	// ほしいブロックゲット♪
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			block.pos.x += 40.0f * nCnt;
			block.pos.z += 40.0f * nCnt;
			SetEnemy(block.pos, ENEMYTYPE_NOMAL);
		}

		block = BlockSearch(BLOCKTYPE_TERRITRY_POINT, 1);	// ほしいブロックゲット♪
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			block.pos.x += 40.0f * nCnt;
			block.pos.z += 40.0f * nCnt;
			SetEnemy(block.pos, ENEMYTYPE_NOMAL);
		}

		block = BlockSearch(BLOCKTYPE_TERRITRY_POINT, 2);	// ほしいブロックゲット♪
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			block.pos.x += 40.0f * nCnt;
			block.pos.z += 40.0f * nCnt;
			SetEnemy(block.pos, ENEMYTYPE_NOMAL);
		}

		block = BlockSearch(BLOCKTYPE_TERRITRY_POINT, 3);	// ほしいブロックゲット♪
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			block.pos.x += 40.0f * nCnt;
			block.pos.z += 40.0f * nCnt;
			SetEnemy(block.pos, ENEMYTYPE_NOMAL);
		}
	}
	else if (GetMode() == MODE_TUTORIAL)
	{
		BLOCK block = BlockSearch(BLOCKTYPE_TERRITRY_POINT, 0);	// ほしいブロックゲット♪
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			block.pos.x += 40.0f * nCnt;
			block.pos.y += 40.0f;
			block.pos.z += 40.0f * nCnt;
			SetEnemy(block.pos, ENEMYTYPE_NOMAL);
		}

		block = BlockSearch(BLOCKTYPE_TERRITRY_POINT, 1);	// ほしいブロックゲット♪
		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			block.pos.x += 40.0f * nCnt;
			block.pos.y += 40.0f;
			block.pos.z += 40.0f * nCnt;
			SetEnemy(block.pos, ENEMYTYPE_NOMAL);
		}

		block = BlockSearch(BLOCKTYPE_TERRITRY_POINT, 2);	// ほしいブロックゲット♪
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
// エネミーの終了
//**************************************************
void UninitEnemy(void)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		// メッシュの破棄
		if (g_aEnemy[nCnt].pMeshEnemy != NULL)
		{
			g_aEnemy[nCnt].pMeshEnemy->Release();
			g_aEnemy[nCnt].pMeshEnemy = NULL;
		}

		// マテリアルの破棄
		if (g_aEnemy[nCnt].pBuffMatEnemy != NULL)
		{
			g_aEnemy[nCnt].pBuffMatEnemy->Release();
			g_aEnemy[nCnt].pBuffMatEnemy = NULL;
		}

		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			// テクスチャの破棄
			if (g_aEnemy[nCnt].apTextureEnemy[nCnt] != NULL)
			{
				g_aEnemy[nCnt].apTextureEnemy[nCnt]->Release();
				g_aEnemy[nCnt].apTextureEnemy[nCnt] = NULL;
			}
		}
	}

	for (int nCnt = 0; nCnt < ENEMYTYPE_MAX; nCnt++)
	{
		// メッシュの破棄
		if (g_aEnemy_EX[nCnt].pMeshEnemy != NULL)
		{
			g_aEnemy_EX[nCnt].pMeshEnemy->Release();
			g_aEnemy_EX[nCnt].pMeshEnemy = NULL;
		}

		// マテリアルの破棄
		if (g_aEnemy_EX[nCnt].pBuffMatEnemy != NULL)
		{
			g_aEnemy_EX[nCnt].pBuffMatEnemy->Release();
			g_aEnemy_EX[nCnt].pBuffMatEnemy = NULL;
		}

		for (int nCntTex = 0; nCntTex < 6; nCntTex++)
		{
			// テクスチャの破棄
			if (g_aEnemy_EX[nCnt].apTextureEnemy[nCntTex] != NULL)
			{
				g_aEnemy_EX[nCnt].apTextureEnemy[nCntTex]->Release();
				g_aEnemy_EX[nCnt].apTextureEnemy[nCntTex] = NULL;
			}
		}
	}
}

//**************************************************
// エネミーの更新
//**************************************************
void UpdateEnemy(void)
{
	PLAYER* pPlayer = GetPlayer();	// プレイヤー情報ゲット

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

			// 重力
			g_aEnemy[nCnt].move.y -= 1.0f;

			g_aEnemy[nCnt].move.x += (0 - g_aEnemy[nCnt].move.x) * 0.1f;
			g_aEnemy[nCnt].move.z += (0 - g_aEnemy[nCnt].move.z) * 0.1f;

			CollisionEnemy(nCnt);
			int nType;

			g_aEnemy[nCnt].pos.y += g_aEnemy[nCnt].move.y;
			// ブロックへの当たり判定
			g_aEnemy[nCnt].blockCollision = CollisionBlockCharacter(&g_aEnemy[nCnt].pos, &g_aEnemy[nCnt].posOld, &g_aEnemy[nCnt].move, &nType, g_aEnemy[nCnt].charParam.fWidth, g_aEnemy[nCnt].charParam.fHeigt);

			g_aEnemy[nCnt].pos.x += g_aEnemy[nCnt].move.x;
			// ブロックへの当たり判定
			g_aEnemy[nCnt].blockCollision = CollisionBlockCharacter(&g_aEnemy[nCnt].pos, &g_aEnemy[nCnt].posOld, &g_aEnemy[nCnt].move, &nType, g_aEnemy[nCnt].charParam.fWidth, g_aEnemy[nCnt].charParam.fHeigt);

			g_aEnemy[nCnt].pos.z += g_aEnemy[nCnt].move.z;
			// ブロックへの当たり判定
			g_aEnemy[nCnt].blockCollision = CollisionBlockCharacter(&g_aEnemy[nCnt].pos, &g_aEnemy[nCnt].posOld, &g_aEnemy[nCnt].move, &nType, g_aEnemy[nCnt].charParam.fWidth, g_aEnemy[nCnt].charParam.fHeigt);


			if (g_aEnemy[nCnt].pos.y <= 0.0f)
			{// 世界のゼロ
				g_aEnemy[nCnt].bUse = false;
			}

			if (TerritryConfirmation(g_aEnemy[nCnt].myTerrtry, g_aEnemy[nCnt].pos) == true)
			{// 自身がテリトリー外
				g_aEnemy[nCnt].myTerrtry.nTimer = 0;
				GoHomeEnemy(nCnt);	// 帰る
			}

			
				if (TerritryConfirmation(g_aEnemy[nCnt].myTerrtry, pPlayer->pos) == true)
				{// またはプレイヤーがテリトリーにいない
					GoHomeEnemy(nCnt);	// 帰る
				}

				if (TerritryConfirmation(g_aEnemy[nCnt].myTerrtry, pPlayer->pos) == false ||
					CollisionSphere(&g_aEnemy[nCnt].pos, &pPlayer->pos, 200.0f, 0.0f, false) ||
					g_aEnemy[nCnt].myTerrtry.nAngerTimer > 0)
				{// プレイヤーがテリトリーにいる,プレイヤーが近くにいる
					// タイマー初期化
					g_aEnemy[nCnt].myTerrtry.nTimer = 0;	// タイマーゼロ
					g_aEnemy[nCnt].myTerrtry.nAngerTimer--;	// 怒りカウンターマイナス

					// 待機
					NeutralEnemy(nCnt);
					if (GetMode() == MODE_GAME)
					{
						// 追いかけ
						ChaseEnemy(nCnt);

						// 攻撃
						AttackEnemy(nCnt);
					}
				}

			// 状態管理
			EnemyStateManegement(nCnt);

			// モーション更新
			UpdateMotion(&g_aEnemy[nCnt].motion, &g_aEnemy[nCnt].aModel[0], g_aEnemy[nCnt].charParam.nState, g_aEnemy[nCnt].charParam.nNumModel);

			for (int nCntPosi = 0; nCntPosi < g_aEnemy[nCnt].charParam.nNumModel; nCntPosi++)
			{
				CollisionPointUpdate(&g_aEnemy[nCnt].aColiPoint[nCntPosi].pos, g_aEnemy[nCnt].aModel[nCntPosi].mtxWorld);
			}

			// 体力ゲージの位置更新
			UpdateHPGaugePos(&g_aEnemy[nCnt].HPGaugeHave[HPGAUGETYPE_BG], g_aEnemy[nCnt].pos, 110.0f, 50.0f);
			UpdateHPGaugePos(&g_aEnemy[nCnt].HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], g_aEnemy[nCnt].pos, 110.0f, 50.0f);
			UpdateHPGaugePos(&g_aEnemy[nCnt].HPGaugeHave[HPGAUGETYPE_GAUGE], g_aEnemy[nCnt].pos, 110.0f, 50.0f);

			// 体力赤ゲージの長さ更新
			UpdateHPGaugeRedZoneWidth(&g_aEnemy[nCnt].HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], g_aEnemy[nCnt].charParam.nLife);

			// 影の更新
			SetPositionShadow(g_aEnemy[nCnt].nShadowIdx, g_aEnemy[nCnt].pos);
		}
	}
}

//**************************************************
// エネミーの描画
//**************************************************
void DrawEnemy(void)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_aEnemy[nCnt].bUse)
		{
			// デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			// 計算用マトリックス
			D3DXMATRIX mtxRot, mtxTrans;

			// 現在のマテリアル保存用
			D3DMATERIAL9 matDef;

			// マテリアルデータへのポインタ
			D3DXMATERIAL* pMat;

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEnemy[nCnt].mtxWorldEnemy);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCnt].rot.y, g_aEnemy[nCnt].rot.x, g_aEnemy[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCnt].mtxWorldEnemy, &g_aEnemy[nCnt].mtxWorldEnemy, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCnt].pos.x, g_aEnemy[nCnt].pos.y, g_aEnemy[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCnt].mtxWorldEnemy, &g_aEnemy[nCnt].mtxWorldEnemy, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCnt].mtxWorldEnemy);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// 全モデル(パーツ)の描画
			for (int nCntModel = 0; nCntModel < g_aEnemy[nCnt].charParam.nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;	// 計算用マトリックス
				D3DXMATRIX mtxParent;					// 親マトリックス

				// パーツのワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld);

				// パーツの向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy[nCnt].aModel[nCntModel].rot.y, g_aEnemy[nCnt].aModel[nCntModel].rot.x, g_aEnemy[nCnt].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld, &g_aEnemy[nCnt].aModel[nCntModel].mtxWorld, &mtxRotModel);

				// パーツの位置(オフセット)を反映
				D3DXMatrixTranslation(&mtxTransModel, g_aEnemy[nCnt].aModel[nCntModel].pos.x, g_aEnemy[nCnt].aModel[nCntModel].pos.y, g_aEnemy[nCnt].aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld, &g_aEnemy[nCnt].aModel[nCntModel].mtxWorld, &mtxTransModel);

				// パーツ「親のマトリックス」を設定
				if (g_aEnemy[nCnt].aModel[nCntModel].nIdxModelParent != -1)
				{// 親モデルがある場合
					mtxParent = g_aEnemy[nCnt].aModel[g_aEnemy[nCnt].aModel[nCntModel].nIdxModelParent].mtxWorld;	// 親モデルのインデックスを設定
				}
				else
				{// 親のモデルがない場合
					mtxParent = g_aEnemy[nCnt].mtxWorldEnemy;	// プレイヤーのマトリックスを設定
				}

				// 算出したパーツのワールドマトリックスと親マトリックスをかけ合わせる
				D3DXMatrixMultiply(&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld,
					&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld,
					&mtxParent);

				// パーツのワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD,
					&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld);

				// マテリアルデータへのポインタを取得
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

						// マテリアルの設定
						pDevice->SetMaterial(&damageMat.MatD3D);
					}
					else
					{
						// マテリアルの設定
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					}

					// テクスチャの設定
					pDevice->SetTexture(0, g_aEnemy[nCnt].aModel[nCntModel].apTexture[nCntMat]);

					// パーツの描画
					g_aEnemy[nCnt].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}
			}

			// 保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//**************************************************
// エネミーの設定
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


			// 敵の種類ごとに設定していく
			switch (type)
			{
			case ENEMYTYPE_NOMAL:	// 通常の敵
				for (int nCntModel = 0; nCntModel < (int)g_aEnemy_EX[ENEMYTYPE_NOMAL].charParam.nNumModel; nCntModel++)
				{
					g_aEnemy[nCnt].aModel[nCntModel] = g_aEnemy_EX[ENEMYTYPE_NOMAL].aModel[nCntModel];	// モデルたち
					g_aEnemy[nCnt].aColiPoint[nCntModel] = g_aEnemy_EX[type].aColiPoint[nCntModel];
				}

				for (int nCntTex = 0; nCntTex < 6; nCntTex++)
				{
					g_aEnemy[nCnt].apTextureEnemy[nCntTex] = g_aEnemy_EX[ENEMYTYPE_NOMAL].apTextureEnemy[nCntTex];
				}
				
				g_aEnemy[nCnt].pMeshEnemy = g_aEnemy_EX[ENEMYTYPE_NOMAL].pMeshEnemy;
				g_aEnemy[nCnt].pBuffMatEnemy = g_aEnemy_EX[ENEMYTYPE_NOMAL].pBuffMatEnemy;
				g_aEnemy[nCnt].mtxWorldEnemy = g_aEnemy_EX[ENEMYTYPE_NOMAL].mtxWorldEnemy;

				g_aEnemy[nCnt].motion = g_aEnemy_EX[ENEMYTYPE_NOMAL].motion;		// モーションたち

				g_aEnemy[nCnt].charParam.nNumModel = g_aEnemy_EX[ENEMYTYPE_NOMAL].charParam.nNumModel;	// パーツの総数
				g_aEnemy[nCnt].charParam.fWidth = g_aEnemy_EX[ENEMYTYPE_NOMAL].charParam.fWidth;		// 幅
				g_aEnemy[nCnt].charParam.fHeigt = g_aEnemy_EX[ENEMYTYPE_NOMAL].charParam.fHeigt;		// 高さ
				g_aEnemy[nCnt].charParam.fJamp = 2.0f;							// ジャンプ力
				g_aEnemy[nCnt].charParam.nLife = 10;							// 体力
				g_aEnemy[nCnt].charParam.nState = MOTIONTYPE_ENEMY_NEUTRAL;		// 状態
				g_aEnemy[nCnt].charParam.nCntState = 0;							// 状態管理カウンター
				g_aEnemy[nCnt].charParam.nCntOcc = 0;							// 発生管理カウンター

				g_aEnemy[nCnt].motion.nNowMotiType =  -1;
				break;

			case ENEMYTYPE_REMOATE:	// 遠隔の敵
				break;

				
			}

			// 敵の総数追加
			g_EnemyMane.nNumEnemy++;

			if (GetMode() == MODE_GAME || GetMode() == MODE_TUTORIAL)
			{
				// HPゲージの設定
				SetHPGauge(&g_aEnemy[nCnt].HPGaugeHave[HPGAUGETYPE_BG], HPGAUGETYPE_BG, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f), 5.0f, 100.0f, g_aEnemy[nCnt].charParam.nLife);
				SetHPGauge(&g_aEnemy[nCnt].HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], HPGAUGETYPE_GAUGE_REDZONE, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5.0f, 100.0f, g_aEnemy[nCnt].charParam.nLife);
				SetHPGauge(&g_aEnemy[nCnt].HPGaugeHave[HPGAUGETYPE_GAUGE], HPGAUGETYPE_GAUGE, D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f), 5.0f, 100.0f, g_aEnemy[nCnt].charParam.nLife);
			}
			// 砂煙
			g_aEnemy[nCnt].naSmokeIdx[0] = SetSmoke(SMOKETYPE_ATTACH, g_aEnemy[nCnt].pos, 20, 20.0f, true);
			g_aEnemy[nCnt].naSmokeIdx[1] = SetSmoke(SMOKETYPE_ATTACH, g_aEnemy[nCnt].pos, 40, 20.0f, true);

			// 影を設定
			g_aEnemy[nCnt].nShadowIdx = SetShadw(g_aEnemy[nCnt].pos, g_aEnemy[nCnt].rot, g_aEnemy[nCnt].charParam.fWidth);

			break;
		}
	}
}

//**************************************************
// エネミー待機
//**************************************************
void NeutralEnemy(int nCntEnemy)
{
	PLAYER* pPlayer = GetPlayer();	// プレイヤー取得

	if (pPlayer->charParam.bDisp == false)
	{
		g_aEnemy[nCntEnemy].charParam.nState = MOTIONTYPE_ENEMY_NEUTRAL;
	}
}

//**************************************************
// エネミー追いかけ
//**************************************************
void ChaseEnemy(int nCntEnemy)
{
	PLAYER* pPlayer = GetPlayer();	// プレイヤー取得

	if (pPlayer->charParam.bDisp)
	{// プレイヤーがいたら
		g_aEnemy[nCntEnemy].charParam.bMove = true;	// 動くよ

		if (g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_NEUTRAL ||
			g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_MOVE)
		{// この状態のとき
			// エネミー移動状態
			EnemyStateChangeMove(nCntEnemy);

			D3DXVECTOR3 vecA = pPlayer->pos - g_aEnemy[nCntEnemy].pos;

			// 正規化
			D3DXVec3Normalize(&vecA, &vecA);

			g_aEnemy[nCntEnemy].move.x = ENEMY_MOVE_SPEED_CHASE * vecA.x;
			g_aEnemy[nCntEnemy].move.y = 0.0f;
			g_aEnemy[nCntEnemy].move.z = ENEMY_MOVE_SPEED_CHASE * vecA.z;

			g_aEnemy[nCntEnemy].rot.y = atan2f(vecA.x, vecA.z);

			
		}
	}
}

//**************************************************
// エネミーどうしの当たり判定
//**************************************************
void CollisionEnemy(int nCntEnemy)
{
	PLAYER* pPlayer = GetPlayer();	// プレイヤー取得

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
// エネミーの当ったとき
//**************************************************
void HitEnemy(int nCntEnemy, int nDamage)
{
	if (g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_DAMAGE)
	{
		return;
	}

	// 敵ヒット音
	PlaySound(SOUND_LABEL_SE_HIT_ENEMY);

	g_aEnemy[nCntEnemy].charParam.nLife -= nDamage;
	g_aEnemy[nCntEnemy].charParam.nState = MOTIONTYPE_ENEMY_DAMAGE;

	// 体力ゲージの長さ更新
	UpdateHPGaugeWidth(&g_aEnemy[nCntEnemy].HPGaugeHave[HPGAUGETYPE_GAUGE], g_aEnemy[nCntEnemy].charParam.nLife);

	// 怒りタイマー設定
	g_aEnemy[nCntEnemy].myTerrtry.nAngerTimer = rand() % 360 + 360;

	if (g_aEnemy[nCntEnemy].charParam.nLife <= 0)
	{// 体力ないなったら
		g_aEnemy[nCntEnemy].bUse = false;

		// 敵の総数減数
		g_EnemyMane.nNumEnemy--;

		// HPゲージ終わり
		EndHPGauge(&g_aEnemy[nCntEnemy].HPGaugeHave[HPGAUGETYPE_BG]);
		EndHPGauge(&g_aEnemy[nCntEnemy].HPGaugeHave[HPGAUGETYPE_GAUGE]);
		EndHPGauge(&g_aEnemy[nCntEnemy].HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE]);


		// 影終了
		EndShadow(g_aEnemy[nCntEnemy].nShadowIdx);

		if (g_EnemyMane.nNumEnemy <= 0 && GetMode() == MODE_GAME)
		{
			//フェードアウトする
			SetFade(MODE_RESULT);
			SetResult(RESULTTYPE_GAMECREAR);
		}
	}
}

//**************************************************
// エネミーの状態管理
//**************************************************
void EnemyStateManegement(int nCnt)
{
	switch (g_aEnemy[nCnt].charParam.nState)
	{
	case MOTIONTYPE_ENEMY_NEUTRAL:
		break;

	case MOTIONTYPE_ENEMY_MOVE:
		UpdateAttachSmoke(g_aEnemy[nCnt].naSmokeIdx[0], g_aEnemy[nCnt].aColiPoint[MODELPOSITION_PLAYER_FOOT_L].pos);		// 煙
		UpdateAttachSmoke(g_aEnemy[nCnt].naSmokeIdx[1], g_aEnemy[nCnt].aColiPoint[MODELPOSITION_PLAYER_FOOT_R].pos);		// 煙
		break;

	case MOTIONTYPE_ENEMY_ATTACK:
		g_aEnemy[nCnt].charParam.nCntState++;	// カウントプラス

		if (g_aEnemy[nCnt].charParam.nCntState >= 90)
		{// カウントが一定数になったら
			g_aEnemy[nCnt].charParam.nCntState = 0;	// カウントリセット
			g_aEnemy[nCnt].charParam.nState = MOTIONTYPE_ENEMY_NEUTRAL;	// 通常状態
		}
		break;

	case MOTIONTYPE_ENEMY_DAMAGE:
		g_aEnemy[nCnt].charParam.nCntState++;	// カウントプラス
		if (g_aEnemy[nCnt].charParam.nCntState >= 30)
		{// カウントが一定数になったら
			g_aEnemy[nCnt].charParam.nCntState = 0;	// カウントリセット
			g_aEnemy[nCnt].charParam.nState = MOTIONTYPE_ENEMY_NEUTRAL;	// 通常状態
		}
		break;

	case MOTIONTYPE_ENEMY_DAETH:
		break;
	}
}

//**************************************************
// エネミーの移動状態
//**************************************************
void EnemyStateChangeMove(int nCntEnemy)
{
	if (g_aEnemy[nCntEnemy].charParam.bMove)
	{
		if (g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_PLAYER_NEUTRAL ||
			g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_PLAYER_RANDING)
		{// この状態のとき
			g_aEnemy[nCntEnemy].charParam.nState = MOTIONTYPE_PLAYER_MOVE;	// 移動状態
		}
	}
}

//**************************************************
// エネミーの攻撃
//**************************************************
void AttackEnemy(int nCntEnemy)
{
	PLAYER* pPlayer = GetPlayer();	// プレイヤーの取得

	if (g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_MOVE ||
		g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_NEUTRAL)
	{// この状態のとき

		if (CollisionSphere(&g_aEnemy[nCntEnemy].pos, &pPlayer->pos, 60.0f, pPlayer->charParam.fWidth, false))
		{// プレイヤーに近い
			g_aEnemy[nCntEnemy].charParam.nState = MOTIONTYPE_ENEMY_ATTACK;	// 攻撃状態にする
			g_aEnemy[nCntEnemy].charParam.nCntState = 0;					// カウントリセット
			g_aEnemy[nCntEnemy].charParam.nCntOcc = 0;						// 発生カウンターゼロ
		}
	}
	else if (CollisionBlockSpher(g_aEnemy[nCntEnemy].pos, 10.0f, BLOCKTYPE_WALL, false).nType == BLOCKTYPE_WALL)
	{
		g_aEnemy[nCntEnemy].charParam.nState = MOTIONTYPE_ENEMY_ATTACK;	// 攻撃状態にする
		g_aEnemy[nCntEnemy].charParam.nCntState = 0;					// カウントリセット
		g_aEnemy[nCntEnemy].charParam.nCntOcc = 0;						// 発生カウンターゼロ
	}

	if (g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_ATTACK)
	{// 攻撃なら
		g_aEnemy[nCntEnemy].charParam.nCntOcc++;	// 発生カウンター追加
		if (g_aEnemy[nCntEnemy].charParam.nCntOcc >= 40)
		{// 一定数以上なったら
			g_aEnemy[nCntEnemy].charParam.nCntDura++;	// 持続カウンター追加

			BLOCKCOLLISION blockCollision[2];

			for (int nCntPModel = 0; nCntPModel < pPlayer->charParam.nNumModel; nCntPModel++)
			{// モデル分回す
				if (CollisionSphere(&g_aEnemy[nCntEnemy].aColiPoint[MODELPOSITION_ENEMY_HAND_L].pos, &pPlayer->aPlayerColiPoint[nCntPModel].pos, g_aEnemy[nCntEnemy].aColiPoint[MODELPOSITION_ENEMY_HAND_R].fRadius, pPlayer->aPlayerColiPoint[nCntPModel].fRadius, false))
				{
					// プレイヤーのヒット処理
					HitPlayer(5);
				}

				if (CollisionSphere(&g_aEnemy[nCntEnemy].aColiPoint[MODELPOSITION_ENEMY_HAND_R].pos, &pPlayer->aPlayerColiPoint[nCntPModel].pos, g_aEnemy[nCntEnemy].aColiPoint[MODELPOSITION_ENEMY_HAND_R].fRadius, pPlayer->aPlayerColiPoint[nCntPModel].fRadius, false))
				{
					// プレイヤーのヒット処理
					HitPlayer(5);
				}

			}

			blockCollision[0] = CollisionBlockSpher(g_aEnemy[nCntEnemy].aColiPoint[MODELPOSITION_ENEMY_HAND_L].pos, 10.0f, BLOCKTYPE_WALL, true);
			blockCollision[1] = CollisionBlockSpher(g_aEnemy[nCntEnemy].aColiPoint[MODELPOSITION_ENEMY_HAND_R].pos, 10.0f, BLOCKTYPE_WALL, true);
			if (blockCollision[0].bHit || blockCollision[1].bHit)
			{// どっちか当たってたら
			}
		}
	}
}

//**************************************************
// エネミー戻る
//**************************************************
void GoHomeEnemy(int nCntEnemy)
{
	if (g_aEnemy[nCntEnemy].myTerrtry.nTimer <= 60)
	{
		if (g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_NEUTRAL ||
			g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_MOVE)
		{// この状態のとき
			// エネミー移動状態
			EnemyStateChangeMove(nCntEnemy);
			// タイマー加算
			g_aEnemy[nCntEnemy].myTerrtry.nTimer++;

			// 目的地までの方向を求めて
			D3DXVECTOR3 vecA = g_aEnemy[nCntEnemy].myTerrtry.pos - g_aEnemy[nCntEnemy].pos;

			// 正規化して
			D3DXVec3Normalize(&vecA, &vecA);

			// 移動量設定
			g_aEnemy[nCntEnemy].move.x = ENEMY_MOVE_SPEED * vecA.x;
			g_aEnemy[nCntEnemy].move.y = 0.0f;
			g_aEnemy[nCntEnemy].move.z = ENEMY_MOVE_SPEED * vecA.z;

			// 向き設定
			g_aEnemy[nCntEnemy].rot.y = atan2f(vecA.x, vecA.z);
		}

		if (CollisionBlockSpher(g_aEnemy[nCntEnemy].pos, g_aEnemy[nCntEnemy].charParam.fWidth, BLOCKTYPE_WALL, false).nType == BLOCKTYPE_WALL)
		{
			AttackEnemy(nCntEnemy);
		}
	}
	else
	{
		// 待機状態
		PatrolEnemy(nCntEnemy);	// 巡回する
	}
}

//**************************************************
// エネミー巡回
//**************************************************
void PatrolEnemy(int nCntEnemy)
{
	if (g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_NEUTRAL || 
		g_aEnemy[nCntEnemy].charParam.nState == MOTIONTYPE_ENEMY_MOVE)
	{// この状態のとき
		if (g_aEnemy[nCntEnemy].myTerrtry.nPatrolTimer <= 0)
		{// タイマーゼロ以下

			g_aEnemy[nCntEnemy].myTerrtry.fAngle = (float)(rand() % 628 - 314) * 0.01f;	// ランダムで向き設定
			g_aEnemy[nCntEnemy].myTerrtry.nPatrolRimit = rand() % 240;					// リミットをランダムで設定
			g_aEnemy[nCntEnemy].myTerrtry.nBreakTimer = rand() % 240;					// 休憩時間をランダムで設定
		}
		else
		{// ゼロより上
			// 向いてる方向の移動量設定
			g_aEnemy[nCntEnemy].move.x = sinf(g_aEnemy[nCntEnemy].myTerrtry.fAngle) * ENEMY_MOVE_SPEED;
			g_aEnemy[nCntEnemy].move.y;
			g_aEnemy[nCntEnemy].move.z = cosf(g_aEnemy[nCntEnemy].myTerrtry.fAngle) * ENEMY_MOVE_SPEED;

			// 向きを設定
			g_aEnemy[nCntEnemy].rot.y = g_aEnemy[nCntEnemy].myTerrtry.fAngle;

			// 移動状態にする
			g_aEnemy[nCntEnemy].charParam.nState = MOTIONTYPE_ENEMY_MOVE;

		}

		// タイマー加算
		g_aEnemy[nCntEnemy].myTerrtry.nPatrolTimer++;

		if (g_aEnemy[nCntEnemy].myTerrtry.nPatrolTimer >= g_aEnemy[nCntEnemy].myTerrtry.nPatrolRimit)
		{// リミットより上
			g_aEnemy[nCntEnemy].charParam.nState = MOTIONTYPE_ENEMY_NEUTRAL;

			// 移動量をなくす
			g_aEnemy[nCntEnemy].move.x = 0.0f;
			g_aEnemy[nCntEnemy].move.y = 0.0f;
			g_aEnemy[nCntEnemy].move.z = 0.0f;

			if (g_aEnemy[nCntEnemy].myTerrtry.nBreakTimer > 0)
			{
				g_aEnemy[nCntEnemy].myTerrtry.nBreakTimer--;	// 休憩タイマー減算
			}
			else
			{
				g_aEnemy[nCntEnemy].myTerrtry.nPatrolTimer = 0;	// タイマーリセット
			}
		}
	}
}

//**************************************************
// エネミーの取得
//**************************************************
ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//**************************************************
// エネミーの取得
//**************************************************
ENEMY_MANAGER GetEnemyManager(void)
{
	return  g_EnemyMane;
}