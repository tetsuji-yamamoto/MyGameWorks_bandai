//**********************************************
// 
// �i���o�[
// Author Tetsuji Yamamoto
// 
//**********************************************
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "object2D.h"


// �i���o�[�N���X
class CNumber
{
public:
	CNumber();
	~CNumber();

	void Init(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight,int nNumber = 0);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CNumber* Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, int nNumber = 0);

	// �Q�b�^�[

	// �Z�b�^�[
	void SetNumber(int nNumber);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@
	int m_nNowNumber;						// ���̔ԍ�
	int m_nIdxTexture;						// �e�N�X�`���̃C���f�b�N�X
};

#endif // !_NUMBER_H_
