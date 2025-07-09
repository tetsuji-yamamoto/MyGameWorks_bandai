//*****************************************
// 
// キャラクター
// Author Tetsuji Yamamoto
// 
//*****************************************
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "main.h"
#include "object.h"
#include "state.h"
#include "shadow.h"

#define FRICTION_VALUE (0.2f)	// 摩擦係数
#define GRAVITY_VALUE (2.0f)	// 重力

// キャラクタークラス
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

	// ゲッター
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

	// セッター
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
	float m_fMovement;	// 移動量
	float m_fJump;		// ジャンプ力
	float m_fRadius;	// 半径
	float m_fHeight;	// 高さ
	int m_nLife;		// 体力

	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_posOld;	// 古い位置
	D3DXVECTOR3 m_rot;		// 向き
	D3DXVECTOR3 m_rotDest;	// 目的の向き
	D3DXVECTOR3 m_move;		// 移動量
	D3DXMATRIX m_mtxWorld;	// マトリックス
	CState* m_pState;		// 状態

	CShadow* m_pShadow;	// 丸影ポインター
};

#endif // !_CHARACTER_H_
