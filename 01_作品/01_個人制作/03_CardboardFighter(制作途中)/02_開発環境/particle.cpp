//*****************************************************
// 
// �p�[�e�B�N��
// Author Tetsuji Yamamoto
// 
//*****************************************************
#include "particle.h"


//*****************************************************
// �p�[�e�B�N������
//*****************************************************
void CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col,float fWidth,float fHeight ,int nLife,float fSpeed,int nAmount)
{
	D3DXVECTOR3 moveR = D3DXVECTOR3_NULL;

	for (int nCnt = 0; nCnt < nAmount; nCnt++)
	{
		int nLifeR = rand() % nLife + (int)((float)nLife * 0.7f);
		int nSpeed = (int)(fSpeed * 100.0f);
		float fSpeedR = (float)(rand() % nSpeed) * 0.01f;
		float fRotR = (float)(rand() % 628 - 314) * 0.01f;

		moveR.x = fSpeedR * sinf(fRotR);
		moveR.y = fSpeedR * cosf(fRotR);

		// �G�t�F�N�g����
		CEffect2DNomal::Create(pos, moveR, col, nLifeR, fWidth, fHeight);
	}
}