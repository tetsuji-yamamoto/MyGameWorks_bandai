//*************************************
// 
// モーション
// Author Tetsuji Yamamoto
// 
//*************************************
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "model.h"
#include <vector>

// キークラス
class CKey
{
public:
	CKey();
	~CKey();

	void Uninit(void) { delete this; }

	// セッター
	void SetPositionX(float fPosX) { m_fPosX = fPosX; }
	void SetPositionY(float fPosY) { m_fPosY = fPosY; }
	void SetPositionZ(float fPosZ) { m_fPosZ = fPosZ; }
	void SetRotationX(float fRotX) { m_fRotX = fRotX; }
	void SetRotationY(float fRotY) { m_fRotY = fRotY; }
	void SetRotationZ(float fRotZ) { m_fRotZ = fRotZ; }

	// ゲッター
	float GetPositionX(void) {return m_fPosX; }
	float GetPositionY(void) {return m_fPosY; }
	float GetPositionZ(void) {return m_fPosZ; }
	float GetRotationX(void) {return m_fRotX; }
	float GetRotationY(void) {return m_fRotY; }
	float GetRotationZ(void) {return m_fRotZ; }

private:
	float m_fPosX;	// 位置X
	float m_fPosY;	// 位置Y
	float m_fPosZ;	// 位置Z
	float m_fRotX;	// 向きX
	float m_fRotY;	// 向きY
	float m_fRotZ;	// 向きZ
};

// キー情報クラス
class CKeyInfo
{
public:
#define KEY_NUM (16)	// キー数

	CKeyInfo();
	~CKeyInfo();

	void Uninit(void);
	CKey* CreateKey(int nNumKey);

	// セッター
	void SetFrame(int nFrame) { m_nFrame = nFrame; }
	void SetPushBackKey(CKey** ppKey) { m_pKey.push_back(*ppKey); }

	// ゲッター
	int GetFrame(void) { return m_nFrame; }
	auto GetKey(int nElementNum) { return m_pKey.begin() + nElementNum; }
	auto GetKeyBegin(void) { return m_pKey.begin(); }
	auto GetKeyEnd(void) { return m_pKey.end(); }
	auto GetKeyElementEnd(void) { return m_pKey.end() - 1; }

private:
	int m_nFrame;	// 再生フレーム
	std::vector<CKey*> m_pKey;	// 各パーツのキー要素
	int m_nNumkey;	// キーの数
};

// キーモーション情報クラス
class CMotionInfo
{
public:
#define KEYINFO_NUM (32)	// キー情報数

	CMotionInfo();
	~CMotionInfo();

	void Uninit(void);
	CKeyInfo* CreateKeyInfo(int nNumKeyInfo);

	// セッター
	void SetLoop(bool bLoop) { m_bLoop = bLoop; }
	void SetNumKey(int nNumKey) { m_nNumKey = nNumKey; }
	void SetPushBackKeyInfo(CKeyInfo** ppKeyInfo) { m_pKeyinfo.push_back(*ppKeyInfo); }

	// ゲッター
	bool GetLoop(void) { return m_bLoop; }
	int GetNumKey(void) { return m_nNumKey; }
	auto GetKeyInfo(int nElementNum) { return m_pKeyinfo.begin() + nElementNum; }
	auto GetKeyInfoBegin(void) { return m_pKeyinfo.begin(); }
	auto GetKeyInfoEnd(void) { return m_pKeyinfo.end(); }
	auto GetKeyInfoElementEnd(void) { return m_pKeyinfo.end() - 1; }

private:
	bool m_bLoop;			// ループするかどうか
	int m_nNumKey;			// キーの総数
	std::vector<CKeyInfo*> m_pKeyinfo;	// キー情報
	int m_nNumKeyInfo;		// キー情報の数
};

// モーションクラス
class CMotion
{
public:
#define MOTIONINFO_NUM (15)	// モーション情報数

	CMotion();
	~CMotion();

	void Init(int nNumMotion);
	void Uninit(void);
	void SetMotion(int nSetMotion);
	void SetMotionblend(CMotion* pBlendMotion,int nSetMotion, int nBlendTime);
	void UpdateMotionGetKey(D3DXVECTOR3* pOutPos, D3DXVECTOR3* pOutRot, int nMotion, int nKey);
	void UpdateMotionGetKeyBlend(D3DXVECTOR3* pOutPos, D3DXVECTOR3* pOutRot, int nMotion, int nKey);
	void UpdateMotionModel();
	void UpdateMotionModelBlend(CMotion* pBlendMotion);
	void CountUpMotionCounter(void) { m_nCounterMotion++; }

	// セッター
	void SetNumMotion(int nNumMotion) { m_nNumMotion = nNumMotion; }
	void SetKeySet(int nKey) { m_nKeySet = nKey; }
	void SetNextKeySet(int nNextKey) { m_nNextKeySet = nNextKey; }
	void SetCounterMotion(int nCounterMotion) { m_nCounterMotion = nCounterMotion; }
	void SetPushBackMotionInfo(CMotionInfo** ppMotionInfo) { m_pMotionInfo.push_back(*ppMotionInfo); }
	void SetModel(std::vector<CModel*>* ppModel);

	// ゲッター
	int GetNumMotion(void) {return m_nNumMotion; }
	int GetKeySet(void) { return m_nKeySet; }
	int GetNextKeySet(void) { return m_nNextKeySet; }
	int GetCounterMotion(void) { return m_nCounterMotion; }
	auto GetMotionInfo(int nElementNum) { return m_pMotionInfo.begin() + nElementNum; }
	bool GetIsEndMotion(void) { return m_bEndMotion; }

private:

	std::vector<CModel*> m_pModel;		// モデルへのポインタ
	std::vector < CMotionInfo*> m_pMotionInfo;	// モーション情報
	int m_nNumMotion;					// モーションの総数
	int m_nKeySet;						// 現在のキーセットNo.
	int m_nNextKeySet;					// 次のキー背セット
	int m_nCounterMotion;				// モーションカウンター
	int m_nTypeMotion;					// モーションタイプ
	int m_nNumModel;					// モデル数
	bool m_bEndMotion;					// モーションが終わったかどうか
	bool m_bBlend;						// モーションブレンドの有無
	int m_nBlendTime;					// ブレンド時間
	int m_nCntBlend;					// ブレンドカウンター
	int m_nTypeBlendMotion;				// ブレンドするモーションタイプ
};

#endif // !_MOTION_H_