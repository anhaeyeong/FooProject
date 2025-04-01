#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "EnemyManager.h"
#include "Rocket.h"
#include "ColliderManager.h"

/*
�ǽ�1. zŰ�� �Է��ؼ� �Ϲݰ���(�̻��� 1�߾� �߻�)
	   xŰ�� �Է��ؼ� ��ź ����(ȭ�� ���� ���� �̻��� ��� ����)

�ǽ�2. Ư�� ������ ȹ�� ��, zŰ�� �Է� ���� �� �Ϲ� ������ ���׷��̵�(�̻��� 2�߾� �߻�)
	   Ư�� �������� �ϳ� �� ȹ�� �ϸ�, �ѹ� �� ���׷��̵�(�̻����� 4�߾� �߻�)
*/

void MainGame::Init()
{
	ImageManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();
	UIManager::GetInstance()->Init();

	UIManager::GetInstance()->AddText("Press 'S' to start", WINSIZE_X / 2, WINSIZE_Y / 2);

	hdc = GetDC(g_hWnd);
	sceneState = SceneState::Lobby;

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT(""), TEXT(""), MB_OK);
	}
	Lobby = new Image();
	if (FAILED(Lobby->Init(TEXT("Image/mainmenu.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/mainmenu.bmp "), TEXT(""), MB_OK);
	}
	backGround = new Image();
	if (FAILED(backGround->Init(TEXT("Image/background1.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp "), TEXT(""), MB_OK);
	}

	ColliderManager::GetInstance()->Init();

	enemyManager = new EnemyManager();
;	enemyManager->Init();
	
	rocket = new Rocket();
	rocket->Init();
	ColliderManager::GetInstance()->SetRocket(rocket);
}

void MainGame::Release()
{
	if (enemyManager)
	{
		enemyManager->Release();
		delete enemyManager;
		enemyManager = nullptr;
	}

	if (rocket)
	{
		rocket->Release();
		delete rocket;
		rocket = nullptr;
	}

	if (backGround)
	{
		backGround->Release();
		delete backGround;
		backGround = nullptr;
	}

	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}
	ReleaseDC(g_hWnd, hdc);

	UIManager::GetInstance()->Release();
	KeyManager::GetInstance()->Release();
	ImageManager::GetInstance()->Release();

}

void MainGame::Update()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(83))
	{
		UIManager::GetInstance()->Clear();
		sceneState = SceneState::Main;
	}
	if (sceneState == SceneState::Main)
	{
		enemyManager->Update();
		rocket->Update();
	}
	
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	// ����ۿ� ���� ����
	
	HDC hBackBufferDC = backBuffer->GetMemDC();
	switch (sceneState)
	{
	case SceneState::Lobby:
		Lobby->Render(hBackBufferDC);
		UIManager::GetInstance()->Render(hBackBufferDC);
		break;
	case SceneState::Main:
		backGround->Render(hBackBufferDC);

		wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePosX, mousePosY);
		TextOut(hBackBufferDC, 20, 60, szText, wcslen(szText));

		enemyManager->Render(hBackBufferDC);
		rocket->Render(hBackBufferDC);
		ColliderManager::GetInstance()->Render(hBackBufferDC);
		TimerManager::GetInstance()->Render(hBackBufferDC);
		break;
	case SceneState::End:
		break;
	}

	// ����ۿ� �ִ� ������ ���� hdc�� ����
	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'a': case 'A':
			break;
		case 'd': case 'D':
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		mousePos.x = LOWORD(lParam);
		mousePos.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}
