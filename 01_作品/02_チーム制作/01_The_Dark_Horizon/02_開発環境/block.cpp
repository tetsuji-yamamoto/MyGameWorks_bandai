#include "block.h"
#include "player.h"
#include "readtext.h"
#include "writetext.h"
#include "keyboard.h"
#include "edit.h"

// グローバル変数宣言
BLOCK g_aBlock[MAX_BLOCK];		// ブロック情報
BLOCKMANAGER g_blockManager;	// ブロック管理
BLOCKCONTROLLER g_blockCont;	// ブロック操作情報

//********************************************
//ブロックの初期化
//********************************************
void InitBlock(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ブロック管理情報初期化
	g_blockManager.nBlockNum = 0;

	// ブロック捜査情報初期化	
	g_blockCont.nNextBlType = BLOCKTYPE_SNOW;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// 各種変数の初期化
		g_aBlock[nCntBlock].apTextureBlock[0] = {};
		g_aBlock[nCntBlock].pMeshBlock = NULL;
		g_aBlock[nCntBlock].pBuffMatBlock = NULL;
		g_aBlock[nCntBlock].dwNumMatBlock = 0;
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f ,0.0f, 0.0f);
		g_aBlock[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].vtxMaxBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].vtxMinBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].nType = BLOCKTYPE_MAX;
		g_aBlock[nCntBlock].bUse = false;
	}

	ReadText();

	g_blockCont.nCntNowBlock = g_blockManager.nBlockNum - 1;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			int nNumVtx;	// 頂点数
			WORD sizeFVF;	// 頂点フォーマットのサイズデータ
			BYTE* pVtxBuff;	// 頂点バッファのポインタ

			// 頂点数の取得
			nNumVtx = g_aBlock[nCntBlock].pMeshBlock->GetNumVertices();

			// 頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(g_aBlock[nCntBlock].pMeshBlock->GetFVF());

			// 頂点バッファのロック
			g_aBlock[nCntBlock].pMeshBlock->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
			{
				// 頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
				//[頂点座標を比較してモデルの最大最小を取得]

				if (g_aBlock[nCntBlock].vtxMaxBlock.x <= vtx.x)
				{// 最大値X
					g_aBlock[nCntBlock].vtxMaxBlock.x = vtx.x;
				}

				if (g_aBlock[nCntBlock].vtxMaxBlock.y <= vtx.y)
				{// 最大値Y
					g_aBlock[nCntBlock].vtxMaxBlock.y = vtx.y;
				}

				if (g_aBlock[nCntBlock].vtxMaxBlock.z <= vtx.z)
				{// 最大値Z
					g_aBlock[nCntBlock].vtxMaxBlock.z = vtx.z;
				}

				if (g_aBlock[nCntBlock].vtxMinBlock.x >= vtx.x)
				{// 最小値X
					g_aBlock[nCntBlock].vtxMinBlock.x = vtx.x;
				}

				if (g_aBlock[nCntBlock].vtxMinBlock.y >= vtx.y)
				{// 最小値Y
					g_aBlock[nCntBlock].vtxMinBlock.y = vtx.y;
				}

				if (g_aBlock[nCntBlock].vtxMinBlock.z >= vtx.z)
				{// 最小値Z
					g_aBlock[nCntBlock].vtxMinBlock.z = vtx.z;
				}

				// 頂点フォーマットのサイズ分ポインタを進める
				pVtxBuff += sizeFVF;
			}

			// 頂点バッファのアンロック
			g_aBlock[nCntBlock].pMeshBlock->UnlockVertexBuffer();
		}
	}
}

//********************************************
// ブロックの終了処理
//********************************************
void UninitBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// メッシュの破棄
		if (g_aBlock[nCntBlock].pMeshBlock != NULL)
		{
			g_aBlock[nCntBlock].pMeshBlock->Release();
			g_aBlock[nCntBlock].pMeshBlock = NULL;
		}

		// マテリアルの破棄
		if (g_aBlock[nCntBlock].pBuffMatBlock != NULL)
		{
			g_aBlock[nCntBlock].pBuffMatBlock->Release();
			g_aBlock[nCntBlock].pBuffMatBlock = NULL;
		}

		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			// マテリアルの破棄
			if (g_aBlock[nCntBlock].apTextureBlock[nCnt] != NULL)
			{
				g_aBlock[nCntBlock].apTextureBlock[nCnt]->Release();
				g_aBlock[nCntBlock].apTextureBlock[nCnt] = NULL;
			}
		}
	}
}

