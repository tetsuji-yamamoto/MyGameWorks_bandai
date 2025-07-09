//**********************************************
// 
// �v���C���[����
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

// �v���C���[�N���X
class CPlayer : public CObject
{
public:
#define PLAYER_MODEL_NUM (10)	// �p�[�c��

	// ���[�V�����^�C�v
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

	// �Q�b�^�[
	CCollisionCylinder* GetCollisionCylinder(void) { return m_pColiCyli; }
	std::vector<CCollisionSpher*> GetCollisionSpher(void) { return m_pColiSpher; }

	// �Z�b�^�[

private:
	CCharacter* m_pCharacter;		// �L�����N�^�[
	std::vector<CModel*> m_pModel;	// ���f��(�p�[�c)�ւ̃|�C���^
	CMotion* m_pMotion;				// ���[�V����
	CMotion* m_pBlendMotion;		// ���[�V�����u�����h
	bool m_bMove;					// �ړ��̗L��
	int m_nNumModel;				// ���f��(�p�[�c)�̑���

	std::vector<CCollisionSpher*> m_pColiSpher;		// ���̓����蔻��(�_���[�W�p)
	CCollisionCylinder* m_pColiCyli;	// �~���̓����蔻��(�̗p)
};

#endif // !PLAYER_H_
