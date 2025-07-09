//**************************************************************
// 
// 当たり判定
// Author Tetsuji Yamamoto
// 
//**************************************************************
#include "collision.h"
#include "manager.h"
#include "input.h"

// 静的メンバー変数宣言
bool CCollision::m_bDraw = false;	// 表示の有無

//--------------------------------------------------------------
// 当たり判定クラス

//**************************************************************
// 当たり判定コンストラクタ
//**************************************************************
CCollision::CCollision()
{
	m_bTrigger = false;								// 当たった瞬間かどうか
	m_pos = D3DXVECTOR3_NULL;						// 位置
	m_posOffset = D3DXVECTOR3_NULL;					// 位置オフセット
	ZeroMemory(&m_mtxWorld,sizeof(D3DXMATRIX)) ;	// マトリックス
}

//**************************************************************
// 当たり判定コンストラクタ
//**************************************************************
CCollision::~CCollision()
{
}

//**************************************************************
// 当たり判定処理
//**************************************************************
void CCollision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger)
{
	m_bTrigger = bTrigger;	// 当たった瞬間かどうか
	m_posOffset = pos;		// 位置オフセット
}

//**************************************************************
// 当たり判定処理
//**************************************************************
void CCollision::Uninit(void)
{
	// 自身の破棄
	CObject::Release();
}

//**************************************************************
// 当たり判定処理
//**************************************************************
D3DXMATRIX CCollision::Update(D3DXVECTOR3 posParent, D3DXVECTOR3 rotParent)
{
	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;
	D3DXMATRIX mtxRotParnt, mtxTransParnt, mtxWorldParnt;
	D3DXVECTOR3 rot = D3DXVECTOR3_NULL;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorldParnt);

	// 向きを追加
	D3DXMatrixRotationYawPitchRoll(&mtxRotParnt, rotParent.y, rotParent.x, rotParent.z);
	D3DXMatrixMultiply(&mtxWorldParnt, &mtxWorldParnt, &mtxRotParnt);

	// 位置を追加
	D3DXMatrixTranslation(&mtxTransParnt, posParent.x, posParent.y, posParent.z);
	D3DXMatrixMultiply(&mtxWorldParnt, &mtxWorldParnt, &mtxTransParnt);


	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 向きを追加
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 位置を追加
	D3DXMatrixTranslation(&mtxTrans, m_posOffset.x, m_posOffset.y, m_posOffset.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// 親と掛け合わせる
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxWorldParnt);

	// 位置を更新
	m_pos.x = mtxWorld._41;
	m_pos.y = mtxWorld._42;
	m_pos.z = mtxWorld._43;

	// 結果を返す
	return mtxWorld;
}

//**************************************************************
// 当たり判定更新処理
//**************************************************************
D3DXMATRIX CCollision::Update(D3DXMATRIX mtxParent)
{
	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;
	D3DXVECTOR3 rot = D3DXVECTOR3_NULL;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 向きを追加
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 位置を追加
	D3DXMatrixTranslation(&mtxTrans, m_posOffset.x, m_posOffset.y, m_posOffset.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// 親と掛け合わせるs
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxParent);

	// 位置を更新
	m_pos.x = mtxWorld._41;
	m_pos.y = mtxWorld._42;
	m_pos.z = mtxWorld._43;

	// 結果を返す
	return mtxWorld;
}

//**************************************************************
// 当たり判定描画処理
//**************************************************************
void CCollision::Draw(void)
{

}

//**************************************************************
// 球の当たり判定
//**************************************************************
void CCollision::IsDraw(void)
{
	// キーボード取得
	CInputKeyboard* pInputKeyboard = CManager::GetInputKeyboard();

	// 表示の有無を切り替える
	if (pInputKeyboard->GetTrigger(DIK_F6) == true)
	{
		m_bDraw = !m_bDraw;
	}
}

//--------------------------------------------------------------
// 球の当たり判定クラス

//**************************************************************
// 球の当たり判定コンストラクタ
//**************************************************************
CCollisionSpher::CCollisionSpher()
{
	m_pSpher = NULL;	// 表示用の球
	m_fRadius = 0.0f;	// 半径
	m_nIdxModel = 0;	// モデルインデックス
}

//**************************************************************
// 球の当たり判定デストラクタ
//**************************************************************
CCollisionSpher::~CCollisionSpher()
{
}

//**************************************************************
// 球の当たり判定
//**************************************************************
HRESULT CCollisionSpher::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger,float fRadius, int nIdxModel)
{
	// デバッグモード時のみ実行
#ifdef _DEBUG
	// 球の生成
	m_pSpher = CSphere::Create(8,8,fRadius,D3DXCOLOR(0.0f,0.0f,1.0f,1.0f),NULL);
#endif

	// 当たり判定情報初期化
	CCollision::Init(pos,rot,bTrigger);

	// 半径設定
	m_fRadius = fRadius;

	// インデックス設定
	m_nIdxModel = nIdxModel;

	return S_OK;
}

//**************************************************************
// 球の当たり判定
//**************************************************************
void CCollisionSpher::Uninit(void)
{
	// デバッグモードし時のみ実行
#ifdef _DEBUG
	// 球の破棄
	if (m_pSpher != NULL)
	{
		m_pSpher->Uninit();
		m_pSpher = NULL;
	}
 #endif

	// 自身の破棄
	CCollision::Uninit();
}

