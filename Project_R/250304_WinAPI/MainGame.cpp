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
        MessageBox(g_hWnd, TEXT("����� ���� ����"), TEXT("���"), MB_OK);
    }
    backGround = new Image();
    if (FAILED(backGround->Init(TEXT("Image/background1.bmp"), WINSIZE_X, WINSIZE_Y)))
    {
        MessageBox(g_hWnd, TEXT("Image/backGround.bmp ���� ����"), TEXT("���"), MB_OK);
    }

    // EnemyManager �ʱ�ȭ
    enemyManager = new EnemyManager();
    enemyManager->Init();

    enemyManager->SetSpawnPattern(0);  // 0�� ������ �⺻������ ����

    // ���� �ʱ�ȭ
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
    // ���� ��ġ �� ���� ������Ʈ
    enemyManager->Update();

    // ���� ������Ʈ
    rocket->Update();

    // ������ ����
    InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
    // ����ۿ� ���� ����
    HDC hBackBufferDC = backBuffer->GetMemDC();

    backGround->Render(hBackBufferDC);

    wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePosX, mousePosY);
    TextOut(hBackBufferDC, 20, 60, szText, wcslen(szText));

    // �� �� ���� ������
    enemyManager->Render(hBackBufferDC);
    rocket->Render(hBackBufferDC);

    TimerManager::GetInstance()->Render(hBackBufferDC);

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
