#include "bullet.h"
#include "camera.h"
#include "explosion.h"
#include "effect.h"
#include "player.h"
#include "enemy.h"
#include "collision.h"
#include "shadow.h"
#include "particle.h"
#include "sound.h"

// グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;				// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pVtxTexturBullet[BULLETTYPE_MAX] = {};		// テクスチャのポインタ
BULLET g_aBullet[MAX_BULLET];									// 弾

//**************************************
// 弾の初期化
//**************************************
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet, NULL);

	VERTEX_3D* pVtx = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_BULLET_SNOW,
		&g_pVtxTexturBullet[BULLETTYPE_SNOW]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_BULLET_SNOW,
		&g_pVtxTexturBullet[BULLETTYPE_SNOW_MEDIUM]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_BULLET_SNOW,
		&g_pVtxTexturBullet[BULLETTYPE_SNOW_BIG]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_BULLET_ICE,
		&g_pVtxTexturBullet[BULLETTYPE_ICE]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_BULLET_GRAVEL,
		&g_pVtxTexturBullet[BULLETTYPE_GRAVEL]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_BULLET_GRAVEL,
		&g_pVtxTexturBullet[BULLETTYPE_GRAVEL_DIFFUSION]);

	// 頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		g_aBullet[nCntBl].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBl].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBl].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBl].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBl].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBl].nType = BULLETTYPE_MAX;
		g_aBullet[nCntBl].fLife = 0.0f;
		g_aBullet[nCntBl].bUse = false;

		g_aBullet[nCntBl].fWidth = 0.0f;

		// 頂点座標の設定
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

		// 各頂点の法線の設定(＊ベクトルの大きさは1にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//*****************************
// 弾の破棄
//*****************************
void UninitBullet(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	for (int nCnt = 0; nCnt < BULLETTYPE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (g_pVtxTexturBullet[nCnt] != NULL)
		{
			g_pVtxTexturBullet[nCnt]->Release();
			g_pVtxTexturBullet[nCnt] = NULL;
		}
	}
}

//*****************************
// 弾の更新
//*****************************
void UpdateBullet(void)
{
	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		if (g_aBullet[nCntBl].bUse == true)
		{

			g_aBullet[nCntBl].posOld = g_aBullet[nCntBl].pos;

			switch (g_aBullet[nCntBl].nType)
			{
			case BULLETTYPE_SNOW:	// 雪玉処理
				SnowBall(nCntBl);
				break;

			case BULLETTYPE_SNOW_MEDIUM:	// 雪玉中処理
				SnowBallMidium(nCntBl);
				break;

			case BULLETTYPE_SNOW_BIG:	// 雪玉大処理
				SnowBallBig(nCntBl);
				break;

			case BULLETTYPE_ICE:	// 氷玉処理
				IceBall(nCntBl);
				break;

			case BULLETTYPE_GRAVEL:	// 砂利玉処理
				GravelBall(nCntBl);
				break;

			case BULLETTYPE_GRAVEL_DIFFUSION:	// 拡散砂利玉処理
				GravelBallDiffusion(nCntBl);
				break;
			}

			// 影の位置更新
			SetPositionShadow(g_aBullet[nCntBl].nShadowIdx, g_aBullet[nCntBl].pos);
		}
	}
}

//*****************************
// 弾の描画
//*****************************
void DrawBullet(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,254);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		if (g_aBullet[nCntBl].bUse == true)
		{// 使ってたら
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBullet[nCntBl].mtxWorld);

			// ビューマトリックス取得
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// カメラの逆行列を設定
			g_aBullet[nCntBl].mtxWorld._11 = mtxview._11;
			g_aBullet[nCntBl].mtxWorld._12 = mtxview._21;
			g_aBullet[nCntBl].mtxWorld._13 = mtxview._31;
			g_aBullet[nCntBl].mtxWorld._21 = mtxview._12;
			g_aBullet[nCntBl].mtxWorld._22 = mtxview._22;
			g_aBullet[nCntBl].mtxWorld._23 = mtxview._32;
			g_aBullet[nCntBl].mtxWorld._31 = mtxview._13;
			g_aBullet[nCntBl].mtxWorld._32 = mtxview._23;
			g_aBullet[nCntBl].mtxWorld._33 = mtxview._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBl].pos.x, g_aBullet[nCntBl].pos.y, g_aBullet[nCntBl].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBl].mtxWorld, &g_aBullet[nCntBl].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBl].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// テクスチャの設定
			pDevice->SetTexture(0, g_pVtxTexturBullet[g_aBullet[nCntBl].nType]);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// 弾の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBl, 2);
		}
	}

	// アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);

	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//*****************************
