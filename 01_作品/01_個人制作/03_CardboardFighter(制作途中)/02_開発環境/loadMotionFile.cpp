//********************************************
// 
// ファイル読込
// Author Tetsuji Yamamoto
// 
//********************************************
#include "loadMotionFile.h"

//********************************************
// ファイル読込コンストラクタ
//********************************************
CLoadMotionFile::CLoadMotionFile()
{
	memset(m_aStr, NULL, sizeof(m_aStr));	// 文字列
	m_pFile = NULL;							// ファイルポインター
	m_type = CLoadMotionFile::TYPE_SCRIPT;	// 読み取りタイプ
	m_bComment = false;						// コメントの有無
	m_nIdxStr = 0;							// 文字列インデックス
	m_nIdxFileName = 0;						// ファイル名インデックス
	m_nResult = 0;							// 読み取り結果用
	m_nModelNum = 0;						// モデルの数
	m_nNumMotion = 0;						// モーション数
	m_nIdxMotionset = 0;					// モーションセットインデックス
	m_nIdxKey = 0;							// キーのインデックス
	m_nIdxKeySet = 0;						// キーセットのインデックス
}

//********************************************
// ファイル読込デストラクタ
//********************************************
CLoadMotionFile::~CLoadMotionFile()
{
}

//********************************************
// ファイル読込終了処理
//********************************************
void CLoadMotionFile::Uninit()
{
	// キャラクター情報破棄
	if (m_pLoadCharacterSet != NULL)
	{
		m_pLoadCharacterSet->Uninit();
		m_pLoadCharacterSet = NULL;
	}

	// パーツセット読込情報破棄
	for (auto& iter : m_pLoadPartsSet)
	{
		iter->Uninit();
	}
	m_pLoadPartsSet.clear();
	
	// ファイル名情報破棄
	for (auto& iter : m_pXFileName)
	{
		iter->Uninit();
	}
	m_pXFileName.clear();


	// モーションセットの破棄
	for (auto& iter : m_apLoadMotionSet)
	{	
		iter->Uninit();
	}
	m_apLoadMotionSet.clear();

	// 自分自身を破棄
	delete this;
}

