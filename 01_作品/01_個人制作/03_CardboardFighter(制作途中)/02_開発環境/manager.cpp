//**********************************************
// 
// マネージャー処理
// Author Tetsuji Yamamoto
// 
//**********************************************
#include "manager.h"
#include "object2D.h"
#include "object3D.h"
#include "player.h"
#include "enemy.h"
#include "explosion.h"
#include "bgManager.h"
#include "effect.h"
#include "number.h"
#include "score.h"
#include "timer.h"
#include "collision.h"

// 静的メンバー変数宣言
CRenderer* CManager::m_pRenderer = NULL ;				// レンダラー
CInputKeyboard* CManager::m_pInputKeyboard = NULL;		// キーボード
CInputMouse* CManager::m_pInputMouse = NULL;			// マウス
CInputJoypad* CManager::m_pInputJoypad = NULL;			// ジョイパッド
CSound* CManager::m_pSound = NULL;						// サウンド
CDebugprocc* CManager::m_pDebugprocc = NULL;			// デバッグ
CPause* CManager::m_pPause = NULL;						// ポーズ
CTexture* CManager::m_pTexture = NULL;					// テクスチャ
CCamera* CManager::m_pCamera = NULL;					// カメラ
CLight* CManager::m_pLight = NULL;						// ライト
CFontManager* CManager::m_pFontMane = NULL;				// フォント
CScore* CManager::m_pScore = NULL;						// スコア
CLoadMotionFile* CManager::m_pLoadMotionFile = NULL;	// モーションファイル読み取り
CStage* CManager::m_pStage = NULL;						// ステージポインタ
CPlayer* CManager::m_pPlayer = NULL;					// プレイヤーのポインター
std::vector<CEnemy*> CManager::m_pEnemy;				// エネミーポインター

//**********************************************
// マネージャーコンストラクタ
//**********************************************
CManager::CManager()
{
}

//**********************************************
// マネージャーデストラクタ
//**********************************************
CManager::~CManager()
{
}