// 弾の設定
//*****************************
void SetBullet(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int nBlType)
{
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBl = 0; nCntBl < MAX_BULLET; nCntBl++)
	{
		if (nBlType == -1)
		{// タイプなかったら作らない
			break;
		}

		if (g_aBullet[nCntBl].bUse == false)
		{
			float fSize = 10.0f;

			g_aBullet[nCntBl].pos.x = pos.x;
			g_aBullet[nCntBl].pos.y = pos.y;
			g_aBullet[nCntBl].pos.z = pos.z;

			g_aBullet[nCntBl].dir = rot;
			g_aBullet[nCntBl].nType = nBlType;
			
			g_aBullet[nCntBl].fWidth = fSize;

			g_aBullet[nCntBl].bUse = true;

			switch (nBlType)
			{
			case BULLETTYPE_SNOW:	// 雪玉
				g_aBullet[nCntBl].move.x = sinf(rot.y) * BULLET_SPEED;
				g_aBullet[nCntBl].move.y = 2.0f;
				g_aBullet[nCntBl].move.z = cosf(rot.y) * BULLET_SPEED;
				g_aBullet[nCntBl].fLife = 120;
				break;

			case BULLETTYPE_SNOW_MEDIUM:	// 中玉
				g_aBullet[nCntBl].move.x = sinf(rot.y) * BULLET_SPEED * 0.5f;
				g_aBullet[nCntBl].move.y = 5.0f;
				g_aBullet[nCntBl].move.z = cosf(rot.y) * BULLET_SPEED * 0.5f;
				g_aBullet[nCntBl].fLife = 180;
				fSize *= 1.5f;
				g_aBullet[nCntBl].fWidth = fSize;
				break;

			case BULLETTYPE_SNOW_BIG:	// 大玉
				g_aBullet[nCntBl].move.x = sinf(rot.y) * BULLET_SPEED * 0.5f;
				g_aBullet[nCntBl].move.y = 0.0f;
				g_aBullet[nCntBl].move.z = cosf(rot.y) * BULLET_SPEED * 0.5f;
				g_aBullet[nCntBl].fLife = 240;
				g_aBullet[nCntBl].pos.y = pos.y + 20.0f;
				fSize *= 2.0f;
				g_aBullet[nCntBl].fWidth = fSize;
				break;

			case BULLETTYPE_ICE:	// 氷玉
				g_aBullet[nCntBl].move.x = sinf(rot.y) * BULLET_SPEED;
				g_aBullet[nCntBl].move.y = 2.0f;
				g_aBullet[nCntBl].move.z = cosf(rot.y) * BULLET_SPEED;
				g_aBullet[nCntBl].fLife = 120;
				break;

			case BULLETTYPE_GRAVEL:	// 砂利玉
				g_aBullet[nCntBl].move.x = sinf(rot.y) * 2.0f;
				g_aBullet[nCntBl].move.y = BULLET_SPEED;
				g_aBullet[nCntBl].move.z = cosf(rot.y) * 2.0f;
				g_aBullet[nCntBl].fLife = 60;
				break;

			case BULLETTYPE_GRAVEL_DIFFUSION:	// 砂利玉拡散弾
				float fAngle = (float)((rand() % 628 - 314) * 0.01f);
				g_aBullet[nCntBl].move.x = rot.x + sinf(fAngle) * (float)((rand() % 150 - 75) * 0.05f);
				g_aBullet[nCntBl].move.y = rot.y;
				g_aBullet[nCntBl].move.z = rot.z + cosf(fAngle) * (float)((rand() % 150 - 75) * 0.05f);
				g_aBullet[nCntBl].fLife = 120;
				fSize *= 0.5f;
				g_aBullet[nCntBl].fWidth = fSize;
				break;
			}

			// 頂点座標の設定
			pVtx[0].pos.x = -fSize;
			pVtx[0].pos.y = fSize;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = fSize;
			pVtx[1].pos.y = fSize;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = -fSize;
			pVtx[2].pos.y = -fSize;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = fSize;
			pVtx[3].pos.y = -fSize;
			pVtx[3].pos.z = 0.0f;

			// 各頂点の法線の設定(＊ベクトルの大きさは1にする必要がある)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// 影設定
			g_aBullet[nCntBl].nShadowIdx = SetShadw(g_aBullet[nCntBl].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fSize);

			break;
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//*****************************
// 雪玉処理の設定
//*****************************
void SnowBall(int nCntBl)
{
	ENEMY* pEnemy = GetEnemy();	// エネミー取得

	g_aBullet[nCntBl].move.y -= (float)BULLET_GRAVITY;

	g_aBullet[nCntBl].pos.x += g_aBullet[nCntBl].move.x;
	g_aBullet[nCntBl].pos.y += g_aBullet[nCntBl].move.y;
	g_aBullet[nCntBl].pos.z += g_aBullet[nCntBl].move.z;

	g_aBullet[nCntBl].fLife -= 1.0f;

	SetEffect(EFFECTTYPE_TRAJECTORY,		// タイプ
		g_aBullet[nCntBl].pos,				// 位置
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 移動量
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 重力
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// 色
		30,									// 寿命
		20.0f,								// 大きさ
		false,								// 影の仕様有無
		true								// 加算合成
	);

	if (g_aBullet[nCntBl].fLife > 0)
	{
		if (CollisionBlock(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move) || g_aBullet[nCntBl].fLife <= 0.0f)
		{// ブロックとの当たり判定
			g_aBullet[nCntBl].bUse = false;

			// 爆発設定
			SETEXPLO setExplo;
			setExplo.pos = g_aBullet[nCntBl].pos;
			setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);

			SetExplosion(setExplo);

			// 影の終了
			EndShadow(g_aBullet[nCntBl].nShadowIdx);


			D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
			D3DXVec3Normalize(&patiMove,&patiMove);

			// パーティクル生成
			SetParticle(EFFECTTYPE_TRAJECTORY,	// タイプ
				g_aBullet[nCntBl].pos,			// 位置
				patiMove,						// 重力
				D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// 色
				50,								// 出す量
				60,								// 寿命
				5.0f,							// 大きさ
				3.0f,							// 速度
				false,							// 影の有無
				true							// 加算合成か減算合成か
			);

			// 雪玉が壊れる音
			PlaySound(SOUND_LABEL_SE_BREAKSNOWBALL);
		}

		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (g_aBullet[nCntBl].bUse == false)
			{// 弾使ってなかったら
				break;
			}

			if (pEnemy->bUse == false)
			{// 敵使ってなかったら
				continue;
			}

			for (int nCntPosi = 0; nCntPosi < pEnemy->charParam.nNumModel; nCntPosi++)
			{
				if (CollisionSphere(&g_aBullet[nCntBl].pos, &pEnemy->aColiPoint[nCntPosi].pos, g_aBullet[nCntBl].fWidth, pEnemy->aColiPoint[nCntPosi].fRadius + 20, false))
				{// 敵の各パーツの当たり判定
					g_aBullet[nCntBl].bUse = false;

					// 爆発設定
					SETEXPLO setExplo;
					setExplo.pos = g_aBullet[nCntBl].pos;
					setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
					SetExplosion(setExplo);

					// 敵のヒット処理
					HitEnemy(nCntEnemy,BULLET_ATTACK_SNOW);

					// 影の終了
					EndShadow(g_aBullet[nCntBl].nShadowIdx);

					D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
					D3DXVec3Normalize(&patiMove, &patiMove);

					// パーティクル生成
					SetParticle(EFFECTTYPE_TRAJECTORY,	// タイプ
						g_aBullet[nCntBl].pos,			// 位置
						patiMove,						// 重力
						D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// 色
						50,								// 出す量
						60,								// 寿命
						5.0f,							// 大きさ
						3.0f,							// 速度
						false,							// 影の有無
						true							// 加算合成か減算合成か
					);

					// 雪玉が壊れる音
					PlaySound(SOUND_LABEL_SE_BREAKSNOWBALL);

					break;
				}
			}
		}
	}
}

