//**********************************************
// 
// プレイヤー処理
// Author Tetsuji Yamamoto
// 
//**********************************************
#include "player.h"
#include "manager.h"
#include "input.h"
#include "particle.h"
#include "texture.h"
#include "object.h"
#include "camera.h"

//**********************************************
// プレイヤーコンストラクタ
//**********************************************
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	m_pBlendMotion = NULL;	// モーション
	m_pMotion = NULL;		// モーションブレンド
	m_pCharacter = NULL;	// キャラクタ-
	m_bMove = false;		// 移動の有無
	m_pColiCyli = NULL;		// 円柱の当たり判定
}

//**********************************************
// プレイヤーデストラクタ
//**********************************************
CPlayer::~CPlayer()
{
}

//**********************************************
// プレイヤー初期化処理
//**********************************************
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nAppStateCnt, const char* pFilePass)
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
		m_pCharacter = CCharacter::Create(pos, rot, fRadiusu,fHeight, nLife, fMoveMent, nAppStateCnt);	// キャラクター情報
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
		CCollisionSpher* oColiSpher = CCollisionSpher::Create(D3DXVECTOR3_NULL, D3DXVECTOR3_NULL,false,15.0f,0);
		m_pColiSpher.push_back(oColiSpher);

		CCollisionSpher* oColiSpherB = CCollisionSpher::Create(D3DXVECTOR3(0.0f,30.0f,0.0f), D3DXVECTOR3_NULL,false,15.0f,0);
		m_pColiSpher.push_back(oColiSpherB);

		// 円柱の当たり判定生成
		m_pColiCyli = CCollisionCylinder::Create(D3DXVECTOR3_NULL, D3DXVECTOR3_NULL, false, fRadiusu,fHeight);
	}

	return S_OK;
}

//**********************************************
//  プレイヤー終了処理
//**********************************************
void CPlayer::Uninit()
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
	for (auto& iter : m_pColiSpher)
	{
		iter->Uninit();
	}
	m_pColiSpher.clear();

	// 円柱の当たり判定の破棄
	if (m_pColiCyli != NULL)
	{
		m_pColiCyli = NULL;
	}

	// 自身の破棄
	Release();
}