//**********************************************
// マネージャー初期化処理
//**********************************************
HRESULT CManager::Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow)
{
	// メモリ確保
	m_pRenderer = new CRenderer;

	if (m_pRenderer != NULL)
	{// 確保できていれば
		// レンダラーの初期化
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{
			MessageBox(NULL, " CManager::Init() > if(FAILED(m_pRenderer->Init(hWnd, TRUE))) > 初期化できませんでした", "Error", MB_OK);
			return -1;
		}
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pRenderer != NULL) > m_pRendererメモリを確保できませんでした", "Error", MB_OK);
	}

	// メモリ確保
	m_pInputKeyboard = new CInputKeyboard;

	if (m_pInputKeyboard != NULL)
	{// 確保できていれば
		// キーボードの初期化
		if (FAILED(m_pInputKeyboard->Init(hinstance, hWnd)))
		{
			MessageBox(NULL, " CManager::Init() > if (FAILED(m_pInputKeyboard->Init(hinstance,hWnd))) > 初期化できませんでした", "Error", MB_OK);
			return -1;
		}
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pInputKeyboard != NULL) > m_pInputKeyboardメモリを確保できませんでした", "Error", MB_OK);
	}

	// メモリ確保
	m_pInputMouse = new CInputMouse;

	if (m_pInputMouse != NULL)
	{// 確保できていれば
		// マウスの初期化
		if (FAILED(m_pInputMouse->Init(hinstance, hWnd)))
		{
			MessageBox(NULL, " CManager::Init() > if (FAILED(m_pInputMouse->Init(hinstance,hWnd))) > 初期化できませんでした", "Error", MB_OK);
			return -1;
		}
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pInputMouse != NULL) > m_pInputKeyboardメモリを確保できませんでした", "Error", MB_OK);
	}

	// メモリ確保
	m_pInputJoypad = new CInputJoypad;

	if (m_pInputJoypad != NULL)
	{// 確保できていれば
		// ジョイパッドの初期化
		if (FAILED(m_pInputJoypad->Init(hinstance, hWnd)))
		{
			MessageBox(NULL, " CManager::Init() > if (FAILED(m_pInputJoypad->Init(hinstance,hWnd))) > 初期化できませんでした", "Error", MB_OK);
			return -1;
		}
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pInputJoypad != NULL) > m_pInputJoypadメモリを確保できませんでした", "Error", MB_OK);
	}

	// メモリ確保
	m_pSound = new CSound;

	if (m_pSound != NULL)
	{// 確保できていれば
		// サウンドの初期化
		if (FAILED(m_pSound->InitSound(hWnd)))
		{
			MessageBox(NULL, " CManager::Init() > if (FAILED(m_pSound->Init(hinstance,hWnd))) > 初期化できませんでした", "Error", MB_OK);
			return -1;
		}
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pSound != NULL) > m_pSoundメモリを確保できませんでした", "Error", MB_OK);
	}

	// メモリ確保
	m_pDebugprocc = new CDebugprocc;

	if (m_pDebugprocc != NULL)
	{// 確保できていれば
		// デバッグの初期化
		m_pDebugprocc->Init();
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pDebugprocc != NULL) > m_pDebugproccメモリを確保できませんでした", "Error", MB_OK);
	}

	// メモリ確保
	m_pCamera = new CCamera;
	if (m_pCamera != NULL)
	{// 確保できていれば
		// デバッグの初期化
		m_pCamera->Init();
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pCamera != NULL) > m_pCameraメモリを確保できませんでした", "Error", MB_OK);
	}

	// メモリ確保
	m_pLight = new CLight;
	if (m_pLight != NULL)
	{// 確保できていれば
		// デバッグの初期化
		m_pLight->Init();
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pLight != NULL) > m_pLightメモリを確保できませんでした", "Error", MB_OK);
	}


	// ヌルであれば
	if (m_pLoadMotionFile == NULL)
	{
		// モーションファイル読み取りクラスのメモリ確保
		m_pLoadMotionFile = CLoadMotionFile::Create();
	}

	// プレイヤーの生成
	if (m_pPlayer == NULL)
	{
		m_pPlayer = new CPlayer;
	}

	// ステージのインスタンス生成
	if (m_pStage == NULL)
	{
		m_pStage = new CStage;
	}

	// プレイヤーの生成
	m_pFontMane = CFontManager::Create();	// フォントマネージャー
	m_pTexture = CTexture::Create();		// テクスチャ
	m_pPause = CPause::Create();			// ポーズ
	m_pTexture->Load();						// テクスチャのロード

	m_pStage->Init("data\\text\\stage_load\\stage_000.txt");

	
	CEnemy* pEnemy = new CEnemy;
	pEnemy->Init(D3DXVECTOR3(0.0f, 0.0f, -80.0f), D3DXVECTOR3_NULL, 60, "data\\motion\\motion_enemy_armor.txt");
	m_pEnemy.push_back(pEnemy);

	m_pPlayer->Init(D3DXVECTOR3(0.0f,0.0f,-80.0f), D3DXVECTOR3_NULL,60, "data\\motion\\motion_player_001.txt");

	/*CEnemy* pEnemy2 = new CEnemy;
	pEnemy2->Init(D3DXVECTOR3(0.0f, 0.0f, -80.0f), D3DXVECTOR3_NULL, 60, "data\\motion\\motion_enemy_armor.txt");
	m_pEnemy.push_back(pEnemy2);*/
	return S_OK;
}

