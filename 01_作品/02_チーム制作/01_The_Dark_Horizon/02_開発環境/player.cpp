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

// グローバル変数宣言

D3DXMATRIX g_mtxWorldPlayer;				// ワールドマトリックス
PLAYER g_player;							// プレイヤー情報
MODELCOLER g_aPlayerModelCol[10][6];		// 便利な色保存場所
int nIdxShadow = 0;

//************************************************
// プレイヤー初期化
//************************************************
void InitPlayer(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// プレイヤー情報初期化
	
	// 各種変数の初期化
	g_player.pos = D3DXVECTOR3(-100.0f, 100.0f, 0.0f);	// 位置
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
	g_player.size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);	// 移動量
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 目的向き
	g_player.snowBall.nMakeTimerSnow = 0;		// 雪玉作る時間
	g_player.snowBall.nMakeTimerSnowMidi = 0;	// 雪玉作る時間
	g_player.snowBall.nMakeTimerSnowBig = 0;	// 雪玉作る時間
	g_player.snowBall.nMakeTimerIce = 0;		// 雪玉作る時間
	g_player.snowBall.nMakeTimerIGravel = 0;	// 雪玉作る時間
	g_player.snowBall.bSrow = false;			// 投げてない

	g_player.nBlockType = 0;				// 踏んでるブロック
	g_player.snowBall.nSnowBallWeight = 0;	// 玉重さ

	g_player.charParam.nNumModel = 0;		// パーツの総数
	g_player.charParam.fHeigt = 0.0f;		// 高さ
	g_player.charParam.fWidth = 0.0f;		// 幅
	g_player.charParam.fJamp = PLAYER_JUMP;		// ジャンプ力
	g_player.charParam.nLife = PLAYER_HP;			// 体力
	g_player.charParam.nState = MOTIONTYPE_PLAYER_NEUTRAL;	// 初期モーション
	g_player.charParam.nCntOcc = 0;		// 発生カウンター
	g_player.charParam.nCntDura = 0;	// 持続カウンター
	g_player.charParam.bMove = false;	// 動くかどうか
	g_player.charParam.bDisp = true;	// 写しますか
	g_player.charParam.bAttack = false;	// 攻撃しますか
	g_player.charParam.bJanp = false;	// ジャンプしますか

	g_player.motion.bLoopMotion = true;
	g_player.motion.nNumKey = 2;
	g_player.motion.nKey = 0;
	g_player.motion.nCounterMotion = 0;
	g_player.motion.nNextKey = g_player.motion.nKey + 1;

	g_player.nShadowIdx = -1;			// 影のインデックス
	g_player.naSmokeIdx[0] = -1;		// 影のインデックス
	g_player.naSmokeIdx[1] = -1;		// 影のインデックス

	for (int nCnt = 0; nCnt < 12; nCnt++)
	{
		g_player.snowBall.nSnowOrder[nCnt] = -1;
		g_player.snowBall.nIceOrder[nCnt] = -1;
		g_player.snowBall.nGravelOrder[nCnt] = -1;
	}

	// モーションテキスト読み込み
	ReadMotionText("date\\motion\\player\\motion.txt", &g_player.aModel[0], &g_player.motion, &g_player.charParam);


	for (int nCntModel = 0; nCntModel < g_player.charParam.nNumModel; nCntModel++)
	{
		g_player.aPlayerColiPoint[nCntModel].fRadius = 10.0f;						// 幅
		g_player.aPlayerColiPoint[nCntModel].pos = g_player.aModel[nCntModel].pos;	// 位置


		//マテリアルデータへのポインタを取得
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			
			g_aPlayerModelCol[nCntModel][nCntMat].fR = pMat[nCntMat].MatD3D.Diffuse.r;
			g_aPlayerModelCol[nCntModel][nCntMat].fG = pMat[nCntMat].MatD3D.Diffuse.g;
			g_aPlayerModelCol[nCntModel][nCntMat].fB = pMat[nCntMat].MatD3D.Diffuse.b;
			g_aPlayerModelCol[nCntModel][nCntMat].fA = pMat[nCntMat].MatD3D.Diffuse.a;
		}
	}

	// 影の設定
	g_player.nShadowIdx = SetShadw(g_player.pos, g_player.rot,g_player.charParam.fWidth);

	if (GetMode() == MODE_GAME || GetMode() == MODE_TUTORIAL)
	{
		// HPゲージの設定
		SetHPGauge(&g_player.HPGaugeHave[HPGAUGETYPE_BG], HPGAUGETYPE_BG, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.9f), 5.0f, 100.0f, g_player.charParam.nLife);
		SetHPGauge(&g_player.HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], HPGAUGETYPE_GAUGE_REDZONE, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.9f), 5.0f, 100.0f, g_player.charParam.nLife);
		SetHPGauge(&g_player.HPGaugeHave[HPGAUGETYPE_GAUGE], HPGAUGETYPE_GAUGE, D3DXCOLOR(0.5f, 1.0f, 0.0f, 0.9f), 5.0f, 100.0f, g_player.charParam.nLife);

		// 雪玉ゲージの設定
		SetHPGauge(&g_player.SBGaugeHave[HPGAUGETYPE_BG], HPGAUGETYPE_BG, D3DXCOLOR(0.0f, 0.5f, 0.5f, 0.9f), 5.0f, 100.0f, 1);
		SetHPGauge(&g_player.SBGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], HPGAUGETYPE_GAUGE_REDZONE, D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.9f), 5.0f, 100.0f, 1);

		SetHPGauge(&g_player.SBGaugeHave[HPGAUGETYPE_GAUGE], HPGAUGETYPE_GAUGE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f), 5.0f, 100.0f, SB_MAKETIMER_SNOW);	// 雪玉
		SetHPGauge(&g_player.SBMidiGaugeHave, HPGAUGETYPE_GAUGE, D3DXCOLOR(1.0f, 1.0f, 0.5f, 0.9f), 5.0f, 100.0f, SB_MAKETIMER_SNOW_MIDI - SB_MAKETIMER_SNOW);	// 雪玉中
		SetHPGauge(&g_player.SBBigGaugeHave, HPGAUGETYPE_GAUGE, D3DXCOLOR(1.0f, 0.5f, 0.5f, 0.9f), 5.0f, 100.0f, SB_MAKETIMER_SNOW_BIG - SB_MAKETIMER_SNOW_MIDI);	// 雪玉大
		SetHPGauge(&g_player.SBIceGaugeHave, HPGAUGETYPE_GAUGE, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.9f), 5.0f, 100.0f, SB_MAKETIMER_ICE);		// 氷玉
		SetHPGauge(&g_player.SBGraGaugeHave, HPGAUGETYPE_GAUGE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.9f), 5.0f, 100.0f, SB_MAKETIMER_GRAVEL);	// 砂利玉

		SetHPGauge(&g_player.aSBWateGauge[HPGAUGETYPE_BG], HPGAUGETYPE_BG, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.9f), 2.5f, 100.0f, SB_WEIGHT_MAX);
		SetHPGauge(&g_player.aSBWateGauge[HPGAUGETYPE_GAUGE_REDZONE], HPGAUGETYPE_GAUGE_REDZONE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.9f), 2.5f, 100.0f, SB_WEIGHT_MAX);
		SetHPGauge(&g_player.aSBWateGauge[HPGAUGETYPE_GAUGE], HPGAUGETYPE_GAUGE, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.9f), 2.5f, 100.0f, SB_WEIGHT_MAX);
	}
	g_player.naSmokeIdx[0] = SetSmoke(SMOKETYPE_ATTACH,g_player.pos,20, 20.0f,true);
	g_player.naSmokeIdx[1] = SetSmoke(SMOKETYPE_ATTACH,g_player.pos,40, 20.0f,true);
}

