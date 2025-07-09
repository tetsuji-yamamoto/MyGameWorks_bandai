//**********************************************
// 
// エネミー処理
// Author Tetsuji Yamamoto
// 
//**********************************************
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "particle.h"
#include "texture.h"
#include "object.h"
#include "camera.h"
#include "myMath.h"

//**********************************************
// エネミーコンストラクタ
//**********************************************
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
{
	m_pBlendMotion = NULL;			// モーション
	m_pMotion = NULL;				// モーションブレンド
	m_pCharacter = NULL;			// キャラクタ-
	m_bMove = false;				// 移動の有無
	m_pColiCyliAttckRange = NULL;	// 球の当たり判定(攻撃範囲)
	m_pColiCyliBody = NULL;			// 円柱の当たり判定(体)
	m_pAttack = NULL;				// 攻撃情報
}

//**********************************************
// エネミーデストラクタ
//**********************************************
CEnemy::~CEnemy()
{
}

//**********************************************
// エネミー初期化処理
//**********************************************
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nAppStateCnt, const char* pFilePass)
{
	// ロードモーションファイルポインタ取得
	CLoadMotionFile* pLoadMotionFile = CManager::GetLoadMotionFile();

	// 種類設定
	CObject::SetType(CObject::TYPE_PLAYER);

	// ファイルパスがあれば処理する
	if (pFilePass != NULL)
	{
		// モーションファイルを読み込む
		pLoadMotionFile->Load(pFilePass);

		// キャラクターセットの取得
		CCharacterSet* pCharcterSet = pLoadMotionFile->GetCharacterSet();

		// 各種パラメータの取得
		float fMoveMent = pCharcterSet->GetMovement();
		float fJump = pCharcterSet->GetJump();
		float fRadiusu = pCharcterSet->GetRadius();
		float fHeight = pCharcterSet->GetHeight();
		int nLife = pCharcterSet->GetLife();

		// 各種変数初期化
		m_pCharacter = CCharacter::Create(pos, rot, fRadiusu, fHeight,nLife, fMoveMent, nAppStateCnt);	// キャラクター情報
		m_bMove = false;		// 移動の有無

		// キャラクター情報取得
		CCharacterSet* pCharacterSet = pLoadMotionFile->GetCharacterSet();

		// パーツ数取得
		m_nNumModel = pCharacterSet->GetNumParts();

		// モデルの読み取った情報をもらう
		pLoadMotionFile->CopyModel(&m_pModel);

		// モーションの読み取った情報をもらう
		pLoadMotionFile->CopyMotion(&m_pMotion);
		pLoadMotionFile->CopyMotion(&m_pBlendMotion);

		// モデルを設定
		m_pMotion->SetModel(&m_pModel);

		// 球の当たり判定生成
		CCollisionSpher* oColiSpher = CCollisionSpher::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3_NULL, false, 20.0f, 12);
		m_pColiSpherAttack.push_back(oColiSpher);

		CCollisionSpher* oColiSpherB = CCollisionSpher::Create(D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXVECTOR3_NULL, false, 20.0f, 12);
		m_pColiSpherAttack.push_back(oColiSpherB);

		// 球の当たり判定(攻撃範囲)
		m_pColiCyliAttckRange = CCollisionCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, -30.0f),D3DXVECTOR3_NULL,false,fRadiusu, fHeight);
		
		// 円柱の当たり判定(体)
		m_pColiCyliBody = CCollisionCylinder::Create(D3DXVECTOR3_NULL, D3DXVECTOR3_NULL,false,fRadiusu,fHeight);

		// 攻撃情報の生成
		m_pAttack = CAttack::Create();
	}

	return S_OK;
}

