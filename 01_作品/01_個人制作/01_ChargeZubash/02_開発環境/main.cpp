#include "main.h"
#include "input.h"
#include "sound.h" 
#include "fade.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "ranking.h" 
#include "tutorial.h" 
#include "background.h" 
#include "player.h" 
#include "block.h" 
#include "enemy.h" 

//�O���[�o���ϐ��錾
LPDIRECT3D9 g_pD3D = NULL;						//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Direct3D�f�o�C�X�ւ̃|�C���^
MODE g_mode = MODE_TITLE;						//���݂̃��[�h
LPD3DXFONT g_pFont = NULL;						//�t�H���g�ւ̃|�C���^
int g_nCountFPS = 0;
bool g_isFullscreen = false;					//�E�B���h�E��؂�ւ��邽�߂̃t���O
RECT g_windowRect;								//�E�B���h�E��؂�ւ��邽�߂̕ϐ�

//=======================
//�f�o�C�X�̎擾
//=======================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=======================
//���C���֐�
//=======================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev,_In_ LPSTR lpCmdLine,_In_ int nCmdShow)
{
	WNDCLASSEX wcex =					//�E�B���h�E�N���X�̍\����
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,						//�E�B���h�E�̃X�^�C��
		WindowProc,						//�E�B���h�E�v���V�[�W��
		0,								//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,								//0�ɂ���(�ʏ�͎g�p���Ȃ�)	
		hInstance,						//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),	//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),		//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),		//�N���C�A���g�̈�̔w�i�F
		NULL,							//���j���[�o�[
		CLASS_NAME,						//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)	//�t�@�C���̃A�C�R��
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//��ʃT�C�Y�̍\����
		
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;//���ݎ���
	DWORD dwExecLastTime;//���ݎ���
	DWORD dwFrameCount;//�t���[���J�E���g
	DWORD dwFPSLastTime;//�Ō��FPS���v����������

	//�E�B���h�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,		//�g���E�B���h�E�X�^�C��
		CLASS_NAME,					//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,				//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,				//�E�B���h�E����X���W
		CW_USEDEFAULT,				//�E�B���h�E����Y���W
		(rect.right - rect.left),	//�E�B���h�E�̕�
		(rect.bottom - rect.top),	//�E�B���h�E�̍���
		NULL,						//�e�E�B���h�E�̃n���h��
		NULL,						//���j���[�n���h���܂��͎q�E�B���h�E�̃n���h��
		hInstance,					//�C���X�^���X�n���h��
		NULL);						//�E�B���h�E�����f�[�^

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//���������������s�����Ƃ�
		return -1;
	}

	//�W���C�p�b�h�̏���������
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);	//�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);			//�N���C�A���g�̈���X�V
	
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windoes�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);	//���z���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);	//�E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DilectX�̏���
			dwCurrentTime = timeGetTime();//���ݎ������擾
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;											//FPS�𑪒肵����ۑ�
				dwFrameCount = 0;														//�t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))//60�t���[��
			{
				dwExecLastTime = dwCurrentTime;
				//�X�V����
				Updata();
				//�`�揈��
				Draw();
				dwFrameCount++;//�t���[���J�E���g�����Z
			}
		}
	}
	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//==========================================
// �E�B���h�E���t���X�N���[���ɕς��鏈��
//==========================================
void ToggleFullscreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}

//==========================================
//�E�B���h�v���V�[�W��
//==========================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY://�E�B���h�j�����b�Z�[�W

		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN://�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:	//ESC�������ꂽ��

			//�E�B���h�E��j������(EM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
			break;

		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//==========================================
//�����������
//==========================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//���X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;//�v���[���e�[�V�����p�����[�^

	//Direc3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^��ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));//�p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;//�Q�[����ʃT�C�Y��
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//�Q�[����ʃT�C�Y����
	d3dpp.BackBufferFormat = d3ddm.Format;//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;//
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//
	d3dpp.EnableAutoDepthStencil = TRUE;//
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//
	d3dpp.Windowed = bWindow;//
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//

	//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐���(�`�揈�����n�[�h�E�F�A,���_������CPU�ōs��)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//�J�����O�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);//�v���C���[�̒��ɓ����x��������
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//�T���u���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);

	//�L�[�{�[�h��������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�w�i�̏�����
	InitBG();
	//�T�E���h�̏���������
	InitSound(hWnd);
	//���[�h�̐ݒ�
	SetMode(g_mode);
	//�t�F�[�h�̐ݒ�
	InitFade(g_mode);
	//�f�o�b�O�p�\���t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"terminal", &g_pFont);

	return S_OK;
}

//==========================================
//�I������
//==========================================
void Uninit(void)
{
	//�T�E���h�̏I������
	UninitSound();

	//�t�F�[�h�̏I������
	UninitFade();

	//�`���[�g���A����ʂ̏I������
	UninitTutorial();

	//�Q�[����ʂ̏I������
	UninitGame();

	//���U���g��ʂ̏I������
	UninitResult();

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�W���C�p�b�h�̏I������
	UninitJoypad();

	//�w�i�̏I��
	UninitBG();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice = NULL;
	}
	//Direct3D�I�u�W�F�N�g
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	//�f�o�b�O�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//==========================================
// �X�V����
//==========================================
void Updata(void)
{
	//�w�i�̍X�V
	UpdateBG();

	//�L�[���͂̍X�V����
	UpdataKeyboard();

	//�W���C�p�b�h�̍X�V����
	UpdataJoypad();

	switch (g_mode)
	{
	case MODE_TITLE:	//�^�C�g�����
		UpdateTitle();
		break;
	case MODE_GAME:		//�Q�[�����
		UpdateGame();
		break;
	case MODE_RESULT:	//���U���g���
		UpdateResult();
		break;
	case MODE_RANKING:	//�����L���O���
		UpdateRanking();
		break;
	case MODE_TUTORIAL:	//�`���[�g���A�����
		UpdateTutorial();
		break;
	}
	
	//�t�F�[�h�̍X�V����
	UpdateFade();
}

