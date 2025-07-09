//****************************************************************************
// 
// 弾
// Author tetuji yamamoto
// 
//****************************************************************************
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "player.h"
#include "effect.h"
#include "texture.h"
#include "easing.h"

//****************************************************************************
// 弾コンストラクタ
//****************************************************************************
CBullet::CBullet(int nPriority) :CObject2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_fMovement = 0.0f;
	m_nLife = 0;
	m_nMaxLife = 0;
	m_nDamage = 0;
}

//****************************************************************************
// 弾デストラクタ
//****************************************************************************
CBullet::~CBullet()
{

}

//****************************************************************************
// 弾初期化処理
//****************************************************************************
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDamage,float fMovement, float fWidth, float fHeight)
{
	// 初期化処理
	CObject2D::Init(pos, rot,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), fWidth, fHeight);

	// タイプ設定
	CObject::SetType(CObject::TYPE_BULLET);

	// 各種変数の初期化
	m_move.x = sinf(rot.z) * fMovement;
	m_move.y = cosf(rot.z) * fMovement;
	m_fMovement = fMovement;
	m_nLife = 180;
	m_nMaxLife = m_nLife;
	m_nDamage = nDamage;

	return S_OK;
}

//****************************************************************************
// 弾終了処理
//****************************************************************************
void CBullet::Uninit(void)
{
	CObject2D::Uninit();
}

//****************************************************************************
// 弾更新処理
//****************************************************************************
void CBullet::Update(void)
{
	D3DXVECTOR3 pos = CObject2D::GetPosition();
	
	m_nLife--;

	if (m_nLife <= 0)
	{
		CObject2D::Uninit();
		CExplosion::Create(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50.0f, 50.0f, 60, 8, 1);
		return;
	}

	if (pos.x <= 0.0f || pos.x >= SCREEN_WIDTH ||
		pos.y <= 0.0f || pos.y >= SCREEN_HEIGHT)
	{
		CObject2D::Uninit();
		return;
	}

	// 位置設定
	CObject2D::SetPosition(pos);


	CObject2D::Update();
}

//****************************************************************************
// 弾描画処理
//****************************************************************************
void CBullet::Draw(void)
{
	CObject2D::Draw();
}

