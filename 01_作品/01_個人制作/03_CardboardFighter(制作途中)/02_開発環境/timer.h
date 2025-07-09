//**********************************************
// 
// �^�C�}�[
// Author Tetsuji Yamamoto
// 
//**********************************************
#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"
#include "object.h"
#include "object2D.h"
#include "number.h"

#define TIME_NOMAL (120)
#define MAX_TIME_DIGIT (3)

// �^�C�}�[�N���X
class CTimer : public CObject // CObject�p��
{
public:
	CTimer();
	~CTimer();

	HRESULT Init();
	HRESULT Init(D3DXVECTOR3 startPos, D3DXCOLOR col, float fWidth, float fHeight, int nDigits, int nTime = TIME_NOMAL);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTimer* Create(D3DXVECTOR3 startPos, D3DXCOLOR col, float fWidth, float fHeight, int nDigits,int nTime = TIME_NOMAL);
	static void AddTime(int nAddTime) { m_nTime += nAddTime; }
	static bool SecondsCnt(void);

	// �Z�b�^�[
	static void SetTime(int nSetTime) { m_nTime = nSetTime; }

	// �Q�b�^�[
	static int GetTime(void) { return m_nTime; }
private:
	CNumber* m_apNumber[MAX_TIME_DIGIT];	// �����I�u�W�F�N�g�̃|�C���^
	int m_nDigit;			// ����
	static int m_nTime;		// �^�C��
	static int m_nCntTime;	// �^�C�}�[�J�E���g
};

#endif // !_TIMER_H_
