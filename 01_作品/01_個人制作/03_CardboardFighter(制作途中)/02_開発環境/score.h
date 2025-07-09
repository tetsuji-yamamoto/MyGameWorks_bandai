//**********************************************
// 
// スコア
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

#define MAX_NUM_DIGIT (4)							// 桁数
#define SCORE_STRING "Score"						// 文字列

// スコアクラス
class CScore : public CObject // CObject継承
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
	CNumber* m_apNumber[MAX_NUM_DIGIT];	// 数字オブジェクトのポインタ
	CWord* m_pWord;						// スコアの文字
	static int m_nScore;				// スコア
	int m_nDigit;						// 桁数
	int m_nLength;						// 文字列の長さ
	int m_nNumWord;						// 文字数
};

#endif // !_SCORE_H_