//********************************************
// ファイル読込
//********************************************
void CLoadMotionFile::Load(const char* pFileName)
{
	// 情報を初期化する
	Reset();

	// 読み取り用としてファイルを開く
	m_pFile = fopen(pFileName, "r");

	// ファイルが開けたら
	if (m_pFile != NULL)
	{
		while (1)
		{// ループ

			// 一文字読み取る
			char cData = fgetc(m_pFile);

			if (cData == '#')
			{// コメント文字を読んだらそのあとの文字は読み飛ばす
				m_bComment = true;	// コメント有の状態にする
				ClearStr();			// 文字列を空にする
				m_nIdxStr = 0;
				continue;			// whileから
			}
			else if (cData == '\n')
			{// 改行よんだら
				m_bComment = false;	// コメント無の状態にする
				ClearStr();			// 文字列を空にする
				m_nIdxStr = 0;		// インデックスリセット
				continue;			// whileから
			}
			else if (cData == '\t')
			{// タブ文字よんだら
				continue;	// whileから
			}
			else if (cData == EOF)
			{// タブ文字よんだら
				break;	// whileから抜け出す
			}


			if (m_bComment == true)
			{// コメント機能がオン
				continue;	// whileから
			}

			m_aStr[m_nIdxStr] = cData;	// 一文字代入
			m_nIdxStr++;				// インデックスカウントアップ

			switch (m_type)
			{
				// スクリプト
			case TYPE_SCRIPT:
				if (strcmp(m_aStr, "NUM_MODEL") == 0)
				{// モデル数
					char aData[4] = {};

					// =を読み込む
					m_nResult = fscanf(m_pFile, "%s", &aData[0]);		
					
					// 数値を読み込む
					m_nResult = fscanf(m_pFile, "%d", &m_nModelNum);	

					// 文字列を空にする
					ClearStr();

					// 文字列インデックスをリセット
					m_nIdxStr = 0;

					// whileから
					continue;
				}
				else if (strcmp(m_aStr, "MODEL_FILENAME") == 0)
				{// xファイル名
					// = を読み取るための変数
					char aData[4] = {};

					// =を読み込む
					m_nResult = fscanf(m_pFile, "%s", aData);

					// ファイル名情報インスタンス生成、確保
					CFileName* pXFileName = new CFileName;

					// ファイル名を読み込む
					m_nResult = fscanf(m_pFile, "%s", pXFileName->GetFileName());

					// ファイル情報を末尾に追加	
					m_pXFileName.push_back(pXFileName);

					// ファイル名インデックスカウントアップ
					m_nIdxFileName++;

					// 文字列を空にする
					ClearStr();

					// 文字列インデックスをリセット
					m_nIdxStr = 0;

					// whileから
					continue;
				}
				else if (strcmp(m_aStr, "CHARACTERSET") == 0)
				{// キャラクター情報
					SetType(TYPE_CHARCTERSET);

					// キャラクターセットインスタンス生成、確保
					m_pLoadCharacterSet = new CCharacterSet;

					// 文字列を空にする
					ClearStr();	

					// 文字列インデックスをリセット
					m_nIdxStr = 0;
				}
				else if (strcmp(m_aStr, "MOTIONSET") == 0)
				{// モーションセット
					// メモリを確保
					CLoadMotionSet* pLoadMotionSet = new CLoadMotionSet;
					
					// 要素を追加
					m_apLoadMotionSet.push_back(pLoadMotionSet);

					// モーション数カウントアップ
					m_nNumMotion++;

					// モーションセットタイプに変更
					SetType(TYPE_MOTIONSET);

					// 文字列を空にする
					ClearStr();

					// 文字列インデックスをリセット
					m_nIdxStr = 0;
				}
				break;

					// キャラクターセット
			case TYPE_CHARCTERSET:
				if (m_pLoadCharacterSet != NULL)
				{// ヌルで無ければ
					// キャラクター情報読み取り
					m_pLoadCharacterSet->Load();
				}
				break;

				//	パーツセット
			case TYPE_PARTSSET:
				// NULLで無ければ
				if (m_pLoadPartsSet.size() > 0)
				{
					auto iter = m_pLoadPartsSet.end() - 1;
					(*iter)->Load();
				}
				break;

			case TYPE_MOTIONSET:
				// NULLで無ければ
				if (m_apLoadMotionSet.size() > 0)
				{
					auto iter = m_apLoadMotionSet.end() - 1;
					(*iter)->Load();
				}
				break;

			case TYPE_KEYSET:
				// 要素があれば
				if (m_apLoadMotionSet.capacity() > 0)
				{
					auto iterLoadMotinSet = m_apLoadMotionSet.end() - 1;
					auto iterLoadKeyset = (*iterLoadMotinSet)->GetLoadKeySetElementEnd();
					(*iterLoadKeyset)->Load();
				}
				break;

			case TYPE_KEY:
				// NULLで無ければ
				if (m_apLoadMotionSet.capacity() > 0)
				{
					auto iterLoadMotinSet = m_apLoadMotionSet.end() - 1;
					auto iterLoadKeyset = (*iterLoadMotinSet)->GetLoadKeySetElementEnd();
					auto iterLoadKey = (*iterLoadKeyset)->GetLoadKeyElementEnd();
					(*iterLoadKey)->Load();
				}
				break;
			}
		}

		// ファイルを閉じる
		fclose(m_pFile);
	}
	// ファイルが開けなかった
	else
	{
		MessageBox(NULL, "CLoadMotionFile::Load() > if (pFile != NULL) ファイルが開けませんでした", "Error", MB_OK);
		return;
	}
}

//*******************************************************
// ファイル読込読み込んだモデルの情報を渡す処理
//*******************************************************
void CLoadMotionFile::CopyModel(std::vector<CModel*>* ppVectorModel)
{
	// モデルカウンター
	int nCntModel = 0;

	// 読み取ったパーツセットの要素分回す
	for (auto iter = m_pLoadPartsSet.begin(); iter != m_pLoadPartsSet.end();iter++, nCntModel++)
	{
		// モデルのメモリ確保
		CModel* pModel = new CModel;

		// xファイル名の情報(イテレーター)を取得
		auto iterXFileName = m_pXFileName.begin() + nCntModel;

		// モデルの初期化
		D3DXVECTOR3 pos = (*iter)->GetPosition();
		D3DXVECTOR3 rot = (*iter)->GetRotation();
		char* pXFilename = (*iterXFileName)->GetFileName();
		pModel->Init(pos, rot, pXFilename);

		// 要素追加
		ppVectorModel->push_back(pModel);
	}

	// モデルカウントリセット
	nCntModel = 0;

	// 親モデルの設定
	for (auto iter = ppVectorModel->begin(); iter != ppVectorModel->end(); iter++, nCntModel++)
	{
		auto iterPartsSet = m_pLoadPartsSet.begin() + nCntModel;
		int nIdx = (*iterPartsSet)->GetIndexParrent();

		// 親がいるのであれば設定する
		if (nIdx >= 0)
		{
			(*iter)->SetParent(*(ppVectorModel->begin() + nIdx));
		}
	}
}

