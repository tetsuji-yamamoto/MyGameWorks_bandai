//*************************************
// 
// モーション
// Author Tetsuji Yamamoto
// 
//*************************************
#include "motion.h"
#include "myMath.h"

//-------------------------------------
// キークラス

//*************************************
// キークラスコンストラクタ
//*************************************
CKey::CKey()
{
	m_fPosX = NULL;	// 位置X
	m_fPosY = NULL;	// 位置Y
	m_fPosZ = NULL;	// 位置Z
	m_fRotX = NULL;	// 向きX
	m_fRotY = NULL;	// 向きY
	m_fRotZ = NULL;	// 向きZ
}

//*************************************
// キークラスデストラクタ
//*************************************
CKey::~CKey()
{
}

//-------------------------------------
// キー情報クラス

//*************************************
// キー情報クラスコンストラクタ
//*************************************
CKeyInfo::CKeyInfo()
{
	m_nFrame = NULL;	// 再生フレーム
	m_nNumkey = 0;		// キー数
}

//*************************************
// キー情報クラスデストラクタ
//*************************************
CKeyInfo::~CKeyInfo() 
{
}

//*************************************
// キーモーション情報初期化
//*************************************
CKey* CKeyInfo::CreateKey(int nNumKey)
{
	//// キー数を保存
	//m_nNumkey = nNumKey;
	//
	//// キー情報分確保する
	//if (m_pKey)
	//{
	//	m_pKey = new CKey[nNumKey];
	//}
	//
	//return m_pKey;
	return NULL;

}

//*************************************
// キーモーション情報終了処理
//*************************************
void CKeyInfo::Uninit()
{
	// キーがあれば破棄する
	for (auto& iter : m_pKey)
	{
		iter->Uninit();
	}
	m_pKey.clear();

	// 自身の破棄
	delete this;
}

//-------------------------------------
// キーモーション情報

//*************************************
// キーモーション情報
//*************************************
CMotionInfo::CMotionInfo()
{
	m_bLoop = false;	// ループするかどうか
	m_nNumKey = NULL;	// キーの総数
	m_nNumKeyInfo = 0;	// キー情報の数
}

//*************************************
// キーモーション情報デストラクタ
//*************************************
CMotionInfo::~CMotionInfo()
{
}

//*************************************
// キーモーション情報終了
//*************************************
void CMotionInfo::Uninit()
{
	// キー情報があれば破棄する
	for (auto& iter : m_pKeyinfo)
	{
		iter->Uninit();
	}
	m_pKeyinfo.clear();

	// 自身の破棄
	delete this;
}

//*************************************
// キーモーション情報初期化
//*************************************
CKeyInfo* CMotionInfo::CreateKeyInfo(int nNumKeyInfo)
{
	// キー情報の数保存
	m_nNumKeyInfo = nNumKeyInfo;

	//// ヌルであればキー情報分確保する
	//if (m_pKeyinfo == NULL)
	//{
	//	m_pKeyinfo = new CKeyInfo[nNumKeyInfo];
	//}

	//return m_pKeyinfo;

	return NULL;
}

//-------------------------------------
// モーションクラス

//*************************************
// モーションクラスコンストラクタ
//*************************************
CMotion::CMotion()
{
	m_nNumMotion = 0;			// モーションの総数
	m_nKeySet = 0;				// 現在のキーセットNo.
	m_nNextKeySet = 0;			// 次のキーセット
	m_nCounterMotion = 0;		// モーションカウンター
	m_nNumModel = 0;			// モデルの数
	m_bEndMotion = false;		// モーションが終わったかどうか
	m_bBlend = false;			// ブレンドの有無
	m_nBlendTime = 1;			// ブレンド時間
	m_nTypeBlendMotion = 0;		// ブレンドするモーションタイプ
	m_nCntBlend = 0;			// モーションブレンドカウンター
}

//*************************************
// モーションクラスデストラクタ
//*************************************
CMotion::~CMotion()
{
}

//*************************************
// モーションクラス初期化
//*************************************
void CMotion::Init(int nNumMotion)
{
	
}

//*************************************
// モーションクラス終了
//*************************************
void CMotion::Uninit()
{
	// モーション情報があれば破棄する
	for (auto& iter : m_pMotionInfo)
	{
		iter->Uninit();
	}
	m_pMotionInfo.clear();

	// 自身の破棄
	delete this;
}

//*************************************
// モーションクラスセット
//*************************************
void CMotion::SetModel(std::vector<CModel*>* ppModel)
{
	m_pModel = *ppModel;
}

