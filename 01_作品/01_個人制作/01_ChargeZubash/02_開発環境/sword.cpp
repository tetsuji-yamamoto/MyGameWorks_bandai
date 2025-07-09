//===================================================================================
//
//剣の処理
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

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureSword = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVteBuffSword = NULL;	//頂点バッファへのポインタ
SWORD g_Sword;									//剣の情報
SWORDANIM g_aSwordAnim[SWORDANIMTYPE_MAX];		//剣のアニメーション情報

//====================
//Swordの初期化処理
//====================
void InitSword(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		SWORD_TEX,
		&g_pTextureSword);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVteBuffSword,
		NULL);

	VERTEX_2D* pVtx;

	//ロック
	g_pVteBuffSword->Lock(0, 0, (void**)&pVtx, 0);

	//初期化
	g_Sword.pos = D3DXVECTOR3(600.0f, 400.0f, 0.0f);	//位置
	g_Sword.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色
	g_Sword.TopLeft = D3DXVECTOR2(0.0f,0.0f);			//0
	g_Sword.TopRight = D3DXVECTOR2(0.0f, 0.0f);			//1
	g_Sword.BottomLeft = D3DXVECTOR2(0.0f, 0.0f);		//2
	g_Sword.BottomRight = D3DXVECTOR2(0.0f, 0.0f);		//3
	g_Sword.rectHitBox = {};				//当たり判定の四角
	g_Sword.nMoveCnt = 0;				//攻撃の後隙カウント
	g_Sword.nState = SWORDANIMTYPE_NONE;	//通常状態
	g_Sword.fLength = 0.0f;					//対角線
	g_Sword.fAngle = 0.0f;					//角度
	g_Sword.fLot = 0.0f;					//角度
	g_Sword.fKeepLot = 0.0f;				//キープ角度
	g_Sword.fPositionX = PLAYER_WIDTH;		//剣の位置調整
	g_Sword.bUse = false;					//使用しない
	g_Sword.bHit = false;					//当たらない
	g_Sword.bJustDisCharge = false;			//ジャストじゃない

	//ビームソード
	g_Sword.beamSword.Andercol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Sword.beamSword.Floatcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Sword.beamSword.tracecol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Sword.beamSword.fBSWidth = 0.0f;
	g_Sword.beamSword.fBSHeight = 0.0f;
	g_Sword.beamSword.bBeamSword = false;
	g_Sword.beamSword.bBeamSword = false;	//生成しない

	for (int nCnt = 0;nCnt < SWORDANIMTYPE_MAX;nCnt++)
	{
		g_aSwordAnim[nCnt].nAnimTurn = SWORDATTACK_PREMOVE;	//攻撃状態
		g_aSwordAnim[nCnt].fAnimCnt1 = 0;					//アニメーションカウント1
		g_aSwordAnim[nCnt].fAnimCnt2 = 0;					//アニメーションカウント2
		g_aSwordAnim[nCnt].fAnimCnt3 = 0;					//アニメーションカウント3
		g_aSwordAnim[nCnt].fBetweenLot = 0.0f;				//目的の値から今の値の間の角度
		g_aSwordAnim[nCnt].fDesiredValueLot1 = 0.0f;		//目的の値1
		g_aSwordAnim[nCnt].fDesiredValueLot2 = 0.0f;		//目的の値2
		g_aSwordAnim[nCnt].fDesiredValueLot3 = 0.0f;		//目的の値3
		g_aSwordAnim[nCnt].bSetAnim = false;				//計算するかどうか
	}

	//座標
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
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラー
	pVtx[0].col = g_Sword.col;
	pVtx[1].col = g_Sword.col;
	pVtx[2].col = g_Sword.col;
	pVtx[3].col = g_Sword.col;
	//テクスチャ座標の設定　　
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//アンロック
	g_pVteBuffSword->Unlock();

	SetSword(D3DXVECTOR3(600.0f, 300.0f, 0.0f));
	
}
//====================
//Swordの終了処理
//====================
void UninitSword(void)
{
	//テクスチャの破棄
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
//Swordの更新処理
//====================
void UpdateSword(void)
{
	float fLot = 0.0f; //角度
	float fEMPos = 0.0f;
	D3DXVECTOR3 Epos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 hitSwordpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	Player* pPlayer = GetPlayer();	//プレイヤー情報取得
	ENEMY* pEnemy = GetEnemy();		//エネミー取得

	VERTEX_2D* pVtx;

	//状態による処理
	switch (g_Sword.nState)
	{
		//通常状態--------------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_NONE:
		EquipmentSword();//定位置に戻す

		if (KeyboardTrigger(DIK_E) == true || GetJoypadTrigger(JOYKEY_X) == true)
		{//通常攻撃
			g_Sword.nState = SWORDANIMTYPE_ATTACK;		//攻撃モードに
		}
		else if (KeyboardTrigger(DIK_F) == true || GetJoypadTrigger(JOYKEY_Y) == true)
		{//放出
			g_Sword.nState = SWORDANIMTYPE_DISCHARGE;	//放出モードに
		}
		break;

		//攻撃状態--------------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_ATTACK:
		SetSwordAnim(g_Sword.nState, 7.0f,3.0f,15.0f, D3DX_PI * 0.4f, -D3DX_PI * 0.6f, D3DX_PI * 0.6f);//情報セット
		SwordAnimation(SWORDANIMTYPE_ATTACK);//攻撃アニメーションにする

		//通常攻撃の当たり判定の大きさ
		g_Sword.rectHitBox.bottom = g_Sword.pos.y;
		g_Sword.rectHitBox.left = g_Sword.pos.x;
		g_Sword.rectHitBox.right = sinf(D3DX_PI + fLot) * SWORD_HEIGHT;
		g_Sword.rectHitBox.top = cosf(D3DX_PI - fLot) * SWORD_HEIGHT;
		break;

		//チャージ状態----------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_CHARGE:
		SetSwordAnim(g_Sword.nState, 15.0f, 60.0f, 15.0f, -D3DX_PI * 2.0f, -D3DX_PI * 2.0f, D3DX_PI * 0.3f);	//情報セット
		SwordAnimation(SWORDANIMTYPE_CHARGE);	//チャージアニメーションにする
		if (HitThunder(g_Sword.pos, SWORD_HEIGHT) == true)
		{
			ChargePower(THUNDER_DAMAGE);
		}
		break;

		//放出状態--------------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_DISCHARGE:
		SetSwordAnim(g_Sword.nState, 60.0f,120.0f, 60.0f, D3DX_PI * 2.6f, -D3DX_PI * 0.9f, -D3DX_PI * 0.9f);//情報セット
		SwordAnimation(SWORDANIMTYPE_DISCHARGE);	//放出アニメーションにする
		BeamSwordGeneration(g_aSwordAnim[SWORDANIMTYPE_DISCHARGE].nAnimTurn);	//ビームソード生成

		//ビームソードの当たり判定
		g_Sword.rectHitBox.right = sinf(D3DX_PI + fLot) * g_Sword.beamSword.fBSHeight;
		g_Sword.rectHitBox.top = cosf(D3DX_PI - fLot) * g_Sword.beamSword.fBSHeight;
		break;

		//ジャスト放出----------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_JUSTDISCHARGE:
		SwordAnimation(SWORDANIMTYPE_JUSTDISCHARGE);	//ジャスト放出アニメーションにする
		BeamSwordGeneration(g_aSwordAnim[SWORDANIMTYPE_JUSTDISCHARGE].nAnimTurn);	//ビームソード生成
		break;

	default:
		break;
	}

	//雷との当たり判定
	if (HitThunder(pPlayer->pos, PLAYER_HEIGHT) == true )
	{
		if (g_Sword.nState == SWORDANIMTYPE_DISCHARGE)
		{//放出状態？
			if (g_aSwordAnim[SWORDANIMTYPE_DISCHARGE].bSetAnim == true &&
				g_aSwordAnim->nAnimTurn == SWORDATTACK_PREMOVE &&
				g_Sword.nMoveCnt <= DISCHARGE_TIMING)
			{//当たったタイミングが良かったら
				g_aSwordAnim[SWORDANIMTYPE_DISCHARGE].nAnimTurn = SWORDATTACK_PREMOVE;
				g_aSwordAnim[SWORDANIMTYPE_DISCHARGE].bSetAnim = false;	//セットできる状態に
				g_Sword.bJustDisCharge = true;
				g_Sword.nState = SWORDANIMTYPE_JUSTDISCHARGE;			//ジャスト放出状態
				SetSwordAnim(g_Sword.nState, 5.0f, 30.0f, 7.0f, D3DX_PI * 0.3f, -D3DX_PI * 0.9f, D3DX_PI * 0.3f);//情報セット
			}
		}
	}

	//ロック
	g_pVteBuffSword->Lock(0, 0, (void**)&pVtx, 0);

	//位置設定
	g_Sword.pos.y = pPlayer->pos.y - PLAYER_HEIGHT * 0.5f;	

	if (pPlayer->bDirection == false)
	{//左向き
		g_Sword.pos.x = pPlayer->pos.x - g_Sword.fPositionX;	//位置
		fLot = g_Sword.fLot * -1.0f;							//向き
	}
	else if (pPlayer->bDirection == true)
	{//右向き
		g_Sword.pos.x = pPlayer->pos.x + g_Sword.fPositionX;	//位置X
		fLot = g_Sword.fLot;									//向き
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

	//当たり判定
	switch (g_Sword.nState)
	{//状態による処理
		//通常状態--------------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_NONE:
		g_Sword.rectHitBox.bottom = g_Sword.pos.y;
		g_Sword.rectHitBox.left = g_Sword.pos.x;
		g_Sword.rectHitBox.right = 0.0f;
		g_Sword.rectHitBox.top = 0.0f;
		break;

		//攻撃状態--------------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_ATTACK:
		//通常攻撃の当たり判定の大きさ
		g_Sword.rectHitBox.right = sinf(D3DX_PI + fLot) * SWORD_HEIGHT * 0.5f;
		g_Sword.rectHitBox.top = cosf(D3DX_PI - fLot) * SWORD_HEIGHT * 0.5f;
		break;

		//チャージ状態----------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_CHARGE:
		break;

		//放出状態--------------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_DISCHARGE:
		//ビームソードの当たり判定
		g_Sword.rectHitBox.right = sinf(D3DX_PI + fLot) * g_Sword.beamSword.fBSHeight * 0.5f;
		g_Sword.rectHitBox.top = cosf(D3DX_PI - fLot) * g_Sword.beamSword.fBSHeight * 0.5f;
		break;

		//ジャスト放出----------------------------------------------------------------------------------------------------------------------
	case SWORDANIMTYPE_JUSTDISCHARGE:
		g_Sword.rectHitBox.right = sinf(D3DX_PI + fLot) * g_Sword.beamSword.fBSHeight * 0.5f;
		g_Sword.rectHitBox.top = cosf(D3DX_PI - fLot) * g_Sword.beamSword.fBSHeight * 0.5f;
		break;

	default:
		break;
	}

	//レクト情報代入
	hitSwordpos.x = g_Sword.pos.x + g_Sword.rectHitBox.right;
	hitSwordpos.y = g_Sword.pos.y + g_Sword.rectHitBox.top;

	SetEffect(g_Sword.pos,						//位置
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//移動量
		D3DXCOLOR(0.0f, 0.9f, 1.0f, 0.5f),		//色
		EFFECTTYPE_NOMAL,						//通常エフェクト
		5.0f,									//ポリゴンサイズ
		0.0f,									//高さ
		0.0f,									//幅
		0.01f,									//ポリゴンサイズ減少数
		0.0f,									//移動量減少数
		10.0f,									//寿命
		0.0f,									//角度
		-1										//消すやつ
	);

	if (g_Sword.rectHitBox.right < 0)
	{//マイナス値にならないようにする
		g_Sword.rectHitBox.right *= -1.0f;
	}

	if (g_Sword.rectHitBox.top < 0)
	{//マイナス値にならないようにする
		g_Sword.rectHitBox.top *= -1.0f;
	}
	
	g_Sword.rectHitBox.bottom = g_Sword.rectHitBox.top;
	g_Sword.rectHitBox.left = g_Sword.rectHitBox.right;

	if (g_Sword.bHit == true)
	{//当たる状態だったら
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{//探す
			if (pEnemy->bUse == true)
			{//使っていたら
				if (HitBox(g_Sword.rectHitBox, pEnemy->rect, hitSwordpos, pEnemy->pos, ANCHORPOINT_CENTER, ANCHORPOINT_CENTER) == true)
				{//当たってたら
					if (g_Sword.beamSword.bBeamSword == true && pEnemy->state == ENEMYSTATE_NORMAL)
					{//ビーム攻撃だったら
						//パーティクル生成
						SetParticle(pEnemy->pos,					//位置
							D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f),		//色
							EFFECTTYPE_NOMAL,	//種類
							20,					//出す量
							314,				//出す角度
							100.0f,				//速さ
							0.0f,				//移動量減少数
							4.0f,				//ポリゴンサイズ
							0.0f,				//ポリゴンサイズ減少数
							0.0f,				//狙いの角度
							60,					//寿命
							5.0f,				//最低の移動量
							0.0f,				//幅
							0.0f,				//高さ
							-1);
					}

					//敵ダメージ処理
					HitEnemy(nCntEnemy, 1);
				}
			}
		}
	}
	
	//座標
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

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = g_Sword.col;
	pVtx[1].col = g_Sword.col;
	pVtx[2].col = g_Sword.col;
	pVtx[3].col = g_Sword.col;

	//テクスチャ座標の設定　　
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//アンロック
	g_pVteBuffSword->Unlock();
}

//====================
//Swordの描画処理
//====================
void DrawSword(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//使用していたら表示する
	if (g_Sword.bUse == true)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVteBuffSword, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureSword);

		//剣の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			0,										//描画する最初の頂点インデックス
			2);										//描画するプリミティブ（剣）数
	}
}
//=========================
//剣の設定
//=========================
void SetSword(D3DXVECTOR3 pos)
{
	if (g_Sword.bUse == false)
	{
		VERTEX_2D* pVtx;

		//ロック
		g_pVteBuffSword->Lock(0, 0, (void**)&pVtx, 0);

		//初期化
		g_Sword.pos = pos;																				//位置
		g_Sword.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);												//色
		g_Sword.fAngle = atan2f(SWORD_HEIGHT, SWORD_WIDTH);												//角度
		g_Sword.fLength = sqrtf((SWORD_WIDTH * SWORD_WIDTH) + (SWORD_HEIGHT * SWORD_HEIGHT));			//対角線
		g_Sword.fLot = 0.0f;																			//角度
		g_Sword.TopLeft.x = sinf(-D3DX_PI * 0.5f + g_Sword.fAngle - g_Sword.fLot) * g_Sword.fLength;	//0X
		g_Sword.TopLeft.y = cosf(D3DX_PI * 0.5f + g_Sword.fAngle - g_Sword.fLot) * g_Sword.fLength;		//0Y
		g_Sword.TopRight.x = sinf(D3DX_PI * 0.5f + g_Sword.fAngle + g_Sword.fLot) * g_Sword.fLength;	//1X
		g_Sword.TopRight.y = cosf(D3DX_PI * 0.5f + g_Sword.fAngle + g_Sword.fLot) * g_Sword.fLength;	//1Y
		g_Sword.BottomLeft.x = sinf(-D3DX_PI * 0.5 - g_Sword.fLot) * SWORD_WIDTH;						//2X
		g_Sword.BottomLeft.y = cosf(-D3DX_PI * 0.5 + g_Sword.fLot) * SWORD_WIDTH;						//2Y
		g_Sword.BottomRight.x = sinf(D3DX_PI * 0.5 - g_Sword.fLot) * SWORD_WIDTH;						//3X
		g_Sword.BottomRight.y = cosf(-D3DX_PI * 0.5 - g_Sword.fLot) * SWORD_WIDTH;						//3Y
		g_Sword.bUse = true;																			//使用する

		//座標
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

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = g_Sword.col;
		pVtx[1].col = g_Sword.col;
		pVtx[2].col = g_Sword.col;
		pVtx[3].col = g_Sword.col;

		//テクスチャ座標の設定　　
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//アンロック
		g_pVteBuffSword->Unlock();
	}
}