//************************************************
// プレイヤーの終了
//************************************************
void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < g_player.charParam.nNumModel; nCnt++)
	{
		// メッシュの破棄
		if (g_player.aModel[nCnt].pMesh != NULL)
		{
			g_player.aModel[nCnt].pMesh->Release();
			g_player.aModel[nCnt].pMesh = NULL;
		}

		// マテリアルの破棄
		if (g_player.aModel[nCnt].pBuffMat != NULL)
		{
			g_player.aModel[nCnt].pBuffMat->Release();
			g_player.aModel[nCnt].pBuffMat = NULL;
		}

		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			//テクスチャの破棄
			if (g_player.aModel[nCnt].apTexture[nCnt] != NULL)
			{
				g_player.aModel[nCnt].apTexture[nCnt]->Release();
				g_player.aModel[nCnt].apTexture[nCnt] = NULL;
			}
		}
	}
}

//************************************************
// プレイヤーの更新
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
			Camera* pCamera = GetCamera();				// カメラの取得
			XINPUT_STATE* pJoypad = GetJoypadState();	// コントローラー情報取得
			g_player.charParam.bMove = false;						// 動かないよ

			// キー操作
			if (KeyboardRepeat(DIK_W))
			{// 前移動
				g_player.charParam.bMove = true;	// 動くよ

				if (KeyboardRepeat(DIK_A))
				{// 左移動
					g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.25f;	// 目的の角度を設定
				}
				else if (KeyboardRepeat(DIK_D))
				{// 右移動		
					g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.25f;	// 目的の角度を設定
				}
				else
				{
					g_player.rotDest.y = pCamera->rot.y;	// 目的の角度を設定
				}
			}
			else if (KeyboardRepeat(DIK_S))
			{// 後ろ移動
				g_player.charParam.bMove = true;	// 動くよ
				if (KeyboardRepeat(DIK_A))
				{// 左移動
					g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;	// 目的の角度を設定
				}
				else if (KeyboardRepeat(DIK_D))
				{// 右移動		
					g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;	// 目的の角度を設定
				}
				else
				{
					g_player.rotDest.y = pCamera->rot.y + D3DX_PI;	// 目的の角度を設定
				}
			}
			else if (KeyboardRepeat(DIK_A))
			{// 左移動
				g_player.charParam.bMove = true;	// 動くよ
				g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.5f;	// 目的の角度を設定
			}
			else if (KeyboardRepeat(DIK_D))
			{// 右移動		
				g_player.charParam.bMove = true;	// 動くよ
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.5f;	// 目的の角度を設定
			}

			if (KeyboardRepeat(DIK_RETURN) || GetJoypadRepeat(JOYKEY_R1))
			{// 雪玉作成

				

				int nOllSnow = g_player.snowBall.nMakeTimerSnow + g_player.snowBall.nMakeTimerSnowMidi + g_player.snowBall.nMakeTimerSnowBig;	// 雪玉のすべての時間
				g_player.charParam.nState = MOTIONTYPE_PLAYER_MAKESNOWBALL;

				if (g_player.snowBall.nMakeType != g_player.nBlockType)
				{// 違うブロックに移ったら
					g_player.snowBall.nMakeType = g_player.nBlockType;	// タイプを更新
					g_player.snowBall.nMakeTimerSnow = 0;		// 作成カウントゼロ
					g_player.snowBall.nMakeTimerSnowMidi = 0;	// 作成カウントゼロ
					g_player.snowBall.nMakeTimerSnowBig = 0;	// 作成カウントゼロ
					g_player.snowBall.nMakeTimerIce = 0;		// 作成カウントゼロ
					g_player.snowBall.nMakeTimerIGravel = 0;	// 作成カウントゼロ
				}

				switch (g_player.snowBall.nMakeType)
				{
				case BLOCKTYPE_SNOW:

					if (nOllSnow < SB_MAKETIMER_SNOW)
					{// 雪玉
						g_player.snowBall.nMakeTimerSnow++;
					}
					else if (nOllSnow < SB_MAKETIMER_SNOW_MIDI && nOllSnow >= SB_MAKETIMER_SNOW)
					{// 雪玉が一段階目作れたら
						g_player.snowBall.nMakeTimerSnowMidi++;
					}
					else if (nOllSnow >= SB_MAKETIMER_SNOW_MIDI)
					{// 雪玉が二段階目作れたら
						g_player.snowBall.nMakeTimerSnowBig++;
					}
					else
					{// カウントリセット
						g_player.snowBall.nMakeTimerSnowMidi = 0;
						g_player.snowBall.nMakeTimerSnowBig = 0;
					}
					break;

				case BLOCKTYPE_ICE:	// 氷玉
					g_player.snowBall.nMakeTimerIce++;
					break;

				case BLOCKTYPE_GRAVEL:	// 砂利玉
					g_player.snowBall.nMakeTimerIGravel++;
					break;
				}
			}
			else if (KeyboardRelease(DIK_RETURN) || GetJoypadRelease(JOYKEY_R1))
			{// 離して重くなかったとき
				g_player.charParam.nState = MOTIONTYPE_PLAYER_NEUTRAL;
				if (g_player.snowBall.nSnowBallWeight < SB_WEIGHT_MAX)
				{
					int nCntOrder = -1;
					nCntOrder = MakeOrderSnowBall(&g_player.snowBall, &g_player.nBlockType);	// 順番に並べる
					SetSBUI(g_player.nBlockType, nCntOrder);	// UIセット
				}
			}
			else
			{// 作ってないとき
				g_player.snowBall.nMakeTimerSnow = 0;		// 作成カウントゼロ
				g_player.snowBall.nMakeTimerSnowMidi = 0;	// 作成カウントゼロ
				g_player.snowBall.nMakeTimerSnowBig = 0;	// 作成カウントゼロ
				g_player.snowBall.nMakeTimerIce = 0;		// 作成カウントゼロ
				g_player.snowBall.nMakeTimerIGravel = 0;	// 作成カウントゼロ
			}

			// コントローラー操作
			if (GetJoyStickL())
			{// 左スティック
				g_player.charParam.bMove = true;	// 動くよ
				// 目的の角度を算出
				g_player.rotDest.y = pCamera->rot.y + atan2f(pJoypad->Gamepad.sThumbLX, pJoypad->Gamepad.sThumbLY);
			}

			if (KeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_A))
			{// Aジャンプ
				if (g_player.charParam.bJanp == false)
				{// ジャンプしてなかったら
					g_player.move.y = g_player.charParam.fJamp;
					g_player.charParam.bJanp = true;	// ジャンプ状態

					// ジャンプ音
					PlaySound(SOUND_LABEL_SE_JUMP);

					// ジャンプ状態に変える
					PlayerStateChangeJump();
				}
			}

			

			if (g_player.charParam.bMove == true)
			{// 動くよ
				g_player.move.x = sinf(g_player.rotDest.y) * PLAYER_MOVE;
				g_player.move.z = cosf(g_player.rotDest.y) * PLAYER_MOVE;

				// 移動状態に変える
				PlayerStateChangeMove();
			}

			// 古い位置を更新
			g_player.posOld.x = g_player.pos.x;
			g_player.posOld.y = g_player.pos.y;
			g_player.posOld.z = g_player.pos.z;

			// 重力
			g_player.move.y -= WORLD_GRAVITY;

			// 慣性
			g_player.move.x += (0 - g_player.move.x) * 0.3f;
			g_player.move.z += (0 - g_player.move.z) * 0.3f;

			// 移動量Y追加
			g_player.pos.y += g_player.move.y;
			if (CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt).nHitfase == BLOCKFACETYPE_TOP)	// 当たり判定
			{
				g_player.charParam.bJanp = false;
			}

			// 移動量X追加
			g_player.pos.x += g_player.move.x;
			CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt);	// 当たり判定

			// 移動量Z追加
			g_player.pos.z += g_player.move.z;
			CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt);	// 当たり判定

			CollisionWall();	// 壁の当たり判定

			if (g_player.pos.y <= 0.0f)
			{// 地面突いたら
				g_player.pos.y = 0.0f;
				g_player.move.y = 0.0f;
				g_player.charParam.bJanp = false;	// ジャンプしてないよ
			}

			if (g_player.charParam.bAttack == false)
			{// 攻撃してないときだけ
				if (KeyboardTrigger(DIK_V) || GetJoypadTrigger(JOYKEY_X))
				{// 弾発射
					// 投げる音
					PlaySound(SOUND_LABEL_SE_THROWBALL);
					g_player.charParam.bAttack = true;				// 攻撃します
					g_player.snowBall.nBallType = BULLETTYPE_SNOW;	// 雪玉作ります
				}
				else if (KeyboardTrigger(DIK_B) || GetJoypadTrigger(JOYKEY_Y))
				{// 氷発射
					// 投げる音
					PlaySound(SOUND_LABEL_SE_THROWBALL);
					g_player.charParam.bAttack = true;				// 攻撃します
					g_player.snowBall.nBallType = BULLETTYPE_ICE;	// 氷玉作ります
				}
				else if (KeyboardTrigger(DIK_N) || GetJoypadTrigger(JOYKEY_B))
				{// 砂利発射
					// 投げる音
					PlaySound(SOUND_LABEL_SE_THROWBALL);
					g_player.charParam.bAttack = true;					// 攻撃します
					g_player.snowBall.nBallType = BULLETTYPE_GRAVEL;	// 砂利玉作ります
				}
			}
		}

		// 角度の正規化
		if (g_player.rotDest.y > D3DX_PI)
		{
			g_player.rotDest.y = -D3DX_PI + (g_player.rotDest.y - D3DX_PI);
		}
		else if (g_player.rotDest.y < -D3DX_PI)
		{
			g_player.rotDest.y = D3DX_PI + (g_player.rotDest.y + D3DX_PI);
		}

		// 角度の正規化
		if (g_player.rot.y > D3DX_PI)
		{
			g_player.rot.y = -D3DX_PI + (g_player.rot.y - D3DX_PI);
		}
		else if (g_player.rot.y < -D3DX_PI)
		{
			g_player.rot.y = D3DX_PI + (g_player.rot.y + D3DX_PI);
		}

		// モデルの角度を目的の角度に近づける
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

		// 影の更新
		SetPositionShadow(g_player.nShadowIdx, g_player.pos);

		// 攻撃状態
		PlayerStateChangeAttack();

		// プレイヤーの状態
		PlayerStateManegement();

		// モーション更新
		UpdateMotion(&g_player.motion, &g_player.aModel[0], g_player.charParam.nState, g_player.charParam.nNumModel);

		for (int nCntPosi = 0; nCntPosi < g_player.charParam.nNumModel; nCntPosi++)
		{
			CollisionPointUpdate(&g_player.aPlayerColiPoint[nCntPosi].pos, g_player.aModel[nCntPosi].mtxWorld);
		}

		// 体力ゲージの位置更新
		UpdateHPGaugePos(&g_player.HPGaugeHave[HPGAUGETYPE_BG], g_player.pos, 110.0f, 50.0f);
		UpdateHPGaugePos(&g_player.HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], g_player.pos, 110.0f, 50.0f);
		UpdateHPGaugePos(&g_player.HPGaugeHave[HPGAUGETYPE_GAUGE], g_player.pos, 110.0f, 50.0f);

		// 体力赤ゲージの長さ更新
		UpdateHPGaugeRedZoneWidth(&g_player.HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], g_player.charParam.nLife);

		// 雪玉ゲージの位置更新
		UpdateHPGaugePos(&g_player.SBGaugeHave[HPGAUGETYPE_BG], g_player.pos, 120.0f, 50.0f);
		UpdateHPGaugePos(&g_player.SBGaugeHave[HPGAUGETYPE_GAUGE_REDZONE], g_player.pos, 120.0f, 50.0f);
		UpdateHPGaugePos(&g_player.SBGaugeHave[HPGAUGETYPE_GAUGE], g_player.pos, 120.0f, 50.0f);
		UpdateHPGaugePos(&g_player.SBMidiGaugeHave, g_player.pos, 120.0f, 50.0f);	// 中玉
		UpdateHPGaugePos(&g_player.SBBigGaugeHave, g_player.pos, 120.0f, 50.0f);	// 大玉
		UpdateHPGaugePos(&g_player.SBIceGaugeHave, g_player.pos, 120.0f, 50.0f);	// 氷玉
		UpdateHPGaugePos(&g_player.SBGraGaugeHave, g_player.pos, 120.0f, 50.0f);	// 砂利玉


		UpdateGaugeWidth(&g_player.SBGaugeHave[HPGAUGETYPE_GAUGE], g_player.snowBall.nMakeTimerSnow, true);		// 雪玉ゲージ
		UpdateGaugeWidth(&g_player.SBMidiGaugeHave, g_player.snowBall.nMakeTimerSnowMidi, true);				// 雪玉中ゲージ
		UpdateGaugeWidth(&g_player.SBBigGaugeHave, g_player.snowBall.nMakeTimerSnowBig, true);					// 雪玉大ゲージ
		UpdateGaugeWidth(&g_player.SBIceGaugeHave, g_player.snowBall.nMakeTimerIce, true);						// 雪玉氷ゲージ
		UpdateGaugeWidth(&g_player.SBGraGaugeHave, g_player.snowBall.nMakeTimerIGravel, true);					// 雪玉砂利ゲージ

		// 重さゲージ
		UpdateHPGaugePos(&g_player.aSBWateGauge[HPGAUGETYPE_BG], g_player.pos, 125.5f, 50.0f);
		UpdateHPGaugePos(&g_player.aSBWateGauge[HPGAUGETYPE_GAUGE_REDZONE], g_player.pos, 125.5f, 50.0f);
		UpdateHPGaugePos(&g_player.aSBWateGauge[HPGAUGETYPE_GAUGE], g_player.pos, 125.5f, 50.0f);

		// 重さゲージの長さ更新
		UpdateHPGaugeWidth(&g_player.aSBWateGauge[HPGAUGETYPE_GAUGE], g_player.snowBall.nSnowBallWeight);

		// 重さ赤ゲージの長さ更新
		UpdateHPGaugeRedZoneWidth(&g_player.aSBWateGauge[HPGAUGETYPE_GAUGE_REDZONE], g_player.snowBall.nSnowBallWeight);

	}
	else if (GetMode() == MODE_TITLE)
	{// タイトルだったら
	// 古い位置を更新
		g_player.posOld.x = g_player.pos.x;
		g_player.posOld.y = g_player.pos.y;
		g_player.posOld.z = g_player.pos.z;

		// 重力
		g_player.move.y -= WORLD_GRAVITY;

		// 移動量Y追加
		g_player.pos.y += g_player.move.y;
		if (CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt).nHitfase == BLOCKFACETYPE_TOP)	// 当たり判定
		{
			g_player.charParam.bJanp = false;
		}

		// 移動量X追加
		g_player.pos.x += g_player.move.x;
		CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt);	// 当たり判定

		// 移動量Z追加
		g_player.pos.z += g_player.move.z;
		CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt);	// 当たり判定

		// モーション更新
		UpdateMotion(&g_player.motion, &g_player.aModel[0], MOTIONTYPE_PLAYER_MAKESNOWBALL, g_player.charParam.nNumModel);
	}
	else if (GetMode() == MODE_RESULT)
	{// タイトルだったら
	// 古い位置を更新
		g_player.posOld.x = g_player.pos.x;
		g_player.posOld.y = g_player.pos.y;
		g_player.posOld.z = g_player.pos.z;

		// 重力
		g_player.move.y -= WORLD_GRAVITY;

		// 移動量Y追加
		g_player.pos.y += g_player.move.y;
		if (CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt).nHitfase == BLOCKFACETYPE_TOP)	// 当たり判定
		{
			g_player.charParam.bJanp = false;
		}

		// 移動量X追加
		g_player.pos.x += g_player.move.x;
		CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt);	// 当たり判定

		// 移動量Z追加
		g_player.pos.z += g_player.move.z;
		CollisionBlockCharacter(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.nBlockType, g_player.charParam.fWidth, g_player.charParam.fHeigt);	// 当たり判定

		if (GetResult() == RESULTTYPE_GAMECREAR)
		{
			// モーション更新
			UpdateMotion(&g_player.motion, &g_player.aModel[0], MOTIONTYPE_PLAYER_WIN, g_player.charParam.nNumModel);
		}
		else if (GetResult() == RESULTTYPE_GAMEOVER)
		{
			// モーション更新
			UpdateMotion(&g_player.motion, &g_player.aModel[0], MOTIONTYPE_PLAYER_LOSE, g_player.charParam.nNumModel);
		}
		else if (GetResult() == RESULTTYPE_TIMEOVER)
		{
			// モーション更新
			UpdateMotion(&g_player.motion, &g_player.aModel[0], MOTIONTYPE_PLAYER_LOSE, g_player.charParam.nNumModel);
		}
	}
}