//********************************************
// ブロックの更新
//********************************************
void UpdateBlock(void)
{
#ifdef _DEBUG
	if (GetEditMode() == EDITMODE_BLOCK)
	{// エディターゲームモードだったら
		BlockControllre();	// ブロック操作
	}

	if (KeyboardTrigger(DIK_DELETE))
	{
		BlockOllDeliete();
		InitBlock();
	}
#endif
}

//********************************************
// ブロックの描画
//********************************************
void DrawBlock(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// 現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{// 使っていたら

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBlock[nCntBlock].mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBlock[nCntBlock].rot.y, g_aBlock[nCntBlock].rot.x, g_aBlock[nCntBlock].rot.z);
			D3DXMatrixMultiply(&g_aBlock[nCntBlock].mtxWorld, &g_aBlock[nCntBlock].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
			D3DXMatrixMultiply(&g_aBlock[nCntBlock].mtxWorld, &g_aBlock[nCntBlock].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBlock[nCntBlock].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].pBuffMatBlock->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].dwNumMatBlock; nCntMat++)
			{
#ifdef _DEBUG
				if (g_blockCont.nCntNowBlock == nCntBlock)
				{
					pMat->MatD3D.Diffuse.a = 0.5f;
				}
#endif

				if (GetEditMode() == EDITMODE_NONE && g_aBlock[nCntBlock].nType == BLOCKTYPE_TERRITRY_POINT)
				{
					D3DXMATERIAL matEX = *pMat;
					matEX.MatD3D.Diffuse.a = 0.0f;

					// マテリアルの設定
					pDevice->SetMaterial(&matEX.MatD3D);
				}
				else
				{
					// マテリアルの設定
					pDevice->SetMaterial(&pMat->MatD3D);
				}

				// テクスチャの設定
				pDevice->SetTexture(0, g_aBlock[nCntBlock].apTextureBlock[nCntMat]);

				// ブロック(パーツの描画)
				g_aBlock[nCntBlock].pMeshBlock->DrawSubset(nCntMat);


			}

			// 保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//********************************************
// ブロックの設定
//********************************************
void SetBlock(SETBLOCK setBlock,bool bFilenameAstr)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{// 使ってなかったら
			// 変数の設定
			g_aBlock[nCntBlock].pos = setBlock.pos;
			g_aBlock[nCntBlock].rot = setBlock.rot;
			g_aBlock[nCntBlock].nType = setBlock.nType;
			if (bFilenameAstr)
			{
				if (setBlock.astr[0] == NULL)
				{
					g_aBlock[nCntBlock].pFilename = &g_blockManager.astr[setBlock.nType][0];
				}
				else
				{
					g_aBlock[nCntBlock].pFilename = &setBlock.astr[0];
				}
			}
			else
			{
				g_aBlock[nCntBlock].pFilename = setBlock.pFilename;

				g_blockCont.nCntNowBlock = nCntBlock;
			}

			g_aBlock[nCntBlock].bUse = true;

			for (int nCnt = 0; nCnt < 256; nCnt++)
			{
				g_aBlock[nCntBlock].astr[nCnt] = setBlock.astr[nCnt];
				if (setBlock.astr[nCnt] == '\n')
				{
					break;
				}
			}

			g_blockManager.nBlockNum++;	// ブロックカウント

			// Xファイルの読み込み
			D3DXLoadMeshFromX(g_aBlock[nCntBlock].pFilename,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_aBlock[nCntBlock].pBuffMatBlock,
				NULL,
				&g_aBlock[nCntBlock].dwNumMatBlock,
				&g_aBlock[nCntBlock].pMeshBlock);

			//マテリアルデータへのポインタを取得
			D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].pBuffMatBlock->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aBlock[nCntBlock].dwNumMatBlock; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{// テクスチャファイルが存在する

					// このファイル名を使用してテクスチャを読み込む
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_aBlock[nCntBlock].apTextureBlock[nCntMat]);
				}
			}

			break;
		}
	}
}

