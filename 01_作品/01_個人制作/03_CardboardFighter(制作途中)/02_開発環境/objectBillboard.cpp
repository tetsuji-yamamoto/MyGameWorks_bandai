//*************************************
//
// オブジェクトビルボードビルボード
// Author Tetsuji Yamamoto
//
//*************************************
#include "objectBillboard.h"
#include "manager.h"
#include "camera.h"

//*************************************
// オブジェクトビルボードコンストラクタ
//*************************************
CObjectBillboard::CObjectBillboard()
{
	m_pVtxBuff = NULL;
	ZeroMemory(m_mtxWorld, sizeof(m_mtxWorld));
	m_nIdxTexture = -1;
}

//*************************************
// オブジェクトビルボードデストラクタ
//*************************************
CObjectBillboard::~CObjectBillboard()
{

}

//*************************************
// オブジェクトビルボード初期化処理
//*************************************
HRESULT CObjectBillboard::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// テクスチャのインスタンス取得
	CTexture* pTexture = CManager::GetTexture();

	HRESULT hr = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "CObjectBillboard::Init > 頂点バッファをクリエイトできませんでした", "Error", MB_OK);
		return E_FAIL;
	}

	// テクスチャンのインデックス設定
	m_nIdxTexture = pTexture->Register("data\\texture\\IMG_4953.JPG");

	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = -50.0f;
	pVtx[0].pos.y = 50.0f;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = 50.0f;
	pVtx[1].pos.y = 50.0f;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -50.0f;
	pVtx[2].pos.y = -50.0f;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = 50.0f;
	pVtx[3].pos.y = -50.0f;
	pVtx[3].pos.z = 0.0f;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
	{
		pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*************************************
// オブジェクトビルボード終了処理
//*************************************
void CObjectBillboard::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if (m_pVtxBuff != NULL)
	{
		MessageBox(NULL, " CObject2D::Uninit() > if (m_pVtxBuff != NULL) メモリがNULLではありません", "Error", MB_OK);
	}

	Release();
}

//*************************************
// オブジェクトビルボード更新処理
//*************************************
void CObjectBillboard::Update(void)
{

}

//*************************************
// オブジェクトビルボード描画処理
//*************************************
void CObjectBillboard::Draw(void)
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

	// ビューマトリックス取得
	D3DXMATRIX mtxview;
	pDevice->GetTransform(D3DTS_VIEW, &mtxview);

	// カメラの逆行列を設定
	m_mtxWorld._11 = mtxview._11;
	m_mtxWorld._12 = mtxview._21;
	m_mtxWorld._13 = mtxview._31;
	m_mtxWorld._21 = mtxview._12;
	m_mtxWorld._22 = mtxview._22;
	m_mtxWorld._23 = mtxview._32;
	m_mtxWorld._31 = mtxview._13;
	m_mtxWorld._32 = mtxview._23;
	m_mtxWorld._33 = mtxview._33;

	m_mtxWorld._42 = 100.0f;

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// テクスチャを設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//*************************************
// オブジェクトビルボード生成処理
//*************************************
CObjectBillboard* CObjectBillboard::Create(void)
{
	CObjectBillboard* pObjectBill = NULL;
	int nNumAll = GetObujectNumAll();

	// オブジェクトビルボード2Dの生成
	if (pObjectBill == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pObjectBill = new CObjectBillboard;
		if (pObjectBill != NULL)
		{
			// 初期化処理
			pObjectBill->Init();
		}
		else
		{
			MessageBox(NULL, " CObjectBillboard::Create() > if ( pObjectBill != NULL) メモリを確保できませんでした", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CObjectBillboard::Create() > if ( pObjectBill == NULL) メモリを確保できませんでした", "Error", MB_OK);
	}

	return  pObjectBill;
}