//==================
//剣の情報取得
//==================
SWORD* GetSword(void)
{
	return &g_Sword;
}

//==========================
//剣のアニメーション情報取得
//==========================
SWORDANIM* GetSwordAnim(void)
{
	return &g_aSwordAnim[0];
}

//=========================
//剣を装備
//=========================
void EquipmentSword(void)
{
	//プレイヤー情報取得
	Player* pPlayer = GetPlayer();

	g_Sword.fLot = D3DX_PI * 0.3f;	//角度
}

//=========================
//剣のモーション
//=========================
void SwordAnimation(int nType)
{
	switch (g_aSwordAnim[nType].nAnimTurn)
	{
	case SWORDATTACK_PREMOVE:

		//計算して回転させていく
		g_Sword.fLot += g_aSwordAnim[nType].fBetweenLot * (1 / g_aSwordAnim[nType].fAnimCnt1);	//角度を足していく
 		g_Sword.nMoveCnt++;																		//カウンター加算

		if (g_Sword.nMoveCnt >= g_aSwordAnim[nType].fAnimCnt1)
		{//一定以上進んだら
			g_aSwordAnim[nType].fBetweenLot = g_aSwordAnim[nType].fDesiredValueLot2 - g_Sword.fLot;//次の目的の値から今の値の間の値を計算
			g_Sword.bHit = true;									//当たるようにする
			g_Sword.nMoveCnt = 0;									//カウンターをゼロ
			g_aSwordAnim[nType].nAnimTurn = SWORDATTACK_MAINMOVE;	//次へ3
		}
		break;

	case SWORDATTACK_MAINMOVE:

		//計算して回転させていく
		g_Sword.fLot += g_aSwordAnim[nType].fBetweenLot * (1 / g_aSwordAnim[nType].fAnimCnt2);	//角度を引いていく
		g_Sword.nMoveCnt++;																		//カウンター加算

		if (g_Sword.nMoveCnt >= g_aSwordAnim[nType].fAnimCnt2)
		{//一定以上進んだら
			g_aSwordAnim[nType].fBetweenLot = g_aSwordAnim[nType].fDesiredValueLot3 - g_Sword.fLot;//次の目的の値から今の値の間の値を計算
			g_Sword.nMoveCnt = 0;									//カウンターをゼロ
			g_aSwordAnim[nType].nAnimTurn = SWORDATTACK_LEARMOVE;	//次へ
		}
		break;

	case SWORDATTACK_LEARMOVE:

		//計算して回転させていく
		g_Sword.fLot += g_aSwordAnim[nType].fBetweenLot * (1 / g_aSwordAnim[nType].fAnimCnt3);	//角度を足していく
		g_Sword.nMoveCnt++;																		//カウンター加算

		if (g_Sword.nMoveCnt >= g_aSwordAnim[nType].fAnimCnt3)
		{//一定以上進んだら
			g_Sword.bHit = false;									//当たらないようにする
			g_aSwordAnim[nType].bSetAnim = false;					//セットできる状態に
			g_Sword.nMoveCnt = 0;									//カウンターをゼロ
			g_aSwordAnim[nType].nAnimTurn = SWORDATTACK_PREMOVE;	//最初から
			g_Sword.nState = SWORDANIMTYPE_NONE;					//通常モード
		}
		break;

	default:
		g_aSwordAnim[nType].bSetAnim = false;					//セットできる状態に
		g_aSwordAnim[nType].nAnimTurn = SWORDATTACK_PREMOVE;	//最初から
		g_Sword.nState = SWORDANIMTYPE_NONE;					//通常モード
		break;
	}
}

