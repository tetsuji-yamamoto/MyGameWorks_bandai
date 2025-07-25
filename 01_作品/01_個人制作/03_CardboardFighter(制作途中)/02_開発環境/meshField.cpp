//*********************************************
// 
// メッシュフィールド
// Author Tetsuji Yamamoto
// 
//*********************************************
#include "meshField.h"
#include "myMath.h"
#include "texture.h"
#include "manager.h"

//*********************************************
// メッシュフィールドコンストラクタ
//*********************************************
CMeshField::CMeshField()
{
	m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	m_pIdxBuff = NULL;		// インデックスバッファへのポインタ
	m_startPos = D3DXVECTOR3_NULL;	// 始まりの位置
	m_nIdxTexture = -1;		// テクスチャへのインデックス
	m_nNumPolygon = 0;		// ポリゴン数
	m_nNumVtx = 0;			// 頂点数
	m_nNumIdx = 0;			// インデックス数
	m_nDivisionX = 0;		// Xの分割数
	m_nDivisionY = 0;		// Yの分割数
	m_fWidth = 0.0f;		// 幅
	m_fHeight = 0.0f;		// 高さ
}

//*********************************************
// メッシュフィールドデストラクタ
//*********************************************
CMeshField::~CMeshField()
{
}

//*********************************************
// メッシュフィールド初期化
//*********************************************
HRESULT CMeshField::Init(D3DXVECTOR3 startPos, int nDivisionX, int nDivisionY, float fWidth, float fHeight, const char* pTexturePass)
{

	// フィールド部分のポリゴン数
	m_nNumPolygon = CMyMath::SeekFieldNumPolygonAll(nDivisionX, nDivisionY);

	// フィールドの頂点数
	m_nNumVtx = CMyMath::SeekFieldNumVertexAll(nDivisionX, nDivisionY);

	// フィールドのインデックス数
	m_nNumIdx = CMyMath::SeekFieldNumIndexAll(m_nNumPolygon);

	// 分割数設定
	m_nDivisionX = nDivisionX;
	m_nDivisionY = nDivisionY;

	// 幅と高さ
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	// 始まりの位置
	m_startPos = startPos;

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
		MessageBox(NULL, "CMeshField::Init > 頂点バッファをクリエイトできませんでした", "Error", MB_OK);
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
		MessageBox(NULL, "CMeshField::Init > インデックスバッファをクリエイトできませんでした", "Error", MB_OK);
		return E_FAIL;
	}

	// テクスチャンのインデックス設定
	m_nIdxTexture = pTexture->Register(pTexturePass);


	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntVtx = 0;

	// Zの分割数回す
	for (int nCntY = 0; nCntY <= nDivisionY; nCntY++)
	{
		// Xの分割数回す
		for (int nCntX = 0; nCntX <= nDivisionX; nCntX++, nCntVtx++)
		{
			float fposX = (fWidth / (float)nDivisionX) * (float)nCntX;	// 位置のX座標
			float fposZ = (fHeight / (float)nDivisionY) * (float)nCntY;	// 位置のY座標
			float fTexX = (1.0f / (float)nDivisionX) * (float)nCntX;	// テクスチャ座標X
			float fTexY = 1.0f / (float)nDivisionY * (float)nCntY;		// テクスチャ座標Y

			// 頂点座標の設定
			pVtx[nCntVtx].pos.x = startPos.x + fposX;
			pVtx[nCntVtx].pos.y = startPos.y;
			pVtx[nCntVtx].pos.z = startPos.z + (-fposZ);

			// 各頂点の法線の設定,面に対して垂直
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[nCntVtx].tex.x = fTexX;
			pVtx[nCntVtx].tex.y = fTexY;
		}
	}

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	// インデック情報へのポインタ
	WORD* pIdx;

	// インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nIdxA = nDivisionX + 1;	// 左側インデックス
	int nIdxB = 0;				// 右側インデックス
	int nCntIdx = 0;			// インデックスカウンター

	// インデックスを求める
	for (int nCntA = 0; nCntA < nDivisionY; nCntA++)
	{// Zの分割数分回す
		for (int nCntB = 0; nCntB <= nDivisionX; nCntB++)
		{// Xの分割数分回す
			pIdx[nCntIdx] = nIdxA;
			pIdx[nCntIdx + 1] = nIdxB;
			nCntIdx += 2;
			nIdxA++;
			nIdxB++;
		}

		if (nCntA < nDivisionY - 1)
		{// 安全装置
			pIdx[nCntIdx] = nIdxB - 1;
			pIdx[nCntIdx + 1] = nIdxA;
			nCntIdx += 2;
		}
	}

	// インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	// 法線の再設定
	CMeshField::ResetNormal();

	return S_OK;
}