//************************************************
// プレイヤーの表示
//************************************************
void DrawPlayer(void)
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
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// 全モデル(パーツ)の描画
	for (int nCntModel = 0; nCntModel < g_player.charParam.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	// 計算用マトリックス
		D3DXMATRIX mtxParent;					// 親マトリックス

		// パーツのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		// パーツの向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		// パーツの位置(オフセット)を反映
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		// パーツ「親のマトリックス」を設定
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{// 親モデルがある場合
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;	// 親モデルのインデックスを設定
		}
		else
		{// 親のモデルがない場合
			mtxParent = g_mtxWorldPlayer;	// プレイヤーのマトリックスを設定
		}

		// 算出したパーツのワールドマトリックスと親マトリックスをかけ合わせる
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
			&g_player.aModel[nCntModel].mtxWorld,
			&mtxParent);

		// パーツのワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD,
			&g_player.aModel[nCntModel].mtxWorld);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
		{
			if (g_player.charParam.nState == MOTIONTYPE_PLAYER_DAMAGE)
			{// ダメージ状態だったら
				D3DXMATERIAL DamageMat = pMat[nCntMat];
				DamageMat.MatD3D.Diffuse.r = 1.0f;
				DamageMat.MatD3D.Diffuse.g = 0.0f;
				DamageMat.MatD3D.Diffuse.b = 0.0f;
				DamageMat.MatD3D.Diffuse.a = 1.0f;

				// マテリアルの設定
				pDevice->SetMaterial(&DamageMat.MatD3D);

			}
			else
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			}

			// テクスチャの設定
			pDevice->SetTexture(0, g_player.aModel[nCntModel].apTexture[nCntMat]);

			// パーツの描画
			g_player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//**************************************************