//********************************************
// ブロックとキャラクターの当たり判定
//********************************************
BLOCKCOLLISION CollisionBlockCharacter(D3DXVECTOR3 *pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, int *pBlockType, float fWidth,float fHeight)
{
	BLOCKCOLLISION collision;	// コリジョン情報
	collision.bHit = false;
	collision.nCnt = -1;
	collision.nHitfase = -1;
	collision.nType = -1;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].nType != BLOCKTYPE_TERRITRY_POINT && g_aBlock[nCntBlock].nType != BLOCKTYPE_UDD_SNOW)
		{
			if (g_aBlock[nCntBlock].bUse == false)
			{
				continue;
			}

			if (pPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
				pPos->y + fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
			{// 上下以内
				// 前後ろの当たり判定
				if (pPos->x - fWidth < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
					pPos->x + fWidth > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
				{// Xの幅
					if (pPosOld->z + fWidth <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z &&
						pPos->z + fWidth >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
					{// Zが手前から奥にめり込んだ
						pPos->z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z - fWidth;
						collision.bHit = true;
						collision.nCnt = nCntBlock;
						collision.nHitfase = BLOCKFACETYPE_SIDE;
						collision.nType = g_aBlock[nCntBlock].nType;
					}
					else if (pPosOld->z - fWidth >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
						pPos->z - fWidth <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z)
					{// Zが奥から手前にめり込んだ前
						pPos->z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z + fWidth;
						collision.bHit = true;
						collision.nCnt = nCntBlock;
						collision.nHitfase = BLOCKFACETYPE_SIDE;
						collision.nType = g_aBlock[nCntBlock].nType;
					}
				}

				// 左右のめり込み判定
				if (pPos->z - fWidth < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
					pPos->z + fWidth > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
				{// Zの幅
					if (pPosOld->x + fWidth <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
						pPos->x + fWidth >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
					{// Xが左から右にめり込んだ
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x - fWidth;
						collision.bHit = true;
						collision.nCnt = nCntBlock;
						collision.nHitfase = BLOCKFACETYPE_SIDE;
						collision.nType = g_aBlock[nCntBlock].nType;
					}
					else if (pPosOld->x - fWidth >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
						pPos->x - fWidth <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x)
					{// Xが右から左にめり込んだ
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x + fWidth;
						collision.bHit = true;
						collision.nCnt = nCntBlock;
						collision.nHitfase = BLOCKFACETYPE_SIDE;
						collision.nType = g_aBlock[nCntBlock].nType;
					}
				}
			}

			// Yの当たり判定
			if (pPos->x - fWidth <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
				pPos->x + fWidth >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
				pPos->z - fWidth <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
				pPos->z + fWidth >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
			{// Xの幅内Zの幅内
				if (pPosOld->y >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
					pPos->y <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y)
				{// 上から下
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y;
					pMove->y = 0.0f;
					*pBlockType = g_aBlock[nCntBlock].nType;
					collision.bHit = true;
					collision.nCnt = nCntBlock;
					collision.nHitfase = BLOCKFACETYPE_TOP;
					collision.nType = g_aBlock[nCntBlock].nType;
				}
				else if (pPosOld->y + fHeight <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y &&
					pPos->y + fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
				{// 下から上
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y - fHeight;
					pMove->y = 0.0f;
					collision.bHit = true;
					collision.nCnt = nCntBlock;
					collision.nHitfase = BLOCKFACETYPE_BOTTOM;
					collision.nType = g_aBlock[nCntBlock].nType;
				}
			}
		}
	}
	return collision;
}

//********************************************
// ブロックの当たり判定
//********************************************
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove)
{
	bool bCollision = false;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].nType != BLOCKTYPE_TERRITRY_POINT && g_aBlock[nCntBlock].nType != BLOCKTYPE_UDD_SNOW)
		{
			if (g_aBlock[nCntBlock].bUse == false)
			{
				continue;
			}

			if (pPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
				pPos->y >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
			{// 上下以内
				// 前後ろの当たり判定
				if (pPos->x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
					pPos->x > g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
				{// Xの幅
					if (pPosOld->z <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z &&
						pPos->z >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
					{// Zが手前から奥にめり込んだ
						pPos->z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z;
						bCollision = true;
					}
					else if (pPosOld->z >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
						pPos->z <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z)
					{// Zが奥から手前にめり込んだ前
						pPos->z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z;
						bCollision = true;
					}
				}

				// 左右のめり込み判定
				if (pPos->z < g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
					pPos->z > g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
				{// Zの幅
					if (pPosOld->x <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
						pPos->x >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
					{// Xが左から右にめり込んだ
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x;
						bCollision = true;
					}
					else if (pPosOld->x >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
						pPos->x <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x)
					{// Xが右から左にめり込んだ
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x;
						bCollision = true;
					}
				}
			}

			// Yの当たり判定
			if (pPos->x <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
				pPos->x >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
				pPos->z <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
				pPos->z >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
			{// Xの幅内Zの幅内
				if (pPosOld->y >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
					pPos->y <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y)
				{// 上から下
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y;
					pMove->y = 0.0f;
					bCollision = true;
				}
				else if (pPosOld->y <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y &&
					pPos->y >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
				{// 下から上
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y;
					pMove->y = 0.0f;
					bCollision = true;
				}
			}
		}
	}
	return bCollision;
}

//********************************************
// ブロックの当たり判定
//********************************************
BLOCKCOLLISION CollisionBlockBullet(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove,float fSize)
{
	BLOCKCOLLISION Collision;

	Collision.bHit = false;
	Collision.nCnt = -1;
	Collision.nHitfase = -1;
	Collision.nType = -1;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].nType != BLOCKTYPE_TERRITRY_POINT && g_aBlock[nCntBlock].nType != BLOCKTYPE_UDD_SNOW)
		{
			if (g_aBlock[nCntBlock].bUse == false)
			{
				continue;
			}

			if (pPos->y - fSize < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
				pPos->y + fSize >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
			{// 上下以内
				// 前後ろの当たり判定
				if (pPos->x - fSize< g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
					pPos->x + fSize> g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
				{// Xの幅
					if (pPosOld->z + fSize <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z &&
						pPos->z + fSize >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
					{// Zが手前から奥にめり込んだ
						pPos->z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z + fSize;
						Collision.bHit = true;
						Collision.nCnt = nCntBlock;
						Collision.nHitfase = BLOCKFACETYPE_SIDE;
						Collision.nType = g_aBlock[nCntBlock].nType;
					}
					else if (pPosOld->z - fSize >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
						pPos->z - fSize <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z)
					{// Zが奥から手前にめり込んだ前
						pPos->z = g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z - fSize;
						Collision.bHit = true;
						Collision.nCnt = nCntBlock;
						Collision.nHitfase = BLOCKFACETYPE_SIDE;
						Collision.nType = g_aBlock[nCntBlock].nType;
					}
				}

				// 左右のめり込み判定
				if (pPos->z - fSize< g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
					pPos->z + fSize> g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
				{// Zの幅
					if (pPosOld->x + fSize <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
						pPos->x + fSize >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x)
					{// Xが左から右にめり込んだ
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x - fSize;
						Collision.bHit = true;
						Collision.nCnt = nCntBlock;
						Collision.nHitfase = BLOCKFACETYPE_SIDE;
						Collision.nType = g_aBlock[nCntBlock].nType;
					}
					else if (pPosOld->x - fSize >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
						pPos->x - fSize <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x)
					{// Xが右から左にめり込んだ
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x + fSize;
						Collision.bHit = true;
						Collision.nCnt = nCntBlock;
						Collision.nHitfase = BLOCKFACETYPE_SIDE;
						Collision.nType = g_aBlock[nCntBlock].nType;
					}
				}
			}

			// Yの当たり判定
			if (pPos->x - fSize <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMaxBlock.x &&
				pPos->x + fSize >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].vtxMinBlock.x &&
				pPos->z - fSize <= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMaxBlock.z &&
				pPos->z + fSize >= g_aBlock[nCntBlock].pos.z + g_aBlock[nCntBlock].vtxMinBlock.z)
			{// Xの幅内Zの幅内
				if (pPosOld->y - fSize >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y &&
					pPos->y - fSize < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y)
				{// 上から下
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMaxBlock.y + fSize;
					pMove->y = 0.0f;
					Collision.bHit = true;
					Collision.nCnt = nCntBlock;
					Collision.nHitfase = BLOCKFACETYPE_TOP;
					Collision.nType = g_aBlock[nCntBlock].nType;
				}
				else if (pPosOld->y + fSize <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y &&
					pPos->y + fSize >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y)
				{// 下から上
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].vtxMinBlock.y - fSize;
					pMove->y = 0.0f;
					Collision.bHit = true;
					Collision.nCnt = nCntBlock;
					Collision.nHitfase = BLOCKFACETYPE_BOTTOM;
					Collision.nType = g_aBlock[nCntBlock].nType;
				}
			}
		}
	}
	return Collision;
}

//********************************************
// ブロックだけど球の判定
//********************************************
BLOCKCOLLISION CollisionBlockSpher(D3DXVECTOR3 posA, float fSizeA, int nBreakType, bool bBreak)
{
	BLOCKCOLLISION collision;
	collision.bHit = false;
	collision.nCnt = -1;
	collision.nHitfase = -1;
	collision.nType = -1;
	float fRange = fSizeA + 40.0f;		// 半径と半径を足した値
	D3DXVECTOR3 vecA;					// ベクトルA

	// 距離を求める
	float fLength = sqrtf((vecA.x * vecA.x) + (vecA.y * vecA.y) + (vecA.z * vecA.z));

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (collision.bHit == true)
		{
			continue;
		}

		if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].nType == nBreakType)
		{
			vecA = g_aBlock[nCntBlock].pos - posA;
			fLength = sqrtf((vecA.x * vecA.x) + (vecA.y * vecA.y) + (vecA.z * vecA.z));

			if (fLength <= fRange)
			{// 短かったら
				collision.bHit = true;
				collision.nCnt = nCntBlock;
				collision.nHitfase = -1;
				collision.nType = g_aBlock[nCntBlock].nType;

				if (bBreak && nBreakType == g_aBlock[nCntBlock].nType)
				{// 壊して良かったら
					g_aBlock[nCntBlock].bUse = false;
				}
			}
		}
	}

	// 結果を返す
	return collision;
}

//********************************************
// ブロックの破壊
//********************************************
void BlockDestroy(int nCnt)
{
	if (g_aBlock[nCnt].nType == BLOCKTYPE_WALL)
	{// 壁なら破壊できるよ
		g_aBlock[nCnt].bUse = false;
	}
}

//********************************************
// ブロックの取得
//********************************************
BLOCK* GetBlock(void)
{
	return &g_aBlock[0];
}

//********************************************
// ブロック操作の取得
//********************************************
BLOCKCONTROLLER* GetBlockController(void)
{
	return &g_blockCont;
}

//********************************************
// ブロック管理の取得
//********************************************
BLOCKMANAGER* GetBlockManager(void)
{
	return &g_blockManager;
}

//********************************************
// ブロック全部消す
//********************************************
void BlockOllDeliete(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].bUse = false;
		g_blockManager.nBlockNum--;
	}
}

//********************************************
// ブロック探す
//********************************************
BLOCK BlockSearch(BLOCKTYPE type,int nNumber)
{
	BLOCK block;	// ブロック情報
	int nCntEX = 0;

	block.apTextureBlock[0] = {};
	block.pMeshBlock = NULL;
	block.pBuffMatBlock = NULL;
	block.dwNumMatBlock = 0;
	block.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	block.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	block.vtxMaxBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	block.vtxMinBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	block.nType = BLOCKTYPE_MAX;
	block.bUse = false;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{// 探す
		 
		if (g_aBlock[nCntBlock].nType == 5)
		{
			int i = 0;
		}

		if (g_aBlock[nCntBlock].bUse == false || g_aBlock[nCntBlock].nType != type)
		{// 使ってなかったらタイプが違う
			continue;
		}

		if (nNumber == nCntEX)
		{// お目当ての番号が合ったら
			block = g_aBlock[nCntBlock];	// 探したものをぶち込む
			break;
		}

		nCntEX++;
	}

	// 結果を返す
	return block;
}

//********************************************
// ブロック操作
//********************************************
void BlockControllre(void)
{
#ifdef _DEBUG
	if (GetEditMode() != EDITMODE_BLOCK)
	{
		return;
	}

#endif

	if (KeyboardTrigger(DIK_RSHIFT))
	{// ブロックを新しく配置

		int OldNumCntBl = g_blockCont.nCntNowBlock;

		for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (g_aBlock[nCntBlock].bUse == false)
			{
				g_blockCont.nCntNowBlock = nCntBlock;
				break;
			}
		}

		//マテリアルデータへのポインタを取得
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_aBlock[OldNumCntBl].pBuffMatBlock->GetBufferPointer();

		pMat->MatD3D.Diffuse.a = 1.0f;

		SETBLOCK setb;
		setb.nType = g_blockCont.nNextBlType;

		switch (setb.nType)
		{
		case BLOCKTYPE_SNOW:
			setb.pFilename = FILE_XFILE_BLOCK_SNOW;
			break;

		case BLOCKTYPE_ICE:
			setb.pFilename = FILE_XFILE_BLOCK_ICE;
			break;

		case BLOCKTYPE_GRAVEL:
			setb.pFilename = FILE_XFILE_BLOCK_GRAVEL;
			break;

		case BLOCKTYPE_WALL:
			setb.pFilename = FILE_XFILE_BLOCK_WALL;
			break;

		case BLOCKTYPE_WALL_ADULT:
			setb.pFilename = FILE_XFILE_BLOCK_WALL_ADULT;
			break;

		case BLOCKTYPE_TERRITRY_POINT:
			setb.pFilename = FILE_XFILE_TERRITORYPOINT;
			break;

		case BLOCKTYPE_UDD_SNOW:
			setb.pFilename = FILE_XFILE_UDD_SNOW;
			break;
		}

		setb.pos = g_aBlock[OldNumCntBl].pos;
		setb.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SetBlock(setb, false);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_aBlock[g_blockCont.nCntNowBlock].pBuffMatBlock->GetBufferPointer();

		pMat->MatD3D.Diffuse.a = 0.5f;
	}
	else if (KeyboardTrigger(DIK_RIGHT))
	{// 次に配置するブロックの種類を変える

		g_aBlock[g_blockCont.nCntNowBlock].bUse = false;

		g_blockCont.nNextBlType++;

		if (g_blockCont.nNextBlType >= BLOCKTYPE_MAX)
		{// 上限行ったら
			g_blockCont.nNextBlType = 0;
		}


		SETBLOCK setb;
		setb.nType = g_blockCont.nNextBlType;

		switch (setb.nType)
		{
		case BLOCKTYPE_SNOW:
			setb.pFilename = FILE_XFILE_BLOCK_SNOW;
			break;

		case BLOCKTYPE_ICE:
			setb.pFilename = FILE_XFILE_BLOCK_ICE;
			break;

		case BLOCKTYPE_GRAVEL:
			setb.pFilename = FILE_XFILE_BLOCK_GRAVEL;
			break;

		case BLOCKTYPE_WALL:
			setb.pFilename = FILE_XFILE_BLOCK_WALL;
			break;

		case BLOCKTYPE_WALL_ADULT:
			setb.pFilename = FILE_XFILE_BLOCK_WALL_ADULT;
			break;

		case BLOCKTYPE_TERRITRY_POINT:
			setb.pFilename = FILE_XFILE_TERRITORYPOINT;
			break;

		case BLOCKTYPE_UDD_SNOW:
			setb.pFilename = FILE_XFILE_UDD_SNOW;
			break;
		}

		setb.pos = g_aBlock[g_blockCont.nCntNowBlock].pos;
		setb.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SetBlock(setb, false);
	}

	if (KeyboardTrigger(DIK_UP))
	{
		// マテリアルデータへのポインタ
		D3DXMATERIAL* pMat;
		int nCntBlock = g_blockCont.nCntNowBlock;

		while (1)
		{
			if (g_aBlock[nCntBlock].bUse)
			{
				if (nCntBlock == g_blockCont.nCntNowBlock)
				{
					nCntBlock++;

					if (nCntBlock >= MAX_BLOCK)
					{// ゼロ以下になったら
						nCntBlock = 0;
					}
					continue;
				}
				else
				{
					// マテリアルデータへのポインタを取得
					pMat = (D3DXMATERIAL*)g_aBlock[g_blockCont.nCntNowBlock].pBuffMatBlock->GetBufferPointer();

					pMat->MatD3D.Diffuse.a = 1.0f;
				}

				g_blockCont.nCntNowBlock = nCntBlock;

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_aBlock[g_blockCont.nCntNowBlock].pBuffMatBlock->GetBufferPointer();

				pMat->MatD3D.Diffuse.a = 0.5f;

				break;
			}

			nCntBlock++;

			if (nCntBlock >= MAX_BLOCK)
			{// ゼロ以下になったら
				nCntBlock = 0;
			}
		}
	}
	else if (KeyboardTrigger(DIK_DOWN))
	{
		// マテリアルデータへのポインタ
		D3DXMATERIAL* pMat;
		int nCntBlock = g_blockCont.nCntNowBlock;

		while (1)
		{
			if (g_aBlock[nCntBlock].bUse)
			{
				if (nCntBlock == g_blockCont.nCntNowBlock)
				{
					nCntBlock--;
					if (nCntBlock < 0)
					{// ゼロ以下になったら
						nCntBlock = MAX_BLOCK;
					}
					continue;
				}
				else
				{
					// マテリアルデータへのポインタを取得
					pMat = (D3DXMATERIAL*)g_aBlock[g_blockCont.nCntNowBlock].pBuffMatBlock->GetBufferPointer();

					pMat->MatD3D.Diffuse.a = 1.0f;
				}

				g_blockCont.nCntNowBlock = nCntBlock;

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_aBlock[g_blockCont.nCntNowBlock].pBuffMatBlock->GetBufferPointer();

				pMat->MatD3D.Diffuse.a = 0.5f;

				break;
			}

			nCntBlock--;

			if (nCntBlock < 0)
			{// ゼロ以下になったら
				nCntBlock = MAX_BLOCK;
			}

		}
	}

	if (KeyboardTrigger(DIK_BACK) && g_blockManager.nBlockNum > 1)
	{
		g_aBlock[g_blockCont.nCntNowBlock].bUse = false;

		for (int nCntBlock = MAX_BLOCK - 1; nCntBlock >= 0; nCntBlock--)
		{
			if (g_aBlock[nCntBlock].bUse)
			{
				g_blockCont.nCntNowBlock = nCntBlock;

				// マテリアルデータへのポインタを取得
				D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_aBlock[nCntBlock].pBuffMatBlock->GetBufferPointer();

				pMat->MatD3D.Diffuse.a = 0.5f;

				g_blockManager.nBlockNum--;// 総数を減らす
				break;
			}
		}
	}

	if (KeyboardTrigger(DIK_RETURN))
	{
		for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (g_aBlock[nCntBlock].bUse)
			{
				if (nCntBlock == g_blockCont.nCntNowBlock)
				{
					continue;
				}

				g_aBlock[nCntBlock].bUse = false;

				g_blockManager.nBlockNum--;// 総数を減らす
			}
		}
	}

	if (KeyboardTrigger(DIK_W))
	{
		g_aBlock[g_blockCont.nCntNowBlock].pos.z += 80.0f;
	}

	if (KeyboardTrigger(DIK_A))
	{
		g_aBlock[g_blockCont.nCntNowBlock].pos.x -= 80.0f;
	}

	if (KeyboardTrigger(DIK_S))
	{
		g_aBlock[g_blockCont.nCntNowBlock].pos.z -= 80.0f;
	}

	if (KeyboardTrigger(DIK_D))
	{
		g_aBlock[g_blockCont.nCntNowBlock].pos.x += 80.0f;
	}

	if (KeyboardTrigger(DIK_Q))
	{
		g_aBlock[g_blockCont.nCntNowBlock].pos.y += 80.0f;
	}
	else if (KeyboardTrigger(DIK_E))
	{
		g_aBlock[g_blockCont.nCntNowBlock].pos.y -= 80.0f;
	}
}