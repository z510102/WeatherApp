//=============================================================================
// ���C������ [main.cpp]
// Author : ���� ��
//=============================================================================
#include "main.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"		// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"��o�p"		// �E�C���h�E�̃L���v�V������(�Q�[����)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
#ifdef _DEBUG
int	g_nCountFPS;	// FPS�J�E���^
#endif

//=============================================================================
// ���C���֐�
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �\���̂̐ݒ�
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	HWND hWnd;				//�E�B���h�E�n���h��(���ʎq)
	MSG msg;				//���b�Z�[�W���i�[����ϐ�
	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwFrameCount;		//�t���[���J�E���g
	DWORD dwExecLastTime;	//�������s�ŏI����
	DWORD dwFPSLastTime;	//FPS�v��ŏI����

							// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	// �}�l�[�W���[�N���X�̐錾
	CManager *pManager = NULL;

	// �k���`�F�b�N
	if (pManager == NULL)
	{
		// �}�l�[�W���[�N���X�̐���
		pManager = new CManager();
	}

	// �}�l�[�W���[�N���X�̏�����
	if (FAILED(pManager->Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	// �t���[���J�E���g������
	dwCurrentTime = dwFrameCount = 0;
	dwExecLastTime = dwFPSLastTime = timeGetTime();

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	// ���݂̎��Ԃ��擾
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b���ƂɎ��s
#ifdef _DEBUG
			 // FPS���Z�o
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				// ���݂̎��Ԃ�ۑ�
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			// 1/60�b�o��
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				// ���݂̎��Ԃ�ۑ�
				dwExecLastTime = dwCurrentTime;

				// �}�l�[�W���[�N���X�̍X�V
				pManager->Update();

				// �}�l�[�W���[�N���X�̕`��
				pManager->Draw();

				dwFrameCount++;
			}
		}
	}

	// �}�l�[�W���[�N���X�̔j��
	if (pManager != NULL)
	{
		// �I������
		pManager->Uninit();

		// �������̊J��
		delete pManager;
		pManager = NULL;
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// ����\��߂�
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;

		// �E�B���h�E�j�󃁃b�Z�[�W
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W��Ԃ�
		PostQuitMessage(0);
		break;

		// �L�[���������Ƃ��ɕ���
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:				// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);	// �E�B���h�E��j������悤�w������
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// FPS�̎擾����
//=============================================================================
#ifdef _DEBUG
int GetCntFPS(void)
{
	return g_nCountFPS;
}
#endif