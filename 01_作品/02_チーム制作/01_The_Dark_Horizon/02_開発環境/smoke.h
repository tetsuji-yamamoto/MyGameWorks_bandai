#ifndef _SMOKE_H_
#define _SMOKE_H_

#include "main.h"

// ���̃^�C�v
typedef enum
{
	SMOKETYPE_NOMAL = 0,	// �ʏ�
	SMOKETYPE_ATTACH,		// ���t��
	SMOKETYPE_FUTSTEP,		// ����
	SMOKETYPE_MAX
}SMOKETYPE;

// �}�N����`
#define MAX_SMOKE (256)	// ���̍ő吔

// ���\����
typedef struct
{
	SMOKETYPE type;				// ���
	D3DXVECTOR3 pos;			// �ʒu
	int nOccurrenceTimer;		// �����^�C�}�[
	int nOccurrenceInterval;	// �����Ԋu
	float fSize;				// �傫��
	bool bUse;					// �g���Ă܂����H
	bool bAttach;				// �����Ɏ��t���܂����H
}SMOKE;

// �v���g�^�C�v�錾
void InitSmoke(void);
int SetSmoke(SMOKETYPE type,D3DXVECTOR3 pos, int nOccurrenceInterval, float fSize, bool bAttach);
void UpdateSmoke(void);
bool UpdateAttachSmoke(int nIdx, D3DXVECTOR3 pos);

#endif // !_SMOKE_H_