//---------------------------------------------------------------------------------
// 弾プレイヤー

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
CBulletPlayer::CBulletPlayer(int nPriority):CBullet(nPriority)
{

}

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
CBulletPlayer::~CBulletPlayer()
{

}

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
HRESULT CBulletPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDamage, float fMovement, float fWidth, float fHeight)
{
	// バレットクラスの初期化
	CBullet::Init(pos, rot, nDamage, fMovement, fWidth, fHeight);

	// テクスチャンのインデックス設定
	CObject2D::SetIdxTexture(CTexture::TEXTURE_BULLET);

	return S_OK;
}

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
void CBulletPlayer::Uninit(void)
{
	CBullet::Uninit();
}

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
void CBulletPlayer::Update(void)
{
	CBullet::Update();

	D3DXVECTOR3 pos = CObject2D::GetPosition();
	D3DXVECTOR3 move = CBullet::GetMove();
	D3DXVECTOR3 moveEasing;
	int nNowLife = CBullet::GetLife();
	int nMaxLife = CBullet::GetMaxLife();
	float fMovement = CBullet::GetMovement();
	//CEnemy* pEnemy = CEnemy::GetEnemy(pos,500.0f);

	float fMugLife = (float)nNowLife / (float)nMaxLife;
	fMugLife = 1.0f - fMugLife;
	float fEasing = SelectEasing(EASING_TYPE_EaseInOutSine, fMugLife);

	//if (pEnemy != NULL)
	//{
	//	D3DXVECTOR3 posEnemy = pEnemy->CObject2D::GetPosition();
	//
	//	D3DXVECTOR3 addMove = posEnemy - pos;
	//	float fLength = sqrtf((addMove.x * addMove.x) + (addMove.y * addMove.y));
	//
	//	addMove /= fLength;
	//	addMove *= fMovement;
	//
	//	move = (move * (1.0f - fEasing)) + (addMove * fEasing);
	//	CBullet::SetMove(move);
	//}
	//pEnemy = NULL;

	moveEasing.x = move.x * fEasing;
	moveEasing.y = move.y * fEasing;
	moveEasing.z = 0.0f;

	pos += move;

	CObject2D::SetPosition(pos);


	if (CollisionEnemy(pos) == true)
	{
		return;
	}

	CEffect2DNomal::Create(pos, D3DXVECTOR3_NULL, D3DXCOLOR(0.2f, 1.0f, 1.0f, 1.0f), 60, 60.0f, 60.0f);
}

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
void CBulletPlayer::Draw(void)
{
	CBullet::Draw();
}

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
CBulletPlayer* CBulletPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDamage, float fMovement, float fWidth, float fHeight)
{
	CBulletPlayer* pBulletP = NULL;
	int nNumAll = GetObujectNumAll();

	// オブジェクト2Dの生成
	if (pBulletP == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pBulletP = new CBulletPlayer(CObject::PRIORITY_4);
		if (pBulletP != NULL)
		{
			// 初期化処理
			pBulletP->Init(pos, rot, nDamage, fMovement, fWidth, fHeight);
		}
		else
		{
			MessageBox(NULL, " CBullet* CBullet::Create() > if ( pBullet != NULL) メモリを確保できませんでした", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CBullet* CBullet::Create() > if ( pBullet == NULL) メモリを確保できませんでした", "Error", MB_OK);
	}

	return  pBulletP;
}

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
bool CBulletPlayer::CollisionEnemy(D3DXVECTOR3 pos)
{
	//for (int nCntPri = 0; nCntPri < CObject::PRIORITY_MAX; nCntPri++)
	//{
	//	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	//	{
	//		CEnemy* pObj = NULL;

	//		// オブジェクトを取得
	//		pObj = (CEnemy*)CObject::Getobject(nCntObj, nCntPri);

	//		if (pObj != NULL)
	//		{
	//			CObject::TYPE type;

	//			// 種類を取得
	//			type = pObj->GetType();

	//			if (type == CObject::TYPE_ENEMY)
	//			{// 種類が敵だった場合
	//				//D3DXVECTOR3 posObj = pObj->GetPosition();
	//				//D3DXVECTOR3 posMy = this->GetPosition();
	//				//float fWidthObj = pObj->GetWidth();
	//				//float fHeightObj = pObj->GetHeight();

	//				//if (posMy.x >= posObj.x - fWidthObj &&	// 左より右
	//				//	posMy.x <= posObj.x + fWidthObj &&	// 右より左
	//				//	posMy.y >= posObj.y - fHeightObj && // 上より下
	//				//	posMy.y <= posObj.y + fHeightObj	// 下より上
	//				//	)
	//				//{// 敵と重なった
	//				//	pObj->Hit(1);
	//				//	CObject2D::Uninit();
	//				//	CExplosion::Create(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100.0f, 100.0f, 60, 8, 1);
	//				//	return true;
	//				//}
	//			}
	//		}
	//	}
	//}
	return false;
}

//---------------------------------------------------------------------------------
// 弾エネミー

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
CBulletEnemy::CBulletEnemy(int nPriority) :CBullet(nPriority)
{

}

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
CBulletEnemy::~CBulletEnemy()
{

}

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
HRESULT CBulletEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDamage, float fMovement, float fWidth, float fHeight)
{
	// バレットクラスの初期化
	CBullet::Init(pos, rot, nDamage, fMovement, fWidth, fHeight);

	// テクスチャンのインデックス設定
	CObject2D::SetIdxTexture(CTexture::TEXTURE_BULLET);

	return S_OK;
}

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
void CBulletEnemy::Uninit(void)
{
	CBullet::Uninit();
}

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
void CBulletEnemy::Update(void)
{
	CBullet::Update();

	D3DXVECTOR3 pos = CObject2D::GetPosition();
	D3DXVECTOR3 move = CBullet::GetMove();

	pos += move;

	CObject2D::SetPosition(pos);


	if (CollisionPlayer(pos) == true)
	{
		return;
	}

	CEffect2DNomal::Create(pos, D3DXVECTOR3_NULL, D3DXCOLOR(1.0f, 0.8f, 0.0f, 1.0f), 60, 60.0f, 60.0f);
}

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
void CBulletEnemy::Draw(void)
{
	CBullet::Draw();
}

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
CBulletEnemy* CBulletEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDamage, float fMovement, float fWidth, float fHeight)
{
	CBulletEnemy* pBulletP = NULL;
	int nNumAll = GetObujectNumAll();

	// オブジェクト2Dの生成
	if (pBulletP == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pBulletP = new CBulletEnemy(CObject::PRIORITY_4);
		if (pBulletP != NULL)
		{
			// 初期化処理
			pBulletP->Init(pos, rot, nDamage, fMovement, fWidth, fHeight);
		}
		else
		{
			MessageBox(NULL, " CBullet* CBullet::Create() > if ( pBullet != NULL) メモリを確保できませんでした", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CBullet* CBullet::Create() > if ( pBullet == NULL) メモリを確保できませんでした", "Error", MB_OK);
	}

	return  pBulletP;
}

//****************************************************************************
// 弾の当たり判定処理
//****************************************************************************
bool CBulletEnemy::CollisionPlayer(D3DXVECTOR3 pos)
{
	//for (int nCntPri = 0; nCntPri < CObject::PRIORITY_MAX; nCntPri++)
	//{
	//	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	//	{
	//		CPlayer * pObj = NULL;
	//
	//		// オブジェクトを取得
	//		pObj = (CPlayer*)CObject::Getobject(nCntObj, nCntPri);
	//
	//		if (pObj != NULL)
	//		{
	//			CObject::TYPE type;
	//
	//			// 種類を取得
	//			type = pObj->GetType();
	//
	//			if (type == CObject::TYPE_PLAYER)
	//			{// 種類が敵だった場合
	//				D3DXVECTOR3 posObj = pObj->GetPosition();
	//				D3DXVECTOR3 posMy = this->GetPosition();
	//				float fWidthObj = pObj->GetWidth();
	//				float fHeightObj = pObj->GetHeight();
	//
	//				if (posMy.x >= posObj.x - fWidthObj &&	// 左より右
	//					posMy.x <= posObj.x + fWidthObj &&	// 右より左
	//					posMy.y >= posObj.y - fHeightObj && // 上より下
	//					posMy.y <= posObj.y + fHeightObj	// 下より上
	//					)
	//				{// プレイヤーと重なった
	//					pObj->Hit(1);
	//					CObject2D::Uninit();
	//					CExplosion::Create(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100.0f, 100.0f, 60, 8, 1);
	//					return true;
	//				}
	//			}
	//		}
	//	}
	//}
	return false;
}