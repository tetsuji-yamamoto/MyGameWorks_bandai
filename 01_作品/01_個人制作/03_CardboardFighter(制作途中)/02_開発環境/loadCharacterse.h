//********************************************
// 
// キャラクター情報読み取り
// Author Tetsuji Yamamoto
// 
//********************************************
#ifndef _CHARACTERSET_H_
#define _CHARACTERSET_H_

#include "main.h"

// キャラクター情報読み取りクラス
class CCharacterSet
{
public:
	CCharacterSet();
	~CCharacterSet();

	void Uninit(void);
	void Load(void);

	// ゲッター
	int GetNumParts(void) { return m_nNumParts; }
	float GetMovement(void) { return m_fMovement; }
	float GetJump(void) { return m_fJump; }
	float GetRadius(void) { return m_fRadius; }
	float GetHeight(void) { return m_fHeight; }
	int GetLife(void) { return m_nLife; }

	// セッター
	void GetNumParts(int nNumParts) { m_nNumParts = nNumParts; }

private:
	int m_nNumParts;	// パーツ数
	float m_fMovement;	// 移動量
	float m_fJump;		// ジャンプ力
	float m_fRadius;	// 半径
	float m_fHeight;	// 高さ
	int m_nLife;		// 体力
};

// パーツセット読み取りクラス
class CLoadPartsSet
{
public:
	CLoadPartsSet();
	~CLoadPartsSet();

	void Uninit(void);
	void Load(void);

	int GetIndexParrent(void) { return m_nIdxParent; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
private:
	int m_nIdxParent;		// 親モデルのインデックス番号
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_rot;		// 向き
};

#endif // !_CHARACTERSET_H_
