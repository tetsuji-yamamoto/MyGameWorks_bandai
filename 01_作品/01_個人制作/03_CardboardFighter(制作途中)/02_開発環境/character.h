//*****************************************
// 
// �L�����N�^�[
// Author Tetsuji Yamamoto
// 
//*****************************************
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "main.h"
#include "object.h"
#include "state.h"
#include "shadow.h"

#define FRICTION_VALUE (0.2f)	// ���C�W��
#define GRAVITY_VALUE (2.0f)	// �d��

// �L�����N�^�[�N���X
class CCharacter
{
public:
	CCharacter();
	~CCharacter();

	HRESULT Init(void) { return S_OK; }
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fHeight, int nLife, float fMovement, int nAppStateCnt = 60);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCharacter* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fHeight,int nLife, float fMovement, int nAppStateCnt = 60);
	void UpdateRotaition(float fX);
	void SetDamageState(int nCntState);

	// �Q�b�^�[
	float GetMovement(void) { return m_fMovement; }
	float GetJump(void) { return m_fJump; }
	float GetRadius(void) { return m_fRadius; }
	float GetHeight(void) { return m_fHeight; }
	int GetLife(void) { return m_nLife; }
	CState GetState(void) { return *m_pState; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetRotationDest(void) { return m_rotDest; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }
	CCharacter GetCharacter(void) { return *this; }

	// �Z�b�^�[
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetState(CState state) { *m_pState = state; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetPositionOld(D3DXVECTOR3 posOld) { m_posOld = posOld; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetRotationDest(D3DXVECTOR3 rotDest) { m_rotDest = rotDest; }
	void SetRotationDestY(float rotY) { m_rotDest.y = rotY; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetMatrix(D3DXMATRIX mtx) { m_mtxWorld = mtx; }
	void SetCharcter(CCharacter character) { *this = character; }

private:
	float m_fMovement;	// �ړ���
	float m_fJump;		// �W�����v��
	float m_fRadius;	// ���a
	float m_fHeight;	// ����
	int m_nLife;		// �̗�

	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_posOld;	// �Â��ʒu
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3 m_rotDest;	// �ړI�̌���
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXMATRIX m_mtxWorld;	// �}�g���b�N�X
	CState* m_pState;		// ���

	CShadow* m_pShadow;	// �ۉe�|�C���^�[
};

#endif // !_CHARACTER_H_
