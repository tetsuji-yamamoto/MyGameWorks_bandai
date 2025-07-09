#ifndef _HIT_H_
#define _HIT_H_

#include "main.h"

//�A���J�[�|�C���g�̏ꏊanchor point
typedef enum
{
	ANCHORPOINT_CENTER = 0,//center
	ANCHORPOINT_BOTTOMLEFT,//����
	ANCHORPOINT_BOTTOMCENTER,//������
}ANCHORPOINT;

//��`�̓����蔻��\����
typedef struct
{
	RECT rect;				//���_���
	VERTEX vertex;			//�l���_���
	D3DXVECTOR3 pos;		//�ʒu
	ANCHORPOINT anchrpoint;	//�A���J�[�|�C���g
}HITBOX;

bool HitBox(RECT rectA, RECT rectB, D3DXVECTOR3 posA, D3DXVECTOR3 posB, ANCHORPOINT anchorpointA, ANCHORPOINT anchorpointB);	//��`�Ƌ�`rectangleand rectangle

#endif // !_HIT_H_