//*****************************
// 雪玉中処理の設定
//*****************************
void SnowBallMidium(int nCntBl)
{
	ENEMY* pEnemy = GetEnemy();	// エネミー取得

	g_aBullet[nCntBl].move.y -= (float)BULLET_GRAVITY;

	g_aBullet[nCntBl].pos.x += g_aBullet[nCntBl].move.x;
	g_aBullet[nCntBl].pos.y += g_aBullet[nCntBl].move.y;
	g_aBullet[nCntBl].pos.z += g_aBullet[nCntBl].move.z;

	g_aBullet[nCntBl].fLife -= 1.0f;

	SetEffect(EFFECTTYPE_TRAJECTORY,		// タイプ
		g_aBullet[nCntBl].pos,				// 位置
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 移動量
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 重力
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// 色
		30,									// 寿命
		25.0f,								// 大きさ
		false,								// 影の仕様有無
		true								// 加算合成
	);

	if (g_aBullet[nCntBl].fLife > 0)
	{
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (g_aBullet[nCntBl].bUse == false)
			{// 弾使ってなかったら	
				break;
			}

			if (pEnemy->bUse == false)
			{// 敵使ってなかったら
				continue;
			}

			for (int nCntPosi = 0; nCntPosi < pEnemy->charParam.nNumModel; nCntPosi++)
			{
				if (CollisionSphere(&g_aBullet[nCntBl].pos, &pEnemy->aColiPoint[nCntPosi].pos, g_aBullet[nCntBl].fWidth, pEnemy->aColiPoint[nCntPosi].fRadius + 20, false))
				{// 敵の各パーツの当たり判定
					g_aBullet[nCntBl].bUse = false;

					// 爆発設定
					SETEXPLO setExplo;
					setExplo.pos = g_aBullet[nCntBl].pos;
					setExplo.size = D3DXVECTOR3(40.0f, 40.0f, 0.0f);

					SetExplosion(setExplo);

					// 敵のヒット処理
					HitEnemy(nCntEnemy, BULLET_ATTACK_SNOW_MIDIUM);

					// 影の終了
					EndShadow(g_aBullet[nCntBl].nShadowIdx);

					D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
					D3DXVec3Normalize(&patiMove, &patiMove);

					// パーティクル生成
					SetParticle(EFFECTTYPE_TRAJECTORY,	// タイプ
						g_aBullet[nCntBl].pos,			// 位置
						patiMove,						// 重力
						D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// 色
						50,								// 出す量
						60,								// 寿命
						10.0f,							// 大きさ
						4.0f,							// 速度
						false,							// 影の有無
						true							// 加算合成か減算合成か
					);

					// 雪玉が壊れる音
					PlaySound(SOUND_LABEL_SE_BREAKSNOWBALL_MIDI);

					break;
				}
			}
		}

		if (CollisionBlock(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move) || g_aBullet[nCntBl].fLife <= 0.0f)
		{// ブロックとの当たり判定
			g_aBullet[nCntBl].bUse = false;

			// 爆発設定
			SETEXPLO setExplo;
			setExplo.pos = g_aBullet[nCntBl].pos;
			setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);

			SetExplosion(setExplo);

			// 影の終了
			EndShadow(g_aBullet[nCntBl].nShadowIdx);

			D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
			D3DXVec3Normalize(&patiMove, &patiMove);

			// パーティクル生成
			SetParticle(EFFECTTYPE_TRAJECTORY,	// タイプ
				g_aBullet[nCntBl].pos,			// 位置
				patiMove,						// 重力
				D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// 色
				50,								// 出す量
				60,								// 寿命
				10.0f,							// 大きさ
				4.0f,							// 速度
				false,							// 影の有無
				true							// 加算合成か減算合成か
			);

			// 雪玉が壊れる音
			PlaySound(SOUND_LABEL_SE_BREAKSNOWBALL_MIDI);
		}
	}
}

