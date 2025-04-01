#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "EnemyManager.h"
#include "Rocket.h"
#include "ColliderManager.h"

/*
실습1. z키를 입력해서 일반공격(미사일 1발씩 발사)
	   x키를 입력해서 폭탄 공격(화면 내의 적과 미사일 모두 삭제)

실습2. 특정 아이템 획득 시, z키를 입력 했을 때 일반 공격이 업그레이드(미사일 2발씩 발사)
	   특정 아이템을 하나 더 획득 하면, 한번 더 업그레이드(미사일이 4발씩 발사)
*/

void MainGame::Init()
{
	ImageManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();
	ColliderManager::GetInstance()->Init();

	hdc = GetDC(g_hWnd);


	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("백버퍼 생성 실패"), TEXT("경고"), MB_OK);
	}
	backGround = new Image();
	if (FAILED(backGround->Init(TEXT("Image/background1.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp 생성 실패"), TEXT("경고"), MB_OK);
	}


	enemyManager = new EnemyManager();
	enemyManager->Init();

	rocket = new Rocket();
	rocket->Init();
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

	ColliderManager::GetInstance()->Release();
	KeyManager::GetInstance()->Release();
	ImageManager::GetInstance()->Release();

}

void MainGame::Update()
{
	enemyManager->Update();
	rocket->Update();
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	// 백버퍼에 먼저 복사
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backGround->Render(hBackBufferDC);

	wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePosX, mousePosY);
	TextOut(hBackBufferDC, 20, 60, szText, wcslen(szText));

	enemyManager->Render(hBackBufferDC);
	rocket->Render(hBackBufferDC);

	TimerManager::GetInstance()->Render(hBackBufferDC);

	// 백버퍼에 있는 내용을 메인 hdc에 복사
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
