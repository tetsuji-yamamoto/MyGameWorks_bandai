//===================================================================================
//
//					プレイヤーの処理
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

//ぐろーばる宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVteBuffPlayer = NULL;
Player g_player;

//====================
//Playerの初期化処理
//====================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_PLAYER_002,
		&g_pTexturePlayer);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVteBuffPlayer,
		NULL);

	VERTEX_2D* pVtx;

	//ロック
	g_pVteBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//初期化
	g_player.rect.bottom = PLAYER_HEIGHT;
	g_player.rect.left = PLAYER_WIDTH;
	g_player.rect.right = PLAYER_WIDTH;
	g_player.rect.top = PLAYER_HEIGHT;
	g_player.pos = D3DXVECTOR3(300.0f, 200.0f, 0.0f);	//位置
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	g_player.col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);		//色
	g_player.fLife = MAX_PLAYER_HP;								//体力
	g_player.nJanpCounter = 0;							//ジャンプカウント
	g_player.nPatternAnim = 0;							//アニメーションパターン
	g_player.nCounterAnim = 0;							//アニメーションカウンター
	g_player.nCntSound = 0;								//音カウンター
	g_player.fAnimLine = 0;								//アニメーションカウンター
	g_player.fGravity = PLAYER_GRAVITY;					//重力
	g_player.bDisp = true;								//表示するか
	g_player.bJanp = false;								//ジャンプ
	g_player.bStand = false;							//待機状態かどうか
	g_player.bCharge = false;							//チャージ状態
	g_player.bDirection = true;							//向き
	g_player.state = PLAYERSTATE_APPER;					//プレイヤー状態
	g_player.pBlock = NULL;								//対象ブロックへのポインタ

	//座標
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

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = g_player.col;
	pVtx[1].col = g_player.col;
	pVtx[2].col = g_player.col;
	pVtx[3].col = g_player.col;

	//テクスチャ座標の設定　　
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//アンロック
	g_pVteBuffPlayer->Unlock();
}
//====================
//Playerの終了処理
//====================
void UninitPlayer(void)
{
	//テクスチャの破棄
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
//Playerの更新処理
//====================
void UpdatePlayer(void)
{
	SWORD* pSword = GetSword();					//剣情報取得
	SWORDANIM* pSwordAnim = GetSwordAnim();		//剣のアニメーション取得
	XINPUT_STATE* pStick = GetJoySticAngle();	//スティック取得

	VERTEX_2D* pVtx;

	//アニメーション遅らせ
	if (g_player.nCounterAnim >= 10)
	{
		g_player.nCounterAnim = 0;

		//パターンをカウント
		g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 2;
	}

	// ロック
	g_pVteBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_player.bDisp == true)
	{
		if (KeyboardRepeat(DIK_A) == true || GetJoypadRepeat(JOYKEY_LEFT) == true || pStick->Gamepad.sThumbLX <= -5000)
		{//左移動
			g_player.move.x += - PLAYER_MOVE;//移動量
			g_player.nCounterAnim++;		//アニメーションをカウント
			g_player.bDirection = false;	//向き
			g_player.nCntSound++;			//音カウンター加算
		}
		else if (KeyboardRepeat(DIK_D) == true || GetJoypadRepeat(JOYKEY_RIGHT) == true || pStick->Gamepad.sThumbLX >= 5000)
		{//右移動
			g_player.move.x += PLAYER_MOVE;	//移動量
			g_player.nCounterAnim++;		//アニメーションをカウント
			g_player.bDirection = true;		//向き
			g_player.nCntSound++;			//音カウンター加算
		}
		else
		{
			g_player.nPatternAnim = 0;	//アニメーションをカウント
			g_player.nCntSound = 14;	//動いた瞬間なる
		}

		//足音を鳴らす
		if (g_player.nCntSound >= 15)
		{//一定以上カウントしたら
			g_player.nCntSound = 0;					//カウントリセット
			if (g_player.bJanp == false)
			{//ジャンプしてなかったら
				PlaySound(SOUND_LABEL_PLAYERMOVE_SE);	//足音
			}
		}

		//ジャンプ
		if (KeyboardTrigger(DIK_SPACE) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{
			if (g_player.bJanp == false)
			{
				g_player.move.y -= PLAYER_JUMP;
				g_player.bJanp = true;
				PlaySound(SOUND_LABEL_PLAYERJUMP_SE);
			}
		}

		//当たったら充電
		if (HitThunder(g_player.pos, PLAYER_HEIGHT) == true)
		{
			ChargePower(THUNDER_DAMAGE);
			PlaySound(SOUND_LABEL_PLAYERCHARGE_SE);//チャージ音
		}

#ifdef _DEBUG //デバッグビルド時だけ使用できる

		if (KeyboardRepeat(DIK_3) == true)
		{//死ぬ
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

		//前回の位置を保存
		g_player.posOld = g_player.pos;

		if (g_player.pBlock != NULL)
		{
			//ブロックが移動した分だけプレイヤーに加算する
			g_player.pos += g_player.pBlock->move;
			g_player.posOld += g_player.pBlock->move;
		}

		//重力
		g_player.move.y += PLAYER_GRAVITY;

		//慣性
		g_player.move.x += (0 - g_player.move.x * 0.4f);

		//移動量を追加
		g_player.pos.y += g_player.move.y;

		//ブロックとの当たり判定
		g_player.bJanp = !CollisionBlockY(&g_player.pos, &g_player.posOld, &g_player.move, PLAYER_HEIGHT, PLAYER_WIDTH,&g_player.pBlock);

		//移動量を追加
		g_player.pos.x += g_player.move.x;

		//ブロックとの当たり判定
		CollisionBlockX(&g_player.pos, &g_player.posOld, &g_player.move, PLAYER_HEIGHT, PLAYER_WIDTH,&g_player.pBlock);


		//画面端から反対側へ
		if (g_player.pos.x - PLAYER_WIDTH > SCREEN_WIDTH)
		{
			g_player.pos.x = 0.0f - PLAYER_WIDTH;
			//前回の位置を保存
			g_player.posOld = g_player.pos;
		}
		else if (g_player.pos.x + PLAYER_WIDTH < 0.0f)
		{
			g_player.pos.x = SCREEN_WIDTH + PLAYER_WIDTH;
			//前回の位置を保存
			g_player.posOld = g_player.pos;
		}
		//画面下処理
		if (g_player.pos.y > SCREEN_HEIGHT)
		{
			g_player.pos.y = SCREEN_HEIGHT;
			g_player.move.y = 0.0f;
			g_player.bJanp = false;
		}

		//ジャンプ中
		if (g_player.bJanp == true)
		{
			//テクスチャ
			g_player.nPatternAnim = 3;
		}

		//状態による処理
		switch (g_player.state)
		{
		case PLAYERSTATE_APPER:
			g_player.state = PLAYERSTATE_NOMAL;	//通常状態に
			break;

		case PLAYERSTATE_NOMAL:
			break;

		case PLAYERSTATE_ATTACK:
			break;

		case PLAYERSTATE_DAMAGE:
			if (g_player.nCounterState > 0)
			{
				g_player.nCounterState--;						//カウンターを減少
				g_player.col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);	//色を赤色に
			}
			else
			{
				g_player.state = PLAYERSTATE_NOMAL;					//通常状態に
				g_player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//通常色に
			}
			break;

		case PLAYERSTATE_DETH:
			g_player.bDisp = false;
			if (GetGameState() == GAMESTATE_NORMAL)
			{
				SetFade(MODE_RESULT);
				SetResult(RESULTTYPE_GAMEOVER);	//ゲームオーバー
			}
			break;
		}

		//向きによって
		if (g_player.bDirection == true)
		{//右向き
			//テクスチャ座標の設定　　
			pVtx[0].tex = D3DXVECTOR2(0.25f * g_player.nPatternAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f * g_player.nPatternAnim, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.25f * g_player.nPatternAnim, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f * g_player.nPatternAnim, 1.0f);
		}
		else if (g_player.bDirection == false)
		{//左向き
			//テクスチャ座標の設定　　
			pVtx[0].tex = D3DXVECTOR2(0.25f + 0.25f * g_player.nPatternAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.25f * g_player.nPatternAnim, 0.0f); 
			pVtx[2].tex = D3DXVECTOR2(0.25f + 0.25f * g_player.nPatternAnim, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f * g_player.nPatternAnim, 1.0f); 
		}

		//座標
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

		//頂点カラー
		pVtx[0].col = g_player.col;
		pVtx[1].col = g_player.col;
		pVtx[2].col = g_player.col;
		pVtx[3].col = g_player.col;
	}

	//アンロック
	g_pVteBuffPlayer->Unlock();
}
//====================
//Playerの描画処理
//====================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();
	if (g_player.bDisp == true)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVteBuffPlayer, 0, sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);
		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			0,										//描画する最初の頂点インデックス
			2);										//描画するプリミティブ（プレイヤー）数
	}
}

//==================
//プレイヤーの取得
//==================
Player* GetPlayer(void)
{
	return &g_player;
}

//=========================
//プレイヤーの当たり判定
//=========================
void HitPlayer(float fDamage)
{
	if (g_player.state == PLAYERSTATE_NOMAL)
	{
		g_player.fLife -= fDamage;	//体力減らす
		PlaySound(SOUND_LABEL_PLAYERDAMAGE_SE);//ダメージ音

		if (g_player.fLife > 0)
		{//体力あったら
			g_player.nCounterState = 60;			//状態カウンターを設定
			g_player.state = PLAYERSTATE_DAMAGE;	//ダメージ状態に
		}
		else if (g_player.fLife <= 0)
		{//体力ない
			if (GetMode() != MODE_TUTORIAL)
			{//チュートリアルモードじゃなかったら
				g_player.state = PLAYERSTATE_DETH;	//デス状態に
			}
			g_player.fLife = 0.0f;
		}
	}
}

//=============================
//ジャンプ
//=============================
void PlayerJamp(void)
{

	
}

//=============================
//放出discharge
//=============================
void Discharge(void)
{
	CHARGE* pCharge = GetCharge();//ここまで
}