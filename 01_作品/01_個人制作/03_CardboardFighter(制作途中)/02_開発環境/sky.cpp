//**************************************
// 
// 空
// Author Tetsuji Yamamoto
// 
//**************************************
#include "sky.h"
#include "texture.h"
#include "manager.h"
#include "myMath.h"

//**************************************
// 空コンストラクタ
//**************************************
CSky::CSky() : CObject(CObject::PRIORITY_0)
{
	m_pVtxBuff = NULL;							// 頂点バッファへのポインタ
	m_pIdxBuff = NULL;							// インデックスバッファへのポインタ
	ZeroMemory(m_mtxWorld, sizeof(m_mtxWorld));	// ワールドマトリックス
	m_pos = D3DXVECTOR3_NULL;					// 位置
	m_nIdxTexture = -1;							// テクスチャへのインデックス
	m_nNumPolygonMeshField = 0;					// メッシュのポリゴンの数
	m_nNumVtx = 0;								// 頂点数
	m_nNumVtxFan = 0;							// 扇状の頂点の数
	m_nNumVtxMeshField = 0;						//メッシュの頂点の数
	m_nNumIdx = 0;								// インデックス数
	m_nNumIdxFan = 0;							// ファンのインデック数
	m_nNumIdxMeshField = 0;						// メッシュフィールドのインデックス数
	m_nDivisionX = 0;							// 分割数X
	m_nDivisionY = 0;							// 分割数Y
}

//**************************************
// 空デストラクタ
//**************************************
CSky::~CSky()
{
}

//**************************************
// 空初期化
//**************************************
HRESULT CSky::Init(int nDivisionX, int nDivisionY, float fRadius)
{

	// 下限を超えないようする
	if (nDivisionX < 3)
	{
		nDivisionX = 1;
	}

	// 下限を超えないようする
	if (nDivisionY < 3)
	{
		nDivisionY = 1;
	}

	m_nDivisionX = nDivisionX;
	m_nDivisionY = nDivisionY;

	// フィールド部分のポリゴン数
	m_nNumPolygonMeshField = CMyMath::SeekFieldNumPolygonAll(nDivisionX, nDivisionY - 2);

	// フィールド部分のインデックス数
	m_nNumIdxMeshField = CMyMath::SeekFieldNumIndexAll(m_nNumPolygonMeshField);

	// ファンのインデックス数
	m_nNumIdxFan = CMyMath::SeekFanNumIndexAll(nDivisionX);

	// すべてのインデックス数
	m_nNumIdx = m_nNumIdxMeshField + (m_nNumIdxFan * 2);

	// 頂点数を求める
	m_nNumVtxMeshField = CMyMath::SeekFieldNumVertexAll(nDivisionX, nDivisionY - 2);
	m_nNumVtxFan = nDivisionX + 2;
	m_nNumVtx = m_nNumVtxMeshField + 2;


	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// テクスチャのインスタンス取得
	CTexture* pTexture = CManager::GetTexture();

	// 頂点を生成
	HRESULT hr = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nNumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "CSky::Init > 頂点バッファをクリエイトできませんでした", "Error", MB_OK);
		return E_FAIL;
	}

	// インデックスバッファの生成
	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&m_pIdxBuff,
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "CSky::Init > インデックスバッファをクリエイトできませんでした", "Error", MB_OK);
		return E_FAIL;
	}

	// テクスチャンのインデックス設定
	m_nIdxTexture = pTexture->Register("data\\texture\\sky001.jpg");

	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fAngleX = (D3DX_PI * 2.0f) / nDivisionX;
	float fAngleY = D3DX_PI / nDivisionY;
	int nIdxVtx = 1;

	pVtx[0].pos = D3DXVECTOR3(0.0f, fRadius, 0.0f);
	pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);


	for (int nCntY = 1; nCntY < nDivisionY; nCntY++)
	{
		float fRadiusXZ = sinf(fAngleY * nCntY) * fRadius;
		for (int nCntX = 0; nCntX <= nDivisionX; nCntX++, nIdxVtx++)
		{
			float fTexX = (1.0f / (float)nDivisionX) * (float)nCntX;	// テクスチャ座標X
			float fTexY = 1.0f / (float)nDivisionY * (float)nCntY;		// テクスチャ座標Y
			pVtx[nIdxVtx].pos.x = sinf(fAngleX * nCntX) * fRadiusXZ;
			pVtx[nIdxVtx].pos.y = cosf(fAngleY * nCntY) * fRadius;
			pVtx[nIdxVtx].pos.z = cosf(fAngleX * nCntX) * fRadiusXZ;
			pVtx[nIdxVtx].tex.x = fTexX;
			pVtx[nIdxVtx].tex.y = fTexY;
		}
	}

	// 一番下の点
	pVtx[m_nNumVtx - 1].pos = D3DXVECTOR3(0.0f, -fRadius, 0.0f);
	pVtx[m_nNumVtx - 1].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点の数分回す
	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		pVtx[nCntVtx].nor = D3DXVECTOR3_NULL;
		pVtx[nCntVtx].col = D3DXCOLOR_FULL;
	}

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	// インデック情報へのポインタ
	WORD* pIdx;

	int nIdxA = nDivisionX + 2;	// 左側インデックス
	int nIdxB = 1;				// 右側インデックス
	int nCntIdx = 1;			// 保存用インデックスのカウンター

	// インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// てっぺんファンインデックス
	pIdx[0] = 0;

	// ファンのインデックス数分回す
	for (int nCntIdxA = m_nNumIdxFan - 2; nCntIdxA > 0; nCntIdxA--, nCntIdx++)
	{
		pIdx[nCntIdx] = nCntIdxA;
	}

	pIdx[m_nNumIdxFan - 1] = 0;

	for (int nCntY = 1; nCntY < nDivisionY - 1; nCntY++)
	{// Zの分割数分回す
		for (int nCntX = 0; nCntX <= nDivisionX; nCntX++)
		{// Xの分割数分回す
			pIdx[nCntIdx] = nIdxA;
			pIdx[nCntIdx + 1] = nIdxB;
			nCntIdx += 2;
			nIdxA++;
			nIdxB++;
		}

		if (nCntY < nDivisionY - 1)
		{// 安全装置
			pIdx[nCntIdx] = nIdxB - 1;
			pIdx[nCntIdx + 1] = nIdxA;
			nCntIdx += 2;
		}
	}

	// 最後ファンインデックス
	nCntIdx--;
	pIdx[nCntIdx] = m_nNumVtx - 1;
	nCntIdx++;

	// ファンのインデックス数分回す
	for (int nCntIdxB = m_nNumVtxMeshField - m_nDivisionX; nCntIdxB < m_nNumVtx - 1; nCntIdxB++, nCntIdx++)
	{
		pIdx[nCntIdx] = nCntIdxB;
	}

	pIdx[nCntIdx] = m_nNumVtx - 1;

	// インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//**************************************
