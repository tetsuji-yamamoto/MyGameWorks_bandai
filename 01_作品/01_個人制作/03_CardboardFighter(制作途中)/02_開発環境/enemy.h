//**********************************************
// 
// �G�l�~�[����
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

// �v���C���[�N���X
class CEnemy : public CObject
{
public:
#define PLAYER_MODEL_NUM (10)	// �p�[�c��

	// ���[�V�����^�C�v
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

	// �Q�b�^�[

	// �Z�b�^�[

private:
	std::vector<CModel*> m_pModel;	// ���f��(�p�[�c)�ւ̃|�C���^
	CCharacter* m_pCharacter;		// �L�����N�^�[
	CMotion* m_pMotion;				// ���[�V����
	CMotion* m_pBlendMotion;		// ���[�V�����u�����h
	CAttack* m_pAttack;				// �U�����
	bool m_bMove;					// �ړ��̗L��
	int m_nNumModel;				// ���f��(�p�[�c)�̑���

	std::vector<CCollisionSpher*> m_pColiSpherAttack;	// ���̓����蔻��(�U���p)
	CCollisionCylinder* m_pColiCyliAttckRange;	// ���̓����蔻��(�U�����f�p)
	CCollisionCylinder* m_pColiCyliBody;		// �~���̓����蔻��(��)
};

#endif // !ENEMY_H_
