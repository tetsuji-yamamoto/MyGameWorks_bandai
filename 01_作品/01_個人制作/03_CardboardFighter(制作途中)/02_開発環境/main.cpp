#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "object2D.h"
#include <crtdbg.h>

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//�O���[�o���ϐ��錾
int g_nCountFPS = 0;
RECT g_windowRect;								//�E�B���h�E��؂�ւ��邽�߂̕ϐ�

//***********************************************
// ���C���֐�
//***********************************************
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev,_In_ LPSTR lpCmdLine,_In_ int nCmdShow)
{
	// ���������[�N���m
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);//���������[�N���m


	WNDCLASSEX wcex =					// �E�B���h�E�N���X�̍\����
	{									   
		sizeof(WNDCLASSEX),				// WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,						// �E�B���h�E�̃X�^�C��
		WindowProc,						// �E�B���h�E�v���V�[�W��
		0,								// 0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,								// 0�ɂ���(�ʏ�͎g�p���Ȃ�)	
		hInstance,						// �C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),	// �^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),		// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),		// �N���C�A���g�̈�̔w�i�F
		NULL,							// ���j���[�o�[
		CLASS_NAME,						// �E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)	// �t�@�C���̃A�C�R��
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	// ��ʃT�C�Y�̍\����
		
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;	// ���ݎ���
	DWORD dwExecLastTime;	// ���ݎ���
	DWORD dwFrameCount;		// �t���[���J�E���g
	DWORD dwFPSLastTime;	// �Ō��FPS���v����������

	// �E�B���h�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,		// �g���E�B���h�E�X�^�C��
		CLASS_NAME,					// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,				// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,				// �E�B���h�E����X���W
		CW_USEDEFAULT,				// �E�B���h�E����Y���W
		(rect.right - rect.left),	// �E�B���h�E�̕�
		(rect.bottom - rect.top),	// �E�B���h�E�̍���
		NULL,						// �e�E�B���h�E�̃n���h��
		NULL,						// ���j���[�n���h���܂��͎q�E�B���h�E�̃n���h��
		hInstance,					// �C���X�^���X�n���h��
		NULL);						// �E�B���h�E�����f�[�^

	// ����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);	// �E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);			// �N���C�A���g�̈���X�V

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	CManager* pManager = NULL;// �}�l�[�W���[�ւ̃|�C���^

	if (pManager == NULL)
	{// �k���ł����
		// �������m��
		pManager = new CManager;

		if (pManager != NULL)
		{// �m�ۂł��Ă����
			// �����_���[�̏�����
			pManager->Init(hInstance,hWnd,TRUE);
		}
		else
		{
			MessageBox(NULL, " WinMain() > if (pManager != NULL) > pManager���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " WinMain() > if(pManager == NULL) > pManager���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// windoes�̏���
			if (msg.message == WM_QUIT)
			{// WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				// ���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);	// ���z���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);	// �E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{// DilectX�̏���
			dwCurrentTime = timeGetTime();	// ���ݎ������擾
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b�o��
				// FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;											// FPS�𑪒肵����ۑ�
				dwFrameCount = 0;														// �t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 60�t���[��
			{
				dwExecLastTime = dwCurrentTime;
			
				CDebugprocc::Print("FPS : %d\n\n", g_nCountFPS);

				// �X�V����
				pManager->Update();

				// �`�揈��
				pManager->Draw();

				dwFrameCount++;	// �t���[���J�E���g�����Z
			}
		}
	}

	// �}�l�[�W���[�̔j��
	if (pManager != NULL)
	{// �k���łȂ�������
		// �}�l�[�W���[�̏I������
		pManager->Uninit();
		delete pManager;
		pManager = NULL;
	}

	if (pManager != NULL)
	{
		MessageBox(NULL, " WinMain() > if (pManager != NULL) > pManager��������NULL�ł͂���܂���", "Error", MB_OK);
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//***********************************************
// �E�B���h�E���t���X�N���[���ɕς��鏈��
//***********************************************
void ToggleFullscreen(HWND hWnd)
{
	static bool isFullscreen = true;	//�E�B���h�E��؂�ւ��邽�߂̃t���O

	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (isFullscreen)
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

	isFullscreen = !isFullscreen;
}

//***********************************************
//�E�B���h�v���V�[�W��
//***********************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;	// �߂�l���i�[
	switch (uMsg)
	{
	case WM_DESTROY:	// �E�B���h�j�����b�Z�[�W

		// WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:	// �L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:	// ESC�������ꂽ��
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				//�E�B���h�E��j������(EM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
			break;

		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}