//=========================
//剣のモーション
//=========================
void SetSwordAnim(int type, float fCnt1, float fCnt2, float fCnt3, float fDesValuLot1, float fDesValuLot2, float fDesValuLot3)
{
	
	if (g_aSwordAnim[type].bSetAnim == false)
	{
		//設定した状態にする
		g_aSwordAnim[type].bSetAnim = true;
		//値を代入
		g_aSwordAnim[type].fDesiredValueLot1 = fDesValuLot1;
		g_aSwordAnim[type].fDesiredValueLot2 = fDesValuLot2;
		g_aSwordAnim[type].fDesiredValueLot3 = fDesValuLot3;
		g_aSwordAnim[type].fAnimCnt1 = fCnt1;
		g_aSwordAnim[type].fAnimCnt2 = fCnt2;
		g_aSwordAnim[type].fAnimCnt3 = fCnt3;
		//目的の値から今の値の間の値を計算
		g_aSwordAnim[type].fBetweenLot = g_aSwordAnim[type].fDesiredValueLot1 - g_Sword.fLot;
	}
}

//=========================
//剣の当たり判定
//=========================
bool HitSword(D3DXVECTOR3 pos,float fWidth)
{
	bool bHit = false;//当たったかどうか

	D3DXVECTOR2 hitPos;
	float fNowDistance;
	float fDistance = 0.0f;
	float fXDis = 0.0f;
	float fYDis = 0.0f;

	if (g_Sword.bHit == true)
	{//当たる状態だったら

		//状態による処理
		switch (g_Sword.nState)
		{
			//通常状態--------------------------------------------------------------------------------------------------------------------------
		case SWORDANIMTYPE_NONE:
			break;

			//攻撃状態--------------------------------------------------------------------------------------------------------------------------
		case SWORDANIMTYPE_ATTACK:

			//剣の先端部分
			hitPos.x = (sinf(-g_Sword.fLot) * SWORD_HEIGHT);
			hitPos.y = (cosf(D3DX_PI + g_Sword.fLot) * SWORD_HEIGHT);
			hitPos.x += (g_Sword.pos.x);
			hitPos.y += (g_Sword.pos.y);

			//半径を合わせた距離
			fDistance = SWORD_WIDTH + fWidth;

			//今の距離感
			fXDis = hitPos.x - pos.x;
			fYDis = hitPos.y - pos.y;

			fNowDistance = sqrtf((fXDis * fXDis) + (fYDis * fYDis) * 0.5f);

			//円どうしの当たり判定
			if (fNowDistance < fDistance)
			{
				//当たったことにする
				bHit = true;
			}
			break;

			//チャージ状態----------------------------------------------------------------------------------------------------------------------
		case SWORDANIMTYPE_CHARGE:
		
			break;

			//放出状態--------------------------------------------------------------------------------------------------------------------------
		case SWORDANIMTYPE_DISCHARGE:
			
			break;

		default:
			break;
		}	
	}

	//値を返す
	return bHit;
}