//*********************************************
// メッシュフィールド終了
//*********************************************
void CMeshField::Uninit(void)
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
		MessageBox(NULL, "  CMeshField::Uninit() > メモリがNULLではありません", "Error", MB_OK);
	}

	// 自分のオブジェクトを破棄
	Release();
}

//*********************************************
// メッシュフィールド更新
//*********************************************
void CMeshField::Update(void)
{

}

//*********************************************
// メッシュフィールド描画
//*********************************************
void CMeshField::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// テクスチャインスタンス取得
	CTexture* pTexture = CManager::GetTexture();

	// 計算用マトリックス
	D3DXMATRIX mtxWorld;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// テクスチャを設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_nNumVtx,
		0,
		m_nNumPolygon
	);
}

//**************************************
// メッシュフィールド生成
//**************************************
CMeshField* CMeshField::Create(D3DXVECTOR3 startPos, int nDivisionX, int nDivisionY, float fWidth, float fheight, const char* pTexturePass)
{
	CMeshField* pMF = NULL;						// メッシュフィールドポインター
	int nNumAll = CObject::GetObujectNumAll();	// オブジェクトの全体数取得

	// オブジェクトの最大数を超えていなければ生成する
	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	// メッシュフィールドの生成
	pMF = new CMeshField;
	if (pMF != NULL)
	{
		// 初期化処理
		pMF->Init(startPos, nDivisionX, nDivisionY, fWidth, fheight, pTexturePass);
	}
	else
	{
		MessageBox(NULL, " CMeshField::Create() > メモリを確保できませんでした", "Error", MB_OK);
	}

	return pMF;
}

//**************************************
// メッシュフィールド生成
//**************************************
bool CMeshField::Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pNor)
{
	// 当たったかどうかの有無
	bool bColision = false;

	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	// インデック情報へのポインタ
	WORD* pIdx;

	// 求める高さ
	float fHeight = pPos->y;									// 求める高さ
	int nCntPolygon = 0;									// ポリゴンカウンター
	int nCntIdx = 0;										// インデックスカウンタ
	float fWidthDiviX = m_fWidth / (float)m_nDivisionX;		// 分割した幅
	float fHeightDiviY = m_fHeight / (float)m_nDivisionY;	// 分割した高さ
	float fMovePosX = 0.0f - m_startPos.x;					// 原点方向に移動させるための移動量X
	float fMovePosY = 0.0f - m_startPos.z;					// 原点方向に移動させるための移動量Y

	// フィールドの範囲外であれば処理しない
	if (pPos->x < m_startPos.x ||
		pPos->x > m_startPos.x + m_fWidth ||
		pPos->z > m_startPos.z ||
		pPos->z < m_startPos.z - m_fHeight)
	{
		return bColision;
	}

	// 当たっている判定にする
	bColision = true;

	// 位置を分割した長さで位置を割り出す
	int nPosDiviX = (int)((pPos->x + fMovePosX) / fWidthDiviX);
	int nPosDiviY = (int)((pPos->z + fMovePosY) / -fHeightDiviY);

	// ポリゴンカウンターを行分進める
	nCntPolygon += (m_nDivisionX * 2) * nPosDiviY;

	// ポリゴンカウンターを縮退ポリゴン分進める
	nCntPolygon += 4 * nPosDiviY;

	// ポリゴンカウンターを列分進める
	nCntPolygon += 2 * nPosDiviX;

	// インデックスカウンターを現在地のポリゴンへ設定
	nCntIdx = nCntPolygon;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// ポリゴン二枚分分回す
	for (int nCntPoly = 0; nCntPoly < 2; nCntPoly++, nCntIdx++)
	{
		D3DXVECTOR3 posA, posB, posC;							// ポリゴンの頂点
		D3DXVECTOR3 vecLineA, vecLineB, vecLineC;				// ポリゴンの一辺のベクトル
		D3DXVECTOR3 vecLinePposA, vecLinePposB, vecLinePposC;	// pPosとのベクトル
		float fClossA, fClossB, fClossC;						// pPosベクトルと一辺ベクトルの外積のY成分

		posA = pVtx[pIdx[nCntIdx]].pos;
		posB = pVtx[pIdx[nCntIdx + 1]].pos;
		posC = pVtx[pIdx[nCntIdx + 2]].pos;

		// ポリゴンの一辺のベクトルを求める
		vecLineA = posB - posA;
		vecLineB = posC - posB;
		vecLineC = posA - posC;

		// posベクトルを求める
		vecLinePposA = *pPos - posA;
		vecLinePposB = *pPos - posB;
		vecLinePposC = *pPos - posC;

		// pPosベクトルと一辺ベクトルの外積を求める
		fClossA = (vecLineA.z * vecLinePposA.x) - (vecLineA.x * vecLinePposA.z);
		fClossB = (vecLineB.z * vecLinePposB.x) - (vecLineB.x * vecLinePposB.z);
		fClossC = (vecLineC.z * vecLinePposC.x) - (vecLineC.x * vecLinePposC.z);

		D3DXVECTOR3 nor;	// 計算した法線を保存する変数
		float fDot;			// 内積の結果を保存する変数

		// 法線とポリゴンの一頂点の内積
		fDot = ((nor.x * posA.x) +
			(nor.y * posA.y) +
			(nor.z * posA.z));

		// 外積がすべてプラスまたはマイナスであれば
		if (fClossA >= 0 &&
			fClossB >= 0 &&
			fClossC >= 0)
		{
			// 外積によって法線を求める
			D3DXVec3Cross(&nor, &vecLineA, &vecLineB);

			// 法線を正規化する
			D3DXVec3Normalize(&nor, &nor);

			// 法線とポリゴンの一頂点の内積
			float fDot = ((nor.x * posA.x) + (nor.y * posA.y) + (nor.z * posA.z));

			//プレイヤーがポリゴン上にいるときのy座標を求める
			fHeight = (-nor.x * pPos->x - nor.z * pPos->z + fDot) / nor.y;

			// 高さ設定
			pPos->y = fHeight;

			// 法線設定
			if (pNor != NULL)
			{
				*pNor = nor;
			}

			return bColision;
		}
		else if (fClossA <= 0 &&
			fClossB <= 0 &&
			fClossC <= 0)
		{
			// 外積によって法線を求める
			D3DXVec3Cross(&nor, &vecLineB, &vecLineA);

			// 法線を正規化する
			D3DXVec3Normalize(&nor, &nor);

			// 法線とポリゴンの一頂点の内積
			float fDot = ((nor.x * posA.x) + (nor.y * posA.y) + (nor.z * posA.z));

			//プレイヤーがポリゴン上にいるときのy座標を求める
			fHeight = (-nor.x * pPos->x - nor.z * pPos->z + fDot) / nor.y;

			// 高さ設定
			pPos->y = fHeight;

			// 法線設定
			if (pNor != NULL)
			{
				*pNor = nor;
			}

			return bColision;
		}
	}

	// インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return fHeight;
}

