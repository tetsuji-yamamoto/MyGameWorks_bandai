//*************************************
// 
// オブジェクトステージ
// Author Tetsuji Yamamoto
// 
//*************************************
#include "objectStage.h"
#include "manager.h"
#include "myMath.h"

//*************************************
// オブジェクトステージ処理
//*************************************
CObjectStage::CObjectStage()
{
	m_apIdxTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	ZeroMemory(m_mtxWorld, sizeof(m_mtxWorld));
}

//*************************************
// オブジェクトステージ処理
//*************************************
CObjectStage::~CObjectStage()
{
}

//*************************************
// オブジェクトステージ処理
//*************************************
HRESULT CObjectStage::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pXFileName)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// テクスチャのインスタンス取得
	CTexture* pTexture = CManager::GetTexture();

	// 各種変数の初期化
	m_pos = pos;
	m_rot = rot;

	HRESULT hr;
	hr = D3DXLoadMeshFromX(
		pXFileName,
		D3DXMESH_MANAGED,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh
	);

	if (FAILED(hr))
	{// 失敗したら
		MessageBox(NULL, "CObjectStage::Init() > モデルを読み込めませんでした", "Error", MB_OK);
	}
	else
	{
		//マテリアル辺のポインタを取得
		D3DXMATERIAL* pMat;
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		// テクスチャインデックスのメモリ確保
		m_apIdxTexture = new int[(int)m_dwNumMat];

		// マテリアルの数分回す
		for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
		{
			m_apIdxTexture[nCntMat] = pTexture->Register((const char*)pMat[nCntMat].pTextureFilename);
		}
	}

	// 結果を返す
	return S_OK;
}

//*************************************
// オブジェクトステージ処理
//*************************************
void CObjectStage::Uninit(void)
{
	// マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	// メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// テクスチャインデックスの破棄
	if (m_apIdxTexture != NULL)
	{
		delete[] m_apIdxTexture;
		m_apIdxTexture = NULL;
	}

	// 自分自身を破棄
	delete this;
}

//*************************************
// オブジェクトステージ処理
//*************************************
void CObjectStage::Update(void)
{

}

//*************************************
// オブジェクトステージ処理
//*************************************
void CObjectStage::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// テクスチャのインスタンス取得
	CTexture* pTexture = CManager::GetTexture();

	// 現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを追加
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を追加
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, pTexture->GetAddress(m_apIdxTexture[nCntMat]));

		// モデル(パーツの描画)
		m_pMesh->DrawSubset(nCntMat);
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//*************************************
// オブジェクトステージ処理
//*************************************
void CObjectStage::Draw(D3DXMATRIX* pMtxPearent)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// テクスチャのインスタンス取得
	CTexture* pTexture = CManager::GetTexture();

	// 現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	if (pMtxPearent != NULL)
	{
		m_mtxWorld = *pMtxPearent;
	}

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, pTexture->GetAddress(m_apIdxTexture[nCntMat]));

		// モデル(パーツの描画)
		m_pMesh->DrawSubset(nCntMat);
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}


//*************************************
// オブジェクトステージ処理
//*************************************
CObjectStage* CObjectStage::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pXFileName)
{
	CObjectStage* pObjectStage = NULL;

	// オブジェクトステージの生成
	if (pObjectStage == NULL)
	{
		pObjectStage = new CObjectStage;
		if (pObjectStage != NULL)
		{
			// 初期化処理
			pObjectStage->Init(pos, rot, pXFileName);
		}
		else
		{
			MessageBox(NULL, "CObjectStage::Create() > if ( pObjectStage != NULL) メモリを確保できませんでした", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CObjectStage::Create() > if ( pObjectStage == NULL) メモリを確保できませんでした", "Error", MB_OK);
	}

	return  pObjectStage;
}

//************************************************
// オブジェクトステージがマウスに当たっているか調べる
//************************************************
bool CObjectStage::CollisionMouse(float fRadius)
{
	// マウス取得
	CInputMouse* pInputMouse = CManager::GetInputMouse();

	// 変換後の位置
	D3DXVECTOR3 pos2D;

	// マウスの座標取得
	D3DXVECTOR3 posMouse = pInputMouse->GetPosition();

	// 座標を2D平面座標に変換
	CMyMath::Posision3Dto2D(&pos2D, m_pos);

	D3DXVECTOR2 posA = { pos2D.x, pos2D.y };
	D3DXVECTOR2 posB = { posMouse.x, posMouse.y };

	// マウスと2D位置が重なっていたら
	if (CMyMath::ColiisionCircleCircle2D(posA, fRadius, posB, 0.0f) == true)
	{
		// 当たっている判定
		return true;
	}

	// 当たっていいない判定
	return false;

}

//*************************************
// オブジェクトのの透明度変更
//*************************************
void CObjectStage::SetAlphaColor(float fAlphar)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		pMat[nCntMat].MatD3D.Diffuse.a = fAlphar;
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
	}
}
