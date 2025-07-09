//*************************************
// 
// ���[�V����
// Author Tetsuji Yamamoto
// 
//*************************************
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "model.h"
#include <vector>

// �L�[�N���X
class CKey
{
public:
	CKey();
	~CKey();

	void Uninit(void) { delete this; }

	// �Z�b�^�[
	void SetPositionX(float fPosX) { m_fPosX = fPosX; }
	void SetPositionY(float fPosY) { m_fPosY = fPosY; }
	void SetPositionZ(float fPosZ) { m_fPosZ = fPosZ; }
	void SetRotationX(float fRotX) { m_fRotX = fRotX; }
	void SetRotationY(float fRotY) { m_fRotY = fRotY; }
	void SetRotationZ(float fRotZ) { m_fRotZ = fRotZ; }

	// �Q�b�^�[
	float GetPositionX(void) {return m_fPosX; }
	float GetPositionY(void) {return m_fPosY; }
	float GetPositionZ(void) {return m_fPosZ; }
	float GetRotationX(void) {return m_fRotX; }
	float GetRotationY(void) {return m_fRotY; }
	float GetRotationZ(void) {return m_fRotZ; }

private:
	float m_fPosX;	// �ʒuX
	float m_fPosY;	// �ʒuY
	float m_fPosZ;	// �ʒuZ
	float m_fRotX;	// ����X
	float m_fRotY;	// ����Y
	float m_fRotZ;	// ����Z
};

// �L�[���N���X
class CKeyInfo
{
public:
#define KEY_NUM (16)	// �L�[��

	CKeyInfo();
	~CKeyInfo();

	void Uninit(void);
	CKey* CreateKey(int nNumKey);

	// �Z�b�^�[
	void SetFrame(int nFrame) { m_nFrame = nFrame; }
	void SetPushBackKey(CKey** ppKey) { m_pKey.push_back(*ppKey); }

	// �Q�b�^�[
	int GetFrame(void) { return m_nFrame; }
	auto GetKey(int nElementNum) { return m_pKey.begin() + nElementNum; }
	auto GetKeyBegin(void) { return m_pKey.begin(); }
	auto GetKeyEnd(void) { return m_pKey.end(); }
	auto GetKeyElementEnd(void) { return m_pKey.end() - 1; }

private:
	int m_nFrame;	// �Đ��t���[��
	std::vector<CKey*> m_pKey;	// �e�p�[�c�̃L�[�v�f
	int m_nNumkey;	// �L�[�̐�
};

// �L�[���[�V�������N���X
class CMotionInfo
{
public:
#define KEYINFO_NUM (32)	// �L�[���

	CMotionInfo();
	~CMotionInfo();

	void Uninit(void);
	CKeyInfo* CreateKeyInfo(int nNumKeyInfo);

	// �Z�b�^�[
	void SetLoop(bool bLoop) { m_bLoop = bLoop; }
	void SetNumKey(int nNumKey) { m_nNumKey = nNumKey; }
	void SetPushBackKeyInfo(CKeyInfo** ppKeyInfo) { m_pKeyinfo.push_back(*ppKeyInfo); }

	// �Q�b�^�[
	bool GetLoop(void) { return m_bLoop; }
	int GetNumKey(void) { return m_nNumKey; }
	auto GetKeyInfo(int nElementNum) { return m_pKeyinfo.begin() + nElementNum; }
	auto GetKeyInfoBegin(void) { return m_pKeyinfo.begin(); }
	auto GetKeyInfoEnd(void) { return m_pKeyinfo.end(); }
	auto GetKeyInfoElementEnd(void) { return m_pKeyinfo.end() - 1; }

private:
	bool m_bLoop;			// ���[�v���邩�ǂ���
	int m_nNumKey;			// �L�[�̑���
	std::vector<CKeyInfo*> m_pKeyinfo;	// �L�[���
	int m_nNumKeyInfo;		// �L�[���̐�
};

// ���[�V�����N���X
class CMotion
{
public:
#define MOTIONINFO_NUM (15)	// ���[�V�������

	CMotion();
	~CMotion();

	void Init(int nNumMotion);
	void Uninit(void);
	void SetMotion(int nSetMotion);
	void SetMotionblend(CMotion* pBlendMotion,int nSetMotion, int nBlendTime);
	void UpdateMotionGetKey(D3DXVECTOR3* pOutPos, D3DXVECTOR3* pOutRot, int nMotion, int nKey);
	void UpdateMotionGetKeyBlend(D3DXVECTOR3* pOutPos, D3DXVECTOR3* pOutRot, int nMotion, int nKey);
	void UpdateMotionModel();
	void UpdateMotionModelBlend(CMotion* pBlendMotion);
	void CountUpMotionCounter(void) { m_nCounterMotion++; }

	// �Z�b�^�[
	void SetNumMotion(int nNumMotion) { m_nNumMotion = nNumMotion; }
	void SetKeySet(int nKey) { m_nKeySet = nKey; }
	void SetNextKeySet(int nNextKey) { m_nNextKeySet = nNextKey; }
	void SetCounterMotion(int nCounterMotion) { m_nCounterMotion = nCounterMotion; }
	void SetPushBackMotionInfo(CMotionInfo** ppMotionInfo) { m_pMotionInfo.push_back(*ppMotionInfo); }
	void SetModel(std::vector<CModel*>* ppModel);

	// �Q�b�^�[
	int GetNumMotion(void) {return m_nNumMotion; }
	int GetKeySet(void) { return m_nKeySet; }
	int GetNextKeySet(void) { return m_nNextKeySet; }
	int GetCounterMotion(void) { return m_nCounterMotion; }
	auto GetMotionInfo(int nElementNum) { return m_pMotionInfo.begin() + nElementNum; }
	bool GetIsEndMotion(void) { return m_bEndMotion; }

private:

	std::vector<CModel*> m_pModel;		// ���f���ւ̃|�C���^
	std::vector < CMotionInfo*> m_pMotionInfo;	// ���[�V�������
	int m_nNumMotion;					// ���[�V�����̑���
	int m_nKeySet;						// ���݂̃L�[�Z�b�gNo.
	int m_nNextKeySet;					// ���̃L�[�w�Z�b�g
	int m_nCounterMotion;				// ���[�V�����J�E���^�[
	int m_nTypeMotion;					// ���[�V�����^�C�v
	int m_nNumModel;					// ���f����
	bool m_bEndMotion;					// ���[�V�������I��������ǂ���
	bool m_bBlend;						// ���[�V�����u�����h�̗L��
	int m_nBlendTime;					// �u�����h����
	int m_nCntBlend;					// �u�����h�J�E���^�[
	int m_nTypeBlendMotion;				// �u�����h���郂�[�V�����^�C�v
};

#endif // !_MOTION_H_