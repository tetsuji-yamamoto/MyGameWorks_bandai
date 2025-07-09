//********************************************
// 
// モーションファイル読込
// Author Tetsuji Yamamoto
// 
//********************************************
#ifndef _LOADMOTIONFILE_H_
#define _LOADMOTIONFILE_H_

#include "main.h"
#include "loadCharacterse.h"
#include "FIleName.h"
#include "LoadMotionSet.h"
#include "model.h"
#include "motion.h"
#include <vector>

// 読込クラス
class CLoadMotionFile
{
public:
#define MAX_PARTS_NUM (32)
#define MAX_XFILE_NUM (32)

	// ファイル読み取りタイプ
	typedef enum
	{
		TYPE_SCRIPT = 0,
		TYPE_CHARCTERSET,
		TYPE_PARTSSET,
		TYPE_MOTIONSET,
		TYPE_KEYSET,
		TYPE_KEY,
		TYPE_MAX
	}TYPE;

	CLoadMotionFile();
	~CLoadMotionFile();

	void Uninit(void);
	void Load(const char* pFileName);
	void ClearStr(void) { memset(m_aStr, NULL, sizeof(m_aStr)); }
	void ResetIdxStr(void) { m_nIdxStr = 0; }
	static CLoadMotionFile* Create(void);
	void CopyMotion(CMotion** ppMotion);
	void CopyModel(std::vector<CModel*>* ppVectorModel);
	void Reset(void);

	// ゲッター
	FILE* GetFile(void) { return m_pFile; }
	CCharacterSet* GetCharacterSet(void) { return m_pLoadCharacterSet; }
	auto GetPartsSet(int nElementNum) { return m_pLoadPartsSet.begin() + nElementNum; }
	auto GetXFileName(int nElementNum) { return m_pXFileName.begin() + nElementNum; }
	CLoadMotionSet* GetLoadMotionSet(int nIdx) { return m_apLoadMotionSet[nIdx]; }
	char* GetStr(void) { return &m_aStr[0]; }
	bool GetIsComment(void) { return m_bComment; }
	int GetIdxStr(void) { return m_nIdxStr; }
	int GetIdxFIleName(void) { return m_nIdxFileName; }
	int GetResult(void) { return m_nResult; }
	int GetIdxLoadPartsSet(void) { return m_nIdxLoadPartsSet; }
	int GetIdxMotionset(void) { return m_nIdxMotionset; }
	int GetIdxKey(void) { return m_nIdxKey; }
	int GetModelNum(void) { return m_nModelNum; }
	int GetIdxKeySet(void) { return m_nIdxKeySet; }
	int GetNumMotion(void) { return m_nNumMotion; }

	// セッター
	void SetType(TYPE type) { m_type = type; }													// ファイル読み取りタイプ
	void SetPartsSet(CLoadPartsSet* pLoadPartsSet) { /*m_pLoadPartsSet = pLoadPartsSet;*/ }
	void SetIdxLoadPartsSet(int nIdxLoadPartsSet) { m_nIdxLoadPartsSet = nIdxLoadPartsSet; }
	void SetIdxMotionset(int nIdxMotionset) { m_nIdxMotionset = nIdxMotionset; }
	void SetIdxKey(int nIdxKey) { m_nIdxKey = nIdxKey; }
	void SetModelNum(int nMmodelNum) { m_nModelNum = nMmodelNum; }
	void SetIdxKeySet(int nIdxKeySet) { m_nIdxKeySet = nIdxKeySet; }
	void SetNumMotion(int nNumMotion) { m_nNumMotion = nNumMotion; }
	void SetPushBackLoadPartsSet(CLoadPartsSet** ppLoadPartsSet) { m_pLoadPartsSet.push_back(*ppLoadPartsSet); }

private:
	FILE* m_pFile;										// ファイルポインタ
	TYPE m_type;										// 読み取りタイプ
	CCharacterSet* m_pLoadCharacterSet;					// キャラクター情報ポインター
	std::vector< CFileName*> m_pXFileName;				// ファイル名
	std::vector<CLoadPartsSet*> m_pLoadPartsSet;		// パーツセットポインター
	std::vector<CLoadMotionSet*> m_apLoadMotionSet;		// モーションセットポインター
	char m_aStr[1024];									// 文字列
	bool m_bComment;									// コメントの有無
	int m_nIdxStr;										// 文字列インデックス
	int m_nIdxFileName;									// ファイル名インデックス
	int m_nIdxLoadPartsSet;								// パーツセットインデックス
	int m_nIdxMotionset;								// モーションセットインデックス
	int m_nIdxKeySet;									// キーセットのインデックス
	int m_nIdxKey;										// キーのインデックス
	int m_nResult;										// 読み取り結果用
	int m_nModelNum;									// モデルの数
	int m_nNumMotion;									// モーションの数
};

#endif // !_LOADFILE_H_