//**********************************************
//  エネミー終了処理
//**********************************************
void CEnemy::Uninit()
{
	if (m_pModel.size() > 0)
	{// モデルパーツがあるのならば破棄してNULLにする
		for (auto& iter : m_pModel)
		{
			iter->Uninit();
		}
		m_pModel.clear();
	}

	if (m_pCharacter != NULL)
	{// キャラクター情報破棄
		m_pCharacter->Uninit();
		m_pCharacter = NULL;
	}

	// モーション情報があれば破棄
	if (m_pMotion != NULL)
	{
		m_pMotion->Uninit();
		m_pMotion = NULL;
	}

	// モーション情報があれば破棄
	if (m_pBlendMotion != NULL)
	{
		m_pBlendMotion->Uninit();
		m_pBlendMotion = NULL;
	}

	// 球の当たり判定の破棄
	m_pColiSpherAttack.clear();

	// 球の当たり判定(攻撃検知)
	if (m_pColiCyliAttckRange != NULL)
	{
		m_pColiCyliAttckRange = NULL;
	}

	// 円柱の当たり判定(体)
	if (m_pColiCyliBody != NULL)
	{
		m_pColiCyliBody = NULL;
	}

	// 攻撃の破棄
	if (m_pAttack != NULL)
	{
		m_pAttack->Uninit();
		m_pAttack = NULL;
	}

	// 自身の破棄
	Release();
}

//**********************************************
//  エネミー更新処理
//**********************************************
void CEnemy::Update()
{
	CInputKeyboard* pInputKeyboard = CManager::GetInputKeyboard();	// キーボード取得
	CInputMouse* pInputMouce = CManager::GetInputMouse();			// マウス取得
	CInputJoypad* pInputJoypad = CManager::GetInputJoypad();		// ジョイパッド取得
	CCamera* pCamera = CManager::GetCamera();						// カメラ取得
	CStage* pStage = CManager::GetStage();							// ステージの取得
	CMeshField* pMeshField = pStage->GetMeshField();				// メッシュフィールドの取得
	std::vector<CWall*> pWall = pStage->Getwall();					// 壁取得
	CPlayer* pPlayer = CManager::GetPlayer();						// プレイヤーの取得
	D3DXVECTOR3 rotCamera = pCamera->GetRotation();					// カメラの向き
	CState state = m_pCharacter->GetState();						// 状態取得
	D3DXVECTOR3 pos = m_pCharacter->GetPosition();					// 位置を取得
	D3DXVECTOR3 posOld = m_pCharacter->GetPositionOld();			// 古い位置を取得
	D3DXVECTOR3 rot = m_pCharacter->GetRotation();					// 向きを取得
	D3DXVECTOR3 rotDest = m_pCharacter->GetRotationDest();			// 目的の向きを取得
	D3DXVECTOR3 move = m_pCharacter->GetMove();						// 移動量を取得
	float fMovement = m_pCharacter->GetMovement();					// 移動値を取得

	m_bMove = false;			// 移動していない状態にする
	float fAngleMove = 0.0f;	// 移動する角度

	// 攻撃のアップデート
	m_pAttack->Update();

	// 攻撃範囲にプレイヤーがいて、攻撃していない状態であれば
	if (IsAttackPlayer() == true)
	{
		// 攻撃モーションに変更
		m_pMotion->SetMotionblend(m_pBlendMotion, MOTION_ATTACK, 20);
		m_pAttack->Set(5,120,130,5);
	}
	// 攻撃していない状態であれば
	else if(m_pAttack->GetIsAttackEnd() == true)
	{
		// 動く状態であれば
		if (m_bMove == true)
		{
			// 移動量の計算
			move.x += sinf(fAngleMove) * fMovement;
			move.z += cosf(fAngleMove) * fMovement;

			// 角度の更新
			m_pCharacter->SetRotationDestY(fAngleMove + D3DX_PI);

			// 走るモーションに変更
			m_pMotion->SetMotionblend(m_pBlendMotion, MOTION_MOVE, 20);
		}
		else
		{
			// 待機モーションに変更
			m_pMotion->SetMotionblend(m_pBlendMotion, MOTION_NONE, 60);
		}
	}

	// 角度の更新
	m_pCharacter->UpdateRotaition(0.3f);

	// 古い位置の更新
	posOld = pos;

	// 重力
	move.y -= 2.0f;

	// 慣性の計算
	move.x += -move.x * FRICTION_VALUE;
	move.z += -move.z * FRICTION_VALUE;

	// 位置に移動量を追加
	pos += move;

	if (pInputKeyboard->GetRelease(DIK_W) == true)
	{
		int a = 0;
	}

	// 壁との当たり判定
	if (pWall.capacity() > 0)
	{
		for (auto& iter : pWall)
		{
			iter->CollisionWall(&pos, posOld);
		}
	}

	// メッシュフィールドとの当たり判定
	if (pMeshField != NULL)
	{
		pMeshField->Collision(&pos);
	}

	// 下限まで落ちないようにする
	if (pos.y <= 0.0f)
	{
		pos.y = 0.0f;
		move.y = 0.0f;
	}

	m_pCharacter->SetPosition(pos);			// 位置を設定
	m_pCharacter->SetPositionOld(posOld);	// 古い位置を設定
	m_pCharacter->SetMove(move);			// 移動量を設定

	// キャラクターアップデート
	m_pCharacter->Update();

	// 状態取得
	int nState = state.GetState();

	// 状態による処理
	switch (nState)
	{
	case CState::STATE_NONE:
		break;

	case CState::STATE_DAMAGE:
		break;

	default:
		break;
	}

	// 当たり判定更新(モーションの更新前に処理すること)
	for (auto& iterColiSpher : m_pColiSpherAttack)
	{
		// モデルのマトリックスを取得する
		int nIdxModel = iterColiSpher->GetIndexModel();
		auto iterModel = m_pModel.begin() + nIdxModel;
		D3DXMATRIX mtxModel = (*iterModel)->GetMatrix();
		iterColiSpher->Update(mtxModel);
	}

	// 当たり判定更新
	m_pColiCyliAttckRange->Update(pos, rot);
	m_pColiCyliBody->Update(pos, rot);

	// モーションのアップデート
	m_pMotion->UpdateMotionModelBlend(m_pBlendMotion);

	// 攻撃判定が出る時間ならを出していい場合なら
	if (m_pAttack->GetIsAttackTime() == true)
	{
		// 自身の攻撃がプレイヤーへ当たっているか調べる
		if (IsCollisionAttackPlayer() == true)
		{
			// 攻撃が終わった状態にする
			m_pAttack->SetIsAttackEnd(false);

			// プレイヤーのヒット処理
			pPlayer->Hit(0,30);
		}
	}
}

