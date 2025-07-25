//***********************************************
// 
// Ûe
// Author Tetsuji Yamamoto
// 
//***********************************************
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "object3D.h"

// eNX
class CShadow : public CObject	// CObjectp³
{
public:
	CShadow();
	~CShadow();

	HRESULT Init(void) { return S_OK; }
	HRESULT Init(float fRadius);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CShadow* Create(float fRadius);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ¸_obt@ÖÌ|C^
	D3DXMATRIX m_mtxWorld;				// [h}gbNX
	D3DXMATRIX m_mtxTrans;				// gåk¬sñ
	D3DXMATRIX m_mtxRot;				// ñ]sñ
	D3DXVECTOR3 m_pos;					// Êu
	D3DXVECTOR3 m_rot;					// ü«
	float m_fRadius;					// ¼a
};

#endif // !_SHADOW_H_