//*****************************
// 雪玉大処理の設定
//*****************************
void SnowBallBig(int nCntBl)
{
	ENEMY* pEnemy = GetEnemy();	// エネミー取得

	BLOCKCOLLISION blockColiision;

	g_aBullet[nCntBl].move.y -= (float)BULLET_GRAVITY;


	g_aBullet[nCntBl].pos.y += g_aBullet[nCntBl].move.y;
	blockColiision = CollisionBlockBullet(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move,20.0f);

	g_aBullet[nCntBl].pos.x += g_aBullet[nCntBl].move.x;
	blockColiision = CollisionBlockBullet(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move,20.0f);

	g_aBullet[nCntBl].pos.z += g_aBullet[nCntBl].move.z;
	blockColiision = CollisionBlockBullet(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move,20.0f);

	g_aBullet[nCntBl].fLife -= 1.0f;

	SetEffect(EFFECTTYPE_TRAJECTORY,		// タイプ
		g_aBullet[nCntBl].pos,				// 位置
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 移動量
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 重力
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// 色
		30,									// 寿命
		30.0f,								// 大きさ
		false,								// 影の仕様有無
		true								// 加算合成
	);

	if (blockColiision.nHitfase == BLOCKFACETYPE_TOP)
	{// 上面に当たったら
		g_aBullet[nCntBl].pos.y += 10.0f;
	}

	if (blockColiision.nHitfase == BLOCKFACETYPE_SIDE || g_aBullet[nCntBl].fLife <= 0.0f)
	{// 壁に当たってたら
		g_aBullet[nCntBl].bUse = false;

		// 爆発設定
		SETEXPLO setExplo;
		setExplo.pos = g_aBullet[nCntBl].pos;
		setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
		SetExplosion(setExplo);

		// 影の終了
		EndShadow(g_aBullet[nCntBl].nShadowIdx);

		D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
		D3DXVec3Normalize(&patiMove, &patiMove);

		// パーティクル生成
		SetParticle(EFFECTTYPE_TRAJECTORY,	// タイプ
			g_aBullet[nCntBl].pos,			// 位置
			patiMove,						// 重力
			D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// 色
			50,								// 出す量
			60,								// 寿命
			15.0f,							// 大きさ
			5.0f,							// 速度
			false,							// 影の有無
			true							// 加算合成か減算合成か
		);

		// 雪玉が壊れる音
		PlaySound(SOUND_LABEL_SE_BREAKSNOWBALL_BIG);
	}

	if (g_aBullet[nCntBl].fLife > 0)
	{// 生きてたら
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (g_aBullet[nCntBl].bUse == false)
			{// 弾使ってなかったら
				break;
			}

			if (pEnemy->bUse == false)
			{// 敵使ってなかったら
				continue;
			}

			for (int nCntPosi = 0; nCntPosi < pEnemy->charParam.nNumModel; nCntPosi++)
			{
				if (CollisionSphere(&g_aBullet[nCntBl].pos, &pEnemy->aColiPoint[nCntPosi].pos, g_aBullet[nCntBl].fWidth, pEnemy->aColiPoint[nCntPosi].fRadius + 20, false))
				{// 敵の各パーツの当たり判定
					g_aBullet[nCntBl].bUse = false;

					// 爆発設定
					SETEXPLO setExplo;
					setExplo.pos = g_aBullet[nCntBl].pos;
					setExplo.size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
					SetExplosion(setExplo);

					// 敵のヒット処理
					HitEnemy(nCntEnemy, BULLET_ATTACK_SNOW_BIG);

					// 影の終了
					EndShadow(g_aBullet[nCntBl].nShadowIdx);

					D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
					D3DXVec3Normalize(&patiMove, &patiMove);

					// パーティクル生成
					SetParticle(EFFECTTYPE_TRAJECTORY,	// タイプ
						g_aBullet[nCntBl].pos,			// 位置
						patiMove,						// 重力
						D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),	// 色
						50,								// 出す量
						60,								// 寿命
						15.0f,							// 大きさ
						5.0f,							// 速度
						false,							// 影の有無
						true							// 加算合成か減算合成か
					);

					// 雪玉が壊れる音
					PlaySound(SOUND_LABEL_SE_BREAKSNOWBALL_BIG);

					break;
				}
			}
		}
	}
}

