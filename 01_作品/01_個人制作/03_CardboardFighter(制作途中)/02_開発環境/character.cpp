//*****************************************
// 
// キャラクター
// Author Tetsuji Yamamoto
// 
//*****************************************
#include "character.h"

//*****************************************
// キャラクター
//*****************************************
CCharacter::CCharacter()
{
	m_nLife = 0;								// 寿命
	m_pos = D3DXVECTOR3_NULL;					// 位置
	m_posOld = D3DXVECTOR3_NULL;				// 古い位置
	m_rot = D3DXVECTOR3_NULL;					// 向き
	m_rotDest = D3DXVECTOR3_NULL;				// 目的の向き
	m_move = D3DXVECTOR3_NULL;					// 移動量
	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));	// ワールドマトリックス
	m_pState = NULL;							// 状態
}

//*****************************************
// キャラクター
//*****************************************
CCharacter::~CCharacter()
{
}

//*****************************************
// キャラクター
//*****************************************
HRESULT CCharacter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fHeight,int nLife, float fMovement, int nAppStateCnt)
{
	// 各種変数の初期化
	m_fRadius = fRadius;						// 半径
	m_fHeight = fHeight;						// 高さ
	m_fMovement = fMovement;					// 移動量
	m_nLife = nLife;							// 寿命
	m_pos = pos;								// 位置
	m_rot = rot;								// 向き
	m_rotDest = D3DXVECTOR3_NULL;				// 目的の向き
	ZeroMemory(m_move, sizeof(D3DXVECTOR3));	// 移動量
	D3DXMatrixIdentity(&m_mtxWorld);			// マトリックス

	// 状態生成
	m_pState = CState::Create();

	// 丸影生成
	m_pShadow = CShadow::Create(fRadius);
	return S_OK;
}

//*****************************************
// キャラクター
//*****************************************
void CCharacter::Uninit(void)
{
	if (m_pState != NULL)
	{
		m_pState->Uninit();
		m_pState = NULL;
	}

	delete this;
}

//*****************************************
// キャラクター
//*****************************************
void CCharacter::Update(void)
{
	// 状態処理
	m_pState->StateCountDown();

	// 影の位置設定
	m_pShadow->SetPosition(m_pos);
}

//*****************************************
// キャラクター
//*****************************************
void CCharacter::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを追加
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を追加
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

}

//*****************************************
// キャラクター
//*****************************************
CCharacter* CCharacter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fHeight, int nLife, float fMovement, int nAppStateCnt)
{
	// プレイヤーポインター
	CCharacter* pCharacter = NULL;	

	// メモリを確保
	pCharacter = new CCharacter;

	if (pCharacter != NULL)
	{// ヌルチェック
		// 初期化処理
		pCharacter->Init(pos, rot, fRadius,fHeight, nLife, fMovement, nAppStateCnt);
	}
	else
	{
		MessageBox(NULL, " CObject2D* CObject2D::Create() > if (pObject2D != NULL) メモリを確保できませんでした", "Error", MB_OK);
	}

	return pCharacter;
}

//*****************************************
// キャラクター
//*****************************************
void CCharacter::UpdateRotaition(float fX)
{
	// 角度の正規化
	if (m_rotDest.y > D3DX_PI)
	{
		m_rotDest.y = -D3DX_PI + (m_rotDest.y - D3DX_PI);
	}
	else if (m_rotDest.y < -D3DX_PI)
	{
		m_rotDest.y = D3DX_PI + (m_rotDest.y + D3DX_PI);
	}

	// 角度の正規化
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI + (m_rot.y - D3DX_PI);
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI + (m_rot.y + D3DX_PI);
	}

	// モデルの角度を目的の角度に近づける
	float fDiff = m_rotDest.y - m_rot.y;

	if (fDiff > D3DX_PI)
	{
		fDiff = fDiff - D3DX_PI * 2;
	}
	else if (fDiff < -D3DX_PI)
	{
		fDiff = fDiff + D3DX_PI * 2;
	}

	m_rot.y += (fDiff)*fX;
}

//*****************************************
// キャラクターダメージ状態にする
//*****************************************
void CCharacter::SetDamageState(int nCntState)
{
	// ダメージ状態にする
	m_pState->SetState(CState::STATE_DAMAGE);

	// カウンター設定
	m_pState->SetStateCnt(nCntState);
}
