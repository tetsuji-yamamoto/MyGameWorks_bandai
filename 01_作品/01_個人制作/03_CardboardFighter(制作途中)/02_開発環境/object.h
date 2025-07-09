//**********************************************
// 
// �I�u�W�F�N�g����
// Author Tetsuji Yamamoto
// 
//**********************************************
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "renderer.h"

// �}�N����`
#define MAX_OBJECT (2560)			// �I�u�W�F�N�g�̍ő吔
#define OBUJECT2D_WIDTH (100.0f)	// �I�u�W�F�N�g2D�̕�
#define PRIORITY_NOMAL (3)			// �D��x�̏����l 

// �I�u�W�F�N�g�N���X
class CObject
{
public:
	// �^�C�v
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_BULLET,
		TYPE_BG,
		TYPE_EXPLOSION,
		TYPE_EFFECT,
		TYPE_SCORE,
		TYPE_MODEL_X,
		TYPE_MAX
	}TYPE;

	// �D��x
	typedef enum
	{
		PRIORITY_0 = 0,
		PRIORITY_1,
		PRIORITY_2,
		PRIORITY_3,
		PRIORITY_4,
		PRIORITY_5,
		PRIORITY_6,
		PRIORITY_7,
		PRIORITY_8,
		PRIORITY_MAX
	}PRIORITY;

	CObject(int nPriority = PRIORITY_NOMAL);
	virtual ~CObject();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static void DrawDebug(void);

	static int GetObujectNumAll(){ return m_nNumAll; }
	void SetType(TYPE type) { m_type = type; };
	void SetPriority(PRIORITY priority) { m_nPriority = priority; };

	static CObject* GetTop(int nPriority) { return m_aPTop[nPriority]; };
	CObject* GetNext(void) { return m_pNext; };
	TYPE GetType(void) { return m_type; };
	int GetPriority(void) { return m_nPriority; };

protected:
	void Release(void);

private:
	static CObject* m_aPTop[PRIORITY_MAX];	// �擪�̃A�h���X
	static CObject* m_aPCur[PRIORITY_MAX];	// �Ō���̃A�h���X
	CObject* m_pPrev;						// �O�̃I�u�W�F�N�g�̃|�C���^
	CObject* m_pNext;						// ���̃I�u�W�F�N�g�̃|�C���^
	bool m_bDeath;							//	���S�t���O

	static int m_nNumAll;	// �I�u�W�F�N�g�̑���
	int m_nID;				// �������g��ID
	int m_nPriority;		// �D��x
	TYPE m_type;			// ���
};

#endif
