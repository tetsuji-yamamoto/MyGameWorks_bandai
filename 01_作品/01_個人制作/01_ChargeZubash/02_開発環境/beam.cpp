//#include "beam.h"
//#include "main.h"
//
////グローバル変数宣言
//LPDIRECT3DTEXTURE9 g_pTextureBeam = NULL;//テクスチャへのポインタ
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBeam = NULL;	//頂点バッファへのポインタ
//Beam g_aBeam[MAX_BEAM];//エフェクトの情報
//
////============================================
////エフェクトの初期化処理
////============================================
//void InitBeam(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	int nCntBeam;
//	//デバイスの取得
//	pDevice = GetDevice();
//	//テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\BEAM\\boost.png",
//		&g_pTextureBeam);
//
//	//頂点バッファの生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BEAM, //必要な頂点数
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffBeam,
//		NULL);
//
//	VERTEX_2D* pVtx;
//	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
//	g_pVtxBuffBeam->Lock(0, 0, (void**)&pVtx, 0);
//
//	//エフェクトの情報の初期化
//	for (nCntBeam = 0; nCntBeam < MAX_BEAM; nCntBeam++)
//	{
//		g_aBeam[nCntBeam].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aBeam[nCntBeam].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		g_aBeam[nCntBeam].fWidth = 0.0f;
//		g_aBeam[nCntBeam].fHeight = 0.0f;
//		g_aBeam[nCntBeam].bUse = false;
//
//		pVtx[0].pos.x = g_aBeam[nCntBeam].pos.x - g_aBeam[nCntBeam].fWidth;
//		pVtx[0].pos.y = g_aBeam[nCntBeam].pos.y - 25.0f;
//		pVtx[0].pos.z = 0.0f;
//		pVtx[1].pos.x = g_aBeam[nCntBeam].pos.x + 100.0f;
//		pVtx[1].pos.y = g_aBeam[nCntBeam].pos.y - 25.0f;
//		pVtx[1].pos.z = 0.0f;
//		pVtx[2].pos.x = g_aBeam[nCntBeam].pos.x - 100.0f;
//		pVtx[2].pos.y = g_aBeam[nCntBeam].pos.y + 25.0f;
//		pVtx[2].pos.z = 0.0f;
//		pVtx[3].pos.x = g_aBeam[nCntBeam].pos.x + 100.0f;
//		pVtx[3].pos.y = g_aBeam[nCntBeam].pos.y + 25.0f;
//		pVtx[3].pos.z = 0.0f;
//
//		//rhwの設定
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//
//		//頂点カラーの設定
//		pVtx[0].col = g_aBeam[nCntBeam].col;
//		pVtx[1].col = g_aBeam[nCntBeam].col;
//		pVtx[2].col = g_aBeam[nCntBeam].col;
//		pVtx[3].col = g_aBeam[nCntBeam].col;
//
//		//テクスチャ座標の設定
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;//頂点データのポインタを四つ分進める
//	}
//	//頂点バッファをアンロックする
//	g_pVtxBuffBeam->Unlock();
//}
////============================================
////エフェクトの終了処理
////============================================
//void UninitBeam(void)
//{
//	//テクスチャの破棄
//	if (g_pTextureBeam != NULL)
//	{
//		g_pTextureBeam->Release();
//		g_pTextureBeam = NULL;
//	}
//	//頂点バッファの破棄
//	if (g_pVtxBuffBeam != NULL)
//	{
//		g_pVtxBuffBeam->Release();
//		g_pVtxBuffBeam = NULL;
//	}
//}
////============================================
////エフェクトの更新処理
////============================================
//void UpdateBeam(void)
//{
//	int nCntBeam;
//
//	VERTEX_2D* pVtx;
//	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
//	g_pVtxBuffBeam->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntBeam = 0; nCntBeam < MAX_BEAM; nCntBeam++)
//	{
//		if (g_aBeam[nCntBeam].bUse == true)
//		{//エフェクトが使用されている
//
//			//頂点座標の設定
//			pVtx[0].pos.x = g_aBeam[nCntBeam].pos.x - g_aBeam[nCntBeam].fRadius;
//			pVtx[0].pos.y = g_aBeam[nCntBeam].pos.y - g_aBeam[nCntBeam].fRadius;
//			pVtx[0].pos.z = 0.0f;
//			pVtx[1].pos.x = g_aBeam[nCntBeam].pos.x + g_aBeam[nCntBeam].fRadius;
//			pVtx[1].pos.y = g_aBeam[nCntBeam].pos.y - g_aBeam[nCntBeam].fRadius;
//			pVtx[1].pos.z = 0.0f;
//			pVtx[2].pos.x = g_aBeam[nCntBeam].pos.x - g_aBeam[nCntBeam].fRadius;
//			pVtx[2].pos.y = g_aBeam[nCntBeam].pos.y + g_aBeam[nCntBeam].fRadius;
//			pVtx[2].pos.z = 0.0f;
//			pVtx[3].pos.x = g_aBeam[nCntBeam].pos.x + g_aBeam[nCntBeam].fRadius;
//			pVtx[3].pos.y = g_aBeam[nCntBeam].pos.y + g_aBeam[nCntBeam].fRadius;
//			pVtx[3].pos.z = 0.0f;
//
//			//頂点カラーの設定
//			pVtx[0].col = g_aBeam[nCntBeam].col;
//			pVtx[1].col = g_aBeam[nCntBeam].col;
//			pVtx[2].col = g_aBeam[nCntBeam].col;
//			pVtx[3].col = g_aBeam[nCntBeam].col;
//		}
//
//		if (g_aBeam[nCntBeam].fLife <= 0.0f)//寿命が尽きた
//		{
//			g_aBeam[nCntBeam].bUse = false;//使用していない状態にする
//		}
//		pVtx += 4;//頂点データのポインタを四つ分進める
//	}
//	//頂点バッファをアンロックする
//	g_pVtxBuffBeam->Unlock();
//}
////============================================
////エフェクトの描画処理
////============================================
//void DrawBeam(void)
//{
//	int nCntBeam;
//
//	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
//	//デバイスの取得
//	pDevice = GetDevice();
//	//頂点バッファをデータストリームに設定
//	pDevice->SetStreamSource(0, g_pVtxBuffBeam, 0, sizeof(VERTEX_2D));
//	//頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//	//αブレンディングを加算合成に設定
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
//	//エフェクトの描画
//	for (nCntBeam = 0; nCntBeam < MAX_BEAM; nCntBeam++)
//	{
//		if (g_aBeam[nCntBeam].bUse == true)
//		{//エフェクトが使用されている
//				//テクスチャの設定
//			pDevice->SetTexture(0, g_pTextureBeam);
//			//ポリゴン描画
//			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
//				4 * nCntBeam,							//描画する最初の頂点インデックス
//				2);
//		}
//	}
//	//αブレンディングを元に戻す
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//}
////============================================
////エフェクトの設定処理
////============================================
//void SetBeam(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, float fPullRadius, float fPullmove, float fLife)
//{
//	int nCntBeam;
//
//	VERTEX_2D* pVtx;
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffBeam->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntBeam = 0; nCntBeam < MAX_BEAM; nCntBeam++)
//	{
//		if (g_aBeam[nCntBeam].bUse == false)
//		{//エフェクトが使用されていない
//			g_aBeam[nCntBeam].pos = pos;
//			g_aBeam[nCntBeam].move = move;
//			g_aBeam[nCntBeam].col = col;
//			g_aBeam[nCntBeam].fRadius = fRadius;
//			g_aBeam[nCntBeam].fPullRadius = fPullRadius;
//			g_aBeam[nCntBeam].fPullmove = fPullmove;
//			g_aBeam[nCntBeam].fLife = fLife;
//			g_aBeam[nCntBeam].bUse = true;//使用している状態にする
//
//			g_aBeam[nCntBeam].fMultiAlpha = g_aBeam[nCntBeam].col.a * (1 / g_aBeam[nCntBeam].fLife);
//
//			//頂点座用の設定
//			pVtx[0].pos.x = g_aBeam[nCntBeam].pos.x - g_aBeam[nCntBeam].fRadius;
//			pVtx[0].pos.y = g_aBeam[nCntBeam].pos.y - g_aBeam[nCntBeam].fRadius;
//			pVtx[0].pos.z = 0.0f;
//			pVtx[1].pos.x = g_aBeam[nCntBeam].pos.x + g_aBeam[nCntBeam].fRadius;
//			pVtx[1].pos.y = g_aBeam[nCntBeam].pos.y - g_aBeam[nCntBeam].fRadius;
//			pVtx[1].pos.z = 0.0f;
//			pVtx[2].pos.x = g_aBeam[nCntBeam].pos.x - g_aBeam[nCntBeam].fRadius;
//			pVtx[2].pos.y = g_aBeam[nCntBeam].pos.y + g_aBeam[nCntBeam].fRadius;
//			pVtx[2].pos.z = 0.0f;
//			pVtx[3].pos.x = g_aBeam[nCntBeam].pos.x + g_aBeam[nCntBeam].fRadius;
//			pVtx[3].pos.y = g_aBeam[nCntBeam].pos.y + g_aBeam[nCntBeam].fRadius;
//			pVtx[3].pos.z = 0.0f;
//
//			break;
//		}
//		pVtx += 4;//頂点データのポインタを四つ分進める
//	}
//	//頂点バッファをアンロックする
//	g_pVtxBuffBeam->Unlock();
//}