//*************************************
// モーションクラスセットモーション
//*************************************
void CMotion::SetMotion(int nSetMotion)
{
	// 今のモーションではなくマイナス域の数値では無かったら
	if (nSetMotion >= 0 && nSetMotion != m_nTypeMotion)
	{
		m_nTypeMotion = nSetMotion;	// モーションタイプ変更
		m_nCounterMotion = 0;		// モーションカウンターゼロ
		m_nKeySet = 0;				// 現在のキーセット数をリセット
	}
}

//*************************************
// モーションクラスセットモーションブレンド
//*************************************
void CMotion::SetMotionblend(CMotion* pBlendMotion,int nSetMotion,int nBlendTime)
{
	// モーションが無ければ設定しない
	if (nSetMotion < 0)
	{
		return;
	}

	auto iterMotionInfo = GetMotionInfo(m_nTypeMotion);			// モーション情報取得
	bool bLoop = (*iterMotionInfo)->GetLoop();					// ループ

	// 今のモーションではない又はモーションが終わっている状態であれば設定
	if (nSetMotion != m_nTypeMotion || m_bEndMotion == true)
	{
		// モーションブレンドのカウンターを設定
		pBlendMotion->SetCounterMotion(m_nCounterMotion);

		// モーションブレンドのキーセットを設定
		pBlendMotion->SetKeySet(m_nKeySet);

		m_nTypeBlendMotion = m_nTypeMotion;	// ブレンドするモーションタイプ
		m_nTypeMotion = nSetMotion;			// モーションタイプ変更
		m_nCounterMotion = 0;				// モーションカウンターゼロ
		m_nCntBlend = 0;					// ブレンドカウンターゼロ
		m_nKeySet = 0;						// 現在のキーセット数をリセット
		m_nBlendTime = nBlendTime;			// ブレンド時間
		m_bBlend = true;					// ブレンドする状態にする
		m_bEndMotion = false;				// モーションが終わっていいない状態にする

		// ブレンド時間は下限を超えないようにする
		if (m_nBlendTime <= 0)
		{
			m_nBlendTime = 1;
		}
	}
}

//*************************************
// モーションクラス更新
//*************************************
void CMotion::UpdateMotionGetKey(D3DXVECTOR3* pOutPos, D3DXVECTOR3* pOutRot, int nMotion,int nKey)
{
	auto iterMotionInfo = GetMotionInfo(nMotion);					// モーション情報取得
	auto iterKeyInfo = (*iterMotionInfo)->GetKeyInfo(m_nKeySet);	// キー情報取得
	bool bLoop = (*iterMotionInfo)->GetLoop();						// ループ
	int nNumKey = (*iterMotionInfo)->GetNumKey();					// キーの総数
	int nFrame = (*iterKeyInfo)->GetFrame();						// フレーム数
	m_nNextKeySet = m_nKeySet + 1;									// 次のキー
	float fMugFlame = (float)m_nCounterMotion / (float)nFrame;		// フレーム倍率を求める
	D3DXVECTOR3 posKey,rotKey;										// 今のキーの位置
	D3DXVECTOR3 posKeyNext,rotKeyNext;								// 次のキーの位置
	D3DXVECTOR3 posDiff, rotDiff;									// キーの差分

	// キーの限界を越したら
	if (m_nNextKeySet >= nNumKey)
	{
		// ゼロにする
		m_nNextKeySet = 0;

		// ループしない場合
		if (bLoop == false)
		{
			// 次のモーションは今と同じモーションにする
			m_nNextKeySet = m_nKeySet;
		}
	}

	// モーションカウンターがフレーム数を超えたら次のキーにする
	if (m_nCounterMotion > nFrame)
	{
		// ループしなくて、次のモーションが今のモーションと同じ場合
		if (bLoop == false && m_nNextKeySet == m_nKeySet)
		{
			// モーションカウンターを変えない
			m_nCounterMotion = nFrame;

			// モーションが終わった状態にする
			m_bEndMotion = true;
		}
		else
		{
			// モーションカウンターをリセット
			m_nCounterMotion = 0;

			// 次のモーションを設定
			m_nKeySet = m_nNextKeySet;
		}
	}

	// 今と先のキーを取得
	auto iterKeyInfoNow = (*iterMotionInfo)->GetKeyInfo(m_nKeySet);
	auto iterKeyInfoNext = (*iterMotionInfo)->GetKeyInfo(m_nNextKeySet);
	auto iterKeyNow = (*iterKeyInfoNow)->GetKey(nKey);
	auto iterKeyNext = (*iterKeyInfoNext)->GetKey(nKey);

	posKey.x = (*iterKeyNow)->GetPositionX();	// 今の位置X取得
	posKey.y = (*iterKeyNow)->GetPositionY();	// 今の位置Y取得
	posKey.z = (*iterKeyNow)->GetPositionZ();	// 今の位置Z取得
	rotKey.x = (*iterKeyNow)->GetRotationX();	// 今の向きX取得
	rotKey.y = (*iterKeyNow)->GetRotationY();	// 今の向きY取得
	rotKey.z = (*iterKeyNow)->GetRotationZ();	// 今の向きZ取得

	posKeyNext.x = (*iterKeyNext)->GetPositionX();	// 次の位置X取得
	posKeyNext.y = (*iterKeyNext)->GetPositionY();	// 次の位置Y取得
	posKeyNext.z = (*iterKeyNext)->GetPositionZ();	// 次の位置Z取得
	rotKeyNext.x = (*iterKeyNext)->GetRotationX();	// 次の向きX取得
	rotKeyNext.y = (*iterKeyNext)->GetRotationY();	// 次の向きY取得
	rotKeyNext.z = (*iterKeyNext)->GetRotationZ();	// 次の向きZ取得

	// モーションが終わっている場合は値をそのまま返す
	if (m_bEndMotion == true)
	{
		*pOutPos = posKey * fMugFlame;
		*pOutRot = rotKey * fMugFlame;
	}

	posDiff = posKeyNext - posKey;	// 位置の差分を求める
	rotDiff = rotKeyNext - rotKey;	// 向きの差分を求める

	// 最短の角度に直す
	rotDiff.x = CMyMath::ShortestAngle(rotDiff.x);
	rotDiff.y = CMyMath::ShortestAngle(rotDiff.y);
	rotDiff.z = CMyMath::ShortestAngle(rotDiff.z);

	*pOutPos = posKey + (posDiff * fMugFlame);	// 位置の差分にフレーム倍率を掛けそれを足し位置を求める
	*pOutRot = rotKey + (rotDiff * fMugFlame);	// 向きの差分にフレーム倍率を掛けそれを足し向きを求める
}