//*****************************
// 氷玉処理の設定
//*****************************
void IceBall(int nCntBl)
{
	ENEMY* pEnemy = GetEnemy();	// エネミー取得

	BLOCKCOLLISION blockColi;

	// 重力
	g_aBullet[nCntBl].move.y -= (float)BULLET_GRAVITY;
	
	// 移動量追加
	g_aBullet[nCntBl].pos.x += g_aBullet[nCntBl].move.x;
	g_aBullet[nCntBl].pos.y += g_aBullet[nCntBl].move.y;
	g_aBullet[nCntBl].pos.z += g_aBullet[nCntBl].move.z;

	// 寿命減らす
	g_aBullet[nCntBl].fLife -= 1.0f;

	SetEffect(EFFECTTYPE_TRAJECTORY,		// タイプ
		g_aBullet[nCntBl].pos,				// 位置
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 移動量
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 重力
		D3DXCOLOR(0.3f, 0.3f, 1.0f, 1.0f),	// 色
		30,									// 寿命
		20.0f,								// 大きさ
		false,								// 影の仕様有無
		true								// 加算合成
	);

	// ブロックとのの当たり判定
	blockColi = CollisionBlockBullet(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move,10.0f);

	if (blockColi.bHit == true || g_aBullet[nCntBl].fLife <= 0.0f)
	{// 当たってたら
		// 弾を使えなくする
		g_aBullet[nCntBl].bUse = false;

		// ブロック破壊
		BlockDestroy(blockColi.nCnt);

		// 爆発設定
		SETEXPLO setExplo;
		setExplo.pos = g_aBullet[nCntBl].pos;
		setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
		SetExplosion(setExplo);

		// 影の終了
		EndShadow(g_aBullet[nCntBl].nShadowIdx);

		D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
		D3DXVec3Normalize(&patiMove, &patiMove);

		// パーティクル生成
		SetParticle(EFFECTTYPE_TRAJECTORY,	// タイプ
			g_aBullet[nCntBl].pos,			// 位置
			patiMove,						// 重力
			D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),	// 色
			50,								// 出す量
			60,								// 寿命
			5.0f,							// 大きさ
			2.0f,							// 速度
			false,							// 影の有無
			true							// 加算合成か減算合成か
		);

		// 氷玉が壊れる音
		PlaySound(SOUND_LABEL_SE_BREAKICEBALL);
	}

	if (g_aBullet[nCntBl].fLife > 0)
	{// 生きてたら
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (pEnemy->bUse == false)
			{// 敵使ってなかったら
				continue;
			}

			for (int nCntPosi = 0; nCntPosi < pEnemy->charParam.nNumModel; nCntPosi++)
			{// モデル分回す
				if (CollisionSphere(&g_aBullet[nCntBl].pos, &pEnemy->aColiPoint[nCntPosi].pos, g_aBullet[nCntBl].fWidth, pEnemy->aColiPoint[nCntPosi].fRadius + 20, false))
				{// 敵の各パーツの当たり判定
					// 敵のヒット処理
					HitEnemy(nCntEnemy, BULLET_ATTACK_ICE);

					// 影の終了
					EndShadow(g_aBullet[nCntBl].nShadowIdx);

					D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
					D3DXVec3Normalize(&patiMove, &patiMove);

					// パーティクル生成
					SetParticle(EFFECTTYPE_TRAJECTORY,	// タイプ
						g_aBullet[nCntBl].pos,			// 位置
						D3DXVECTOR3(0.0f,0.0f,0.0f),	// 重力
						D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),	// 色
						50,								// 出す量
						60,								// 寿命
						10.0f,							// 大きさ
						3.0f,							// 速度
						false,							// 影の有無
						true							// 加算合成か減算合成か
					);

					// 氷玉が壊れる音
					PlaySound(SOUND_LABEL_SE_BREAKICEBALL);

					break;
				}
			}
		}
	}
	else
	{
		// 爆発設定
		SETEXPLO setExplo;
		setExplo.pos = g_aBullet[nCntBl].pos;
		setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
		SetExplosion(setExplo);

		// 影の終了
		EndShadow(g_aBullet[nCntBl].nShadowIdx);
	}
}

