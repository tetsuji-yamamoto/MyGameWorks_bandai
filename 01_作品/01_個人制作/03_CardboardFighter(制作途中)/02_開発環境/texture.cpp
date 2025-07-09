//******************************************
// 
// テクスチャ
// Author Tetsuji Yamamoto
// 
//******************************************
#include "texture.h"
#include "renderer.h"
#include "debugproc.h"

// 静的メンバー変数宣言
int CTexture::m_nNumAll = 0;

//******************************************
// テクスチャ
//******************************************
CTexture::CTexture()
{
	memset(m_apTexture, NULL, sizeof(m_apTexture));
}

//******************************************
// テクスチャ
//******************************************
CTexture::~CTexture()
{

}

//******************************************
// テクスチャ
//******************************************
HRESULT CTexture::Load(void)
{
	// どこでも使うすべてのテクスチャの読込
	for (int nCnTex = 0; nCnTex < TEXTURE_MAX; nCnTex++)
	{
		// デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
		HRESULT hr = D3DXCreateTextureFromFile(pDevice,
			m_apFileName[nCnTex],
			&m_apTexture[nCnTex]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "CTexture::Load() > テクスチャを読み込めませんでした", "Error", MB_OK);
			return E_FAIL;
		}

		m_nNumAll++;	// テクスチャの総数カウントアップ
	}

	return S_OK;
}

//******************************************
// テクスチャ
//******************************************
void CTexture::Unload(void)
{
	// すべてのテクスチャを破棄
	for (int nCnTex = 0; nCnTex < MAX_TEXTURE_NUM; nCnTex++)
	{
		if (m_apTexture[nCnTex] != NULL)
		{
			m_apTexture[nCnTex]->Release();
			m_apTexture[nCnTex] = NULL;
		}

		if (m_apFileName[nCnTex] != NULL)
		{
			m_apFileName[nCnTex] = NULL;
		}

		if (m_apTexture[nCnTex] != NULL)
		{
			MessageBox(NULL, "CTexture::Unload() > テクスチャがNULLではありません", "Error", MB_OK);
		}
	}

	delete this;
}

//******************************************
// テクスチャ
//******************************************
int CTexture::Register(const char* pFileName)
{
	if (pFileName == NULL)
	{
		return -1;
	}

	// すでにあるかどうかを調べる
	for (int nCntTex = 0; nCntTex < m_nNumAll; nCntTex++)
	{
		if (strcmp(pFileName, m_apFileName[nCntTex]) == 0)
		{// もうすでにテクスチャがある場合
			// このテクスチャのインデックスを返す
			return nCntTex;
		}
	}

	// 無かったら新しく設定する
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	int nIdx = m_nNumAll;
	m_apFileName[nIdx] = pFileName;

	// テクスチャを読み込む
	HRESULT hr = D3DXCreateTextureFromFile(pDevice,
		m_apFileName[nIdx],
		&m_apTexture[nIdx]);

	// 読込失敗
	if (FAILED(hr))
	{
		MessageBox(NULL, "CTexture::Register() > テクスチャを読み込めませんでした", "Error", MB_OK);
		return E_FAIL;
	}

	// テクスチャの総数カウントアップ
	m_nNumAll++;	

	// 設定したインデックスを返す
	return nIdx;
}

//******************************************
// テクスチャ
//******************************************
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if (nIdx < 0 || nIdx >= MAX_TEXTURE_NUM)
	{
		return NULL;
	}

	return m_apTexture[nIdx];
}

//******************************************
// テクスチャ
//******************************************
CTexture* CTexture::Create()
{
	CTexture* pTexture = NULL;

	// オブジェクト2Dの生成
	if (pTexture == NULL)
	{
		pTexture = new CTexture;
		if (pTexture == NULL)
		{
#ifdef _DEBUG
			MessageBox(NULL, " CBullet* CBullet::Create() > if ( pBullet != NULL) メモリを確保できませんでした", "Error", MB_OK);
#endif
		}
	}

	// 結果を返す
	return  pTexture;
}

//******************************************
// テクスチャ
//******************************************
void CTexture::DebugTexture()
{
	CDebugprocc::Print("[ CTexture ]\n");
	CDebugprocc::Print("TEXTURE_ADD_NUM : %d\n",TEXTURE_ADD_NUM);
	CDebugprocc::Print("TEXTURE_MAX : %d\n",TEXTURE_MAX);
	CDebugprocc::Print("MAX_TEXTURE_NUM : %d\n",MAX_TEXTURE_NUM);
	CDebugprocc::Print("m_nNumAll : %d\n",m_nNumAll);
	CDebugprocc::Print("\n");
}