// 空終了
//**************************************
void CSky::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// 頂点インデックスの破棄
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// 破棄に失敗している
	if (m_pVtxBuff != NULL || m_pIdxBuff != NULL)
	{
		MessageBox(NULL, " CObject2D::Uninit() > メモリがNULLではありません", "Error", MB_OK);
	}

	// 自分のオブジェクトを破棄
	Release();
}

//**************************************
// 空更新
//**************************************
void CSky::Update(void)
{

}

//**************************************
// 空描画
//**************************************
void CSky::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// テクスチャインスタンス取得
	CTexture* pTexture = CManager::GetTexture();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// テクスチャを設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画(てっぺん)
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLEFAN,
		0,
		0,
		m_nNumVtxFan,
		0,
		m_nDivisionX
	);

	// ポリゴンの描画(中)
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_nNumVtxMeshField,
		m_nNumIdxFan - 1,
		m_nNumPolygonMeshField
	);

	// ポリゴンの描画(下)
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLEFAN,
		0,
		0,
		m_nNumVtxFan,
		m_nNumIdxFan + m_nNumIdxMeshField,
		m_nDivisionX
	);

	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//**************************************
// 空生成
//**************************************
CSky* CSky::Create(int nDivisionX, int nDivisionY, float fRadius)
{
	CSky* pSphere = NULL;			// 空ポインター
	int nNumAll = GetObujectNumAll();	// オブジェクトの全体数取得

	// 空の生成
	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	pSphere = new CSky;
	if (pSphere != NULL)
	{
		// 初期化処理
		pSphere->Init(nDivisionX, nDivisionY, fRadius);
	}
	else
	{
		MessageBox(NULL, " CSky::Create() > if (pPlayer != NULL) メモリを確保できませんでした", "Error", MB_OK);
	}

	return pSphere;
}