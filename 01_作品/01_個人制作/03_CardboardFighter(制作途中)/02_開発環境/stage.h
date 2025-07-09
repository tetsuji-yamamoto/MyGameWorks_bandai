//******************************************
// 
// �X�e�[�W
// Author Tetsuji Yamamoto
// 
//******************************************
#ifndef _STAGE_H_
#define _STAGE_H_

#include "main.h"
#include "object.h"
#include "model.h"
#include "wall.h"
#include "meshField.h"
#include "sphere.h"
#include "cylinderBG.h"
#include "objectStage.h"
#include "sky.h"
#include <vector>

// �X�e�[�W�N���X
class CStage : public CObject // CObject�p��
{
public:
	// �ǂݎ��^�C�v
	typedef enum
	{
		TYPE_MODEL = 0,	// ���f��
		TYPE_MESHFIELD,	// ���b�V���t�B�[���h
		TYPE_MAX
	}TYPE;

	CStage();
	~CStage();

	HRESULT Init(void) { return S_OK; }
	HRESULT Init(const char *pFIleName);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Load(const char* pFileName);

	CSky* GetSphere() { return m_pSky; }
	CCylinderBG* GetCylinder() { return m_pCylinderBG; }
	CMeshField* GetMeshField() { return m_pMeshField; }
	std::vector<CWall*> Getwall() { return m_pWall; }
	std::vector<CObjectStage*> GetObjectStage() { return m_pObjStage; }

private:
	CMeshField* m_pMeshField;					// ���b�V���t�B�[���h�̃|�C���^�[
	CSky* m_pSky;								// ��̃|�C���^�[
	CCylinderBG* m_pCylinderBG;						// �V�����_�[�|�C���^�[
	std::vector<CWall*> m_pWall;				// ��
	std::vector<CObjectStage*> m_pObjStage;		// �I�u�W�F�N�g�X�e�[�W�̃|�C���^�[
};

#endif // !_STAGE_H_
