//*************************************
// 
// モデル
// Author Tetsuji Yamamoto
// 
//*************************************
#include "model.h"
#include "manager.h"
#include "myMath.h"

//*************************************
// モデル
//*************************************
CModel::CModel()
{
	m_dwNumMat = 0;
	m_apIdxTexture = NULL;
	m_pBuffMat = NULL;
	m_pMesh = NULL;

	ZeroMemory(m_pos, sizeof(D3DXVECTOR3));
	ZeroMemory(m_rot, sizeof(D3DXVECTOR3));
	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));
	m_pParent = NULL;
}

//*************************************
// モデル
//*************************************
CModel::~CModel()
{
}

//*************************************
// モデル
//*************************************
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pXFileName)
{

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// テクスチャのインスタンス取得
	CTexture* pTexture = CManager::GetTexture();

	// 各種変数の初期化
	m_pos = pos;	// 位置
	m_rot = rot;	// 向き

	// Xファイル読込
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
		MessageBox(NULL, "CModel::Init() > モデルを読み込めませんでした", "Error", MB_OK);

		// 結果を返す
		return E_FAIL;
	}

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

	// 結果を返す
	return S_OK;
}

//*************************************
// モデル
//*************************************
void CModel::Uninit(void)
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

	if (m_pParent != NULL)
	{// 親モデルの情報があれば
		m_pParent = NULL;	// 忘れる
	}

	// 自身の破棄
	delete this;
}

//*************************************
// モデル
//*************************************
void CModel::Draw(void)
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
// モデル
//*************************************
void CModel::DrawParentChild(D3DXCOLOR*pCol)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// テクスチャのインスタンス取得
	CTexture* pTexture = CManager::GetTexture();

	// 現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	D3DXMATRIX mtxParent;// 親マトリックス

	// 親マトリックスを掛け合わせる
	if (m_pParent != NULL)
	{// 親がいる
		mtxParent = m_pParent->GetMatrix();	// 親マトリックス取得
	}
	else
	{// 親がいない
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);	// 親マトリックス取得
	}

	// 親マトリックを掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// 色がある場合
		if (pCol != NULL)
		{
			// 色を変更
			D3DXMATERIAL pMatValue = pMat[nCntMat];
			pMatValue.MatD3D.Diffuse.r = pCol->r;
			pMatValue.MatD3D.Diffuse.g = pCol->g;
			pMatValue.MatD3D.Diffuse.b = pCol->b;
			pMatValue.MatD3D.Diffuse.a = pCol->a;

			// 設定
			pDevice->SetMaterial(&pMatValue.MatD3D);
		}
		// ない場合
		else
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		}

		// テクスチャの設定
		pDevice->SetTexture(0, pTexture->GetAddress(m_apIdxTexture[nCntMat]));

		// モデル(パーツの描画)
		m_pMesh->DrawSubset(nCntMat);
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//*************************************
// モデル
//*************************************
CModel* CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pXFileName)
{
	CModel* pModel = NULL;

	// メモリ確保
	pModel = new CModel;
	if (pModel != NULL)
	{
		// 初期化処理
		if (pModel->Init(pos, rot, pXFileName) == E_FAIL)
		{
			delete pModel;
			pModel = NULL;
		}
	}
	else
	{
		MessageBox(NULL, "CModel::Create() > if ( pObjectX != NULL) メモリを確保できませんでした", "Error", MB_OK);
	}

	return  pModel;
}

//*************************************
// モデルの透明度変更
//*************************************
void CModel::SetAlphaColor(float fAlphar)
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

//************************************************
// モデルがマウスに当たっているか調べる
//************************************************
bool CModel::CollisionMouse(float fRadius)
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