// プレイヤーの状態管理
//**************************************************
void PlayerStateManegement(void)
{
	switch (g_player.charParam.nState)
	{
	case MOTIONTYPE_PLAYER_NEUTRAL:
		break;

	case MOTIONTYPE_PLAYER_MOVE:
		if (UpdateAttachSmoke(g_player.naSmokeIdx[0], g_player.aPlayerColiPoint[MODELPOSITION_PLAYER_FOOT_L].pos))	// 煙
		{// 煙出すとき
			// 足音
			PlaySound(SOUND_LABEL_SE_WALKONTHESNOW_L);
		}

		if(UpdateAttachSmoke(g_player.naSmokeIdx[1],g_player.aPlayerColiPoint[MODELPOSITION_PLAYER_FOOT_R].pos))		// 煙
		{// 煙出すとき
			// 足音
			PlaySound(SOUND_LABEL_SE_WALKONTHESNOW_R);
		}

		if (g_player.charParam.bMove == false)
		{// 動いてなかったら
			g_player.charParam.nState = MOTIONTYPE_PLAYER_NEUTRAL;	// 待機状態 
		}
		break;

	case MOTIONTYPE_PLAYER_JUMP:
		if (g_player.charParam.bJanp == false)
		{// ジャンプしてなかったら
			if (g_player.charParam.bMove == false)
			{// 動いてたら
				g_player.charParam.nState = MOTIONTYPE_PLAYER_MOVE;	// 動くよ
			}
			else
			{
				g_player.charParam.nState = MOTIONTYPE_PLAYER_NEUTRAL;	// 待機
			}
		}
		break;

	case MOTIONTYPE_PLAYER_ATTACK:
		g_player.charParam.nCntState++;		// カウントプラス
		if (g_player.charParam.nCntState >= 45)
		{// カウントが一定数になったら
			g_player.charParam.nCntState = 0;	// カウントリセット
			g_player.charParam.nState = MOTIONTYPE_PLAYER_NEUTRAL;	// 通常状態
			g_player.charParam.bAttack = false;	// 攻撃してないよ
			g_player.snowBall.bSrow = false;
		}
		break;

	case MOTIONTYPE_PLAYER_ATTACK_SUPER:
		g_player.charParam.nCntState++;		// カウントプラス
		if (g_player.charParam.nCntState >= 120)
		{// カウントが一定数になったら
			g_player.charParam.nCntState = 0;	// カウントリセット
			g_player.charParam.nState = MOTIONTYPE_PLAYER_NEUTRAL;	// 通常状態
			g_player.charParam.bAttack = false;	// 攻撃してないよ
			g_player.snowBall.bSrow = false;
		}
		break;

	case MOTIONTYPE_PLAYER_DAMAGE:
		g_player.charParam.nCntState++;	// カウントプラス
		if (g_player.charParam.nCntState >= 60)
		{// カウントが一定数になったら
			g_player.charParam.nCntState = 0;	// カウントリセット
			g_player.charParam.nState = MOTIONTYPE_PLAYER_NEUTRAL;	// 通常状態
		}
		break;

	case MOTIONTYPE_PLAYER_DEATH:
		break;
	}
}