//*************************************
// モーションクラスブレンド更新
//*************************************
void CMotion::UpdateMotionGetKeyBlend(D3DXVECTOR3* pOutPos, D3DXVECTOR3* pOutRot, int nMotion, int nKey)
{
	auto iterMotionInfo = GetMotionInfo(nMotion);					// モーション情報取得
	auto iterKeyInfo = (*iterMotionInfo)->GetKeyInfo(m_nKeySet);	// キー情報取得
	bool bLoop = (*iterMotionInfo)->GetLoop();						// ループ
	int nFrame = (*iterKeyInfo)->GetFrame();						// フレーム数
	float fMugFlame = (float)m_nCounterMotion / (float)nFrame;		// フレーム倍率を求める
	D3DXVECTOR3 posKey, rotKey;										// 今のキーの位置
	D3DXVECTOR3 posKeyNext, rotKeyNext;								// 次のキーの位置
	D3DXVECTOR3 posDiff, rotDiff;									// キーの差分

	if (m_nKeySet == -1)
	{// キーが無ければ処理しない
		*pOutPos = D3DXVECTOR3_NULL;
		*pOutRot = D3DXVECTOR3_NULL;
		return;
	}

	// 今と先のキーを取得
	auto iterKeyInfoNow = (*iterMotionInfo)->GetKeyInfo(m_nKeySet);
	auto iterKeyInfoNext = (*iterMotionInfo)->GetKeyInfo(m_nNextKeySet);
	auto iterKeyNow = (*iterKeyInfoNow)->GetKey(nKey);
	auto iterKeyNext = (*iterKeyInfoNext)->GetKey(nKey);

	posKey.x = (*iterKeyNow)->GetPositionX();	// 今の位置X取得
	posKey.y = (*iterKeyNow)->GetPositionY();	// 今の位置Y取得
	posKey.z = (*iterKeyNow)->GetPositionZ();	// 今の位置Z取得
	rotKey.x = (*iterKeyNow)->GetRotationX();	// 今の向きX取得
	rotKey.y = (*iterKeyNow)->GetRotationY();	// 今の向きY取得
	rotKey.z = (*iterKeyNow)->GetRotationZ();	// 今の向きZ取得

	posKeyNext.x = (*iterKeyNext)->GetPositionX();	// 次の位置X取得
	posKeyNext.y = (*iterKeyNext)->GetPositionY();	// 次の位置Y取得
	posKeyNext.z = (*iterKeyNext)->GetPositionZ();	// 次の位置Z取得
	rotKeyNext.x = (*iterKeyNext)->GetRotationX();	// 次の向きX取得
	rotKeyNext.y = (*iterKeyNext)->GetRotationY();	// 次の向きY取得
	rotKeyNext.z = (*iterKeyNext)->GetRotationZ();	// 次の向きZ取得

	posDiff = posKeyNext - posKey;	// 位置の差分を求める
	rotDiff = rotKeyNext - rotKey;	// 向きの差分を求める

	*pOutPos = posKey + (posDiff * fMugFlame);	// 位置の差分にフレーム倍率を掛けそれを足し位置を求める
	*pOutRot = rotKey + (rotDiff * fMugFlame);	// 向きの差分にフレーム倍率を掛けそれを足し向きを求める
}

