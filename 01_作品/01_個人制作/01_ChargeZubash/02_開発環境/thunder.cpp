#include "main.h"
#include "thunder.h"
#include "particle.h"
#include "effect.h"
#include "block.h"
#include "player.h"
#include "charge.h"
#include "sound.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_aPTextureThunder[THUNDERTYPE_MAX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffThunder = NULL;				//頂点バッファへのポインタ
THUNDER g_aThunder[MAX_THUNDER];								//雷ポリゴンの情報
int nCntThunderLight;											//落ちるまでの間

//======================================
//雷初期化
//======================================
void InitThunder(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	int nCntThunder;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_THUNDER, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffThunder,
		NULL);

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffThunder->Lock(0, 0, (void**)&pVtx, 0);

	nCntThunderLight = 0;

	//雷情報を初期化
	for (nCntThunder = 0; nCntThunder < MAX_THUNDER; nCntThunder++)
	{
		g_aThunder[nCntThunder].pFileName = NULL;
		g_aThunder[nCntThunder].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aThunder[nCntThunder].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aThunder[nCntThunder].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aThunder[nCntThunder].col = D3DXCOLOR(RGBA_FULLCOLOR);
		g_aThunder[nCntThunder].nType = THUNDERTYPE_NOMAL;
		g_aThunder[nCntThunder].nThunderx = 0;
		g_aThunder[nCntThunder].nDirection = THUNDERDIRECT_XSELECT;
		g_aThunder[nCntThunder].nCntTiming = 0;
		g_aThunder[nCntThunder].nCntStrikeTime = 0;
		g_aThunder[nCntThunder].nEPower = 2;
		g_aThunder[nCntThunder].fThunderHeight = 0.0f;
		g_aThunder[nCntThunder].fThunderWidth = 0.0f;
		g_aThunder[nCntThunder].bUse = false;
		g_aThunder[nCntThunder].bHit = false;
		g_aThunder[nCntThunder].bFell = false;

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
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを四つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffThunder->Unlock();
}
//======================================
//雷終了
//======================================
void UninitThunder(void)
{
	for (int nCntThunder = 0; nCntThunder < THUNDERTYPE_MAX; nCntThunder++)
	{
		//テクスチャの破棄
		if (g_aPTextureThunder[nCntThunder] != NULL)
		{
			g_aPTextureThunder[nCntThunder]->Release();
			g_aPTextureThunder[nCntThunder] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffThunder != NULL)
	{
		g_pVtxBuffThunder->Release();
		g_pVtxBuffThunder = NULL;
	}
}
//======================================
//雷更新
//======================================
void UpdateThunder(void)
{
	VERTEX_2D* pVtx;

	//発生までのカウントを加算
	nCntThunderLight--;

	if (nCntThunderLight <= 0)
	{//一定時間たったら

		nCntThunderLight = (rand() % 120) + 60;

		//雷を設定
		SetThunder(FILE_TEX_THUNDER, THUNDERTYPE_NOMAL);
	}

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffThunder->Lock(0, 0, (void**)&pVtx, 0);

	//使っている雷を更新していく
	for (int nCntThunder = 0; nCntThunder < MAX_THUNDER; nCntThunder++)
	{
		if (g_aThunder[nCntThunder].bUse == true)
		{//使っていたら
			//落雷
			LightningStrike(nCntThunder);

			//位置
			pVtx[0].pos.x = g_aThunder[nCntThunder].pos.x - g_aThunder[nCntThunder].fThunderWidth;
			pVtx[0].pos.y = g_aThunder[nCntThunder].pos.y - g_aThunder[nCntThunder].fThunderHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aThunder[nCntThunder].pos.x + g_aThunder[nCntThunder].fThunderWidth;
			pVtx[1].pos.y = g_aThunder[nCntThunder].pos.y - g_aThunder[nCntThunder].fThunderHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aThunder[nCntThunder].pos.x - g_aThunder[nCntThunder].fThunderWidth;
			pVtx[2].pos.y = g_aThunder[nCntThunder].pos.y;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aThunder[nCntThunder].pos.x + g_aThunder[nCntThunder].fThunderWidth;
			pVtx[3].pos.y = g_aThunder[nCntThunder].pos.y;
			pVtx[3].pos.z = 0.0f;

			//頂点カラーの設定
			pVtx[0].col = g_aThunder[nCntThunder].col;
			pVtx[1].col = g_aThunder[nCntThunder].col;
			pVtx[2].col = g_aThunder[nCntThunder].col;
			pVtx[3].col = g_aThunder[nCntThunder].col;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffThunder->Unlock();

}
//======================================
//雷描画
//======================================
void DrawThunder(void)
{
	int nCntThunder;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffThunder, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//雷の描画
	for (nCntThunder = 0; nCntThunder < MAX_THUNDER; nCntThunder++)
	{
		if (g_aThunder[nCntThunder].bUse == true)
		{//雷が使用されている

			//テクスチャの設定
			pDevice->SetTexture(0, g_aPTextureThunder[g_aThunder[nCntThunder].nType]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntThunder,						//描画する最初の頂点インデックス
				2);
		}
	}
}

//======================================
//雷設定
//======================================
void SetThunder(const char* pFileName, THUNDERTYPE type)
{

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffThunder->Lock(0, 0, (void**)&pVtx, 0);

	//雷情報を初期化
	for (int nCntThunder = 0; nCntThunder < MAX_THUNDER; nCntThunder++)
	{
		if (g_aThunder[nCntThunder].bUse == false)
		{
			g_aThunder[nCntThunder].pFileName = pFileName;
			g_aThunder[nCntThunder].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aThunder[nCntThunder].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aThunder[nCntThunder].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aThunder[nCntThunder].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			g_aThunder[nCntThunder].nType = type;
			g_aThunder[nCntThunder].nCntTiming = 0;
			g_aThunder[nCntThunder].nCntStrikeTime = 0;
			g_aThunder[nCntThunder].nEPower = 2;
			g_aThunder[nCntThunder].fThunderWidth = THUNDER_WIDTH;
			g_aThunder[nCntThunder].fThunderHeight = SCREEN_HEIGHT;
			g_aThunder[nCntThunder].bUse = true;
			g_aThunder[nCntThunder].bHit = false;
			g_aThunder[nCntThunder].bFell = false;

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				g_aThunder[nCntThunder].pFileName,
				&g_aPTextureThunder[g_aThunder[nCntThunder].nType]);

			//位置
			pVtx[0].pos.x = g_aThunder[nCntThunder].pos.x - g_aThunder[nCntThunder].fThunderWidth;
			pVtx[0].pos.y = g_aThunder[nCntThunder].pos.y - g_aThunder[nCntThunder].fThunderHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aThunder[nCntThunder].pos.x + g_aThunder[nCntThunder].fThunderWidth;
			pVtx[1].pos.y = g_aThunder[nCntThunder].pos.y - g_aThunder[nCntThunder].fThunderHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aThunder[nCntThunder].pos.x - g_aThunder[nCntThunder].fThunderWidth;
			pVtx[2].pos.y = g_aThunder[nCntThunder].pos.y;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aThunder[nCntThunder].pos.x + g_aThunder[nCntThunder].fThunderWidth;
			pVtx[3].pos.y = g_aThunder[nCntThunder].pos.y;
			pVtx[3].pos.z = 0.0f;

			//頂点カラーの設定
			pVtx[0].col = g_aThunder[nCntThunder].col;
			pVtx[1].col = g_aThunder[nCntThunder].col;
			pVtx[2].col = g_aThunder[nCntThunder].col;
			pVtx[3].col = g_aThunder[nCntThunder].col;

			break;
		}
		pVtx += 4;//頂点データのポインタを四つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffThunder->Unlock();
}

//======================================
//落雷lightning strike
//======================================
void LightningStrike(int nCntThunder)
{
	//前の位置を更新
	g_aThunder[nCntThunder].posOld = g_aThunder[nCntThunder].pos;

	//演出順に処理
	switch (g_aThunder[nCntThunder].nDirection)
	{
	case THUNDERDIRECT_XSELECT:
		//落ちる場所を決める
		SelectStrike(nCntThunder);
		g_aThunder[nCntThunder].nDirection = THUNDERDIRECT_PREMONISION;
		break;

	case THUNDERDIRECT_YSELECT:
		g_aThunder[nCntThunder].nDirection = THUNDERDIRECT_PREMONISION;
		break;

	case THUNDERDIRECT_PREMONISION:
		//予感

		g_aThunder[nCntThunder].pos.y += SCREEN_HEIGHT / 60;

		//パーティクル生成
		SetParticle(D3DXVECTOR3(g_aThunder[nCntThunder].pos.x, g_aThunder[nCntThunder].pos.y, 0.0f),	//位置
			D3DXCOLOR(1.0f, 0.8f, 0.8f, 1.0f),			//色
			EFFECTTYPE_THUNDER,	//種類
			1,					//出す量
			100,				//出す角度
			2.0f,				//速さ
			0.1f,				//移動量減少数
			4.0f,				//ポリゴンサイズ
			0.001f,				//ポリゴンサイズ減少数
			0.0f,				//狙いの角度
			300,				//寿命
			1.0f,				//最低の移動量
			0.0f,				//幅
			0.0f,				//高さ
			nCntThunder);

		//地面に当たったか調べる
		g_aThunder[nCntThunder].bHit = CollisionBlock(&g_aThunder[nCntThunder].pos, &g_aThunder[nCntThunder].posOld, &g_aThunder[nCntThunder].move, g_aThunder[nCntThunder].fThunderHeight, g_aThunder[nCntThunder].nCntStrikeTime);

		if (g_aThunder[nCntThunder].bHit == true)
		{//当たったら
			g_aThunder[nCntThunder].nDirection = THUNDERDIRECT_FALLING;
		}

		if (g_aThunder[nCntThunder].pos.y >= SCREEN_HEIGHT)
		{//画面下までいったら
			g_aThunder[nCntThunder].nDirection = THUNDERDIRECT_FALLING;
		}

		break;

	case THUNDERDIRECT_FALLING:
		//落雷
		ThunderFalling(nCntThunder);
		break;

	case THUNDERDIRECT_END:
		//終わり
		EndEffect(EFFECTTYPE_THUNDER, nCntThunder);
		g_aThunder[nCntThunder].nDirection = THUNDERDIRECT_XSELECT;
		g_aThunder[nCntThunder].bFell = false;	//落ちた状態終わり
		g_aThunder[nCntThunder].bUse = false;
		break;

	default:
		break;
	}
}

//=================================
//雷の落ちるX座標を決める
//=================================
void SelectStrike(int nCntThunder)
{
	int nSelect = 20;

	//ランダムで算出
	nSelect = rand() % SCREEN_WIDTH;

	//出た数字を代入
	g_aThunder[nCntThunder].pos.x = nSelect;
}

//=================================
//雷の落ちるY座標を決める
//=================================
void ThunderFalling(int nCntThunder)
{
	//タイマーを加算
	g_aThunder[nCntThunder].nCntStrikeTime++;

	if (g_aThunder[nCntThunder].nCntStrikeTime >= 60)
	{//一定時間たったら

		//明度をあげる
		g_aThunder[nCntThunder].col.a += 0.1f;

		if (g_aThunder[nCntThunder].col.a > 1.0f)
		{//明度MAX

			SetParticle(D3DXVECTOR3(g_aThunder[nCntThunder].pos.x, g_aThunder[nCntThunder].pos.y, 0.0f),	//位置
				D3DXCOLOR(1.0f, 0.8f, 0.8f, 1.0f),			//色
				EFFECTTYPE_NOMAL,	//種類
				50,					//出す量
				10,				//出す角度
				60.0f,				//速さ
				0.1f,				//移動量減少数
				5.0f,				//ポリゴンサイズ
				0.001f,				//ポリゴンサイズ減少数
				D3DX_PI * 0.55f,				//狙いの角度
				60.0f,				//寿命
				0.0f,				//最低の移動量
				0.0f,				//幅
				0.0f,				//高さ
				-1);

			SetParticle(D3DXVECTOR3(g_aThunder[nCntThunder].pos.x, g_aThunder[nCntThunder].pos.y, 0.0f),	//位置
				D3DXCOLOR(1.0f, 0.8f, 0.8f, 1.0f),			//色
				EFFECTTYPE_NOMAL,	//種類
				50,					//出す量
				10,					//出す角度
				60.0f,				//速さ
				0.1f,				//移動量減少数
				5.0f,				//ポリゴンサイズ
				0.001f,				//ポリゴンサイズ減少数
				-D3DX_PI * 0.55f,	//狙いの角度
				60.0f,				//寿命
				0.0f,				//最低の移動量
				0.0f,				//幅
				0.0f,				//高さ
				-1);

			g_aThunder[nCntThunder].bFell = true;					//落ちた状態
			g_aThunder[nCntThunder].nCntStrikeTime = 0;				//タイマーをゼロ
			g_aThunder[nCntThunder].nDirection = THUNDERDIRECT_END;	//演出をエンドに
			PlaySound(SOUND_LABEL_THUNDER_SE);
		}
	}
}

//=================================
//雷の当たり判定
//=================================
bool HitThunder(D3DXVECTOR3 pos,float fHeight)
{
	bool bHit = false;//当たってない

	for (int nCntThunder = 0; nCntThunder < MAX_THUNDER; nCntThunder++)
	{//探す
		if (g_aThunder[nCntThunder].bUse == true && g_aThunder[nCntThunder].bFell == true)
		{//使っていたら
			
			if (g_aThunder[nCntThunder].pos.y > pos.y - fHeight &&
				g_aThunder[nCntThunder].pos.x - THUNDER_WIDTH < pos.x &&
				g_aThunder[nCntThunder].pos.x + THUNDER_WIDTH > pos.x)
			{//雷より上にいたら当たる
				bHit = true;
			}
		}
	}

	//値を返す
	return bHit;
}