//*******************************************************
// ファイル読込読み込んだモーションの情報を渡す処理
//*******************************************************
void CLoadMotionFile::CopyMotion(CMotion** ppMotion)
{
	// キャラクター情報取得
	CCharacterSet* pCharacterSet = this->GetCharacterSet();

	// ヌルであればメモリを確保する
	if (*ppMotion == NULL)
	{
		*ppMotion = new CMotion;
	}

	// モーション数設定
	ppMotion[0]->SetNumMotion(m_nNumMotion);

	// 読み取ったモーションの数分設定する
	for (auto iterLoadtMotinSet = m_apLoadMotionSet.begin(); iterLoadtMotinSet != m_apLoadMotionSet.end();iterLoadtMotinSet++)
	{
		// モーションのインスタンス生成、確保
		CMotionInfo* pMyMotionInfo = new CMotionInfo;

		// モーションインフォの末尾に要素を追加
		ppMotion[0]->SetPushBackMotionInfo(&pMyMotionInfo);

		// ループの有無とキー数の取得
		bool bLoop = (*iterLoadtMotinSet)->GetLoop();
		int nNumkey = (*iterLoadtMotinSet)->GetNumKey();

		// ループの有無とキー数の設定
		pMyMotionInfo->SetLoop(bLoop);
		pMyMotionInfo->SetNumKey(nNumkey);

		// 読み取ったキーの数分回す
		for (auto iterLoadKeyset = (*iterLoadtMotinSet)->GetLoadKeySetBegin(); iterLoadKeyset != (*iterLoadtMotinSet)->GetLoadKeySetEnd(); iterLoadKeyset++)
		{
			// キーインフォのインスタンス生成
			CKeyInfo* pMyKeyInfo = new CKeyInfo;;

			// モーション情報の末尾にキーインフォの要素を追加
			pMyMotionInfo->SetPushBackKeyInfo(&pMyKeyInfo);

			// キーのフレーム数取得
			int nFlame = (*iterLoadKeyset)->GetFlame();

			// フレーム数設定
 			pMyKeyInfo->SetFrame(nFlame);

			// キー(モデル)の数分回す
			for (auto iterKeySet = (*iterLoadKeyset)->GetLoadKeyBegin(); iterKeySet != (*iterLoadKeyset)->GetLoadKeyEnd(); iterKeySet++)
			{
				// キーのインスタンス生成、確保
				CKey* pMyKey = new CKey;

				// キーインフォの末尾にキーの要素追加
				pMyKeyInfo->SetPushBackKey(&pMyKey);

				// 引き渡し用変数
				D3DXVECTOR3 pos, rot;

				// 読み取った位置と向きを取得
				pos = (*iterKeySet)->GetPosition();
				rot = (*iterKeySet)->GetRotation();

				// 自身のキーに読み取った位置と向きを設定
				pMyKey->SetPositionX(pos.x);
				pMyKey->SetPositionY(pos.y);
				pMyKey->SetPositionZ(pos.z);
				pMyKey->SetRotationX(rot.x);
				pMyKey->SetRotationY(rot.y);
				pMyKey->SetRotationZ(rot.z);
			}
		}
	}
}

//********************************************
// ファイル読込生成処理
//********************************************
CLoadMotionFile* CLoadMotionFile::Create(void)
{
	CLoadMotionFile* pLoadMotionFile = NULL;

	// オブジェクト2Dの生成
	if (pLoadMotionFile == NULL)
	{

		pLoadMotionFile = new CLoadMotionFile;
		if (pLoadMotionFile == NULL)
		{
			MessageBox(NULL, " CLoadMotionFile::Create() > if ( pBullet != NULL) メモリを確保できませんでした", "Error", MB_OK);
		}
	}

	return  pLoadMotionFile;
}
 
//********************************************
// ファイル読込情報を初期化する処理
//********************************************
void CLoadMotionFile::Reset(void)
{
	// パーツセット読込情報破棄
	for (auto& iter : m_pLoadPartsSet)
	{
		iter->Uninit();
	}
	m_pLoadPartsSet.clear();

	// ファイル名情報破棄
	for (auto& iter : m_pXFileName)
	{
		iter->Uninit();
	}
	m_pXFileName.clear();

	// キャラクター情報破棄
	m_pLoadCharacterSet->Uninit();

	// モーションセットの破棄
	for (auto& iter : m_apLoadMotionSet)
	{
		iter->Uninit();
	}
	m_apLoadMotionSet.clear();

	memset(m_aStr, NULL, sizeof(m_aStr));	// 文字列
	m_pFile = NULL;							// ファイルポインター
	m_type = CLoadMotionFile::TYPE_SCRIPT;	// 読み取りタイプ
	m_bComment = false;						// コメントの有無
	m_nIdxStr = 0;							// 文字列インデックス
	m_nIdxFileName = 0;						// ファイル名インデックス
	m_nResult = 0;							// 読み取り結果用
	m_nModelNum = 0;						// モデルの数
	m_nNumMotion = 0;						// モーション数
	m_nIdxMotionset = 0;					// モーションセットインデックス
	m_nIdxKey = 0;							// キーのインデックス
	m_nIdxKeySet = 0;						// キーセットのインデックス
}