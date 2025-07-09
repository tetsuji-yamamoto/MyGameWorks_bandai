#ifndef _SWORD_H_
#define _SWORD_H_

#include "main.h"

#define SWORD_TEX "data\\SWORD\\LightningSword_001.png"	//���̃e�N�X�`��
#define SWORD_WIDTH (20)			//��
#define SWORD_HEIGHT (140)			//����
#define MAX_ATTACK_FLAME (25)		//�U���̑S�̃t���[��
#define SWORD_DAMAGE (1)			//���̍U����
#define BEAMSWORD_HEIGHT (400.0f)	//�r�[���\�[�h�̒���
#define DISCHARGE_TIMING (40)		//�W���X�g���o�L�]�t���[��
#define BEAMSWORD_ANDERCOLOR_RED "D3DXVECTOR3(1.0f,0.3f,0.3f,1.0f)"
#define BEAMSWORD_ANDERCOLOR_BLUE "D3DXVECTOR3(0.3f,0.3f,1.0f,1.0f)"
#define BEAMSWORD_FLONTCOLOR_RED "D3DXVECTOR3(1.0f,0.5f,0.5f,1.0f)"
#define BEAMSWORD_FLONTCOLOR_BLUE "D3DXVECTOR3(0.5f,0.5f,1.0f,1.0f)"

#define BEAMBEAMBEAM (-2)

//���̍U�����[�V����
typedef enum
{
	SWORDATTACK_PREMOVE = 0,	//�O����
	SWORDATTACK_MAINMOVE,		//�{����
	SWORDATTACK_LEARMOVE,		//�㓮��
	SWORDATTACK_MAX,
	
}SWORDATTACKMOVE;

//���̃��[�V�����̎�ޗ񋓌^
typedef enum
{
	SWORDANIMTYPE_NONE = 0,			//�Ȃ�
	SWORDANIMTYPE_ATTACK,			//�ʏ�U��
	SWORDANIMTYPE_CHARGE,			//�`���[�W
	SWORDANIMTYPE_DISCHARGE,		//���o
	SWORDANIMTYPE_JUSTDISCHARGE,	//�W���X�g���o
	SWORDANIMTYPE_MAX
}SWORDANIMTYPE;

//�r�[���\�[�h�\����
typedef struct
{
	D3DXCOLOR Andercol;	//�F
	D3DXCOLOR Floatcol;	//�F
	D3DXCOLOR tracecol;	//�F
	bool bBeamSword;	//�r�[���\�[�h�𐶐����Ă��邩�ǂ���
	float fBSHeight;	//�r�[���\�[�h�̒���
	float fBSWidth;		//�r�[���\�[�h�̕�
}BEAMSWORD;

//���\����
typedef struct
{
	BEAMSWORD beamSword;		//�r�[���\�[�h���
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR2 TopLeft;		//0
	D3DXVECTOR2 TopRight;		//1
	D3DXVECTOR2 BottomLeft;		//2
	D3DXVECTOR2 BottomRight;	//3
	D3DXCOLOR col;				//�F
	RECT rectHitBox;			//�����蔻��̑傫��
	int nState;					//���
	int nMoveCnt;				//�U���̃t���[���J�E���g
	float fAngle;				//�p�x
	float fKeepLot;				//�L�[�v����p�x
	float fLot;					//�ǉ��̊p�x
	float fPositionX;			//���̈ʒu
	float fTopLeftX;			//0X
	float fLength;				//�Ίp��
	bool bUse;					//�g�����ǂ���
	bool bHit;					//�����邩�ǂ���
	bool bJustDisCharge;		//�W���X�g���o���ǂ���
}SWORD;

//���A�j���[�V�����\����
typedef struct
{
	int nAnimTurn;				//�U���̏��
	float fAnimCnt1;			//�A�j���[�V�����t���[����1
	float fAnimCnt2;			//�A�j���[�V�����t���[����2
	float fAnimCnt3;			//�A�j���[�V�����t���[����3
	float fDesiredValueLot1;	//�ړI�̒l1
	float fDesiredValueLot2;	//�ړI�̒l2
	float fDesiredValueLot3;	//�ړI�̒l3
	float fBetweenLot;			//�ړI�̒l���獡�̒l�̊�
	bool bSetAnim;				//�v�Z���邩�ǂ���
}SWORDANIM;

//�v���g�^�C�v
void InitSword(void);
void UninitSword(void);
void UpdateSword(void);
void DrawSword(void);
void SetSword(D3DXVECTOR3 pos);
void EquipmentSword(void);//equipment
void SwordAnimation(int nType);
void SetSwordAnim(int type, float fCnt1, float fCnt2, float fCnt3, float fDesValuLot1, float fDesValuLot2, float fDesValuLot3);
bool HitSword(D3DXVECTOR3 pos, float fWidth);
void BeamSwordGeneration(int nTurn);
SWORD* GetSword(void);
SWORDANIM* GetSwordAnim(void);
#endif