//**********************************************
// 
// プレイヤー処理
// Author Tetsuji Yamamoto
// 
//**********************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "object3D.h"
#include "objectX.h"
#include "model.h"
#include "bullet.h"
#include "score.h"
#include "state.h"
#include "character.h"
#include "motion.h"
#include "collision.h"
#include <vector>

// プレイヤークラス
class CPlayer : public CObject
{
public:
#define PLAYER_MODEL_NUM (10)	// パーツ数

	// モーションタイプ
	typedef enum
	{
		MOTION_NONE = 0,
		MOTION_MOVE,
		MOTION_02,
		MOTION_03,
		MOTION_RANDING,
		MOTION_MAX
	}MOTION;

	CPlayer(int nPriority = PRIORITY_NOMAL);
	~CPlayer();

	HRESULT Init() { return S_OK; }
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nAppStateCnt = 60, const char* pFilePass = NULL);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nLife, float fMovement, float fFrictionValue, int nAppStateCnt = 60);
	void Hit(int nDamage, int nCntState);

	// ゲッター
	CCollisionCylinder* GetCollisionCylinder(void) { return m_pColiCyli; }
	std::vector<CCollisionSpher*> GetCollisionSpher(void) { return m_pColiSpher; }

	// セッター

private:
	CCharacter* m_pCharacter;		// キャラクター
	std::vector<CModel*> m_pModel;	// モデル(パーツ)へのポインタ
	CMotion* m_pMotion;				// モーション
	CMotion* m_pBlendMotion;		// モーションブレンド
	bool m_bMove;					// 移動の有無
	int m_nNumModel;				// モデル(パーツ)の総数

	std::vector<CCollisionSpher*> m_pColiSpher;		// 球の当たり判定(ダメージ用)
	CCollisionCylinder* m_pColiCyli;	// 円柱の当たり判定(体用)
};

#endif // !PLAYER_H_