//*****************************
// 砂利玉処理の設定
//*****************************
void GravelBall(int nCntBl)
{
	ENEMY* pEnemy = GetEnemy();	// エネミー取得

	g_aBullet[nCntBl].move.y -= (float)BULLET_GRAVITY;

	g_aBullet[nCntBl].pos.x += g_aBullet[nCntBl].move.x;
	g_aBullet[nCntBl].pos.y += g_aBullet[nCntBl].move.y;
	g_aBullet[nCntBl].pos.z += g_aBullet[nCntBl].move.z;

	g_aBullet[nCntBl].fLife -= 1.0f;

	SetEffect(EFFECTTYPE_TRAJECTORY,		// タイプ
		g_aBullet[nCntBl].pos,				// 位置
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 移動量
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 重力
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// 色
		30,									// 寿命
		10.0f,								// 大きさ
		false,								// 影の仕様有無
		false								// 減算合成
	);

	if (CollisionBlock(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move) || g_aBullet[nCntBl].fLife <= 0.0f)
	{// ブロックどうしの当たり判定
		// 弾設定
		SETBULLET setBlt;

		D3DXVECTOR3 vecA = g_aBullet[nCntBl].pos - g_aBullet[nCntBl].posOld;

		// 情報代入
		setBlt.pos = g_aBullet[nCntBl].pos;
		setBlt.size = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
		setBlt.nType = BULLETTYPE_GRAVEL_DIFFUSION;
		setBlt.fLife = 120.0f;
		setBlt.move.x = vecA.x;
		setBlt.move.y = vecA.y;
		setBlt.move.z = vecA.z;

		for (int nCnt = 0; nCnt < 50; nCnt++)
		{
			// 引数にぶち込んでセットする
			SetBullet(g_aBullet[nCntBl].pos, vecA,BULLETTYPE_GRAVEL_DIFFUSION);
		}

		g_aBullet[nCntBl].bUse = false;

		// 爆発設定
		SETEXPLO setExplo;
		setExplo.pos = g_aBullet[nCntBl].pos;
		setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
		SetExplosion(setExplo);

		// 影の終了
		EndShadow(g_aBullet[nCntBl].nShadowIdx);

		// 砂利玉が壊れる音
		PlaySound(SOUND_LABEL_SE_BREAKGRAVELBALL);
	}

	if (g_aBullet[nCntBl].fLife > 0)
	{
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (g_aBullet[nCntBl].bUse == false)
			{// 弾使ってなかったら
				break;
			}

			if (pEnemy->bUse == false)
			{// 敵使ってなかったら
				continue;
			}

			for (int nCntPosi = 0; nCntPosi < pEnemy->charParam.nNumModel; nCntPosi++)
			{
				if (CollisionSphere(&g_aBullet[nCntBl].pos, &pEnemy->aColiPoint[nCntPosi].pos, g_aBullet[nCntBl].fWidth, pEnemy->aColiPoint[nCntPosi].fRadius + 20, false))
				{// 敵の各パーツの当たり判定
					g_aBullet[nCntBl].bUse = false;

					// 爆発設定
					SETEXPLO setExplo;
					setExplo.pos = g_aBullet[nCntBl].pos;
					setExplo.size = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
					SetExplosion(setExplo);

					// 敵のヒット処理
					HitEnemy(nCntEnemy, BULLET_ATTACK_GRAVEL);

					// 影の終了
					EndShadow(g_aBullet[nCntBl].nShadowIdx);

					// 砂利玉が壊れる音
					PlaySound(SOUND_LABEL_SE_BREAKGRAVELBALL);

					break;
				}
			}
		}
	}
}

