#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "EnemyManager.h"
#include "Rocket.h"
#include "ColliderManager.h"
#include "ItemManager.h"

void MainGame::Init()
{
	ImageManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();
	UIManager::GetInstance()->Init();

	
	hdc = GetDC(g_hWnd);
	sceneState = SceneState::Lobby;
	elapsedTime = 0.0f;
	lobbyFrame = 0;
	mainFrame = 0;

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("BackBuffer Failed"), TEXT("Fail!"), MB_OK);
	}
	Lobby = new Image();
	if (FAILED(Lobby->Init(TEXT("Image/Cinematic.bmp"), WINSIZE_X * 40, WINSIZE_Y - 300, 40, 1)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/Cinematic.bmp"), TEXT("Fail!"), MB_OK);
	}
	startMenu = new Image();
	if (FAILED(startMenu->Init(TEXT("Image/mainmenu.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/mainmenu.bmp"), TEXT("Fail!"), MB_OK);
	}
	ImageManager::GetInstance()->AddImage("Ending", TEXT("Image/GameOver.bmp"), WINSIZE_X, WINSIZE_Y);
	backGround = new Image();
	if (FAILED(backGround->Init(TEXT("Image/backgroundspace.bmp"), WINSIZE_X, WINSIZE_Y * 8, 1, 8)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp"), TEXT("Fail!"), MB_OK);
	}
	sign = ImageManager::GetInstance()->AddImage("Sign", TEXT("Image/Sign.bmp"), 30, 20);

	ColliderManager::GetInstance()->Init();
	
	rocket = new Rocket();
	rocket->Init();
	
	itemManager = new ItemManager();
	itemManager->Init();

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

	if (itemManager)
	{
		itemManager->Release();
		delete itemManager;
		itemManager = nullptr;
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
	
	switch (sceneState)
	{
	case SceneState::Lobby:
		elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
		if (elapsedTime >= 0.07f)
		{
			lobbyFrame++;
			if (lobbyFrame >= 40)
			{
				UIManager::GetInstance()->Clear();
				UIManager::GetInstance()->AddText("Press 'S' to start", WINSIZE_X / 2 - 50, 300);
				sceneState = SceneState::Start;
			}
			elapsedTime = 0.0f;
		}
		break;
	case SceneState::Start:
		if (KeyManager::GetInstance()->IsOnceKeyDown(83))
		{
			UIManager::GetInstance()->Clear();
			UIManager::GetInstance()->InitMainSceneUI();
			sceneState = SceneState::Main;
			PlaySound(TEXT("BGM.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
		}
		break;
	case SceneState::Main:
		elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
		if (elapsedTime > 0.07f)
		{
			mainFrame++;
			if (mainFrame >= 8)
			{
				mainFrame = 0;
			}
			elapsedTime = 0.0f;
		}
		EnemyManager::GetInstance()->Update();
		rocket->Update();
		itemManager->Update();
		ColliderManager::GetInstance()->Update();
		if (!rocket->GetIsAlive())
		{
			UIManager::GetInstance()->Clear();
			sceneState = SceneState::End;
			UIManager::GetInstance()->AddImage("Sign", TEXT("Image/Sign.bmp"), WINSIZE_X - 100, WINSIZE_Y - 80, 100, 80);
			Lobby = ImageManager::GetInstance()->FindImage("Ending");
		}
		break;
	case SceneState::End:
		break;
	}
	
	
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	HDC hBackBufferDC = backBuffer->GetMemDC();
	switch (sceneState)
	{
	case SceneState::Lobby:
		Lobby->FrameRender(hBackBufferDC, WINSIZE_X / 2, WINSIZE_Y / 2, lobbyFrame, 0);
		break;
	case SceneState::Start:
		startMenu->Render(hBackBufferDC);
		UIManager::GetInstance()->Render(hBackBufferDC);
		break;
	case SceneState::Main:
		backGround->FrameRender(hBackBufferDC, WINSIZE_X / 2, WINSIZE_Y / 2, 0, mainFrame);

		wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePosX, mousePosY);
		TextOut(hBackBufferDC, 20, 60, szText, wcslen(szText));

		EnemyManager::GetInstance()->Render(hBackBufferDC);
		rocket->Render(hBackBufferDC);
		itemManager->Render(hBackBufferDC);
		UIManager::GetInstance()->Render(hBackBufferDC);
		ColliderManager::GetInstance()->Render(hBackBufferDC);
		TimerManager::GetInstance()->Render(hBackBufferDC);
		break;
	case SceneState::End:
		Lobby->Render(hBackBufferDC);
		UIManager::GetInstance()->Render(hBackBufferDC);
		break;
	}
	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
	case WM_KEYDOWN:

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
