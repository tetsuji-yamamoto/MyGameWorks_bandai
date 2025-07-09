//****************************************************************************
// 
// �w�i
// Author tetuji yamamoto
// 
//****************************************************************************
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "object2D.h"

// �w�i�N���X
class CBG : public CObject2D // CObject2D�p��
{
public:

	// �w�i�^�C�v
	typedef enum
	{
		TYPE_00 = 0,
		TYPE_01,
		TYPE_02,
		TYPE_MAX
	}TYPE;

	CBG(int nPriority = PRIORITY_NOMAL);
	~CBG();

	HRESULT Init(float fFeedRate, float fFeedAngle, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBG* Create(float fFeedRate, float fFeedAngle, TYPE type);

private:
	TYPE m_type;		// ���
	float m_fFeedAngle;	// ����p�x
	float m_fFeedRate;	// ���葬�x
	float m_fAddTexX;	// ���蕝
	float m_fAddTexY;	// ���荂��
};

#endif