//*************************************
// モーションクラス更新
//*************************************
void CMotion::UpdateMotionModel()
{
	// モデルカウンター
	int nCntModel = 0;

	for (auto iter = m_pModel.begin(); iter != m_pModel.end(); iter++, nCntModel++)
	{
		// 計算用マトリックス
		D3DXMATRIX mtxWorld, mtxRot, mtxTrans;

		// モーション用ベクトル
		D3DXVECTOR3 outPos, outRot;

		// モデルの位置と向きを取得
		D3DXVECTOR3 pos = (*iter)->GetPosition();
		D3DXVECTOR3 rot = (*iter)->GetRotation();

		// モーションのアップデート
		CMotion::UpdateMotionGetKey(&outPos, &outRot, m_nTypeMotion, nCntModel);

		// 出力された値を追加
		pos += outPos;
		rot += outRot;

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// 向きを追加
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 位置を追加
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

		// マトリックスを設定
		(*iter)->SetMatrix(mtxWorld);
	}

	// モーションカウンターをカウントアップ
	m_nCounterMotion++;
}

//*************************************
// モーションクラス更新
//*************************************
void CMotion::UpdateMotionModelBlend(CMotion* pBlendMotion)
{
	// モデルカウンター
	int nCntModel = 0;

	for (auto iter = m_pModel.begin(); iter != m_pModel.end(); iter++, nCntModel++)
	{
		// 計算用マトリックス
		D3DXMATRIX mtxWorld, mtxRot, mtxTrans;

		// モーション用ベクトル
		D3DXVECTOR3 outPos, outRot;

		// ブレンドモーション用ベクトル
		D3DXVECTOR3 blendPos, blendRot;

		// モデルの位置と向きを取得
		D3DXVECTOR3 pos = (*iter)->GetPosition();
		D3DXVECTOR3 rot = (*iter)->GetRotation();

		// モーションのアップデート
		CMotion::UpdateMotionGetKey(&outPos, &outRot, m_nTypeMotion, nCntModel);
		pBlendMotion->UpdateMotionGetKey(&blendPos, &blendRot, m_nTypeBlendMotion, nCntModel);

		// モーションブレンドをする状態であれば
		if (m_bBlend == true)
		{
			// ブレンド時間の倍率を出す
			float fMugBlendTime = (float)m_nCntBlend / (float)m_nBlendTime;

			outPos *= fMugBlendTime;
			outRot *= fMugBlendTime;
			blendPos *= 1.0f - fMugBlendTime;
			blendRot *= 1.0f - fMugBlendTime;

			// 算出された値を追加
			pos += outPos + blendPos;
			rot += outRot + blendRot;
		}
		else
		{
			// 取得した値を追加
			pos += outPos;
			rot += outRot;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// 向きを追加
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 位置を追加
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

		// マトリックスを設定
		(*iter)->SetMatrix(mtxWorld);
	}

	// モーションカウンターをカウントアップ
	this->CountUpMotionCounter();

	// モーションカウンターをカウントアップ
	pBlendMotion->CountUpMotionCounter();

	// ブレンドモーションカウンタがブレンド時間より大きければ
	if (m_nCntBlend > m_nBlendTime)
	{
		// モーションブレンドをしない状態にする
		m_bBlend = false;
	}
	// ブレンドモーションカウンタがあれば
	else
	{
		// モーションブレンドカウントアップ
		m_nCntBlend++;
	}
}