//*****************************
// 砂利玉処理の設定
//*****************************
void GravelBallDiffusion(int nCntBl)
{
	ENEMY* pEnemy = GetEnemy();	// エネミー取得

	g_aBullet[nCntBl].move.y -= (float)BULLET_GRAVITY;

	g_aBullet[nCntBl].pos.x += g_aBullet[nCntBl].move.x;
	g_aBullet[nCntBl].pos.y += g_aBullet[nCntBl].move.y;
	g_aBullet[nCntBl].pos.z += g_aBullet[nCntBl].move.z;

	g_aBullet[nCntBl].fLife -= 1.0f;

	SetEffect(EFFECTTYPE_TRAJECTORY,		// タイプ
		g_aBullet[nCntBl].pos,				// 位置
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 移動量
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 重力
		D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f),	// 色
		60,									// 寿命
		5.0f,								// 大きさ
		false,								// 影の仕様有無
		false								// 減算合成
	);

	if (CollisionBlock(&g_aBullet[nCntBl].pos, &g_aBullet[nCntBl].posOld, &g_aBullet[nCntBl].move) || g_aBullet[nCntBl].fLife <= 0.0f)
	{// ブロックとの当たり判定
		g_aBullet[nCntBl].bUse = false;

		// 爆発設定
		SETEXPLO setExplo;
		setExplo.pos = g_aBullet[nCntBl].pos;
		setExplo.size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		SetExplosion(setExplo);

		// 影の終了
		EndShadow(g_aBullet[nCntBl].nShadowIdx);

		D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
		D3DXVec3Normalize(&patiMove, &patiMove);

		// パーティクル生成
		SetParticle(EFFECTTYPE_TRAJECTORY,		// タイプ
			g_aBullet[nCntBl].pos,				// 位置
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 重力
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// 色
			50,									// 出す量
			60,									// 寿命
			10.0f,								// 大きさ
			5.0f,								// 速度
			false,								// 影の有無
			false								// 加算合成か減算合成か
		);

		// 砂利玉が壊れる音
		PlaySound(SOUND_LABEL_SE_BREAKGRAVELBALL);
	}

	if (g_aBullet[nCntBl].fLife > 0)
	{
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (g_aBullet[nCntBl].bUse == false)
			{// 弾使ってなかったら
				break;
			}

			if (pEnemy->bUse == false)
			{// 敵使ってなかったら
				continue;
			}

			for (int nCntPosi = 0; nCntPosi < pEnemy->charParam.nNumModel; nCntPosi++)
			{
				if (CollisionSphere(&g_aBullet[nCntBl].pos, &pEnemy->aColiPoint[nCntPosi].pos, g_aBullet[nCntBl].fWidth, pEnemy->aColiPoint[nCntPosi].fRadius + 20, false))
				{// 敵の各パーツの当たり判定
					g_aBullet[nCntBl].bUse = false;

					// 爆発設定
					SETEXPLO setExplo;
					setExplo.pos = g_aBullet[nCntBl].pos;
					setExplo.size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
					SetExplosion(setExplo);

					// 敵のヒット処理
					HitEnemy(nCntEnemy, BULLET_ATTACK_GRAVEL_DIFFSION);

					// 影の終了
					EndShadow(g_aBullet[nCntBl].nShadowIdx);

					D3DXVECTOR3 patiMove = g_aBullet[nCntBl].move;
					D3DXVec3Normalize(&patiMove, &patiMove);

					// パーティクル生成
					SetParticle(EFFECTTYPE_TRAJECTORY,		// タイプ
						g_aBullet[nCntBl].pos,				// 位置
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 重力
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// 色
						50,									// 出す量
						60,									// 寿命
						10.0f,								// 大きさ
						3.0f,								// 速度
						false,								// 影の有無
						false								// 加算合成か減算合成か
					);

					// 砂利玉が壊れる音
					PlaySound(SOUND_LABEL_SE_BREAKGRAVELBALL);

					break;
				}
			}
		}
	}

}