//**********************************************
// マネージャー終了処理
//**********************************************
void CManager::Uninit(void)
{
	// レンダラーの破棄
	if (m_pRenderer != NULL)
	{// ヌルでなかったら
		// レンダラーの終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	if (m_pRenderer != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pRenderer != NULL) > m_pRendererメモリがNULLではありません", "Error", MB_OK);
	}

	// キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{// ヌルでなかったら
		// キーボードの終了処理
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	if (m_pInputKeyboard != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pInputKeyboard != NULL) > m_pInputKeyboardメモリがNULLではありません", "Error", MB_OK);
	}

	// マウスの破棄
	if (m_pInputMouse != NULL)
	{// ヌルでなかったら
		// マウスの終了処理
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	if (m_pInputMouse != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pInputMouse != NULL) > m_pInputMouseメモリがNULLではありません", "Error", MB_OK);
	}

	// ジョイパッドの破棄
	if (m_pInputJoypad != NULL)
	{// ヌルでなかったら
		// ジョイパッドの終了処理
		m_pInputJoypad->Uninit();
		delete m_pInputJoypad;
		m_pInputJoypad = NULL;
	}

	if (m_pInputJoypad != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pInputJoypad != NULL) > m_pInputJoypadメモリがNULLではありません", "Error", MB_OK);
	}

	// サウンドの破棄
	if (m_pSound != NULL)
	{// ヌルでなかったら
		// サウンドの終了処理
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = NULL;
	}

	if (m_pSound != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pSound != NULL) > m_pSoundメモリがNULLではありません", "Error", MB_OK);
	}

	// デバッグの破棄
	if (m_pDebugprocc != NULL)
	{// ヌルでなかったら
		// デバッグの終了処理
		m_pDebugprocc->Uninit();
		delete m_pDebugprocc;
		m_pDebugprocc = NULL;
	}

	if (m_pDebugprocc != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pDebugprocc != NULL) > m_pDebugproccメモリがNULLではありません", "Error", MB_OK);
	}

	// カメラの破棄
	if (m_pCamera != NULL)
	{// ヌルでなかったら
		// デバッグの終了処理
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	if (m_pCamera != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pDebugprocc != NULL) > m_pDebugproccメモリがNULLではありません", "Error", MB_OK);
	}

	// ライトの破棄
	if (m_pLight != NULL)
	{// ヌルでなかったら
		// デバッグの終了処理
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// ライトが破棄されていない
	if (m_pLight != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pDebugprocc != NULL) > m_pDebugproccメモリがNULLではありません", "Error", MB_OK);
	}

	// モーションファイル読み取りクラスのメモリがあれば破棄
	if (m_pLoadMotionFile != NULL)
	{
		// メモリを破棄しNULLにする
		m_pLoadMotionFile->Uninit();
		m_pLoadMotionFile = NULL;
	}

	// フォントの破棄
	if (m_pFontMane != NULL)
	{
		m_pFontMane->Uninit();
		delete m_pFontMane;
		m_pFontMane = NULL;
	}

	// ポーズの破棄
	if (m_pPause != NULL)
	{
		m_pPause = NULL;	// ポーズのメモリを忘れる
	}

	//	テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Unload();	// テクスチャとメモリ破棄
		m_pTexture = NULL;		// 忘れる
	}

	// ステージの破棄
	if (m_pStage != NULL)
	{
		m_pStage = NULL;
	}

	// プレイヤーの破棄
	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;
	}

	// エネミーの破棄
	m_pEnemy.clear();
}

//**********************************************
// マネージャー更新処理
//**********************************************
void CManager::Update(void)
{
	m_pInputKeyboard->Update();	// キーボード
	m_pInputMouse->Update();	// マウス
	m_pInputJoypad->Update();	// ジョイパッド
	m_pCamera->Update();		// カメラ

	// 現在のポーズの有無を取得
	bool bNowPause = m_pPause->GetPause();	
	
	if (m_pInputKeyboard->GetTrigger(DIK_P) == true)
	{// Pキーを押したら
		// 現在とは逆のポーズにする
		m_pPause->SetPause(!bNowPause);
	}

	// デバッグモード時のみ有効
#ifdef _DEBUG
	// 当たり判定用モデルの描画操作
	CCollision::IsDraw();
#endif

	// ポーズ状態で無ければ
	if (m_pPause->GetPause() == false)
	{
		// レンダラーの更新処理
		m_pRenderer->Update();		
	}
}

//**********************************************
// マネージャー描画処理
//**********************************************
void CManager::Draw(void)
{
	m_pCamera->Debug();			// カメラのデバッグ表示
	CObject::DrawDebug();		// オブジェクトのデバッグ表示
	CTexture::DebugTexture();	// テクスチャンのデバッグ表示

	m_pRenderer->Draw();		// レンダラーの描画処理
}