//*********************状態*****************************
// プレイヤーの移動
//**************************************************
void PlayerStateChangeMove(void)
{
	if (g_player.charParam.bMove)
	{
		if (g_player.charParam.nState == MOTIONTYPE_PLAYER_NEUTRAL ||
			g_player.charParam.nState == MOTIONTYPE_PLAYER_RANDING)
		{// この状態のとき
			g_player.charParam.nState = MOTIONTYPE_PLAYER_MOVE;	// 移動状態
		}
	}
}

//**************************************************
// プレイヤーのジャンプ状態
//**************************************************
void PlayerStateChangeJump(void)
{
	if (g_player.charParam.nState == MOTIONTYPE_PLAYER_NEUTRAL ||
		g_player.charParam.nState == MOTIONTYPE_PLAYER_RANDING || 
		g_player.charParam.nState == MOTIONTYPE_PLAYER_MOVE)
	{// この状態のとき
		g_player.charParam.nState = MOTIONTYPE_PLAYER_JUMP;	// ジャンプ状態
	}
}

//**************************************************
// プレイヤーの攻撃状態
//**************************************************
void PlayerStateChangeAttack(void)
{
	if (g_player.charParam.bAttack)
	{
		if (g_player.charParam.nState == MOTIONTYPE_PLAYER_NEUTRAL ||
			g_player.charParam.nState == MOTIONTYPE_PLAYER_RANDING ||
			g_player.charParam.nState == MOTIONTYPE_PLAYER_MOVE ||
			g_player.charParam.nState == MOTIONTYPE_PLAYER_JUMP)
		{// この状態のとき
			g_player.charParam.nState = MOTIONTYPE_PLAYER_ATTACK;	// 攻撃状態
			g_player.charParam.nCntOcc = 20;		// 発生カウンターゼロ
			g_player.charParam.nCntDura = 0;	// 持続カウンターゼロ
		}

		if (g_player.charParam.nState == MOTIONTYPE_PLAYER_ATTACK ||
			g_player.charParam.nState == MOTIONTYPE_PLAYER_ATTACK_SUPER)
		{// 攻撃状態なら
			g_player.charParam.nCntOcc--;	// 発生カウンター追加

			if (g_player.charParam.nCntOcc <= 0 && g_player.snowBall.bSrow == false)
			{
				int nBulletType;	// 返された雪玉の情報

				switch (g_player.snowBall.nBallType)
				{
				case BULLETTYPE_SNOW:	// 雪玉
					nBulletType = BreakOrderSnowBall(&g_player.snowBall, BULLETTYPE_SNOW);	// 雪玉作れますか？

					if (nBulletType == BULLETTYPE_SNOW_BIG)
					{
						g_player.charParam.nState = MOTIONTYPE_PLAYER_ATTACK_SUPER;
						g_player.snowBall.nBallType = BULLETTYPE_SNOW_BIG;
					}
					else
					{
						EndSBUI(&g_player.snowBall, nBulletType);			// UI消す
						SetBullet(g_player.aPlayerColiPoint[MODELPOSITION_PLAYER_HAND_R].pos, g_player.rotDest, nBulletType);	// 弾設定
						g_player.snowBall.bSrow = true;
					}

					break;

				case BULLETTYPE_SNOW_BIG:	// 雪玉
					if (g_player.charParam.nCntOcc == -50 && g_player.charParam.nState == MOTIONTYPE_PLAYER_ATTACK_SUPER)
					{

						EndSBUI(&g_player.snowBall, BULLETTYPE_SNOW_BIG);			// UI消す
						SetBullet(g_player.aPlayerColiPoint[MODELPOSITION_PLAYER_HAND_R].pos, g_player.rotDest, BULLETTYPE_SNOW_BIG);	// 弾設定
						g_player.snowBall.bSrow = true;
					}
					break;

				case BULLETTYPE_ICE:	// 氷
					nBulletType = BreakOrderSnowBall(&g_player.snowBall, BULLETTYPE_ICE);	// 雪玉作れますか？
					EndSBUI(&g_player.snowBall, nBulletType);			// UI消す
					SetBullet(g_player.aPlayerColiPoint[MODELPOSITION_PLAYER_HAND_R].pos, g_player.rotDest, nBulletType);	// 弾設定
					g_player.snowBall.bSrow = true;
					break;

				case BULLETTYPE_GRAVEL:	// 砂利玉
					nBulletType = BreakOrderSnowBall(&g_player.snowBall, BULLETTYPE_GRAVEL);	// 雪玉作れますか？
					EndSBUI(&g_player.snowBall, nBulletType);			// UI消す
					SetBullet(g_player.aPlayerColiPoint[MODELPOSITION_PLAYER_HAND_R].pos, g_player.rotDest, nBulletType);	// 弾設定
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
// プレイヤーのダメージ処理
//**************************************************
void HitPlayer(int nDamage)
{
	if (g_player.charParam.nState == MOTIONTYPE_PLAYER_NEUTRAL ||
		g_player.charParam.nState == MOTIONTYPE_PLAYER_RANDING ||
		g_player.charParam.nState == MOTIONTYPE_PLAYER_MOVE ||
		g_player.charParam.nState == MOTIONTYPE_PLAYER_JUMP ||
		g_player.charParam.nState == MOTIONTYPE_PLAYER_ATTACK)
	{// この状態のときは

		g_player.charParam.nLife -= nDamage;	// ダメージ追加
		g_player.charParam.nState = MOTIONTYPE_PLAYER_DAMAGE;	// ダメージ状態
		g_player.charParam.nCntState = 0;	// カウンターゼロ

		// 体力ゲージの長さ更新
		UpdateHPGaugeWidth(&g_player.HPGaugeHave[1], g_player.charParam.nLife);

		// ダメージ音
		PlaySound(SOUND_LABEL_SE_HIT_PLAYER);
	}

	if (g_player.charParam.nLife <= 0)
	{// 体力ないなったら
		g_player.charParam.nState = MOTIONTYPE_PLAYER_DEATH;	// 死んだ

		//フェードアウトする
		SetFade(MODE_RESULT);
		SetResult(RESULTTYPE_GAMEOVER);

		// 影終了
		EndShadow(g_player.nShadowIdx);

		// HPゲージ終わり
		EndHPGauge(&g_player.HPGaugeHave[HPGAUGETYPE_BG]);
		EndHPGauge(&g_player.HPGaugeHave[HPGAUGETYPE_GAUGE]);
		EndHPGauge(&g_player.HPGaugeHave[HPGAUGETYPE_GAUGE_REDZONE]);
	}
}

//************************************************
// プレイヤーの取得
//************************************************
PLAYER* GetPlayer(void)
{
	return &g_player;
}