//*****************************
// 雪玉の当たり判定
//*****************************
bool CollisionSpharBullet(int nCnt)
{
	ENEMY *pEnemy = GetEnemy();// エネミーの取得

	bool bCollision = false;
	float fAx_Bx = g_aBullet[nCnt].pos.x - pEnemy->pos.x;
	float fAy_By = g_aBullet[nCnt].pos.y - pEnemy->pos.y;
	float fAz_Bz = g_aBullet[nCnt].pos.z - pEnemy->pos.z;
	float fLength = sqrtf((fAx_Bx * fAx_Bx) + (fAy_By * fAy_By) + (fAz_Bz * fAz_Bz));
	float fRange = 20.0f + 10.0f;

	switch (g_aBullet[nCnt].nType)
	{
	case BULLETTYPE_SNOW_MEDIUM:	// 中玉
		fRange = 20.0f + 15.0f;
		break;

	case BULLETTYPE_SNOW_BIG:	// 大玉
		fRange = 20.0f + 20.0f;
		break;

	case BULLETTYPE_GRAVEL_DIFFUSION:	// 砂利玉拡散弾
		fRange = 20.0f + 5.0f;
		break;
	}

	if (CollisionSphere(&g_aBullet[nCnt].pos, &pEnemy->pos, 10.0f, 20.0f,false))
	{// 当たる判定より短かったら
		bCollision = true;
		//HitEnemy();
	}

	// 結果を返す
	return bCollision;
}