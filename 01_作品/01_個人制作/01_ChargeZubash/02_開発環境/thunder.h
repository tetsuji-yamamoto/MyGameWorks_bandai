#ifndef _THUNDER_H_
#define _THUNDER_H_

#include "main.h"

typedef enum
{
	THUNDERTYPE_NOMAL = 0,
	THUNDERTYPE_MAX
}THUNDERTYPE;

typedef enum
{
	THUNDERDIRECT_XSELECT = 0,	//������ꏊ��I��
	THUNDERDIRECT_YSELECT,		//������ꏊ��I��
	THUNDERDIRECT_PREMONISION,	//������ꏊ��\��������
	THUNDERDIRECT_FALLING,		//����
	THUNDERDIRECT_END,			//�I���
	THUNDERDIRECT_MAX,

}THUNDERDIRECT;
//�}�N����`
#define FILE_TEX_THUNDER "data\\THNDER\\Thunder_001.png"
#define MAX_THUNDER (50)//���̍ő吔
#define THUNDER_WIDTH (25)//���̕�
#define THUNDER_DAMAGE (1)//���̃_���[�W

//���\����
typedef struct
{
	const char* pFileName;	//�t�@�C���l�[��
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posOld;		//�O�̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXCOLOR col;			//�F
	int nType;				//�^�C�v
	int nThunderx;			//������ꏊ
	int nDirection;			//���o
	int nCntTiming;			//������^�C�~���O
	int nCntStrikeTime;		//������܂ł̃^�C�~���O
	int nEPower;			//�d��
	float fThunderWidth;	//��
	float fThunderHeight;	//����
	bool bUse;				//�g�p���Ă邩�ǂ���
	bool bHit;				//�������Ă��邩�ǂ���
	bool bFell;				//���������ǂ���
}THUNDER;

//�v���g�^�C�v�錾
void InitThunder(void);
void UninitThunder(void);
void UpdateThunder(void);
void DrawThunder(void);
void SetThunder(const char* pFileName, THUNDERTYPE type);
void LightningStrike(int nCntThunder);
void SelectStrike(int nCntThunder);
void ThunderFalling(int nCntThunder);
bool HitThunder(D3DXVECTOR3 pos, float fHeight);
#endif // !1
