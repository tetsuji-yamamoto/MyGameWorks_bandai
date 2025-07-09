//***********************************************
// 
// 丸影
// Author Tetsuji Yamamoto
// 
//***********************************************
#include "shadow.h"
#include "stage.h"
#include "texture.h"
#include "manager.h"
#include "meshField.h"
#include "myMath.h"

//***********************************************
// 丸影
//***********************************************
CShadow::CShadow() : CObject(CObject::PRIORITY_4)
{
	m_pVtxBuff = NULL;							// 頂点バッファへのポインタ
	memset(m_mtxWorld,0,sizeof(m_mtxWorld)) ;	// ワールドマトリックス
	memset(m_mtxTrans,0,sizeof(m_mtxTrans)) ;	// 拡大縮小行列
	memset(m_mtxRot,0,sizeof(m_mtxRot)) ;		// 回転行列
	m_pos = D3DXVECTOR3_NULL ;					// 位置
	m_rot = D3DXVECTOR3_NULL ;					// 向き
	m_fRadius = 0.0f;							// 半径
}

//***********************************************
// 丸影
//***********************************************
CShadow::~CShadow()
{
}

//***********************************************
// 丸影
//***********************************************
HRESULT CShadow::Init(float fRadius)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// テクスチャのインスタンス取得
	CTexture* pTexture = CManager::GetTexture();

	// 各種変数の設定
	m_fRadius = fRadius;
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&m_mtxTrans);
	D3DXMatrixIdentity(&m_mtxRot);
	 
	// 頂点バッファの生成
	HRESULT hr = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "CShadow::Init > 頂点バッファをクリエイトできませんでした", "Error", MB_OK);
		return E_FAIL;
	}

	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fAddY = 0.5f;

	pVtx[0].pos.x = -fRadius;
	pVtx[0].pos.y = fAddY;
	pVtx[0].pos.z = fRadius;

	pVtx[1].pos.x = fRadius;
	pVtx[1].pos.y = fAddY;
	pVtx[1].pos.z = fRadius;

	pVtx[2].pos.x = -fRadius;
	pVtx[2].pos.y = fAddY;
	pVtx[2].pos.z = -fRadius;

	pVtx[3].pos.x = fRadius;
	pVtx[3].pos.y = fAddY;
	pVtx[3].pos.z = -fRadius;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
	{
		pVtx[nCntVtx].col = D3DXCOLOR_FULL;
	}

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//***********************************************
// 丸影
//***********************************************
void CShadow::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if (m_pVtxBuff != NULL)
	{
		MessageBox(NULL, " CShadow::Uninit() > メモリがNULLではありません", "Error", MB_OK);
	}

	// オブジェクトの破棄
	Release();
}

//***********************************************
// 丸影
//***********************************************
void CShadow::Update(void)
{
	// メッシュフィールド取得
	CStage* pStage = CManager::GetStage();
	CMeshField* pMeshField = pStage->GetMeshField();

	// 計算用ベクトル
	D3DXVECTOR3 nor;

	// 行列を初期化する
	D3DXMatrixIdentity(&m_mtxRot);

	// メッシュとの判定をする
	if (pMeshField->Collision(&m_pos, &nor) == true)
	{
		D3DXVECTOR3 look;
		D3DXVECTOR3 X = {1.0f,0.0f,0.0f};
		D3DXVec3Cross(&look, &nor,&X);
		D3DXVec3Normalize(&look, &look);
		m_mtxRot = CMyMath::ConvertLocalCoordinatesToRotMtx(m_pos, m_pos + look,nor);
	}
}

//***********************************************
// 丸影
//***********************************************
void CShadow::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	D3DXMATRIX mtxTrans;

	// テクスチャインスタンス取得
	CTexture* pTexture = CManager::GetTexture();

	// ワールドマトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを追加
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	// 位置を追加
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// テクスチャを設定
	pDevice->SetTexture(0, pTexture->GetAddress(CTexture::TEXTURE_SHADOW));

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);

	// アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// 設定をを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//***********************************************
// 丸影生成
//***********************************************
CShadow* CShadow::Create(float fRadius)
{
	CShadow* pShadow = NULL;
	int nNumAll = GetObujectNumAll();

	// オブジェクトが最大数に達しタラ生成しない
	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	pShadow = new CShadow;
	if (pShadow != NULL)
	{
		// 初期化処理
		pShadow->Init(fRadius);
	}
	else
	{
		MessageBox(NULL, " CShadow::Create() > メモリを確保できませんでした", "Error", MB_OK);
	}

	return  pShadow;
}