//******************************************
// 
// ステージ
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

// ステージクラス
class CStage : public CObject // CObject継承
{
public:
	// 読み取りタイプ
	typedef enum
	{
		TYPE_MODEL = 0,	// モデル
		TYPE_MESHFIELD,	// メッシュフィールド
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
	CMeshField* m_pMeshField;					// メッシュフィールドのポインター
	CSky* m_pSky;								// 空のポインター
	CCylinderBG* m_pCylinderBG;						// シリンダーポインター
	std::vector<CWall*> m_pWall;				// 壁
	std::vector<CObjectStage*> m_pObjStage;		// オブジェクトステージのポインター
};

#endif // !_STAGE_H_