//**********************************************
// エネミー描画処理
//**********************************************
void CEnemy::Draw()
{
	// キャラクター描画
	m_pCharacter->Draw();

	if (m_pModel.size() > 0)
	{// モデルパーツがあるのならば描画
		for (auto& iter : m_pModel)
		{
			iter->DrawParentChild();
		}
	}
}

//**********************************************
// エネミー生成処理
//**********************************************
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nLife, float fMovement, float fFrictionValue, int nAppStateCnt)
{
	// オブジェクトの全体数取得
	int nNumAll = GetObujectNumAll();	

	// オブジェクトの全体数を上回るなら処理しない
	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	// エネミーの生成
	CEnemy* pEnemy = new CEnemy;
	
	// メモリを確保できた
	if (pEnemy != NULL)
	{
		// 初期化処理
		pEnemy->Init(pos, rot, nAppStateCnt);
	}
	// メモリを確保できなかった
	else
	{
		MessageBox(NULL, " CEnemy::Create() > メモリを確保できませんでした", "Error", MB_OK);
	}

	// 結果を返す
	return pEnemy;
}

//****************************************************************************
// エネミー
//****************************************************************************
void CEnemy::Hit(int nDamage)
{

}

//****************************************************************************
// エネミーの円柱と円柱の当たり判定
//****************************************************************************
void CEnemy::CollisionCylinderCylinder(D3DXVECTOR3 * pPosPartner, float fHeightPartner, float fRadiusPartner)
{
	// 位置と古い位置の取得
	D3DXVECTOR3 pos = m_pCharacter->GetPosition();
	D3DXVECTOR3 posOld = m_pCharacter->GetPositionOld();

	// 半径取得
	float fRadius = m_pColiCyliBody->GetRadius();
	
	// 高さ取得
	float fHeight = m_pColiCyliBody->GetHeight();

	// 当たっていなかったら処理を止める
	if (CMyMath::ColiisionCylinderCylinder(pos,fRadius,fHeight,*pPosPartner,fRadiusPartner,fHeightPartner) == false)
	{
		return;
	}
	
	// D3DXVECTOR3からD3DXVECTOR2へ移し替える
	D3DXVECTOR2 pos2D, pos2DPar;
	pos2D.x = pos.x;
	pos2D.y = pos.z;
	pos2DPar.x = pPosPartner->x;
	pos2DPar.y = pPosPartner->z;

	// 限界の長さ
	float fLimitLength = fRadius + fRadiusPartner;

	// 点と点の長さを図る
	float fLength = CMyMath::LengthTrigonometric2D(pos2D, pos2DPar);

	// 限界の長さより短ければ当たっている判定
	if (fLength <= fLimitLength)
	{
		CStage* pStage = CManager::GetStage();							// ステージの取得
		std::vector<CWall*> pWall = pStage->Getwall();					// 壁取得

		// 円と円の重なった部分の間の長さの半分を取る
		float fSpaceLength = (fLimitLength - fLength) * 0.5f;

		// 自身から相手への向きベクトルを取る
		D3DXVECTOR3 vecPos;
		vecPos.x = pos.x - pPosPartner->x;
		vecPos.y = 0.0f;
		vecPos.z = pos.z - pPosPartner->z;

		// 正規化する
		D3DXVec3Normalize(&vecPos, &vecPos);

		// 押し返すベクトルを求める
		D3DXVECTOR3 vecPush = vecPos * fSpaceLength;

		// 押し返す
		pos += vecPush;
		*pPosPartner -= vecPush;

		// 壁との当たり判定
		if (pWall.capacity() > 0)
		{
			for (auto& iter : pWall)
			{
				iter->CollisionWall(&pos, posOld);
			}
		}

		// 位置を設定
		m_pCharacter->SetPosition(pos);
	}
}

