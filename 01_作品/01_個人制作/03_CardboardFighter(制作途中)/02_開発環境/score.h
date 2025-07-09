//**********************************************
// 
// �X�R�A
// Author Tetsuji Yamamoto
// 
//**********************************************
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "object.h"
#include "object2D.h"
#include "number.h"
#include "word.h"

#define MAX_NUM_DIGIT (4)							// ����
#define SCORE_STRING "Score"						// ������

// �X�R�A�N���X
class CScore : public CObject // CObject�p��
{
public:
	CScore();
	~CScore();

	HRESULT Init();
	HRESULT Init(D3DXVECTOR3 startPos,D3DXCOLOR col, float fWidth, float fHeight, int nDigits, const char* pStr);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScore* Create(D3DXVECTOR3 startPos, D3DXCOLOR col, float fWidth, float fHeight, int nDigits,const char *pStr);
	static void AddScore(int nAddScore) { m_nScore += nAddScore; }

private:
	CNumber* m_apNumber[MAX_NUM_DIGIT];	// �����I�u�W�F�N�g�̃|�C���^
	CWord* m_pWord;						// �X�R�A�̕���
	static int m_nScore;				// �X�R�A
	int m_nDigit;						// ����
	int m_nLength;						// ������̒���
	int m_nNumWord;						// ������
};

#endif // !_SCORE_H_
