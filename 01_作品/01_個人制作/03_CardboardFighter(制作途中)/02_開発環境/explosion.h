//****************************************************************************
// 
// ����
// Author tetuji yamamoto
// 
//****************************************************************************
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "object2D.h"


// �����N���X
class CExplosion : public CObject2D	// CObject2D�p��
{
public:
	CExplosion(int nPriority = PRIORITY_NOMAL);
	~CExplosion();

	HRESULT Init(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, int nLimitTime, int nMaxTexPattern, int nPatternLine);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CExplosion* Create(D3DXVECTOR3 pos, D3DXCOLOR col,float fWidth,float fHeight,int nLimitTime, int nMaxTexPattern, int nPatternLine);

private:
	int m_nCntTime;							// ���Ԍv���J�E���^�[
	int m_nLimitTime;						// ���Ԍv���J�E���^�[
	int m_nMaxTexPattern;					// �e�N�X�`���̃p�^�[����
	int m_nNowPattern;						// �e�N�X�`���̍��̃p�^�[����
	int m_nPatternLine;						// �p�^�[����
	float m_fTexPatternWidth;				// �e�N�X�`���p�^�[����
	float m_fTexPatternHeight;				// �e�N�X�`���p�^�[������
};

#endif // !_EXPLOSION_H_