//**************************************************************
// 球の当たり判定更新
//**************************************************************
void CCollisionSpher::Update(D3DXVECTOR3 posParent, D3DXVECTOR3 rotParent)
{
	// マトリックスで位置更新
	D3DXMATRIX mtxWorld = CCollision::Update(posParent, rotParent);

	// デバッグモード時のみ実行
#ifdef _DEBUG
	m_pSpher->SetMatrix(mtxWorld);
#endif
}

//**************************************************************
// 球の当たり判定更新
//**************************************************************
void CCollisionSpher::Update(D3DXMATRIX mtxParent)
{
	// マトリックスで位置更新
	D3DXMATRIX mtxWorld = CCollision::Update(mtxParent);

	// デバッグモード時のみ実行
#ifdef _DEBUG
	m_pSpher->SetMatrix(mtxWorld);
#endif
}


//**************************************************************
// 球の当たり判定
//**************************************************************
void CCollisionSpher::Draw(void)
{
	// デバッグモード時のみ実行
#ifdef _DEBUG

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// 描画して良い状態ならば
	if (CCollision::GetIsDraw() == true)
	{
		// ワイヤーフレームオン
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		// 球の描画
		m_pSpher->Draw();

		// ワイヤーフレームオフ
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
#endif
}

//**************************************************************
// 球の当たり判定生成
//**************************************************************
CCollisionSpher* CCollisionSpher::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger, float fRadius, int nIdxModel)
{
	// 球の当たり判定ポインター
	CCollisionSpher* pColiSpher = NULL;

	// オブジェクトの全体数取得
	int nNumAll = CObject::GetObujectNumAll();

	// オブジェクトの最大数を上回らいないようにする
	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	// 球の当たり判定インスタンス生成
	pColiSpher = new CCollisionSpher;

	// メモリの確保ができたなら
	if (pColiSpher != NULL)
	{
		// 初期化処理
		pColiSpher->Init(pos,rot,bTrigger,fRadius, nIdxModel);
	}
	// できなかった
	else
	{
		// メッセージ表示
		MessageBox(NULL, " CCollisionSpher::Create() > メモリを確保できませんでした", "Error", MB_OK);
	}

	// 結果を返す
	return pColiSpher;
}

//-----------------------------------------------------------------
// 円柱の当たり判定

//**************************************************************
// 円柱の当たり判定コンストラクタ
//**************************************************************
CCollisionCylinder::CCollisionCylinder()
{
	m_pCylinder = NULL;	// 表示用の円柱
	m_fRadius = 0.0f;	// 半径
	m_fHeight = 0.0f;	// 高さ
}

//**************************************************************
// 円柱の当たり判定デストラクタ
//**************************************************************
CCollisionCylinder::~CCollisionCylinder()
{
}

//**************************************************************
// 円柱の当たり判定初期化
//**************************************************************
HRESULT CCollisionCylinder::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger, float fRadius, float fHeight)
{
	// デバッグモード時のみ実行
#ifdef _DEBUG
	// 円柱の生成
	m_pCylinder = CCylinder::Create(D3DXVECTOR3_NULL,8, 1, fRadius,fHeight, D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), NULL);
#endif

	// 当たり判定情報初期化
	CCollision::Init(pos, rot, bTrigger);

	// 半径と高さ設定
	m_fRadius = fRadius;
	m_fHeight = fHeight;

	return S_OK;
}

//**************************************************************
// 円柱の当たり判定終了
//**************************************************************
void CCollisionCylinder::Uninit(void)
{
	// デバッグモード時のみ実行
#ifdef _DEBUG
	// 球の破棄
	if (m_pCylinder != NULL)
	{
		m_pCylinder->Uninit();
		m_pCylinder = NULL;
	}
#endif

	// 自身の破棄
	CCollision::Uninit();
}

//**************************************************************
// 円柱の当たり判定更新
//**************************************************************
void CCollisionCylinder::Update(D3DXVECTOR3 posParent, D3DXVECTOR3 rotParent)
{
	// マトリックスで位置更新
	D3DXMATRIX mtxWorld = CCollision::Update(posParent, rotParent);

	// デバッグモード時のみ実行
#ifdef _DEBUG
	m_pCylinder->SetMatrix(mtxWorld);
#endif
}

//**************************************************************
// 円柱の当たり判定描画
//**************************************************************
void CCollisionCylinder::Draw(void)
{
	// デバッグモード時のみ実行
#ifdef _DEBUG

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// 描画して良い状態ならば
	if (CCollision::GetIsDraw() == true)
	{
		// ワイヤーフレームオン
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		// 球の描画
		m_pCylinder->Draw();

		// ワイヤーフレームオフ
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
#endif
}

//**************************************************************
// 円柱の当たり判定生成
//**************************************************************
CCollisionCylinder* CCollisionCylinder::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger, float fRadius, float fHeight)
{
	// 円柱の当たり判定ポインター
	CCollisionCylinder* pColiCyli = NULL;

	// オブジェクトの全体数取得
	int nNumAll = CObject::GetObujectNumAll();

	// オブジェクトの最大数を上回らいないようにする
	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	// 円柱の当たり判定インスタンス生成
	pColiCyli = new CCollisionCylinder;

	// メモリの確保ができたなら
	if (pColiCyli != NULL)
	{
		// 初期化処理
		pColiCyli->Init(pos, rot, bTrigger, fRadius, fHeight);
	}
	// できなかった
	else
	{
		// メッセージ表示
		MessageBox(NULL, " CCollisionCylinder::Create() > メモリを確保できませんでした", "Error", MB_OK);
	}

	// 結果を返す
	return pColiCyli;
}