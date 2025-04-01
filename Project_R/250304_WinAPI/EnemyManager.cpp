#include "EnemyManager.h"
#include "Enemy.h"

void EnemyManager::Init()
{
    spawnInterval = 2;       // 적 생성 주기 (초 단위)
    elapsedTime = 0.0f;      // 시작 시간
    maxEnemies = 10;         // 최대 생성되는 적 수
    spawnPattern = 0;        // 기본적으로 일렬로 생성

    // 초기 적들을 일렬로 배치 (간격 설정)
    for (int i = 0; i < maxEnemies; i++)
    {
        AddEnemy();  // 적 추가
    }
}

void EnemyManager::Release()
{
    for (int i = 0; i < vecEnemys.size(); i++)
    {
        delete vecEnemys[i];
    }
    vecEnemys.clear();
}

void EnemyManager::Update()
{
    elapsedTime += 0.016f;

    // 일정 시간이 지나면 새로운 적을 추가
    if (elapsedTime >= spawnInterval)
    {
        elapsedTime = 0.0f;  // 타이머 리셋
        if (vecEnemys.size() < maxEnemies)  // 최대 적 수보다 적을 생성
        {
            AddEnemy();
        }
    }

    // 생성된 적들 업데이트
    for (int i = 0; i < vecEnemys.size(); i++)
    {
        vecEnemys[i]->Update();
    }
}

void EnemyManager::Render(HDC hdc)
{
    for (int i = 0; i < vecEnemys.size(); i++)
    {
        vecEnemys[i]->Render(hdc);
    }
}

void EnemyManager::AddEnemy()
{
    Enemy* newEnemy = new Enemy();
    float spawnX = 0.0f;
    float spawnY = 0.0f;

    spawnX = 10.0f + (rand() % 5) * 60.0f;  // X 좌표 랜덤화 (간격 조정)
    spawnY = 80.0f + (rand() % 3) * 90.0f; // Y 좌표 랜덤화 (간격 조정)

    newEnemy->Init(spawnX, spawnY);
    vecEnemys.push_back(newEnemy);
}

void EnemyManager::SetSpawnPattern(int pattern)
{

    for (int i = 0; i < vecEnemys.size(); i++)      // 기존 적들 삭제
    {
        delete vecEnemys[i];
    }
    vecEnemys.clear();

    switch (pattern)
    {
    case 0:
        for (int i = 0; i < 10; i++)
        {
            vecEnemys.push_back(new Enemy());
            vecEnemys[i]->Init(10.0f + 60.0f * (i % 5), 80.0f + 90.0f * (i / 5));
        }
        break;
    case 1:
        for (int i = 0; i < 10; i++)
        {
            vecEnemys.push_back(new Enemy());
            float randomX = rand() % WINSIZE_X;
            float randomY = rand() % WINSIZE_Y;
            vecEnemys[i]->Init(randomX, randomY);
        }
        break;
    case 2:
        for (int i = 0; i < 10; i++)
        {
            vecEnemys.push_back(new Enemy());
            vecEnemys[i]->Init(50.0f * (i % 5), 100.0f + 50.0f * (i / 5));
        }
        break;
    case 3:
        for (int i = 0; i < 10; i++)
        {
            vecEnemys.push_back(new Enemy());
            float randomX = 100.0f * i;
            float randomY = (i % 2 == 0) ? 100.0f : 150.0f;
            vecEnemys[i]->Init(randomX, randomY);
        }
        break;
    }
}