//**************************************
// 法線の再設定
//**************************************
void CMeshField::ResetNormal(void)
{
	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// すべての頂点分回す
	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		// 法線変数
		D3DXVECTOR3 aNor[6];
		D3DXVECTOR3 nor;

		// ポリゴン縁ベクトル変数
		D3DXVECTOR3 vecRight;
		D3DXVECTOR3 vecLeft;
		D3DXVECTOR3 vecUp;
		D3DXVECTOR3 vecDown;
		D3DXVECTOR3 vecRightDown;
		D3DXVECTOR3 vecLeftUp;

		// 頂点位置変数
		D3DXVECTOR3 posCenter;
		D3DXVECTOR3 posRight;
		D3DXVECTOR3 posLeft;
		D3DXVECTOR3 posUp;
		D3DXVECTOR3 posDown;
		D3DXVECTOR3 posRightDown;
		D3DXVECTOR3 posLeftDown;
		D3DXVECTOR3 posRightUp;
		D3DXVECTOR3 posLeftUp;

		// 頂点番号を求める
		int nRightNum = nCntVtx + 1;
		int nLeftNum = nCntVtx - 1;
		int nUpNum = nCntVtx - (m_nDivisionX + 1);
		int nDownNum = nCntVtx + m_nDivisionX + 1;
		int nRightDownNum = nCntVtx + m_nDivisionX + 2;
		int nLeftUpNum = nCntVtx - (m_nDivisionX + 2);

		// 左上である
		if (nCntVtx == 0)
		{
			// 真ん中、右、下、右下の頂点の位置を求める
			posCenter = pVtx[nCntVtx].pos;
			posRight = pVtx[nRightNum].pos;
			posDown = pVtx[nDownNum].pos;
			posRightDown = pVtx[nRightDownNum].pos;

			// ポリゴンの縁を求める
			vecRight = posRight - posCenter;
			vecRightDown = posRightDown - posCenter;
			vecDown = posDown - posCenter;

			// 外積で法線を計算、正規化
			D3DXVec3Cross(&aNor[0], &vecRight, &vecRightDown);
			D3DXVec3Cross(&aNor[1], &vecRightDown, &posDown);
			D3DXVec3Normalize(&aNor[0], &aNor[0]);
			D3DXVec3Normalize(&aNor[1], &aNor[1]);

			// それぞれの法線の平均値で法線を求める
			nor = aNor[0] + aNor[1];
			nor = nor / 2;

		}
		// 右上である
		else if (nCntVtx == m_nDivisionX)
		{
			// 真ん中、左、下、左下の頂点の位置を求める
			posCenter = pVtx[nCntVtx].pos;
			posLeft = pVtx[nLeftNum].pos;
			posDown = pVtx[nDownNum].pos;

			// ポリゴンの縁を求める
			vecLeft = posLeft - posCenter;
			vecDown = posDown - posCenter;

			// 外積で法線を計算、正規化
			D3DXVec3Cross(&nor, &vecDown, &vecLeft);
			D3DXVec3Normalize(&nor, &nor);
		}
		// 左下である
		else if (nCntVtx == (m_nDivisionX + 1) * m_nDivisionY)
		{
			// 真ん中、上、右の頂点の位置を求める
			posCenter = pVtx[nCntVtx].pos;
			posRight = pVtx[nRightNum].pos;
			posUp = pVtx[nUpNum].pos;

			// ポリゴンの縁を求める
			vecRight = posRight - posCenter;
			vecUp = posUp - posCenter;

			// 外積で法線を計算、正規化
			D3DXVec3Cross(&nor, &vecUp, &vecRight);
			D3DXVec3Normalize(&nor, &nor);
		}
		// 右下である
		else if (nCntVtx == m_nDivisionX + (m_nDivisionX + 1) * m_nDivisionY)
		{
			// 真ん中、上、左上、左の頂点の位置を求める
			posCenter = pVtx[nCntVtx].pos;
			posUp = pVtx[nUpNum].pos;
			posLeftUp = pVtx[nLeftUpNum].pos;
			posLeft = pVtx[nLeftNum].pos;

			// ポリゴンの縁を求める
			vecUp = posUp - posCenter;
			vecLeftUp = posLeftUp - posCenter;
			vecLeft = posLeft - posCenter;

			// 外積で法線を計算、正規化
			D3DXVec3Cross(&aNor[0], &vecUp, &vecLeftUp);
			D3DXVec3Cross(&aNor[1], &vecLeftUp, &vecLeft);
			D3DXVec3Normalize(&aNor[0], &nor);
			D3DXVec3Normalize(&aNor[1], &nor);

			// それぞれの法線の平均値で法線を求める
			nor = aNor[0] + aNor[1];
			nor = nor / 2;
		}
		// 上辺である
		else if (nCntVtx > 0 && nCntVtx < m_nDivisionX)
		{
			// 真ん中、左、下、右上、右の頂点の位置を求める
			posCenter = pVtx[nCntVtx].pos;
			posLeft = pVtx[nLeftNum].pos;
			posDown = pVtx[nDownNum].pos;
			posRightDown = pVtx[nRightDownNum].pos;
			posRight = pVtx[nRightNum].pos;

			// ポリゴンの縁を求める
			vecLeft = posLeft - posCenter;
			vecDown = posDown - posCenter;
			vecRightDown = posRightDown - posCenter;
			vecRight = posRight - posCenter;

			// 外積で法線を計算、正規化
			D3DXVec3Cross(&aNor[0], &vecDown, &vecLeft);
			D3DXVec3Cross(&aNor[1], &vecRightDown, &vecDown);
			D3DXVec3Cross(&aNor[2], &vecRight, &vecRightDown);
			D3DXVec3Normalize(&aNor[0], &aNor[0]);
			D3DXVec3Normalize(&aNor[1], &aNor[1]);
			D3DXVec3Normalize(&aNor[2], &aNor[2]);

			// それぞれの法線の平均値で法線を求める
			nor = aNor[0] + aNor[1] + aNor[2];
			nor = nor / 3;
		}
		// 下辺である
		else if (nCntVtx >= m_nNumVtx - m_nDivisionX && nCntVtx < m_nNumVtx)
		{
			// 真ん中、左、左上、上、右の頂点の位置を求める
			posCenter = pVtx[nCntVtx].pos;
			posLeft = pVtx[nLeftNum].pos;
			posLeftUp = pVtx[nLeftUpNum].pos;
			posUp = pVtx[nUpNum].pos;
			posRight = pVtx[nRightNum].pos;

			// ポリゴンの縁を求める
			vecLeft = posLeft - posCenter;
			vecLeftUp = posLeftUp - posCenter;
			vecUp = posUp - posCenter;
			vecRight = posRight - posCenter;

			// 外積で法線を計算、正規化
			D3DXVec3Cross(&aNor[0], &vecLeft, &vecLeftUp);
			D3DXVec3Cross(&aNor[1], &vecLeftUp, &vecUp);
			D3DXVec3Cross(&aNor[2], &vecUp, &vecRight);
			D3DXVec3Normalize(&aNor[0], &aNor[0]);
			D3DXVec3Normalize(&aNor[1], &aNor[1]);
			D3DXVec3Normalize(&aNor[2], &aNor[2]);

			// それぞれの法線の平均値で法線を求める
			nor = aNor[0] + aNor[1] + aNor[2];
			nor = nor / 3;
		}
		// 左辺である
		else if (nCntVtx % (m_nDivisionX + 1) == 0)
		{
			// 真ん中、上、右、右下、下の頂点の位置を求める
			posCenter = pVtx[nCntVtx].pos;
			posUp = pVtx[nUpNum].pos;
			posLeft = pVtx[nLeftNum].pos;
			posRight = pVtx[nRightNum].pos;
			posRightDown = pVtx[nRightDownNum].pos;
			posDown = pVtx[nDownNum].pos;

			// ポリゴンの縁を求める
			vecUp = posUp - posCenter;
			vecRight = posRight - posCenter;
			vecRightDown = posRightDown - posCenter;
			vecDown = posDown - posCenter;

			// 外積で法線を計算、正規化
			D3DXVec3Cross(&aNor[0], &vecUp, &vecRight);
			D3DXVec3Cross(&aNor[1], &vecRight, &vecRightDown);
			D3DXVec3Cross(&aNor[2], &vecRightDown, &vecDown);
			D3DXVec3Normalize(&aNor[0], &aNor[0]);
			D3DXVec3Normalize(&aNor[1], &aNor[1]);
			D3DXVec3Normalize(&aNor[2], &aNor[2]);

			// それぞれの法線の平均値で法線を求める
			nor = aNor[0] + aNor[1] + aNor[2];
			nor = nor / 3;
		}
		// 右辺である
		else if ((nCntVtx - m_nDivisionX) % (m_nDivisionX + 1) == 0)
		{
			// 真ん中、下、左、左上、上の頂点の位置を求める
			posCenter = pVtx[nCntVtx].pos;
			posDown = pVtx[nDownNum].pos;
			posLeft = pVtx[nLeftNum].pos;
			posLeftUp = pVtx[nLeftUpNum].pos;
			posUp = pVtx[nUpNum].pos;

			// ポリゴンの縁を求める
			vecDown = posDown - posCenter;
			vecLeft = posLeft - posCenter;
			vecLeftUp = posLeftUp - posCenter;
			vecUp = posUp - posCenter;

			// 外積で法線を計算、正規化
			D3DXVec3Cross(&aNor[0], &vecLeftUp, &vecUp);
			D3DXVec3Cross(&aNor[1], &vecLeft, &vecLeftUp);
			D3DXVec3Cross(&aNor[2], &vecDown, &vecLeft);
			D3DXVec3Normalize(&aNor[0], &aNor[0]);
			D3DXVec3Normalize(&aNor[1], &aNor[1]);
			D3DXVec3Normalize(&aNor[2], &aNor[2]);

			// それぞれの法線の平均値で法線を求める
			nor = aNor[0] + aNor[1] + aNor[2];
			nor = nor / 3;
		}
		// それ以外である
		else
		{
			// 真ん中、上、右、右下、下、左、左上の頂点の位置を求める
			posCenter = pVtx[nCntVtx].pos;
			posUp = pVtx[nUpNum].pos;
			posRight = pVtx[nRightNum].pos;
			posRightDown = pVtx[nRightDownNum].pos;
			posDown = pVtx[nDownNum].pos;
			posLeft = pVtx[nLeftNum].pos;
			posLeftUp = pVtx[nLeftUpNum].pos;

			// ポリゴンの縁を求める
			vecUp = posUp - posCenter;
			vecRight = posRight - posCenter;
			vecRightDown = posRightDown - posCenter;
			vecDown = posDown - posCenter;
			vecLeft = posLeft - posCenter;
			vecLeftUp = posLeftUp - posCenter;

			// 外積で法線を計算、正規化
			D3DXVec3Cross(&aNor[0], &vecLeftUp, &vecUp);
			D3DXVec3Cross(&aNor[1], &vecLeft, &vecLeftUp);
			D3DXVec3Cross(&aNor[2], &vecDown, &vecLeft);
			D3DXVec3Cross(&aNor[3], &vecRightDown, &vecDown);
			D3DXVec3Cross(&aNor[4], &vecRight, &vecRightDown);
			D3DXVec3Cross(&aNor[5], &vecUp, &vecRight);
			D3DXVec3Normalize(&aNor[0], &aNor[0]);
			D3DXVec3Normalize(&aNor[1], &aNor[1]);
			D3DXVec3Normalize(&aNor[2], &aNor[2]);
			D3DXVec3Normalize(&aNor[3], &aNor[3]);
			D3DXVec3Normalize(&aNor[4], &aNor[4]);
			D3DXVec3Normalize(&aNor[5], &aNor[5]);

			// それぞれの法線の平均値で法線を求める
			nor = aNor[0] + aNor[1] + aNor[2];
			nor = nor / 3;
		}

		pVtx[nCntVtx].nor = nor;
	}

	// インデックスバッファのアンロック
	m_pIdxBuff->Unlock();
}

