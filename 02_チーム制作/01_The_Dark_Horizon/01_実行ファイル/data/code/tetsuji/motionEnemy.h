#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "model.h"

// �L�[�̍\����
typedef struct
{
	float fPosX;// �ʒuX
	float fPosY;// �ʒuY
	float fPosZ;// �ʒuZ
	float fRotX;// ����X
	float fRotY;// ����Y
	float fRotZ;// ����Z
}KEY;

// �L�[���̍\����
typedef struct
{
	int nFrame;		// �Đ��t���[��
	KEY aKey[16];	// �e�p�[�c�̃L�[�v�f
}KEY_INFO;

// �L�[���[�V�������\����
typedef struct
{
	bool bLoop;				// ���[�v���邩�ǂ���
	int nNumKey;			// �L�[�̑���
	KEY_INFO aKeyinfo[32];	// �L�[���
}MOTION_INFO;

typedef struct
{
	MOTION_INFO aMotionInfo[15];	// ���[�V�������
	int nNumMotion;					// ���[�V�����̑���
	bool bLoopMotion;				// ���[�v���邩�ǂ���
	int nNumKey;					// �L�[�̑���
	int nKey;						// ���݂̃L�[No.
	int nCounterMotion;				// ���[�V�����J�E���^�[
	int nNowMotiType;				// ���݂̃��[�V�����^�C�v

	int nNextKey;	// ���̃L�[
}MOTION;

// �L�����N�^�[�p�����[�^�[
typedef struct
{
	float fWidth;	// ��
	float fHeigt;	// ����
	float fJamp;	// �W�����v��
	int nNumModel;	// ���f����
	int nLife;		// �̗�
	int nState;		// ���
	int nCntState;	// ��ԊǗ��J�E���^�[
	int nCntOcc;	// �����J�E���^�[
	int nCntDura;	// �����J�E���^�[
	bool bMove;		// �������ǂ���
	bool bJanp;		// �W�����v���Ă��邩�ǂ���
	bool bDisp;		// �\�����܂���
	bool bAttack;	// �U�����Ă��邩�ǂ���
}CHARPARAM;

typedef struct
{
	int nCntMotionInfo;		//	���[�V���������J�E���g�������
	int nCntKeyInfo;	//	�L�[���[�V�����̏����J�E���g�������
	int nCntKey;		//	�L�[���J�E���g�������
}SET_MOTION_MANAGER;

// �v���g�^�C�v�錾
void InitMotion(void);
void ReadMotionText(const char* pFileName,Model *pModel, MOTION* motion, CHARPARAM *charParam);
void ReadScript(FILE *pFile,Model* pModel,MOTION *motion, CHARPARAM* charParam);
void ReadCharacterSet(FILE* pFile, Model* pModel, MOTION* motion, CHARPARAM* charParam);
bool UpdateMotion(MOTION *motion,Model *model, int nType,int nNumModel);

void MostionSet(FILE* pFile, MOTION* motion);
void MostionSet(MOTION* motion, MOTION_INFO setMotInfo);
void KeySet(FILE* pFile, MOTION* motion);
void EndKeySet(MOTION* motion, KEY_INFO keyInfo);
void Key(FILE* pFile, MOTION* motion);
void EndKey(MOTION* motion, KEY key);

void StringClear(char* astr, int nMaxCunt);
void ReadComment(FILE *pFile, char* aResult);
#endif // !_MOTION_H_