#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "EnemyManager.h"
#include "Rocket.h"

void MainGame::Init()
{
    ImageManager::GetInstance()->Init();
    KeyManager::GetInstance()->Init();

    hdc = GetDC(g_hWnd);

    backBuffer = new Image();
    if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
    {
        MessageBox(g_hWnd, TEXT("백버퍼 생성 실패"), TEXT("경고"), MB_OK);
    }
    backGround = new Image();
    if (FAILED(backGround->Init(TEXT("Image/background1.bmp"), WINSIZE_X, WINSIZE_Y)))
    {
        MessageBox(g_hWnd, TEXT("Image/backGround.bmp 생성 실패"), TEXT("경고"), MB_OK);
    }

    // EnemyManager 초기화
    enemyManager = new EnemyManager();
    enemyManager->Init();

    enemyManager->SetSpawnPattern(0);  // 0번 패턴을 기본값으로 설정

    // 로켓 초기화
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

    KeyManager::GetInstance()->Release();
    ImageManager::GetInstance()->Release();
}

void MainGame::Update()
{
    // 적의 위치 및 상태 업데이트
    enemyManager->Update();

    // 로켓 업데이트
    rocket->Update();

    // 윈도우 갱신
    InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
    // 백버퍼에 먼저 복사
    HDC hBackBufferDC = backBuffer->GetMemDC();

    backGround->Render(hBackBufferDC);

    wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePosX, mousePosY);
    TextOut(hBackBufferDC, 20, 60, szText, wcslen(szText));

    // 적 및 로켓 렌더링
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
        case 'q': case 'Q':
            enemyManager->SetSpawnPattern(1);
            break;
        case 'w': case 'W':
            enemyManager->SetSpawnPattern(2);
            break;
        case 'e': case 'E':
            enemyManager->SetSpawnPattern(3);
            break;
        case 'r': case 'R':
            enemyManager->SetSpawnPattern(4);
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