//**********************************************
//  プレイヤー更新処理
//**********************************************
void CPlayer::Update()
{
	CInputKeyboard* pInputKeyboard = CManager::GetInputKeyboard();	// キーボード取得
	CInputMouse* pInputMouce = CManager::GetInputMouse();			// マウス取得
	CInputJoypad* pInputJoypad = CManager::GetInputJoypad();		// ジョイパッド取得
	CCamera* pCamera = CManager::GetCamera();						// カメラ取得
	CStage* pStage = CManager::GetStage();							// ステージの取得
	CMeshField* pMeshField = pStage->GetMeshField();				// メッシュフィールドの取得
	std::vector<CWall*> pWall = pStage->Getwall();					// 壁取得
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

	if (pInputKeyboard->GetPress(DIK_W) == true ||
		pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_UP) == true)
	{// 上移動
		if (pInputKeyboard->GetPress(DIK_A) == true ||
			pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_LEFT) == true)
		{// 左上移動
			fAngleMove = rotCamera.y + ANGLE_UP_LEFT;	// カメラを含めた角度計算
			m_bMove = true;								// 移動している状態にす
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true ||
			pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_RIGHT) == true)
		{// 右上移動
			fAngleMove = rotCamera.y + ANGLE_UP_RIGHT;	// カメラを含めた角度計算
			m_bMove = true;								// 移動している状態にす
		}
		else
		{// 上移動
			fAngleMove = rotCamera.y + ANGLE_UP;	// カメラを含めた角度計算
			m_bMove = true;							// 移動している状態にす
		}
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true ||
		pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_DOWN) == true)
	{// 下移動

		if (pInputKeyboard->GetPress(DIK_A) == true ||
			pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_LEFT) == true)
		{// 左下移動
			fAngleMove = rotCamera.y + ANGLE_DOWN_LEFT;	// カメラを含めた角度計算
			m_bMove = true;							// 移動している状態にす
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true ||
			pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_RIGHT) == true)
		{// 右下移動
			fAngleMove = rotCamera.y + ANGLE_DOWN_RIGHT;	// カメラを含めた角度計算
			m_bMove = true;									// 移動している状態にす
		}
		else
		{// 下移動
			fAngleMove = rotCamera.y + ANGLE_DOWN;	// カメラを含めた角度計算
			m_bMove = true;								// 移動している状態にす
		}
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true ||
		pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_LEFT) == true)
	{// 左移動
		fAngleMove = rotCamera.y + ANGLE_LEFT;	// カメラを含めた角度計算
		m_bMove = true;							// 移動している状態にす
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true ||
		pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_RIGHT) == true)
	{// 右移動
		fAngleMove = rotCamera.y + ANGLE_RIGHT;	// カメラを含めた角度計算
		m_bMove = true;							// 移動している状態にす
	}

	// 動く状態であれば
	if (m_bMove == true)
	{
		// 移動量の計算
		move.x += sinf(fAngleMove) * fMovement;
		move.z += cosf(fAngleMove) * fMovement;

		// 角度の更新
		m_pCharacter->SetRotationDestY(fAngleMove + D3DX_PI);

		// 走るモーションに変更
		//m_pMotion->SetMotion(MOTION_MOVE);
		m_pMotion->SetMotionblend(m_pBlendMotion, MOTION_MOVE, 20);
	}
	else
	{
		// 待機モーションに変更
		m_pMotion->SetMotionblend(m_pBlendMotion, MOTION_NONE, 30);
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

	// 高さと幅を取得
	float fHeight = m_pCharacter->GetHeight();
	float fRadius = m_pCharacter->GetRadius();

	// 敵との当たり判定
	for (auto& iter : CManager::GetEnmey())
	{
		iter->CollisionCylinderCylinder(&pos, fHeight,fRadius);
	}


	// 壁との当たり判定
	if (pWall.capacity() > 0)
	{
		for (auto& iter : pWall)
		{
			if (iter->CollisionWall(&pos, posOld))
			{

			}
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
		// 通常状態
	case CState::STATE_NONE:
		break;

		// ダメージ状態
	case CState::STATE_DAMAGE:
		break;

	default:
		break;
	}

	// 当たり判定更新(モーションの更新前に処理すること)
	for (auto& iterColiSpher : m_pColiSpher)
	{
		// モデルのマトリックスを取得する
		int nIdxModel = iterColiSpher->GetIndexModel();
		auto iterModel = m_pModel.begin() + nIdxModel;
		D3DXMATRIX mtxModel = (*iterModel)->GetMatrix();
		iterColiSpher->Update(mtxModel);
	}
	m_pColiCyli->Update(pos, rot);

	// モーションのアップデート
	m_pMotion->UpdateMotionModelBlend(m_pBlendMotion);

	// 追従カメラにする
	pCamera->FollowCamera(pos);
}

//**********************************************
// プレイヤー描画処理
//**********************************************
void CPlayer::Draw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 状態取得
	CState state = m_pCharacter->GetState();
	
	// モデルに適用する色
	D3DXCOLOR* pCol = NULL;

	// ダメージ色変数
	D3DXCOLOR colDamage;

	// 状態取得
	int nState = state.GetState();

	// 状態による処理
	switch (nState)
	{
		// 通常状態
	case CState::STATE_NONE:
		break;

		// ダメージ状態
	case CState::STATE_DAMAGE:
		// 色を設定
		colDamage.r = 1.0f;
		colDamage.g = 0.0f;
		colDamage.b = 0.0f;
		colDamage.a = 1.0f;

		// ダメージ色を覚えさせる
		pCol = &colDamage;
		break;

	default:
		break;
	}

	// キャラクター描画
	m_pCharacter->Draw();

	if (m_pModel.size() > 0)
	{// モデルパーツがあるのならば描画
		for (auto& iter : m_pModel)
		{
			iter->DrawParentChild(pCol);
		}
	}
}

//**********************************************
// プレイヤー生成処理
//**********************************************
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nLife, float fMovement, float fFrictionValue, int nAppStateCnt)
{
	CPlayer* pPlayer = NULL;			// プレイヤーポインター
	int nNumAll = GetObujectNumAll();	// オブジェクトの全体数取得

	// プレイヤーの生成
	if (pPlayer == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pPlayer = new CPlayer;
		if (pPlayer != NULL)
		{
			// 初期化処理
			pPlayer->Init(pos, rot, nAppStateCnt);
		}
		else
		{
			MessageBox(NULL, " CPlayer::Create() > if (pPlayer != NULL) メモリを確保できませんでした", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CObject2D* CObject2D::Create() > if (pObject2D == NULL) メモリを確保できませんでした", "Error", MB_OK);
	}

	return pPlayer;

}

//****************************************************************************
// プレイヤーヒット処理
//****************************************************************************
void CPlayer::Hit(int nDamage,int nCntState)
{
	// 現在の体力取得
	int nLifeNow = m_pCharacter->GetLife();

	// 受けたダメージを追加
	nLifeNow += nDamage;

	// 体力を設定
	m_pCharacter->SetLife(nLifeNow);
	
	// 体力がなくなってしまった
	if (nLifeNow < 0)
	{

	}
	// まだ体力がある
	else
	{
		// ダメージ状態にする
		m_pCharacter->SetDamageState(nCntState);
	}
}