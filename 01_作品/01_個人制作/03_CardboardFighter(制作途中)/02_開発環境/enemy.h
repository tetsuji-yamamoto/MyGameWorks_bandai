//**********************************************
// 
// エネミー処理
// Author Tetsuji Yamamoto
// 
//**********************************************
#ifndef _ENEMY_H_
#define _ENEMY_H_

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
#include "attack.h"

// プレイヤークラス
class CEnemy : public CObject
{
public:
#define PLAYER_MODEL_NUM (10)	// パーツ数

	// モーションタイプ
	typedef enum
	{
		MOTION_NONE = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_03,
		MOTION_RANDING,
		MOTION_MAX
	}MOTION;

	CEnemy(int nPriority = PRIORITY_NOMAL);
	~CEnemy();

	HRESULT Init() { return S_OK; }
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nAppStateCnt = 60, const char* pFilePass = NULL);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nLife, float fMovement, float fFrictionValue, int nAppStateCnt = 60);
	void Hit(int nDamage);
	void CollisionCylinderCylinder(D3DXVECTOR3* pPosPartner, float fHeightPartner, float fRadiusPartner);
	bool IsAttackPlayer(void);
	bool IsCollisionAttackPlayer(void);

	// ゲッター

	// セッター

private:
	std::vector<CModel*> m_pModel;	// モデル(パーツ)へのポインタ
	CCharacter* m_pCharacter;		// キャラクター
	CMotion* m_pMotion;				// モーション
	CMotion* m_pBlendMotion;		// モーションブレンド
	CAttack* m_pAttack;				// 攻撃情報
	bool m_bMove;					// 移動の有無
	int m_nNumModel;				// モデル(パーツ)の総数

	std::vector<CCollisionSpher*> m_pColiSpherAttack;	// 球の当たり判定(攻撃用)
	CCollisionCylinder* m_pColiCyliAttckRange;	// 球の当たり判定(攻撃判断用)
	CCollisionCylinder* m_pColiCyliBody;		// 円柱の当たり判定(体)
};

#endif // !ENEMY_H_
