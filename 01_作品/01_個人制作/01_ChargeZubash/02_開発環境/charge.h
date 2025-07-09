#ifndef _CHARGE_H_
#define _CHARGE_H_

#include "main.h"

#define MAX_ELECTRICPOWER (5) //�ő�d��electric power
#define MAX_CHARGERUI (10)		//UI�̖���
#define CHARGE_HEIGHT (20)		//����
#define CHARGE_WIDTH (30)		//��
#define FILE_TEX_CHARGER_FLAME "data\\CHARGER\\Charger_Flame_001.png"
#define FILE_TEX_CHARGER_GAUGE "data\\CHARGER\\Charger_Gauge_001.png"

//�[�d��UI�^�C�v�񋓌^
typedef enum
{
	CHARGEUITYPE_FLAME = 0,	//�t���[��
	CHARGEUITYPE_GAUGE,		//�Q�[�W
	CHARGEUITYPE_MAX
}CHARGERUITYPE;

//�[�d��̏�ԗ񋓌^
typedef enum
{
	CHARGESTATE_NONE = 0,	//�Ȃ�
	CHARGESTATE_FULL,		//�t��
	CHARGESTATE_MAX
}CHARGESTATE;

//�[�d��̎��
typedef enum
{
	CHARGENUM_ZERO = 0,	//���
	CHARGENUM_ONE,		//���
	CHARGENUM_TWO,		//�O��
	CHARGENUM_THREE,	//�l��
	CHARGENUM_FOUR,		//�܌�
	CHARGENUM_MAX
}CHARGENUM;

//�[�d��UI�̍\����
typedef struct
{
	const char* pFileName;	//�t�@�C���̃p�X
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	int nType;				//���
	int nState;				//���
	int nNumber;			//��
	float fHeight;			//����
	float fWidth;			//��
	bool bUse;				//�g�p���Ă��邩�ǂ���
}CHARGERUI;

//�[�d�G�l���M�[�̍\����
typedef struct
{
	float fChargrAmount;//�[�d��Charge amount
	int nCntTime;			//���d�J�E���g
}CHARGE;

//�v���g�^�C�v
void InitCharge(void);
void UninitCharge(void);
void UpdateCharge(void);
void DrawCharge(void);
void SetCharger(const char* pFileName, D3DXVECTOR3 pos, CHARGERUITYPE type, int num,float fWidth);
void ChargePower(float fEPower);
void ChargerFlameState(int nCntCharger);
void ChargerGaugeState(int nCntCharger);
void DisCharge(D3DXVECTOR3 pos);
CHARGE* GetCharge(void);
#endif