//==========================================
//�`�揈��
//==========================================
void Draw(void)
{
	//��ʃN���A(�o�b�t�@�o�b�t�@&�̃N���A�j
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		 D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		//�w�i�̕`��
		DrawBG();		

		switch (g_mode)
		{
		case MODE_TITLE:	//�^�C�g�����
			DrawTitle();
			break;
		case MODE_GAME:		//�Q�[�����
			DrawGame();
			break;
		case MODE_RESULT:	//���U���g���
			DrawResult();
			break;
		case MODE_RANKING:	//�����L���O���
			DrawRanking();
			break;

		case MODE_TUTORIAL:	//�`���[�g���A�����
			DrawTutorial();
			break;
		}

		//�t�F�[�h�̕`�揈��
		DrawFade();
#ifdef _DEBUG //�f�o�b�O�r���h�������\��

		//FPS�\��
		DrawFPS();

		//�v���C���[�̍��W
		DebagDrawPlayer();

		//�u���b�N�̏���
		DebagDrawBlock();

		//�G�l�~�[
		DebagDrawEnemy();
#endif

		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//==========================================
//���[�h�̐ݒ�
//==========================================
void SetMode(MODE mode)
{
	//���݂̉��(���[�h)�̏I������
	switch (g_mode)
	{
	case MODE_TITLE:	//�^�C�g�����
		UninitTitle();
		break;
	case MODE_GAME:		//�Q�[�����
		UninitGame();
		break;
	case MODE_RESULT:	//���U���g���
		UninitResult();
		break;
	case MODE_RANKING:	//�����L���O���
		UninitRanking();
		break;

	case MODE_TUTORIAL:	//�`���[�g���A�����
		UninitTutorial();
		break;
	}

	//�V������ʉ��(���[�h)�̏���������
	switch (mode)
	{
	case MODE_TITLE:	//�^�C�g�����
		InitTitle();
		break;

	case MODE_GAME:		//�Q�[�����
		InitGame();
		break;

	case MODE_RESULT:	//���U���g���
		InitResult();
		break;

	case MODE_RANKING:	//�����L���O���
		InitRanking();
		break;

	case MODE_TUTORIAL:	//�`���[�g���A�����
		InitTutorial();
		break;
	}

	g_mode = mode;//���݂̉��(���[�h)��؂�ւ���

}

//==========================================
//���[�h�̎擾
//==========================================
MODE GetMode(void)
{
	return g_mode;
}

//==========================================
//�f�o�b�O�\��
//==========================================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	//�����ɑ��
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);
	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==========================================
//�v���C���[�f�o�b�O�\��
//==========================================
void DebagDrawPlayer(void)
{
	Player* pPlayer = GetPlayer();

	RECT rectPosx = { 0,15,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT rectPosy = { 0,30,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStrPosx[128];
	char aStrPosy[128];

	//�����ɑ��
	sprintf(&aStrPosx[0], "PLAYER_POS_X:%.2f\n", pPlayer->pos.x);
	sprintf(&aStrPosy[0], "PLAYER_POS_Y:%.2f\n", pPlayer->pos.y);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStrPosx[0], -1, &rectPosx, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawText(NULL, &aStrPosy[0], -1, &rectPosy, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
//=============================
//�u���b�N�̃f�o�b�O�\��
//=============================
void DebagDrawBlock(void)
{
	//�u���b�N�����擾
	BLOCK* pBlock = GetBlock();

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++, pBlock++)
	{
		if (pBlock->bUse == true)
		{
			RECT rectPosx = { pBlock->pos.x,pBlock->pos.y,SCREEN_WIDTH,SCREEN_HEIGHT };

			char aStrPosx[64];

			//�����ɑ��
			sprintf(&aStrPosx[0],"%d\n", nCnt);

			//�e�L�X�g�̕`��
			g_pFont->DrawText(NULL, &aStrPosx[0], -1, &rectPosx, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
		}
	}
}

//=============================
//�G�l�~�[�̃f�o�b�O�\��
//=============================
void DebagDrawEnemy(void)
{
	int nNumEnemy = GetNumEnemy();	//�G�l�~�[�̑������擾
	ENEMY* pEnemy = GetEnemy();		//�G�l�~�[�����擾

	RECT rectPosx = {0,45,SCREEN_WIDTH,SCREEN_HEIGHT };

	char aStrPosx[64];

	//�����ɑ��
	sprintf(&aStrPosx[0], "NUMENEMY:%d\n", nNumEnemy);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStrPosx[0], -1, &rectPosx, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));



	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			RECT rectPosx = { pEnemy->pos.x,pEnemy->pos.y,SCREEN_WIDTH,SCREEN_HEIGHT };

			char aStrPosx[64];

			//�����ɑ��
			sprintf(&aStrPosx[0], "%d\n", nCnt);

			//�e�L�X�g�̕`��
			g_pFont->DrawText(NULL, &aStrPosx[0], -1, &rectPosx, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
		}
	}
}