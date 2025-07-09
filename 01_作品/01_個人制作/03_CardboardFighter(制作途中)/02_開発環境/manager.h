//**********************************************
// 
// �}�l�[�W���[����
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

// �}�l�[�W���[�N���X
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
	static CRenderer* m_pRenderer;				// �����_���[�ւ̃|�C���^
	static CInputKeyboard* m_pInputKeyboard;	// �L�[�{�[�h�ւ̃|�C���^
	static CInputMouse* m_pInputMouse;			// �}�E�X�ւ̃|�C���^
	static CInputJoypad* m_pInputJoypad;		// �W���C�p�b�h�ւ̃|�C���^
	static CSound* m_pSound;					// �T�E�h�ւ̃|�C���^
	static CDebugprocc* m_pDebugprocc;			// �f�o�b�O�̃|�C���^
	static CPause* m_pPause;					// �|�[�Y�̃|�C���^
	static CTexture* m_pTexture;				// �e�N�X�`���̃|�C���^
	static CCamera* m_pCamera;					// �J�����̃|�C���^
	static CLight* m_pLight;					// ���C�g�̃|�C���^
	static CLoadMotionFile* m_pLoadMotionFile;	// ���[�V�����t�@�C���ǂݎ��|�C���^
	static CFontManager* m_pFontMane;			// �t�H���g�}�l�[�W���[�̃|�C���^
	static CScore* m_pScore;					// �X�R�A�ւ̃|�C���^
	static CPlayer* m_pPlayer;					// �v���C���[�̃|�C���^
	static CStage* m_pStage;					// �X�e�[�W�|�C���^
	CMeshField* m_pMeshField;					// ���b�V���t�B�[���h�̃|�C���^�[
	static std::vector<CEnemy*>m_pEnemy;				// �G�l�~�[�|�C���^�[

};

#endif // !_MANAGER_H_