//**********************************************
// 
// マネージャー処理
// Author Tetsuji Yamamoto
// 
//**********************************************
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "sound.h"
#include "debugproc.h"
#include "pause.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "object3D.h"
#include "objectX.h"
#include "objectBillboard.h"
#include "word.h"
#include "string.h"
#include "fontManager.h"
#include "loadMotionFile.h"
#include "sphere.h"
#include "meshField.h"
#include "cylinder.h"
#include "wall.h"
#include "stage.h"
#include "objectStage.h"
#include "enemy.h"
#include "sky.h"
#include "particle.h"
#include <vector>

// マネージャークラス
class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRenderer* GetRenderer(void) { return m_pRenderer; };
	static CInputKeyboard* GetInputKeyboard(void) { return m_pInputKeyboard; };
	static CInputMouse* GetInputMouse(void) { return m_pInputMouse; };
	static CInputJoypad* GetInputJoypad(void) { return m_pInputJoypad; };
	static CSound* GetSound(void) { return m_pSound; };
	static CDebugprocc* GetDebugprocc(void) { return m_pDebugprocc; };
	static CPause* GetPause(void) { return m_pPause; };
	static CTexture* GetTexture(void) { return m_pTexture; };
	static CCamera* GetCamera(void) { return m_pCamera; };
	static CLight* GetLight(void) { return m_pLight; };
	static CFontManager* GetFOntMane(void) { return m_pFontMane; };
	static CScore* GetScore(void) { return m_pScore; }
	static CLoadMotionFile* GetLoadMotionFile() { return m_pLoadMotionFile; }
	static CPlayer* GetPlayer(void) { return m_pPlayer; }
	static CStage* GetStage(void) { return m_pStage; }
	static std::vector<CEnemy*> GetEnmey(void) { return m_pEnemy; }

private:
	static CRenderer* m_pRenderer;				// レンダラーへのポインタ
	static CInputKeyboard* m_pInputKeyboard;	// キーボードへのポインタ
	static CInputMouse* m_pInputMouse;			// マウスへのポインタ
	static CInputJoypad* m_pInputJoypad;		// ジョイパッドへのポインタ
	static CSound* m_pSound;					// サウドへのポインタ
	static CDebugprocc* m_pDebugprocc;			// デバッグのポインタ
	static CPause* m_pPause;					// ポーズのポインタ
	static CTexture* m_pTexture;				// テクスチャのポインタ
	static CCamera* m_pCamera;					// カメラのポインタ
	static CLight* m_pLight;					// ライトのポインタ
	static CLoadMotionFile* m_pLoadMotionFile;	// モーションファイル読み取りポインタ
	static CFontManager* m_pFontMane;			// フォントマネージャーのポインタ
	static CScore* m_pScore;					// スコアへのポインタ
	static CPlayer* m_pPlayer;					// プレイヤーのポインタ
	static CStage* m_pStage;					// ステージポインタ
	CMeshField* m_pMeshField;					// メッシュフィールドのポインター
	static std::vector<CEnemy*>m_pEnemy;				// エネミーポインター

};

#endif // !_MANAGER_H_