//****************************************************************************
// エネミープレイヤーへのアタックの判断処理
//****************************************************************************
bool CEnemy::IsAttackPlayer(void)
{
	// プレイヤーの取得
	CPlayer*pPlayer = CManager::GetPlayer();

	// プレイヤーの体の当たり判定取得
	CCollisionCylinder* pColiCyliPlayer = pPlayer->GetCollisionCylinder();

	// プレイヤーの当たり判定位置と半径と高さを取得
	D3DXVECTOR3 posPlayer = pColiCyliPlayer->GetPosition();
	float fRadiusPlayer = pColiCyliPlayer->GetRadius();
 	float fHeightPlayer = pColiCyliPlayer->GetHeight();

	// 自身の攻撃範囲の位置と半径と高さの取得s
	D3DXVECTOR3 pos = m_pColiCyliAttckRange->GetPosition();
	float fRadius = m_pColiCyliAttckRange->GetRadius();
	float fHeight = m_pColiCyliAttckRange->GetHeight();

	// 当たっていなかったら処理を止める
	if (CMyMath::ColiisionCylinderCylinder(pos, fRadius, fHeight, posPlayer, fRadiusPlayer, fHeightPlayer) == false)
	{
		// 攻撃範囲に入っていないと判断する
		return false;
	}

	// 攻撃範囲に入っていると判断する
	return true;
}

//****************************************************************************
// エネミープレイヤーへ攻撃の判定を調べる処理
//****************************************************************************
bool CEnemy::IsCollisionAttackPlayer(void)
{
	// プレイヤーの取得
	CPlayer* pPlayer = CManager::GetPlayer();

	// プレイヤーの体の当たり判定取得
	std::vector<CCollisionSpher*> pColiSpherPlayer = pPlayer->GetCollisionSpher();

	// 自身の攻撃判定の数分回す
	for (auto& iterColiSpherAttack : m_pColiSpherAttack)
	{
		// エネミーの当たり判定位置と半径を取得
		D3DXVECTOR3 posEnemy = iterColiSpherAttack->GetPosition();
		float fRadiusEnemy = iterColiSpherAttack->GetRadius();

		// プレイヤーの受ける判定分回す
		for (auto& iterColiSpherPlayer : pColiSpherPlayer)
		{
			// プレイヤーの当たり判定位置と半径を取得
			D3DXVECTOR3 posPlayer = iterColiSpherPlayer->GetPosition();
			float fRadiusPlayer = iterColiSpherPlayer->GetRadius();

			// 球と球の当たり判定で調べる
			if (CMyMath::ColiisionSpherSpher(posEnemy, fRadiusEnemy, posPlayer, fRadiusPlayer) == true)
			{
				// 当たっていると判定し処理を止める
				return true;
			}
		}
	}

	// 当たっていない判定
	return false;
}