//=========================
//ビーム剣の設定
//=========================
void BeamSwordGeneration(int nTurn)
{
	CHARGE* pCharge = GetCharge();//チャージ取得

	

	if (g_Sword.bJustDisCharge == true)
	{//ジャストだったら
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
		{//チャージされてたら
			g_Sword.beamSword.fBSHeight = (BEAMSWORD_HEIGHT / MAX_ELECTRICPOWER) * pCharge->fChargrAmount + SWORD_HEIGHT;	//高さ
		}
		else if (pCharge->fChargrAmount == 0)
		{//チャージされてなかったら
			g_Sword.beamSword.fBSHeight = 0.0f;	//高さ
		}
		break;

	case SWORDATTACK_MAINMOVE:

		if (g_Sword.beamSword.bBeamSword == false)
		{//使ってなかったら
			g_Sword.beamSword.bBeamSword = true;	//生成した
			ChargePower((pCharge->fChargrAmount) * -1);


			g_Sword.beamSword.fBSWidth = 15.0f;		//幅

			SetEffect(g_Sword.pos,						//位置
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//移動量
				g_Sword.beamSword.Andercol,				//色
				EFFECTTYPE_BEAMSWORD,					//通常エフェクト
				0.0f,									//ポリゴンサイズ
				g_Sword.beamSword.fBSHeight,			//高さ
				15.0f,									//幅
				0.0f,									//ポリゴンサイズ減少数
				0.0f,									//移動量減少数
				1.0f,									//寿命
				0.0f,									//角度
				BEAMBEAMBEAM										//消すやつ
			);

			SetEffect(g_Sword.pos,						//位置
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//移動量
				g_Sword.beamSword.Floatcol,				//色
				EFFECTTYPE_BEAMSWORD,					//通常エフェクト
				0.0f,									//ポリゴンサイズ
				g_Sword.beamSword.fBSHeight,			//高さ
				6,										//幅
				0.0f,									//ポリゴンサイズ減少数
				0.0f,									//移動量減少数
				1.0f,									//寿命
				0.0f,									//角度
				BEAMBEAMBEAM										//消すやつ
			);

			PlaySound(SOUND_LABEL_BEAMSWORD_GENERATE_SE);//ビーム音
		}

		//パーティクル生成
		SetParticle(g_Sword.pos,				//位置
			g_Sword.beamSword.tracecol,			//色
			EFFECTTYPE_BEAM,					//種類
			2,			//出す量
			314,		//出す角度
			5,			//速さ
			1.0f,		//移動量減少数
			0.0f,		//ポリゴンサイズ
			0.0f,		//ポリゴンサイズ減少数
			0.0f,		//狙いの値
			7,			//寿命
			2.0f,		//最低の移動量
			10.0f,		//幅
			300.0f,		//高さ
			BEAMBEAMBEAM);
		break;

	case SWORDATTACK_LEARMOVE:
		g_Sword.beamSword.bBeamSword = false;	//生成していない
		g_Sword.beamSword.fBSHeight = 0.0f;		//高さゼロ
		EndEffect(EFFECTTYPE_BEAMSWORD, BEAMBEAMBEAM);		//ビームソード消去
		StopSound(SOUND_LABEL_BEAMSWORD_GENERATE_SE);		//ビーム音消す
		break;

	}
}