//*****************************************************
// メッシュフィールド高さ編集
//*****************************************************
void CMeshField::EditHeight(D3DXVECTOR3 pos, float fHeight, float fRadius)
{
	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点を一時保存
	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 posVtx;
		posVtx = pVtx[nCntVtx].pos;

		D3DXVECTOR2 posXZ, posXZVtx;
		posXZ.x = pos.x;
		posXZ.y = pos.z;
		posXZVtx.x = posVtx.x;
		posXZVtx.y = posVtx.z;

		// 頂点が半径の範囲内にいる
		if (CMyMath::ColiisionCircleCircle2D(posXZ, fRadius, posXZVtx, 0.0f) == true)
		{
			pVtx[nCntVtx].pos.y = fHeight;
		}
	}

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	// 法線の再設定
	CMeshField::ResetNormal();
}

//*****************************************************
// メッシュフィールド色設定
//*****************************************************
void CMeshField::SetColor(D3DXCOLOR col)
{
	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 全頂点の色変更
	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		pVtx[nCntVtx].col = col;
	}

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//*****************************************************
// メッシュフィールド位置設定
//*****************************************************
void CMeshField::SetPosition(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	m_startPos = pos;
	m_fHeight = fHeight;
	m_fWidth = fWidth;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntVtx = 0;

	// Zの分割数回す
	for (int nCntY = 0; nCntY <= m_nDivisionY; nCntY++)
	{
		// Xの分割数回す
		for (int nCntX = 0; nCntX <= m_nDivisionX; nCntX++, nCntVtx++)
		{
			float fposX = (m_fWidth / (float)m_nDivisionX) * (float)nCntX;	// 位置のX座標
			float fposZ = (m_fHeight / (float)m_nDivisionY) * (float)nCntY;	// 位置のY座標

			// 頂点座標の設定
			pVtx[nCntVtx].pos.x = pos.x + fposX;
			pVtx[nCntVtx].pos.y = pos.y;
			pVtx[nCntVtx].pos.z = pos.z + (-fposZ);
		}
	}

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//*****************************************************
// メッシュフィールドの保存
//*****************************************************
void CMeshField::Save(const char* pFilePass)
{
	// 書き込み用としてファイルを開く
	FILE* pFile = fopen(pFilePass, "w");

	// ファイルが開けたら
	if (pFile != NULL)
	{
		// 頂点情報へのポインタ
		VERTEX_3D* pVtx = NULL;

		fprintf(pFile, "#*********************************************************\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "# メッシュフィールド情報\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "# テクスチャはお好みのファイルパスを記入してあげてください\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#*********************************************************\n");
		fprintf(pFile, "START_POS = %0.3f %0.3f %0.3f\n", m_startPos.x, m_startPos.y, m_startPos.z);
		fprintf(pFile, "WIDTH = %0.3f\n", m_fWidth);
		fprintf(pFile, "HEIGHT = %0.3f\n", m_fHeight);
		fprintf(pFile, "POLYGON_NUM = %d\n", m_nNumPolygon);
		fprintf(pFile, "VERTEX_NUM = %d\n", m_nNumVtx);
		fprintf(pFile, "INDEX_NUM = %d\n", m_nNumIdx);
		fprintf(pFile, "DIVISION_X = %d\n", m_nDivisionX);
		fprintf(pFile, "DIVISION_Y = %d\n", m_nDivisionY);
		fprintf(pFile, "TEXTURE_FILE = \n");
		fprintf(pFile, "\n");

		// 頂点バッファをロック
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		fprintf(pFile, "SET_VERTEXBUFF\n");
		// 頂点分回す
		for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 pos = pVtx[nCntVtx].pos;
			D3DXVECTOR3 nor = pVtx[nCntVtx].nor;
			D3DXVECTOR2 tex = pVtx[nCntVtx].tex;
			D3DXCOLOR col = pVtx[nCntVtx].col;

			fprintf(pFile, "SET_VTX\n");
			fprintf(pFile, "POS = %0.3f %0.3f %0.3f\n", pos.x, pos.y, pos.z);
			fprintf(pFile, "NOR = %0.3f %0.3f %0.3f\n", nor.x, nor.y, nor.z);
			fprintf(pFile, "COL = %0.3f %0.3f %0.3f %0.3f\n", col.r, col.g, col.b, col.a);
			fprintf(pFile, "TEX = %0.3f %0.3f\n", tex.x, tex.y);
			fprintf(pFile, "END_VTX\n");
			fprintf(pFile, "\n");
		}
		fprintf(pFile, "END_VERTEXBUFF\n");
		fprintf(pFile, "\n");

		// 頂点バッファをアンロック
		m_pVtxBuff->Unlock();

		fprintf(pFile, "END_FILE");

		// ファイルを閉じる
		fclose(pFile);
	}
}

//*****************************************************
// メッシュフィールドの保存
//*****************************************************
void CMeshField::Load(const char* pFilePass)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// 読み取り用としてファイルを開く
	FILE* pFile = fopen(pFilePass, "r");

	// ファイルが開けたら
	if (pFile != NULL)
	{
		// 頂点情報へのポインタ
		VERTEX_3D* pVtx = NULL;

		char aStr[1024] = {};		// 文字列
		bool bComment = false;		// コメントの有無
		int nIdxStr = 0;			// 文字列インデックス
		int nIdxFileName = 0;		// ファイル名インデックス
		char aData[4] = {};			// =読み取り用
		char aFileName[128] = {};	// ファイル名用変数
		int nIdxVtx = 0;			// 頂点インデックス
		bool bSetVerBuff = false;	// 頂点バッファの設定の有無

		while (1)
		{// ループ

			// 一文字読み取る
			char cData = fgetc(pFile);

			if (cData == '#')
			{// コメント文字を読んだらそのあとの文字は読み飛ばす
				bComment = true;				// コメント有の状態にする
				memset(aStr, 0, sizeof(aStr));	// 文字列を空にする
				nIdxStr = 0;					// 文字列インデックスリセット
				continue;						// whileから
			}
			else if (cData == '\n')
			{// 改行よんだら
				bComment = false;				// コメント無の状態にする
				memset(aStr, 0, sizeof(aStr));	// 文字列を空にする
				nIdxStr = 0;					// 文字列インデックスリセット
				continue;						// whileから
			}
			else if (cData == '\t')
			{// タブ文字よんだら
				continue;	// whileから
			}
			else if (cData == EOF)
			{// タブ文字よんだら
				break;	// whileから抜け出す
			}

			if (bComment == true)
			{// コメント機能がオン
				continue;	// whileから
			}

			aStr[nIdxStr] = cData;	// 一文字代入
			nIdxStr++;				// インデックスカウントアップ

			// スタート位置読込
			if (strcmp(aStr, "START_POSE") == 0)
			{
				// =を読み込む
				fscanf(pFile, "%s", &aData[0]);

				// 値読み取り
				fscanf(pFile, "%f", &m_startPos.x);
				fscanf(pFile, "%f", &m_startPos.y);
				fscanf(pFile, "%f", &m_startPos.z);

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			// 幅読み取り
			else if (strcmp(aStr, "WIDTH") == 0)
			{
				// =を読み込む
				fscanf(pFile, "%s", &aData[0]);

				// 値読み取り
				fscanf(pFile, "%f", &m_fWidth);

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			// 高さ読み取り
			else if (strcmp(aStr, "HEIGHT") == 0)
			{
				// =を読み込む
				fscanf(pFile, "%s", &aData[0]);

				// 値読み取り
				fscanf(pFile, "%f", &m_fHeight);

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			// ポリゴン数読込
			else if (strcmp(aStr, "POLYGON_NUM") == 0)
			{
				// =を読み込む
				fscanf(pFile, "%s", &aData[0]);

				// 値読み取り
				fscanf(pFile, "%d", &m_nNumPolygon);

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			// 頂点数読込
			else if (strcmp(aStr, "VERTEX_NUM") == 0)
			{
				// =を読み込む
				fscanf(pFile, "%s", &aData[0]);

				// 値読み取り
				fscanf(pFile, "%d", &m_nNumVtx);

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			// インデックス数の読込
			else if (strcmp(aStr, "INDEX_NUM") == 0)
			{
				// =を読み込む
				fscanf(pFile, "%s", &aData[0]);

				// 値読み取り
				fscanf(pFile, "%d", &m_nNumIdx);

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			// Xの分割数読込
			else if (strcmp(aStr, "DIVISION_X") == 0)
			{
				// =を読み込む
				fscanf(pFile, "%s", &aData[0]);

				// 値読み取り
				fscanf(pFile, "%d", &m_nDivisionX);

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			// Yの分割数
			else if (strcmp(aStr, "DIVISION_Y") == 0)
			{
				// =を読み込む
				fscanf(pFile, "%s", &aData[0]);

				// 値読み取り
				fscanf(pFile, "%d", &m_nDivisionY);

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			// テクスチャファイル名読込
			else if (strcmp(aStr, "TEXTURE_FILE") == 0)
			{
				// =を読み込む
				fscanf(pFile, "%s", &aData[0]);

				// 値読み取り
				fscanf(pFile, "%s", aFileName);

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			// テクスチャファイル名読込
			else if (strcmp(aStr, "SET_VERTEXBUFF") == 0)
			{
				// 初期化処理を行う
				Init(m_startPos, m_nDivisionX, m_nDivisionY, m_fWidth, m_fHeight, aFileName);

				if (m_pVtxBuff != NULL)
				{
					// 頂点バッファをセットしている状態にする
					bSetVerBuff = true;

					// 頂点バッファをロック
					m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
				}

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			// ファイル終了
			else if (strcmp(aStr, "END_FILE") == 0)
			{
				// =を読み込む
				fscanf(pFile, "%s", &aData[0]);

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}

			// 頂点読込可能であれば通す
			if (bSetVerBuff == true)
			{
				// 位置読込
				if (strcmp(aStr, "POS") == 0)
				{
					// =を読み込む
					fscanf(pFile, "%s", &aData[0]);

					// 値を読み込む
					fscanf(pFile, "%f", &pVtx[nIdxVtx].pos.x);
					fscanf(pFile, "%f", &pVtx[nIdxVtx].pos.y);
					fscanf(pFile, "%f", &pVtx[nIdxVtx].pos.z);

					// 文字列を空にする
					memset(aStr, 0, sizeof(aStr));

					// 文字列インデックスリセット
					nIdxStr = 0;
				}
				// 法線読込
				else if (strcmp(aStr, "NOR") == 0)
				{
					// =を読み込む
					fscanf(pFile, "%s", &aData[0]);

					// 値を読み込む
					fscanf(pFile, "%f", &pVtx[nIdxVtx].nor.x);
					fscanf(pFile, "%f", &pVtx[nIdxVtx].nor.y);
					fscanf(pFile, "%f", &pVtx[nIdxVtx].nor.z);

					// 文字列を空にする
					memset(aStr, 0, sizeof(aStr));

					// 文字列インデックスリセット
					nIdxStr = 0;
				}
				// 色読込
				else if (strcmp(aStr, "COL") == 0)
				{
					// =を読み込む
					fscanf(pFile, "%s", &aData[0]);

					// 値を読み込む
					fscanf(pFile, "%f", &pVtx[nIdxVtx].nor.x);
					fscanf(pFile, "%f", &pVtx[nIdxVtx].nor.y);
					fscanf(pFile, "%f", &pVtx[nIdxVtx].nor.z);

					// 文字列を空にする
					memset(aStr, 0, sizeof(aStr));

					// 文字列インデックスリセット
					nIdxStr = 0;
				}
				// テクスチャ座標読込
				else if (strcmp(aStr, "TEX") == 0)
				{
					// =を読み込む
					fscanf(pFile, "%s", &aData[0]);

					// 値を読み込む
					fscanf(pFile, "%f", &pVtx[nIdxVtx].tex.x);
					fscanf(pFile, "%f", &pVtx[nIdxVtx].tex.y);

					// 文字列を空にする
					memset(aStr, 0, sizeof(aStr));

					// 文字列インデックスリセット
					nIdxStr = 0;
				}
				// 頂点読込終了
				else if (strcmp(aStr, "END_VTX") == 0)
				{
					// インデックスを一つ進める
					nIdxVtx++;

					// 文字列を空にする
					memset(aStr, 0, sizeof(aStr));

					// 文字列インデックスリセット
					nIdxStr = 0;
				}
				// 頂点読込終了
				else if (strcmp(aStr, "END_VERTEXBUFF") == 0)
				{
					bSetVerBuff = false;

					// 頂点バッファをアンロック
					m_pVtxBuff->Unlock();

					// 文字列を空にする
					memset(aStr, 0, sizeof(aStr));

					// 文字列インデックスリセット
					nIdxStr = 0;
				}
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	// ファイルが開けなかった
	else
	{
		MessageBox(NULL, "CMeshField::Load() > ファイルが開けませんでした", "Error", MB_OK);
		return;
	}
}