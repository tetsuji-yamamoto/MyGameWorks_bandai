//**********************************************
// 
// オブジェクト処理
// Author Tetsuji Yamamoto
// 
//**********************************************
#include "object.h"
#include "debugproc.h"

// 静的メンバー変数宣言
CObject* CObject::m_aPTop[PRIORITY_MAX] = {};	// 先頭のアドレス
CObject* CObject::m_aPCur[PRIORITY_MAX] = {};	// 最後尾のアドレス

int CObject::m_nNumAll = 0;						// オブジェクトの総数

//**********************************************
// オブジェクトコンストラクタ
//**********************************************
CObject::CObject(int nPriority)
{
	// 自信をリストに追加
	
	// 前のオブジェクトを最後尾のアドレスに設定
	m_pPrev = m_aPCur[nPriority];

	// 前のオブジェクトの次のオブジェクトのポインタを自身に設定
	if (m_pPrev != NULL)
	{
		m_pPrev->m_pNext = this;
	}

	// 次のオブジェクトのポインタはNULL
	m_pNext = NULL;	

	// 先頭のアドレスが無ければ自信を先頭アドレスにする
	if (m_aPTop[nPriority] == NULL)
	{
		m_aPTop[nPriority] = this;
	}

	// 最後尾のオブジェクトを自分自身に設定
	m_aPCur[nPriority] = this;

	m_type = TYPE_NONE;			// タイプを設定
	m_nPriority = nPriority;	// 優先度
	m_nNumAll++;				// 総数をカウントアップ

	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	if (m_apObject[nPriority][nCnt] == NULL)
	//	{
	//		m_apObject[nPriority][nCnt] = this;	// 自分自身を代入
	//		m_nID = nCnt;						// 自分自身のIDを保存
	//		m_type = TYPE_NONE;					// タイプを設定
	//		m_nPriority = nPriority;			// 優先度
	//		m_nNumAll++;						// 総数をカウントアップ
	//		break;
	//	}
	//}
}

//**********************************************
// オブジェクトデストラクタ
//**********************************************
CObject::~CObject()
{
}

//**********************************************
// オブジェクト全破棄処理
//**********************************************
void CObject::ReleaseAll(void)
{
	// プライオリティの数分回す
	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		// 先頭のオブジェクト代入
		CObject* pObject = m_aPTop[nCntPri];

		// 次のオブジェクトがNULLになるまでループする
		while (pObject != NULL)
		{
			// 次のオブジェクトポインタを一時保存
			CObject* pObjectNext = pObject->m_pNext;

			// 修了処理
			pObject->Uninit();

			// 次のオブジェクトを代入
			pObject = pObjectNext;
		}

		// 先頭と最後尾のポインタをNULLにする
		m_aPTop[nCntPri] = NULL;
		m_aPCur[nCntPri] = NULL;
	}


	//for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	//{
	//	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//	{
	//		if (m_apObject[nCntPri][nCnt] != NULL)
	//		{
	//			m_apObject[nCntPri][nCnt]->Uninit();
	//		}
	//	}
	//}
	//
	//for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	//{
	//	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//	{
	//		if (m_apObject[nCntPri][nCnt] != NULL)
	//		{
	//			MessageBox(NULL, " CObject::ReleaseAll() > if (m_apObject[nCntPri][nCnt]) > m_apObject[nCntPri][nCnt]メモリがNULLではありません", "Error", MB_OK);
	//			return;
	//		}
	//	}
	//}
}

//**********************************************
// オブジェクト全更新処理
//**********************************************
void CObject::UpdateAll(void)
{
	// プライオリティの数分回す
	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		// 先頭のオブジェクト代入
		CObject* pObject = m_aPTop[nCntPri];
		
		// 次のオブジェクトがNULLになるまでループする
		while (pObject != NULL)
		{
			// 次のオブジェクトポインタを一時保存
			CObject* pObjectNext = pObject->m_pNext;

			// 更新処理
			pObject->Update();

			// 次のオブジェクトを代入
			pObject = pObjectNext;
		}
	}

	//for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	//{
	//	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//	{
	//		if (m_apObject[nCntPri][nCnt] != NULL)
	//		{
	//			m_apObject[nCntPri][nCnt]->Update();
	//		}
	//	}
	//}
}

//**********************************************
// オブジェクト全描画処理
//**********************************************
void CObject::DrawAll(void)
{
	// プライオリティの数分回す
	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		// 先頭のオブジェクト代入
		CObject* pObject = m_aPTop[nCntPri];

		// 次のオブジェクトがNULLになるまでループする
		while (pObject != NULL)
		{
			// 次のオブジェクトポインタを一時保存
			CObject* pObjectNext = pObject->m_pNext;

			// 描画処理
			pObject->Draw();

			// 次のオブジェクトを代入
			pObject = pObjectNext;
		}
	}

	//for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	//{
	//	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//	{
	//		if (m_apObject[nCntPri][nCnt] != NULL)
	//		{
	//			m_apObject[nCntPri][nCnt]->Draw();
	//		}
	//	}
	//}
}

//**********************************************
// オブジェクト破棄処理
//**********************************************
void CObject::Release(void)
{
	// 自信をリストから削除

	// 優先度を取得
	int nPriority = GetPriority();

	// リストをつなげる
	// 先頭がなくなる場合
	if (m_pPrev == NULL && m_pNext != NULL)
	{
		m_pNext->m_pPrev = NULL;
		m_aPTop[nPriority] = m_pNext;
	}
	// 最後尾がなくなる場合
	else if (m_pPrev != NULL && m_pNext == NULL)
	{
		m_pPrev->m_pNext = NULL;
		m_aPCur[nPriority] = m_pPrev;
	}
	// リストの途中の場合
	else if (m_pPrev != NULL && m_pNext != NULL)
	{
		m_pNext->m_pPrev = m_pPrev;
		m_pPrev->m_pNext = m_pNext;
	}

	// 総数カウントダウン
	m_nNumAll--;

	// 自分自信を破棄
	delete this;

	//int nIdx = this->m_nID;
	//int nPri = this->m_nPriority;
	//
	//if (m_apObject[nPri][nIdx] != NULL)
	//{
	//	delete m_apObject[nPri][nIdx];
	//	m_apObject[nPri][nIdx] = NULL;
	//	m_nNumAll--;
	//}
	//
	//if (m_apObject[nPri][nIdx] != NULL)
	//{
	//	MessageBox(NULL, " void CObject::Release(void) > if (m_apObject[nIdx] != NULL) > m_apObject[nIdx]メモリがNULLではありません", "Error", MB_OK);
	//}
}

//**********************************************
// オブジェクトデバッグ表示処理
//**********************************************
void CObject::DrawDebug(void)
{
	CDebugprocc::Print("[ s Object おぶじぇくと オブジェクト 物 ]\n");
	CDebugprocc::Print("m_nNumAll : %d\n",m_nNumAll);
	CDebugprocc::Print("\n");
}