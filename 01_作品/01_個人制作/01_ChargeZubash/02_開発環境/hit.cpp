#include "hit.h"
#include "effect.h"
//��`�Ƌ�`�̓����蔻��
bool HitBox(RECT rectA, RECT rectB,D3DXVECTOR3 posA,D3DXVECTOR3 posB, ANCHORPOINT anchorpointA, ANCHORPOINT anchorpointB)
{
	bool bHit = false;
	HITBOX hitbox[2];

	//�u�`�R��
	hitbox[0].rect = rectA;
	hitbox[1].rect = rectB;
	hitbox[0].pos = posA;
	hitbox[1].pos = posB;
	hitbox[0].anchrpoint = anchorpointA;
	hitbox[1].anchrpoint = anchorpointB;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{//����v�Z
		//�l���_�ɏ��Ԃ�����
		switch (hitbox[nCnt].anchrpoint)
		{
		case ANCHORPOINT_CENTER://����
			hitbox[nCnt].vertex.BottomLeft.x = hitbox[nCnt].pos.x - hitbox[nCnt].rect.left;
			hitbox[nCnt].vertex.BottomLeft.y = hitbox[nCnt].pos.y + hitbox[nCnt].rect.bottom;
			hitbox[nCnt].vertex.BottomRight.x = hitbox[nCnt].pos.x + hitbox[nCnt].rect.right;
			hitbox[nCnt].vertex.BottomRight.y = hitbox[nCnt].pos.y + hitbox[nCnt].rect.bottom;
			hitbox[nCnt].vertex.TopLeft.x = hitbox[nCnt].pos.x - hitbox[nCnt].rect.left;
			hitbox[nCnt].vertex.TopLeft.y = hitbox[nCnt].pos.y - hitbox[nCnt].rect.top;
			hitbox[nCnt].vertex.TopRight.x = hitbox[nCnt].pos.x + hitbox[nCnt].rect.right;
			hitbox[nCnt].vertex.TopRight.y = hitbox[nCnt].pos.y - hitbox[nCnt].rect.top;
			break;

		case ANCHORPOINT_BOTTOMLEFT://����
			hitbox[nCnt].vertex.BottomLeft.x = hitbox[nCnt].pos.x;
			hitbox[nCnt].vertex.BottomLeft.y = hitbox[nCnt].pos.y;
			hitbox[nCnt].vertex.BottomRight.x = hitbox[nCnt].pos.x + hitbox[nCnt].rect.right;
			hitbox[nCnt].vertex.BottomRight.y = hitbox[nCnt].pos.y;
			hitbox[nCnt].vertex.TopLeft.x = hitbox[nCnt].pos.x;
			hitbox[nCnt].vertex.TopLeft.y = hitbox[nCnt].pos.y - hitbox[nCnt].rect.top * 2.0f;
			hitbox[nCnt].vertex.TopRight.x = hitbox[nCnt].pos.x + hitbox[nCnt].rect.right;
			hitbox[nCnt].vertex.TopRight.y = hitbox[nCnt].pos.y - hitbox[nCnt].rect.top * 2.0f;
			break;

		case ANCHORPOINT_BOTTOMCENTER://������
			hitbox[nCnt].vertex.BottomLeft.x = hitbox[nCnt].pos.x - hitbox[nCnt].rect.left;
			hitbox[nCnt].vertex.BottomLeft.y = hitbox[nCnt].pos.y;
			hitbox[nCnt].vertex.BottomRight.x = hitbox[nCnt].pos.x + hitbox[nCnt].rect.right;
			hitbox[nCnt].vertex.BottomRight.y = hitbox[nCnt].pos.y;
			hitbox[nCnt].vertex.TopLeft.x = hitbox[nCnt].pos.x - hitbox[nCnt].rect.left;
			hitbox[nCnt].vertex.TopLeft.y = hitbox[nCnt].pos.y - hitbox[nCnt].rect.top * 2.0f;
			hitbox[nCnt].vertex.TopRight.x = hitbox[nCnt].pos.x + hitbox[nCnt].rect.right;
			hitbox[nCnt].vertex.TopRight.y = hitbox[nCnt].pos.y - hitbox[nCnt].rect.top * 2.0f;
			break;
		}
	}

	if (hitbox[0].vertex.TopLeft.x <= hitbox[1].vertex.BottomRight.x &&
		hitbox[1].vertex.TopLeft.x <= hitbox[0].vertex.BottomRight.x &&
		hitbox[0].vertex.TopLeft.y <= hitbox[1].vertex.BottomRight.y &&
		 hitbox[1].vertex.TopLeft.y <= hitbox[0].vertex.BottomRight.y)
	{
		bHit = true;
	}

	//SetEffect(D3DXVECTOR3(hitbox[0].vertex.BottomLeft.x, hitbox[0].vertex.BottomLeft.y, 0.0f),	//�ʒu
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//�ړ���
	//	D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f),		//�F
	//	EFFECTTYPE_NOMAL,						//�ʏ�G�t�F�N�g
	//	10.0f,									//�|���S���T�C�Y
	//	0.0f,									//����
	//	0.0f,									//��
	//	0.0f,									//�|���S���T�C�Y������
	//	0.0f,									//�ړ��ʌ�����
	//	2.0f,									//����
	//	0.0f,									//�p�x
	//	-1										//�������
	//);

	//SetEffect(D3DXVECTOR3(hitbox[0].vertex.BottomRight.x, hitbox[0].vertex.BottomRight.y, 0.0f),	//�ʒu
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//�ړ���
	//	D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f),		//�F
	//	EFFECTTYPE_NOMAL,						//�ʏ�G�t�F�N�g
	//	10.0f,									//�|���S���T�C�Y
	//	0.0f,									//����
	//	0.0f,									//��
	//	0.0f,									//�|���S���T�C�Y������
	//	0.0f,									//�ړ��ʌ�����
	//	2.0f,									//����
	//	0.0f,									//�p�x
	//	-1										//�������
	//);

	//SetEffect(D3DXVECTOR3(hitbox[0].vertex.TopLeft.x, hitbox[0].vertex.TopLeft.y, 0.0f),	//�ʒu
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//�ړ���
	//	D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f),		//�F
	//	EFFECTTYPE_NOMAL,						//�ʏ�G�t�F�N�g
	//	10.0f,									//�|���S���T�C�Y
	//	0.0f,									//����
	//	0.0f,									//��
	//	0.0f,									//�|���S���T�C�Y������
	//	0.0f,									//�ړ��ʌ�����
	//	2.0f,									//����
	//	0.0f,									//�p�x
	//	-1										//�������
	//);

	//SetEffect(D3DXVECTOR3(hitbox[0].vertex.TopRight.x, hitbox[0].vertex.TopRight.y, 0.0f),	//�ʒu
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//�ړ���
	//	D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f),		//�F
	//	EFFECTTYPE_NOMAL,						//�ʏ�G�t�F�N�g
	//	10.0f,									//�|���S���T�C�Y
	//	0.0f,									//����
	//	0.0f,									//��
	//	0.0f,									//�|���S���T�C�Y������
	//	0.0f,									//�ړ��ʌ�����
	//	2.0f,									//����
	//	0.0f,									//�p�x
	//	-1										//�������
	//);

	return bHit;
}