#include "EnemyManager.h"
#include "Enemy.h"

void EnemyManager::Init()
{
    spawnInterval = 2;       // �� ���� �ֱ� (�� ����)
    elapsedTime = 0.0f;      // ���� �ð�
    maxEnemies = 10;         // �ִ� �����Ǵ� �� ��
    spawnPattern = 0;        // �⺻������ �Ϸķ� ����

    // �ʱ� ������ �Ϸķ� ��ġ (���� ����)
    for (int i = 0; i < maxEnemies; i++)
    {
        AddEnemy();  // �� �߰�
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

    // ���� �ð��� ������ ���ο� ���� �߰�
    if (elapsedTime >= spawnInterval)
    {
        elapsedTime = 0.0f;  // Ÿ�̸� ����
        if (vecEnemys.size() < maxEnemies)  // �ִ� �� ������ ���� ����
        {
            AddEnemy();
        }
    }

    // ������ ���� ������Ʈ
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

    spawnX = 10.0f + (rand() % 5) * 60.0f;  // X ��ǥ ����ȭ (���� ����)
    spawnY = 80.0f + (rand() % 3) * 90.0f; // Y ��ǥ ����ȭ (���� ����)

    newEnemy->Init(spawnX, spawnY);
    vecEnemys.push_back(newEnemy);
}

void EnemyManager::SetSpawnPattern(int pattern)
{

    for (int i = 0; i < vecEnemys.size(); i++)      // ���� ���� ����
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

